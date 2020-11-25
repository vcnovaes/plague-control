#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define FPS 60
#define width 960
#define height 672

//Por enquanto, a tela inicial está com uma imagem aleatoria de fundo até Edson fazer uma arte pro menu inicial

int main(){
    int time = 0;                                                                   //variavel para fazer o botao de start piscar no menu
    bool done = false, redraw = true;
    int pos_x = width / 2, pos_y = height / 2;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *background = NULL;                                             
    ALLEGRO_FONT *fonte_start = NULL;
    ALLEGRO_FONT *fonte_logo = NULL;
    ALLEGRO_FONT *fonte_creditos = NULL;
    ALLEGRO_SAMPLE *somFundo = NULL;
    ALLEGRO_SAMPLE *efeito_click = NULL;
    ALLEGRO_SAMPLE_INSTANCE *somFundoInstance = NULL;

    if(!al_init()){
        fprintf(stderr, "Failed to initialize allegro.\n");
        return -1;
    }

    display = al_create_display(width, height);

    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return 1;
    }

    //Inicializando o que sera usado
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_reserve_samples(2);                                                          //saber quantos efeitos estao sendo usados
    

    //Loading
    fonte_start = al_load_font("fonte_menu_inicial.ttf", 36, 0);
    fonte_logo = al_load_font("Base 02.ttf", 88, 0);
    fonte_creditos = al_load_font("fonte_menu_inicial.ttf", 30, 0);
    efeito_click = al_load_sample("efeito_sonoro_click.wav");
    somFundo = al_load_sample("NDKG_CreepyAtmosphere_Reg.wav");
    background = al_load_bitmap("nymburk-rampart.jpg");


    //Creating
    somFundoInstance = al_create_sample_instance(somFundo);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    //Configurando musica de fundo
    al_set_sample_instance_playmode(somFundoInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(somFundoInstance, al_get_default_mixer());

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    //Colocando a musica para tocar
    //al_play_sample_instance(somFundoInstance);

    al_start_timer(timer);
    while(!done){
        time++;
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //fechar o programa
            done = true;
        }
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_text(fonte_logo, al_map_rgb(255, 0, 0), width/2, height/4, ALLEGRO_ALIGN_CENTRE, "PLAGUE CONTROL");

        if(time < 10){
            al_draw_text(fonte_start, al_map_rgb(255, 255, 255), width/2, height/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
        }

        al_draw_text(fonte_creditos, al_map_rgb(255, 255, 255), width/2, height/1.65, ALLEGRO_ALIGN_CENTRE, "CREDITOS");
        al_flip_display();
        if(time > 20) time = 0;

        //Quando clicar em start
            //al_play_sample(efeito_click, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    al_destroy_sample_instance(somFundoInstance);
    al_destroy_font(fonte_start);
    al_destroy_font(fonte_logo);
    al_destroy_font(fonte_creditos);
    al_destroy_display(display);
    al_destroy_sample(somFundo);
    al_destroy_sample(efeito_click);
    al_destroy_bitmap(background);

    return 0;
}
