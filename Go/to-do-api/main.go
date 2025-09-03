package main

import (
	"log"
	"net/http"
	"to-do-api/config"
	"to-do-api/models"
	"to-do-api/routers"
)

func main() {
	config.InitializeDB()

	err := config.DB.AutoMigrate(&models.ToDo{})

	if err != nil {
		log.Fatal("Error occurred during migration", err)
	}

	router := routers.InitializeRouter()

	log.Println("Server running on http://localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", router))
}
