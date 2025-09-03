package services

import (
	"encoding/json"
	"github.com/gorilla/mux"
	"log"
	"net/http"
	"strconv"
	"time"
	"to-do-api/config"
	"to-do-api/models"
)

func CreateTodo(w http.ResponseWriter, r *http.Request) {
	log.Println("POST", r.URL.Path)

	var toDo models.ToDo

	if err := json.NewDecoder(r.Body).Decode(&toDo); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
	}

	if err := config.DB.Create(&toDo).Error; err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	w.WriteHeader(http.StatusCreated)

	err := json.NewEncoder(w).Encode(toDo)

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func GetAllTodos(w http.ResponseWriter, r *http.Request) {
	log.Println("GET", r.URL.Path)

	var toDos []models.ToDo

	config.DB.Find(&toDos)

	err := json.NewEncoder(w).Encode(toDos)

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func GetTodo(w http.ResponseWriter, r *http.Request) {
	log.Println("GET", r.URL.Path)

	id, _ := strconv.Atoi(mux.Vars(r)["id"])

	var toDo models.ToDo

	result := config.DB.First(&toDo, id)

	if result.Error != nil {
		http.Error(w, "Error occurred during retrieving a to-do.", http.StatusBadRequest)
	}

	err := json.NewEncoder(w).Encode(toDo)

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func UpdateTodo(w http.ResponseWriter, r *http.Request) {
	log.Println("PUT", r.URL.Path)

	id, _ := strconv.Atoi(mux.Vars(r)["id"])

	var toDo models.ToDo

	result := config.DB.First(&toDo, id)

	if result.Error != nil {
		http.Error(w, "Error occurred during retrieving a to-do.", http.StatusBadRequest)
	}

	var updatedToDo models.ToDo

	if err := json.NewDecoder(r.Body).Decode(&updatedToDo); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
	}

	updatedToDo.UpdatedAt = time.Now()

	config.DB.Model(&toDo).Updates(updatedToDo)

	err := json.NewEncoder(w).Encode(updatedToDo)

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func DeleteTodo(w http.ResponseWriter, r *http.Request) {
	log.Println("DELETE", r.URL.Path)

	id, _ := strconv.Atoi(mux.Vars(r)["id"])

	if err := config.DB.Delete(&models.ToDo{}, id).Error; err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	_, err := w.Write([]byte(`{"status": "deleted"}`))

	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}
