package routers

import (
	"github.com/gorilla/mux"
	"to-do-api/services"
)

func InitializeRouter() *mux.Router {
	router := mux.NewRouter()

	router.HandleFunc("/todos", services.GetAllTodos).Methods("GET")
	router.HandleFunc("/todos/{id}", services.GetTodo).Methods("GET")
	router.HandleFunc("/createTodo", services.CreateTodo).Methods("POST")
	router.HandleFunc("/updateTodo/{id}", services.UpdateTodo).Methods("PUT")
	router.HandleFunc("/deleteTodo/{id}", services.DeleteTodo).Methods("DELETE")

	return router
}
