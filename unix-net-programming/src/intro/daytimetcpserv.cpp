/**
 * @brief a demo of daytime server using IPv4
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */


//============================================================================|
//          INCLUDES
//============================================================================|
#include "rednet.h"
#include "wrapsock.h"
#include "errorsh.h"





//============================================================================|
//          FUNCTIONS
//============================================================================|
int main(int argc, char *argv[])
{
    int listenfd, connfd;       // socket descriptor for listening and incomming
    struct sockaddr_in addr;    // address info
    char buffer[MAXLINE+1];     // storage buffer
    time_t ticks;               // get's the current system time as ticks

    
    listenfd = Socket(AF_INET, SOCK_STREAM);
    iZero(addr, sizeof(addr));
    addr.sin_addr.s_addr = INADDR_ANY;      // on all interfaces
    addr.sin_family = AF_INET;              // IPv4
    addr.sin_port = htons(13);              // daytime port

    Bind(listenfd, (SA *)&addr, sizeof(addr));
    Listen(listenfd);

    while (1) 
    {
        connfd = Accept(listenfd, (SA *)&addr, sizeof(addr));

        ticks = time(NULL);
        snprintf(buffer, MAXLINE, "%.24s\r\n", ctime(&ticks));
        Write(connfd, buffer, strlen(buffer));

        close(connfd);
    } // end while

    return 0;
} // end main