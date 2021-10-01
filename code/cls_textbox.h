#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "sdl_rect.h"
#include "cls_position.h"
#include "sim.h"
#include "resources.h"

class TextBox
    {
 
//https://gamedev.stackexchange.com/questions/140294/what-is-the-most-efficient-way-to-render-a-textbox-in-c-sdl2
SDL_Rect textbox;
SDL_Texture* gTextOutput = NULL;
SDL_Rect clip;
SDL_Color color;
std::string text;

    
    public: void init 
    (
    std::string textstr, int xpos, int ypos, int width, int fsize
    )
        {
        text = textstr;
        textbox.x = xpos;
        textbox.y = ypos;
        textbox.w = width;
        textbox.h = fsize;
        color = { 255, 255, 255, 0xFF };
        }

    public: void set_pos 
    (
    Position * new_pos
    )
        {
        textbox.x = new_pos->get_x();
        textbox.y = new_pos->get_y();
        }
        
    public: void updt
    (
    void
    )
        {
        if( true )
            {
            return;
            }
        }

    public: SDL_Rect get_textbox
    (
    void
    )
        {
        return textbox;
        }
        

    public: std::string get_text
    (
    void
    )
        {
        return text;
        }
        
    public: void set_text
    (
    std::string newstr
    )
        {
        text = newstr;
        }
          
    public: SDL_Color get_color
    (
    void
    )
        {
        return color;
        }

    public: void render
    (
    resource_data           *io_resource_data,         /* simulation data                  */
    sim_data                *io_sim_data
    )
        {       
        SDL_Texture* gTextOutput = NULL;
        //SDL_RenderSetClipRect( io_sim_data->renderer, &textbox );

            SDL_Surface* gTextSurface = TTF_RenderText_Solid( io_resource_data->fonts.fonts[ 0 ], text.c_str(), color );
            if (gTextSurface != NULL)
            {
                gTextOutput = SDL_CreateTextureFromSurface(io_sim_data->renderer, gTextSurface);
                }
            if (gTextOutput == NULL)
            {
                throw "Unable to render texture! SDL ERROR: ";
            }

        SDL_RenderCopy(io_sim_data->renderer, gTextOutput, NULL, &textbox );
        }
};