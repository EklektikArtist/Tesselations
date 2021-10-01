#pragma once
#include "utilities.h"

#define             SCREEN_WIDTH            800
                                            /* initial width of screen          */
#define             SCREEN_HEIGHT           500
                                            /* initial height of screen         */
class Position
    {
    int x;
    int y;
    char buffer[ MAX_STR_LEN ];

    public: int get_x
    (
    void
    )
        {
        return x;
        }

    public: int get_y
    (
    void
    )
        {
        return y;
        }
    public: void init 
    (
    int xp,
    int yp
    )
        {
        x = xp;
        y = yp;
        }

    public: void set_x
    (
    int xp
    )
        {
        if( xp >= SCREEN_WIDTH )
            {
            x = SCREEN_WIDTH;
            }
        else if( xp <= 0 )
            {
            x = 0;
            } 
        else
            {
            x = xp;
            }
        }

    public: void set_y
    (
    int yp
    )
        {
        if( yp >= SCREEN_HEIGHT )
            {
            y = SCREEN_HEIGHT;
            }
        else if( yp <= 0 )
            {
            y = 0;
            }            
        else
            {
            y = yp;
            }
        }

    public: void shift_x
    (
    int x_offset
    )
        {
        set_x( x + x_offset );
        }

    public: void shift_y
    (
    int y_offset
    )
        {
        set_y( y + y_offset );
        }

    public: char * stringify
    (
    void
    )
        {

        sprintf( buffer, "( %d, %d)", x, y );
        return( buffer );
        }
    };