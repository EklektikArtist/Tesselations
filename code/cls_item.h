#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_item.h

    Description:
        Header for item class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <stdlib.h>

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_circle.h"

/*--------------------------------------------------------------------------------

    Name:
        Item

    Description:
        An object which affets a tesselation

--------------------------------------------------------------------------------*/

class Item
    {
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/  
    public:int          health_affect;      /* item's health affect             */
    Circle              sprite;             /* sprite                           */


    /*----------------------------------------------------------------------------

    Name:
        get_sprite

    Description:
        Returns the hub's sprite

    ----------------------------------------------------------------------------*/

    public: Circle* get_sprite
    (
    void
    )
        {
        return &sprite;
        }


    /*----------------------------------------------------------------------------

    Name:
        handle_collision

    Description:
        Respond to a collision event

    ----------------------------------------------------------------------------*/

    public: void handle_collision
    (
    void
    )
        {
        sprite.set_pos( rand() % WORLD_WIDTH, rand() % WORLD_HEIGHT );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a hub object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    void
    )
        {
        sprite.init( 0, 0, 5 );
        sprite.set_color( 0xFF, 0xFF, 0x00, 0xFF );
        health_affect = 100;
        }


    /*----------------------------------------------------------------------------

    Name:
        render

    Description:
        Renders the item on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    sim_data           *io_sim_data,        /* simulation data                  */
    Position           *camera              /* camera                           */
    )
        {
        sprite.render( io_sim_data, camera );
        }

};