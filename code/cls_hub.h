#pragma once
#include "cls_circle.h"
#include "cls_textbox.h"
#include "cls_position.h"
#include "resources.h"
#include "sim.h"
class Hub
    {
    //public pygame.sprite.Sprite
    
    int speedx;
    int speedy;
    
    Circle sprite;
    TextBox text_pos;
    

    public: void init 
    (
    void
    )
        {
        sprite.init( 0, 0, 5 );
        text_pos.init( sprite.get_pos()->stringify(), sprite.get_pos()->get_x(), sprite.get_pos()->get_y(), 100, 12 );
        }
    public: void update 
    (
    void
    )
        {
        text_pos.set_text( sprite.get_pos()->stringify() );
        text_pos.set_pos( sprite.get_pos() );
        }
        
    public: void handle_key
    (
    SDL_Keycode key_press
    )
        {
        speedx = 0;
        speedy = 0;
        switch( key_press )
            {
            case SDLK_UP:
                speedy = -8;
                break;

            case SDLK_DOWN:
                speedy = 8;        
                break;

            case SDLK_LEFT:
                speedx = -8;
                break;

            case SDLK_RIGHT:
                speedx = 8;
                break;
            }
        
        sprite.get_pos()->shift_x( speedx );
        sprite.get_pos()->shift_y( speedy );
        update();
        }

    public: Circle get_sprite
    (
    void
    )
        {
        return sprite;
        }

    public: void render
    (
    resource_data           *io_resource_data,         /* simulation data                  */
    sim_data                *io_sim_data
    )
        {
        sprite.render( io_sim_data );
        text_pos.render( io_resource_data, io_sim_data );
        }
};