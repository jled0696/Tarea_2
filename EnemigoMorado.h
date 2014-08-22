#ifndef ENEMIGOMORADO_H
#define ENEMIGOMORADO_H

#include "Enemigo.h"

class EnemigoMorado : public Enemigo
{
    public:
        EnemigoMorado(SDL_Renderer* renderer);
        virtual ~EnemigoMorado();
        void logica();
    protected:
    private:
};

#endif // ENEMIGOMORADO_H
