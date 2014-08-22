#include "EnemigoMorado.h"

EnemigoMorado::EnemigoMorado(SDL_Renderer* renderer)
{
    this->renderer=renderer;
    textura = IMG_LoadTexture(renderer,"enemigo3.png");
    SDL_QueryTexture(textura, NULL, NULL, &rectangulo.w, &rectangulo.h);
    rectangulo.x = 0;
    rectangulo.y = 0;
}

EnemigoMorado::~EnemigoMorado()
{
    //dtor
}

void EnemigoMorado::logica()
{   if(rectangulo.x<700&&rectangulo.y==0)
        rectangulo.x++;
    else if(rectangulo.x==700&&rectangulo.y<500)
        rectangulo.y++;
    else if(rectangulo.x>0&&rectangulo.y==500)
        rectangulo.x--;
    else
        rectangulo.y--;
}
