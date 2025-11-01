package main

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"grpc-messenger/grpc-messenger/messenger"
	"io"
	"log"
	"time"
)

func main() {
	conn, err := grpc.NewClient("localhost:8001", grpc.WithTransportCredentials(insecure.NewCredentials()))

	if err != nil {
		log.Fatalln("Error happened during client opening: ", err)
	}

	defer func(conn *grpc.ClientConn) {
		err := conn.Close()
		if err != nil {
			log.Fatalln("Error happened during connection closing: ", err)
		}
	}(conn)

	client := messenger.NewMessengerClient(conn)

	res, err := client.SendMessage(context.Background(), &messenger.MessageRequest{
		Author:  "byte",
		Content: "hello",
	})

	if err != nil {
		log.Fatalln("Error happened during message sending: ", err)
	}

	log.Printf("Response: %v", res)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)

	defer cancel()

	stream, err := client.GetMessages(ctx, &messenger.Empty{})

	if err != nil {
		log.Fatalln("Error happened during message stream creation: ", err)
	}

	log.Println("Listening for streamed messages.")

	for {
		msg, err := stream.Recv()

		if err == io.EOF {
			log.Println("End of stream")
			break
		}

		if err != nil {
			log.Fatalln("Error happened during stream receiving: ", err)
		}

		log.Printf("New message: %s: %s (timestamp = %d)\n", msg.Author, msg.Content, msg.Timestamp)
	}
}
