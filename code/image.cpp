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

static void load_image
(
    main_data          *io_main_data,       /* main data                        */
    char               *i_image_name        /* name of image to load            */
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
    load_image( io_main_data, (char*)"Background.png" );
    io_main_data->resources.image_count++;
    check_or_error( io_main_data->sim_info.running, "Failed to load background image" );

    }   /* load_all_images() */


/*--------------------------------------------------------------------------------

    Name:
        load_image

    Description:
        Load a specified image

--------------------------------------------------------------------------------*/

static void load_image
(
    main_data          *io_main_data,       /* main data                        */
    char               *i_image_name        /* name of image to load            */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    char               *img_loc;            /* full image path                  */
    char               *img_path;           /* image location                   */
    SDL_Texture       **o_image;            /* created image                    */
    SDL_Surface        *tmp_surface;        /* temporary surface                */
    
    /*------------------------------------------------
    Load the path relative to working directory
    ------------------------------------------------*/
    img_path = (char*)"../images";

    /*------------------------------------------------
    Create the full image path
    ------------------------------------------------*/
    img_loc = (char *)malloc( MAX_STR_LEN );
    snprintf( img_loc, MAX_STR_LEN, "%s/%s/%s", io_main_data->sim_info.root_dir, img_path, i_image_name );

    /*------------------------------------------------
    Load the image
    ------------------------------------------------*/
    tmp_surface = IMG_Load( img_loc );
    io_main_data->sim_info.running = check_or_error( tmp_surface != NULL, "Could not load image", EH_SDL_IMG );

    /*------------------------------------------------
    Convert the image surface to a texture
    ------------------------------------------------*/
    o_image = &io_main_data->resources.images[ io_main_data->resources.image_count ];
    *o_image = SDL_CreateTextureFromSurface( io_main_data->sim_info.renderer, tmp_surface );
    io_main_data->sim_info.running = check_or_error( *o_image != NULL, "Could not convert image to texture", EH_SDL );

    }   /* load_image() */