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
	bool				test,				/* condition to test				*/
	const char		   *msg 				/* message to print on fail			*/
)
	{
	/*------------------------------------------------
	If test fails, print the error message
	------------------------------------------------*/
	if( !test )
		{
		printf( "%s. SDL Error: %s\n\n", msg, SDL_GetError() );
		}

	/*------------------------------------------------
	Return
	------------------------------------------------*/
	return( test );

	}	/* check_or_error() */


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
	int					driver_cnt;			/* count of render drivers          */
	int					driver_i;			/* drivers iterator					*/	
	SDL_RendererInfo	info;				/* driver information               */

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

	}	/* debug_info() */