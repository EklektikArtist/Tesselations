#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_position.h

    Description:
        Header for Position class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "utilities.h"

/*------------------------------------------------
Local Constants
------------------------------------------------*/
#define             SCREEN_WIDTH            800
                                            /* initial width of screen          */
#define             SCREEN_HEIGHT           500
                                            /* initial height of screen         */


/*--------------------------------------------------------------------------------

    Name:
        Position

    Description:
        A 2 dimensional description of position.  
        
    Note:
        (0, 0) is the top right of the screen

--------------------------------------------------------------------------------*/

class Position
    {
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    int                 x;                  /* x position                       */
    int                 y;                  /* y position                       */
    char                buffer[ MAX_STR_LEN ];
                                            /* stringified buffer               */
    

    /*----------------------------------------------------------------------------

    Name:
        get_x

    Description:
        Return the position's x coordinate

    ----------------------------------------------------------------------------*/

    public: int get_x
    (
    void
    ) const
        {
        return x;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        get_y

    Description:
        Return the position's y coordinate

    ----------------------------------------------------------------------------*/

    public: int get_y
    (
    void
    ) const
        {
        return y;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    int                 i_xp,               /* x position                       */
    int                 i_yp                /* y position                       */
    )
        {
        x = i_xp;
        y = i_yp;

        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_x

    Description:
        Updates the x value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_x
    (
    int                 i_xp                /* x position                       */
    )
        {
        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_xp >= SCREEN_WIDTH )
            {
            x = SCREEN_WIDTH;
            }
        else if( i_xp <= 0 )
            {
            x = 0;
            } 
        else
            {
            x = i_xp;
            }

        update();

        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Updates the position if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_pos
    (
    int                 i_xp,               /* x position                       */
    int                 i_yp                /* y position                       */
    )
        {
        set_x( i_xp );
        set_y( i_yp );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Updates the position if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_pos
    (
    Position           *pos                 /* position                         */
    )
        {
        set_x( pos->get_x() );
        set_y( pos->get_y() );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_x_buff

    Description:
        Updates the x value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_x_buff
    (
    int                 i_xp,               /* x position                       */
    int                 i_x_buff            /* x buffer                         */
    )
        {
        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_xp >= SCREEN_WIDTH - i_x_buff)
            {
            x = SCREEN_WIDTH - i_x_buff;
            }
        else if( i_xp <= 0 )
            {
            x = 0;
            } 
        else
            {
            x = i_xp;
            }

        update();

        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_y

    Description:
        Updates the y value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_y
    (
    int                 i_yp                /* y position                       */
    )
        {
        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_yp >= SCREEN_HEIGHT )
            {
            y = SCREEN_HEIGHT;
            }
        else if( i_yp <= 0 )
            {
            y = 0;
            }            
        else
            {
            y = i_yp;
            }

        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_y_buff

    Description:
        Updates the y value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: void set_y_buff
    (
    int                 i_yp,               /* y position                       */
    int                 i_y_buff            /* y buffer                         */
    )
        {
        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_yp >= SCREEN_HEIGHT - i_y_buff )
            {
            y = SCREEN_HEIGHT - i_y_buff;
            }
        else if( i_yp <= 0 )
            {
            y = 0;
            }            
        else
            {
            y = i_yp;
            }

        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        shift_x

    Description:
        Shifts the x value by a given amount

    ----------------------------------------------------------------------------*/

    public: void shift_x
    (
    int                 i_x_offset          /* x offset                         */
    )
        {
        set_x( x + i_x_offset );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_pos_buff

    Description:
        Sets the position

    ----------------------------------------------------------------------------*/

    public: void set_pos_buff
    (
    int                 i_xp,               /* x position                       */
    int                 i_yp,               /* y position                       */
    int                 i_buff              /* buffer                           */
    )
        {
        set_x_buff( i_xp, i_buff );
        set_y_buff( i_yp, i_buff );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        shift_x_buff

    Description:
        Shifts the x value by a given amount

    ----------------------------------------------------------------------------*/

    public: void shift_x_buff
    (
    int                 i_x_offset,         /* x offset                         */
    int                 i_x_buff            /* x buffer                         */
    )
        {
        set_x_buff( x + i_x_offset, i_x_buff );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        shift_pos_buff

    Description:
        Shifts the position by a given amount

    ----------------------------------------------------------------------------*/

    public: void shift_pos_buff
    (
    int                 i_x_offset,         /* x offset                         */
    int                 i_y_offset,         /* y offset                         */
    int                 i_buff              /* buffer                           */
    )
        {
        set_pos_buff( x + i_x_offset, y + i_y_offset, i_buff );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        shift_y

    Description:
        Shifts the x value by a given amount

    ----------------------------------------------------------------------------*/

    public: void shift_y
    (
    int                 i_y_offset          /* y offset                         */
    )
        {
        set_y( y + i_y_offset );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        shift_y_buf

    Description:
        Shifts the y value by a given amount

    ----------------------------------------------------------------------------*/

    public: void shift_y_buff
    (
    int                 i_y_offset,         /* y offset                         */
    int                 i_y_buff            /* y buffer                         */
    )
        {
        set_y_buff( y + i_y_offset, i_y_buff );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        stringify

    Description:
        Return the position as a formatted string

    ----------------------------------------------------------------------------*/

    public: const char * stringify
    (
    void
    ) const
        {
        return( buffer );
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
        sprintf( buffer, "( %d, %d )", x, y );
        }
    };