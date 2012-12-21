#include "image.h"

image::image() {
    surface = NULL;
}

image::~image() {
//    delete surface;
}


void image::load(string pFilePath, bool adjustHeight) {

    ALLEGRO_BITMAP *sfTemp = NULL;
    sfTemp = al_load_bitmap( pFilePath.c_str() );
    if(!sfTemp) {
        fprintf(stderr, "image::load(): Failed to load '%s' !\n", pFilePath.c_str() );
    }
    surface = sfTemp;

    if(adjustHeight) {
        int height = al_get_bitmap_height( surface );
        if(height>16) modH = height - 16;
        else modH = 0;
    } else modH = 0;



}


void image::draw(int pX, int pY) {
    al_draw_bitmap(surface, pX, pY-modH, 0);
}
