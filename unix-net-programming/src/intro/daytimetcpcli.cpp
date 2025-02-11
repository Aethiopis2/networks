/**
 * @brief a demo of simple day-time client application using IPv4 on
 *  a TCP enabled network.
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */


//============================================================================|
//          INCLUDES
//============================================================================|
#include "rednet.h"
#include "errorsh.h"





//============================================================================|
//          FUNCTIONS
//============================================================================|
int main(int argc, char *argv[])
{
    int sockfd, n;              // socket descriptor and storage for bytes
    struct sockaddr_in addr;    // address info
    char buffer[MAXLINE+1];     // storage buffer

    if (argc != 2)
        Use_Error("*ERROR: USAGE is: %s <IP Address>", argv[0]); 

#ifdef WINDOWS 
    // load up winsock 2 libraries in Windows
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa))
        Err_Exit("WSAStartup error");   // in Windows it's to stderror always
#endif

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        Err_Exit("socket error");

    iZero(addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0)
        Err_Exit("inet_pton error");

    if ( connect(sockfd, (SA *)&addr, sizeof(addr)) < 0)
        Err_Exit("connect error");

    while ( (n = read(sockfd, buffer, MAXLINE)) > 0) {
        buffer[n] = 0;
        if (fputs(buffer, stdout) == EOF)
            Err_Exit("fputs error");
    } // end while

    if (n < 0)
        Err_Exit("read error");

    return 0;
} // end main