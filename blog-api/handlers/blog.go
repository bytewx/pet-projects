package handlers

import (
	"encoding/json"
	"github.com/gorilla/mux"
	"log"
	"net/http"
	"strconv"
	"time"

	"blog-api/config"
	"blog-api/models"
)

func CreateBlog(w http.ResponseWriter, r *http.Request) {
	log.Println("POST", r.URL.Path)
	var blog models.Blog
	if err := json.NewDecoder(r.Body).Decode(&blog); err != nil {
		http.Error(w, "Invalid input", http.StatusBadRequest)
		return
	}
	if err := config.DB.Create(&blog).Error; err != nil {
		http.Error(w, "Failed to create blog", http.StatusInternalServerError)
		return
	}
	w.WriteHeader(http.StatusCreated)
	err := json.NewEncoder(w).Encode(blog)
	if err != nil {
		return 
	}
}

func GetBlogs(w http.ResponseWriter, r *http.Request) {
	var blogs []models.Blog
	config.DB.Find(&blogs)
	err := json.NewEncoder(w).Encode(blogs)
	if err != nil {
		return
	}
}

func GetBlog(w http.ResponseWriter, r *http.Request) {
	id, _ := strconv.Atoi(mux.Vars(r)["id"])
	var blog models.Blog
	result := config.DB.First(&blog, id)
	if result.Error != nil {
		http.Error(w, "Blog not found", http.StatusNotFound)
		return
	}
	err := json.NewEncoder(w).Encode(blog)
	if err != nil {
		return 
	}
}

func UpdateBlog(w http.ResponseWriter, r *http.Request) {
	id, _ := strconv.Atoi(mux.Vars(r)["id"])
	var blog models.Blog
	if err := config.DB.First(&blog, id).Error; err != nil {
		http.Error(w, "Blog not found", http.StatusNotFound)
		return
	}
	var updated models.Blog
	if err := json.NewDecoder(r.Body).Decode(&updated); err != nil {
		http.Error(w, "Invalid input", http.StatusBadRequest)
		return
	}
	updated.UpdatedAt = time.Now()
	config.DB.Model(&blog).Updates(updated)
	err := json.NewEncoder(w).Encode(blog)
	if err != nil {
		return 
	}
}

func DeleteBlog(w http.ResponseWriter, r *http.Request) {
	id, _ := strconv.Atoi(mux.Vars(r)["id"])
	if err := config.DB.Delete(&models.Blog{}, id).Error; err != nil {
		http.Error(w, "Delete failed", http.StatusInternalServerError)
		return
	}
	w.Write([]byte(`{"status":"deleted"}`))
}
