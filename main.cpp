#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<vector>
#include "Enemigo.h"
#include "EnemigoRojo.h"
#include "EnemigoMorado.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character1, *character2, *character_otro;
SDL_Rect rect_background,rect_character, rect_character_otro;
Mix_Music *musica = NULL;

bool colision(SDL_Rect r1, SDL_Rect r2)
{
    if(r1.x + r1.w <= r2.x)//r1 esta muy a la i
        return false;

    if(r2.x + r2.w <= r1.x)//r1 esta muy a la der
        return false;

    if(r1.y + r1.h <= r2.y)//r1 esta muy a la i
        return false;

    if(r2.y + r2.h <= r1.y)//r1 esta muy a la der
        return false;

    return true;
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Este es mi mensaje", 100, 100, 800/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //SDL mixer
    if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096))
    {
        return 40;
    }

    musica = Mix_LoadMUS("musica.ogg");
    Mix_PlayMusic(musica, 1);

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character1 = IMG_LoadTexture(renderer, "derecha1.png");
    character2 = IMG_LoadTexture(renderer, "derecha2.png");
    character_otro = IMG_LoadTexture(renderer, "derecha1.png");

    SDL_QueryTexture(character1, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 0;
    rect_character.w = w;
    rect_character.h = h;

    SDL_QueryTexture(character_otro, NULL, NULL, &w, &h);
    rect_character_otro.x = 40;
    rect_character_otro.y = 50;
    rect_character_otro.w = w;
    rect_character_otro.h = h;

    //Main Loop
    int cont = 0;
    int aux = 0;

    int frame = 0;
    int animacion_personaje = 0;

    int frame_anterior = 0;

    vector<Enemigo*>enemigos;
    enemigos.push_back(new EnemigoRojo(renderer));
    enemigos.push_back(new EnemigoMorado(renderer));
    enemigos.push_back(new Enemigo(renderer));

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        const Uint8* estado_teclas = SDL_GetKeyboardState( NULL );

        if(estado_teclas[SDL_SCANCODE_W])
        {
            rect_character.y--;
            if(colision(rect_character,rect_character_otro))
                rect_character.y++;
        }

        if(estado_teclas[SDL_SCANCODE_A])
        {
            if(rect_character.x>0)
                rect_character.x--;
            if(colision(rect_character,rect_character_otro))
                rect_character.x++;
        }

        if(estado_teclas[SDL_SCANCODE_S])
        {
            rect_character.y++;
            if(colision(rect_character,rect_character_otro))
                rect_character.y--;
        }

        if(estado_teclas[SDL_SCANCODE_D])
        {
            if(rect_character.x<800-w)
                rect_character.x++;
            if(colision(rect_character,rect_character_otro))
                rect_character.x--;
        }


        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        if(animacion_personaje%2 == 0)
            SDL_RenderCopy(renderer, character1, NULL, &rect_character);
        else
            SDL_RenderCopy(renderer, character2, NULL, &rect_character);

        SDL_RenderCopy(renderer, character_otro, NULL, &rect_character_otro);

        if(frame%200==0)
        {
            animacion_personaje++;
        }

        for(int i=0;i<enemigos.size();i++)
        {
            enemigos[i]->dibujar();

            enemigos[i]->logica();
            cout<<enemigos[i]->rectangulo.y<<endl;

        }

        SDL_RenderPresent(renderer);
        frame++;

        int frame_actual = SDL_GetTicks() - frame_anterior;
        frame_anterior = SDL_GetTicks();
        if(17-frame_actual>0)
            SDL_Delay( 17-frame_actual );

    }

	return 0;
}
