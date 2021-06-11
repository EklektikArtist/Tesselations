#include <stdio.h>
#include <SDL2/SDL.h>



/*------------------------------------------------
Main Prototypes
------------------------------------------------*/
bool main_init
    (
    char*           i_window_name,
                    /* name of window           */
    SDL_Window*     o_window,
                    /* created window           */
    SDL_Surface*    o_surface,
                    /* created surface on window*/
    );

bool main_close
    (
    void
    );

bool load_all_images
    (
    void
    );

void game_loop
    (
    void
    );

/*------------------------------------------------
Media Prototypes
------------------------------------------------*/
bool load_image
    (
    void
    );

/*------------------------------------------------
Code Flow Prototypes
------------------------------------------------*/
bool check_or_error( 
    boolean     test,   /* test to check            */
    char*       msg1,   /* message if test fails 1  */
    char*       msg2    /* message if test fails 2  */
    );


/*------------------------------------------------
    Name: 
        main

    Description:
        Main Loop for code
------------------------------------------------*/

int main( 
    char*       i_window_name,
                    /* name of window           */
    SDL_Window* o_window,
                    /* created window           */
    SDL_Surface* o_surface,
                    /* created surface on window*/
    )
{
/*------------------------------------------------
Local Variables
------------------------------------------------*/
SDL_Window* main_window;
SDL_Surface* main_surface;

/*------------------------------------------------
Initialization
------------------------------------------------*/
main_window = NULL;
main_surface = NULL;
running = true; //create a 'status' enum

/*------------------------------------------------
Initialize Environment
------------------------------------------------*/
running = main_init( &main_window, &main_surface );
check_or_error( running, "Initialization Failed" );

/*------------------------------------------------
Load Media
------------------------------------------------*/
running = load_all_images();
check_or_error( running, "Failed to get all images" );

/*------------------------------------------------
Run Simulation
------------------------------------------------*/
game_loop();

/*------------------------------------------------
Clean up Environment
------------------------------------------------*/
main_close();

/*------------------------------------------------
Exit
------------------------------------------------*/
return( 0 );
}

bool main_init
    (
    char*   i_window_name,
                    /* name of window           */
    SDL_Window* o_window,
                    /* created window           */
    SDL_Surface* o_surface,
                    /* created surface on window*/
    )
{
/*------------------------------------------------
Local Variables
------------------------------------------------*/
bool running;

running = ( SDL_Init( SDL_INIT_VIDEO ) < 0 );
check_or_error( running, "SDL Failed to initialize.  SDL_Error:" );

o_window = ( SDL_CreateWindow( i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ) );
running = check_or_error( o_window != NULL , "Could not create window" );

o_surface = SDL_GetWindowSurface( o_window );
running = check_or_error( o_surface != NULL , "Could not create window" );



}

bool load_all_images
    (
    void
    )

{
/*------------------------------------------------
Local Variables
------------------------------------------------*/
bool running;
running = load_image( "Background.png");
check_or_error( running, "Failed to load background image" );

}