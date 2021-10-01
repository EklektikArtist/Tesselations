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
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "mpi.h"        //not in use yet, but leave to make sure compilation works
#include "neat.h"       //not in use yet, but leave to make sure compilation works

/*------------------------------------------------
File Header
------------------------------------------------*/
#include "main.h"

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "font.h"
#include "image.h"
#include "utilities.h"

/*------------------------------------------------
Class Headers
------------------------------------------------*/
#include "cls_textbox.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

static void main_init
(
    char               *i_window_name,      /* name of window                   */
    main_data          *io_sim_data         /* simulation data                  */
);

static void main_loop
(
    main_data          *io_sim_data         /* simulation data                  */
);

static void main_close
(
    main_data          *io_sim_data         /* simulation data                  */
);

void init_sim_data
(
    main_data          *io_sim_data         /* simulation data                  */
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
    Local Variables
    ------------------------------------------------*/
    main_data            main_sim_data;      /* simulation data                  */

    /*------------------------------------------------
    Print out startup status info
    ------------------------------------------------*/
    debug_info();

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    init_sim_data( &main_sim_data );

    /*------------------------------------------------
    Initialize Environment
    ------------------------------------------------*/
    main_init( "Tesselations", &main_sim_data );
    check_or_error( main_sim_data.sim_data.running, "Initialization Failed" );

    /*------------------------------------------------
    Load Images
    ------------------------------------------------*/
    load_all_images( &main_sim_data );
    check_or_error( main_sim_data.sim_data.running, "Failed to get all images" );

    /*------------------------------------------------
    Load Fonts
    ------------------------------------------------*/
    load_all_fonts( &main_sim_data );
    check_or_error( main_sim_data.sim_data.running, "Failed to get all images" );

    main_sim_data.hub_info.hubs[ 0 ].init();
    main_sim_data.hub_info.hub_count = 1;
    main_sim_data.hub_info.selected_hub = 0;
    /*------------------------------------------------
    Run Simulation
    ------------------------------------------------*/
    main_loop( &main_sim_data );

    /*------------------------------------------------
    Clean up Environment
    ------------------------------------------------*/
    main_close( &main_sim_data );

    /*------------------------------------------------
    Exit
    ------------------------------------------------*/
    return( 0 );

    }    /* main */


/*--------------------------------------------------------------------------------

    Name:
        init_sim_data

    Description:
        Primary Initializer

--------------------------------------------------------------------------------*/

void init_sim_data
(
    main_data           *io_sim_data         /* simulation data                  */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 i;                  /* argument count                   */

    for( i = 0; i < MAX_IMAGES; i++ )
        {
        io_sim_data->resources.textures.images[ i ] = NULL;
        }
    io_sim_data->resources.textures.image_count = 0;

    for( i = 0; i < MAX_FONTS; i++ )
        {
        io_sim_data->resources.fonts.fonts[ i ] = NULL;
        }
    io_sim_data->resources.fonts.font_count = 0;

    io_sim_data->sim_data.renderer = NULL;
    io_sim_data->sim_data.window = NULL;
    io_sim_data->sim_data.running = SIM_STAT_RUNNING;

    }    /* init_sim_data */

/*--------------------------------------------------------------------------------

    Name:
        main_init

    Description:
        Primary Initializer

--------------------------------------------------------------------------------*/

void main_init
(
    char               *i_window_name,      /* name of window                   */
    main_data           *io_sim_data         /* simulation data                  */
)
    {
    /*------------------------------------------------
    Initialize SDL
    - Video Output
    ------------------------------------------------*/
    io_sim_data->sim_data.running = ( SDL_Init( SDL_INIT_VIDEO ) == 0 );
    check_or_error( io_sim_data->sim_data.running, "SDL Failed to initialize", EH_SDL );

    /*------------------------------------------------
    Initialize PNG Handling
    ------------------------------------------------*/
    int imgFlags = IMG_INIT_PNG;
    io_sim_data->sim_data.running = ( IMG_Init( imgFlags ) & imgFlags );
    check_or_error( io_sim_data->sim_data.running, "SDL_image could not initialize!", EH_SDL_IMG );
    
    /*------------------------------------------------
    Initialize Font Handling
    ------------------------------------------------*/
    io_sim_data->sim_data.running = ( TTF_Init()!=-1 );
    check_or_error( io_sim_data->sim_data.running, "SDL_TTF could not initialize!", EH_SDL_TTF );
    
    /*------------------------------------------------
    Create the main window
    ------------------------------------------------*/
    io_sim_data->sim_data.window = ( SDL_CreateWindow( i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ) );
    io_sim_data->sim_data.running = check_or_error( io_sim_data->sim_data.window != NULL, "Could not create window", EH_SDL );

    /*------------------------------------------------
    Create the main renderer
    ------------------------------------------------*/
    io_sim_data->sim_data.renderer = SDL_CreateRenderer( io_sim_data->sim_data.window, -1, SDL_RENDERER_SOFTWARE );
    io_sim_data->sim_data.running = check_or_error( io_sim_data->sim_data.renderer != NULL, "Could not create renderer", EH_SDL );

    }    /* main_init */


/*--------------------------------------------------------------------------------

    Name:
        main_loop

    Description:
        Main Loop for code

--------------------------------------------------------------------------------*/

void main_loop
(
    main_data           *io_sim_data         /* simulation data                  */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    SDL_Event           event;              /* SDL event information            */
    Hub *sel_hub = &io_sim_data->hub_info.hubs[ io_sim_data->hub_info.selected_hub ];
    /*------------------------------------------------
    Display the test image
    ------------------------------------------------*/
    SDL_RenderCopy( io_sim_data->sim_data.renderer, io_sim_data->resources.textures.images[ 0 ], NULL, NULL );
    sel_hub->render( &io_sim_data->resources, &io_sim_data->sim_data );
    SDL_RenderPresent( io_sim_data->sim_data.renderer );

    /*------------------------------------------------
    Event Loop
    ------------------------------------------------*/
    while( io_sim_data->sim_data.running )
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
                io_sim_data->sim_data.running = SIM_STAT_END;
                }
            else if( event.type == SDL_KEYDOWN )
                {
                /*------------------------------------
                Forward the key event to the sprite
                ------------------------------------*/
                sel_hub->handle_key( event.key.keysym.sym );
                
                /*------------------------------------
                Clear the screen
                ------------------------------------*/
                SDL_RenderCopy( io_sim_data->sim_data.renderer, io_sim_data->resources.textures.images[ 0 ], NULL, NULL );

                /*------------------------------------
                Create the sprite retangle
                ------------------------------------*/
                sel_hub->render( &io_sim_data->resources, &io_sim_data->sim_data );

                /*------------------------------------
                Refresh the screen
                ------------------------------------*/
                SDL_RenderSetClipRect( io_sim_data->sim_data.renderer, NULL);    
                SDL_RenderPresent( io_sim_data->sim_data.renderer );
                }
            }
            

        /*--------------------------------------------
        Limit farme rate
        --------------------------------------------*/
        SDL_Delay( 16 );
        }

    }    /* main_loop */


/*--------------------------------------------------------------------------------

    Name:
        main_close

    Description:
        Handle simulation cleanup

--------------------------------------------------------------------------------*/

void main_close
(
    main_data           *io_sim_data         /* simulation data                  */
)
    {
    /*------------------------------------------------
    Destroy Renderer
    ------------------------------------------------*/
    SDL_DestroyRenderer( io_sim_data->sim_data.renderer );
    io_sim_data->sim_data.renderer = NULL;

    /*------------------------------------------------
    Destroy Window
    ------------------------------------------------*/
    SDL_DestroyWindow( io_sim_data->sim_data.window );
    io_sim_data->sim_data.window = NULL;

    /*------------------------------------------------
    Quit SDL subsystems
    ------------------------------------------------*/
    SDL_Quit();

    }    /* main_close */