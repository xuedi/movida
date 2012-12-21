#include "gfxSystem.h"


gfxSystem::gfxSystem() {
    flagDebug = 0;
    gfxPath = "";
    sfNone = NULL;
}




gfxSystem::~gfxSystem() {
    //dtor
}




void gfxSystem::init(bool pDebug, string pPath) {
    flagDebug = pDebug;
    gfxPath = pPath;

    // set name of the image
    std::stringstream tmpMessage;
    tmpMessage << pPath << "/sfNone.bmp";

    // BASE GFX
    sfNone = al_load_bitmap(tmpMessage.str().c_str() );
    if(!sfNone) {
        fprintf(stderr, "Failed to load sfNone!\n");
    }

}




void gfxSystem::load(string pFilename, bool adjustHeight) {

    // set name of the image
    std::stringstream tmpFilePath;
    tmpFilePath << gfxPath << pFilename;

    image tmpImage;
    tmpImage.load(tmpFilePath.str().c_str(), adjustHeight);
    gfxPool.insert(gfxPoolPair(pFilename, tmpImage));
}



// not used jet
ALLEGRO_BITMAP* gfxSystem::getSurface(string pKey) {

    gfxPoolIterator i = gfxPool.find(pKey);
    if(i != gfxPool.end()) {
        return i->second.surface;
    }
    return sfNone;
}




void gfxSystem::draw(string pKey, int pX, int pY) {

    gfxPoolIterator i = gfxPool.find(pKey);
    if(i != gfxPool.end()) {
        i->second.draw(pX, pY);
    }

}


