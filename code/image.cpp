/*--------------------------------------------------------------------------------

    Name:
        image.cpp

    Description:
        Image handling

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_image.h>
#include <stdio.h>

/*------------------------------------------------
File Header
------------------------------------------------*/
#include "image.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "utilities.h"
#include "main.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

static bool load_image
(
    char               *i_image_name,       /* name of image to load            */
    SDL_Renderer       *i_renderer,         /* image renderer                   */
    SDL_Texture       **o_image             /* created image                    */
);

/*--------------------------------------------------------------------------------
Procedures
--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------

    Name:
        load_all_images

    Description:
        Load all the images for the sim

--------------------------------------------------------------------------------*/

void load_all_images
(
    main_data           *io_main_data       /* main data                        */
)
    {
    /*------------------------------------------------
    Load the background image
    ------------------------------------------------*/
    io_main_data->sim_data.running = load_image( "Background.png", io_main_data->sim_data.renderer, &io_main_data->resources.images[ io_main_data->resources.image_count ] );
    io_main_data->resources.image_count++;
    check_or_error( io_main_data->sim_data.running, "Failed to load background image" );

    }   /* load_all_images() */


/*--------------------------------------------------------------------------------

    Name:
        load_image

    Description:
        Load a specified image

--------------------------------------------------------------------------------*/

static bool load_image
(
    char               *i_image_name,       /* name of image to load            */
    SDL_Renderer       *i_renderer,         /* image renderer                   */
    SDL_Texture       **o_image             /* created image                    */
)
    {
    /*------------------------------------------------
    Local Constants
    ------------------------------------------------*/
    #define MAX_STR_SIZE 100

    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    char               *img_loc;            /* full image path                  */
    char               *img_path;           /* image location                   */
    sim_stat_t8         running;            /* simulation status                */
    SDL_Surface        *tmp_surface;        /* temporary surface                */

    /*------------------------------------------------
    Load the proper path for the current OS
    ------------------------------------------------*/
    if( WINDOWS )
        {
        img_path = "C:/Users/infof/Documents/Git/Tesselations/images";
        }
    else
        {
        img_path = "../images";
        }

    /*------------------------------------------------
    Create the full image path
    ------------------------------------------------*/
    img_loc = (char *)malloc( MAX_STR_SIZE );
    snprintf( img_loc, MAX_STR_SIZE, "%s/%s", img_path, i_image_name );

    /*------------------------------------------------
    Load the image
    ------------------------------------------------*/
    tmp_surface = IMG_Load( img_loc );
    running = check_or_error( tmp_surface != NULL, "Could not load image", EH_SDL_IMG );

    /*------------------------------------------------
    Convert the image surface to a texture
    ------------------------------------------------*/
    *o_image = SDL_CreateTextureFromSurface( i_renderer, tmp_surface );
    running = check_or_error( *o_image != NULL, "Could not convert image to texture", EH_SDL );

    /*------------------------------------------------
    Return the simulator status
    ------------------------------------------------*/
    return( running );

    }   /* load_image() */