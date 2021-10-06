#pragma once
/*--------------------------------------------------------------------------------

    Name:
        resources.h

    Description:
        Header for resource functionality

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

struct resource_data
    {
    SDL_Texture        *images[ MAX_IMAGES ];
                                            /* array of images for sim          */
    int                 image_count;        /* count of images in use           */
    TTF_Font           *fonts[ MAX_FONTS ];
                                            /* array of fonts for sim           */
    int                 font_count;         /* count of fonts in use            */
    };