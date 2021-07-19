//#define SDL_MAIN_HANDLED 1
//#include <iostream>
//#include <string>
//using namespace std;


#include <SDL.h>
#include <SDL_image.h>


#include "main.h"
#include "utilities.h"
#include "image.h"
#include "utilities.h"


#include "mpi.h"
#include "neat.h"

/*------------------------------------------------
    Name: 
        main

    Description:
        Main Loop for code
------------------------------------------------*/

int main (int argc, char *argv[])
{
/*------------------------------------------------
Local Constants
------------------------------------------------*/
const int MAX_IMAGES = 5;
/*------------------------------------------------
Local Variables
------------------------------------------------*/
SDL_Window* main_window;
SDL_Surface* main_surface;

SDL_Texture* main_images[ MAX_IMAGES ];
SDL_Renderer*    main_renderer;
int          main_image_count;
bool         running;
int         i;

debug_info();
/*------------------------------------------------
Initialization
------------------------------------------------*/
main_window = NULL;
main_renderer = NULL;
for( i = 0; i < MAX_IMAGES; i++ )
    {
    main_images[ i ] = NULL;
    }
main_image_count = 0;
running = true; //create a 'status' enum

/*------------------------------------------------
Initialize Environment
------------------------------------------------*/
running = main_init( "Tesselations", &main_window, &main_renderer, &main_surface);
check_or_error( running, "Initialization Failed" );

/*------------------------------------------------
Load Media
------------------------------------------------*/
running = load_all_images( &main_renderer, main_images, main_image_count );
check_or_error( running, "Failed to get all images" );

/*------------------------------------------------
Run Simulation
------------------------------------------------*/
game_loop( &main_window, &main_renderer, main_images, main_image_count );

/*------------------------------------------------
Clean up Environment
------------------------------------------------*/
main_close( &main_window, &main_renderer );

/*------------------------------------------------
Exit
------------------------------------------------*/
return( 0 );
}

bool main_init
(
    char* i_window_name,
    /* name of window           */
    SDL_Window** o_window,
    /* created window           */
    SDL_Renderer** o_renderer,
    SDL_Surface** o_surface
    /* created surface on window*/

)
{
    /*------------------------------------------------
    Local Constants
    ------------------------------------------------*/
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 500;

    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    bool running;

    running = (SDL_Init(SDL_INIT_VIDEO) == 0);
    check_or_error(running, "SDL Failed to initialize");

    IMG_Init(IMG_INIT_PNG);

    *o_window = (SDL_CreateWindow(i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    running = check_or_error(*o_window != NULL, "Could not create window");

    *o_renderer = SDL_CreateRenderer(*o_window, -1, SDL_RENDERER_SOFTWARE);
    running = check_or_error(*o_renderer != NULL, "Could not create renderer");


    // *o_surface = SDL_GetWindowSurface( *o_window );
    //running = check_or_error( *o_surface != NULL , "Could not create surface" );

    return(running);
}

bool game_loop
    (
    SDL_Window**     io_window,
                    /* main window to be destroyed  */    
    SDL_Renderer** io_renderer,
        /* main surface to be destroyed */
        SDL_Texture*    i_images[],
    int             i_image_count
    )
{
/*------------------------------------------------
Local Variables
------------------------------------------------*/
int running;

/*------------------------------------------------
Initialization
------------------------------------------------*/
//running = 0;

//while( running < 500 )
//    {
SDL_RenderCopy(*io_renderer, i_images[0], NULL, NULL);
SDL_RenderPresent(*io_renderer);

	//Apply the image
//	running = ( SDL_BlitSurface( i_images[0], NULL, *io_surface, NULL ) == 0 );
//	check_or_error( running, "SDL Failed to blit background" );

	//Update the surface
//	running = ( SDL_UpdateWindowSurface( *io_window ) == 0 );
//	check_or_error( running, "SDL Failed to update the surface" );

//    SDL_Delay( 2000 );
//    running++;
//  /   }
bool is_running = true; 
//return( running ); 
SDL_Event event;
 while (is_running) {
    while (SDL_PollEvent(&event)) {
       if (event.type ==   SDL_QUIT) {
            is_running = false; 
        }
    }
    SDL_Delay(16);
}

return( true );

}

bool main_close
(
    SDL_Window** io_window,
    /* main window to be destroyed  */
    SDL_Renderer** io_surface
    /* main surface to be destroyed */

)
{
    //Destroy renderer
    SDL_DestroyRenderer(*io_surface);
    *io_surface = NULL;
    //Destroy window
    SDL_DestroyWindow( *io_window );
    *io_window = NULL;

    //Quit SDL subsystems
    SDL_Quit();

    return(true);
}