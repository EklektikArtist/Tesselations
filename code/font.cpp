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

static void load_font
(
    main_data          *io_main_data,       /* main data                        */
    char               *i_font_name,        /* name of font to load             */
    int                 i_font_sz          /* font size                        */
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
    load_font( io_main_data, (char*)"Consolas.ttf", 14 );
    io_main_data->resources.font_count++;
    check_or_error( io_main_data->sim_info.running, "Failed to primary font" );

    }   /* load_all_fonts() */


/*--------------------------------------------------------------------------------

    Name:
        load_font

    Description:
        Load a specified font

--------------------------------------------------------------------------------*/

static void load_font
(
    main_data          *io_main_data,       /* main data                        */
    char               *i_font_name,        /* name of font to load             */
    int                 i_font_sz          /* font size                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    char               *font_loc;           /* full font path                   */
    char               *font_path;          /* font location                    */
    TTF_Font          **o_font;             /* created font                     */
    sim_stat_t8         running;            /* simulation status                */
    
    /*------------------------------------------------
    Load the path relative to working directory
    ------------------------------------------------*/
    font_path = (char*)"../fonts";
    
    /*------------------------------------------------
    Create the full font path
    ------------------------------------------------*/
    font_loc = (char *)malloc( MAX_STR_LEN );
    snprintf( font_loc, MAX_STR_LEN, "%s/%s/%s", io_main_data->sim_info.root_dir, font_path, i_font_name );

    /*------------------------------------------------
    Load the font
    ------------------------------------------------*/
    o_font = &io_main_data->resources.fonts[ io_main_data->resources.font_count ];
    *o_font = TTF_OpenFont( font_loc, i_font_sz );
    io_main_data->sim_info.running = check_or_error( *o_font != NULL, "Could not load font", EH_SDL_TTF );

    }   /* load_font() */