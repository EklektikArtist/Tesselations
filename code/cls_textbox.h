#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_textbox.h

    Description:
        Header for textbox class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "resources.h"
#include "SDL_rect.h"
#include "sim.h"

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_position.h"


/*--------------------------------------------------------------------------------

    Name:
        TextBox

    Description:
        An area with text

    Note:
        References from https://gamedev.stackexchange.com/questions/140294/what-is-the-most-efficient-way-to-render-a-textbox-in-c-sdl2

--------------------------------------------------------------------------------*/

class TextBox
    { 
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    SDL_Color           color;               /* textbox color                   */
    std::string         text;                /* textbox contents                */
    SDL_Rect            textbox;             /* box containing the text         */
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

public:TextBox
    (
    )
        {
        color = { 255, 255, 255, 0xFF };
        text = "";
        textbox.x = 0;
        textbox.y = 0;
        textbox.w = 100;
        textbox.h = 12;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

public:TextBox
    (
    std::string         i_textstr,          /* textbox string                   */
    int                 i_xpos,             /* x position                       */
    int                 i_ypos,             /* y position                       */
    int                 i_width,            /* width                            */
    int                 i_fsize             /* height/font size                 */
    )
        {
        color = { 255, 255, 255, 0xFF };
        text = i_textstr;
        textbox.x = i_xpos;
        textbox.y = i_ypos;
        textbox.w = i_width;
        textbox.h = i_fsize;
        }

    /*----------------------------------------------------------------------------

    Name:
        get_text

    Description:
        Returns the text of the textbox

    ----------------------------------------------------------------------------*/        

    public: std::string get_text
    (
    void
    )
        {
        return text;
        }

    /*----------------------------------------------------------------------------

    Name:
        render

    Description:
        Renders the textbox on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    resource_data      *i_resource_data,    /* resource data                    */
    sim_data           *io_sim_data,        /* simulation data                  */
    Position           *camera              /* camera                           */
    )
        {       
        /*--------------------------------------------
        Local Variables
        --------------------------------------------*/
	    SDL_Texture     *gTextOutput;       /* texture to which the textbox     */
	                                        /*  should be rendered              */
	    SDL_Surface     *gTextSurface;		/* surface on which to render the   */
							    			/*  textbox                         */
        
        /*--------------------------------------------
        Create the textbox surface
        --------------------------------------------*/   
        gTextSurface = TTF_RenderText_Solid( i_resource_data->fonts[ 0 ], text.c_str(), color );
        check_or_error( gTextSurface != NULL, "Could not render textbox", EH_SDL );

        gTextOutput = SDL_CreateTextureFromSurface( io_sim_data->renderer, gTextSurface );
        check_or_error( gTextOutput != NULL, "Could not render surface to texture", EH_SDL );
        
        /*--------------------------------------------
        Render the texture to the screen 
        --------------------------------------------*/   
        SDL_Rect pos_on_screen = bbox_shift( camera );
        SDL_RenderCopy( io_sim_data->renderer, gTextOutput, NULL, &pos_on_screen );

        /*--------------------------------------------
        Free Memory
        --------------------------------------------*/
        SDL_FreeSurface( gTextSurface );
        gTextSurface = NULL;

        SDL_DestroyTexture( gTextOutput );
        gTextOutput = NULL;
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Sets the position of the textbox

    ----------------------------------------------------------------------------*/

    public: void set_pos 
    (
    Position const     *i_new_pos           /* new position                     */
    )
        {
        textbox.x = i_new_pos->get_x();
        textbox.y = i_new_pos->get_y();
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_text

    Description:
        Set the text of the textbox

    ----------------------------------------------------------------------------*/
       
    public: void set_text
    (
    std::string         i_new_str           /* new string                       */
    )
        {
        text = i_new_str;
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
             = { textbox.x - shift_pos->get_x(),
                 textbox.y - shift_pos->get_y(),
                 textbox.w,
                 textbox.h };

        return( ret_rect );
        }

};