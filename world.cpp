#include "world.h"

world::world() {
    gfx = new gfxSystem;
    refreshBuffer=1;
    worldMapCenterX=0;
    worldMapCenterY=0;
}

world::~world() {
    delete gfx;
}


void world::createWorldMap(void) {

    worldMapSize = 100; // radius= 200x200

    srand ( time(NULL) ); // set random seed

    int i,e, cnt=0;
    for(i=-worldMapSize;i<=worldMapSize;i++) {
        for(e=-worldMapSize;e<=worldMapSize;e++) {
            worldMap[i][e] = rand() % 4 +1;
            cnt++;
        }
    }

    worldMap[0][0] = 5;
    worldMap[0][1] = 5;
    worldMap[0][2] = 5;
    worldMap[1][1] = 5;
    worldMap[2][1] = 5;

    worldMap[-1][3] = 5;

}

void world::load(void) {
    gameFont = al_load_ttf_font("data/times.ttf",14,0 );
    gfx->init(1, "data/gfx/world/");
    gfx->load("sfSlap.bmp",1);
    gfx->load("sfSlap001.bmp",1);
    gfx->load("sfSlap002.bmp",1);
    gfx->load("sfSlap003.bmp",1);
    gfx->load("sfSlap004.bmp",1);
    gfx->load("sfSlap005.bmp",1);
    createWorldMap();
    renderBuffer = al_create_bitmap(config::instance()->resX, config::instance()->resY);
}

void world::tick(void) {
    if(status::instance()->gameState==1) {

        //

    }
}
void world::render(void) {
    if(refreshBuffer==1) {

        // set new target
        al_set_target_bitmap(renderBuffer);

        // clear old buffer
        al_clear_to_color(al_map_rgb(0, 0, 0));















        // public setup
        int pShiftX = 0,    //-16,
            pShiftY = 0;    //-8;
        int tShiftX = 0,
            tShiftY = 0;
        int blocksX = (config::instance()->resX-32)/32,     // full width
            blocksY = (config::instance()->resY-16)/16;   // full heigth minus 100



        // internal variables
        int x,y;
        int tx,ty;          // title
        int px,py;          // position
        bool straigt=1;
        int xcnt=0,ycnt=0;



        // looping
        for(y=0;y<=(blocksY*2);y++) {
            for(x=0;x<=blocksX;x++) {

                // get the maped map position
                tx = x+xcnt;
                ty = blocksY-x+ycnt;

                // center the map on the screen
                tx -= blocksX;
                ty -= blocksY;

                // shift the map to the position
                tx += worldMapCenterX;
                ty += worldMapCenterY;


                tx += tShiftX;
                ty += tShiftY;

                // get the general position
                px = pShiftX + (x*32);
                py = pShiftY + (y*8);

                // correct the pattern at every second row
                if(!straigt) px += 16;

                // draw exept the last block of every second row
                if(straigt || x < blocksX) {

                    // choose the differnt Slaps
                    switch(worldMap[tx][ty]) {

                        case 1:
                            gfx->draw("sfSlap001.bmp", px, py);
                        break;

                        case 2:
                            gfx->draw("sfSlap002.bmp", px, py);
                        break;

                        case 3:
                            gfx->draw("sfSlap003.bmp", px, py);
                        break;

                        case 4:
                            gfx->draw("sfSlap004.bmp", px, py);
                        break;

                        case 5:
                            gfx->draw("sfSlap005.bmp", px, py);
                        break;

                        default:
                            gfx->draw("sfSlap.bmp", px, py);
                        break;

                    }

                }

            }

            // do the counting
            if(straigt) {
                straigt = 0;
                xcnt++;
            }
            else {
                straigt = 1;
                ycnt++;
            }
        }



        // return drawinginto the backbuffer
        al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

        // set flag as renderd
        refreshBuffer=0;
    }
}

void world::draw(void) {
    if(status::instance()->gameState==1) {

        render();

        // blit the cached game screen
        al_draw_bitmap(renderBuffer, 0, 0, 0);

    }
}

//
