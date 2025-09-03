package tests

import (
	"github.com/DATA-DOG/go-sqlmock"
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"io"
	"log"
	"net/http"
	"net/http/httptest"
	"testing"
)

func setupMockDB(t *testing.T) (*gorm.DB, sqlmock.Sqlmock) {
	mockDB, mock, err := sqlmock.New()

	if err != nil {
		t.Fatalf("Failed to open mock SQL DB, %v", err)
	}

	dialector := mysql.New(mysql.Config{
		Conn:                      mockDB,
		SkipInitializeWithVersion: true,
	})

	db, err := gorm.Open(dialector, &gorm.Config{})

	if err != nil {
		t.Fatalf("Failed to open GORM DB, %v", err)
	}

	return db, mock
}

func TestGetToDos(t *testing.T) {
	_, mock := setupMockDB(t)

	rows := sqlmock.NewRows([]string{"id", "title", "description", "completed", "created_at", "updated_at"}).
		AddRow(1, "Title 1", "Content 1", true, "2024-01-01", "2024-01-01").
		AddRow(2, "Title 2", "Content 2", false, "2024-01-02", "2024-01-02")

	mock.ExpectQuery("SELECT (.+) FROM `todos`").WillReturnRows(rows)

	w := httptest.NewRecorder()

	res := w.Result()

	defer func(Body io.ReadCloser) {
		err := Body.Close()

		if err != nil {
			log.Fatal(err)
		}
	}(res.Body)

	if res.StatusCode != http.StatusOK {
		t.Errorf("Expected status 200 OK, got %v", res.StatusCode)
	}
}
