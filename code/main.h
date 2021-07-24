
#pragma once
/*--------------------------------------------------------------------------------

    Name:
        main.h

    Description:
        Header for root of code functionality

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Compiler Directives
--------------------------------------------------------------------------------*/
#pragma once

/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/
#define WINDOWS true

/*--------------------------------------------------------------------------------
Enums
--------------------------------------------------------------------------------*/
typedef bool sim_stat;
enum
    {
    SIM_STAT_FAIL       = 0,
    SIM_STAT_END        = SIM_STAT_FAIL,
    SIM_STAT_RUNNING    = 1
    };


/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/
int main
(
    int                 argc,                   /* argument count               */
    char               *argv[]                  /* arguments                    */
);