

#include <SDL.h>
#include <stdio.h>

bool check_or_error
(
    bool            test,
    /* condition to test            */
    const char* msg
    /* message to print on fail     */
)
{
    if (!test)
    {
        printf("%s. SDL Error: %s\n\n", msg, SDL_GetError());
    }

    //    printf( "hi" );
    //    std::cout << "hi" << " " << std::endl;
    return(test);
}


void debug_info
(
    void
)
{
    int i = 0;
    int r = 0;
    SDL_RendererInfo info;
    r = SDL_GetNumRenderDrivers();
    while (i < r) {
        if (SDL_GetRenderDriverInfo(i, &info) == 0)
        {
            printf("%s\n", info.name);
        }
        i++;
    }
}