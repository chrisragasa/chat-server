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
int setupSocket(int portNumber);

int main(int argc, char *argv[])
{
    char *hostname;
    int portnumber;
    char clientHandle[HANDLE_LENGTH];
    char serverHandle[HANDLE_LENGTH];
    memset(clientHandle, '\0', HANDLE_LENGTH); // Initialize arrays with null terminators
    memset(serverHandle, '\0', HANDLE_LENGTH); // Initialize arrays with null terminators

    /* Validate correct usage */
    if (argc != 3)
        error("error: incorrect usage\nusage: ./chatclient [host name] [port number]", 1);

    hostname = argv[1];
    portnumber = atoi(argv[2]); // Convert string to an integer

    /* Get client handle */
    printf("Enter client handle (length 10 or less): ");
    scanf("%s", clientHandle);
    printf("\n");

    /* Create socket */
    int sockfd = setupSocket(portnumber);

    int s = send(sockfd, clientHandle, strlen(clientHandle), 0); // Send client handle

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
int setupSocket(int portNumber)
{
    int socketFD;                                        // Socket file descriptor
    struct sockaddr_in serverAddress;                    // Server address struct
    struct hostent *server = gethostbyname("localhost"); // Get host IP
    if (server == NULL)
        error("error: host was not found\n", 1); // error if host not found

    /* Open the socket */
    socketFD = socket(AF_INET, SOCK_STREAM, 0); // returns a socket descriptor that we can use in later system calls. returns -1 on error.
    if (socketFD < 0)
    {
        error("error: opening socket", 1); // check if the return value was -1 to signify an error
    }

    /* Set up server address struct */
    memset((char *)&serverAddress, '\0', sizeof(serverAddress));                             // Clear out the address struct
    serverAddress.sin_family = AF_INET;                                                      // Create a network-capable socket
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length); // copy serv_addr ip into server->h_addr
    serverAddress.sin_port = htons(portNumber);                                              // Store the port number

    /* Connect to server */
    if (connect(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        error("error: connecting to socket", 1); // Connection error
    }

    return socketFD;
}