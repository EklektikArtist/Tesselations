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

    /*------------------------------------------------
    Set up hubs
    ------------------------------------------------*/
    main_sim_data.hub_info.hubs[ 0 ].init();
    main_sim_data.hub_info.hubs[ 0 ].get_sprite()->set_pos( 100, 0 );
    main_sim_data.hub_info.hubs[ 1 ].init();
    main_sim_data.hub_info.hubs[ 1 ].get_sprite()->set_color( 0x00, 0xFF, 0x00, 0xFF );
    main_sim_data.hub_info.hubs[ 1 ].get_sprite()->set_pos( 100, 100 );

    main_sim_data.hub_info.hub_count = 2;
    main_sim_data.hub_info.selected_hub = 0;

    /*------------------------------------------------
    Set up items
    ------------------------------------------------*/
    main_sim_data.item_info.items[ 0 ].init();
    main_sim_data.item_info.items[ 0 ].get_sprite()->set_pos( 200, 200 );

    main_sim_data.item_info.item_count = 1;

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
    io_main_data->sim_data.last_update = 0;

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
    float               time_step;          /* seconds since last update        */
    Uint32              this_update;        /* current time                     */
    Uint8               i;                  /* loop counter                     */
    bool                collision;          /* collision detected?              */
    Uint8               j;                  /* loop counter                     */
    bool                skip;
    int                 visited_hubs_count;
    int                 visited_hubs[ MAX_HUBS ];
        
    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    visited_hubs_count = 0;
    sel_hub = &io_main_data->hub_info.hubs[ io_main_data->hub_info.selected_hub ];

    /*------------------------------------------------
    Update timer
    ------------------------------------------------*/
    this_update = SDL_GetTicks();
    time_step = ( this_update - io_main_data->sim_data.last_update ) / 1000.0f;
    io_main_data->sim_data.last_update = this_update;

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
        Clear the screen
        --------------------------------------------*/
        SDL_RenderCopy(io_main_data->sim_data.renderer, io_main_data->resources.images[ 0 ], NULL, NULL);

        /*--------------------------------------------
        Update hubs
        --------------------------------------------*/
        for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
            {
            io_main_data->hub_info.hubs[ i ].move( time_step );
            io_main_data->hub_info.hubs[ i ].render( &io_main_data->resources, &io_main_data->sim_data );
            }

        /*--------------------------------------------
        Update items
        --------------------------------------------*/
        for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
            {
            io_main_data->item_info.items[ i ].render( &io_main_data->sim_data );
            }

        /*--------------------------------------------
        Check Tess <-> Tess Collisions
        --------------------------------------------*/

        visited_hubs_count = 0;
        for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
            {
            skip = false;
            for( j = 0; j < visited_hubs_count; j++ )
                {
                if( i == visited_hubs[ j ] )
                    {
                    skip = true;
                    break;
                    }
                }

            if( skip )
                {
                continue;
                }

            for ( j = 0; j < io_main_data->hub_info.hub_count; j++ )
                {
                collision = false;
                if( i == j )
                    {
                    continue;
                    }

                collision = SDL_HasIntersection( io_main_data->hub_info.hubs[ i ].get_sprite()->get_bbox(),
                                                 io_main_data->hub_info.hubs[ j ].get_sprite()->get_bbox() );
                if( collision )
                    {
                    io_main_data->hub_info.hubs[ i ].handle_collision( &io_main_data->hub_info.hubs[ j ] );
                    visited_hubs[ visited_hubs_count ] = j;
                    visited_hubs_count++;
                    }
                }
            }
        
        for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
            {
            for( j = 0; j < io_main_data->item_info.item_count; j++ )
                {
                collision = false;

                collision = SDL_HasIntersection( io_main_data->hub_info.hubs[ i ].get_sprite()->get_bbox(),
                                                 io_main_data->item_info.items[ j ].get_sprite()->get_bbox() );
                if( collision )
                    {
                    io_main_data->hub_info.hubs[ i ].handle_collision( &io_main_data->item_info.items[ j ] );
                    io_main_data->item_info.items[ j ].handle_collision(  );
                    io_main_data->item_info.items[ j ].init();
                    }
                }
            }

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
                
                }
            }

        /*--------------------------------------------
        Refresh the screen
        --------------------------------------------*/
        SDL_RenderSetClipRect(io_main_data->sim_data.renderer, NULL);
        SDL_RenderPresent(io_main_data->sim_data.renderer);
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