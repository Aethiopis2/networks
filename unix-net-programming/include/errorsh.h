/**
 * @brief prototypes for error handling functions mostly oriented at POSIX 
 *  compliant system
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */
#ifndef ERRORSH_H
#define ERRORSH_H



//============================================================================|
//          Includes
//============================================================================|
#include "rednet.h"



//============================================================================|
//          Prototypes
//============================================================================|
void Err_Exit(const char *fmt, ...);
void Use_Error(const char *fmt, ...);
void Fatal(const char *fmt, ...);
void Sys_Error(const char *fmt, ...);
void App_Error(const char *fmt, ...);



#endif