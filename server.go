package main

import (
	"fmt"
	"log"
	"net"
	"os"
)

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Not enough arguments")
		os.Exit(1)
	}

	var isServer = os.Args[1] == "true"

	if isServer {
		// Run server
		createServer(8080, "localhost")
	} else {
		// Run client
		createClient(8080, "localhost", 8081, "localhost")
	}
}

func createServer(port int, addr string) {
	fmt.Println("Running server at ", addr, ":", port)
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", addr, port))
	if err != nil {
		fmt.Println(err.Error())
		fmt.Println("Failed to init listener for server")
		os.Exit(1)
	}

	defer listener.Close()

	for {
		connection, err := listener.Accept()
		if err != nil {
			fmt.Println("Failed to accept incoming request")
			os.Exit(1)
		}

		go handleRequest(connection)
	}
}

func createClient(serverPort int, serverAddr string, clientPort int, clientAddr string) {
	dialer := &net.Dialer{LocalAddr: &net.TCPAddr{IP: net.ParseIP(clientAddr), Port: clientPort}}
	conn, err := dialer.Dial("tcp", fmt.Sprintf("%s:%d", serverAddr, serverPort))
	if err != nil {
		fmt.Println("Error when creating connection")
		fmt.Println(err)
		return
	}

	// Send some data to the server
	_, err = conn.Write([]byte("Hello, server!"))
	if err != nil {
		fmt.Println(err)
		return
	}

	writeMessage("Hello, server", clientPort, serverPort)

	// Close the connection
	conn.Close()
}

func handleRequest(connection net.Conn) {
	fmt.Println("Handling request from: ", connection.RemoteAddr().String())
	connection.Close()
}

func writeMessage(message string, srcPort int, recvPort int) {
	f, err := os.OpenFile(fmt.Sprintf("./files/%d_%d.log", srcPort, recvPort), os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		log.Fatal(err)
	}

	_, err = f.WriteString(message + "\n")
	if err != nil {
		fmt.Println("Failed to open file")
		os.Exit(1)
	}
	f.Close()
}
