#ifndef    TPCON_H
   #define TPCON_H
// file-logging facilities
// Screen output using ANSI X3.64 terminal escape definitions and
//
// Author: J. van Wijk
//
// JvW  29-08-2001 Rename to TPCON
// JvW  28-07-1999 Removed ANSI_DEF_ONLY / A_DYNAMIC stuff for simplicity
// JvW  07-05-1996 Added Mutex semaphore to serialize trace output
// JvW  09-03-1996 Added trace macro's and implementation
// JvW  15-02-1996 Added ddl global debugging variable
// JvW  17-05-1996 Added Tprintf CLEAN and RAW callback hooks
// JvW  25-02-1996 Fixed "," bug in ANSI_DEF_ONLY part
// JvW  26-12-1996 Added BRETURN and EOLN / NOLN macro's
// JvW  17-06-1995 Initial version, split off from DHPFS.C


#define MAXLBUF            1024                 // max lbuf length
#define MAXLINE             260                 // max line length (path)
#define MAXMBUF              81                 // max single-word length
#define MAXPAGE            4096                 // page-size buffer
#define MAXSBUF              16                 // max sbuf length

#define TPK_ENTER          0x0d                 // Enter  key value
#define TPK_ESCAPE         0x1b                 // Escape key value
#define TPK_SPACE          0x20                 // Space  key value

#define TPM_QUERY_ONLY     0xffff               // Query More value
#define TPM_SCREEN_SIZE    0xfffe               // More value to default
#define TPM_UNLIMITTED     0x0                  // More value 0 (no limit)

typedef char   PAGE[MAXPAGE];                   // page buffers
typedef char   LBUF[MAXLBUF];                   // large buffers
typedef char   LINE[MAXLINE];                   // line buffers
typedef char   MBUF[MAXMBUF];                   // word buffers
typedef char   SBUF[MAXSBUF];                   // small buffers

typedef enum screen_state
{
   SCREEN_ON          = 0,
   SCREEN_OFF         = 1,
   SCREEN_TEST        = 2
} SCREEN_STATE;                                 // end of enum "screen_state"


typedef enum tph_type
{
   TPH_T_CLEAN,                                 // No ANSI escape sequences
   TPH_T_RAW,                                   // include all ANSI stuff
} TPH_TYPE;                                     // end of enum "tph_type"


typedef enum tph_operation
{
   TPH_REGISTER,                                // Register a handler
   TPH_DEREGISTER,                              // Deregister a handler
} TPH_OPERATION;                                // end of enum "tph_operation"


typedef void (* TPH_CALLBACK)
(
   char               *text,                    // IN    Tprintf text to copy
   void               *data                     // IN    user data pointer
);


typedef struct tph_info                         // ansi Tprintf copy info
{
   char               *cbuf;                    // ansi copy buffer
   ULONG               size;                    // size of copy buffer
   TPH_CALLBACK        copy;                    // handler for ansi data
   void               *user;                    // user data pointer
   BOOL                active;                  // handler currently active
   BOOL                follow_screen_toggle;    // follow screen on/off
   struct tph_info    *next;                    // ptr to next handler in chain
   struct tph_info    *prev;                    // ptr to prev handler in chain
} TPH_INFO;                                     // end of struct "tph_info"


#define A_ON              ''                   // on  (escape strings)
#define A_OFF             '\0'                  // off (empty strings)

#define NORMAL              0
#define NORMAL_RED          1
#define NORMAL_GREEN        2
#define NORMAL_YELLOW       3
#define NORMAL_BLUE         4
#define NORMAL_MAGENTA      5
#define NORMAL_CYAN         6
#define NORMAL_WHITE        7
#define NORMAL_BLACK        8
#define BRIGHT_RED          9
#define BRIGHT_GREEN       10
#define BRIGHT_YELLOW      11
#define BRIGHT_BLUE        12
#define BRIGHT_MAGENTA     13
#define BRIGHT_CYAN        14
#define BRIGHT_WHITE       15
#define BRIGHT_GREY        16
#define NOR_BG_RED         17
#define NOR_BG_GREEN       18
#define NOR_BG_YELLOW      19
#define NOR_BG_BLUE        20
#define NOR_BG_MAGENTA     21
#define NOR_BG_CYAN        22
#define NOR_BG_WHITE       23
#define NOR_BG_BLACK       24
#define BRI_BG_RED         25
#define BRI_BG_GREEN       26
#define BRI_BG_YELLOW      27
#define BRI_BG_BLUE        28
#define BRI_BG_MAGENTA     29
#define BRI_BG_CYAN        30
#define BRI_BG_WHITE       31
#define BRI_BG_GREY        32
#define CURSOR_UP1         33
#define CURSOR_UP2         34
#define CURSOR_UP4         35
#define CURSOR_UP8         36
#define CURSOR_DOWN1       37
#define CURSOR_DOWN2       38
#define CURSOR_DOWN4       39
#define CURSOR_DOWN8       40
#define CURSOR_RIGHT1      41
#define CURSOR_RIGHT2      42
#define CURSOR_RIGHT4      43
#define CURSOR_RIGHT8      44
#define CURSOR_LEFT1       45
#define CURSOR_LEFT2       46
#define CURSOR_LEFT4       47
#define CURSOR_LEFT8       48
#define CURSOR_SAVEP       49
#define CURSOR_RESTP       50
#define CLEAR_TO_EOL       51
#define CURS_GO_1_70       52
#define CURS_GO_1_75       53
#define CURS_GO_1_01       54
#define CURS_GO_2_01       55
#define CURS_GO23_01       56
#define CURS_GO24_01       57
#define NUMBER_ANSIS       58

typedef char           ANSISTRING[10];
typedef ANSISTRING     ANSIDEFS[NUMBER_ANSIS];

#define CNN            ansi[NORMAL]
#define CNR            ansi[NORMAL_RED]
#define CNG            ansi[NORMAL_GREEN]
#define CNY            ansi[NORMAL_YELLOW]
#define CNB            ansi[NORMAL_BLUE]
#define CNM            ansi[NORMAL_MAGENTA]
#define CNC            ansi[NORMAL_CYAN]
#define CNW            ansi[NORMAL_WHITE]
#define CNZ            ansi[NORMAL_BLACK]
#define CBR            ansi[BRIGHT_RED]
#define CBG            ansi[BRIGHT_GREEN]
#define CBY            ansi[BRIGHT_YELLOW]
#define CBB            ansi[BRIGHT_BLUE]
#define CBM            ansi[BRIGHT_MAGENTA]
#define CBC            ansi[BRIGHT_CYAN]
#define CBW            ansi[BRIGHT_WHITE]
#define CBZ            ansi[BRIGHT_GREY]
#define CnR            ansi[NOR_BG_RED]
#define CnG            ansi[NOR_BG_GREEN]
#define CnY            ansi[NOR_BG_YELLOW]
#define CnB            ansi[NOR_BG_BLUE]
#define CnM            ansi[NOR_BG_MAGENTA]
#define CnC            ansi[NOR_BG_CYAN]
#define CnW            ansi[NOR_BG_WHITE]
#define CnZ            ansi[NOR_BG_BLACK]
#define CbR            ansi[BRI_BG_RED]
#define CbG            ansi[BRI_BG_GREEN]
#define CbY            ansi[BRI_BG_YELLOW]
#define CbB            ansi[BRI_BG_BLUE]
#define CbM            ansi[BRI_BG_MAGENTA]
#define CbC            ansi[BRI_BG_CYAN]
#define CbW            ansi[BRI_BG_WHITE]
#define CbZ            ansi[BRI_BG_GREY]
#define CU1            ansi[CURSOR_UP1]
#define CU2            ansi[CURSOR_UP2]
#define CU4            ansi[CURSOR_UP4]
#define CU8            ansi[CURSOR_UP8]
#define CD1            ansi[CURSOR_DOWN1]
#define CD2            ansi[CURSOR_DOWN2]
#define CD4            ansi[CURSOR_DOWN4]
#define CD8            ansi[CURSOR_DOWN8]
#define CR1            ansi[CURSOR_RIGHT1]
#define CR2            ansi[CURSOR_RIGHT2]
#define CR4            ansi[CURSOR_RIGHT4]
#define CR8            ansi[CURSOR_RIGHT8]
#define CL1            ansi[CURSOR_LEFT1]
#define CL2            ansi[CURSOR_LEFT2]
#define CL4            ansi[CURSOR_LEFT4]
#define CL8            ansi[CURSOR_LEFT8]
#define CGS            ansi[CURSOR_SAVEP]
#define CGR            ansi[CURSOR_RESTP]
#define CGE            ansi[CLEAR_TO_EOL]
#define CG170          ansi[CURS_GO_1_70]
#define CG175          ansi[CURS_GO_1_75]
#define CG1            ansi[CURS_GO_1_01]
#define CG2            ansi[CURS_GO_2_01]
#define CG23           ansi[CURS_GO23_01]
#define CG24           ansi[CURS_GO24_01]

extern  ANSIDEFS    ansi;


/*--- TRACE macro definitions -----------------------------------------------*/

#undef  ENTER
#undef  BRETURN
#undef  VRETURN
#undef  RETURN
#undef  TREOLN
#undef  TPREOLN
#undef  TRNOLN
#undef  TPRNOLN
#undef  TRACON
#undef  TRARGS
#undef  TRARGX
#undef  TRINTF
#undef  TRACEL
#undef  TRACES
#undef  TRACEX
#undef  TRHEXD
#undef  TRCRCD
#undef  TRDUMP
#undef  TRINIT
#undef  TREXIT

extern  ULONG       AnsiTrace;                  // trace level

#if defined (DUMP)
    //- additional tracing using Tprintf, if trace is enabled (AnsiTrace)

#include <time.h>
#include <stdio.h>
#include <string.h>


#define ENTER(mod)  char AnsiTrMod[80]; strcpy( AnsiTrMod, mod);              \
                    if (AnsiTrace >= 10)                                      \
                    {                                                         \
                       AnsiTrcEnter(mod, AnsiTrMod);                          \
                    }

#define VRETURN()                                                             \
                    if (AnsiTrace >= 10)                                      \
                    {                                                         \
                       AnsiTrcRetVoid( AnsiTrMod);                            \
                    }                                                         \
                    return

#define BRETURN(rc)                                                           \
                    if (AnsiTrace >= 10)                                      \
                    {                                                         \
                       AnsiTrcRetBool( AnsiTrMod, (BOOL) rc);                 \
                    }                                                         \
                    return(rc)

#define RETURN(rc)                                                            \
                    if (AnsiTrace >= 10)                                      \
                    {                                                         \
                       AnsiTrcReturn( AnsiTrMod, (ULONG) rc);                 \
                    }                                                         \
                    return(rc)


#define TRLEVX(lev,tpf)                                                       \
                 {                                                            \
                    if (AnsiTrace >= lev)                                     \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       AnsiTrcLeader();                                       \
                       Tprintf  tpf;                                          \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }

// Trace to logfile only, avoiding recursive loops tracing Tprintf window stuff
//                     usage:  TRACEL((log, "fmt-str", arg1, arg2, ...));
#define TRACEL(tpf)                                                           \
                 {                                                            \
                    if (AnsiTrace >= 90)                                      \
                    {                                                         \
                       FILE *log = TpQueryLogFile();                          \
                       fprintf  tpf;                                          \
                       fflush(log);                                           \
                       TpScreenState(SCREEN_ON);                              \
                    }                                                         \
                 }

#define TRHEXD(lev,a,b)                                                       \
                 {                                                            \
                    if (AnsiTrace >= lev)                                     \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       TpDisplHexDump((char *)a, (ULONG) b);                  \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }


#define TRCRCD(l,a,b,d)                                                       \
                 {                                                            \
                    if (AnsiTrace >= 30)                                      \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       Tprintf("%s  Data *: %8.8lX, size: % 9lu "             \
                                    "= %8.8lX, CRC: %s%8.8lX%s\n",            \
                                    l, a, (ULONG) b, (ULONG) b,               \
                                    CBY, TpCrc32( a, (ULONG) b), CNN);        \
                       TpDisplHexDump((char *)a, (ULONG) d);                  \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }


#define TRDUMP(lev,l,a,b,o)                                                   \
                 {                                                            \
                    if (AnsiTrace >= lev)                                     \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       TpDisplayHex(l, (char *)a, (ULONG) b, (ULONG) o);      \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }


#define TRINIT(lev)                                                           \
                    if (AnsiTrace >= lev)                                     \
                    {                                                         \
                       AnsiTrcLeader();                                       \
                       AnsiScrClaim()


#define TREXIT()                                                              \
                       AnsiScrRelease();                                      \
                    }



#define TREOLN                  ((AnsiTrace != 0) ? "\n" : "")
#define TRNOLN                  ((AnsiTrace == 0) ? "\n" : "")

#define TPREOLN()                                                             \
                 {                                                            \
                    if (AnsiTrace != 0)                                       \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       Tprintf("\n");                                         \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }

#define TPRNOLN()                                                             \
                 {                                                            \
                    if (AnsiTrace == 0)                                       \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       Tprintf("\n");                                         \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }

// TRACE printf without a leader (to print single character progress)
#define TRINTF(tpf)                                                           \
                 {                                                            \
                    if (AnsiTrace >= 70)                                      \
                    {                                                         \
                       AnsiScrClaim();                                        \
                       Tprintf  tpf;                                          \
                       AnsiScrRelease();                                      \
                    }                                                         \
                 }


#define TRACON(args)            TRLEVX(1 ,args)
#define TRARGS(args)            TRLEVX(30,args)
#define TRARGX(args)            TRLEVX(50,args)
#define TRACES(args)            TRLEVX(70,args)
#define TRACEX(args)            TRLEVX(90,args)



// Handle entry for a routine
void AnsiTrcEnter
(
   char              *mod,                      // IN    module/function name
   char               save[]                    // OUT   module name save
);


// Handle numeric return of a routine
void AnsiTrcReturn
(
   char              *mod,                      // IN    module/function name
   ULONG              rc                        // IN    return value
);


// Handle boolean return of a routine
void AnsiTrcRetBool
(
   char              *mod,                      // IN    module/function name
   BOOL               rc                        // IN    return value
);


// Handle return of a void routine
void AnsiTrcRetVoid
(
   char              *mod                       // IN    module/function name
);


// Timestamp, thread-id and indent for trace-line
void AnsiTrcLeader
(
   void
);

#else
    //- make sure macro's are not defined for no-trace situation

#define ENTER(mod)
#define VRETURN()
#define BRETURN(rc) return(rc)
#define RETURN(rc)  return(rc)

#define TREOLN                  ""
#define TPREOLN()
#define TRNOLN                  "\n"
#define TPRNOLN()               Tprintf("\n")
#define TRACON(args)
#define TRARGS(args)
#define TRARGX(args)
#define TRINTF(args)
#define TRACEL(args)
#define TRACES(args)
#define TRACEX(args)
#define TRHEXD(lev,a,b)
#define TRCRCD(l,a,b,d)
#define TRDUMP(lev,l,a,b,o)
#define TRINIT(lev) if (AnsiTrace >= lev)                                     \
                    {
#define TREXIT()    }
#endif


// Initialise Ansi environment
void AnsiInit
(
   BOOL                ansiOff,                 // IN    don't use ANSI colors
   BOOL                ascii7                   // IN    Convert to 7-bit ASCII
);


// Terminate Ansi environment
void AnsiTerminate
(
   void
);


//- Set ansi active or inactive (initial, later controlled by Tprintf)
void AnsiMode
(
   char                mode                     // IN    ansi mode
);

// Get ansi string definitions active or inactive
char TpGetAnsiMode                              // RET   ansi mode
(
   void
);

// Claim access to Screen
ULONG AnsiScrClaim                              // RET   result
(
   void
);


// Release access to Screen
ULONG AnsiScrRelease                            // RET   result
(
   void
);


// Perform operations on Tprintf HOOK chain
BOOL TprintfHook                                // RET   success
(
   TPH_TYPE            type,                    // IN    type of handler
   TPH_OPERATION       operation,               // IN    requested operation
   TPH_INFO           *hinfo                    // IN    handler info
);


// Close existing and if specified, open new logfile
BOOL TpAppendToLogFile                          // RET   logfile opened
(
   char                *fname                   // IN    name of (new) logfile
);


// Signal logging state
FILE *TpQueryLogFile                            // RET   logging handle
(
   void
);


// Output textual information in array of char-pointers
void TpShowTxt
(
   char               *txt[]                    // IN    text to display
);


// Test and set TpScreenState
SCREEN_STATE TpScreenState                      // RET   screen active
(
   SCREEN_STATE        action                   // IN    screen action
);


// Make ascii-dump of data area on Tprintf output
void TpDisplAscDump
(
   char               *lead,                    // IN    leading string
   char               *data,                    // IN    data area
   ULONG               size                     // IN    size to dump
);

// Make hex-dump of data area on Tprintf output
void TpDisplHexDump
(
   char               *data,                    // IN    data area
   ULONG               size                     // IN    size to dump
);

// Make hex-dump of based data area on Tprintf output, with leading text
void TpDisplayHex
(
   char               *lead,                    // IN    leading text
   char               *data,                    // IN    data area
   ULONG               size,                    // IN    size to dump
   ULONG               base                     // IN    base for display
);

// Translate Mixed Ascii / Hex string specification to length + buffer
USHORT TpFormatMixedStr                         // RET   length of buffer
(
   char              *data,                     // IN    mixed string
   char              *buf                       // OUT   formatted buffer
);


// Return ascii printable character
char Tprintable                                 // RET   printable character
(
   char               c                         // IN    character
);


// printf-like print on stdout, TEE filehandle and output hooks
void Tprintf
(
   char              *fmt,                      // IN    format string (printf)
   ...                                          // IN    variable arguments
);

#if defined (DEV32)
// Write to stream (redirected stdout) with logfile (TEE) and output hooks
void TpWriteStream
(
   TPHFILE            stream,                   // IN    stream to write to
   char              *text                      // IN    string to write
);
#endif

#if defined (DOS16)
// Wait for specified nr of msec (approximation, +/- 32 msec)
ULONG TpBusyWait                                // RET   waited nr of msec
(
   ULONG               msec                     // IN    nr of msec to wait
);
#endif


// Claim TP keyboard access-functions for current thread (TpAbort etc)
ULONG TpClaimKeyboard                           // RET   previous owner
(
   void
);

// Cancel any pending abort status (as returned by TpAbort)
void TpCancelAbort
(
   void
);

// Set abort status to pending, for other threads (as returned by TpAbort)
void TpSetPendingAbort
(
   void
);

// Return kbhit status and latest More ... reply, read away the hit
BOOL TpAbort                                    // RET   TRUE when abort wanted
(
   void
);

// Display a message using format string and ask confirmation; Yes/No/cancel
BOOL TpConfirm                                  // RET   Confirmed
(
   ULONG               helpid,                  // IN    helpid confirmation
   char               *fmt,                     // IN    format string (printf)
   ...                                          // IN    variable arguments
);


// Display a message or warning using format string and wait for OK
void TpMessage
(
   BOOL                acknowledge,             // IN    wait for acknowledge
   ULONG               helpid,                  // IN    helpid confirmation
   char               *fmt,                     // IN    format string (printf)
   ...                                          // IN    variable arguments
);


// Prompt for user input with a message and read the input
BOOL TpPrompt                                   // RET   value not empty
(
   ULONG               helpid,                  // IN    helpid confirmation
   short               length,                  // IN    max length of value
   char               *value,                   // INOUT entry field value
   char               *fmt,                     // IN    format string (printf)
   ...                                          // IN    variable arguments
);

// Remove ANSI control code from a text-string (in place conversion)
char *TpStripAnsiCodes                          // RET   stripped string
(
   char               *text                     // INOUT ANSI text to strip
);

// Replace specfied character by another in whole string
void TpRepl
(
   char              *str,                      // INOUT string to convert
   char               old,                      // IN    old char, to replace
   char               new                       // IN    new char
);

#define TPASCII827_STRIP   ((unsigned char) 0x00)
#define TPASCII827_TRANS   ((unsigned char) 0x80)
// Filter 8-bit ASCII, strip to 7-bit, translate, or replace by specified char
void TpAscii827                                 // translate 8-bit to 7-bit
(
   char               *str,                     // INOUT string to convert
   unsigned char       new                      // IN    new char, or 0x00/0x80
);

// Copy string to destination, clip at buffer-length and terminate it
void TpCopy
(
   char               *dest,                    // OUT   destination string
   char               *source,                  // IN    source string
   int                 len                      // IN    max length incl \0
);

// Return 15-character TPLIB version string
char  *tpVersionString                          // RET   15-char version string
(
   void
);

// Convert C-string to dynamically allocated TPLIB text structure
char  **tpString2Text                           // RET   TPLIB text structure
(
   char               *string,                  // IN    null terminated string
   int                *maxlen,                  // INOUT line length
   int                *lines                    // OUT   nr of lines
);

// Free memory allocated for dynamic TPLIB text
void tpFreeText
(
   char              **text                     // IN    dyn. allocated text
);


/*======== Screen related functions, TPWIOP.C ===============================*/

// Return number of columns on the screen
short  TpScreenCols                             // RET   current screen columns
(
   void
);

// Return number of lines on the screen
short  TpScreenRows                             // RET   current screen rows
(
   void
);

// Return current cursor column, 0 = left
short  TpCursorCol                              // RET   current cursor column
(
   void
);

// Return current cursor row, 0 = top
short  TpCursorRow                              // RET   current cursor row
(
   void
);

// Set new cursor position row and column
void TpSetCursorPos
(
   short               row,                     // IN    destination row
   short               col                      // IN    destination column
);

// Set new cursor visibility and style
void TpSetCursorStyle
(
   BOOL                visible,                 // IN    cursor visible
   BOOL                insert                   // IN    insert style
);

// Set blinking/bright-background mode for fullscreen sessions (VGA)
void TpSetBrightBgMode
(
   BOOL                bright                   // IN    use bright background
);

#endif
