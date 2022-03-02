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
#if defined(_WIN64) || defined(_WIN32)
#include <direct.h>
#define GET_CURRENT_DIR _getcwd
#elif defined(__linux__)
#include <unistd.h>
#define GET_CURRENT_DIR getcwd
#endif
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "genome.h"
#include "population.h"

#include "mpi.h"        //not in use yet, but leave to make sure compilation works
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
Namespace markers
--------------------------------------------------------------------------------*/
using namespace NEAT;
using namespace std;

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

void handle_events
(
    main_data           *io_main_data       /* main data                        */
);

void handle_tess_item_collisions
(
    main_data           *io_main_data       /* main data                        */
);

void create_pop
(
    main_data           *io_main_data,      /* main data                        */
    Genome 				*gnome
);

void handle_tess_tess_collisions
(
    main_data           *io_main_data       /* main data                        */
);

void init_brains
(
    main_data          *io_main_data,        /* main data                        */
    Genome 				*gnome
);

void init_sim_resources_data
(
    main_data          *io_main_data        /* main data                        */
);

static void main_close
(
    main_data          *io_main_data        /* main data                        */
);

static void main_init
(
    char               *i_window_name,      /* name of window                   */
    main_data          *io_main_data        /* main data                        */
);

static void main_loop
(
    main_data          *io_main_data        /* main data                        */
);

void remove_hub
(
    main_data          *io_main_data,       /* main data                        */
    int                 hub_idx             /* index of hub to remove           */
);

void update_hubs
(
    main_data           *io_main_data,      /* main data                        */
    float                time_step          /* seconds since last update        */
);

void update_species
(
    main_data          *io_main_data       /* main data                        */
);


/*--------------------------------------------------------------------------------
Enumerations
--------------------------------------------------------------------------------*/
typedef int inputs_t8;
enum
    {
    INPUTS_NUM_ENEMIES                  = 0,
    INPUTS_X_DIST_NRST_ENEMY,
    INPUTS_Y_DIST_NRST_ENEMY,
    INPUTS_NUM_ITEMS,
    INPUTS_X_DIST_NRST_ITEM,
    INPUTS_Y_DIST_NRST_ITEM,
    INPUTS_CNT
    };


typedef int outputs_t8;
enum
    {
    OUTPUTS_UP                  = 0,
    OUTPUTS_DOWN,
    OUTPUTS_LEFT,
    OUTPUTS_RIGHT,
    OUTPUTS_CNT
    };

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
    main_data           main_sim_data;     /* simulation data                  */
    int                 i;                 /* loop counter                     */               
    ifstream            iFile;              /* input file                       */
    Genome             *start_genome;       /* starting genome                  */  

    /*------------------------------------------------
    Print out startup status info
    ------------------------------------------------*/
    debug_info();

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    init_sim_resources_data( &main_sim_data );

    /*------------------------------------------------
    Initialize Environment
    ------------------------------------------------*/
    main_init( (char*)"Tesselations", &main_sim_data );
    check_or_error( main_sim_data.sim_info.running, "Initialization Failed" );

    /*------------------------------------------------
    Load Images
    ------------------------------------------------*/
    load_all_images( &main_sim_data );
    check_or_error( main_sim_data.sim_info.running, "Failed to get all images" );

    /*------------------------------------------------
    Load Fonts
    ------------------------------------------------*/
    load_all_fonts( &main_sim_data );
    check_or_error( main_sim_data.sim_info.running, "Failed to get all fonts" );      
    
    /*------------------------------------------------
    Open the starting genome file
    ------------------------------------------------*/
    //gene_loc = (char *)malloc( MAX_STR_LEN );
    //snprintf( gene_loc, MAX_STR_LEN, "%s/%s/%s", ROOT_PATH, "genes", "tessstartgenes" );
    //iFile.open( gene_loc, std::ifstream::in );
    
    /*------------------------------------------------
    Read in the start Genome
    ------------------------------------------------*/
    //cout<<"Reading in the start genome"<<endl;
    //iFile>>curword;
    //iFile>>id;
    //cout<<"Reading in Genome id "<<id<<endl;
    start_genome=new Genome( INPUTS_CNT, OUTPUTS_CNT, 0, 0 );
    //iFile.close();

    create_pop( &main_sim_data, start_genome );

    /*------------------------------------------------
    Set up items
    ------------------------------------------------*/
    main_sim_data.item_info.item_count = MAX_ITEMS;

    for( i = 0; i < main_sim_data.item_info.item_count; i++ )
        {
        main_sim_data.item_info.items[ i ].init();
        main_sim_data.item_info.items[ i ].handle_collision();  
        }
    /*------------------------------------------------
    Initialize Statistics
    ------------------------------------------------*/
    main_sim_data.statistics.max_fit = 0;

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
        create_pop

    Description:
        Update hub inputs for latest events

--------------------------------------------------------------------------------*/

void create_pop
(
    main_data           *io_main_data,      /* main data                        */
    Genome 				*gnome
)
    {

    /*------------------------------------------------
    Set up hubs
    ------------------------------------------------*/
    for( int i = 0; i < MAX_HUBS; i++ )
        {
        io_main_data->hub_info.hubs[ i ] = new Hub();
        io_main_data->hub_info.hubs[ i ]->get_sprite()->set_pos( rand() % WORLD_WIDTH, rand() % WORLD_HEIGHT );

        }

    io_main_data->hub_info.hub_count = MAX_HUBS;
    io_main_data->hub_info.selected_hub = 0;

    /*------------------------------------------------
    Set up brains
    ------------------------------------------------*/
    init_brains( io_main_data, gnome );
    }


/*--------------------------------------------------------------------------------

    Name:
        get_sensor_data

    Description:
        Update hub inputs for latest events

--------------------------------------------------------------------------------*/

void get_sensor_data
(
    main_data           *io_main_data,      /* main data                        */
    Hub                 *i_hub,              /* first pointer to a hub           */
    double              *io_sensvals
)
    {
    
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/    
    float                dist;              /* distance between hubs            */
    int                  i;                 /* iterator                         */
    float                min_dist;          /* minimum distance between hubs    */
    Hub                 *nearest_hub;       /* pointer to nearest hub           */
    Item                *nearest_item;      /* pointer to nearest item          */
    Hub                 *p_hub;             /* first pointer to a hub           */
    Item                *p_item;            /* first pointer to an item         */
    
    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    nearest_hub = NULL;
    nearest_item = NULL;
    min_dist = 999999;

    /*------------------------------------------------
    Find the closest hub
    ------------------------------------------------*/
    for( i = 0; i < io_main_data->hub_info.hub_count; i++ )
        {
        p_hub = io_main_data->hub_info.hubs[ i ];

        if( p_hub == i_hub )
            {
            continue;
            }
        dist = i_hub->get_sprite()->get_pos()->dist_to( p_hub->get_sprite()->get_pos() );
        
        if( abs( dist ) < abs( min_dist ) )
            {
            min_dist = dist;
            nearest_hub = p_hub;
            }
        }
    
    /*------------------------------------------------
    Find the closest item
    ------------------------------------------------*/
    min_dist = 999999;
    for( i = 0; i < io_main_data->item_info.item_count; i++ )
        {
        p_item = &io_main_data->item_info.items[ i ];
        dist = i_hub->get_sprite()->get_pos()->dist_to( p_item->get_sprite()->get_pos() );

        if( abs( dist ) < abs( min_dist ) )
            {
            min_dist = dist;
            nearest_item = p_item;
            }
        }
    
    /*------------------------------------------------
    Update hub related inputs
    ------------------------------------------------*/
    io_sensvals[ INPUTS_NUM_ENEMIES ] = io_main_data->hub_info.hub_count - 1;
    if( io_main_data->hub_info.hub_count > 1 )
        {
        io_sensvals[ INPUTS_X_DIST_NRST_ENEMY ] = i_hub->get_sprite()->get_pos()->get_x() - nearest_hub->get_sprite()->get_pos()->get_x() / 10;
        io_sensvals[ INPUTS_Y_DIST_NRST_ENEMY ] = i_hub->get_sprite()->get_pos()->get_y() - nearest_hub->get_sprite()->get_pos()->get_y() / 10;
        }
    else
        {
        io_sensvals[ INPUTS_X_DIST_NRST_ENEMY ] = min_dist / 10;        
        io_sensvals[ INPUTS_Y_DIST_NRST_ENEMY ] = min_dist / 10;
        }
    
    /*------------------------------------------------
    Update item related inputs
    ------------------------------------------------*/
    io_sensvals[ INPUTS_NUM_ITEMS ] = io_main_data->item_info.item_count - 1;
    if( io_main_data->item_info.item_count > 1 )
        {
        io_sensvals[ INPUTS_X_DIST_NRST_ITEM ] = i_hub->get_sprite()->get_pos()->get_x() - nearest_item->get_sprite()->get_pos()->get_x() / 10;
        io_sensvals[ INPUTS_Y_DIST_NRST_ITEM ] = i_hub->get_sprite()->get_pos()->get_y() - nearest_item->get_sprite()->get_pos()->get_y() / 10;
        }
    else
        {
        io_sensvals[ INPUTS_X_DIST_NRST_ITEM ] = min_dist / 10;        
        io_sensvals[ INPUTS_Y_DIST_NRST_ITEM ] = min_dist / 10;
        }


    }    /* get_sensor_data */


/*--------------------------------------------------------------------------------

    Name:
        handle_events

    Description:
        Handle latest events

--------------------------------------------------------------------------------*/

void handle_events
(
    main_data           *io_main_data       /* main data                        */
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
    sel_hub = io_main_data->hub_info.hubs[ io_main_data->hub_info.selected_hub ];

    /*--------------------------------------------
    Check for events
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
            io_main_data->sim_info.running = SIM_STAT_END;
            }
        else if( event.type == SDL_KEYDOWN )
            {
            /*------------------------------------
            Forward the key event to the sprite
            ------------------------------------*/
            sel_hub->handle_key( event.key.keysym.sym );                
            }
        }

    }    /* handle_events */


/*--------------------------------------------------------------------------------

    Name:
        handle_tess_item_collisions

    Description:
        Handle collisions between a tess and an item

--------------------------------------------------------------------------------*/

void handle_tess_item_collisions
(
    main_data           *io_main_data       /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    bool                collision;          /* collision detected?              */
    Uint8               i;                  /* loop counter                     */
    Uint8               j;                  /* loop counter                     */
    Hub                *p_hub_1;            /* first pointer to a hub           */
    Item               *p_item;             /* pointer to an item               */
    
    /*------------------------------------------------
    Check Tess <-> Item Collisions
    ------------------------------------------------*/
    for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
        {
        /*----------------------------------------
        Assign pointers
        ----------------------------------------*/
        p_hub_1 = io_main_data->hub_info.hubs[ i ];
        for( j = 0; j < io_main_data->item_info.item_count; j++ )
            {
            /*------------------------------------
            Initialize loop variables
            ------------------------------------*/
            p_item = &io_main_data->item_info.items[ j ];
            collision = false;
                
	        /*------------------------------------
	        Check for collision
	        ------------------------------------*/
            collision = SDL_HasIntersection( p_hub_1->get_sprite()->get_bbox(),
                                             p_item->get_sprite()->get_bbox() );

	        /*------------------------------------
	        Handle Collision
	        ------------------------------------*/
            if( collision )
                {
                p_hub_1->items_collected++;
                p_hub_1->handle_collision( p_item );
                p_item->handle_collision();
                }
            }
        }

    }   /* handle_tess_item_collisions */


/*--------------------------------------------------------------------------------

    Name:
        handle_tess_tess_collisions

    Description:
        Handle collisions between tess

--------------------------------------------------------------------------------*/

void handle_tess_tess_collisions
(
    main_data           *io_main_data       /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    bool                collision;          /* collision detected?              */
    int                 collided_hubs[ MAX_HUBS ][ MAX_HUBS ];
                                            /* list of collided hubs            */
    int                 collided_hubs_count[ MAX_HUBS ];
                                            /* numder of collided hubs          */
    Uint8               i;                  /* loop counter                     */
    Uint8               j;                  /* loop counter                     */
    Hub                *p_hub_1;            /* first pointer to a hub           */
    Hub                *p_hub_2;            /* second pointer to a hub          */
    
    /*------------------------------------------------
    Initialize variables
    ------------------------------------------------*/  
    for( i = 0; i < MAX_HUBS; i++ )
        {
        collided_hubs_count[ i ] = 0;
        }
        
    /*------------------------------------------------
    Check Tess <-> Tess Collisions
    ------------------------------------------------*/ 
    for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
        {
        /*----------------------------------------
        Assign pointers
        ----------------------------------------*/
        p_hub_1 = io_main_data->hub_info.hubs[ i ];

        for ( j = 0; j < io_main_data->hub_info.hub_count; j++ )
            {
            /*------------------------------------
            Initialize loop variables
            ------------------------------------*/
            p_hub_2 = io_main_data->hub_info.hubs[ j ];
            collision = false;

	        /*------------------------------------
	        Check if this hub has already collided
	        ------------------------------------*/
            if( ( i == j )
                || ( i == collided_hubs[ i ][ j ] ) )
                {
                continue;
                }

	        /*------------------------------------
	        Check for collision
	        ------------------------------------*/
            collision = SDL_HasIntersection( p_hub_1->get_sprite()->get_bbox(),
                                             p_hub_2->get_sprite()->get_bbox() );

	        /*------------------------------------
	        Handle Collision
            Mark Collision between 
	        ------------------------------------*/
            if( collision )
                {
                p_hub_1->handle_collision( p_hub_2 );
                collided_hubs[ j ][ collided_hubs_count[ j ] ] = i;
                collided_hubs_count[ j ]++;
                }
            }
        }

    }    /* handle_tess_tess_collisions */


/*--------------------------------------------------------------------------------

    Name:
        init_brains

    Description:
        Initialize brains

--------------------------------------------------------------------------------*/

void init_brains
(
    main_data          *io_main_data,        /* main data                        */
    Genome 				*gnome
)
    {    
    vector<Species*>::iterator 
                        curspec;            /* used in printing out debug info  */  
    
    /*------------------------------------------------
    Spawn the Population from starter gene
    ------------------------------------------------*/
    //cout<<"Spawning Population off Genome"<<endl;
    io_main_data->pop_info.population = new Population(gnome, io_main_data->hub_info.hub_count );
    io_main_data->pop_info.offspring_count = 0;

    //cout<<"Verifying Spawned Pop"<<endl;
    io_main_data->pop_info.population->verify();

    update_species( io_main_data );

    /*------------------------------------------------
    Create Champion Species
    ------------------------------------------------*/
    //io_main_data->champions

    /*------------------------------------------------
    //For printing only
    ------------------------------------------------*/
   /* for(curspec=(io_main_data->pop_info.population->species).begin();curspec!=(io_main_data->pop_info.population->species).end();curspec++) 
        {
        cout<<"Species "<<(*curspec)->id<<" size: "<<(*curspec)->organisms.size()<<" average: "<<(*curspec)->average_est<<endl;
        }

    cout<<"Pop size: "<<io_main_data->pop_info.population->organisms.size()<<endl;*/

    }    /* init_brains */


/*--------------------------------------------------------------------------------

    Name:
        init_sim_resources_data

    Description:
        Primary Initializer

--------------------------------------------------------------------------------*/

void init_sim_resources_data
(
    main_data          *io_main_data        /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 i;                  /* argument count                   */
    
    /*------------------------------------------------
    Initialize Image Data
    ------------------------------------------------*/
    for( i = 0; i < MAX_IMAGES; i++ )
        {
        io_main_data->resources.images[ i ] = NULL;
        }
    io_main_data->resources.image_count = 0;
    
    /*------------------------------------------------
    Initialize Resource Data
    ------------------------------------------------*/
    for( i = 0; i < MAX_FONTS; i++ )
        {
        io_main_data->resources.fonts[ i ] = NULL;
        }
    io_main_data->resources.font_count = 0;
    
    /*------------------------------------------------
    Initialize Sim Variables
    ------------------------------------------------*/
    io_main_data->sim_info.renderer = NULL;
    io_main_data->sim_info.window = NULL;
    io_main_data->sim_info.running = SIM_STAT_RUNNING;
    io_main_data->sim_info.last_update = 0;

    io_main_data->sim_info.root_dir = (char *)malloc( MAX_STR_LEN );
    GET_CURRENT_DIR(io_main_data->sim_info.root_dir, 256);

    io_main_data->sim_info.camera = new Position( 0, 0 );

    }    /* init_sim_resources_data */


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
    SDL_DestroyRenderer( io_main_data->sim_info.renderer );
    io_main_data->sim_info.renderer = NULL;

    /*------------------------------------------------
    Destroy Window
    ------------------------------------------------*/
    SDL_DestroyWindow( io_main_data->sim_info.window );
    io_main_data->sim_info.window = NULL;

    /*------------------------------------------------
    Quit SDL subsystems
    ------------------------------------------------*/
    SDL_Quit();

    }    /* main_close */


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
    io_main_data->sim_info.running = ( SDL_Init( SDL_INIT_VIDEO ) == 0 );
    check_or_error( io_main_data->sim_info.running, "SDL Failed to initialize", EH_SDL );

    /*------------------------------------------------
    Initialize PNG Handling
    ------------------------------------------------*/
    int imgFlags = IMG_INIT_PNG;
    io_main_data->sim_info.running = ( IMG_Init( imgFlags ) & imgFlags );
    check_or_error( io_main_data->sim_info.running, "SDL_image could not initialize!", EH_SDL_IMG );
    
    /*------------------------------------------------
    Initialize Font Handling
    ------------------------------------------------*/
    io_main_data->sim_info.running = ( TTF_Init() != -1 );
    check_or_error( io_main_data->sim_info.running, "SDL_TTF could not initialize!", EH_SDL_TTF );
    
    /*------------------------------------------------
    Create the main window
    ------------------------------------------------*/
    io_main_data->sim_info.window = ( SDL_CreateWindow( i_window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ) );
    io_main_data->sim_info.running = check_or_error( io_main_data->sim_info.window != NULL, "Could not create window", EH_SDL );

    /*------------------------------------------------
    Create the main renderer
    ------------------------------------------------*/
    io_main_data->sim_info.renderer = SDL_CreateRenderer( io_main_data->sim_info.window, -1, SDL_RENDERER_SOFTWARE );
    io_main_data->sim_info.running = check_or_error( io_main_data->sim_info.renderer != NULL, "Could not create renderer", EH_SDL );

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
    Uint8               i;                  /* loop counter                     */
    Item               *p_item;             /* pointer to an item               */
    Uint32              this_update;        /* current time                     */
    float               time_step;          /* seconds since last update        */

    /*------------------------------------------------
    Update timer
    ------------------------------------------------*/
    this_update = SDL_GetTicks();
    time_step = ( this_update - io_main_data->sim_info.last_update ) / 1000.0f;
    io_main_data->sim_info.last_update = this_update;

    /*------------------------------------------------
    Event Loop
    ------------------------------------------------*/
    while( io_main_data->sim_info.running )
        {      
        /*--------------------------------------------
        Clear the screen
        --------------------------------------------*/
        SDL_RenderCopy( io_main_data->sim_info.renderer, io_main_data->resources.images[ 0 ], NULL, NULL );

        /*--------------------------------------------
        Update hubs
        --------------------------------------------*/
        update_hubs( io_main_data, time_step );
        SDL_Event e;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                //quit = true;
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_COMMA:
                        io_main_data->sim_info.camera.shift_y_buff( -10, SCREEN_WIDTH / 2 );
                        break;

                    case SDLK_o:
                        io_main_data->sim_info.camera.shift_y_buff( 10, SCREEN_WIDTH / 2 );
                        break;

                    case SDLK_a:
                        io_main_data->sim_info.camera.shift_x_buff( 10, SCREEN_HEIGHT / 2);
                        break;

                    case SDLK_e:
                        io_main_data->sim_info.camera.shift_x_buff( -10, SCREEN_HEIGHT / 2);
                        break;

                    default:
                    break;
                }
            }
        }

        /*--------------------------------------------
        Update items
        --------------------------------------------*/
        for ( i = 0; i < io_main_data->item_info.item_count; i++ )
            {
            p_item = &io_main_data->item_info.items[ i ];
            p_item->render( &io_main_data->sim_info, &io_main_data->sim_info.camera );
            } 

        /*--------------------------------------------
        Check Tess <-> Tess Collisions
        --------------------------------------------*/
        handle_tess_tess_collisions( io_main_data );
        
        /*--------------------------------------------
        Check Tess <-> Item Collisions
        --------------------------------------------*/  
        handle_tess_item_collisions( io_main_data );

        /*--------------------------------------------
        Get latest events
        --------------------------------------------*/
        handle_events( io_main_data );
        if( io_main_data->hub_info.hub_count == 0 )
            {                           
            /*------------------------------------
            Create the child brain

            Here we call two rtNEAT calls: 
            1) choose_parent_species() decides 
                which species should produce the 
                next offspring
            2) reproduce_one(...) creates a 
                single offspring from the chosen 
                species    
            ------------------------------------*/    
            if( io_main_data->champions.size() == 0 )
                {
                create_pop( io_main_data, io_main_data->pop_info.population->choose_parent_species()->organisms.back()->gnome );
                }
            else
                {       
                create_pop( io_main_data, io_main_data->champions.back() );
                }
                continue;
                
            }

        /*--------------------------------------------
        Refresh the screen
        --------------------------------------------*/
        SDL_RenderSetClipRect( io_main_data->sim_info.renderer, NULL );
        SDL_RenderPresent( io_main_data->sim_info.renderer );
        }

    }    /* main_loop */


/*--------------------------------------------------------------------------------

    Name:
        remove_hub

    Description:
        Handle simulation cleanup

--------------------------------------------------------------------------------*/

void remove_hub
(
    main_data           *io_main_data,      /* main data                        */
    int                 hub_idx             /* index of hub to remove           */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    Uint8               i;                  /* loop counter                     */
    
    /*------------------------------------------------
    Remove selecte hub
    ------------------------------------------------*/
    for( i = hub_idx; i < io_main_data->hub_info.hub_count - 1; i++ )
        {
        io_main_data->hub_info.hubs[ i ] = io_main_data->hub_info.hubs[ i + 1 ];
        }
    io_main_data->hub_info.hub_count -= 1;

    }    /* remove_hub */


/*--------------------------------------------------------------------------------

    Name:
        update_hubs

    Description:
        Update all the hubs for the current timestep

--------------------------------------------------------------------------------*/

void update_hubs
(
    main_data           *io_main_data,      /* main data                        */
    float               time_step           /* seconds since last update        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    string              file;               /* output file                      */ 
    Uint8               i;                  /* loop counter                     */
    Uint8               j;                  /* loop counter                     */
    SDL_Keycode         key;                /* key being pressed                */
    int                 min_dist;           /* minimum distance                 */
    Organism           *new_org;            /* new organism being created       */
    Position           *new_pos;            /* new position                     */
    Hub                *p_hub_1;            /* first pointer to a hub           */
    Hub                *p_hub_2;            /* second pointer to a hub          */
    Organism           *p_org;              /* pointer to an organism           */    
    
    /*------------------------------------------------
    Update Hubs
    ------------------------------------------------*/
    for ( i = 0; i < io_main_data->hub_info.hub_count; i++ )
        {
        /*----------------------------------------
        Assign pointers
        ----------------------------------------*/
        p_hub_1 = io_main_data->hub_info.hubs[ i ];
        p_org = io_main_data->pop_info.population->organisms.at( i );
        if( p_org->fitness < p_hub_1->items_collected * 1000 + p_hub_1->health - 2000 )
            {
            p_org->fitness = p_hub_1->items_collected * 1000 + p_hub_1->health - 2000;
            }
        
        /*----------------------------------------
        Save genome if this organism is the most
        superior discovered
        ----------------------------------------*/
        if( io_main_data->statistics.max_fit < p_org->fitness )
            {
            io_main_data->statistics.max_fit = p_org->fitness;
            
            file = ROOT_PATH;
            file += "output//";
            file += to_string(p_hub_1->items_collected);
            file += "_";
            file += to_string( p_hub_1->health );
            file += ".txt";
            cout<<"Max Fit: " << io_main_data->statistics.max_fit << ", Health: " << p_hub_1->health << ", Items: " << p_hub_1->items_collected << std::endl;
            print_Genome_tofile( p_org->gnome, file.c_str() );
            io_main_data->champions.push_back( (p_org->gnome)->duplicate( 0 ) );
            }

        /*----------------------------------------
        Reduce health based on time passing
        ----------------------------------------*/        
        p_hub_1->health -= ( time_step );

        /*----------------------------------------
        Remove hubs with no health
        ----------------------------------------*/
        if( p_hub_1->health <= 0 )
            {
            remove_hub( io_main_data, i );
            io_main_data->pop_info.population->remove_org( io_main_data->pop_info.population->organisms.at( i ) );
            i--;
            continue;
            }            

        /*----------------------------------------
        A hub with more than 2000 health should
        create a new 'child' hub
        ----------------------------------------*/
        if( ( p_hub_1->health >= 1200 )
         && ( io_main_data->hub_info.hub_count < MAX_HUBS ) )
            {
            /*------------------------------------
            Create the child hub
            ------------------------------------*/
            cout << " A CHILD!" << std::endl;
            io_main_data->hub_info.hubs[ io_main_data->hub_info.hub_count ] = new Hub();
            p_hub_2 = io_main_data->hub_info.hubs[ io_main_data->hub_info.hub_count ];
            p_hub_2->get_sprite()->set_color( 0x00, 0xFF, 0x00, 0xFF );
            p_hub_2->set_generation( p_hub_1->get_generation() + 1 );
            io_main_data->hub_info.hub_count++;
                
            /*------------------------------------
            Create the child brain

            Here we call two rtNEAT calls: 
            1) choose_parent_species() decides 
                which species should produce the 
                next offspring
            2) reproduce_one(...) creates a 
                single offspring from the chosen 
                species    
            ------------------------------------*/    
            new_org=(io_main_data->pop_info.population->choose_parent_species())->reproduce_one(io_main_data->pop_info.offspring_count, io_main_data->pop_info.population, io_main_data->pop_info.population->species);
            io_main_data->pop_info.offspring_count++;

            /*------------------------------------
            Place the child below the parent
            ------------------------------------*/
            min_dist = p_hub_1->get_sprite()->get_radius() + p_hub_2->get_sprite()->get_radius();
            new_pos = new Position( p_hub_1->get_sprite()->get_pos() );
            new_pos->shift_y( min_dist );
            p_hub_2->get_sprite()->set_pos( new_pos );
                
            /*------------------------------------
            Remove health from the parent
            ------------------------------------*/
            p_hub_1->health -= 500;
        
            /*------------------------------------
            Save genome if this organism is able
            to produce a child
            ------------------------------------*/
            file = ROOT_PATH;
            file += "output//CHILD_PARENT_";
            file += to_string(p_hub_1->items_collected);
            file += "_";
            file += to_string( p_hub_1->health );
            file += ".txt";
            cout<<"Max Fit: " << io_main_data->statistics.max_fit << ", Health: " << p_hub_1->health << ", Items: " << p_hub_1->items_collected << std::endl;
            print_Genome_tofile( p_org->gnome, file.c_str() );
            }
        
        /*----------------------------------------
        Load the sensor 
        ----------------------------------------*/
        double sensvals[ INPUTS_CNT ];
        get_sensor_data( io_main_data, p_hub_1, sensvals );
        p_org->net->load_sensors( sensvals );
        p_org->net->activate();

        /*----------------------------------------
        Read the weights of the horizontal and 
        vertical motion outputs
        ----------------------------------------*/   
        outputs_t8 max = OUTPUTS_CNT;
        double max_weight = 0;
        j = 0;
        for( auto & otp : p_org->net->outputs )
            {
            if( otp->activation > max_weight )
                {
                max = j;
                max_weight = otp->activation;
                }
            j++;
            }
        
        /*----------------------------------------
        Simualte the keypress of the direction 
        with the maximum weight
        ----------------------------------------*/
        key = SDLK_UNKNOWN;
        switch( max )
            {
            case OUTPUTS_UP:
                key = SDLK_UP;
                break;
                
            case OUTPUTS_DOWN:
                key = SDLK_DOWN;
                break;
                
            case OUTPUTS_LEFT:
                key = SDLK_LEFT;
                break;
                
            case OUTPUTS_RIGHT:
                key = SDLK_RIGHT;
                break;

            }
        p_hub_1->handle_key( key ); 
            
             
        /*----------------------------------------
        Move and render the current hub
        ----------------------------------------*/
        p_hub_1->move( time_step );
        p_hub_1->render( &io_main_data->resources, &io_main_data->sim_info, &io_main_data->sim_info.camera );
        }

    }    /* update_hubs */


/*--------------------------------------------------------------------------------

    Name:
        update_species

    Description:
        Update all the hubs for the current timestep

--------------------------------------------------------------------------------*/

void update_species
(
    main_data           *io_main_data       /* main data                        */
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 compat_adjust_frequency;
                                            /* frequency of compatibility       */
                                            /*  adjustment                      */
    double              compat_mod;         /* speciation control threshold     */
    vector<Organism*>::iterator 
                        curorg;             /* current organisim               */
    int                 num_species;        /* current number of species       */
    int                 num_species_target; /* target number of species        */
    
    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/                                                
    num_species_target=NEAT::pop_size/15;
  
    /*------------------------------------------------
    This is where we determine the frequency of 
    compatibility threshold adjustment
    ------------------------------------------------*/
    compat_adjust_frequency = NEAT::pop_size/10;
    if (compat_adjust_frequency < 1)
        {
        compat_adjust_frequency = 1;
        }
        
    /*------------------------------------------------
    Every pop_size reproductions, adjust the 
    compat_thresh to better match the 
    num_species_target and reassign the population to
    new species                                            
    ------------------------------------------------*/  
    if (io_main_data->pop_info.offspring_count % compat_adjust_frequency == 0) 
        {
        num_species = io_main_data->pop_info.population->species.size();
        compat_mod=0.1;                                            
        
    /*------------------------------------------------
    This tinkers with the compatibility threshold 
    ------------------------------------------------*/
        if (num_species < num_species_target) 
            {
	        NEAT::compat_threshold -= compat_mod;
            }
        else if (num_species > num_species_target)
            {
	        NEAT::compat_threshold += compat_mod;
            }

    if (NEAT::compat_threshold < 0.3)
        {
	    NEAT::compat_threshold = 0.3;
        }

    //cout<<"compat_thresh = "<<NEAT::compat_threshold<<endl;
    
    /*------------------------------------------------
    Go through entire population, reassigning 
    organisms to new species       
    ------------------------------------------------*/                                           
    for (curorg = (io_main_data->pop_info.population->organisms).begin(); curorg != io_main_data->pop_info.population->organisms.end(); ++curorg) 
        {
	    io_main_data->pop_info.population->reassign_species(*curorg);
        }
    }                                                                          
     
    /*------------------------------------------------
    Rank all the organisms from best to worst in each 
    species
    ------------------------------------------------*/
    io_main_data->pop_info.population->rank_within_species();  
    
    /*------------------------------------------------
    Assign each species an average fitness 
    
    This average must be kept up-to-date by rtNEAT 
    in order to select species probabailistically for
    reproduction
    ------------------------------------------------*/
    io_main_data->pop_info.population->estimate_all_averages();   

}    /* update_species */
