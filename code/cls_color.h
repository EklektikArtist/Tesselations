#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_color.h

    Description:
        Header for color class

--------------------------------------------------------------------------------*/

/*------------------------------------------------
Project Headers
------------------------------------------------*/


/*--------------------------------------------------------------------------------

    Name:
        Color

    Description:
        Storage for color data

--------------------------------------------------------------------------------*/

class Color
    {

    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
    
    /*----------------------------------------------------------------------------

    Name:
        get_red

    Description:
        Return the color's red hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_red
    (
    void
    )
        {
        return red;
        }
    
    /*----------------------------------------------------------------------------

    Name:
        get_green

    Description:
        Return the color's green hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_green
    (
    void
    )
        {
        return green;
        }
    
    /*----------------------------------------------------------------------------

    Name:
        get_blue

    Description:
        Return the color's blue hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_blue
    (
    void
    )
        {
        return blue;
        }
    
    /*----------------------------------------------------------------------------

    Name:
        get_alpha

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_alpha
    (
    void
    )
        {
        return alpha;
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a color object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    void
    )
        {
        set_color( 0xFF, 0xFF, 0xFF, 0xFF );
        }
          
    
    /*----------------------------------------------------------------------------

    Name:
        set_color

    Description:
        Set the color

    ----------------------------------------------------------------------------*/

    public: void set_color 
    (
    Uint8               i_red,             /* red                               */
    Uint8               i_green,           /* green                             */
    Uint8               i_blue,            /* blue                              */ 
    Uint8               i_alpha            /* alpha                             */
    )
        {
        red = i_red;
        green = i_green;
        blue = i_blue;
        alpha = i_alpha;
        }
    };