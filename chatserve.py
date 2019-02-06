'''
Author: Christopher Ragasa
Date: Feb 5, 2019
Program Description: chatserve.py is the server side of chat-serve program.
'''
import socket
import sys

MAX_LENGTH = 500


def handShake(socket, handle):
    """Perform handshake with the client and exchange handles.
    Args:
        socket: socket object
        handle: server's handle
    Returns:
        Client's handle (in bytes)
    """
    clientHandle = socket.recv(1024)
    return clientHandle


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
        # returns conn (socket object) and addr (address bound to socket on other end of conn)
        conn, addr = s.accept()
        print("Established connection with " + str(addr))
        print(handShake(conn, addr).decode("utf-8"))


if __name__ == "__main__":
    main()
