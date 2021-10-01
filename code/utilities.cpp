/*--------------------------------------------------------------------------------

    Name:
        utilities.cpp

    Description:
        Utility handling

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

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include <stdio.h>
#include "utilities.h"


/*--------------------------------------------------------------------------------
Procedures
--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------

    Name:
        check_or_error

    Description:
        Check the test case and print an error message if it fails

--------------------------------------------------------------------------------*/
bool check_or_error
(
    bool                i_test,             /* condition to test                */
    const char         *i_msg               /* message to print on fail         */
)
    {
    /*------------------------------------------------
    Forward call to generic function
    ------------------------------------------------*/
    return( check_or_error( i_test, i_msg, EH_NONE ) );

    }    /* check_or_error() */

/*--------------------------------------------------------------------------------

    Name:
        check_or_error

    Description:
        Check the test case and print an error message if it fails

--------------------------------------------------------------------------------*/
bool check_or_error
(
    bool                i_test,             /* condition to test                */
    const char         *i_msg,              /* message to print on fail         */
    error_handler_t8    i_eh                /* error handler to use for info    */
)
    {
    /*------------------------------------------------
    If test fails, print the error message
    ------------------------------------------------*/
    if( !i_test )
        {
        switch( i_eh )
            {
            case EH_SDL:
                printf( "%s. SDL Error: %s\n", i_msg, SDL_GetError() );
                break;

            case EH_SDL_IMG:
                printf( "%s. SDL_IMG Error: %s\n", i_msg, IMG_GetError() );
                break;

            case EH_SDL_TTF:
                printf( "%s. SDL_TTF Error: %s\n", i_msg, TTF_GetError() );
                break;
                
            case EH_NONE:
                printf( "%s. \n", i_msg );                
                break;
            }
        }

    /*------------------------------------------------
    Return
    ------------------------------------------------*/
    return( i_test );

    }    /* check_or_error() */


/*--------------------------------------------------------------------------------

    Name:
        debug_info

    Description:
        Print out high level debug information

--------------------------------------------------------------------------------*/
void debug_info
(
    void
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    int                 driver_cnt;         /* count of render drivers          */
    int                 driver_i;           /* drivers iterator                 */    
    SDL_RendererInfo    info;               /* driver information               */

    /*------------------------------------------------
    Initialization
    ------------------------------------------------*/
    driver_cnt = SDL_GetNumRenderDrivers();

    /*------------------------------------------------
    Print out all the driver information
    ------------------------------------------------*/
    printf( "Render Drivers\n" );
    for( driver_i = 0; driver_i < driver_cnt; driver_i++ )
        {
        if( SDL_GetRenderDriverInfo( driver_i, &info ) == 0 )
            {
            printf( "  -%s\n", info.name );
            }
        }

    }    /* debug_info() */


/*--------------------------------------------------------------------------------

    Name:
        utl_sprintf

    Description:
        Print out high level debug information

--------------------------------------------------------------------------------*/
void utl_sprintf
(
    void
)
    {
    /*------------------------------------------------
    Local Variables
    ------------------------------------------------*/
    


    }    /* utl_sprintf() */