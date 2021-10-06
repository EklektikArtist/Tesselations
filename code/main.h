
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
#include "resources.h"
#include "cls_hub.h"
#include "sim.h"

/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/
#define             WINDOWS                 true
#define             MAX_HUBS                5

/*--------------------------------------------------------------------------------
Types
--------------------------------------------------------------------------------*/

struct hub_data
    {
    Hub                 hubs[ MAX_HUBS ];   /* array of hubs for sim            */
    int                 hub_count;          /* count of hubs in use             */
    int                 selected_hub;       /* index of currently selected hub  */
    };

struct main_data
    {
    sim_data            sim_data;           /* simulator data                   */
    hub_data            hub_info;           /* hub data                         */
    resource_data       resources;          /* resource data                    */
    };

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/
int main
(
    int                 argc,               /* argument count                   */
    char               *argv[]              /* arguments                        */
);