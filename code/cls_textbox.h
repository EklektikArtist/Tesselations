#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_textbox.h

    Description:
        Header for textbox class

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
#include "sdl_rect.h"
#include "cls_position.h"
#include "sim.h"
#include "resources.h"


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
    SDL_Rect            textbox;             /* box containing the text         */
    SDL_Color           color;               /* textbox color                   */
    std::string         text;                /* textbox contents                */
    

    /*----------------------------------------------------------------------------

    Name:
        init

    Description:
        Initializes a position object

    ----------------------------------------------------------------------------*/

    public: void init 
    (
    std::string         i_textstr,          /* textbox string                   */
    int                 i_xpos,             /* x position                       */
    int                 i_ypos,             /* y position                       */
    int                 i_width,            /* width                            */
    int                 i_fsize             /* height/font size                 */
    )
        {
        text = i_textstr;
        textbox.x = i_xpos;
        textbox.y = i_ypos;
        textbox.w = i_width;
        textbox.h = i_fsize;
        color = { 255, 255, 255, 0xFF };
        }
    

    /*----------------------------------------------------------------------------

    Name:
        set_pos

    Description:
        Sets the position of the textbox

    ----------------------------------------------------------------------------*/

    public: void set_pos 
    (
    Position           *i_new_pos           /* new position                     */
    )
        {
        textbox.x = i_new_pos->get_x();
        textbox.y = i_new_pos->get_y();
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
        init

    Description:
        Renders the textbox on screen

    ----------------------------------------------------------------------------*/

    public: void render
    (
    resource_data      *i_resource_data,    /* resource data                    */
    sim_data           *io_sim_data         /* simulation data                  */
    )
        {       
        /*--------------------------------------------
        Local Variables
        --------------------------------------------*/
	    SDL_Texture        *gTextOutput;         /* texture to which the textbox     */
	                                             /*  should be rendered              */
	    SDL_Surface        *gTextSurface;		 /* surface on which to render the   */
												 /*  textbox                         */
        gTextSurface = TTF_RenderText_Solid( i_resource_data->fonts[ 0 ], text.c_str(), color );
        check_or_error( gTextSurface != NULL, "Could not render textbox", EH_SDL );

        gTextOutput = SDL_CreateTextureFromSurface( io_sim_data->renderer, gTextSurface );
        check_or_error( gTextOutput != NULL, "Could not render surface to texture", EH_SDL );
        
        /*--------------------------------------------
        Render the texture to the screen 
        --------------------------------------------*/   
        SDL_RenderCopy( io_sim_data->renderer, gTextOutput, NULL, &textbox );

        /*--------------------------------------------
        Free Memory
        --------------------------------------------*/
        SDL_FreeSurface( gTextSurface );
        gTextSurface = NULL;

        SDL_DestroyTexture( gTextOutput );
        gTextOutput = NULL;
        }
};