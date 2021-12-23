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
#include "cls_item.h"
#include "resources.h"
#include "sim.h"

/*------------------------------------------------
Local Constants
------------------------------------------------*/
#define             PX_PER_SEC             650
                                            /* pixels per second                */
#define             PI                     3.1415926536f

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
    Sint8                 speedx;             /* speed in the x direction         */
    Sint8                 speedy;             /* speed in the y direction         */
    Circle              sprite;             /* sprite                           */
    TextBox             text_pos;           /* textbox                          */
    float               heading;            /* heading                          */
    int                 health;
    
   /*--------------------------]]-------------------------------------------------

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
        sprite.init( 0, 0, 25 );
        drag_ratio = .01f;
        text_pos.init( sprite.get_pos()->stringify(), sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 100, 12 );
        speedx = 0;
        speedy = 0;
        health = 100;
        }

    /*----------------------------------------------------------------------------

    Name:
        update

    Description:
        Syncronizes the hubs information

    ----------------------------------------------------------------------------*/

    public: void move
    (
    float timestep
    )
        {
        sprite.shift_pos_buff( speedx * timestep, speedy * timestep, sprite.get_radius() );
        text_pos.set_text( sprite.get_pos()->stringify() );
        text_pos.set_pos( sprite.get_pos() );
        
        handle_drag( timestep );
        }


    /*----------------------------------------------------------------------------

    Name:
        handle_collision

    Description:
        Respond to a collision event

    ----------------------------------------------------------------------------*/

    public: void handle_collision
    (
    Hub                *hub                /* hub collided with                */
    )
        {
        int min_dist;
        float angle;
        Position new_pos;
        int x_shift;
        int y_shift;
        int x_boost;
        int y_boost;
        float heading;
        int damage;

        damage = ( abs( ( speedx - hub->speedx ) + (speedy - hub->speedy ) ) ) / 10;
        health -= damage;
        hub->health -= damage;
        min_dist = sprite.get_radius() + hub->get_sprite()->get_radius();
        min_dist *= 1.1f;
        heading = get_heading();
        angle = sprite.get_pos()->angle_to( hub->get_sprite()->get_pos() );// get_heading();
        if( ( heading - angle > PI / 2 )
         && ( heading - angle < 3.0f * PI / 2.0f) )
            {
            angle -= PI;
            }
        memcpy( &new_pos, hub->get_sprite()->get_pos(), sizeof(Position) );
        x_shift = min_dist * cos( angle );
        y_shift = min_dist * sin( angle );
        new_pos.shift_x( x_shift * 1.1f );
        new_pos.shift_y( y_shift * 1.1f );
        sprite.set_pos( &new_pos );

        hub->speedx = hub->speedx + speedx / 2;
        hub->speedy = hub->speedy + speedy / 2 ;

        speedx = speedx / 2;
        speedy = speedy / 2;

        }


    /*----------------------------------------------------------------------------

    Name:
        handle_collision

    Description:
        Respond to a collision event

    ----------------------------------------------------------------------------*/

    public: void handle_collision
    (
    Item               *item               /* item collided with               */
    )
        {
        health += item->health_affect;
        }


    /*----------------------------------------------------------------------------

    Name:
        handle_drag

    Description:
        Adjust the speed in response to the drag on the hub

    ----------------------------------------------------------------------------*/

    public: void handle_drag
    (
    float               timestep
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

        dragx = ( speedx * drag_ratio * timestep );
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
                heading = PI / 2.0f;
                break;

            case SDLK_DOWN:
                speedy = 50;        
                heading = 3.0f * PI / 2.0f;
                break;

            case SDLK_LEFT:
                speedx = -50;
                heading = 0.0f;
                break;

            case SDLK_RIGHT:
                speedx = 50;
                heading = PI;
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
        get_heading

    Description:
        Returns the hub's heading

    ----------------------------------------------------------------------------*/

    public: float get_heading
    (
    void
    )
        {
        return heading;
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