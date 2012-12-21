#ifndef IMAGE_H
#define IMAGE_H


#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <string.h>
#include <iostream>
#include <sstream>
#include <map>



using namespace std;

class image {


    public:
        image();
        virtual ~image();

        void load(string pFilePath, bool adjustHeight);
        void draw(int pX, int pY);

        ALLEGRO_BITMAP *surface;



    private:

        int modH;
};

#endif // IMAGE_H
