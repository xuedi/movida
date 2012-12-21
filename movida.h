#ifndef MOVIDA_H
#define MOVIDA_H


#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// singelton inside :-P
#include "config.h"
#include "status.h"

#include "world.h"
#include "interface.h"


using namespace std;

class movida {


    public:
        movida();
        virtual ~movida();

        bool init();
        bool run();


    protected:


    private:


        bool gameExit;
        bool gameHadInit;
        bool gameRedraw;
        bool gameRender;

        int cntTicks;
        int frames;
        int framesPerSecond;

        ALLEGRO_DISPLAY *screen;            // global display, focus/target handled by allegro
        ALLEGRO_EVENT_QUEUE* event_queue;
        ALLEGRO_TIMER* timer;
        ALLEGRO_FONT *gameFont;

        int mouseX, mouseY;
        int mouseLockedX, mouseLockedY;
        int mapLockedX,mapLockedY;
        bool mouseLocked;


        void tick();
        void tickSecond();
        void draw();

        world *gameWorld;
        interface *gameInterface;


};

#endif // MOVIDA_H
