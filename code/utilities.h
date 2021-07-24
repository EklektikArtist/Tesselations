#pragma once
/*--------------------------------------------------------------------------------

    Name:
        utilities.h

    Description:
        Header for utility operations

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

void debug_info
(
    void
);

bool check_or_error
(
    bool                i_test,             /* condition to test                */
    const char         *i_msg               /* message to print on fail         */
);