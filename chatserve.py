'''
Author: Christopher Ragasa
Date: Feb 5, 2019
Program Description: chatserve.py is the server side of chat-serve program.
'''
import socket
import sys

MAX_LENGTH = 1024


def handShake(socket, address, handle):
    """Perform handshake with the client: receive the client's handle and send the server's handle
    Args:
        socket: socket object
        address: address bound to socket on the other end of connection
        handle: server's handle (string)
    Returns:
        Client's handle (in bytes)
    """
    clientHandle = socket.recv(MAX_LENGTH)
    socket.send(bytes(handle, 'UTF-8'))  # Encode
    return clientHandle


def initChat(clientHandle, serverHandle, socket, address):
    """Create a chat session with the client: send and recieve messages
    Args:
        clientHandle: client's handle (string)
        serverHandle: server's handle (string)
        socket: socket object
    Returns:
        N/A
    """
    while(1):
        # Receive message
        message = socket.recv(MAX_LENGTH).decode().strip(' \t\r\n\0')
        if message == "\quit":
            print("The client has dropped the connection...")
            break
        print(clientHandle + "> " + message)
        buffer = ''
        buffer = input(serverHandle+"> ")
        while len(buffer) == 0 or len(buffer) > 500:
            print("Message must be of length [1, 500]")
            buffer = input(serverHandle+"> ")
        if buffer == "\quit":
            print("Dropped connection with " +
                  str(address) + "...")
            break
        else:
            socket.send(bytes(buffer, 'UTF-8'))


def main():
    # Validate correct usage
    if len(sys.argv) != 2:
        print("error: incorrect usage")
        print("usage: python3 chatserver.py [port number]")
        exit(1)

    HOST = ""   # Symbolic name meaning all avaialble interfaces
    PORT = int(sys.argv[1])

    # Create socket (SOCK_STREAM means a TCP socket)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)

    while 1:
        # accept() returns conn (socket object) and addr (address bound to socket on other end of conn)
        conn, addr = s.accept()
        print("Established connection with " + str(addr) + "...")
        # Store client handle as a string
        clientHandle = handShake(conn, addr, "HostA").decode(
            "utf-8")
        initChat(clientHandle, "HostA", conn, addr)
        conn.close()


if __name__ == "__main__":
    main()
