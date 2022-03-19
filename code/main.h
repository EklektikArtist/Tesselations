
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
#include "species.h"
#include "mpi.h"

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
#include "cls_world.h"
#include "cls_population.h"

using namespace NEAT;

/*--------------------------------------------------------------------------------
Constants
--------------------------------------------------------------------------------*/
#define                 WINDOWS             true
#define                 MAX_SCT_HUBS            15
#define                 START_SCT_HUBS            10
#define                 START_SCT_ITEMS           40
//#define                 ROOT_PATH           "T:/tesselations/"
#define               ROOT_PATH           "."

enum types
    {
    TESS_HUB_TYPE,
    TESS_ITM_TYPE
    };

/*--------------------------------------------------------------------------------
Types
--------------------------------------------------------------------------------*/

struct hub_data
    {
    
    //std::vector<Hub>   hubs;               /* vector of hubs for sim            */
    //int                 hub_count;          /* count of hubs in use             */
    //int                 selected_hub;       /* index of currently selected hub  */
    };

struct item_data
    {
    std::vector<Item>   items;              /* vector of items for sim           */
    //int                 item_count;         /* count of items in use            */
    };

struct population_data
    {
    Population         *population;         /* array of brains                  */
    int                 offspring_count;    /* count of brains in use           */
    };

struct statistic_data
    {
    double              max_fit;            /* highest achieved fitness         */
    };

struct local_rank_data
    {
    char                node[MPI_MAX_PROCESSOR_NAME];
    int                 rank;
    };

struct mpi_data
    {    
    int                 world_size;
    int                 root;
    int                 ui;
    local_rank_data     local;
    };

struct main_data
    {
    sim_data            sim_info;           /* simulator data                   */
    Sector              sector_info;
    //World               world;
    //hub_data            hub_info;           /* hub data                         */
    //item_data           item_info;          /* item data                        */
    std::vector<Genome*> 
                        champions;          /* champion list                    */
    resource_data       resources;          /* resource data                    */
    statistic_data      statistics;         /* statitstic records               */
    mpi_data            mpi_info;           /* MPI data                         */
    };

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/
int main
(
    int                 argc,               /* argument count                   */
    char               *argv[]              /* arguments                        */
);