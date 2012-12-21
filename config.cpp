#include "config.h"


/**
 * Set all variables to zero
 */
config::config() {
    flagInit=0;
    terminate=0;
    terminateReason="";
}

config::~config() {
    //dtor
}

/**
 * The config system load methos is quite important, first it loads all
 * the key/value based config strings out of the config file and stores
 * them in a key/value based datapool.
 * In the second part ge graps the config strings that he needs and copy
 * them over into the variables, if no key is found it uses the default
 * setting.
 */
bool config::load(string configPath) {

    ifstream ifs( configPath.c_str() );
    string temp;
    unsigned int i;
    bool flagReadValue;
    string key, value;


    while( getline( ifs, temp ) ) {

        key="";
        value="";
        flagReadValue=0;

        // check if not empty
        if(temp.length()>0) {

            // check if not a comment
            if(temp[0] != '#') {

                // loop for all characters
                for(i=0; i<temp.length(); i++) {

                    // check for detemeter
                    if(temp[i] == '=') flagReadValue=1;

                    if(flagReadValue==0) key += temp[i];
                    else if(temp[i] != '=') value += temp[i];

                }

                // add Key/Value pair to the cache
                cache.insert(pair<string, string>(key, value));
//                cout << "Key: " << key << ", Value: " << value <<endl;
            }
        }
    }


    resX = config::instance()->getValueInt("ResolutionX", 1024);
    resY = config::instance()->getValueInt("ResolutionY", 768);

    int crc = getValueInt("CRC", 0);
    if(crc==0) return false;
    else return true;
}



/**
 * This method is grapping an integer value out of the datapool, it does a
 * atoi cast.
 *   @warning the atoi cast is not at all caught by an exeption
 *   @param Key The key-string
 *   @param defaultValue if the key is not found, it will return the default value
 */
int config::getValueInt(string Key, int defaultValue) {
    map<string, string>::iterator i = cache.find(Key);
    if(i == cache.end()) {
        return defaultValue;
    }
    return atoi(i->second.c_str());
}

/**
 * Simmilar to getValueInt() iz just returns a string value
 *   @param Key The key-string
 *   @param defaultValue if the key is not found, it will return the default value
 */
string config::getValueString(string Key, string defaultValue) {
    map<string, string>::iterator i = cache.find(Key);
    if(i == cache.end()) {
        return defaultValue;
    }
    return i->second;
}
