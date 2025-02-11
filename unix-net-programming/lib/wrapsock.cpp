/**
 * @brief implementation detalis for socket wrapper functions
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */
//============================================================================|
//          Includes
//============================================================================|
#include "wrapsock.h"
#include "errorsh.h"




//============================================================================|
//          Types
//============================================================================|




//============================================================================|
//          Prototypes
//============================================================================|
/**
 * Windows specific; loads WinSock dll version 2.2, that is required by network
 *  applications in Windows systems.
 */
void Init_Winsock() 
{
#ifdef WINDOWS
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa))
        Fatal("WSAStartup failed with error code: %d", WSAGetLastError());
    
#endif
} // end Init_Winsock


//============================================================================|
/**
 * Wrapps around standard socket function and make's life easy by handling any
 *  errors by terminating the app.
 * 
 * @param family socket family IPv4 vs IPv6
 * @param stream type of stream usually SOCK_STREAM
 * @param proto protocol defaults to 0
 * 
 * @return the new socket descriptor
 */
int Socket(int family, int stream, int proto)
{
    int fd;
    if ( (fd = socket(family, stream, proto)) < 0)
        Err_Exit("socket error");
    
    return fd;
} // end Socket


//============================================================================|
/**
 * Establishes an active connection with the provided address info, exits the
 *  app on connect error
 * 
 * @param fd socket descriptor
 * @param addr socket address structure
 * @param len length of the address above
 */
void Connect(int fd, SA *addr, const socklen_t len) 
{
    if (connect(fd, addr, len) < 0)
        Err_Exit("connect fail");
} // end Connect


//============================================================================|
/**
 * Binds the socket to the address provided, exits the application upon error
 *  This is usually called during server process setup.
 * 
 * @param fd the socket desriptor
 * @param addr the address structure to bind to socket
 * @param len the length of the address structure
 */
void Bind(int fd, SA *addr, const socklen_t len)
{
    if (bind(fd, addr, len) < 0)
        Err_Exit("bind error");
} // end Bind


//============================================================================|
/**
 * Puts the server into listing mode to await for incomming connections once
 *  bound to interface. Function exits process on error
 * 
 * @param fd the socket descriptor to listen
 * @param backlog the maximum number of concurrent connections (defaults to BACKLOG)
 */
void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
        Err_Exit("lisen error");
} // end Listen


//============================================================================|
/**
 * Accepts incomming connection if the system can alas kills the app with an
 *  exit error.
 */
int Accept(int fd, SA *addr, socklen_t len)
{
    int sockfd;
    if ( (sockfd = accept(fd, addr, &len)) < 0)
        Err_Exit("accept fail");

    return sockfd;
} // end Accept


//============================================================================|
/**
 * Wraps around write system call and make's sure the exact bytes are written
 *  or exit the app
 * 
 * @param fd socket descriptor
 * @param buf buffer containing data
 * @param len length of buffer above
 */
int Write(int fd, char *buf, const size_t len)
{
    int n;
    if ( (n = write(fd, buf, len)) != len )
        Err_Exit("write error");
    
    return n;       // number of bytes written
} // end Write