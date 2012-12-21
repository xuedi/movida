#include "movida.h"


movida::movida() {
    screen = NULL;

    gameExit = false;
    gameRedraw = true;
    gameRender = false;
    gameHadInit = false;


    frames = 0;
    framesPerSecond = 0;


    mouseX = 0;
    mouseY = 0;
    mouseLockedX=0, mouseLockedY=0;
    mapLockedX=0,mapLockedY=0;
    mouseLocked=0;


    gameWorld = new world;
    gameInterface = new interface;

}


movida::~movida() {
    delete gameWorld;
    delete gameInterface;
    if (timer) al_destroy_timer(timer);
    if (screen) al_destroy_display(screen);
    if (event_queue) al_destroy_event_queue(event_queue);
}



bool movida::init() {


    // allegro
    cout << "allegro ... ";
    if(!al_init()) {
        cout << "FAILED" << endl;
        return 1;
    }else cout << "OK" << endl;


    // allegro - KEYBOARD
    cout << " - install keyboard ... ";
    if(!al_install_keyboard()) {
        cout << "FAILED" << endl;
        return 2;
    }else cout << "OK" << endl;


    // allegro - MOUSE
    cout << " - install mouse ... ";
    if(!al_install_mouse()) {
        cout << "FAILED" << endl;
        return 3;
    }else cout << "OK" << endl;


    // allegro - primitives
    cout << " - init primitives ... ";
    if(!al_init_primitives_addon()) {
        cout << "FAILED" << endl;
        return 4;
    }else cout << "OK" << endl;


    // allegro - IMAGE
    cout << " - init image addon ... ";
    if(!al_init_image_addon()) {
        cout << "FAILED" << endl;
        return 4;
    }else cout << "OK" << endl;


    // allegro - FONT
    al_init_font_addon();


    // allegro - FONT -* TTF
    cout << " - init fonts true type module ... ";
    if(!al_init_ttf_addon()) {
        cout << "FAILED" << endl;
        return 5;
    }else cout << "OK" << endl;


    // allegro - TIMER
    cout << " - create timer ... ";
    timer = al_create_timer(1.0 / 60); // 60 ticks a second
    if(!timer) {
        cout << "FAILED" << endl;
        return 6;
    }else cout << "OK" << endl;


    // allegro - EVENTS
    cout << " - create event_queue ... ";
    event_queue = al_create_event_queue();
    if(!event_queue) {
        cout << "FAILED" << endl;
        return 7;
    }else cout << "OK" << endl;



    // allegro - screen
    cout << " - create screen ... ";
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    screen = al_create_display(config::instance()->resX, config::instance()->resY);
    if(!screen) {
        cout << "FAILED" << endl;
        return 8;
    }else cout << "OK" << endl;


    // register events
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(screen));


    al_start_timer(timer);

    gameFont = al_load_ttf_font("data/times.ttf",14,0 );

    // load recources
    gameInterface->load();
    gameWorld->load();


//    gfx::instance()->init(1, "/home/xuedi/projects/slapEngine/movida/data/gfx/"); // loads sfNone.bmp ad default !!
//    gfx::instance()->load("sfSlap.bmp");

    gameHadInit = 1;

    return 0;

}


bool movida::run() {

    if(!gameHadInit) return 1;
    cout << "starting" << endl;



    // prepare
    al_clear_to_color(al_map_rgb(0,0,0));



    // loop
    while(!gameExit) {

        ALLEGRO_EVENT event;

        // keep the CPU idle :-)
        al_wait_for_event(event_queue, &event);

        // react to events
        switch( event.type ) {

            // new tick of 60 a second
            case ALLEGRO_EVENT_TIMER:
                tick();
            break;

            // handle the closing of the window
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameExit = true;
            break;

            // mouse was moved
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                status::instance()->mouseX = mouseX;
                status::instance()->mouseY = mouseY;
//                engine.eventMousePos( mouseX, mouseY );
            break;

            // in case the mouse moved
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                gameInterface->injectMouseClick(mouseLockedX, mouseLockedY);

                mouseLocked = 0;
                mouseLockedX= 0;
                mouseLockedY= 0;
                //check inf click or drag
            break;

            // in case the mouse moved
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouseLocked = 1;
                mouseLockedX=mouseX;
                mouseLockedY=mouseY;
            break;



            // get the keyboard keys
            case ALLEGRO_EVENT_KEY_DOWN:

                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        gameRedraw = true;
//                        engine.moveCenter(1,1);
                    break;

                    case ALLEGRO_KEY_DOWN:
                        gameRedraw = true;
//                        engine.moveCenter(-1,-1);
                    break;

                    case ALLEGRO_KEY_LEFT:
                        gameRedraw = true;
//                        engine.moveCenter(1,-1);
                    break;

                    case ALLEGRO_KEY_RIGHT:
                        gameRedraw = true;
//                        engine.moveCenter(-1,1);
                    break;

                    case ALLEGRO_KEY_ESCAPE:
                        gameExit = true;
                    break;

                }

            break;

        }

        // SCREEN - only redraw when nothing else to do
        if(gameRedraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw();
            al_flip_display();
            gameRedraw = false;
        }
    }


    return 0;

}


void movida::tickSecond() {
    gameRedraw = true;
}


void movida::tick() {

    frames++;
    if(frames>=60) {
        frames=0;
        tickSecond();
    }

    gameWorld->tick();
    gameInterface->tick();

    // react to stat changes
    if(status::instance()->shutDown) gameExit = true;
    if(status::instance()->singelRender) {
        gameRedraw = true;
        status::instance()->singelRender=0;
    }

}


void movida::draw() {
    gameWorld->draw();
    gameInterface->draw();

    al_draw_textf(gameFont, al_map_rgb(255,255,255), 10, 10,ALLEGRO_ALIGN_LEFT, "State: %i", status::instance()->gameState);
    al_draw_textf(gameFont, al_map_rgb(255,255,255), 10, 30,ALLEGRO_ALIGN_LEFT, "Mouse %i/%i", (int)mouseX, (int)mouseY );


}
