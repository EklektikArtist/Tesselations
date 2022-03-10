#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_world.h

    Description:
        Header for world class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_sector.h"

/*--------------------------------------------------------------------------------

    Name:
        World

    Description:
        Storage for world data

--------------------------------------------------------------------------------*/


class World
    {
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    std::vector<Sector>    c_sectors;               /* vector of hubs for sim            */

    
    public: World 
    (
        void
    )
        {

        }

    public: void add_sector
    (
    Sector             *i_sector
    )
        {
        i_sector->set_id( c_sectors.size() );
        c_sectors.push_back( *i_sector );
        for( Sector sec : c_sectors )
            {
            sec.set_world_sector_cnt( c_sectors.size() );
            }
        }
    

    public: Sector* get_sector
    (
    Uint8               i_sector_id
    )
        {
        return( &c_sectors.at( i_sector_id ) );
        }

    };