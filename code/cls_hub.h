#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_hub.h

    Description:
        Header for hub class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Headers
------------------------------------------------*/
#include       "SDL_timer.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "cls_circle.h"
#include "cls_textbox.h"
#include "cls_position.h"
#include "resources.h"
#include "sim.h"

/*------------------------------------------------
Local Constants
------------------------------------------------*/
#define             PX_PER_TICK             .1
                                            /* pixels per tick                  */

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
    int                 drag;               /* resistance to speed              */
    int                 speedx;             /* speed in the x direction         */
    int                 speedy;             /* speed in the y direction         */
    Circle              sprite;             /* sprite                           */
    TextBox             text_pos;           /* textbox                          */
    Uint32              last_update;        /* last update time                 */
    

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
        drag = 2;
        text_pos.init( sprite.get_pos()->stringify(), sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 100, 12 );
        last_update = 0;
        speedx = 0;
        speedy = 0;
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
        /*------------------------------------------------
        Local Variables
        ------------------------------------------------*/
        Uint32          this_update;        /* current time                     */

        this_update = SDL_GetTicks();

        sprite.get_pos()->shift_x( speedx * PX_PER_TICK * ( this_update - last_update ) );
        sprite.get_pos()->shift_y( speedy * PX_PER_TICK * ( this_update - last_update ));
        text_pos.set_text( sprite.get_pos()->stringify() );
        text_pos.set_pos( sprite.get_pos() );
        
        handle_drag();

        last_update = this_update;
        }

    /*----------------------------------------------------------------------------

    Name:
        handle_drag

    Description:
        Adjust the speed in response to the drag on the hub

    ----------------------------------------------------------------------------*/

    public: void handle_drag
    (
    void
    )
        {
        /*------------------------------------------------
        Return early if the hub is stationary
        ------------------------------------------------*/
        if( ( speedx == 0 )
         && ( speedy == 0 ) )
            {
            return;
            }

        /*------------------------------------------------
        Adjust the x speed
        ------------------------------------------------*/
        if( speedx > 0 )
            {
            if (speedx - drag >= 0 )
                {
                speedx -= drag;
                }
            else
                {
                speedx = 0;
                }
            }
        else if( speedx < 0 )
            {
            if (speedx + drag <= 0 )
                {
                speedx += drag;
                }
            else
                {
                speedx = 0;
                }
            }
        
        /*------------------------------------------------
        Adjust the y speed
        ------------------------------------------------*/
        if( speedy > 0 )
            {
            if (speedy - drag >= 0 )
                {
                speedy -= drag;
                }
            else
                {
                speedy = 0;
                }
            }
        else if( speedy < 0 )
            {
            if (speedy + drag <= 0 )
                {
                speedy += drag;
                }
            else
                {
                speedy = 0;
                }
            }
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
        switch( key_press )
            {
            case SDLK_UP:
                speedy = -100;
                break;

            case SDLK_DOWN:
                speedy = 100;        
                break;

            case SDLK_LEFT:
                speedx = -100;
                break;

            case SDLK_RIGHT:
                speedx = 100;
                break;
            }
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