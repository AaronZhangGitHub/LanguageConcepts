package main

import (
	"fmt"
	"log"
	"net"
  "bufio"
  "time"
)

type client chan<- string // an outgoing message channel

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		// 1. Send the message to all the clients
		case msg := <-messages:
      for cli := range clients{
        select{
          case cli <- msg:
      }
    }
		// 2. Update the clients map
		case cli := <-entering:
      clients[cli] = true
		// 3. Update the clients map and close the client channel
		case cli := <-leaving:
      delete(clients,cli)
      close(cli)
		}
	}
}

func handleConn(conn net.Conn) {
  timer := time.NewTimer(60*time.Second)
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	// Client's IP address
	who := conn.RemoteAddr().String()

	// 1. Send a message to the new client confirming their identity
	// e.g. "You are 1.2.3"
  ch<-"You are "+who
  go clientWriter(conn,ch)
	// 2. Broadcast a message to all the clients that a new client has joined
	// e.g. "1.2.3. has joined"
  messages<-who+" has joined"
	// 3. Send the client to the entering channel
  entering<-ch
	// 4. Use a scanner (e.g. bufio.NewScanner) to read from the client and broadcast the incoming messages to all the clients
	go func(){
		<-timer.C
		leaving<-ch
		messages<-who+" has left"
		conn.Close()
	}()
	input := bufio.NewScanner(conn)
  for input.Scan(){
    messages<-who + ": "+input.Text()
    timer.Reset(60*time.Second)
  }
	// 5. Send the client to the leaving channel
  leaving<-ch
	// 6. Broadcast a message to all clients that the client has left
	// e.g. "1.2.3. has left"
  messages<-who + " has left"

	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

func main() {
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}
