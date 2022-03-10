#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_circle.h

    Description:
        Header for circle class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "sim.h"

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_color.h"
#include "cls_position.h"


/*--------------------------------------------------------------------------------

    Name:
        Circle

    Description:
        An area with a position and radius

--------------------------------------------------------------------------------*/

class Circle
    {
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    SDL_Rect            bbox;               /* box in which to draw the circle  */
    Color               color;              /* color                            */
    Position            pos;                /* position                         */
    int                 radius;             /* radius                           */
    
    

    public: Circle
    (
    void
    )    
        {
        radius = 10;
        update();
        }

    /*----------------------------------------------------------------------------

    Name:
        get_bbox

    Description:
        Return the circle's bounding box

    ----------------------------------------------------------------------------*/

    public: const SDL_Rect* get_bbox
    (
    void
    )
        {
        return &bbox;
        }
    
    /*----------------------------------------------------------------------------

    Name:
        get_pos

    Description:
        Return the circle's position

    ----------------------------------------------------------------------------*/

    public: const Position* get_pos 
    (
    void
    )
        {
        return &pos;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        get_radius

    Description:
        Return the circle's radius

    ----------------------------------------------------------------------------*/

    public: int get_radius 
    (
    void
    )
        {
        return radius;
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a circle object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    Position            i_cntr,             /* center of circle                 */
    int                 i_rad               /* radius of circle                 */
    )
        {
        init( i_cntr.get_x(), i_cntr.get_y(), i_rad );
        update();
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a circle object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    int                 i_xp,               /* x position of circle             */
    int                 i_yp,               /* y position of circle             */
    int                 i_rad               /* radius of circle                 */
    )
        {
        pos = new Position( i_xp, i_yp );
        radius = i_rad;
        color = *new Color( 0xFF, 0x00, 0x00, 0xFF );
        update();
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        render

    Description:
        Renders the circle on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    sim_data           *io_sim_data,        /* simulation data                  */
    Position           *camera              /* camera                           */
    )
        {        
        /*--------------------------------------------
        Set the color
        --------------------------------------------*/
        SDL_SetRenderDrawColor( io_sim_data->renderer, color.get_red(), color.get_green() , color.get_blue() , color.get_alpha() );

        /*--------------------------------------------
        Render the circle to the screen
        --------------------------------------------*/
        SDL_Rect pos_on_screen = bbox_shift( camera );
        SDL_RenderFillRect( io_sim_data->renderer, &pos_on_screen );
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        set_color

    Description:
        Set the color of the circle

    ----------------------------------------------------------------------------*/

    public: void set_color 
    (
    Uint8               i_red,             /* red                               */
    Uint8               i_green,           /* green                             */
    Uint8               i_blue,            /* blue                              */ 
    Uint8               i_alpha            /* alpha                             */
    )
        {
        color.set_color( i_red, i_green, i_blue, i_alpha );
        update();
        }
          
          
    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Set the color of the circle

    ----------------------------------------------------------------------------*/

    public: void set_pos
    (
    Position           *new_pos             /* position                         */
    )
        {
        pos.set_pos( new_pos );
        update();
        }
          
          
    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Set the color of the circle

    ----------------------------------------------------------------------------*/

    public: void set_pos
    (
    int                 i_xp,               /* x position                       */
    int                 i_yp                /* y position                       */
    )
        {
        pos.set_pos( i_xp, i_yp );
        update();
        }
          
          
    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Set the color of the circle

    ----------------------------------------------------------------------------*/

    public: void shift_pos_buff
    (
    int                 i_x_offset,         /* x offset                         */
    int                 i_y_offset,         /* y offset                         */
    int                 i_buff              /* buffer                           */
    )
        {
        pos.shift_pos_buff( i_x_offset, i_y_offset, i_buff );
        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        get_radius

    Description:
        Return the circle's radius

    ----------------------------------------------------------------------------*/

    public: void update
    (
    void
    )
        {
        bbox = { pos.get_x() - radius,
                 pos.get_y() - radius,
                 radius * 2,
                 radius * 2 };
        }
    

    /*----------------------------------------------------------------------------

    Name:
        get_radius

    Description:
        Return the circle's radius

    ----------------------------------------------------------------------------*/

    public: SDL_Rect bbox_shift
    (
    Position           *shift_pos           /* shift position                   */
    )
        {
        SDL_Rect ret_rect
         = { pos.get_x() - radius - shift_pos->get_x(),
                 pos.get_y() - radius - shift_pos->get_y(),
                 radius * 2,
                 radius * 2 };

        return( ret_rect );
        }
    };