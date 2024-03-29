#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#define MAXDATASIZE 1024

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "usage: threeServer port-number\n");
        exit(1);
    }

    // place your code between the lines of //
    ///////////////////////////////////////////////////////

    // create the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    ///////////////////////////////////////////////////////

    struct sockaddr_in sa, caller;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(atoi(argv[1]));

    // place your code between the lines of //
    ///////////////////////////////////////////////////////

    // bind the socket
    bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));

    //////////////////////////////////////////////////////

    // place your code between the lines of //
    ///////////////////////////////////////////////////////

    // listen for requests, the second argument is the number of incoming connections that can be accepted at the same time
    listen(sockfd, 5);

    ///////////////////////////////////////////////////////

    socklen_t length = sizeof(caller);
    // place your code between the lines of //
    /////////////////////////////////////////////////////////////

    int client_sockfd = accept(sockfd, (struct sockaddr *)&caller, &length);

    /////////////////////////////////////////////////////////////

    char message[MAXDATASIZE] = "congrats you successfully connected to the server!";
    while (strlen(message) > 0)
    {
        int numbytes; // number of bytes of data read from socket

        // send data to the client and then get data back from the client:
        // place your code between the lines of //
        ///////////////////////////////////////////////////////

        // send the data:
        write(client_sockfd, message, strlen(message));

        // read the data:
        numbytes = read(client_sockfd, message, MAXDATASIZE - 1);

        ///////////////////////////////////////////////////////

        message[numbytes - 1] = '\0';
    }

    // place your code between the lines of //
    ///////////////////////////////////////////////////////

    close(client_sockfd);
    close(sockfd);

    ///////////////////////////////////////////////////////

    exit(0);
}