#pragma once
/*--------------------------------------------------------------------------------

    Name:
        main.h

    Description:
        Header for root of code functionality

--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>

/*------------------------------------------------
Project Headers
------------------------------------------------*/


/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Enums
--------------------------------------------------------------------------------*/
typedef int sim_stat_t8;
enum
    {
    SIM_STAT_FAIL       = 0,
    SIM_STAT_END        = SIM_STAT_FAIL,
    SIM_STAT_RUNNING    = 1
    };

/*--------------------------------------------------------------------------------
Types
--------------------------------------------------------------------------------*/

struct sim_data
    {
    SDL_Renderer       *renderer;           /* primary renderer                 */
    SDL_Window         *window;             /* primary window                   */
    sim_stat_t8         running;            /* simulation status                */
    };