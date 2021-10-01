#pragma once
#include "cls_position.h"
#include "sim.h"
class Circle
    {
    Position pos;
    int radius;

    public: Position* get_pos 
    (
    void
    )
        {
        return &pos;
        }

    public: int get_radius 
    (
    void
    )
        {
        return radius;
        }

    public: void init 
    (
    Position cntr,
    int rad
    )
        {
        pos = cntr;
        radius = rad;
        }

    public: void init 
    (
    int xp,
    int yp,
    int rad
    )
        {
        pos.init( xp, yp );
        radius = rad;
        }

    public: void render
    (
    sim_data           *io_sim_data         /* simulation data                  */
    )
        {    
        SDL_Rect fillRect;
        fillRect = {
                    pos.get_x(), 
                    pos.get_y(),
                    radius,
                    radius 
                    };
        SDL_SetRenderDrawColor( io_sim_data->renderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( io_sim_data->renderer, &fillRect );
       /* SDL_RenderSetClipRect( io_sim_data->renderer, NULL);    
        SDL_RenderCopy(io_sim_data->renderer, gTextOutput, NULL, &textbox );*/
        }
    };