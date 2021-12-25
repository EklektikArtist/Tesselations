#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_hub.h

    Description:
        Header for hub class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Headers
------------------------------------------------*/
#include "SDL_timer.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "resources.h"
#include "sim.h"

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_circle.h"
#include "cls_item.h"
#include "cls_position.h"
#include "cls_textbox.h"

/*--------------------------------------------------------------------------------
Local Constants
--------------------------------------------------------------------------------*/
#define                 PX_PER_SEC          650
                                            /* pixels per second                */
#define                 PI                  3.1415926536f
                                            /* pi                               */


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
    char                buffer[ MAX_STR_LEN ];
                                            /* stringified buffer               */
    float               drag_ratio;         /* resistance to speed              */
    float               heading;            /* heading                          */
    public :int         health;             /* health                           */
    Sint8               speedx;             /* speed in the x direction         */
    Sint8               speedy;             /* speed in the y direction         */
    Circle              sprite;             /* sprite                           */
    TextBox             text_pos;           /* textbox                          */

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
        Respond to a collision event with another hub

    ----------------------------------------------------------------------------*/

    public: void handle_collision
    (
    Hub                *hub                /* hub collided with                */
    )
        {
        /*------------------------------------------------
        Local variables
        ------------------------------------------------*/
        float           angle;              /* angle between hubs               */
        int             damage;             /* damage caused by collision       */
        float           heading;            /* heading of current hub           */
        int             min_dist;           /* minimum distance allowed         */
        Position        new_pos;            /* new position for hub             */
        int             x_boost;            /* boost in the x direction         */
        int             x_shift;            /* shift in the x direction         */
        int             y_boost;            /* boost in the y direction         */
        int             y_shift;            /* shift in the y direction         */
        
        /*------------------------------------------------
        Apply collision damage
        ------------------------------------------------*/
        damage = ( abs( ( speedx - hub->speedx ) + (speedy - hub->speedy ) ) ) / 10;
        health -= damage;
        hub->health -= damage;
        
        /*------------------------------------------------
        Calculate separation distance
        Add a buffer to handle rounding errors
        ------------------------------------------------*/
        min_dist = sprite.get_radius() + hub->get_sprite()->get_radius();
        min_dist *= 1.1f;
        
        /*------------------------------------------------
        Calculate direction of repulsion
        ------------------------------------------------*/
        heading = get_heading();
        angle = sprite.get_pos()->angle_to( hub->get_sprite()->get_pos() );
        if( ( heading - angle > PI / 2.0f )
         && ( heading - angle < 3.0f * PI / 2.0f ) )
            {
            angle -= PI;
            }
        
        /*------------------------------------------------
        Shift this hub by the proper distance in the
        proper direction.

        Note: The current code moves the hub with the
        smallest index, improvement would move both hubs
        half way
        ------------------------------------------------*/
        x_shift = min_dist * cos( angle );
        y_shift = min_dist * sin( angle );
        memcpy( &new_pos, hub->get_sprite()->get_pos(), sizeof(Position) );
        new_pos.shift_x( x_shift * 1.1f );
        new_pos.shift_y( y_shift * 1.1f );
        sprite.set_pos( &new_pos );
        
        /*------------------------------------------------
        Update the speeds of the two hubs
        ------------------------------------------------*/
        hub->speedx = hub->speedx + speedx / 2;
        hub->speedy = hub->speedy + speedy / 2 ;

        speedx = speedx / 2;
        speedy = speedy / 2;
        
        /*------------------------------------------------
        Update dependent data
        ------------------------------------------------*/
        update();

        }


    /*----------------------------------------------------------------------------

    Name:
        handle_collision

    Description:
        Respond to a collision event with an item

    ----------------------------------------------------------------------------*/

    public: void handle_collision
    (
    Item               *item               /* item collided with               */
    )
        {
        health += item->health_affect;
        update();
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
        /*------------------------------------------------
        Local variables
        ------------------------------------------------*/
        float           dragx;              /* drag in the x direction          */   
        float           dragy;              /* drag in the y direction          */

        /*------------------------------------------------
        Return early if the hub is stationary
        ------------------------------------------------*/
        if( ( speedx == 0 )
         && ( speedy == 0 ) )
            {
            return;
            }
        
        /*------------------------------------------------
        Set the drag effects
        ------------------------------------------------*/
        dragx = ( speedx * drag_ratio * timestep );
        dragy = ( speedy * drag_ratio * timestep );

        /*------------------------------------------------
        Adjust the x speed
        ------------------------------------------------*/
        if ( abs( speedx - dragx ) >= 0 )
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
        if ( abs( speedy - dragy ) >= 0 )
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
            /*--------------------------------------------
            Handle up arrow press
            --------------------------------------------*/
            case SDLK_UP:
                speedy = -50;
                heading = PI / 2.0f;
                break;
                
            /*--------------------------------------------
            Handle down arrow press
            --------------------------------------------*/
            case SDLK_DOWN:
                speedy = 50;        
                heading = 3.0f * PI / 2.0f;
                break;
                
            /*--------------------------------------------
            Handle left arrow press
            --------------------------------------------*/
            case SDLK_LEFT:
                speedx = -50;
                heading = 0.0f;
                break;
                
            /*--------------------------------------------
            Handle right arrow press
            --------------------------------------------*/
            case SDLK_RIGHT:
                speedx = 50;
                heading = PI;
                break;
            }
        }
    
   /*---------------------------------------------------------------------------

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
        text_pos.init( "", sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 250, 15 );
        speedx = 0;
        speedy = 0;
        health = 100;

        update();
        }

    /*----------------------------------------------------------------------------

    Name:
        update

    Description:
        Move the hub and update the information

    ----------------------------------------------------------------------------*/

    public: void move
    (
    float timestep
    )
        {
        sprite.shift_pos_buff( speedx * timestep, speedy * timestep, sprite.get_radius() );
        text_pos.set_pos( sprite.get_pos() );        
        handle_drag( timestep );

        update();
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
    

    /*----------------------------------------------------------------------------

    Name:
        update

    Description:
        Update the position

    ----------------------------------------------------------------------------*/

    public: void update
    (
    void
    )
        {
        snprintf( buffer, MAX_STR_LEN, "Position: %s, Health: %d", sprite.get_pos()->stringify(), health );
        text_pos.set_text( buffer );
        }
};