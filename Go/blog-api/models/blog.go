package models

import (
	"gorm.io/datatypes"
	"time"
)

type Blog struct {
	ID        uint           `gorm:"primaryKey" json:"id"`
	Title     string         `json:"title"`
	Content   string         `json:"content"`
	Category  string         `json:"category"`
	Tags      datatypes.JSON `gorm:"type:json" json:"tags"`
	CreatedAt time.Time      `json:"createdAt"`
	UpdatedAt time.Time      `json:"updatedAt"`
}
