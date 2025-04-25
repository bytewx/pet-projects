# Blog API

A simple, RESTful API for a blogging platform built with Go, Gorilla Mux, GORM, and MySQL. This API allows users to create, read, update, and delete blog posts.

## Features

- **CRUD Operations**: Create, Read, Update, and Delete blog posts.
- **Database Integration**: MySQL database with GORM for ORM-based interactions.
- **Environment Configuration**: `.env` support for easy configuration.

## Requirements

- Go 1.18+ 
- MySQL 5.7+
- Docker (optional, for containerization)

## Installation

1. **Clone the repository**

 ```bash
 git clone https://github.com/yourusername/blog-api.git
 cd blog-api
 ```

2. **Set up your environment variables**

 Create a `.env` file in the root of your project with the following variables:

```env
DB_USER=root
DB_PASSWORD=password
DB_NAME=blogdb
DB_HOST=localhost
DB_PORT=3306
```

3. **Install dependencies**

```
go mod tidy
```

4. **Run application locally**

```
go run main.go
```

## Dockerization (optional)

1. **Build a Docker image**

```
docker build -t blog-api .
```

2. **Run the Docker container**

```
docker run -p 8080:8080 --env-file .env blog-api
```

## Testing

1. **Run the tests**

```
go test ./...
```
