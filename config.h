#ifndef CONFIG_H
#define CONFIG_H


#include <string.h>     // strcpy,strcmp
#include <iostream>
#include <map>
#include <fstream>
#include <stdio.h>      // atoi
#include <stdlib.h>     // atoi


//#include <yaml.h> //  -lyaml




using namespace std;

/// This file contains the config cache
class config {

    static config *globInstance;            //!< define the singelton pointer

    public:

        /// This class is used as an global singeltin instance
        static config *instance() {
            if (!globInstance) globInstance = new config;
            return globInstance;
        }


        config();                           //!< Constructor
        virtual ~config();                  //!< Destructor
        bool load(string configPath);       //!< Load the config file

        map<string, string> cache;          //!< This is the actual key/value config pool

        bool terminate;
        string terminateReason;


        // fixed&fast important configs
        int resX,
            resY;

        // slow dynamic config cache
        int getValueInt(string Key, int defaultValue);              //!< graps an interger value out of the pool
        string getValueString(string Key, string defaultValue);     //!< graps a string out of the pool

    protected:

    private:

        bool flagInit;                                              //!< Is set after init is done
};


#endif // CONFIG_H
