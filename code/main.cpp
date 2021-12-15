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
    main_data          *io_main_data        /* main data                        */
);

static void main_loop
(
    main_data          *io_main_data        /* main data                        */
);

static void main_close
(
    main_data          *io_main_data        /* main data                        */
);

void init_sim_data
(
    main_data          *io_main_data        /* main data                        */
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
    main_data            main_sim_data;     /* simulation data                  */

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
    main_data          *io_main_data        /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 i;                  /* argument count                   */

    for( i = 0; i < MAX_IMAGES; i++ )
        {
        io_main_data->resources.images[ i ] = NULL;
        }
    io_main_data->resources.image_count = 0;

    for( i = 0; i < MAX_FONTS; i++ )
        {
        io_main_data->resources.fonts[ i ] = NULL;
        }
    io_main_data->resources.font_count = 0;

    io_main_data->sim_data.renderer = NULL;
    io_main_data->sim_data.window = NULL;
    io_main_data->sim_data.running = SIM_STAT_RUNNING;

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
    main_data          *io_main_data        /* main data                        */
)
    {
    /*------------------------------------------------
    Initialize SDL
    - Video Output
    ------------------------------------------------*/
    io_main_data->sim_data.running = ( SDL_Init( SDL_INIT_VIDEO ) == 0 );
    check_or_error( io_main_data->sim_data.running, "SDL Failed to initialize", EH_SDL );

    /*------------------------------------------------
    Initialize PNG Handling
    ------------------------------------------------*/
    int imgFlags = IMG_INIT_PNG;
    io_main_data->sim_data.running = ( IMG_Init( imgFlags ) & imgFlags );
    check_or_error( io_main_data->sim_data.running, "SDL_image could not initialize!", EH_SDL_IMG );
    
    /*------------------------------------------------
    Initialize Font Handling
    ------------------------------------------------*/
    io_main_data->sim_data.running = ( TTF_Init()!=-1 );
    check_or_error( io_main_data->sim_data.running, "SDL_TTF could not initialize!", EH_SDL_TTF );
    
    /*------------------------------------------------
    Create the main window
    ------------------------------------------------*/
    io_main_data->sim_data.window = ( SDL_CreateWindow( i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ) );
    io_main_data->sim_data.running = check_or_error( io_main_data->sim_data.window != NULL, "Could not create window", EH_SDL );

    /*------------------------------------------------
    Create the main renderer
    ------------------------------------------------*/
    io_main_data->sim_data.renderer = SDL_CreateRenderer( io_main_data->sim_data.window, -1, SDL_RENDERER_SOFTWARE );
    io_main_data->sim_data.running = check_or_error( io_main_data->sim_data.renderer != NULL, "Could not create renderer", EH_SDL );

    }    /* main_init */


/*--------------------------------------------------------------------------------

    Name:
        main_loop

    Description:
        Main Loop for code

--------------------------------------------------------------------------------*/

void main_loop
(
    main_data          *io_main_data        /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    SDL_Event           event;              /* SDL event information            */
    Hub                *sel_hub;            /* selected hub pointer             */
        
    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    sel_hub = &io_main_data->hub_info.hubs[ io_main_data->hub_info.selected_hub ];

    /*------------------------------------------------
    Display the test image
    ------------------------------------------------*/
    SDL_RenderCopy( io_main_data->sim_data.renderer, io_main_data->resources.images[ 0 ], NULL, NULL );
    sel_hub->render( &io_main_data->resources, &io_main_data->sim_data );
    SDL_RenderPresent( io_main_data->sim_data.renderer );

    /*------------------------------------------------
    Event Loop
    ------------------------------------------------*/
    while( io_main_data->sim_data.running )
        {
        /*--------------------------------------------
        Update hubs
        --------------------------------------------*/
        sel_hub->update();

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
                io_main_data->sim_data.running = SIM_STAT_END;
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
                SDL_RenderCopy( io_main_data->sim_data.renderer, io_main_data->resources.images[ 0 ], NULL, NULL );

                /*------------------------------------
                Create the sprite retangle
                ------------------------------------*/
                sel_hub->render( &io_main_data->resources, &io_main_data->sim_data );

                /*------------------------------------
                Refresh the screen
                ------------------------------------*/
                SDL_RenderSetClipRect( io_main_data->sim_data.renderer, NULL);    
                SDL_RenderPresent( io_main_data->sim_data.renderer );
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
    main_data           *io_main_data       /* main data                        */
)
    {
    /*------------------------------------------------
    Destroy Renderer
    ------------------------------------------------*/
    SDL_DestroyRenderer( io_main_data->sim_data.renderer );
    io_main_data->sim_data.renderer = NULL;

    /*------------------------------------------------
    Destroy Window
    ------------------------------------------------*/
    SDL_DestroyWindow( io_main_data->sim_data.window );
    io_main_data->sim_data.window = NULL;

    /*------------------------------------------------
    Quit SDL subsystems
    ------------------------------------------------*/
    SDL_Quit();

    }    /* main_close */