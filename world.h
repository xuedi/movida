#ifndef WORLD_H
#define WORLD_H


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
#include <time.h> // random

using namespace std;

class world {


    public:
        world();
        virtual ~world();

        void tick(void);
        void draw(void);
        void load(void);

        bool injectMouseClick(int mx, int my);

    protected:


    private:

        void render(void);
        void createWorldMap(void);


        bool refreshBuffer;

        ALLEGRO_BITMAP *renderBuffer;
        ALLEGRO_FONT *gameFont;

        gfxSystem *gfx;


        std::map<int, std::map<int, int> > worldMap;
        int worldMapSize;
        int worldMapCenterX, worldMapCenterY;


};

#endif // WORLD_H
