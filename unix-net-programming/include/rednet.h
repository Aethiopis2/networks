/**
 * @brief contains common header files, globals, and various utilites. It's
 *  a modification of Richard Steven's "unp.h" 
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */
#ifndef REDNET_H
#define REDNET_H


//============================================================================|
//          Defines
//============================================================================|
#if defined(WIN32) || defined(_WIN64)
#define WINDOWS
#endif 



//============================================================================|
//          Includes
//============================================================================|
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <time.h>



#ifdef WINDOWS
#include <WinSock2.h>
#else 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif



//============================================================================|
//          Types
//============================================================================|
// basic types
typedef __int128_t s128;
typedef __int64_t s64;
typedef __int32_t s32;
typedef __int16_t s16;
typedef __int8_t s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;


// shorthand form
typedef struct sockaddr SA;


//============================================================================|
//          Macros
//============================================================================|
// simplify memset
#define iZero(buffer, size)      memset(&buffer, 0, size)





//============================================================================|
//          Constants
//============================================================================|
constexpr u32 MAXLINE   = 1024;             // default buffer size
constexpr u8 LOG_ERR    = 0;                // determines error log level; Unix stuff
constexpr u32 BACKLOG   = 32;               // max number of conurrrent connections


#endif