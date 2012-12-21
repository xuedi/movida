#ifndef STATUS_H
#define STATUS_H


class status {

    static status *globInstance;            //!< define the singelton pointer

    public:

        /// This class is used as an global singeltin instance
        static status *instance() {
            if (!globInstance) globInstance = new status;
            return globInstance;
        }


        status();
        virtual ~status();


        int gameState;
        int mouseX, mouseY;

        bool shutDown;

        bool singelRender;

    protected:


    private:


};

#endif // STATUS_H
