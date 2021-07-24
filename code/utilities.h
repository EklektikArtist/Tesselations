#pragma once
/*--------------------------------------------------------------------------------

	Name:
		utilities.h

	Description:
		Header for utility operations

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

void debug_info
(
    void
);

bool check_or_error
(
	bool				test,				/* condition to test				*/
	const char		   *msg 				/* message to print on fail			*/
);