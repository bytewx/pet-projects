package main

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
	"grpc-messenger/grpc-messenger/messenger"
	"log"
	"net"
	"time"
)

type Server struct {
	messenger.UnimplementedMessengerServer
}

func newServer() *Server {
	return &Server{}
}

func (s *Server) SendMessage(ctx context.Context, in *messenger.MessageRequest) (*messenger.MessageResponse, error) {
	return &messenger.MessageResponse{
		Author:    in.Author,
		Content:   in.Content,
		Timestamp: 123456789,
	}, nil
}

func (s *Server) GetMessages(_ *messenger.Empty, stream messenger.Messenger_GetMessagesServer) error {
	messages := []messenger.MessageResponse{
		{Author: "Alice", Content: "Alice's message", Timestamp: 1},
		{Author: "Bob", Content: "Bob's message", Timestamp: 2},
		{Author: "Mary", Content: "Mary's message", Timestamp: 3},
	}

	for i := range messages {
		if err := stream.Send(&messages[i]); err != nil {
			return err
		}

		time.Sleep(1 * time.Second)
	}

	return nil
}

func main() {
	lis, err := net.Listen("tcp", ":8001")

	if err != nil {
		log.Fatalln("Error happened during creation of the connection: ", err)
	}

	s := grpc.NewServer()

	messenger.RegisterMessengerServer(s, &Server{})

	reflection.Register(s)

	log.Println("Serving gRPC on 0.0.0.0:8001")

	log.Fatalln(s.Serve(lis))
}
