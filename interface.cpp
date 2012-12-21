#include "interface.h"

interface::interface() {
    gfx = new gfxSystem;
}

interface::~interface() {
    delete gfx;
}

void interface::load(void) {
    gameFont = al_load_ttf_font("data/times.ttf",14,0 );
    gfx->init(1, "data/gfx/interface/");
    gfx->load("sfButton.bmp",0);
}

void interface::tick(void) {
    //dtor
}

void interface::draw(void) {

    // choose the differnt Slaps
    switch(status::instance()->gameState) {

        case 0: // main menue
            drawMainMenue();
        break;

        case 1: // running game
            //gfxSystem->draw("sfSlapGreen.bmp", px, py);
        break;

    }
}


void interface::drawMainMenue(void) {
//    int x=(config::instance()->resX/2)-150;
//    int y=(config::instance()->resY/2);

    int bx, by, bw, bh;
    int mx = status::instance()->mouseX;
    int my = status::instance()->mouseY;


    bx=100;    by=100;    bw=300;    bh=30;
    gfx->draw("sfButton.bmp", bx, by); // is 200x30
    if(mx>bx&&mx<(bx+bw)&&my>by&&my<(by+bh)) al_draw_textf(gameFont, al_map_rgb(0,0,255), bx+(bw/2), by+7,ALLEGRO_ALIGN_CENTRE, "New game" );
    else al_draw_textf(gameFont, al_map_rgb(0,0,0), bx+(bw/2), by+7,ALLEGRO_ALIGN_CENTRE, "New game" );

    bx=100;    by=200;    bw=300;    bh=30;
    gfx->draw("sfButton.bmp", bx, by); // is 200x30
    if(mx>bx&&mx<(bx+bw)&&my>by&&my<(by+bh)) al_draw_textf(gameFont, al_map_rgb(0,0,255), bx+(bw/2), by+7,ALLEGRO_ALIGN_CENTRE, "EXIT" );
    else al_draw_textf(gameFont, al_map_rgb(0,0,0), bx+(bw/2), by+7,ALLEGRO_ALIGN_CENTRE, "EXIT" );
}


bool interface::injectMouseClick(int mx, int my) {

    if(status::instance()->gameState==0) {
        int bx, by, bw, bh;
        bx=100;    by=200;    bw=300;    bh=30;
        if(mx>bx&&mx<(bx+bw)&&my>by&&my<(by+bh)) status::instance()->shutDown = 1; // EXIT

        bx=100;    by=100;    bw=300;    bh=30;
        if(mx>bx&&mx<(bx+bw)&&my>by&&my<(by+bh)) status::instance()->gameState = 1; // START GAME
    }

    return false;
}






