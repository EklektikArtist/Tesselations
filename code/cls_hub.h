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
#include <math.h>

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
    int                 generation;         /* generation via birth             */
    float               heading;            /* heading                          */
    public :double      health;             /* health                           */
    int                 items_collected;	/* number of items collected        */
    Sint8               speedx;             /* speed in the x direction         */
    Sint8               speedy;             /* speed in the y direction         */
    Circle              sprite;             /* sprite                           */
    TextBox            *text_pos;           /* textbox                          */
    
   /*---------------------------------------------------------------------------

    Description:
        Creates a hub object

    ----------------------------------------------------------------------------*/

public:Hub 
    (
    void
    )
        {
        memset( buffer, 0, sizeof(char) * MAX_STR_LEN );
        drag_ratio = .001f;
        heading = 0;
        health = 1000;
        items_collected = 0;
        sprite.init( 0, 0, 10 );
        generation = 0;
        speedx = 0;
        speedy = 0;
        text_pos = new TextBox( "", sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 250, 15 );

        update();
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
        get_generation

    Description:
        Returns the hub's generation

    ----------------------------------------------------------------------------*/

    public: int get_generation
    (
    void
    )
        {
        return generation;
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
        float           min_dist;           /* minimum distance allowed         */
        Position       *new_pos;            /* new position for hub             */
        float           x_shift;            /* shift in the x direction         */
        float           y_shift;            /* shift in the y direction         */
        
        /*------------------------------------------------
        Apply collision damage
        ------------------------------------------------*/
        damage = ( 50 + ( abs( ( speedx - hub->speedx ) + (speedy - hub->speedy ) ) ) / 10 );
        health -= damage;
        hub->health -= damage;
        
        /*------------------------------------------------
        Calculate separation distance
        Add a buffer to handle rounding errors
        ------------------------------------------------*/
        min_dist = (float)( sprite.get_radius() + hub->get_sprite()->get_radius() );
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
        new_pos = new Position( hub->get_sprite()->get_pos() );
        new_pos->shift_x( (int)( x_shift * 1.1f ) );
        new_pos->shift_y( (int)( y_shift * 1.1f ) );
        sprite.set_pos( new_pos );
        
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
            speedx -= (Sint8)dragx;
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
            speedy -= (Sint8)dragy;
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
                if( speedy > -13 )
                    {
                    speedy -= 5;
                    heading = PI / 2.0f;
                    health -= 1;
                    }
                break;
                
            /*--------------------------------------------
            Handle down arrow press
            --------------------------------------------*/
            case SDLK_DOWN:
                if( speedy < 13 )
                    {
                    speedy += 5;        
                    heading = 3.0f * PI / 2.0f;
                    health -= 1;
                    }
                break;
                
            /*--------------------------------------------
            Handle left arrow press
            --------------------------------------------*/
            case SDLK_LEFT:
                if( speedx > -13 )
                    {
                    speedx -= 5;
                    heading = 0.0f;
                    health -= 1;
                    }
                break;
                
            /*--------------------------------------------
            Handle right arrow press
            --------------------------------------------*/
            case SDLK_RIGHT:
                if( speedx < 13 )
                    {
                    speedx += 5;
                    heading = PI;
                    health -= 1;
                    }
                break;
            }
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
        sprite.shift_pos_buff( ceil( speedx * timestep ), ceil( speedy * timestep ), sprite.get_radius() );
        text_pos->set_pos( sprite.get_pos() );        
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
    sim_data           *io_sim_data,        /* simulation data                  */
    Position           *camera              /* camera                           */
    )
        {
        sprite.render( io_sim_data, camera );
        text_pos->render( i_resource_data, io_sim_data, camera );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_generation

    Description:
        Updates the generation

    ----------------------------------------------------------------------------*/

    public: void set_generation
    (
    int                 i_gen               /* new generation                   */
    )
        {
        generation = i_gen;
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
        snprintf( buffer, MAX_STR_LEN, "Position: %s, Health: %f2", sprite.get_pos()->stringify(), health );
        text_pos->set_text( buffer );
        }
};