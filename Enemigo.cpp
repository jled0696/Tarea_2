#include "Enemigo.h"

Enemigo::Enemigo(SDL_Renderer* renderer)
{
    this->renderer=renderer;
    textura = IMG_LoadTexture(renderer,"enemigo1.png");
    SDL_QueryTexture(textura, NULL, NULL, &rectangulo.w, &rectangulo.h);
    rectangulo.x = 0;
    rectangulo.y = 0;
}

Enemigo::Enemigo()
{
    //dtor
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::logica()
{
if(rectangulo.y<500)
        rectangulo.y++;
    else if(rectangulo.y==500)
        rectangulo.y=0;

}

void Enemigo::dibujar()
{
    SDL_RenderCopy(renderer, textura, NULL, &rectangulo);
}
