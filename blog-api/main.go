package main

import (
	"blog-api/config"
	"blog-api/models"
	"blog-api/routers"
	"log"
	"net/http"
)

func main() {
	config.InitDB()
	err := config.DB.AutoMigrate(&models.Blog{})
	if err != nil {
		return
	}

	router := routes.InitRouter()

	log.Println("Server running on http://127.0.0.1:8000")
	log.Fatal(http.ListenAndServe(":8000", router))
}
