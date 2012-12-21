#ifndef GFXSYSTEM_H
#define GFXSYSTEM_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <string.h>
#include <iostream>
#include <sstream>
#include <map>

#include "image.h"



using namespace std;

class gfxSystem {


    public:

        gfxSystem();
        virtual ~gfxSystem();

        void init(bool pDebug, string pPath);
        void load(string pFilename, bool adjustHeight);
        void draw(string pKey, int pX, int pY);


    private:


        ALLEGRO_BITMAP* getSurface(string pKey);


        /// type to make the code more clean
        typedef std::pair<string, image> gfxPoolPair;               //!< The Pair for the gfxPool
        typedef std::map<string, image> gfxPoolMap;                 //!< The Map for the gfxPool
        typedef std::map<string, image>::iterator gfxPoolIterator;  //!< The Iterator for the gfxPool

        /// This is the gfxPool
        map<string,image> gfxPool;

        /// Debug mode
        int flagDebug;

        /// Base Path
        string gfxPath;

        ALLEGRO_BITMAP *sfNone;


};

#endif // GFXSYSTEM_H
