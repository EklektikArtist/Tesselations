#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_hub.h

    Description:
        Header for hub class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "cls_circle.h"
#include "cls_textbox.h"
#include "cls_position.h"
#include "resources.h"
#include "sim.h"


/*--------------------------------------------------------------------------------

    Name:
        Hub

    Description:
        The central node for a tesselation

--------------------------------------------------------------------------------*/

class Hub
    {  

    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/  
    int                 speedx;             /* speed in the x direction         */
    int                 speedy;             /* speed in the y direction         */
    
    Circle              sprite;             /* sprite                           */
    TextBox             text_pos;           /* textbox                          */
    

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
        text_pos.init( sprite.get_pos()->stringify(), sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 100, 12 );
        }

    /*----------------------------------------------------------------------------

    Name:
        update

    Description:
        Syncronizes the hubs information

    ----------------------------------------------------------------------------*/

    public: void update 
    (
    void
    )
        {
        text_pos.set_text( sprite.get_pos()->stringify() );
        text_pos.set_pos( sprite.get_pos() );
        }

    /*----------------------------------------------------------------------------

    Name:
        handle_key

    Description:
        Responds to a keypress

    ----------------------------------------------------------------------------*/
        
    public: void handle_key
    (
    SDL_Keycode         key_press           /* key pressed                      */
    )
        {
        speedx = 0;
        speedy = 0;
        switch( key_press )
            {
            case SDLK_UP:
                speedy = -8;
                break;

            case SDLK_DOWN:
                speedy = 8;        
                break;

            case SDLK_LEFT:
                speedx = -8;
                break;

            case SDLK_RIGHT:
                speedx = 8;
                break;
            }
        
        sprite.get_pos()->shift_x( speedx );
        sprite.get_pos()->shift_y( speedy );
        update();
        }

    /*----------------------------------------------------------------------------

    Name:
        get_sprite

    Description:
        Returns the hub's sprite

    ----------------------------------------------------------------------------*/

    public: Circle get_sprite
    (
    void
    )
        {
        return sprite;
        }

    /*----------------------------------------------------------------------------

    Name:
        render

    Description:
        Renders the hub on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    resource_data      *i_resource_data,    /* resource data                    */
    sim_data           *io_sim_data         /* simulation data                  */
    )
        {
        sprite.render( io_sim_data );
        text_pos.render( i_resource_data, io_sim_data );
        }
};