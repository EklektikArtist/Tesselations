#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_color.h

    Description:
        Header for color class

--------------------------------------------------------------------------------*/

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
    Uint8               red;               /* red                               */
    Uint8               green;             /* green                             */
    Uint8               blue;              /* blue                              */ 
    Uint8               alpha;             /* alpha                             */
    
    public: Color 
    (
        void
    )
        {
        red = 255;
        green = 255;
        blue = 255;
        alpha = 255;
        }
    
    public: Color 
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

   public: void to_array( vector<Uint8>* res_vec ) 
        {
        res_vec->push_back( red );
        res_vec->push_back( green );
        res_vec->push_back( blue );
        res_vec->push_back( alpha );
        }
    };