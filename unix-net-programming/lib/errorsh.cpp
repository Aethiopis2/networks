/**
 * @brief implemntation details for error handling library.
 * 
 * @author Rediet Worku aka Aethiopis II ben Zahab
 * @date 11th of Feburary 2025, Tuesday
 */

//============================================================================|
//          Includes
//============================================================================|
#include "errorsh.h"
#include <stdarg.h>

#ifdef __unix__
#include <sys/syslog.h>
#endif



//============================================================================|
//          Globals
//============================================================================|
int daemon_proc = 0;    // is server running as daemon




//============================================================================|
//          Functions
//============================================================================|
/**
 * Prints the formatted text either to the standard error stream or logs it
 *  in system log for unix derived implementations; in Windows its all standard
 *  error baby!
 * 
 * @param errnoflg determines if we have encountered sys call vs app level err
 * @param level Unix stuff; logging level for daemon processes
 * @param fmt C formatted error description to dump
 * @param ap variable list of arguments for the list in param #3 fmt.
 */
static void Output(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE + 1];

    errno_save = errno;
    vsnprintf(buf, MAXLINE, fmt, ap);
    n = strlen(buf);

    if (errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    if (daemon_proc)
        syslog(level, buf);
    else 
    {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    } // end else on stdandard error
} // end Output


//============================================================================|
/**
 * Dumps the error pertaining to the system call and terminates the app. If 
 *  app started as daemon process then error is logged in system joural.
 * 
 * @param fmt C formmated string
 */
void Err_Exit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    Output(1, LOG_ERR, fmt, ap);
    va_end(ap);
    
    exit(1);
} // end Err_Exit


//============================================================================|
/**
 * Occurs whenever system encounters a usage error, usually during command-line
 *  usage. It dumps the error either to stderror or journal an d terminates app
 * 
 * @param fmt C formatted string
 */
void Use_Error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    Output(0, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(1);
} // end Usage_Error


//============================================================================|
/**
 * This should be used whenever application level error's are encountered, this
 *  also terminate's the application.
 * 
 * @param fmt C formmated string
 */
void Fatal(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    Output(0, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(1);
} // end Fatal


//============================================================================|
/**
 * Used whenever system call error's should't kill the application. 
 * 
 * @param fmt C formmated string
 */
void Sys_Error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    Output(1, LOG_ERR, fmt, ap);
    va_end(ap);
} // end Dump_Error


//============================================================================|
/**
 * Application specific non-fatal error
 * 
 * @param fmt C formmated string
 */
void App_Error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    Output(0, LOG_ERR, fmt, ap);
    va_end(ap);
} // end Dump_Error