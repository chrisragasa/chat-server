/*
Author: Christopher Ragasa
Date: Feb 5, 2019
Program Description: chatclient.c is the client side of chat-serve program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define HANDLE_LENGTH 11
#define MESSAGE_LENGTH 500

/* Functions */
void error(const char *msg, int exitVal);
int setupSocket(int portNumber, char *hostname);
void initChat(char *clientHandle, char *serverHandle, int sockfd);

int main(int argc, char *argv[])
{
    char *hostname;
    int portnumber;
    char clientHandle[HANDLE_LENGTH];
    char serverHandle[HANDLE_LENGTH];
    memset(clientHandle, '\0', HANDLE_LENGTH); // Initialize array with null terminators
    memset(serverHandle, '\0', HANDLE_LENGTH); // Initialize array with null terminators

    /* Validate correct usage */
    if (argc != 3)
        error("error: incorrect usage\nusage: ./chatclient [host name] [port number]", 1);

    hostname = argv[1];
    portnumber = atoi(argv[2]); // Convert string to an integer

    /* Get client handle */
    printf("Enter client handle (length 10 or less): ");
    fgets(clientHandle, HANDLE_LENGTH, stdin);
    clientHandle[strcspn(clientHandle, "\n")] = 0; // Strip newline character

    /* Create socket and establish connection between the two hosts */
    int sockfd = setupSocket(portnumber, hostname);

    /* Handshake */
    int s = send(sockfd, clientHandle, strlen(clientHandle), 0); // Send client handle
    int r = recv(sockfd, serverHandle, HANDLE_LENGTH, 0);        // Receive the servers handle

    initChat(clientHandle, serverHandle, sockfd);

    return 0;
}

/**************************
Function: error
Description: A utility function to display error messages with exit values
Input: error message (string), exit value (int)
Output: N/A
**************************/
void error(const char *msg, int exitVal)
{
    fprintf(stderr, "%s\n", msg);
    exit(exitVal);
}

/**************************
Function: setupSocket
Description: Socket setup
Input: portNo (int) - a valid port number that will be used for the socket
Output: sockFD (int) - int that represents socket file descriptor
**************************/
int setupSocket(int portNumber, char *hostname)
{
    int socketFD;                                     // Socket file descriptor
    struct sockaddr_in serverAddress;                 // Server address struct
    struct hostent *server = gethostbyname(hostname); // Get host IP
    if (server == NULL)
        error("error: host was not found", 1);

    /* Open the socket */
    socketFD = socket(AF_INET, SOCK_STREAM, 0); // Returns a socket descriptor that we can use in later system calls. returns -1 on error.
    if (socketFD < 0)
    {
        error("error: opening socket", 1);
    }

    /* Set up server address struct */
    memset((char *)&serverAddress, '\0', sizeof(serverAddress));                             // Clear out the address struct
    serverAddress.sin_family = AF_INET;                                                      // Create a network-capable socket
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length); // Copy serv_addr ip into server->h_addr
    serverAddress.sin_port = htons(portNumber);                                              // Store the port number

    /* Connect to server */
    if (connect(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        error("error: connecting to socket", 1); // Connection error
    }

    return socketFD;
}

/**************************
Function: initChat
Description: Establish connection with server and create a chat session
Input: 
clientHandle (string) - client's handle
serverHandle (string) - server's handle
sockfd (int) - socket file descriptor
Output: N/A
**************************/
void initChat(char *clientHandle, char *serverHandle, int sockfd)
{
    char msgSend[MESSAGE_LENGTH];
    char msgRecv[MESSAGE_LENGTH];
    int bytesRecv;
    int bytesSent;

    memset(msgSend, '\0', MESSAGE_LENGTH); // Initialize array with null terminators
    memset(msgRecv, '\0', MESSAGE_LENGTH); // Initialize array with null terminators

    while (1)
    {
        printf("%s> ", clientHandle);

        /* Send message */
        memset(msgSend, '\0', MESSAGE_LENGTH);
        fgets(msgSend, MESSAGE_LENGTH, stdin);
        msgSend[strcspn(msgSend, "\n")] = 0;

        if (strcmp(msgSend, "\\quit") == 0)
        {
            break;
        }
        else
        {
            bytesSent = send(sockfd, msgSend, MESSAGE_LENGTH, 0);
            if (bytesSent == -1)
            {
                error("error: message could not be sent from client to server", 1);
            }
        }

        /* Receive message */
        memset(msgRecv, '\0', MESSAGE_LENGTH);
        bytesRecv = recv(sockfd, msgRecv, MESSAGE_LENGTH, 0);
        if (bytesRecv < 0)
        {
            error("error: message could not be sent from client to server", 1);
        }
        else if (bytesRecv > 0)
        {
            printf("%s> %s\n", serverHandle, msgRecv);
        }
        else
        {
            printf("The server has dropped the connection...\n");
            break;
        }
    }
}