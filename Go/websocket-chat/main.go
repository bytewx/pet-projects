package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strings"
	"sync"

	"github.com/gorilla/websocket"
)

type ChatRoom struct {
	Name      string
	Clients   map[*websocket.Conn]string
	Broadcast chan string
	History   []string
	Mu        sync.Mutex
}

func NewChatRoom(name string) *ChatRoom {
	return &ChatRoom{
		Name:      name,
		Clients:   make(map[*websocket.Conn]string),
		Broadcast: make(chan string),
	}
}

func (r *ChatRoom) Run() {
	for msg := range r.Broadcast {
		r.Mu.Lock()
		r.History = append(r.History, msg)
		if len(r.History) > 50 {
			r.History = r.History[len(r.History)-50:]
		}
		for c := range r.Clients {
			err := c.WriteMessage(websocket.TextMessage, []byte(msg))
			if err != nil {
				fmt.Println("error happened during writing the message: ", err)
				return
			}
		}
		r.Mu.Unlock()
	}
}

func (r *ChatRoom) SendUserList() {
	r.Mu.Lock()
	defer r.Mu.Unlock()

	userList := "Online: "
	first := true
	for _, name := range r.Clients {
		if !first {
			userList += ", "
		}
		userList += name
		first = false
	}

	for c := range r.Clients {
		err := c.WriteMessage(websocket.TextMessage, []byte(userList))
		if err != nil {
			fmt.Println("error happened during writing the message: ", err)
			return
		}
	}
}

var rooms = map[string]*ChatRoom{
	"gophers":              NewChatRoom("Gophers"),
	"gophers (but better)": NewChatRoom("Gophers (but better)"),
}

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool { return true },
}

func serveHome(w http.ResponseWriter, r *http.Request) {
	tmpl, _ := template.ParseFiles("static/index.html")
	err := tmpl.Execute(w, rooms)
	if err != nil {
		fmt.Println("error happened during serving the page: ", err)
		return
	}
}

func handleWS(w http.ResponseWriter, r *http.Request) {
	roomName := r.URL.Query().Get("room")
	user := r.URL.Query().Get("user")

	room, ok := rooms[roomName]
	if !ok {
		http.Error(w, "invalid room", http.StatusBadRequest)
		return
	}

	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println("upgrade:", err)
		return
	}

	room.Mu.Lock()
	room.Clients[conn] = user
	room.Mu.Unlock()

	room.Mu.Lock()
	for _, msg := range room.History {
		err := conn.WriteMessage(websocket.TextMessage, []byte(msg))
		if err != nil {
			fmt.Println("error happened during writing the message: ", err)
			return
		}
	}
	room.Mu.Unlock()

	room.SendUserList()
	room.Broadcast <- fmt.Sprintf("%s joined the chat!", user)

	defer func() {
		room.Mu.Lock()
		delete(room.Clients, conn)
		room.Mu.Unlock()
		room.Broadcast <- fmt.Sprintf("%s left the chat.", user)
		room.SendUserList()
		err := conn.Close()
		if err != nil {
			fmt.Println("error happened during closing the connection: ", err)
			return
		}
	}()

	for {
		_, msg, err := conn.ReadMessage()
		if err != nil {
			break
		}
		text := strings.TrimSpace(string(msg))
		if text != "" {
			room.Broadcast <- fmt.Sprintf("[%s] %s: %s", room.Name, user, text)
		}
	}
}

func main() {
	for _, room := range rooms {
		go room.Run()
	}

	http.HandleFunc("/", serveHome)
	http.HandleFunc("/ws", handleWS)
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))

	fmt.Println("Server running at http://localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}
