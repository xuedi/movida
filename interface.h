#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "gfxSystem.h"

// singelton inside :-P
#include "config.h"
#include "status.h"


using namespace std;

class interface {


    public:
        interface();
        virtual ~interface();

        void tick(void);
        void draw(void);
        void load(void);

        bool injectMouseClick(int mx, int my);

    protected:


    private:

        void drawMainMenue(void);

        gfxSystem *gfx;

        ALLEGRO_FONT *gameFont;



};

#endif // INTERFACE_H
