/**
 * @brief protoypes for socket function wrappers and error handling
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */
#ifndef WRAPSOCK_H
#define WRAPSOCK_H



//============================================================================|
//          Includes
//============================================================================|
#include "rednet.h"




//============================================================================|
//          Types
//============================================================================|




//============================================================================|
//          Prototypes
//============================================================================|
void Init_Winsock();
int Socket(int familiy, int stream, int proto = 0);
void Connect(int fd, SA *addr, const socklen_t len);
void Bind(int fd, SA *addr, const socklen_t len);
void Listen(int fd, int backlog = BACKLOG);
int Accept(int fd, SA *addr, socklen_t len);
int Write(int fd, char *buf, const size_t len);


#endif