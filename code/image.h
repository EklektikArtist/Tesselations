bool load_all_images
(
    SDL_Renderer** i_renderer,
    SDL_Texture* i_images[],
    int             i_image_count
);


bool load_image
(
    char* i_image_name,
    /* name of image to load           */
    SDL_Renderer** i_renderer,
    SDL_Texture** o_image
    /* created image                   */

);