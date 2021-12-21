#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_item.h

    Description:
        Header for item class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
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
    Circle              sprite;             /* sprite                           */
    

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
        }

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
        render

    Description:
        Renders the item on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    sim_data           *io_sim_data         /* simulation data                  */
    )
        {
        sprite.render( io_sim_data );
        }
};