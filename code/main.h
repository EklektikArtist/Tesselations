#pragma once


#define WINDOWS true

bool main_init
(
	char* i_window_name,
	/* name of window           */
	SDL_Window** o_window,
	/* created window           */
	SDL_Renderer** o_renderer,
	SDL_Surface** o_surface
	/* created surface on window*/

);

bool main_close
(
	SDL_Window** io_window,
	/* main window to be destroyed  */
	SDL_Renderer** io_surface
	/* main surface to be destroyed */

);

bool game_loop
(
	SDL_Window** io_window,
	/* main window to be destroyed  */
	SDL_Renderer** io_renderer,
	/* main surface to be destroyed */
	SDL_Texture* i_images[],
	int             i_image_count
);


int main(
	int argc,
	char* argv[]
);