#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_position.h

    Description:
        Header for Position class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "utilities.h"

/*--------------------------------------------------------------------------------
Local Constants
--------------------------------------------------------------------------------*/
#define             SCREEN_WIDTH            800
                                            /* initial width of screen          */
#define             SCREEN_HEIGHT           500
                                            /* initial height of screen         */
#define             WORLD_WIDTH             500
                                            /* initial width of world           */
#define             WORLD_HEIGHT            1000
                                            /* initial height of world          */

typedef Uint8 sector_shift_t8;
enum
    {
    SECTOR_SHIFT_NONE,
    SECTOR_SHIFT_UP,
    SECTOR_SHIFT_DN
    };


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
    char                buffer[ MAX_STR_LEN ];
                                            /* stringified buffer               */
    int                 s;                  /* sector                           */
    int                 x;                  /* x position                       */
    int                 y;                  /* y position                       */
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

    public: Position
    (
    void
    )
        {
        x = rand() % WORLD_WIDTH;
        y = rand() % WORLD_HEIGHT;

        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

    public: Position
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
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

    public: Position
    (
    const Position        *position
    )
        {
        x = position->get_x();
        y = position->get_y();

        update();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        angle_to

    Description:
        Calculate the angle to another position

    ----------------------------------------------------------------------------*/

    public: float angle_to
    (
    const Position           *pos           /* Second Position                  */
    ) const 
        {
        /*------------------------------------------------
        Local variables
        ------------------------------------------------*/
        float           opp;                /* length of opposite side          */  
        float           adj;                /* length of adjacent side          */
        float           ang;                /* angle between positions          */
        
        /*------------------------------------------------
        Calculate the nagle
        ------------------------------------------------*/
        adj = (float)( x - pos->get_x() );
        opp = (float)( y - pos->get_y() );

        ang = atan( opp / adj );
        
        /*------------------------------------------------
        Return
        ------------------------------------------------*/
        return ang;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        dist_to

    Description:
        Calculate the distance to another position

    ----------------------------------------------------------------------------*/

    public: float dist_to
    (
    const Position     *pos                 /* Second Position                  */
    ) const 
        {
        /*------------------------------------------------
        Local variables
        ------------------------------------------------*/
        float           x_sqr;              /* x difference squared             */  
        float           y_sqr;              /* y difference squared             */
        float           dist;               /* distance between positions       */
        
        /*------------------------------------------------
        Calculate the distance
        ------------------------------------------------*/
        x_sqr = (float)( ( x - pos->get_x() ) ^ 2 );
        y_sqr = (float)( ( y - pos->get_y() ) ^ 2 );

        dist = sqrt( abs( x_sqr - y_sqr ) );
        
        /*------------------------------------------------
        Return
        ------------------------------------------------*/
        return dist;
        }
    

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
        set_pos_buff

    Description:
        Sets the position

    ----------------------------------------------------------------------------*/

    public: sector_shift_t8 set_pos_buff
    (
    int                 i_xp,               /* x position                       */
    int                 i_yp,               /* y position                       */
    int                 i_buff              /* buffer                           */
    )
        {

        sector_shift_t8 ret_val;
        ret_val = SECTOR_SHIFT_NONE;
        ret_val = set_x_buff( i_xp, i_buff );
        set_y_buff( i_yp, i_buff );

        return( ret_val );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_x

    Description:
        Updates the x value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: sector_shift_t8 set_x
    (
    int                 i_xp                /* x position                       */
    )
        {
        sector_shift_t8 ret_val;
        ret_val = SECTOR_SHIFT_NONE;

        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_xp >= WORLD_WIDTH )
            {
            x = 0;
            ret_val = SECTOR_SHIFT_UP;
            }
        else if( i_xp < 0 )
            {
            x = WORLD_WIDTH;
            ret_val = SECTOR_SHIFT_DN;
            } 
        else
            {
            x = i_xp;
            }

        update();

        return( ret_val );
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_x_buff

    Description:
        Updates the x value if the new position is valid

    ----------------------------------------------------------------------------*/

    public: sector_shift_t8 set_x_buff
    (
    int                 i_xp,               /* x position                       */
    int                 i_x_buff            /* x buffer                         */
    )
        {
        sector_shift_t8 ret_val;
        ret_val = SECTOR_SHIFT_NONE;

        /*--------------------------------------------
        If the new position is past the edge of the
        screen, set the position to the closest edge
        --------------------------------------------*/
        if( i_xp >= WORLD_WIDTH - i_x_buff )
            {
            x = 0;
            ret_val = SECTOR_SHIFT_UP;
            }
        else if( i_xp < 0 )
            {
            x = WORLD_WIDTH - i_x_buff;
            ret_val = SECTOR_SHIFT_DN;
            } 
        else
            {
            x = i_xp;
            }

        update();

        return( ret_val );
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
        if( i_yp >= WORLD_HEIGHT )
            {
            y = 0;
            }
        else if( i_yp < 0 )
            {
            y = WORLD_HEIGHT;
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
        if( i_yp >= WORLD_HEIGHT - i_y_buff )
            {
            y = 0;
            }
        else if( i_yp < 0 )
            {
            y = WORLD_HEIGHT - i_y_buff;
            }            
        else
            {
            y = i_yp;
            }

        update();
        }
          

    /*----------------------------------------------------------------------------

    Name:
        shift_pos_buff

    Description:
        Shifts the position by a given amount

    ----------------------------------------------------------------------------*/

    public: sector_shift_t8 shift_pos_buff
    (
    int                 i_x_offset,         /* x offset                         */
    int                 i_y_offset,         /* y offset                         */
    int                 i_buff              /* buffer                           */
    )
        {
        sector_shift_t8 ret_val;
        ret_val = SECTOR_SHIFT_NONE;
        ret_val = set_pos_buff( x + i_x_offset, y + i_y_offset, i_buff );

        return( ret_val );
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
        update

    Description:
        Update the position

    ----------------------------------------------------------------------------*/

    public: void update
    (
    void
    )
        {
        sprintf( buffer, "( %d, %d )", x, y );
        }

    };