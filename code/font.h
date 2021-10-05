#pragma once
/*--------------------------------------------------------------------------------

    Name:
        font.h

    Description:
        Header for font operations

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_ttf.h>

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "main.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

void load_all_fonts
(
    main_data           *io_main_data       /* main data                        */
);