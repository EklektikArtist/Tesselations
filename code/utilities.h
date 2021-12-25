#pragma once
/*--------------------------------------------------------------------------------

    Name:
        utilities.h

    Description:
        Header for utility operations

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Enums
--------------------------------------------------------------------------------*/
typedef int error_handler_t8;
enum
    {
    EH_NONE             = 0,
    EH_SDL,
    EH_SDL_IMG,
    EH_SDL_TTF
    };

/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/
#define                 MAX_STR_LEN         100

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

bool check_or_error
(
    bool                i_test,             /* condition to test                */
    const char         *i_msg               /* message to print on fail         */
);

bool check_or_error
(
    bool                i_test,             /* condition to test                */
    const char         *i_msg,              /* message to print on fail         */
    error_handler_t8    i_eh                /* error handler to use for info    */
);

void debug_info
(
    void
);