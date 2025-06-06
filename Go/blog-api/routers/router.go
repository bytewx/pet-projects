package routes

import (
	"blog-api/handlers"
	"github.com/gorilla/mux"
)

func InitRouter() *mux.Router {
	router := mux.NewRouter()

	router.HandleFunc("/blogs", handlers.GetBlogs).Methods("GET")
	router.HandleFunc("/blog/{id}", handlers.GetBlog).Methods("GET")
	router.HandleFunc("/createBlog", handlers.CreateBlog).Methods("POST")
	router.HandleFunc("/updateBlog/{id}", handlers.UpdateBlog).Methods("PUT")
	router.HandleFunc("/deleteBlog/{id}", handlers.DeleteBlog).Methods("DELETE")

	return router
}
