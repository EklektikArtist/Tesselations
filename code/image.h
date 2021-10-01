#pragma once
/*--------------------------------------------------------------------------------

    Name:
        image.h

    Description:
        Header for image operations

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------*/

/*------------------------------------------------
External Libraries
------------------------------------------------*/
#include <SDL_image.h>

/*------------------------------------------------
Project Headers
------------------------------------------------*/
#include "main.h"

/*--------------------------------------------------------------------------------
Declarations
--------------------------------------------------------------------------------*/

void load_all_images
(
    main_data           *io_sim_data         /* simulation data                  */
);