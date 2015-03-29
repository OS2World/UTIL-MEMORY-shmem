#ifndef TPWIN_H
#define TPWIN_H
//
// TP window library interfaces
//
// Author: J. van Wijk
//
// Developed for LPTool/DFSee utilities
//

#define TPW_INVALID       (-1)                  // invalid value

typedef ULONG             TPWHANDLE;            // TP window handle
typedef ULONG             TPWHENUM;             // TP enumeration handle

// Predefined window handles
#define TPHWND_NULL       (TPWHANDLE) 0
#define TPHWND_DESKTOP    (TPWHANDLE) 1
#define TPHWND_OBJECT     (TPWHANDLE) 2         // not supported yet
#define TPHWND_TOP        (TPWHANDLE) 3         // last window in Z-order
#define TPHWND_BOTTOM     (TPWHANDLE) 4         // currently equals desktop


// Query window codes
#define TPQW_NEXT         0
#define TPQW_PREV         1
#define TPQW_TOP          2
#define TPQW_BOTTOM       3
#define TPQW_OWNER        4
#define TPQW_PARENT       5

// TPWIN window classes
//
// Note: STATIC without buffer behaves like FRAME, with empty buffer as CANVAS
//      STATIC with ASCII artwork can be used as a DIALOG frame

typedef enum tpwclass                           // window classes
{                                               // type of client area painting
   TPW_FRAME,                                   // border only, no client fill
   TPW_CANVAS,                                  // background color / pattern
   TPW_STATIC,                                  // static window text
   TPW_SBVIEW,                                  // TPRINTF scroll buffer view
   TPW_ENTRYFIELD,                              // simple 1-line entry field
   TPW_TEXTVIEW,                                // ascii text viewer
   TPW_BUTTON                                   // button - push/radio/checkbox
} TPWCLASS;                                     // end of enum "tpwclass"


typedef enum tpwmsgid                           // TP window messages
{
   TPWM_CREATE,                                 // window has just been created
   TPWM_DESTROY,                                // window will be destroyed
   TPWM_CHAR,                                   // keyboard event, key in mp2
   TPWM_COMMAND,                                // window command (menu)
   TPWM_CLOSE,                                  // close this window
   TPWM_QUIT,                                   // terminate application
   TPWM_HELP,                                   // activate help system
   TPWM_BORDER,                                 // paint border only
   TPWM_STATUS,                                 // paint status info, add text
   TPWM_PAINT,                                  // paint invalided win contents
   TPWM_SETFOCUS,                               // keyboard input focus
   TPWM_ENABLE,                                 // window enable notification
   TPWM_SHOW,                                   // window visible notification
   TPWM_ACTIVATE,                               // set (frame) window active
   TPWM_SELECTED,                               // set (dialog) item selected
   TPWM_CURSORVISIBLE,                          // set cursor visibility
   TPWM_MOVE,                                   // window has been moved
   TPWM_SIZE,                                   // window has been resized
   TPWM_CONTROL,                                // dialog control message
   TPWM_INITDLG,                                // init dialog
   TPWM_USER         = 0x1000                   // lowest user message id
} TPWMSGID;                                     // end of enum "tpwmsgid"

typedef struct tpwqmsg
{
   TPWHANDLE           hwnd;
   ULONG               msg;                     // message id
   ULONG               mp1;
   ULONG               mp2;
} TPWQMSG;                                      // end of struct "tpwqmsg"

typedef struct tp2d                             // TP two-dimensional entity
{
   short               x;                       // x-coord (horizontal)
   short               y;                       // y-coord (vertical)
} TP2D;                                         // end of struct "tp2d"

typedef TP2D           TPOINT;                  // TP two-dimensional point


typedef struct tprect                           // TP (normalized) rectangle
{
   short               left;
   short               top;
   short               right;
   short               bottom;
} TPRECT;                                       // end of struct "tprect"

typedef struct tpcell                           // TP display cell
{
   BYTE                ch;                      // character value
   BYTE                at;                      // color attribute
} TPCELL;                                       // end of struct "tpcell"

typedef enum tphselect
{
   TPH_PREV,                                    // next older entry
   TPH_NEXT,                                    // next newer entry
   TPH_HIGHEST,                                 // highest order (latest)
   TPH_LOWEST                                   // lowest order  (oldest)
} TPHSELECT;                                    // end of enum "tphselect"

#define TPH_NOCURR ((USHORT) 0xffff)            // no current index

typedef struct tphelem                          // history element
{
   ULONG               order;                   // element order value
   char               *string;                  // history string
} TPHELEM;                                      // end of struct "tphelem"

typedef struct tphist                           // line history information
{
   USHORT              hsize;                   // nr of history entries
   USHORT              esize;                   // size of history string
   BOOL                ascend;                  // ascending sort-order
   USHORT              current;                 // current element
   TPHELEM            *elem;                    // history element array
   char               *buf;                     // character buffer
} TPHIST;                                       // end of struct "tphist"

#define TPWSB_VIEWS    4
typedef struct tpsbdata                         // scroll buffer data
{
   ULONG               vsize;                   // virtual/view size (lines)
   ULONG               width;                   // width of buffer, linelength
   ULONG               length;                  // length of buffer, #lines
   ULONG               firstline;               // First written line in buf
   BOOL                midscroll;               // scroll when not at end
   BOOL                wrap;                    // Wrap long lines on write
   TPWHANDLE           view;                    // auto-update view window
   TPCELL             *buf;                     // display scroll buffer
} TPSBDATA;                                     // end of struct "tpsbdata"

typedef struct tpsbview                         // scroll buffer view info
{
   ULONG               topline;                 // index of top-line
   short               leftcol;                 // offset in string for col 0
   ULONG               maxtop;                  // current maximum for topline
   short               maxcol;                  // current maximum for leftcol
   TPSBDATA           *sbdata;                  // related scroll-buffer data
   MBUF                status;                  // free-format status text
   BYTE                scolor;                  // free-format status color
} TPSBVIEW;                                     // end of struct "tpsbview"

typedef struct tpentryfield                     // entry field info
{
   short               leftcol;                 // offset in string for col 0
   short               maxcol;                  // current maximum for leftcol
   short               curpos;                  // offset of cursor position
   short               rsize;                   // real allocated size
   TPHIST             *history;                 // optional history buffer
   char               *buf;                     // entry field buffer
} TPENTRYFIELD;                                 // end of struct "tpentryfield"

typedef struct tptextview                       // text viewer
{
   ULONG               topline;                 // index of top-line
   short               leftcol;                 // offset in string for col 0
   ULONG               maxtop;                  // current maximum for topline
   short               maxcol;                  // current maximum for leftcol
   char              **buf;                     // display text array
} TPTEXTVIEW;                                   // end of struct "tptextview"

typedef struct tpstatic                         // static text
{
   char              **buf;                     // display text array
} TPSTATIC;                                     // end of struct "tpstatic"

typedef struct tpbutton
{
   BOOL                checked;                 // button state
   char               *text;                    // button descriptive text
} TPBUTTON;                                     // end of struct "tpbutton"

typedef struct tpwindow                         // TP window definitions
{
   TPRECT              client;                  // client window dimensions
   TPRECT              border;                  // border window dimensions
   TPCELL              clientclear;             // default client cell
   TPCELL              borderclear;             // default border cell
   ULONG               style;                   // window & border styles
   ULONG               helpid;                  // compound helpid
   char               *title;                   // window title
   BYTE                titlecolor;              // title color
   BYTE                titlefocus;              // title focus color
   char               *footer;                  // footer border text
   BYTE                footercolor;             // footer color
   BYTE                footerfocus;             // footer focus color
   USHORT              dlgFocusID;              // ID of child to get focus
   ULONG               dlgResult;               // result when used as dialog
   union
   {
      TPSBVIEW         sb;                      // scroll-buffer view
      TPENTRYFIELD     ef;                      // entryfield 1-line
      TPTEXTVIEW       tv;                      // text viewer (scrollable)
      TPSTATIC         st;                      // static text
      TPBUTTON         bu;                      // push- radio or checkbox
   };
} TPWINDOW;                                     // end of struct "tpwindow"

// helpid when no help reaction (F1) is wanted
#define TPWH_NO_HELP   0xffffffff               // help-id for no-help

// TPWS_ style bits for window and border
#define TPWS_TITLEBORDER      0x00000001        // use a title-border at top
#define TPWS_SIDEBORDERS      0x00000002        // use side borders  left/right
#define TPWS_FOOTRBORDER      0x00000004        // use footer-border at bottom
#define TPWS_BORDERLINES      0x00000008        // use lines in border
#define TPWS_BRACKETSIDE      0x00000010        // use [] with no borderlines
#define TPWS_LINESDOUBLE      0x00000020        // linestyle single/double
#define TPWS_LINESHALF        0x00000040        // linestyle half-blocks
#define TPWS_LINESFULL        0x00000080        // linestyle full-blocks
#define TPWS_LINESCUSTOM      0x00000100        // linestyle custom settable
#define TPWS_LEFTJUSTIFY      0x00000200        // left-justify title & footer
#define TPWS_MOVEABLE         0x00000400        // can be moved/sized by user
#define TPWS_FOCUS_PAINT      0x00000800        // paint on set-focus (popup)
#define TPWS_VISIBLE          0x00001000        // window could be visible
#define TPWS_DISABLED         0x00002000        // window is disabled
#define TPWS_SAVEBITS         0x00004000        // save underlying cells
#define TPWS_SYNCPAINT        0x00008000        // paint on invalidate
#define TPWS_HCHILD_SIZE      0x00010000        // horizontal resize this child
#define TPWS_VCHILD_SIZE      0x00020000        // vertical   resize this child
#define TPWS_HCHILD_MOVE      0x00040000        // H move child on parent resize
#define TPWS_VCHILD_MOVE      0x00080000        // V move child on parent resize

#define TPWS_FOURBORDERS (TPWS_TITLEBORDER | TPWS_SIDEBORDERS | TPWS_FOOTRBORDER)
#define TPWS_CHILDWINDOW (TPWS_BORDERLINES | TPWS_SYNCPAINT   | TPWS_VISIBLE)
#define TPWS_STDWINDOW   (TPWS_CHILDWINDOW | TPWS_SAVEBITS)


// TPxS_ style bits for control flags (B = button, E = entryfield ...)
// The 8 high-order bits in the style are reserved for controls
// These bits are NOT unique for different control classes!

// TPBS_ button control styles
#define TPBS_PUSHBUTTON       0x00000000        // push  button
#define TPBS_RADIOBUTTON      0x01000000        // radio button
#define TPBS_AUTORADIOBUTTON  0x05000000        // automatic radio button
#define TPBS_CHECKBOX         0x02000000        // checkbox
#define TPBS_AUTOCHECKBOX     0x06000000        // automatic checkbox
#define TPBS_AUTOMATIC        0x04000000        // automatic draw variant
#define TPBS_PRIMARYSTYLES    0x07000000        // primary styles mask

#define TPBS_HELP             0x08000000        // Help button (TPWM_HELP)

// TPES_ entryfield control styles
#define TPES_LEFT             0x00000000        // left justified
#define TPES_CENTER           0x01000000        // centered
#define TPES_RIGHT            0x02000000        // right justified
#define TPES_UNREADABLE       0x04000000        // unreadable field (password)
#define TPES_CTRL_FIELD       0x08000000        // handle ctrl-arrow in field
#define TPES_DLGE_FIELD       0x10000000        // handle Esc/Enter in Dialog

// TPWM_COMMAND msg source codes
#define TPCMDSRC_PUSHBUTTON      1
#define TPCMDSRC_MENU            2
#define TPCMDSRC_ACCELERATOR     3
#define TPCMDSRC_FONTDLG         4
#define TPCMDSRC_FILEDLG         5
#define TPCMDSRC_PRINTDLG        6
#define TPCMDSRC_COLORDLG        7
#define TPCMDSRC_OTHER           0


// A linestyle is defined by a 48 character string in 4 groups of 12
// LINESDOUBLE, LINESHALF and LINESFULL (see TPWS above) are predefined
// and LINESCUSTOM can be defined using the tpwSetLinesCustom function
//
// TPW linestyle groups
#define TPLP_STANDARD (TPLP_POS * 0)            // no special condition
#define TPLP_FOCUS    (TPLP_POS * 1)            // window has focus
#define TPLP_ACTIVE   (TPLP_POS * 2)            // window is active (dialog)
#define TPLP_SELECTED (TPLP_POS * 3)            // window is selected
#define TPLP_SIZE     (TPLP_POS * 4)            // total length of string

// TPW linestyle position definitions
#define TPLP_LFT              0                 //        left   side
#define TPLP_TLC              1                 // top    left   corner
#define TPLP_TOP              2                 // top
#define TPLP_TRC              3                 // top    right  corner
#define TPLP_RGT              4                 //        right  side
#define TPLP_BLC              5                 // bottom left   corner
#define TPLP_BOT              6                 // bottom
#define TPLP_BRC              7                 // bottom right  corner
#define TPLP_TXL              8                 // text   left   stop
#define TPLP_TXR              9                 // text   right  stop
#define TPLP_L1L             10                 // single line, left
#define TPLP_R1L             11                 // single line, right
#define TPLP_POS             12                 // nr of items in string


// TPW position option bits                        (SetWindowPos)
#define TPSWP_SIZE            0x00000001        // resize window (abs/relative)
#define TPSWP_MOVE            0x00000002        // move window (rel to parent)
#define TPSWP_ABSOLUTE        0x00010000        // move window absolute to scr
#define TPSWP_RELATIVE        0x00020000        // move window relative to self
#define TPSWP_ZORDER          0x00000004        // change Z-order, not used yet
#define TPSWP_SHOW            0x00000008
#define TPSWP_HIDE            0x00000010
#define TPSWP_NOREDRAW        0x00000020
#define TPSWP_NOADJUST        0x00000040
#define TPSWP_ACTIVATE        0x00000080
#define TPSWP_DEACTIVATE      0x00000100
#define TPSWP_EXTSTATECHANGE  0x00000200
#define TPSWP_MINIMIZE        0x00000400
#define TPSWP_MAXIMIZE        0x00000800
#define TPSWP_RESTORE         0x00001000
#define TPSWP_FOCUSACTIVATE   0x00002000
#define TPSWP_FOCUSDEACTIVATE 0x00004000

// window flags definitions
#define TPFF_ACTIVE           0x0002            // active window (dialog)
#define TPFF_DLGDISMISSED     0x0010            // dialog is dismissed
#define TPFF_SELECTED         0x0040            // window is selected
#define TPFF_COLLAPSED        0x0080            // window is collapsed to title
                                                // size stored in _X and _Y us

#define TPQWS_USER            0                 // user definable ushort
#define TPQWS_ID              1                 // window id
#define TPQWS_X               2                 // x value
#define TPQWS_Y               3                 // y value
#define TPQWS_FLAGS           4                 // window flags
#define TPQWS_SIZE            5                 // nr of window ushorts

#define TPQWL_USER            0                 // user definable ulong
#define TPQWP_USER            1                 // user definable pointer
#define TPQWL_SIZE            2                 // nr of window ulongs and ptrs


// Predefined dialog id values
#define TPDID_OK                     1
#define TPDID_CANCEL                 2
#define TPDID_ERROR                  0xffff

// MessageBox return values and flag definitions
#define TPMBID_OK                    1
#define TPMBID_CANCEL                2
#define TPMBID_ABORT                 3
#define TPMBID_RETRY                 4
#define TPMBID_IGNORE                5
#define TPMBID_YES                   6
#define TPMBID_NO                    7
#define TPMBID_HELP                  8
#define TPMBID_ENTER                 9
#define TPMBID_ERROR                 0xffff

#define TPMB_OK                      0x0000
#define TPMB_OKCANCEL                0x0001
#define TPMB_RETRYCANCEL             0x0002
#define TPMB_ABORTRETRYIGNORE        0x0003
#define TPMB_YESNO                   0x0004
#define TPMB_YESNOCANCEL             0x0005
#define TPMB_CANCEL                  0x0006
#define TPMB_ENTER                   0x0007
#define TPMB_ENTERCANCEL             0x0008
#define TPMB_PRIMARYSTYLES           0x000f

#define TPMB_NOICON                  0x0000
#define TPMB_QUERY                   0x0010
#define TPMB_WARNING                 0x0020
#define TPMB_INFORMATION             0x0030
#define TPMB_ERROR                   0x0040
#define TPMB_ANYICON                 0x00f0

#define TPMB_DEFBUTTON1              0x0000
#define TPMB_DEFBUTTON2              0x0100
#define TPMB_DEFBUTTON3              0x0200

#define TPMB_APPLMODAL               0x0000
#define TPMB_HELP                    0x2000
#define TPMB_MOVEABLE                0x4000


typedef ULONG  (* TPWINPROC)                    // window procedure
(
   TPWHANDLE           hwnd,
   ULONG               msg,
   ULONG               mp1,
   ULONG               mp2
);

// PC-specific color definitions, compatible with OS/2, DOS and Win-NT
#define  TPwFGC(color)  (color & 0x0f)
#define  TPwBGC(color) ((color & 0x0f) << 4)

// Attribute intensity bit
#define  TpwINT  ((BYTE) 0x08)

// Attribute value for color, starting with the default White-on-Black
#define  TPwCNN  ((BYTE) 0x07)

// Attribute values for foreground colors
#define  TPwCNZ  ((BYTE) 0x00)
#define  TPwCNB  ((BYTE) 0x01)
#define  TPwCNG  ((BYTE) 0x02)
#define  TPwCNC  ((BYTE) 0x03)
#define  TPwCNR  ((BYTE) 0x04)
#define  TPwCNM  ((BYTE) 0x05)
#define  TPwCNY  ((BYTE) 0x06)
#define  TPwCNW  ((BYTE) 0x07)
#define  TPwCBZ  ((BYTE) 0x08)
#define  TPwCBB  ((BYTE) 0x09)
#define  TPwCBG  ((BYTE) 0x0A)
#define  TPwCBC  ((BYTE) 0x0B)
#define  TPwCBR  ((BYTE) 0x0C)
#define  TPwCBM  ((BYTE) 0x0D)
#define  TPwCBY  ((BYTE) 0x0E)
#define  TPwCBW  ((BYTE) 0x0F)

// Attribute values for background colors
#define  TPwCnZ  ((BYTE) 0x00)
#define  TPwCnB  ((BYTE) 0x10)
#define  TPwCnG  ((BYTE) 0x20)
#define  TPwCnC  ((BYTE) 0x30)
#define  TPwCnR  ((BYTE) 0x40)
#define  TPwCnM  ((BYTE) 0x50)
#define  TPwCnY  ((BYTE) 0x60)
#define  TPwCnW  ((BYTE) 0x70)
#define  TPwCbZ  ((BYTE) 0x80)
#define  TPwCbB  ((BYTE) 0x90)
#define  TPwCbG  ((BYTE) 0xA0)
#define  TPwCbC  ((BYTE) 0xB0)
#define  TPwCbR  ((BYTE) 0xC0)
#define  TPwCbM  ((BYTE) 0xD0)
#define  TPwCbY  ((BYTE) 0xE0)
#define  TPwCbW  ((BYTE) 0xF0)

// Some combined foreground and background colors with readable names :-)
#define  TP_Default             TPwCNN
#define  TP_Inverse            (TPwCnW + TPwCNZ)
#define  TP_Yellow_on_Cyan     (TPwCnC + TPwCBY)
#define  TP_Black_on_Cyan      (TPwCnC + TPwCNZ)
#define  TP_White_on_Cyan      (TPwCnC + TPwCNW)
#define  TP_Cyan_on_Cyan       (TPwCnC + TPwCNC)
#define  TP_Green_on_Cyan      (TPwCnC + TPwCBG)
#define  TP_Yellow_on_Green    (TPwCnG + TPwCBY)
#define  TP_Black_on_Green     (TPwCnG + TPwCNZ)
#define  TP_White_on_Green     (TPwCnG + TPwCNW)
#define  TP_Green_on_Green     (TPwCnG + TPwCNG)
#define  TP_Yellow_on_Magenta  (TPwCnM + TPwCBY)
#define  TP_Black_on_Magenta   (TPwCnM + TPwCNZ)
#define  TP_White_on_Magenta   (TPwCnM + TPwCNW)
#define  TP_Magenta_on_Magenta (TPwCnM + TPwCNM)
#define  TP_Yellow_on_Blue     (TPwCnB + TPwCBY)
#define  TP_White_on_Blue      (TPwCnB + TPwCNW)
#define  TP_Cyan_on_Blue       (TPwCnB + TPwCBC)
#define  TP_Green_on_Blue      (TPwCnB + TPwCBG)
#define  TP_Yellow_on_Grey     (TPwCbZ + TPwCBY)
#define  TP_Black_on_Grey      (TPwCbZ + TPwCNZ)
#define  TP_White_on_Grey      (TPwCbZ + TPwCNW)
#define  TP_Grey_on_Grey       (TPwCbZ + TPwCBZ)
#define  TP_Green_on_Black     (TPwCnZ + TPwCNG)
#define  TP_Red_on_Black       (TPwCnZ + TPwCBR)
#define  TP_Black_on_Black     (TPwCnZ + TPwCNZ)


// Keyboard (conio, getch) translation values to get unique key-definitions
#define  TPW_KEY_GROUP_0        0x000
#define  TPW_KEY_GROUP_1        0x100


// key-values as delivered by GetKeyEvent or in mp2 with a TPWM_CHAR msg

// Normal key values
#define TPk_F1                  0x13b
#define TPk_F2                  0x13c
#define TPk_F3                  0x13d
#define TPk_F4                  0x13e
#define TPk_F5                  0x13f
#define TPk_F6                  0x140
#define TPk_F7                  0x141
#define TPk_F8                  0x142
#define TPk_F9                  0x143
#define TPk_F10                 0x144
#define TPk_F11                 0x185
#define TPk_F12                 0x186

#define TPk_ENTER               0x00d
#define TPk_BACKSPACE           0x008
#define TPk_TAB                 0x009
#define TPk_ESCAPE              0x01b
#define TPk_BACKQUOTE           0x060

#define TPk_INSERT              0x152
#define TPk_DELETE              0x153
#define TPk_UP                  0x148
#define TPk_DOWN                0x150
#define TPk_LEFT                0x14b
#define TPk_RIGHT               0x14d
#define TPk_PGUP                0x149
#define TPk_PGDN                0x151
#define TPk_HOME                0x147
#define TPk_END                 0x14f


// Shift+key values
#define TPs_F1                  0x154
#define TPs_F2                  0x155
#define TPs_F3                  0x156
#define TPs_F4                  0x157
#define TPs_F5                  0x158
#define TPs_F6                  0x159
#define TPs_F7                  0x15a
#define TPs_F8                  0x15b
#define TPs_F9                  0x15c
#define TPs_F10                 0x15d
#define TPs_F11                 0x187
#define TPs_F12                 0x188

#define TPs_TAB                 0x10f


// Ctrl+key values
#define TPc_F1                  0x15e
#define TPc_F2                  0x15f
#define TPc_F3                  0x160
#define TPc_F4                  0x161
#define TPc_F5                  0x162
#define TPc_F6                  0x163
#define TPc_F7                  0x164
#define TPc_F8                  0x165
#define TPc_F9                  0x166
#define TPc_F10                 0x167
#define TPc_F11                 0x189
#define TPc_F12                 0x18a

#define TPc_ENTER               0x00a
#define TPc_BACKSP              0x07f
#define TPc_TAB                 0x194
#define TPc_2                   0x103
#define TPc_6                   0x01e
#define TPc_MINUS               0x01f
#define TPc_LBRACKET            0x01b
#define TPc_RBRACKET            0x01d
#define TPc_BACKSLASH           0x01c

#define TPc_INSERT              0x192
#define TPc_DELETE              0x193
#define TPc_UP                  0x18d
#define TPc_DOWN                0x191
#define TPc_LEFT                0x173
#define TPc_RIGHT               0x174
#define TPc_PGUP                0x184
#define TPc_PGDN                0x176
#define TPc_HOME                0x177
#define TPc_END                 0x175

#define TPc_A                   0x001
#define TPc_B                   0x002
#define TPc_C                   0x003           // usualy intercepted!
#define TPc_D                   0x004
#define TPc_E                   0x005
#define TPc_F                   0x006
#define TPc_G                   0x007
#define TPc_H                   0x008
#define TPc_I                   0x009
#define TPc_J                   0x00A
#define TPc_K                   0x00B
#define TPc_L                   0x00C
#define TPc_M                   0x00D
#define TPc_N                   0x00E
#define TPc_O                   0x00F
#define TPc_P                   0x010           // usualy intercepted!
#define TPc_Q                   0x011
#define TPc_R                   0x012
#define TPc_S                   0x013           // usualy intercepted!
#define TPc_T                   0x014
#define TPc_U                   0x015
#define TPc_V                   0x016
#define TPc_W                   0x017
#define TPc_X                   0x018
#define TPc_Y                   0x019
#define TPc_Z                   0x01A


// Alt+key values
#define TPa_F1                  0x168
#define TPa_F2                  0x169
#define TPa_F3                  0x16a
#define TPa_F4                  0x16b
#define TPa_F5                  0x16c
#define TPa_F6                  0x16d
#define TPa_F7                  0x16e
#define TPa_F8                  0x16f
#define TPa_F9                  0x170
#define TPa_F10                 0x171
#define TPa_F11                 0x18b
#define TPa_F12                 0x18c

#define TPa_ENTER               0x11c
#define TPa_BACKSP              0x10e
#define TPa_1                   0x178
#define TPa_2                   0x179
#define TPa_3                   0x17a
#define TPa_4                   0x17b
#define TPa_5                   0x17c
#define TPa_6                   0x17d
#define TPa_7                   0x17e
#define TPa_8                   0x17f
#define TPa_9                   0x180
#define TPa_0                   0x181
#define TPa_MINUS               0x182
#define TPa_EQUAL               0x183
#define TPa_LBRACKET            0x11a
#define TPa_RBRACKET            0x11b
#define TPa_SEMICOLON           0x127
#define TPa_QUOTE               0x128
#define TPa_BACKQUOTE           0x129
#define TPa_BACKSLASH           0x12b
#define TPa_COMMA               0x133
#define TPa_DOT                 0x134
#define TPa_SLASH               0x135

#define TPa_INSERT              0x1a2
#define TPa_DELETE              0x1a3
#define TPa_UP                  0x198
#define TPa_DOWN                0x1a0
#define TPa_LEFT                0x19b
#define TPa_RIGHT               0x19d
#define TPa_PGUP                0x199
#define TPa_PGDN                0x1a1
#define TPa_HOME                0x197
#define TPa_END                 0x19f

#define TPa_A                   0x11e
#define TPa_B                   0x130
#define TPa_C                   0x12e
#define TPa_D                   0x120
#define TPa_E                   0x112
#define TPa_F                   0x121
#define TPa_G                   0x122
#define TPa_H                   0x123
#define TPa_I                   0x117
#define TPa_J                   0x124
#define TPa_K                   0x125
#define TPa_L                   0x126
#define TPa_M                   0x132
#define TPa_N                   0x131
#define TPa_O                   0x118
#define TPa_P                   0x119
#define TPa_Q                   0x110
#define TPa_R                   0x113
#define TPa_S                   0x11f
#define TPa_T                   0x114
#define TPa_U                   0x116
#define TPa_V                   0x12f
#define TPa_W                   0x111
#define TPa_X                   0x12d
#define TPa_Y                   0x115
#define TPa_Z                   0x12c


/*======== String related  macro ============================================*/

#define tpSlen(s)  ((short) strlen(s))
#define tpLlen(s)  ((ULONG) strlen(s))


/*======== Specific windowing trace macro's =================================*/

#if defined (DUMP)
   #define TRCMSG(hwnd,msg,mp1,mp2)                                          \
           TRACES(("hwnd:%8.8lx, msg:%2.2lx = %s%s%s, mp:%lx %lx\n",         \
                    hwnd, msg, CBC, tpwMsgDescription(msg), CNN, mp1, mp2));

   #define TRCLAS(txt,hwnd)                                                  \
           TRACES(("%s - hwnd:%8.8lx, class: %s%s%s\n",                      \
                    txt, hwnd, CBM, tpwClassDescription(hwnd), CNN));

   #define TRECTA(txt,rect)                                                 \
           if (rect != NULL)                                                 \
           {                                                                 \
              TRACES(("%s - top:% 3hd  left:% 3hd  bot:% 3hd  right:% 3hd\n",\
                  txt, rect->top, rect->left, rect->bottom, rect->right));   \
           }

   #define TRWBSV(txt,wbs)                                                   \
           if (AnsiTrace >= 70)                                              \
           {                                                                 \
              tpwWbsDescription(txt,wbs);                                    \
           }
   #define TRSTYL(txt,hwnd) TRWBSV(txt,((TPWINBASE *)hwnd)->window->style)


   #define TRWINS(txt)                                                       \
           if (AnsiTrace >= 70)                                              \
           {                                                                 \
              tpwDumpWindows(txt);                                           \
           }

// Return short message description for msg-id
char *tpwMsgDescription
(
   ULONG               msg                      // IN    message-id
);

// Return short description for class-id
char *tpwClassDescription
(
   TPWHANDLE           hwnd                     // IN    window handle or 0
);

// Display overview of a style value, with expanded texts for each flag
void tpwWbsDescription
(
   char               *text,                    // IN    leading text
   ULONG               wbs                      // IN    style value
);

// Dump most important window variables to screen/logfile
void tpwDumpWindows
(
   char               *text                     // IN    identifying string
);

#else
   #define TRCMSG(hwnd,msg,mp1,mp2)
   #define TRCLAS(txt,hwnd)
   #define TRECTA(txt,rect)
   #define TRWBSV(txt,wbs)
   #define TRSTYL(txt,hwnd)
   #define TRWINS(txt)
#endif

/*======== Scroll-buffer setup functions, TPWPRINT.C ========================*/

// Initialize Tprintf hook to a scroll-buffer and related views
ULONG tpwInitPrintfSBHook
(
   TPSBDATA           *sbuf                     // IN    Scroll-buffer data
);

// Terminate Tprintf hook to a scroll-buffer and related views
void tpwTermPrintfSBHook
(
   void
);

// Save (part of) the scroll buffer to specified file as plain ASCII
ULONG tpwSavePrintfSB                           // RET   nr of lines written
(
   char               *fname,                   // IN    name of output file
   ULONG               lines,                   // IN    lines from start/end
   BOOL                fromEnd                  // IN    last lines (from end)
);


/*======== Message related functions, TPWMSG.C ==============================*/

// Get next message from queue (posted msg or keyboard events)
BOOL tpwGetMsg                                  // RET   FALSE if QUIT
(
   TPWQMSG            *qmsg                     // OUT   message packet
);

// Dispatch a message to destination window
ULONG tpwDispatchMsg                            // RET   result
(
   TPWQMSG            *qmsg                     // IN    message packet
);

// Send a message to specified window
ULONG tpwSendMsg                                // RET   result
(
   TPWHANDLE           hwnd,                    // IN    destination window
   ULONG               msg,                     // IN    message id
   ULONG               mp1,                     // IN    msg param 1
   ULONG               mp2                      // IN    msg param 2
);

// Post a message to specified window, 0 indicates the focus-window
BOOL tpwPostMsg                                 // RET   message posted
(
   TPWHANDLE           hwnd,                    // IN    destination window
   ULONG               msg,                     // IN    message id
   ULONG               mp1,                     // IN    msg param 1
   ULONG               mp2                      // IN    msg param 2
);


// Note: use of GetMsg is recommended since it handles other messages too
// Get keystroke(s) and return a unique single value for each (getch) key
ULONG tpwGetKeyEvent                            // RET   unique key value
(
   void
);

/*======== Window related functions, TPWIND.C ===============================*/

// Initialize TP window manager and create the desktop window
TPWHANDLE tpwInitializeDesktop                  // RET   Desktop handle
(
   TPWINDOW           *custom,                  // IN    custom desktop style
   TPWINPROC           winproc                  // IN    custom desktop proc
);

// Terminate TP window manager including the desktop window
void tpwTerminateDesktop
(
   void
);

// Determine if specified handle is an existing window
BOOL tpwIsWindow
(
   TPWHANDLE           hwnd                     // IN    window handle
);

// Query window-handles related to the specified one
TPWHANDLE tpwQueryWindow
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               relation                 // IN    window relation
);

// Get a pointer to the TPWINDOW data from window-handle
TPWINDOW *tpwWindowData
(
   TPWHANDLE           hwnd                     // IN    window handle
);

// Initialize a setup window structure for Create
void tpwSetupWindowData
(
   short               row,                     // IN    top-left row (border)
   short               col,                     // IN    top-left column
   short               rows,                    // IN    nr of rows incl border
   short               cols,                    // IN    nr of cols incl border
   ULONG               style,                   // IN    window & border style
   ULONG               helpid,                  // IN    compound helpid
   BYTE                wincolor,                // IN    default window color
   BYTE                borcolor,                // IN    default border color
   BYTE                winchar,                 // IN    default window char
   BYTE                borchar,                 // IN    default border char
   BYTE                titlecolor,              // IN    default title  color
   BYTE                titlefocus,              // IN    focus   title  color
   char               *title,                   // IN    title text string
   BYTE                footercolor,             // IN    default footer color
   BYTE                footerfocus,             // IN    focus   footer color
   char               *footertxt,               // IN    footer text string
   TPWINDOW           *win                      // OUT   window structure
);

// Create a new base window element and initialize its window-data
// Note: owner and winproc must be 0 for a dialog frame (see CreateDlg)
TPWHANDLE tpwCreateWindow
(
   TPWHANDLE           parent,                  // IN    parent window
   TPWCLASS            class,                   // IN    class of this window
   TPWHANDLE           owner,                   // IN    owner window
   TPWHANDLE           after,                   // IN    insert after ...
   TPWINDOW           *setup,                   // IN    window setup data
   TPWINPROC           winproc                  // IN    window procedure
);

// Destroy a base window element and remove it from the list
ULONG tpwDestroyWindow                          // RET   result
(
   TPWHANDLE           hwnd                     // IN    window handle
);

// Set focus to specified window, notify old and new focus-windows
ULONG tpwSetFocus
(
   TPWHANDLE           hwnd                     // IN    destination window
);

// Enable or disable specified window
ULONG tpwEnableWindow
(
   TPWHANDLE           hwnd,                    // IN    destination window
   BOOL                enable                   // IN    enable flag
);

// Query enable state of window
BOOL tpwIsWindowEnabled                         // RET   window is enabled
(
   TPWHANDLE           hwnd                     // IN    window to query
);

// Sets or clears windows VISIBLE flag, and shows/hides the window
ULONG tpwShowWindow
(
   TPWHANDLE           hwnd,                    // IN    destination window
   BOOL                visible                  // IN    visible flag
);

// Query visible state of window (and ALL of its parents)
BOOL tpwIsWindowVisible                         // RET   window is visible
(
   TPWHANDLE           hwnd                     // IN    window to query
);

// Invalidate all windows in Z-order, except the specified one
// causing repaint of all windows overlapped by Rect
void tpwInvalidateAllRect
(
   TPWHANDLE           hwnd,                    // IN    excluded window
   TPRECT             *rect                     // IN    invalid rectangle
);

// Invalidate indicated rectangle area of specified window, forcing repaint
ULONG tpwInvalidateRect
(
   TPWHANDLE           hwnd,                    // IN    destination window
   TPRECT             *rect,                    // IN    invalid rectangle
   BOOL                invChildren              // IN    invalidate children
);

// Invalidate border area of specified window, forcing border repaint
ULONG tpwInvalidateBorder
(
   TPWHANDLE           hwnd,                    // IN    destination window
   TPRECT             *rect                     // IN    invalid rectangle
);

// Signal start of window-repaint, validate and return rectangle to be painted
BOOL tpwBeginPaint                              // RET   update rect non-empty
(
   TPWHANDLE           hwnd,                    // IN    destination window
   TPRECT             *rect                     // OUT   invalid rectangle
);

// Signal end of window re-paint
BOOL tpwEndPaint
(
   TPWHANDLE           hwnd                     // IN    destination window
);

// Query window rectangle, as a rectangle indicating the client area size
BOOL tpwQueryWindowRect
(
   TPWHANDLE           hwnd,                    // IN    window handle
   TPRECT             *rect                     // OUT   client area size
);                                              //       (left/top are zero)

// Query USHORT window value
USHORT tpwQueryWindowUShort
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index                    // IN    index of window-ushort
);


// Query ULONG  window value
ULONG  tpwQueryWindowULong
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index                    // IN    index of window-ulong
);

// Query PTR    window value
void  *tpwQueryWindowPtr
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index                    // IN    index of window-ptr
);

// Set USHORT window value
BOOL tpwSetWindowUShort
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index,                   // IN    index of window-ushort
   USHORT              us                       // IN    value to set
);

// Set ULONG  window value
BOOL tpwSetWindowULong
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index,                   // IN    index of window-ulong
   ULONG               ul                       // IN    value to set
);

// Query PTR    window value
BOOL tpwSetWindowPtr
(
   TPWHANDLE           hwnd,                    // IN    window handle
   ULONG               index,                   // IN    index of window-ptr
   void               *p                        // IN    value to set
);

// Set window position related attributes
BOOL tpwSetWindowPos
(
   TPWHANDLE           hwnd,                    // IN    window handle or 0
   TPWHANDLE           after,                   // IN    after this in Z-order
   short               x,                       // IN    new abs x-position
   short               y,                       // IN    new abs y-position
   short               cx,                      // IN    new x-size
   short               cy,                      // IN    new y-size
   ULONG               fl                       // IN    positioning options
);

// Resolve window-handle from specified ID, for specified parent
TPWHANDLE tpwWindowFromID
(
   TPWHANDLE           parent,                  // IN    window handle or 0
   USHORT              id                       // IN    window id
);


/*======== Window Procedures and Dialogs, TPWPROC.C =========================*/

// Default window procedure, for any window-class except dialogs
ULONG tpwDefWindowProc                          // RET   result
(
   TPWHANDLE           hwnd,                    // IN    current window
   ULONG               msg,                     // IN    message id
   ULONG               mp1,                     // IN    msg param 1
   ULONG               mp2                      // IN    msg param 2
);

// Default window procedure, for dialogs including their control windows
ULONG tpwDefDlgProc                             // RET   result
(
   TPWHANDLE           hwnd,                    // IN    current window
   ULONG               msg,                     // IN    message id
   ULONG               mp1,                     // IN    msg param 1
   ULONG               mp2                      // IN    msg param 2
);

// Dismiss dialog and pass-on result code
ULONG tpwDismissDlg
(
   TPWHANDLE           hwnd,                    // IN    dialog handle
   ULONG               result                   // IN    result code
);

// Create a Dialog from memory-structures (created frame + linked controls)
TPWHANDLE tpwCreateDlg
(
   TPWHANDLE           parent,                  // IN    parent (ignored!)
   TPWHANDLE           owner,                   // IN    owner  window
   TPWINPROC           dlgproc,                 // IN    dialog procedure
   TPWHANDLE           dlg,                     // IN    dialog frame window
   PVOID               cData                    // IN    user control data
);

// Process a (modal) dialog using a local msg-loop
ULONG tpwProcessDlg                             // RET   dialog rc (dismiss)
(
   TPWHANDLE           hwnd                     // IN    dialog handle
);

// Create, Process and Destroy a (modal) dialog
ULONG tpwDlgBox                                 // RET   dialog rc (dismiss)
(
   TPWHANDLE           parent,                  // IN    parent (ignored!)
   TPWHANDLE           owner,                   // IN    owner  window
   TPWINPROC           dlgproc,                 // IN    dialog procedure
   TPWHANDLE           dlg,                     // IN    dialog frame window
   PVOID               cData                    // IN    user control data
);

/*======== Standard dialogs,      TPWSTDLG.C ================================*/

// Display standard message-box dialog with text, buttons and help-id
ULONG tpwMessageBox
(
   TPWHANDLE           parent,                  // IN    parent window
   TPWHANDLE           owner,                   // IN    owner  window
   char               *message,                 // IN    message text
   char               *title,                   // IN    title for the dialog
   ULONG               helpid,                  // IN    help on message
   ULONG               flags                    // IN    specification flags
);                                              //       see TPMB_xxxx defs


// Display standard prompt-box dialog with text an entryfield and help-id
ULONG tpwPromptBox
(
   TPWHANDLE           parent,                  // IN    parent window
   TPWHANDLE           owner,                   // IN    owner  window
   char               *message,                 // IN    message text
   char               *title,                   // IN    title for the dialog
   ULONG               helpid,                  // IN    help on message
   ULONG               flags,                   // IN    specification flags
   short               eflength,                // IN    max length of value
   char               *value                    // INOUT entry field value
);

/*======== Help related functions, TPWHELP.C ================================*/

// Display standard help dialog with text for specified help-id
ULONG tpwHelpDialog
(
   ULONG               helpid                   // IN    id for helpitem
);

// Register a helptext of one section with multiple items
ULONG tpwRegisterHelpText
(
   ULONG               baseid,                  // IN    base id type/section
   char               *title,                   // IN    section title
   char               *text[]                   // IN    help text array
);

// Free helpmanager resources
void tpwTerminateHelpManager
(
   void
);

/*======== Window drawing functions, TPWDRAW.C ==============================*/

// Set custom linestyle for border painting
BOOL tpwSetLinesCustom                          // RET   linestyle string OK
(
   char               *custom                   // IN   custom string (40)
);

// Draw a character-string at specified position, clip to optional clip-rect
void tpwDrawCharString
(
   TPWHANDLE           hwnd,                    // IN    window handle
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   char               *str                      // IN    string to draw
);

// Draw a character-string at position in specified color, using clip-rect
void tpwDrawCharStrCol
(
   TPWHANDLE           hwnd,                    // IN    window handle
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   char               *str,                     // IN    string to draw
   BYTE                color                    // IN    color attribute
);

// Draw a cell-string at specified position, clip to optional clip-rect
void tpwDrawCellString
(
   TPWHANDLE           hwnd,                    // IN    window handle
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   TPCELL             *cell,                    // IN    cell-string to draw
   short               size                     // IN    nr of cells
);

// Read a cell-string from specified position on screen to a string
void tpwScrReadCellString
(
   short               row,                     // IN    source row
   short               col,                     // IN    source column
   TPCELL             *cell,                    // OUT   cell-string to draw
   short               length                   // IN    nr of cells
);

// Fill area for rectangle with specified cell (clear area)
void tpwFillClientWindow
(
   TPWHANDLE           hwnd,                    // IN    window handle
   TPCELL              cell                     // IN    cell-string to draw
);

// Scroll client area up or down, fill new with specified cell
void tpwScrollClientWindow
(
   TPWHANDLE           hwnd,                    // IN    window handle
   int                 scroll                   // IN    scroll lines (+ = up)
);

// Set cursor position inside a client window
void tpwSetCursorPos
(
   TPWHANDLE           hwnd,                    // IN    window handle
   short               row,                     // IN    destination row
   short               col                      // IN    destination column
);

// Set cursor style for window, visible only when inside (parent) clip area
void tpwSetCursorStyle
(
   TPWHANDLE           hwnd,                    // IN    window handle
   BOOL                insert                   // IN    insert style
);

/*======== Window utility functions, TPWUTIL.C ==============================*/

// Start enumeration of child windows
TPWHENUM tpwBeginEnumWindows                    // RET   enumeration handle
(
   TPWHANDLE           parent                   // IN    Parent window handle
);

// End an enumeration of child-windows (free resources)
BOOL tpwEndEnumWindows                          // RET   henum was valid
(
   TPWHENUM            henum                    // IN    Enumeration handle
);

// Retrieve next child's handle in enumeration
TPWHANDLE tpwGetNextWindow                      // RET   next child or 0
(
   TPWHENUM            henum                    // IN    Enumeration handle
);

// Determine if window is a direct descendant of parent (or parent itself)
BOOL tpwIsChild                                 // RET   window is a child
(
   TPWHANDLE           window,                  // IN    window to test
   TPWHANDLE           parent                   // IN    Parent window handle
);

// Determine if window is a descendant of given parent  (or parent itself)
BOOL tpwIsDescendant                            // RET   window is descendant
(
   TPWHANDLE           hwnd,                    // IN    window to test
   TPWHANDLE           parent                   // IN    Parent window handle
);


// Determine if either this window OR a parent is currently COLLAPSED
BOOL tpwIsCollapsed                             // RET   window is descendant
(
   TPWHANDLE           hwnd,                    // IN    window to test
   BOOL                parent                   // IN    check parents only
);                                               //       or check THIS only

// Determine if a position is within specified rectangle
BOOL tpwInRectangle                             // RET   position in rectangle
(
   short               row,                     // IN    position row
   short               col,                     // IN    position column
   TPRECT             *rect                     // IN    rectangle
);

// Calculate intersection of two rectangles return not-empty
BOOL tpwIntersectRect                           // RET   non-empty intersection
(
   TPRECT             *rec1,                    // IN    rectangle 1
   TPRECT             *rec2,                    // IN    rectangle 2
   TPRECT             *rect                     // OUT   intersection
);

// Determine if first rectangle overlaps second (invalidates its border)
BOOL tpwOverlappingRect                         // RET   overlapping rectangle
(
   TPRECT             *rec1,                    // IN    rectangle 1
   TPRECT             *rec2                     // IN    rectangle 2
);

// Calculate union of two rectangles
void tpwUniteRect
(
   TPRECT             *rec1,                    // IN    rectangle 1
   TPRECT             *rec2,                    // IN    rectangle 2
   TPRECT             *rect                     // OUT   union
);

// Test if rectangle is normalized, and make normalized when requested
BOOL tpwNormalRect                              // RET   input was normalized
(
   BOOL                normalize,               // IN    update rectangle
   TPRECT             *rect                     // INOUT rectangle
);

//               ÚÄÄÄÄÄÄÄÄÄ¿
//         rec1  ³111111111³                 111 is 1st exclusion
//               ³2222 ÚÄÄÄÅÄÄÄÄÄÄ¿          222 is 2nd exclusion
//               ÀÄÄÄÄÄÅÄÄÄÙ      ³ rec2
//                     ÀÄÄÄÄÄÄÄÄÄÄÙ
//
// Calculate 2 exclusion areas for two overlapping rectangles
BOOL tpwExclusionRectangles                     // RET   2nd exclusion valid
(
   TPRECT             *rec1,                    // IN    rectangle 1
   TPRECT             *rec2,                    // IN    rectangle 2
   TPRECT             *xcl1,                    // OUT   exclusion 1
   TPRECT             *xcl2                     // OUT   exclusion 2
);


// Calculate new rectangle, 2nd top-left as move & 2nd bottom-right as size
void tpwMoveSizeRect
(
   TPRECT             *rec1,                    // IN    rectangle 1
   TPRECT             *rec2,                    // IN    rectangle 2 (reference)
   TPRECT             *rect                     // OUT   moved/sized rect 1
);

// Calculate transposition of a rectangle, using top-left of 2nd as reference
void tpwTransposeRect
(
   TPRECT             *rec1,                    // IN    rectangle 1 (relative)
   TPRECT             *rec2,                    // IN    rectangle 2 (reference)
   TPRECT             *rect                     // OUT   transposed rect 1
);

// Calculate clipped sub-string start-position and length
short  tpwCalculateStringClip                   // RET   clipped length
(
   short               row,                     // IN    draw dest row
   short               col,                     // IN    draw dest column
   short               len,                     // IN    draw length
   TPRECT             *clip,                    // IN    clip-rectangle
   short              *offset                   // OUT   clipped offset
);

// Create history-buffer data-structure
BOOL tpwInitializeHistory
(
   TPHIST             *hb,                      // IN    history structure
   USHORT              entries,                 // IN    entries in history
   USHORT              esize                    // IN    max size of entry
);

// Terminate history-buffer data-structure
void tpwTerminateHistory
(
   TPHIST             *hb                       // IN    history structure
);

// Get a history-element string from the buffer, move current position
char  *tpwGetHistory
(
   TPHIST             *hb,                      // IN    history structure
   TPHSELECT           select                   // IN    selection
);

// Put new character-string in the history buffer, at lowest order
void tpwPutHistory
(
   TPHIST             *hb,                      // IN    history structure
   ULONG               order,                   // IN    order (or 0)
   char               *value                    // IN    string value to store
);

// Find a (sub) character-string in the history buffer
char *tpwFindHistory                            // RET   found history string
(
   TPHIST             *hb,                      // IN    history structure
   char               *value,                   // IN    string value to store
   BOOL                use_current              // IN    start from current
);

// Reverse find a (sub) character-string in the history buffer (old to new)
char *tpwRfndHistory                            // RET   found history string
(
   TPHIST             *hb,                      // IN    history structure
   char               *value,                   // IN    string value to match
   BOOL                use_current              // IN    start from current
);

// Sort history-buffer data-structure
void tpwSortHistory
(
   TPHIST             *hb,                      // IN    history structure
   BOOL                ascend                   // IN    sort order wanted
);

/*======== Screen related functions, TPWIOP.C ===============================*/

// Draw a character-string at specified position, clip to optional clip-rect
void tpwScrDrawCharString
(
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   TPRECT             *clip,                    // IN    opt clip-rectangle
   char               *str                      // IN    string to draw
);

// Draw a character-string at position in specified color, using clip-rect
void tpwScrDrawCharStrCol
(
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   TPRECT             *clip,                    // IN    opt clip-rectangle
   char               *str,                     // IN    string to draw
   BYTE                color                    // IN    color attribute
);

// Draw a cell-string at specified position, clip to optional clip-rect
void tpwScrDrawCellString
(
   short               row,                     // IN    destination row
   short               col,                     // IN    destination column
   TPRECT             *clip,                    // IN    opt clip-rectangle
   TPCELL             *cell,                    // IN    cell-string to draw
   short               size                     // IN    nr of cells
);

// Fill area for rectangle with specified cell (clear area)
void tpwScrFillRectangle
(
   TPRECT             *rect,                    // IN    destination rectangle
   TPCELL              cell                     // IN    cell-string to draw
);

// Scroll rectangle up or down, fill new with specified cell
void tpwScrScrollRectangle
(
   TPRECT             *rect,                    // IN    scroll rectangle
   int                 scroll,                  // IN    scroll lines (+ = up)
   TPCELL              cell                     // IN    cell-string to draw
);

#endif
