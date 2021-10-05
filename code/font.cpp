/*--------------------------------------------------------------------------------

    Name:
        ttf.cpp

    Description:
        Font handling

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>
#include <stdio.h>

/*------------------------------------------------
File Header
------------------------------------------------*/
#include "font.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "utilities.h"
#include "main.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

static bool load_font
(
    char               *i_font_name,        /* name of font to load            */
    int                 i_font_sz,          /* font size                       */
    TTF_Font          **o_font              /* created font                    */
);

/*--------------------------------------------------------------------------------
Procedures
--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------

    Name:
        load_all_fonts

    Description:
        Load all the fonts for the sim

--------------------------------------------------------------------------------*/

void load_all_fonts
(
    main_data           *io_main_data        /* main data                        */
)
    {
    /*------------------------------------------------
    Load the background font
    ------------------------------------------------*/
    io_main_data->sim_data.running = load_font( "Consolas.ttf", 14, &io_main_data->fonts.fonts[ io_main_data->fonts.font_count ] );
    io_main_data->fonts.font_count++;
    check_or_error( io_main_data->sim_data.running, "Failed to primary font" );

    }   /* load_all_fonts() */


/*--------------------------------------------------------------------------------

    Name:
        load_font

    Description:
        Load a specified font

--------------------------------------------------------------------------------*/

static bool load_font
(
    char               *i_font_name,        /* name of font to load             */
    int                 i_font_sz,          /* font size                        */
    TTF_Font          **o_font              /* created font                     */
)
    {
    /*------------------------------------------------
    Local Constants
    ------------------------------------------------*/
    #define MAX_STR_SIZE 100

    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    char               *font_loc;           /* full font path                   */
    char               *font_path;          /* font location                    */
    sim_stat_t8         running;            /* simulation status                */
    
    /*------------------------------------------------
    Load the proper path for the current OS
    ------------------------------------------------*/
    if( WINDOWS )
        {
        font_path = "T:/tesselations/fonts";
        }
    else
        {
        font_path = "../fonts";
        }
    
    /*------------------------------------------------
    Create the full font path
    ------------------------------------------------*/
    font_loc = (char *)malloc( MAX_STR_SIZE );
    snprintf( font_loc, MAX_STR_SIZE, "%s/%s", font_path, i_font_name );

    /*------------------------------------------------
    Load the font
    ------------------------------------------------*/
    *o_font = TTF_OpenFont( font_loc, i_font_sz );
    running = check_or_error( o_font != NULL, "Could not load font", EH_SDL_TTF );

    /*------------------------------------------------
    Return the simulator status
    ------------------------------------------------*/
    return( running );

    }   /* load_font() */