
#include <SDL_image.h>
#include <stdio.h>

#include "image.h"
#include "utilities.h"
#include "main.h"
bool load_all_images
(
    SDL_Renderer** i_renderer,
    SDL_Texture* i_images[],
    int             i_image_count
)
{
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    bool running;
    running = load_image("Background.svg", i_renderer, &i_images[i_image_count]);
    i_image_count++;
    check_or_error(running, "Failed to load background image");

    return(true);
}

bool load_image
(
    char* i_image_name,
    /* name of image to load           */
    SDL_Renderer** i_renderer,
    SDL_Texture** o_image
    /* created image                   */

)
{
#define MAX_STR_SIZE 100
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    bool running = true;
    SDL_Surface* tmp_surface;
    char* img_path;
    char* img_loc;


    if (WINDOWS)
    {
        img_path = "T:/tesselations/images";
    }
    else
    {
        img_path = "../images";
    }
    img_loc = (char*)malloc(MAX_STR_SIZE);
    snprintf(img_loc, MAX_STR_SIZE, "%s/%s", img_path, i_image_name);
    tmp_surface = IMG_Load(img_loc);
    running = check_or_error(tmp_surface != NULL, "Could not load image");

    *o_image = SDL_CreateTextureFromSurface(*i_renderer, tmp_surface);
    running = check_or_error(*o_image != NULL, "Could not convert image to texture");

    return(running);

}