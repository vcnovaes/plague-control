#include <stdio.h>
#include <stdlib.h>
#include "libs/characters.h"
#include "libs/controles.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define width 960
#define height 672

ALLEGRO_DISPLAY *display = NULL; 
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
//const int y_vel = 3;

bool keys[4] = {false, false, false, false};

char * IMG_walk_jogador[4] = {
    "Graficos/medico/WALK/medico_walk_up.png",
    "Graficos/medico/WALK/medico_walk_down.png",
    "Graficos/medico/WALK/medico_walk_right.png",
    "Graficos/medico/WALK/medico_walk_left.png"
};
char * IMG_attack_jogador[4] = {
    "Graficos/medico/PUSH/medico_push_up.png",
    "Graficos/medico/PUSH/medico_push_down.png",
    "Graficos/medico/PUSH/medico_push_right.png",
    "Graficos/medico/PUSH/medico_push_left.png"
};
char * IMG_Soldado_Medieval[3]  ={
    "Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 sword 1.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 sword 2.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 axe.png"
    };
// para cada imagem ---> height = 52  
////////            ---> width = 196


/// Enum  para ser usado no switch para indentificar graficos gerar
enum Fase{Fase1, Fase2, Fase3};
enum STATE {FASE1, FASE2, FASE3, MENU, PAUSA, INSTRUCOES, CREDITOS, GAME_OVER};

//Mapas
int mapFase1[21][30] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int mapFase2[21][30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int mapFase3[21][30] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

PERSONAGEM jogador;

const int n_soldados_medievais = 9;  // numero de soldados medievais

/// A função cria os soldados medievais, configurndo suas structs;
///
SOLDADO_MEDIEVAL  *Soldado_medieval;

int initAllegro() {
    // Initialize allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro.\n");
        return 1;
    }

    // Initialize the timer
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "Failed to create timer.\n");
        return 1;
    }

    // Create the display
    display = al_create_display(width,height);
    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return 1;
    }

    // Create the event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue.");
        return 1;
    }
    // Initializing keyboard
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    // Register event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // inicializing player
    Criar_Personagem(&jogador,IMG_walk_jogador, IMG_attack_jogador, 22,22);
    Personagem_SetFrames(&jogador,4,32,32);
    Criar_Soldado_Medieval(&Soldado_medieval,n_soldados_medievais,IMG_Soldado_Medieval);
    return 0;
}

int main(int argc, char *argv[]) {
    int err = initAllegro();
    if(err){
        return err;
    }
    double marcadorDeTempo = 0;
    int time = 0;
    bool running = true;
    bool redraw = true;
    int times_of_attack_enemy = 0;
    int times_of_attack_player = 20;
    int Fase = Fase1;
    int estado_atual = -1;
    POSICAO ultima_posicao_plyr;

    ALLEGRO_BITMAP *background = NULL;                                             
    ALLEGRO_FONT *fonte_start = NULL;
    ALLEGRO_FONT *fonte_logo = NULL;
    ALLEGRO_FONT *fonte_creditos = NULL;
    ALLEGRO_SAMPLE *somFundo = NULL;
    ALLEGRO_SAMPLE_INSTANCE *somFundoInstance = NULL;
    ALLEGRO_BITMAP *Mapas[3];
    ALLEGRO_BITMAP *tela_game_over = NULL;
    ALLEGRO_BITMAP *tela_creditos = NULL;
    ALLEGRO_BITMAP *tutorial = NULL;

    //Initializing
    al_install_audio();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_reserve_samples(1);   

    //Loading
    Mapas[0] = al_load_bitmap("Graficos/Mapas/Fase 1/mapa_fase1_final.png");
    Mapas[1] = al_load_bitmap("Graficos/Mapas/Fase 2/mapa_fase2_final.png");
    Mapas[2] = al_load_bitmap("Graficos/Mapas/Fase 3/mapa_fase3_final.png");
    fonte_start = al_load_font("Graficos/Menu Inicial/fonte_menu_inicial.ttf", 36, 0);
    //if(fonte_start == NULL)exit(-1);
    fonte_logo = al_load_font("Graficos/Menu Inicial/Base 02.ttf", 88, 0);
    fonte_creditos = al_load_font("Graficos/Menu Inicial/fonte_menu_inicial.ttf", 30, 0);
    somFundo = al_load_sample("Graficos/Menu Inicial/NDKG_CreepyAtmosphere_Reg.wav");
    background = al_load_bitmap("Graficos/Menu Inicial/menu_inicial_background.jpeg");
    tela_game_over = al_load_bitmap("Graficos/Menu Inicial/game_over.jpeg");
    tela_creditos = al_load_bitmap("Graficos/Menu Inicial/tela_creditos.jpeg");
    tutorial = al_load_bitmap("Graficos/Menu Inicial/instrucoes.jpeg");

    //Creating
    somFundoInstance = al_create_sample_instance(somFundo);

    //Configurando musica de fundo
    al_set_sample_instance_playmode(somFundoInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(somFundoInstance, al_get_default_mixer());

    //Colocando a musica para tocar
    al_play_sample_instance(somFundoInstance);

    //Inicializando o estado atual como o menu
    estado_atual = MENU;
    
    // Start the timer
    al_start_timer(timer); //Nao colocar nada entre essa linha de codigo e o while

    // Game loop
    while(running) {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;
        
        // Initialize timeout
        al_init_timeout(&timeout, 0.06);
        // Fetch the event (if one exists)
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

        if(estado_atual == MENU){
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_text(fonte_logo, al_map_rgb(255, 0, 0), width/2, height/6, ALLEGRO_ALIGN_CENTRE, "PLAGUE CONTROL");
            if(time < 15){                                                                                                                  //fazer o texto "piscar"
                al_draw_text(fonte_start, al_map_rgb(255, 255, 255), width/2, height/2.5, ALLEGRO_ALIGN_CENTRE, "PRESS SPACE TO START");
            }
            al_draw_text(fonte_creditos, al_map_rgb(255, 255, 255), width/2, height/2, ALLEGRO_ALIGN_CENTRE, "PRESS X TO SEE HOW TO PLAY");
            al_draw_text(fonte_creditos, al_map_rgb(255, 255, 255), width/2, height/1.7, ALLEGRO_ALIGN_CENTRE, "PRESS S TO SEE CREDITS");
            al_flip_display();
            if(time > 30) time = 0;
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:
                        switch (event.keyboard.keycode)
                        {
                        case ALLEGRO_KEY_SPACE:       //se o usuario pressionar espaco, comecar o jogo 
                            estado_atual = FASE1;
                            break;
                        case ALLEGRO_KEY_S:           //se o usuario pressionar a tecla S, mostrar os creditos
                            estado_atual = CREDITOS;
                            break;
                        case ALLEGRO_KEY_X:           //se o usuario pressionar a tecla S, mostrar as instrucoes
                            estado_atual = INSTRUCOES;
                            break;
                        default:
                            break;
                        }
                      break;
                    
                }
            }
        }
        else if(estado_atual == INSTRUCOES){
            al_draw_bitmap(tela_game_over, 0, 0, 0); //provisoria
            al_flip_display();
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:       //se o usuario pressionar espaco, voltar para o menu inicial
                        switch (event.keyboard.keycode){
                            case ALLEGRO_KEY_SPACE:
                                estado_atual = MENU;
                                break;
                            default:
                                 break;
                        }       
                }
            }
        }
        else if(estado_atual == GAME_OVER){
            al_draw_bitmap(tela_game_over, 0, 0, 0);
            al_flip_display();
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = false;
                        break;
                    
                    case ALLEGRO_EVENT_KEY_DOWN:       //se o usuario pressionar espaco, recomecar o jogo
                        switch (event.keyboard.keycode)
                        {
                        case ALLEGRO_KEY_SPACE:
                            estado_atual = FASE1;
                            break;
                        default:
                            break;
                        }
                            
                }
            }
        }
        else if(estado_atual == CREDITOS){
            al_draw_bitmap(tela_creditos, 0, 0, 0);
            al_flip_display();
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = true;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:       //se o usuario pressionar espaco, voltar para o menu inicial
                            switch (event.keyboard.keycode)
                            {
                            case ALLEGRO_KEY_SPACE:
                                estado_atual = MENU;
                                break;
                            
                            default:
                                break;
                            }

                }
            }
        }
        else if(estado_atual == FASE1){
            al_draw_bitmap(Mapas[0], 0, 0, 0);
            al_draw_textf(fonte_creditos, al_map_rgb(255, 0, 0), 40, 20, ALLEGRO_ALIGN_LEFT, "Vidas: %d", jogador.vida);
            al_flip_display();

            // Handle the event
            if (get_event) {
                switch (event.type) {
                    case ALLEGRO_EVENT_TIMER:
                        redraw = true;
                        break;
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:
                        switch(event.keyboard.keycode)
                        {
                            case ALLEGRO_KEY_UP:
                                
                                jogador.Acao = Walk;
                                jogador.CurrentDir = North;
                                
                                keys[UP] = true;
                            
                            break;
                            
                            case ALLEGRO_KEY_DOWN:
                                jogador.Acao = Walk;
                                jogador.CurrentDir = South;
                                
                                keys[DOWN] = true;
                            break;
                            case ALLEGRO_KEY_LEFT:
                                jogador.Acao = Walk;
                                jogador.CurrentDir = West;
                                
                                keys[LEFT] = true;
                            break;
                            case ALLEGRO_KEY_RIGHT:
                                jogador.Acao = Walk;
                                jogador.CurrentDir = East;
                                
                                keys[RIGHT] = true;
                            break;

                            case ALLEGRO_KEY_Z:
                                jogador.Acao = Attack;
                                times_of_attack_player = 80;
                                break;
                        }
                        break;
                    case ALLEGRO_EVENT_KEY_UP:
                        switch(event.keyboard.keycode)
                        {
                            case ALLEGRO_KEY_UP:
                                keys[UP] = false;
                            break;
                            case ALLEGRO_KEY_DOWN:
                                keys[DOWN] = false;
                            break;
                            case ALLEGRO_KEY_LEFT:
                                keys[LEFT] = false;
                            break;
                            case ALLEGRO_KEY_RIGHT:
                                keys[RIGHT] = false;
                            break;
                            }
                        
                        jogador.Acao = Nothing;
                        break;

                    default:
                        //jogador.Acao = Nothing;
                        fprintf(stderr, "Unsupported event received: %d\n", event.type);
                        break;
                }
            }
            if(event.type == ALLEGRO_EVENT_TIMER){
            // Check if we need to redraw
            if (redraw && al_is_event_queue_empty(event_queue)) {
                // Redraw
                int posicao_jogador = (Display_WIDTH - 50)/2; // aqui vai ficar a posição do jogador
                al_clear_to_color(al_map_rgb(125, 205, 0 ));

                al_draw_bitmap(Mapas[0],0,0,0);
                if(jogador.Acao ==  Walk){
                            Personagem_AtualizarPosicao(&jogador,keys, mapFase1);
                            al_draw_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],
                                    jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                                    jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0); 
                        }
                        //code
                        if( jogador.Acao ==  Attack || times_of_attack_player > 0){
                            Personagem_AtualizarPosicao(&jogador,keys,mapFase1);
                            al_draw_bitmap_region(jogador.imagem_ataque[jogador.CurrentDir],
                                    jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                                    jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0);
                            times_of_attack_player--; 
                            //printf("%d  - %d\n", times_of_attack_player, jogador.frames.currentFrame);
                        }
                        else{    
                        al_draw_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],
                                    jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                                    jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0); 
                        }
                        //MudarFrame_Personagem(&jogador,128);
                        ultima_posicao_plyr = jogador.pos;
                        

                switch (Fase){
                    case Fase1:
                            
                            //Soldados Medievais
                            for(int i = 0 ; i < n_soldados_medievais ; i++)
                            {   // int timing = (al_get_time() - marcadorDeTempo) + timing;  
                                bool hitted = false;
                                /// esse if verifica o intervalo para mudar de frame 
                                // esse numero esquisito ai é o intervalo
                                //printf("\n%lf",(timing));
                                if((al_get_time() - marcadorDeTempo) > 0.03169 || marcadorDeTempo == 0){    
                                    //timing = 0;
                                    if(!Soldado_medieval[i].dir && (Soldado_medieval[i].pos.x < posicao_jogador) 
                                    && Soldado_medieval[i].action == sm_walk){
                                        Soldado_medieval[i].pos.x += Soldado_medieval[i].pos.dx;
                                    }else if(Soldado_medieval[i].dir == 1 && Soldado_medieval[i].pos.x > 0 && 
                                        Soldado_medieval[i].action == sm_walk){
                                    Soldado_medieval[i].pos.x -= Soldado_medieval[i].pos.dx;
                                    }else if(Soldado_medieval[i].action == sm_walk){
                                        Soldado_medieval[i].dir = !Soldado_medieval[i].dir;
                                    }
                                    Soldado_medieval[i].sprite.curr_Y = Soldado_medieval[i].sprite.Height * Soldado_medieval[i].action;
                                    if((Soldado_medieval[i].sprite.curr_X + Soldado_medieval[i].sprite.Width )< 448
                                        && Soldado_medieval[i].action != sm_death){
                                        Soldado_medieval[i].sprite.curr_X += Soldado_medieval[i].sprite.Width;
                                    }else{
                                    Soldado_medieval[i].sprite.curr_X  = 0;
                                    }
                                    if(Soldado_medieval[i].pos.x == posicao_jogador){
                                        Soldado_medieval[i].action = sm_attack;
                                        times_of_attack_enemy += 1;
                                    }
                                    /// isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 100){
                                        Soldado_medieval[i].action = sm_walk;
                                    }
                                    // a part e da morte não está funcionando muito bem
                                    if(Soldado_medieval[i].vida  <= 0){
                                        Soldado_medieval[i].action = sm_death;
                                    }
                                    if(Soldado_medieval[i].action == sm_death){
                                        Soldado_medieval[i].sprite.curr_Y = 3;
                                        Soldado_medieval[i].sprite.curr_X = 192;
                                    }
                                    
                                        //Soldado_medieval[i].action= sm_death;  
                                    if(Soldado_medieval[i].pos.x > 10 && Soldado_medieval[i].pos.x < 12 ){
                                        hitted = true;
                                    }
                                    
                            
                                //printf("EM Y_IMG %d X_IMG %d\n", Soldado_medieval[i].sprite.curr_Y, Soldado_medieval[i].sprite.curr_X);
                            }
                            if(!Soldado_medieval[i].hitted){
                                al_draw_bitmap_region(Soldado_medieval[i].sprite.Imagem,
                                Soldado_medieval[i].sprite.curr_X,Soldado_medieval[i].sprite.curr_Y,
                                Soldado_medieval[i].sprite.Width, Soldado_medieval[i].sprite.Height,
                                Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y,
                                Soldado_medieval[i].dir);
                            }
                        }  
                        break;
                case Fase2:
                    break;

                default:
                    break;
                }
                
                al_flip_display();
                marcadorDeTempo= al_get_time();
                redraw = false;
                
                }
            }
        }
    } 

    // Clean up
    free(Soldado_medieval);
    for(int i = 0; i < 3; i++)
        al_destroy_bitmap(Mapas[i]);
    al_destroy_bitmap(tutorial);
    al_destroy_bitmap(tela_game_over);
    al_destroy_bitmap(tela_creditos);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample_instance(somFundoInstance);
    al_destroy_font(fonte_start);
    al_destroy_font(fonte_logo);
    al_destroy_font(fonte_creditos);
    al_destroy_sample(somFundo);
    al_destroy_bitmap(background);

    return 0;
}
