package main

import (
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"log"
	"net/http"
)

var DB *gorm.DB

type Course struct {
	ID          uint   `json:"id" gorm:"primary_key"`
	Name        string `json:"name"`
	Description string `json:"description"`
	Category    string `json:"category"`
	Enabled     bool   `json:"enabled"`
}

func InitDB() {
	dsn := "root:@tcp(127.0.0.1:3306)/learning_platform?charset=utf8mb4&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", dsn)

	if err != nil {
		log.Fatal("Failed to connect to database:", err)
	}

	DB = db
	log.Println("Connected to database")
}

func GetCourses(w http.ResponseWriter, _ *http.Request) {
	var courses []Course
	DB.Find(&courses)
	err := json.NewEncoder(w).Encode(courses)

	if err != nil {
		log.Fatalf("Failed to encode response: %v", err)
	}
}

func GetCourse(w http.ResponseWriter, r *http.Request) {
	params := mux.Vars(r)

	id := params["id"]

	var course Course

	if err := DB.First(&course, "id = ?", id).Error; err != nil {
		http.Error(w, "Course not found", http.StatusNotFound)

		return
	}

	err := json.NewEncoder(w).Encode(course)

	if err != nil {
		log.Fatalf("Failed to encode response: %v", err)
	}
}

func CreateCourse(w http.ResponseWriter, r *http.Request) {
	var course Course

	err := json.NewDecoder(r.Body).Decode(&course)

	if err != nil {
		log.Fatalf("Failed to decode request body: %v", err)
	}

	DB.Create(&course)

	err = json.NewEncoder(w).Encode(course)

	if err != nil {
		log.Fatalf("Failed to encode response: %v", err)
	}
}

func UpdateCourse(w http.ResponseWriter, r *http.Request) {
	params := mux.Vars(r)

	id := params["id"]

	var course Course

	if err := DB.First(course, "id = ?", id).Error; err != nil {
		http.Error(w, "Course not found", http.StatusNotFound)

		return
	}

	if err := json.NewDecoder(r.Body).Decode(&course); err != nil {
		http.Error(w, "Failed to decode request body: " + err.Error(), http.StatusBadRequest)

		return
	}

	DB.Save(&course)

	err := json.NewEncoder(w).Encode(course)

	if err != nil {
		log.Fatalf("Failed to encode response: %v", err)
	}
}

func DeleteCourse(w http.ResponseWriter, r *http.Request) {
	params := mux.Vars(r)

	id := params["id"]

	var course Course

	if err := DB.First(&course, "id = ?", id).Error; err != nil {
		http.Error(w, "Course not found", http.StatusNotFound)

		return
	}

	DB.Delete(&course)

	err := json.NewEncoder(w).Encode(course)

	if err != nil {
		log.Fatalf("Failed to encode response: %v", err)
	}
}

func main() {
	InitDB()
	router := mux.NewRouter()

	router.HandleFunc("/courses", GetCourses).Methods("GET")
	router.HandleFunc("/courses", CreateCourse).Methods("POST")
	router.HandleFunc("/courses/{id}", GetCourse).Methods("GET")
	router.HandleFunc("/courses/{id}", UpdateCourse).Methods("PUT")
	router.HandleFunc("/courses/{id}", DeleteCourse).Methods("DELETE")

	fmt.Println("Server is running on port 8080")

	log.Fatal(http.ListenAndServe(":8080", router))
}