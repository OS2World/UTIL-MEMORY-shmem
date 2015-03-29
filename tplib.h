#ifndef TPLIB_H
#define TPLIB_H
//
// TP library interfaces
//
// Author: J. van Wijk
//
// Developed for LPT/DFSee utilities
//

#if   defined (WIN32)
   #include <windows.h>
   #if defined (_DEBUG)
      #define DUMP 1
   #endif
#elif defined (DOS16)
   #include <dos.h>
#else
   #define DEV32
   #define INCL_BASE
   #define INCL_LONGLONG                        // Use 64bit compiler support
   #define INCL_WINSHELLDATA
   #include <os2.h>
   #define INCL_REXXSAA
   #include <rexxsaa.h>                         // REXX API's
#endif

#include <stdarg.h>                             // variable vfprintf
#include <io.h>                                 // special  i/o
#include <stdio.h>                              // std/file i/o
#include <conio.h>                              // console  i/o
#include <stdlib.h>                             // std C stuff
#include <stddef.h>                             // threadid and errno
#include <string.h>                             // fast strings
#include <ctype.h>                              // type tests & conversions
#include <malloc.h>                             // memory allocation
#include <direct.h>                             // directory funcions
#include <process.h>                            // threading etc
#include <time.h>                               // time functions


#if defined (TPFTRC)                            // TPlib low impact Flow Trace
   #define TPFLOW(cond,nr,hex,str)                                         \
   if (cond)                                                               \
   {                                                                       \
      fprintf(stderr, "\n%12.12s %5u: ", __FILE__, __LINE__);              \
      fprintf(stderr, "%9lu %8.8lX %s", (ULONG) nr, (ULONG) hex, str);     \
   }
#else
   #define TPFLOW(cond,nr,hex,str)
#endif

#ifndef SECTORSIZE
#define SECTORSIZE  512
#endif

#if   defined (WIN32)
   #define  USHORT                 unsigned short int
   #define  SPARAM                 ULONG        // 32 bit env params
   #define  APIRET                 ULONG
   #define  PPARAM                 PVOID        // 32 bit env pointer
   #define  RESV16
   #define  TPINVALID              ((ULONG) -1)
   #define  TPCURTHREAD            ((ULONG) _threadid)
   #define  TPHTHREAD              HANDLE
   #define  TPHFILE                HANDLE
   #define  TpRead(hf,b,z,w)       (APIRET) !ReadFile(hf,b,z,w,NULL)
   #define  TpWrite(hf,b,z,w)      (APIRET) !WriteFile(hf,b,z,w,NULL)
   #define  TpSetSize(hf,s)        0, SetFilePointer(hf,s,NULL,FILE_BEGIN); \
                                   SetEndOfFile(hf)
   #define  TpClose(hf)            (APIRET) !CloseHandle(hf)
   #define  TpDeleteFile(f)        _unlink(f)
   #define  TpSleep(msec)          Sleep(msec)
   #define  TpAlloc(num,size)      calloc((size_t) (num), (size_t) (size))
   #define  TpFreeMem(ptr)         if (ptr != NULL) {free(ptr); ptr = NULL;}
   #define  TpThreadPrioMin()      SetThreadPriority(GetCurrentThread(), \
                                      THREAD_PRIORITY_LOWEST)
   #define  TpThreadPrioLow()      SetThreadPriority(GetCurrentThread(), \
                                      THREAD_PRIORITY_BELOW_NORMAL)
   #define  TpThreadPrioStd()      SetThreadPriority(GetCurrentThread(), \
                                      THREAD_PRIORITY_NORMAL)
   #define  TpThreadPrioHigh()     SetThreadPriority(GetCurrentThread(), \
                                      THREAD_PRIORITY_ABOVE_NORMAL)
   #define  TpThreadPrioMax()      SetThreadPriority(GetCurrentThread(), \
                                      THREAD_PRIORITY_HIGHEST)
   #define  TpBeginThread(f,s,p)   (TPHTHREAD) _beginthread(f,s,p)
   #define  TpKillThread(ht)       TerminateThread(ht, 0)
   #define  FATTR_ARCHIVED         FILE_ATTRIBUTE_ARCHIVE
   #define  FATTR_SYSTEM           FILE_ATTRIBUTE_SYSTEM
   #define  FATTR_HIDDEN           FILE_ATTRIBUTE_HIDDEN
   #define  FATTR_READONLY         FILE_ATTRIBUTE_READONLY
   #define  FATTR_DIRECTORY        FILE_ATTRIBUTE_DIRECTORY
   #define  FATTR_LABEL            0x0008
#elif defined (DOS16)
   typedef  unsigned char          BYTE;        // b
   typedef  unsigned short         BOOL;        // f
   typedef  unsigned short         USHORT;      // us
   typedef  unsigned long          ULONG;       // ul
   typedef  long                   LONG;        // l
   typedef  void                  *PVOID;       // p
   #define  LOBYTE(w)              ((BYTE)(          w        & 0xff))
   #define  HIBYTE(w)              ((BYTE)(((USHORT)(w) >> 8) & 0xff))
   #define  NO_ERROR               0
   #define  TRUE                   1
   #define  FALSE                  0
   #define  SPARAM                 USHORT       // 16 bit env params
   #define  APIRET                 USHORT       // 16 bit env return value
   #define  PPARAM                 char *       // 16 bit env pointer
   #define  TPCURTHREAD            ((ULONG) 0)
   #define  TPHTHREAD              ULONG
   #define  TPHFILE                FILE *
   #define  TpRead(hf,b,z,w)       (APIRET) !fread(b,z,1,hf)
   #define  TpWrite(hf,b,z,w)      (APIRET) !fwrite(b,z,1,hf)
   #define  TpSetSize(hf,s)        (APIRET) chsize(fileno(hf),(long) s)
   #define  TpClose(hf)            fclose(hf)
   #define  TpDeleteFile(f)        unlink(f)
   #define  TpSleep(msec)          TpBusyWait(msec)
   #define  TpAlloc(num,size)      halloc((long) (num), (size_t) (size))
   #define  TpFreeMem(ptr)         if (ptr != NULL) {hfree(ptr); ptr = NULL;}
   #define  TpThreadPrioMin()
   #define  TpThreadPrioLow()
   #define  TpThreadPrioStd()
   #define  TpThreadPrioHigh()
   #define  TpThreadPrioMax()
   #define  TpBeginThread(f,s,p)   f(p)
   #define  TpKillThread(ht)
   #define  FATTR_ARCHIVED         _A_ARCH
   #define  FATTR_SYSTEM           _A_SYSTEM
   #define  FATTR_HIDDEN           _A_HIDDEN
   #define  FATTR_READONLY         _A_RDONLY
   #define  FATTR_DIRECTORY        _A_SUBDIR
   #define  FATTR_LABEL            _A_VOLID
#else
   #define  SPARAM              ULONG           // 32 bit env params
   #define  PPARAM              PVOID           // 32 bit env pointer
   #define  RESV16
   #define  TPCURTHREAD         ((ULONG)(*(ULONG  *) _threadid))
   #define  TpAlloc(num,size)   calloc((size_t) (num), (size_t) (size))
   #define  TpFreeMem(ptr)      if (ptr != NULL) {free(ptr); ptr = NULL;}
   #define  TPHTHREAD              TID
   #define  TPHFILE                HFILE
   #define  TpRead(hf,b,z,w)       DosRead(hf,b,z,w)
   #define  TpWrite(hf,b,z,w)      DosWrite(hf,b,z,w)
   #define  TpSetSize(hf,s)        DosNewSize(hf,s)
   #define  TpClose(hf)            DosClose(hf)
   #define  TpDeleteFile(f)        unlink(f)
   #define  TpSleep(msec)          DosSleep(msec)
   #define  TpThreadPrioMin()      DosSetPrty(PRTYS_THREAD,              \
                                      PRTYC_IDLETIME, PRTYD_MAXIMUM, 0)
   #define  TpThreadPrioLow()      DosSetPrty(PRTYS_THREAD,              \
                                      PRTYC_REGULAR, PRTYD_MINIMUM, 0)
   #define  TpThreadPrioStd()      DosSetPrty(PRTYS_THREAD,              \
                                      PRTYC_REGULAR, 0, 0)
   #define  TpThreadPrioHigh()     DosSetPrty(PRTYS_THREAD,              \
                                      PRTYC_FOREGROUNDSERVER, PRTYD_MAXIMUM, 0)
   #define  TpThreadPrioMax()      DosSetPrty(PRTYS_THREAD,              \
                                      PRTYC_TIMECRITICAL, 0, 0)
   #define  TpBeginThread(f,s,p)   _beginthread(f, NULL, s, p)
   #define  TpKillThread(ht)       DosKillThread(ht)
   #define  FATTR_ARCHIVED         FILE_ARCHIVED
   #define  FATTR_SYSTEM           FILE_SYSTEM
   #define  FATTR_HIDDEN           FILE_HIDDEN
   #define  FATTR_READONLY         FILE_READONLY
   #define  FATTR_DIRECTORY        FILE_DIRECTORY
   #define  FATTR_LABEL            0x0008
#endif

#include <tpcon.h>                              // TP ANSI console and tracing
#include <tpwin.h>                              // text-mode windowing

#define TP_ERROR                     813        // Generic TP error
#define TP_FILE_EXISTS               814        // File already exists
#define TP_INVALID_DRIVE             815        // Drive (letter) invalid
#define TP_INVALID_FILE              816        // File cannot be opened
#define TP_PENDING                   817        // Function pending
#define TP_FAILED                    818        // Function failed
#define TP_ALLOC_ERROR               819        // Memory allocation error
#define TP_NO_COMPRESS               830        // No compression achieved
#define TP_NO_INITIALIZE             831        // No compress init
#define TP_ABORTED                   837        // Function aborted
#define TP_INVALID_HANDLE            840        // Invalid handle specified
#define TP_BAD_OPTION_CHAR           850        // option char out of range
#define TP_TOO_MANY_ARGS             851        // too many argumants for cmd

// Generic definition for a linked list of strings (like warnings/errors)
typedef struct tpstrlist
{
   char               *string;                  // payload
   struct tpstrlist   *next;                    // next element
} TPSTRLIST;                                    // end of struct "tpstrlist"

// Add string to string-list (allocate memory)
char *TpStrListAdd                              // RET   added string
(
   TPSTRLIST         **list,                    // IN    address of list (head)
   char               *str                      // IN    string to add
);

// Free string-list (free memory)
void  TpStrListFree
(
   TPSTRLIST         **list                     // IN    address of list (head)
);

#pragma pack(1)                                 // byte packing
typedef struct _tpfs_ebpb                       // ext. boot parameter block
{
   USHORT              SectSize;                // bytes per sector (BPB start)
   BYTE                ClustSize;               // sectors per cluster
   USHORT              FatOffset;               // reserved sectors to 1st FAT
   BYTE                NrOfFats;                // nr of FATS        (FAT only)
   USHORT              RootEntries;             // Max std entries \ (FAT only)
   USHORT              Sectors;                 // nr of sectors if <  64K
   BYTE                MediaType;               // mediatype (F8 for HD)
   USHORT              FatSectors;              // nr of sectors/FAT (FAT only)
   USHORT              LogGeoSect;              // nr of sectors/Track
   USHORT              LogGeoHead;              // nr of heads
   ULONG               HiddenSectors;           // Sector-offset from MBR/EBR
   ULONG               BigSectors;              // nr of sectors if >= 64K
} TPFS_EBPB;                                    // end of struct "tpfs_ebpb"


#if defined (DOS16)                             // Dos interface defs
   typedef struct _tpfs_gparm                   // IoCtl structure
   {
      BYTE          special;                    // special functions
      BYTE          devtype;                    // device type
      USHORT        devattr;                    // device attributes
      USHORT        cylinders;                  // Nr of cylinders
      BYTE          density;                    // Media density
      TPFS_EBPB     eb;                         // Extended BPB
   } TPFS_GPARM;                                // end of struct "tpfs_gparm"
#endif


// Execute standard commands
APIRET TpStdCommand
(
   void                                         // parameters through TPA
);


#define TPACK_TYPESIG  '#'                      // small-file compr indicator
#define TPACK_FILESIG  "Tpack#"                 // file compression header
                                                // followed by 2 byte bufsize
                                                // and 2+2 byte method/size

#define TPACK_TYPEBIG  '$'                      // big-file compr indicator
#define TPACK_FILEBIG  "Tpack$"                 // big-file compression header
                                                // followed by 2 byte reserverd
                                                // 4 byte max buffer-size and
                                                // and 4+4 byte method/size

#define TPACK_MRLE_04  0x10                     // run length encoding

#define TPACK_MLZW_10  0x0a                     // LZW 10 bits
#define TPACK_MLZW_11  0x0b
#define TPACK_MLZW_12  0x0c
#define TPACK_MLZW_13  0x0d
#define TPACK_MLZW_14  0x0e                     // LZW 14 bits

#define TPACK_MLZWMAX  0x1f                     // maximum LZW method value

typedef ULONG          TPHANDLE;

#if   defined (WIN32)
   typedef FILE       *TPACK_PARAM;
#elif defined (DOS16)
   typedef FILE _FAR_ *TPACK_PARAM;
#else
   typedef FILE       *TPACK_PARAM;
#endif

// Register a new instance of the Tpack abstract-data-type
ULONG TpackRegister                             // RET   result code
(
   TPHANDLE           *tph                      // OUT   Tpack handle
);

// Terminate use of an instance of the Tpack abstract-data-type
void TpackTerminate
(
   TPHANDLE            tph                      // IN    Tpack handle
);


// Buffer Compression routine
ULONG TpackBufCompress
(
   TPHANDLE            tph,                     // IN    Tpack handle
   ULONG               method,                  // IN    compression method
   BYTE               *ibuf,                    // IN    input buffer
   ULONG               ilen,                    // IN    input buffer length
   BYTE               *obuf,                    // OUT   output buffer
   ULONG               olen,                    // IN    output buffer length
   ULONG              *size                     // OUT   compressed size
);

// Buffer Un-compress routine
ULONG TpackBufUncompress
(
   TPHANDLE            tph,                     // IN    Tpack handle
   ULONG               method,                  // IN    compression method
   BYTE               *ibuf,                    // IN    input buffer
   ULONG               ilen,                    // IN    input buffer length
   BYTE               *obuf,                    // OUT   output buffer
   ULONG               olen,                    // IN    output buffer length
   ULONG              *size                     // OUT   un-compressed size
);


typedef int (* TPACK_RD_CALLBACK)               // RET   one character value
(
   TPACK_PARAM         calldata                 // INOUT callback data
);

typedef int (* TPACK_WR_CALLBACK)               // RET   one character value
(
   int                 value,                   // IN    character to write
   TPACK_PARAM         calldata                 // INOUT callback data
);

// Compress input-file to output file
ULONG TpackCompress
(
   TPHANDLE            tph,                     // IN    Tpack handle
   ULONG               method,                  // IN    compression method
   TPACK_RD_CALLBACK   fnget,                   // input  function
   TPACK_PARAM         input,                   // input  data reference
   TPACK_WR_CALLBACK   fnput,                   // output function
   TPACK_PARAM         output                   // output data reference
);

// expansion routine
ULONG TpackUncompress
(
   TPHANDLE            tph,                     // IN    Tpack handle
   ULONG               method,                  // IN    compression method
   TPACK_RD_CALLBACK   fnget,                   // input  function
   TPACK_PARAM         input,                   // input  data reference
   TPACK_WR_CALLBACK   fnput,                   // output function
   TPACK_PARAM         output                   // output data reference
);



//--------- TPlib SCRIPT/REXX subcommand definitions and functions -----------

typedef APIRET (* TP_NATIVE_CALLBACK)           // modelled after MultiCmd
(
   char               *cmd,                     // IN    command string (input)
   BOOL                echo,                    // IN    echo   before each cmd
   BOOL                prompt                   // IN    prompt after  each cmd
);

// Run native TPS script using callback (from parsed RUN cmd if runcmd == NULL)
APIRET TpsNativeRun
(
   char               *name,                    // IN    TPS script to execute
   char               *runcmd,                  // IN    RUN cmd string or NULL
   TP_NATIVE_CALLBACK  subcom                   // IN    subcommand handler
);

#if   defined (DEV32)

typedef ULONG (* _System TP_SUBCOM_CALLBACK)
(
   PRXSTRING           cmd,                     // IN    command string
   PUSHORT             err_flag,                // OUT   ERROR/FAILURE
   PRXSTRING           rv                       // OUT   string retcode
);


// Execute a REXX command script using a subcommand environment
APIRET TpsRexxRun
(
   char               *name,                    // IN    REXX proc to execute
   char               *args,                    // IN    Arguments
   char               *envname,                 // IN    REXX environment name
   TP_SUBCOM_CALLBACK  subcom                   // IN    subcommand handler
);


// Set string variable in the REXX variable pool using printf syntax
APIRET TpsRexxSetnum
(
   char              *name,                     // IN    Name of variable
   ULONG              ulv,                      // IN    value for variable
   char              *fmt                       // IN    format strings
);

// Set a string variable in the REXX variable pool
APIRET TpsRexxSetvar
(
   char              *name,                     // IN    Name of variable
   void              *value,                    // IN    ptr to value buffer
   ULONG              length                    // IN    length of value
);


//--------- TPlib TpFileTree, recursive tree itterator ---------------------
// Recursive findfile with call-back function to operate on found files
// Derived from SysFileTree implementation from REXXUTIL (IBMCPP samples)
// Major functional changes made:
//
//   - REXX interfaces (stem, variablepool) changed to normal 'C'
//   - Action on each matching file implemented as a call-back function
//     with the full "true-filename" and a FILEFINDBUF4 structure as parameters
//   - Source and Destination mask use different syntax (+,-,* and ARSHD)
//
//     options  - Any combo of the following:
//                 'B' - Search for files and directories. (default)
//                 'D' - Search for directories only.
//                 'F' - Search for files only.
//                 'S' - Recursively scan subdirectories.

typedef ULONG (* FLTREE_CALLBACK)               // RET   callback result
(
   char               *fullname,                // IN    full filename
   FILEFINDBUF4       *fileinfo,                // IN    attrib, EA info etc
   void               *calldata                 // INOUT callback data
);


// Itterate through files and directories matching filespec and attributes
ULONG TpFileTree
(
   char               *fspec,                   // IN    Filespec to match
   char               *fopts,                   // IN    Find options
   char               *fattr,                   // IN    Select attributes
   char               *mattr,                   // IN    Modify attributes
   char              **exclude,                 // IN    Exclude file-spec
   FLTREE_CALLBACK     callback,                // IN    function to call back
   void               *calldata                 // IN    callback data
);

#endif


//--------- TPlib command execution with full output redirection ------------

// Execute an external command, output redirected to TPRINTF
APIRET tp_exec_cmd                              // RET   command exit-code (RC)
(
   char              *cmd                       // IN    command to execute
);



//--------- 32-bit CRC implementation --------------------------------------
// CRC32 interface; derived from textbook:
//       'C' programmers guide to NETBIOS
//
// Calculate CRC-32 value for supplied data (no TRACE info)
ULONG TpCrc32
(
   void               *pcDat,                   // IN    pointer to data
   ULONG               ulSize                   // IN    length of data
);

// Calculate sector checksum, using HPFS algorithm and fixed 512 byte size
ULONG TpHpfsCheckSum                            // RET   HPFS style crc
(
   char               *data                     // IN    data sector
);

// Calculate 32-bit CRC value using LVM compatible algorithm and polynom
ULONG TpCalculateLvmCrc
(
   char               *area,                    // IN    data area needing CRC
   ULONG               size                     // IN    size of the data area
);

//--------- FileSystem functions -------------------------------------------

#define TPS2MB(secs,bps) ((double) ((double) (secs)                       \
                                 * ((double) ((bps != 0) ? (bps) : 512))  \
                                 / ((double) 1048576)))


// Perform a shutdown (if possible) followed by a (COLD) boot of the system
BOOL TpReboot                                   // RET   reboot OK
(
   void
);


// Set critical error handling to auto-fail (versus interactive Abort, retry .)
void TpFsCritErrAutoFail
(
   BOOL                fail                     // IN    autofail on CritErr
);

// Build string with present volumes
void TpFsVolumes
(
   BOOL                flop,                    // IN    include floppies
   char               *vols                     // OUT   Present volumes
);

// Show volume/filesystem info for all registred drive-letters
void TpFsDrivemap
(
   char               *lead,                    // IN    Leading text string
   BOOL                flop                     // IN    include floppies
);

// Show volume/filesystem info on a single output line using tprintf
APIRET TpFsShow
(
   char               *lead,                    // IN    Leading text string
   char               *drive                    // IN    Drive specification
);

// Determine attached fstype, e.g. HPFS for specified drive
BOOL TpFsType                                   // RET   FS type resolved
(
   char              *drive,                    // IN    Drive specification
   char              *fstype,                   // OUT   Attached FS type
   char               *details                  // OUT   detailed info (UNC)
);


// Determine free and total-available space (sectors) on specified drive
APIRET TpFsSpace
(
   char               *drive,                   // IN    Drive specification
   ULONG              *sfree,                   // OUT   Free sectors
   ULONG              *stotal,                  // OUT   Total sectors
   USHORT             *bpsect                   // OUT   Sectorsize
);

// Query type for specified path and resolve truename (canonical)
ULONG  FlTrueNameDir                            // RET   0 = Dir, 80 = File
(
   char               *path,                    /* IN    path specification  */
   LINE                true                     /* OUT   true filename       */
);


// Check path, optionaly create it in a recursive fashion
ULONG FlMakePath                                /* RET   result              */
(
   char               *filename                 /* IN    Directory-path      */
);

// Make an 8-dot-3 compatible copy of the supplied path/filename string
ULONG FlMake8dot3                               // RET   length converted name
(
   char               *filename,                // IN    relative/absolute path
   char               *fname8d3                 // OUT   8dot3 compatible buf
);                                              //       with size >= filename

// Function : count number of non-wildcard chars in string
int FlStrwcnt                                   // RET   nr of non-wild chars
(
    char              *s                        // IN    candidate string
);


// wildcard compare of candidate to template string
int FlStrwcmp                                   // RET   negative if no match
(
    char              *cs,                      // IN    candidate string
    char              *ts                       // IN    template string
);


// See FlStrwcmp; case-insensitive
int FlStrwicmp                                  // RET   negative if no match
(
    char              *cs,                      // IN    candidate string
    char              *ts                       // IN    template string
);

// Append translated Unicode string-fragment to an ASCII string
char *FlUnicAppend                              // RET   ptr to ASCII string
(
   USHORT             *uni,                     // IN    Unicode string part
   char               *asc,                     // INOUT ASCII string
   USHORT              len                      // IN    maximum Unicode length
);

// Perform a Unicode to ASCII case-sensitive stringcompare (aka strncmp)
int FlUnicStrncmp                               // RET   compare result
(
   char               *uni,                     // IN    Unicode string
   char               *asc,                     // IN    ASCII   string
   size_t              len                      // IN    max ASCII comp-length
);

// Perform a Unicode to ASCII case-insensitive stringcompare (aka strnicmp)
int FlUnicStrnicmp                              // RET   compare result
(
   char               *uni,                     // IN    Unicode string
   char               *asc,                     // IN    ASCII   string
   size_t              len                      // IN    max ASCII comp-length
);

// Append default 8.3 filename extention to filename, if none present
char *FlnameExt                                 // RET   ptr to filename
(
   char               *fname,                   // INOUT filename string
   char               *ext                      // IN    default extention
);

// Find file in a path specified by environment variable (like PATH)
char *FlFindByPath                              // RET   ptr to filename
(
   char               *fname,                   // IN    filename string
   char               *path,                    // IN    env-var with path
   char               *found                    // OUT   found file
);


//--------- CommandParser definitions and functions ---------------------------

#define TPA_BASE      32                        // first valid option ASCII
#define TPA_SIZE      96                        // number of options

#define TPA_ARGC      16                        // maximum nr of params

#define TPA_NONE      ((TPA_TYPE)  0)
#define TPA_NUMBER    ((TPA_TYPE)  1)
#define TPA_STRING    ((TPA_TYPE)  2)
#define TPA_NO_VAL    ((TPA_TYPE)  3)

#define TPA_DFUNIT    ((BYTE)    ' ')           // default unit

#define TPA_CUR       ((TPHANDLE)  3)           // special CURRENT  handle
#define TPA_PREV      ((TPHANDLE)  2)           // special PREVIOUS handle
#define TPA_1ST       ((TPHANDLE)  1)           // special FIRST    handle
#define TPA_NUL       ((TPHANDLE)  0)           // special bad TPA  handle

#define TPA_ALL       ((int)       0)           // get ALL arguments
#define TPA_OPT       ((int)  0xffff)           // get ALL args + options

// shorthand macro's for most used option/argument retrieval
#define TpaOption(o)            TpaOptionYes(     TPA_CUR,o)
#define TpaOptSet(o)           (TpaGetOption(     TPA_CUR,o) != NULL)
#define TpaOptAsString(o,s,b)   TpaOptionAsString(TPA_CUR,o,s,b)
#define TpaOptStr(o,e,d)        TpaOptionStr(     TPA_CUR,o,e,d)
#define TpaOptNum(o,e,d)        TpaOptionNum(     TPA_CUR,o,e,d)
#define TpaOptValue(o)          TpaGetOption(     TPA_CUR,o)
#define TpaOptCount()           TpaGetOptc(       TPA_CUR  )
#define TpaOptMutEx(c,o,m,e)    TpaMutualX(       TPA_CUR,c,o,m,e)
#define TpaArgCount()           TpaGetArgc(       TPA_CUR  )
#define TpaArgValue(n)          TpaGetArgv(       TPA_CUR,n)
#define TpaExeSwitch(o)         TpaOptionYes(     TPA_1ST,o)
#define TpaExeSwitchSet(o)     (TpaGetOption(     TPA_1ST,o) != NULL)
#define TpaExeSwAsString(o,s,b) TpaOptionAsString(TPA_1ST,o,s,b)
#define TpaExeSwitchStr(o,e,d)  TpaOptionStr(     TPA_1ST,o,e,d)
#define TpaExeSwitchNum(o,e,d)  TpaOptionNum(     TPA_1ST,o,e,d)
#define TpaExeSwitchValue(o)    TpaGetOption(     TPA_1ST,o)
#define TpaExeOptc()            TpaGetOptc(       TPA_1ST  )
#define TpaExeMutEx(c,o,m,e)    TpaMutualX(       TPA_CUR,c,o,m,e)
#define TpaExeArgc()            TpaGetArgc(       TPA_1ST  )
#define TpaExeArgv(n)           TpaGetArgv(       TPA_1ST,n)

typedef BYTE TPA_TYPE;                          // option none/number/string

typedef union tpa_value
{
   ULONG               number;                  // number value
   char               *string;                  // string value
} TPA_VALUE;                                    // end of union "tpa_value"

typedef struct tpa_option
{
   TPA_TYPE            type;                    // none/number/string
   BYTE                unit;                    // one char c,m,s etc (on nrs)
   TPA_VALUE           value;
} TPA_OPTION;                                   // end of struct "tpa_option"


// Create new level of command options for a given command string
ULONG TpaParseCommandString                     // RET   result
(
   char               *cmd,                     // IN    command string
   BOOL                freeform,                // IN    free format options
   TPHANDLE           *tph                      // OUT   TPA handle (optional)
);


// Replace current level of command options for a new command string (Reparse)
ULONG TpaReParseCommand                         // RET   result
(
   char               *cmd                      // IN    new command string
);


// Create new level of command options for a set of argc/argv variables
ULONG TpaParseArgcArgv                          // RET   result
(
   int                 argc,                    // IN    argument count
   char               *argv[],                  // IN    array of arguments
   BOOL                freeform,                // IN    free format options
   TPHANDLE           *tph                      // OUT   TPA handle (optional)
);

#define  TPAO_QUIET    ((ULONG)0)
#define  TPAO_NORMAL   ((ULONG)1)
#define  TPAO_VERBOSE  ((ULONG)2)
#define  TPAO_EXTREME  ((ULONG)3)
#define  TPAO_MAXIMUM  ((ULONG)4)

// Get verbosity value from Option 'o'
ULONG TpaOutputVerbosity                        // RET   output verbosity value
(
   char                optchar                  // IN    option character
);

#define  TPAE_QUIT     ((int)'q')
#define  TPAE_IGNORE   ((int)'i')
#define  TPAE_CONFIRM  ((int)'c')

// Get errorStrategy value from Option 'e' and batch-mode indicator 'quit'
int TpaErrorStrategy                            // RET   error strategy value
(
   char                optchar,                 // IN    option character
   BOOL                quit                     // IN    quit as default
);

// Parse a decimal or hex number value from a string
ULONG TpaParseNumber                            // RET   number value
(
   char               *value,                   // IN    value string with nr
   BYTE               *unit                     // OUT   optional unit char, if
);                                              //       not needed use NULL

// Parse a boolean value from a string (empty string returns TRUE)
BOOL TpaParseBool                               // RET   FALSE: 0 - n f off
(
   char               *param                    // IN    pragma parameter
);

// Terminate use of current or all instances of the TPA abstract-data-type
BOOL TpaDropParsedCommand                       // RET   more instances left
(
   BOOL                whole_stack              // IN    drop all, terminate
);

// Show contents of one or all instances of the TPA abstract-data-type
void TpaShowParsedCommand                       // RET   more instances left
(
   BOOL                whole_stack              // IN    show all levels
);

// Get reference to specified option data, or NULL if option not set
TPA_OPTION *TpaGetOption                        // RET   option ptr or NULL
(
   TPHANDLE            tph,                     // IN    TPA handle
   char                opt                      // IN    option character
);

// Get simple YES/NO status for specified option. Not set is "NO"
BOOL TpaOptionYes                               // RET   option set to YES
(
   TPHANDLE            tph,                     // IN    TPA handle
   char                opt                      // IN    option character
);

// Get string value for specified option, convert to string for any type
char *TpaOptionAsString                         // RET   option String value
(
   TPHANDLE            tph,                     // IN    TPA handle
   char                opt,                     // IN    option character
   int                 size,                    // IN    size of buffer
   char               *str                      // OUT   string buffer, also
);                                              // default when not specified

// Get string value for specified option, use default if no string (and warn!)
char *TpaOptionStr                              // RET   option String value
(
   TPHANDLE            tph,                     // IN    TPA handle
   char                opt,                     // IN    option character
   char               *error,                   // IN    error text or NULL
   char               *deflt                    // IN    default value
);

// Get number value for specified option, use default if no number (and warn!)
ULONG TpaOptionNum                              // RET   option Number value
(
   TPHANDLE            tph,                     // IN    TPA handle
   char                opt,                     // IN    option character
   char               *error,                   // IN    error text or NULL
   ULONG               deflt                    // IN    default value
);

// Build space separated concatenated string of arguments
char *TpaGetArgString                           // RET   argument str or NULL
(
   TPHANDLE            tph,                     // IN    TPA handle
   int                 first,                   // IN    first argument to copy
   int                 last,                    // IN    last arg, _ALL or _OPT
   char               *args                     // OUT   argument string
);

// Return comment part of command, if any
char *TpaGetComment                             // RET   comment  str or NULL
(
   TPHANDLE            tph,                     // IN    TPA handle
   char               *comment                  // OUT   comment string
);

// Get reference to specified argument-string
char *TpaGetArgv                                // RET   ptr to argv string
(
   TPHANDLE            tph,                     // IN    TPA handle
   int                 argn                     // IN    argument number 0..n
);

// Get the number of arguments for specified TPA instance
int TpaGetArgc                                  // RET   argument count
(
   TPHANDLE            tph                      // IN    TPA handle
);

// Get the number of options for specified TPA instance
int TpaGetOptc                                  // RET   option count
(
   TPHANDLE            tph                      // IN    TPA handle
);

// Test for mutual exclusive options and specified condition; handle error msg
BOOL TpaMutualX
(
   TPHANDLE            tph,                     // IN    TPA handle
   BOOL                cond,                    // IN    other  exclusive cond
   char               *opts,                    // IN    mutual exclusive opts
   char               *condmsg,                 // IN    msg when cond TRUE or NULL
   char               *msgtext                  // OUT   message text or NULL
);                                              //       (NULL ==> Tprintf)

//--------- Registration checking and definitions ---------------------------

typedef enum tpreg
{
   TPREG_WHEN_NOT_REGISTRED,
   TPREG_DISPLAY_ONLY,
   TPREG_DISPLAY_CONFIRM,
   TPREG_CONFIRM_ONLY
} TPREG;                                        // end of enum "tpreg"


// Print registration info to the screen and request confirmation
void TprRegistrationInfo
(
   TPREG               mode,                    // IN    display/confirm mode
   BOOL                confirm                  // IN    confirmation required
);

// Check registration availability and acceptance, and evaluation expiration
BOOL TprRegistrationTest                        // RET   not expired/cracked
(
   char               *product,                 // IN    name product/regfile
   char               *major,                   // IN    major version
   long                introduction,            // IN    introduction date
   long                expiration               // IN    expiration date
);

// Get registration status and description
BOOL TprRegistrationValid                       // RET   registration valid
(
   char               *description              // OUT   optional description
);

#endif
