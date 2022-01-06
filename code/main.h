
#pragma once
/*--------------------------------------------------------------------------------

    Name:
        main.h

    Description:
        Header for root of code functionality

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>
#include "population.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "resources.h"
#include "sim.h"

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_hub.h"
#include "cls_item.h"

using namespace NEAT;

/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/
#define                 WINDOWS             true
#define                 MAX_HUBS            10
#define                 MAX_ITEMS           50

/*--------------------------------------------------------------------------------
Types
--------------------------------------------------------------------------------*/

struct hub_data
    {
    Hub                 hubs[ MAX_HUBS ];   /* array of hubs for sim            */
    int                 hub_count;          /* count of hubs in use             */
    int                 selected_hub;       /* index of currently selected hub  */
    };

struct item_data
    {
    Item                items[ MAX_ITEMS ]; /* array of items for sim           */
    int                 item_count;         /* count of items in use            */
    };

struct population_data
    {
    Population         *population;         /* array of brains                  */
    int                 offspring_count;    /* count of brains in use           */
    };

struct main_data
    {
    sim_data            sim_data;           /* simulator data                   */
    hub_data            hub_info;           /* hub data                         */
    item_data           item_info;          /* item data                        */
    resource_data       resources;          /* resource data                    */
    population_data     pop_info;           /* population data                  */
    double              max_fit;            /* highest achieved fitness         */

    };

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/
int main
(
    int                 argc,               /* argument count                   */
    char               *argv[]              /* arguments                        */
);