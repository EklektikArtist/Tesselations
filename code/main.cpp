/*--------------------------------------------------------------------------------

    Name:
        main.cpp

    Description:
        Root of code functionality

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL.h>
#include <SDL_image.h>

#include "mpi.h"        //not in use yet, but leave to make sure complation works
#include "neat.h"       //not in use yet, but leave to make sure complation works

/*------------------------------------------------
File Header
------------------------------------------------*/
#include "main.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "image.h"
#include "utilities.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

static sim_stat main_init
(
    char               *i_window_name,      /* name of window                   */
    SDL_Window        **o_window,           /* created window                   */
    SDL_Renderer      **o_renderer          /* created renderer for window      */
);

static bool main_loop
(
    SDL_Texture        *i_images[],         /* image array to be used           */
    int                 i_image_count,      /* number of available images       */
    SDL_Window        **io_window,          /* main window to be used           */
    SDL_Renderer      **io_renderer         /* main renderer to be used         */
);

static void main_close
(
    SDL_Window        **io_window,          /* main window to be destroyed      */
    SDL_Renderer      **io_renderer         /* main surface to be destroyed     */

);

/*--------------------------------------------------------------------------------
Procedures
--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------

    Name:
        main

    Description:
        Code entry point

--------------------------------------------------------------------------------*/

int main
(
    int                 argc,               /* argument count                   */
    char               *argv[]              /* arguments                        */
)
    {
    /*------------------------------------------------
    Local Constants
    ------------------------------------------------*/
    const int           MAX_IMAGES = 5;

    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 i;                  /* argument count                   */
    SDL_Texture        *main_images[ MAX_IMAGES ];
                                            /* array of images for sim          */
    int                 main_image_count;   /* count of images in use           */
    SDL_Renderer       *main_renderer;      /* primary renderer                 */
    SDL_Window         *main_window;        /* primary window                   */
    sim_stat            running;            /* simulation status                */

    /*------------------------------------------------
    Print out startup status info
    ------------------------------------------------*/
    debug_info();

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    for( i = 0; i < MAX_IMAGES; i++ )
        {
        main_images[ i ] = NULL;
        }
    main_image_count = 0;
    main_renderer = NULL;
    main_window = NULL;
    running = SIM_STAT_RUNNING;

    /*------------------------------------------------
    Initialize Environment
    ------------------------------------------------*/
    running = main_init( "Tesselations", &main_window, &main_renderer );
    check_or_error( running, "Initialization Failed" );

    /*------------------------------------------------
    Load Media
    ------------------------------------------------*/
    running = load_all_images( &main_renderer, main_images, main_image_count );
    check_or_error( running, "Failed to get all images" );

    /*------------------------------------------------
    Run Simulation
    ------------------------------------------------*/
    main_loop( main_images, main_image_count, &main_window, &main_renderer );

    /*------------------------------------------------
    Clean up Environment
    ------------------------------------------------*/
    main_close( &main_window, &main_renderer );

    /*------------------------------------------------
    Exit
    ------------------------------------------------*/
    return( 0 );

    }    /* main */


/*--------------------------------------------------------------------------------

    Name:
        main_init

    Description:
        Primary Initializer

--------------------------------------------------------------------------------*/

sim_stat main_init
(
    char               *i_window_name,      /* name of window                   */
    SDL_Window        **o_window,           /* created window                   */
    SDL_Renderer      **o_renderer          /* created renderer for window      */
)
    {
    /*------------------------------------------------
    Local Constants
    ------------------------------------------------*/
    const int SCREEN_WIDTH  = 800;          /* initial width of screen          */
    const int SCREEN_HEIGHT = 500;          /* initial height of screen         */

    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    sim_stat            running;            /* simulation status                */

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    running = SIM_STAT_RUNNING;

    /*------------------------------------------------
    Initialize SDL
    - Video Output
    ------------------------------------------------*/
    running = ( SDL_Init( SDL_INIT_VIDEO ) == 0 );
    check_or_error( running, "SDL Failed to initialize" );

    /*------------------------------------------------
    Initialize PNG Handling
    ------------------------------------------------*/
    IMG_Init( IMG_INIT_PNG );

    /*------------------------------------------------
    Create the main window
    ------------------------------------------------*/
    *o_window = ( SDL_CreateWindow( i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ) );
    running = check_or_error( *o_window != NULL, "Could not create window" );

    /*------------------------------------------------
    Create the main renderer
    ------------------------------------------------*/
    *o_renderer = SDL_CreateRenderer( *o_window, -1, SDL_RENDERER_SOFTWARE );
    running = check_or_error( *o_renderer != NULL, "Could not create renderer" );

    /*------------------------------------------------
    Return running status
    ------------------------------------------------*/
    return( running );

    }    /* main_init */


/*--------------------------------------------------------------------------------

    Name:
        main_loop

    Description:
        Main Loop for code

--------------------------------------------------------------------------------*/

bool main_loop
(
    SDL_Texture        *i_images[],         /* image array to be used           */
    int                 i_image_count,      /* number of available images       */
    SDL_Window        **io_window,          /* main window to be used           */
    SDL_Renderer      **io_renderer         /* main renderer to be used         */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    SDL_Event           event;              /* SDL event information            */
    sim_stat            running;            /* simulation status                */

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    running = SIM_STAT_RUNNING;

    /*------------------------------------------------
    Display the test image
    ------------------------------------------------*/
    SDL_RenderCopy( *io_renderer, i_images[ 0 ], NULL, NULL );
    SDL_RenderPresent( *io_renderer );

    /*------------------------------------------------
    Event Loop
    ------------------------------------------------*/
    while( running )
        {
        /*--------------------------------------------
        Get latest events
        --------------------------------------------*/
        while( SDL_PollEvent( &event ) )
            {
            /*----------------------------------------
            Handle exit button press
            ----------------------------------------*/
            if( event.type == SDL_QUIT )
                {
                /*------------------------------------
                Flag the loop to end
                ------------------------------------*/
                running = SIM_STAT_END;
                }
            }

        /*--------------------------------------------
        Limit farme rate
        --------------------------------------------*/
        SDL_Delay( 16 );
        }

    return( true );

    }    /* main_loop */


/*--------------------------------------------------------------------------------

    Name:
        main_close

    Description:
        Handle simulation cleanup

--------------------------------------------------------------------------------*/

void main_close
(
    SDL_Window        **io_window,          /* main window to be destroyed      */
    SDL_Renderer      **io_renderer         /* main surface to be destroyed     */

)
    {
    /*------------------------------------------------
    Destroy Renderer
    ------------------------------------------------*/
    SDL_DestroyRenderer( *io_renderer );
    *io_renderer = NULL;

    /*------------------------------------------------
    Destroy Window
    ------------------------------------------------*/
    SDL_DestroyWindow( *io_window );
    *io_window = NULL;

    /*------------------------------------------------
    Quit SDL subsystems
    ------------------------------------------------*/
    SDL_Quit();

    }    /* main_close */