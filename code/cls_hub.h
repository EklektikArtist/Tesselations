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
#define             PX_PER_SEC             650
                                            /* pixels per second                */

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
    float               drag_ratio;         /* resistance to speed              */
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
        sprite.init( 0, 0, 50 );
        drag_ratio = .01f;
        text_pos.init( sprite.get_pos()->stringify(), sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 100, 12 );
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
    float timestep
    )
        {
        sprite.get_pos()->shift_x_buff( speedx * timestep, sprite.get_radius() );
        sprite.get_pos()->shift_y_buff( speedy * timestep, sprite.get_radius() );
        text_pos.set_text( sprite.get_pos()->stringify() );
        text_pos.set_pos( sprite.get_pos() );
        
        handle_drag( timestep);
        }

    /*----------------------------------------------------------------------------

    Name:
        handle_drag

    Description:
        Adjust the speed in response to the drag on the hub

    ----------------------------------------------------------------------------*/

    public: void handle_drag
    (
        float timestep
    )
        {
        float dragx;
        float dragy;

        /*------------------------------------------------
        Return early if the hub is stationary
        ------------------------------------------------*/
        if( ( speedx == 0 )
         && ( speedy == 0 ) )
            {
            return;
            }

        dragx = (speedx * drag_ratio * timestep );
        dragy = ( speedy * drag_ratio * timestep );

        /*------------------------------------------------
        Adjust the x speed
        ------------------------------------------------*/
        if ( abs(speedx - dragx ) >= 0 )
            {
            speedx -= dragx;
            }
        else
            {
            speedx = 0;
            }
        
        /*------------------------------------------------
        Adjust the y speed
        ------------------------------------------------*/
        if ( abs(speedy - dragy ) >= 0 )
            {
            speedy -= dragy;
            }
        else
            {
            speedy = 0;
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
                speedy = -50;
                break;

            case SDLK_DOWN:
                speedy = 50;        
                break;

            case SDLK_LEFT:
                speedx = -50;
                break;

            case SDLK_RIGHT:
                speedx = 50;
                break;
            }
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