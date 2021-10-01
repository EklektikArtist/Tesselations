#pragma once
/*--------------------------------------------------------------------------------

    Name:
        main.h

    Description:
        Header for root of code functionality

--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>

/*------------------------------------------------
Project Headers
------------------------------------------------*/

#define             MAX_IMAGES              5
#define             MAX_FONTS               5

/*--------------------------------------------------------------------------------
Types
--------------------------------------------------------------------------------*/

struct texture_data
    {
    SDL_Texture        *images[ MAX_IMAGES ];
                                            /* array of images for sim          */
    int                 image_count;        /* count of images in use           */
    };

struct font_data
    {
    TTF_Font           *fonts[ MAX_FONTS ];
                                            /* array of fonts for sim           */
    int                 font_count;         /* count of fonts in use            */
    };

struct resource_data
    {
    texture_data textures;
    font_data fonts;
    };