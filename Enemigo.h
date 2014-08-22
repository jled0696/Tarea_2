#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SDL.h>
#include <SDL_image.h>

class Enemigo
{
    public:
        SDL_Renderer* renderer;
        SDL_Texture* textura;
        SDL_Rect rectangulo;
        Enemigo(SDL_Renderer* renderer);
        Enemigo();
        virtual ~Enemigo();
        void dibujar();
        virtual void logica();
    protected:
    private:
};

#endif // ENEMIGO_H
