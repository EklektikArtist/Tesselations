#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_circle.h

    Description:
        Header for circle class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "cls_position.h"
#include "sim.h"
#include "cls_color.h"


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
    Position            pos;                /* position                         */
    int                 radius;             /* radius                           */
    Color               color;              /* color                            */
    
    /*----------------------------------------------------------------------------

    Name:
        get_pos

    Description:
        Return the circle's position

    ----------------------------------------------------------------------------*/

    public: Position* get_pos 
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
        pos = i_cntr;
        radius = i_rad;
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
        pos.init( i_xp, i_yp );
        radius = i_rad;
        set_color( 0xFF, 0x00, 0x00, 0xFF );
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        render

    Description:
        Renders the circle on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    sim_data           *io_sim_data         /* simulation data                  */
    )
        {
        /*--------------------------------------------
        Local Variables
        --------------------------------------------*/
        SDL_Rect bbox;                      /* box in which to draw the circle  */
        
        /*--------------------------------------------
        Initialization
        --------------------------------------------*/
        bbox = { pos.get_x(), 
                 pos.get_y(),
                 radius,
                 radius };
        
        /*--------------------------------------------
        Set the color
        --------------------------------------------*/
        SDL_SetRenderDrawColor( io_sim_data->renderer, color.get_red(), color.get_green() , color.get_blue() , color.get_alpha() );

        /*--------------------------------------------
        Render the circle to the screen
        --------------------------------------------*/      
        SDL_RenderFillRect( io_sim_data->renderer, &bbox );
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
        }
    };