'''
Author: Christopher Ragasa
Date: Feb 5, 2019
Program Description: chatserve.py is the server side of chat-serve program.
'''
import socket
import sys

MAX_LENGTH = 500


def handShake(socket, address, handle):
    """Perform handshake with the client: receive the client's handle and send the server's handle
    Args:
        socket: socket object
        address: address bound to socket on the other end of connection
        handle: server's handle (string)
    Returns:
        Client's handle (in bytes)
    """
    clientHandle = socket.recv(1024)
    socket.send(bytes(handle, 'UTF-8'))  # Encode
    return clientHandle


def initChat(clientHandle, serverHandle, socket, address):
    """Establish connection with client and create a chat session
    Args:
        clientHandle: client's handle (string)
        serverHandle: server's handle (string)
        socket: socket object
    Returns:
        N/A
    """
    while(1):
        message = socket.recv(MAX_LENGTH).decode("utf-8")
        print(clientHandle + "> " + message)
        buffer = ''
        while len(buffer) == 0 or len(buffer) > MAX_LENGTH:
            buffer = input(serverHandle+"> ")
        if buffer == "\quit":
            print("Dropping connection with " +
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
