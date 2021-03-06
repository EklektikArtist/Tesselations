#pragma once
/*--------------------------------------------------------------------------------

    Name:
        sim.h

    Description:
        Header for simulaton functionality

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>
#include "cls_position.h"

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
    sim_stat_t8         running;            /* simulation status                */
    Uint32              last_update;        /* last update of sim state         */
    SDL_Renderer       *renderer;           /* primary renderer                 */
    SDL_Window         *window;             /* primary window                   */
    Position            camera;             /* camera                           */
    char               *root_dir;           /* root directory                   */
    };