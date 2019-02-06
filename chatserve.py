'''
Author: Christopher Ragasa
Date: Feb 5, 2019
Program Description: chatserve.py is the server side of chat-serve program.
'''
import socket
import sys

MAX_LENGTH = 500


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
    '''
    Return value of accept() is a pair:
    conn is a new socket object usable to send and recieve data on connection.
    addr is the address bound to the socket on the other end of the connection 
    '''

    while 1:
        conn, addr = s.accept()
        print("Established connection with " + str(addr))


if __name__ == "__main__":
    main()
