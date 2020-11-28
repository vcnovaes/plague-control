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
char *IMG_Soldado_Militares_RUN[4] = {
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/WALK/SMS_Soldier_WALK_NORTH_strip4.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/WALK/SMS_Soldier_WALK_SOUTH_strip4.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/WALK/SMS_Soldier_WALK_WEST_strip4.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/WALK/SMS_Soldier_WALK_EAST_strip4.png"
};
char *IMG_Soldado_Militares_Attack[4] = {
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/ATTACK KICK single frames/NES_Soldier_ATTACKKICK_NORTH.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/ATTACK KICK single frames/NES_Soldier_ATTACKKICK_SOUTH.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/ATTACK KICK single frames/NES_Soldier_ATTACKKICK_WEST.png",
    "Graficos/Pixel_Art_Gamejam/Fase 2/Soldado_Movements/ATTACK KICK single frames/NES_Soldier_ATTACKKICK_EAST.png"
};
char *IMG_inimigos_fase3[2] = {
    "Graficos/Pixel_Art_Gamejam/Fase 3/coronavirus-walk-redim.png",
    "Graficos/Pixel_Art_Gamejam/Fase 3/Bat 32x32.png"
};

char *Boss_Walk_Fase2[4] = {
    "Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/RUN/general_RUN_NORTH_strip4.png", 
    "Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/RUN/general_RUN_SOUTH_strip4.png", 
    "Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/RUN/general_RUN_WEST_strip4.png", 
    "Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/RUN/general_RUN_EAST_strip4.png", 
};
char *Boss_Attack_Fase2[4] = {
        "Plague-Control/Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/ATTACK KICK  single frames/general_ATTACKKICK_NORTH.png",
        "Plague-Control/Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/ATTACK KICK  single frames/general_ATTACKKICK_SOUTH.png",
        "Plague-Control/Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/ATTACK KICK  single frames/general_ATTACKKICK_WEST.png",
        "Plague-Control/Graficos/Pixel_Art_Gamejam/Fase 2/GENERAL/ATTACK KICK  single frames/general_ATTACKKICK_EAST.png",
};

char *Boss_Walk_Fase3[2] = {
        "Graficos/Pixel_Art_Gamejam/Fase 3/Presidente/presidente_run_left.png",
        "Graficos/Pixel_Art_Gamejam/Fase 3/Presidente/presidente_run_right.png"
};
char *Boss_Attack_Fase3[2] = {
    "Graficos/Pixel_Art_Gamejam/Fase 3/Presidente/presidente_punch_left.png",
    "Graficos/Pixel_Art_Gamejam/Fase 3/Presidente/presidente_punch_right.png"   
};
/// NECESSARIO JUNTAR TODAS AS IMAGENS NUMA SÒ , COMO O SPRITE PADRÃO
char *Boss_Walk_Left_Fase1[8] = {
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_1.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_2.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_3.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_4.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_5.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_6.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_7.png",
    "Graficos/Pixel_Art_Gamejam/Fase 1/PRIEST-WALK-LEFT/padre_walk_left_8.png",
};



// para cada imagem ---> height = 52  
////////            ---> width = 196


/// Enum  para ser usado no switch para indentificar graficos gerar
enum Fase {Fase1 = 0, Fase2, Fase3};
enum STATE {FASE1, FASE2, FASE3, MENU, CREDITOS, GAME_OVER};

//Mapas

int bit_map_Fase1[21][30] = {
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
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
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

int bit_map_Fase2[21][30] = {
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

int bit_map_Fase3[21][30] = {
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
// UNIFICANDO TODOS OS BITMAPS EM UM SÒ ARRAY FICA MAIS FACIL PASSAR COMO ARGUMENTO 

int BitMaps[3][21][30] = {
    {
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
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
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
},
{
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
},
{
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
}


};


PERSONAGEM jogador;

int n_soldados_medievais = 0;  // numero de soldados medievais
int n_soldados_militares = 1;
int n_inimigos = 30;
/// A função cria os soldados medievais, configurndo suas structs;
///
SOLDADO_MEDIEVAL  *Soldado_medieval = NULL, *Soldado_militar = NULL, *Inimigos_fase3 = NULL, 
        Boss_fase1, Boss_fase2, Presidente; 

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
    Criar_Personagem(&jogador,IMG_walk_jogador, IMG_attack_jogador, 466,571);
    Personagem_SetFrames(&jogador,4,32,32);
    Criar_Soldado_Medieval(&Soldado_medieval,n_soldados_medievais,IMG_Soldado_Medieval, bit_map_Fase1);
    Criar_Soldado_Militar(&Soldado_militar, n_soldados_militares,
                            IMG_Soldado_Militares_RUN, IMG_Soldado_Militares_Attack, bit_map_Fase2);
    Criar_InimigosFase3(&Inimigos_fase3,n_inimigos,IMG_inimigos_fase3,bit_map_Fase3);
    Criar_BossFase2(&Boss_fase2,Boss_Walk_Fase2,Boss_Attack_Fase2,bit_map_Fase2);
    Criar_BossFase3(&Presidente,Boss_Walk_Fase3,Boss_Attack_Fase3,bit_map_Fase3);
    return 0;
}

int main(int argc, char *argv[]) {
    int err = initAllegro();
    if(err){
        return err;
    }
    double marcadorDeTempo = 0;
    int time = 0; // Comentado no live share
    bool entrouFase1 = false, entrouFase2 = false, entrouFase3 = false, passouFase1 = false, passouFase2 = false, passouFase3 = false;
    bool running = true;
    bool redraw = true;
    int times_of_attack_enemy = 0;
    int times_of_attack_player = 20;
    int Fase = Fase2;
    int vzs_atingido = 0;
    int estado_atual = -1;
    POSICAO curr_posicao_plyr;

    ALLEGRO_FONT *fonte_creditos = NULL;
    ALLEGRO_SAMPLE *somFundo = NULL;
    ALLEGRO_SAMPLE_INSTANCE *somFundoInstance = NULL;
    ALLEGRO_BITMAP *Mapas[3];
    ALLEGRO_BITMAP *background = NULL;  
    ALLEGRO_FONT *fonte_start = NULL;
    ALLEGRO_FONT *fonte_logo = NULL;
    ALLEGRO_BITMAP *tela_game_over = NULL;
    ALLEGRO_BITMAP *tela_creditos = NULL;
    ALLEGRO_BITMAP *tutorial = NULL;
    ALLEGRO_BITMAP *telasAdicionais[5];

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
    telasAdicionais[0] = al_load_bitmap("Graficos/Pixel_Art_Gamejam/telasFases/tela_pre_fase1.jpeg");
    telasAdicionais[1] = al_load_bitmap("Graficos/Pixel_Art_Gamejam/telasFases/tela_pos_fase1.jpeg");
    telasAdicionais[2] = al_load_bitmap("Graficos/Pixel_Art_Gamejam/telasFases/tela_pre_fase2.jpeg");
    telasAdicionais[3] = al_load_bitmap("Graficos/Pixel_Art_Gamejam/telasFases/tela_pre_fase3.jpeg");
    telasAdicionais[4] = al_load_bitmap("Graficos/Pixel_Art_Gamejam/telasFases/tela_vitoria.jpeg");

    //Creating
    somFundoInstance = al_create_sample_instance(somFundo);

    //Configurando musica de fundo
    al_set_sample_instance_playmode(somFundoInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(somFundoInstance, al_get_default_mixer());

    //Colocando a musica para tocar
    //al_play_sample_instance(somFundoInstance);

    //Inicializando o estado atual como o menu
    estado_atual = MENU;
    
    // Start the timer
    al_start_timer(timer); //Nao colocar nada entre essa linha de codigo e o while

    // Game loop
    while(running){
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;
            
        // Initialize timeout
        al_init_timeout(&timeout, 0.06);
        // Fetch the event (if one exists)
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

        if(estado_atual == MENU){
            entrouFase1 = entrouFase2 = entrouFase3 = passouFase1 = passouFase2 = passouFase3 = false; //zerar as fases
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_text(fonte_logo, al_map_rgb(255, 0, 0), width/2, height/6, ALLEGRO_ALIGN_CENTRE, "PLAGUE CONTROL");
            if(time < 15){                                                                                                                  //fazer o texto "piscar"
                al_draw_text(fonte_start, al_map_rgb(255, 255, 255), width/2, height/2.5, ALLEGRO_ALIGN_CENTRE, "PRESS SPACE TO START");
            }
            al_draw_text(fonte_creditos, al_map_rgb(255, 255, 255), width/2, height/2, ALLEGRO_ALIGN_CENTRE, "PRESS S TO SEE CREDITS");
            al_flip_display();
            if(time > 30) time = 0;
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:
                        switch (event.keyboard.keycode){
                            case ALLEGRO_KEY_SPACE:       //se o usuario pressionar espaco, comecar o jogo 
                                estado_atual = FASE1;
                                break;
                            case ALLEGRO_KEY_S:           //se o usuario pressionar a tecla S, mostrar os creditos
                                estado_atual = CREDITOS;
                                break;
                            default:
                                break;
                        }
                    break;
                }
            }
        }
        else if(estado_atual == GAME_OVER){
            entrouFase1 = entrouFase2 = entrouFase3 = passouFase1 = passouFase2 = passouFase3 = false; //zerar as fases
            al_draw_bitmap(tela_game_over, 0, 0, 0);
            al_flip_display();
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:       //se o usuario pressionar espaco, recomecar o jogo
                        switch (event.keyboard.keycode){
                            case ALLEGRO_KEY_SPACE:
                                estado_atual = FASE1;
                                break;
                            default:
                                break;
                        }
                    default:
                        break;        
                }
            }
        }
        else if(estado_atual == CREDITOS){
            entrouFase1 = entrouFase2 = entrouFase3 = passouFase1 = passouFase2 = passouFase3 = false; //zerar as fases
            al_draw_bitmap(tela_creditos, 0, 0, 0);
            al_flip_display();
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  //fechar o programa
                        running = true;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:       //se o usuario pressionar espaco, voltar para o menu inicial
                        switch (event.keyboard.keycode){
                            case ALLEGRO_KEY_SPACE:
                                estado_atual = MENU;
                                break;
                            default:
                                break;
                        }
                    default:
                        break;
                }
            }
        }
        else if(estado_atual == FASE1 || estado_atual == FASE2 || estado_atual == FASE3){
            //Apresentar as telas adicionais entre as fases
         /*   if(entrouFase1 == false){
                al_draw_bitmap(telasAdicionais[0], 0, 0, 0);
                al_flip_display();
                al_rest(5.0);
                entrouFase1 = true;
                Fase = Fase1;
            }
            if(entrouFase2 == false && passouFase1 == true){
                al_draw_bitmap(telasAdicionais[1], 0, 0, 0);
                al_flip_display();
                al_rest(5.0);
                al_draw_bitmap(telasAdicionais[2], 0, 0, 0);
                al_flip_display();
                al_rest(5.0);
                entrouFase2 = true;
                Fase = Fase2;
            }*/
            if(entrouFase3 == false && passouFase2 == true){
                al_draw_bitmap(telasAdicionais[3], 0, 0, 0);
                al_flip_display();
                al_rest(5.0);
                entrouFase3 = true;
                Fase = Fase3;
            }
            if(passouFase3 == true){ //Ganhou o jogo
                al_draw_bitmap(telasAdicionais[3], 0, 0, 0);
                al_flip_display();
                al_rest(5.0);
                estado_atual = CREDITOS; //se acabar o jogo, mostra os creditos
            }
            al_draw_bitmap(Mapas[Fase], 0, 0, 0);
            //al_flip_display();

            // Handle the event
            if(get_event){
                switch(event.type){
                    case ALLEGRO_EVENT_TIMER:
                        redraw = true;
                        break;
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        running = false;
                        break;
                    case ALLEGRO_EVENT_KEY_DOWN:
                        switch(event.keyboard.keycode){
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
                                times_of_attack_player = 5;
                                break;
                        }
                        break;
                    case ALLEGRO_EVENT_KEY_UP:
                        switch(event.keyboard.keycode){
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
            int ult_pos_ataque_x = -1; //saber as coordenadas de onde aconteceu o ataque do personagem
            int ult_pos_ataque_y = -1;
            if(event.type == ALLEGRO_EVENT_TIMER){
                // Check if we need to redraw
                if(redraw && al_is_event_queue_empty(event_queue)){
                    // Redraw
                    //int posicao_jogador = (Display_WIDTH - 50)/2; // aqui vai ficar a posição do jogador
                    al_clear_to_color(al_map_rgb(125, 205, 0 ));

                    al_draw_bitmap(Mapas[Fase], 0, 0, 0);
                    // ALLEGRO_BITMAP * f1 = al_load_bitmap("Graficos/Pixel_Art_Gamejam/Fase 1/Padre/PRIEST-WALK4.gif");
                    // al_draw_bitmap(f1, 0, 0,0);

                    if(jogador.Acao ==  Walk){
                        Personagem_AtualizarPosicao(&jogador,keys, BitMaps[Fase]);
                        al_draw_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],
                        jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                        jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0); 
                    }
                    //code
                    if(jogador.Acao ==  Attack || times_of_attack_player > 0){
                        al_draw_bitmap_region(jogador.imagem_ataque[jogador.CurrentDir],
                        jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                        jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0);
                        times_of_attack_player--; 
                        //printf("%d  - %d\n", times_of_attack_player, jogador.frames.currentFrame);
                        //Saber a posicao do personagem quando atacou o inimigo, os 32's sao para ajustar
                        //de acordo com o tamanho da imagem do medico (32x32)
                        if(jogador.CurrentDir == East){
                            ult_pos_ataque_x = jogador.pos.x + 32;
                            ult_pos_ataque_y = jogador.pos.y;
                        }
                        else if(jogador.CurrentDir == West || jogador.CurrentDir == North){
                            ult_pos_ataque_x = jogador.pos.x;
                            ult_pos_ataque_y = jogador.pos.y;
                        }
                        else if(jogador.CurrentDir == South){
                            ult_pos_ataque_x = jogador.pos.x;
                            ult_pos_ataque_y = jogador.pos.y + 32;
                        }
                    }
                    else {    
                        al_draw_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],
                        jogador.frames.currentFrame, 0, jogador.frames.w_Frame,
                        jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0); 
                    }

                    //MudarFrame_Personagem(&jogador,128);  
                    bool vivo = true;
                    bool hitted = false;
                    int qtd_vivo = 0;
                    curr_posicao_plyr = jogador.pos;

                    switch(Fase){
                        case Fase1:
                        //Soldados Medievais
                        for(int i = 0 ; i < n_soldados_medievais ; i++){
                            //Se o soldado estiver no range, perde uma vida
                            hitted = false;
                            if(jogador.Acao == Attack && Esta_nas_proximidades(Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y, jogador.pos.x, jogador.pos.y, 20)){
                                hitted = true;
                                /// Soldado_medieval[i].vida--;
                            }

                            // int timing = (al_get_time() - marcadorDeTempo) + timing;  
                            // esse if verifica o intervalo para mudar de frame 
                            // esse numero esquisito ai é o intervalo
                            //printf("\n%lf",(timing));
                            // checando se soldado ta vivo
                            vivo = true;
                            if(Soldado_medieval[i].vida <= 0){ 
                                vivo = false;
                            }
                            else {
                                qtd_vivo++;
                            }
                            if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0 && vivo)){
                                //timing = 0;
                                if(Soldado_medieval[i].dir == sm_direita && Soldado_medieval[i].action == sm_walk){
                                    if(!Existe_Obstaculo(Soldado_medieval[i].pos.x + Soldado_medieval[i].pos.dx + 32, Soldado_medieval[i].pos.y, bit_map_Fase1) && !HoraDoAtaque(Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y, curr_posicao_plyr)){
                                        //printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                        Soldado_medieval[i].pos.x += Soldado_medieval[i].pos.dx;
                                    }
                                    else{ 
                                        Soldado_medieval[i].dir = sm_esquerda;
                                    } 
                                }
                                if(Soldado_medieval[i].dir == sm_esquerda  && Soldado_medieval[i].action == sm_walk){
                                    if(!Existe_Obstaculo(Soldado_medieval[i].pos.x - Soldado_medieval[i].pos.dx, Soldado_medieval[i].pos.y, bit_map_Fase1) && (!HoraDoAtaque(Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y, curr_posicao_plyr))){ 
                                        //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                        Soldado_medieval[i].pos.x -= Soldado_medieval[i].pos.dx;
                                    }   
                                    else {
                                        //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                        Soldado_medieval[i].dir = sm_direita;
                                    }
                                }
                                Soldado_medieval[i].sprite.curr_Y = Soldado_medieval[i].sprite.Height * Soldado_medieval[i].action;
                                if((Soldado_medieval[i].sprite.curr_X + Soldado_medieval[i].sprite.Width) < 448 && (Soldado_medieval[i].action != sm_death)){
                                    Soldado_medieval[i].sprite.curr_X += Soldado_medieval[i].sprite.Width;
                                }
                                else{
                                    Soldado_medieval[i].sprite.curr_X  = 0;
                                }
                                if(HoraDoAtaque(Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y,curr_posicao_plyr)){
                                    printf("\nHora de atacar \n");
                                    Soldado_medieval[i].action = sm_attack;
                                    if(Soldado_medieval[i].pos.x < curr_posicao_plyr.x){
                                        Soldado_medieval[i].dir = sm_direita; 
                                        //if(!Existe_Obstaculo(curr_posicao_plyr.)
                                    }
                                    else{
                                        Soldado_medieval[i].dir = sm_esquerda;
                                    }
                                    times_of_attack_enemy += 1;
                                    if(Esta_nas_proximidades(jogador.pos.x,jogador.pos.y,Soldado_medieval[i].pos.x,Soldado_medieval[i].pos.y,16)){
                                        vzs_atingido++;
                                        if(vzs_atingido > 20){
                                            jogador.vida--;
                                            vzs_atingido = 0;
                                            al_draw_tinted_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],al_map_rgb(135,0,0), jogador.frames.currentFrame, 0, jogador.frames.w_Frame, jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0);
                                        }
                                    }
                                    else{
                                        vzs_atingido = 0;
                                    }
                                }
                                else {
                                    Soldado_medieval[i].action = sm_walk;
                                }
                                // isso meio que  ta mensurando o tempo de ataque
                                if(times_of_attack_enemy > 20){
                                    printf("\n%d \n",times_of_attack_enemy);
                                    printf("\nO ataque parou\n");
                                    Soldado_medieval[i].action = sm_walk;
                                    times_of_attack_enemy  = 0;
                                }
                                //Soldado_medieval[i].action= sm_death; 
                                //printf("EM Y_IMG %d X_IMG %d\n", Soldado_medieval[i].sprite.curr_Y, Soldado_medieval[i].sprite.curr_X);
                            }
                            if(vivo){
                            // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                            //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y);     
                                if(hitted){
                                    al_draw_bitmap_region(Soldado_medieval[i].sprite.Imagem,
                                                        Soldado_medieval[i].sprite.curr_X,Soldado_medieval[i].sprite.curr_Y,
                                                        Soldado_medieval[i].sprite.Width, Soldado_medieval[i].sprite.Height,
                                                        Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y,
                                                        (Soldado_medieval[i].dir == sm_direita)? 0 : 1);
                                    Soldado_medieval[i].vida--;
                                    al_draw_tinted_bitmap_region(Soldado_medieval[i].sprite.Imagem,al_map_rgb(135,0,0),
                                                            Soldado_medieval[i].sprite.curr_X, 0, Soldado_medieval[i].sprite.Width,
                                                            Soldado_medieval[i].sprite.Height, Soldado_medieval[i].pos.x, 
                                                            Soldado_medieval[i].pos.y, 0);
                                    hitted = false;
                                }
                                else{
                                    al_draw_bitmap_region(Soldado_medieval[i].sprite.Imagem,
                                                    Soldado_medieval[i].sprite.curr_X,Soldado_medieval[i].sprite.curr_Y,
                                                    Soldado_medieval[i].sprite.Width, Soldado_medieval[i].sprite.Height,
                                                    Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y,
                                                    (Soldado_medieval[i].dir == sm_direita)? 0 : 1);
                                }    
                            }
                        }
                        if(!qtd_vivo){
                            //libera boss
                            hitted = false;
                            if(jogador.Acao == Attack && Esta_nas_proximidades(Boss_fase1.pos.x, Boss_fase1.pos.y, jogador.pos.x, jogador.pos.y, 20)){
                                hitted = true;
                            }
                            vivo = true;
                            if(Boss_fase1.vida <= 0){
                                vivo = false;
                                passouFase1 = true;
                            }
                            else qtd_vivo++;
                            if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0 && vivo)){
                                //timing = 0;
                                if(Boss_fase1.dir == sm_direita && Boss_fase1.action == sm_walk){
                                    if(!Existe_Obstaculo(Boss_fase1.pos.x + Boss_fase1.pos.dx + 32, Boss_fase1.pos.y, bit_map_Fase1) && !HoraDoAtaque(Boss_fase1.pos.x,Boss_fase1.pos.y, curr_posicao_plyr)){  
                                        // printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                        Boss_fase1.pos.x += Boss_fase1.pos.dx;
                                    }
                                    else{ 
                                        Boss_fase1.dir = sm_esquerda;
                                    } 
                                }
                                    if((Boss_fase1.dir == sm_esquerda  && Boss_fase1.action == sm_walk )){
                                        if(!Existe_Obstaculo(Boss_fase1.pos.x  - Boss_fase1.pos.dx, Boss_fase1.pos.y, bit_map_Fase1) && (!HoraDoAtaque(Boss_fase1.pos.x, Boss_fase1.pos.y, curr_posicao_plyr))){  
                                            //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                            Boss_fase1.pos.x -= Boss_fase1.pos.dx;
                                        }   
                                        else {
                                            //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                            Boss_fase1.dir = sm_direita;
                                        }
                                    }
                                    Boss_fase1.sprite.curr_Y = Boss_fase1.sprite.Height * Boss_fase1.action;
                                    if((Boss_fase1.sprite.curr_X + Boss_fase1.sprite.Width) < 64 && Boss_fase1.action == sm_walk){
                                        Boss_fase1.sprite.curr_X += Boss_fase1.sprite.Width;
                                    }
                                    else{
                                        Boss_fase1.sprite.curr_X  = 0;
                                    }
                                    if(HoraDoAtaque(Boss_fase1.pos.x, Boss_fase1.pos.y,curr_posicao_plyr)){  
                                        printf("\nHORA DE ATACAR\n");
                                        Boss_fase1.action = sm_attack;
                                        if(Boss_fase1.pos.x < curr_posicao_plyr.x){
                                            Boss_fase1.dir = sm_direita;
                                        }
                                        else{
                                            Boss_fase1.dir = sm_esquerda; // não recordo-me a direção original do sprite 
                                        }
                                        times_of_attack_enemy += 1;
                                    }
                                    //isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 20 && Boss_fase1.action == sm_attack){
                                        printf("\nParou o ataque\n");
                                        Boss_fase1.action = sm_walk;
                                        times_of_attack_enemy  = 0;
                                    }
                                    //Soldado_militar[i].action= sm_death;  
                                    //printf("EM Y_IMG %d X_IMG %d\n", Soldado_militar[i].sprite.curr_Y, Soldado_militar[i].sprite.curr_X);
                                }
                                if(vivo){
                                    if(hitted){
                                        // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                                        //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_militar[i].pos.x, Soldado_militar[i].pos.y);
                                        
                                      /*  al_draw_bitmap_region(Boss_fase1.sprite.Imagem_walk_EAST,
                                                                Boss_fase1.sprite.curr_X,Boss_fase1.sprite.curr_Y,
                                                                Boss_fase1.sprite.Width, Boss_fase1.sprite.Height,
                                                                Boss_fase1.pos.x, Boss_fase1.pos.y,
                                                                (Boss_fase1.dir == sm_direita)? 0 : 1);*/
                                        Boss_fase1.vida--;

                                        al_draw_tinted_bitmap_region(Boss_fase1.sprite.Imagem_walk_EAST,al_map_rgb(135,0,0),
                                                                    Boss_fase1.sprite.curr_X, 0, Boss_fase1.sprite.Width,
                                                                    Boss_fase1.sprite.Height, Boss_fase1.pos.x, 
                                                                    Boss_fase1.pos.y,(Boss_fase1.dir == sm_direita)? 0 : 1);
                                    }
                                else if(Boss_fase1.action == sm_attack){
                                    al_draw_bitmap_region(Boss_fase1.sprite.Imagem_attack_EAST,
                                                            Boss_fase1.sprite.curr_X = 0, Boss_fase1.sprite.curr_Y = 0,
                                                            Boss_fase1.sprite.Width, Boss_fase1.sprite.Height,
                                                            Boss_fase1.pos.x, Boss_fase1.pos.y,
                                                            (Boss_fase1.dir == sm_direita)? 1: 0);
                                    //al_rest(13.0);
                                }
                                n_soldados_medievais = 0;
                            }
                        } 
                        break; 

                        case Fase2:
                            qtd_vivo = 0;
                            for(int i = 0 ; i < n_soldados_militares ; i++){
                                // int timing = (al_get_time() - marcadorDeTempo) + timing;  
                                // esse if verifica o intervalo para mudar de frame 
                                // esse numero esquisito ai é o intervalo
                                hitted = false;
                                if(jogador.Acao == Attack && Esta_nas_proximidades(Soldado_militar[i].pos.x,
                                 Soldado_militar[i].pos.y, jogador.pos.x, jogador.pos.y, 23)){
                                    Soldado_militar[i].vida --;
                                    hitted = true;
                                }

                                vivo = true;
                                // wtf?
                                if(Soldado_militar[i].vida <= 0) vivo = false;
                                else qtd_vivo++;

                                if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0 && vivo)){
                                    //timing = 0;
                                    if(Soldado_militar[i].dir == sm_direita && Soldado_militar[i].action == sm_walk){
                                       if(!Existe_Obstaculo(Soldado_militar[i].pos.x + Soldado_militar[i].pos.dx + 32, 
                                         Soldado_militar[i].pos.y,bit_map_Fase2) && !HoraDoAtaque(Soldado_militar[i].pos.x,
                                         Soldado_militar[i].pos.y, curr_posicao_plyr)){ 
                                                // printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                                Soldado_militar[i].pos.x += Soldado_militar[i].pos.dx;
                                        }
                                        else{ 
                                            Soldado_militar[i].dir = sm_esquerda;
                                        } 
                                    }
                                    if((Soldado_militar[i].dir == sm_esquerda  && Soldado_militar[i].action == sm_walk )){
                                        if(!Existe_Obstaculo(Soldado_militar[i].pos.x  - Soldado_militar[i].pos.dx, Soldado_militar[i].pos.y,bit_map_Fase2) && (!HoraDoAtaque(Soldado_militar[i].pos.x, Soldado_militar[i].pos.y, curr_posicao_plyr))){
                                                //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                                Soldado_militar[i].pos.x -= Soldado_militar[i].pos.dx;
                                        }   
                                        else {
                                            //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                            Soldado_militar[i].dir = sm_direita;
                                        }
                                    }

                                    Soldado_militar[i].sprite.curr_Y = Soldado_militar[i].sprite.Height * Soldado_militar[i].action;

                                    if((Soldado_militar[i].sprite.curr_X + Soldado_militar[i].sprite.Width ) < 64 && Soldado_militar[i].action == sm_walk){
                                        Soldado_militar[i].sprite.curr_X += Soldado_militar[i].sprite.Width;
                                    }
                                    else{
                                        Soldado_militar[i].sprite.curr_X  = 0;
                                    }

                                    if(HoraDoAtaque(Soldado_militar[i].pos.x, Soldado_militar[i].pos.y,curr_posicao_plyr)){  
                                        printf("\nHORA DE ATACAR\n");
                                        Soldado_militar[i].action = sm_attack;
                                        if(Soldado_militar[i].pos.x < curr_posicao_plyr.x){
                                            Soldado_militar[i].dir = sm_direita;
                                        }
                                        else{
                                            Soldado_militar[i].dir = sm_esquerda; // não recordo-me a direção original do sprite 
                                        }
                                        if(Esta_nas_proximidades(jogador.pos.x,jogador.pos.y,Soldado_militar[i].pos.x,
                                            Soldado_militar[i].pos.y,23)){
                                            vzs_atingido++;
                                                if(vzs_atingido > 20){
                                                    jogador.vida--;
                                                    vzs_atingido = 0;
                                                    al_draw_tinted_bitmap_region(jogador.imagem_caminhar[jogador.CurrentDir],
                                                    al_map_rgb(135,0,0), jogador.frames.currentFrame, 0, jogador.frames.w_Frame, 
                                                    jogador.frames.h_Frame, jogador.pos.x, jogador.pos.y, 0);
                                                    if(!Existe_Obstaculo(jogador.pos.x - jogador.pos.dx, 
                                                      jogador.pos.y + jogador.pos.dy,bit_map_Fase2)){
                                                            jogador.pos.x -= 3;
                                                            jogador.pos.y += 3;
                                                      }
                                                    
                                                }
                                        }
                                        else{
                                            vzs_atingido = 0;
                                        }

                                        times_of_attack_enemy += 1;
                                        /// correção dos jogadores ficarem parados
                                    }else{
                                        Soldado_militar[i].action = sm_walk;
                                    }
                                    // isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 20 && Soldado_militar[i].action == sm_attack){
                                        printf("\nParou o ataque\n");
                                        Soldado_militar[i].action = sm_walk;
                                        times_of_attack_enemy  = 0;
                                    }
                                    // Soldado_militar[i].action= sm_death; 
                                    //printf("EM Y_IMG %d X_IMG %d\n", Soldado_militar[i].sprite.curr_Y, Soldado_militar[i].sprite.curr_X);
                                }
                                if(vivo){
                                    if(hitted){
                                        // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                                        //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_militar[i].pos.x, Soldado_militar[i].pos.y);
                                        /*al_draw_bitmap_region(Soldado_militar[i].sprite.Imagem_walk_EAST,
                                                                Soldado_militar[i].sprite.curr_X,Soldado_militar[i].sprite.curr_Y,
                                                                Soldado_militar[i].sprite.Width, Soldado_militar[i].sprite.Height,
                                                                Soldado_militar[i].pos.x, Soldado_militar[i].pos.y,
                                                                (Soldado_militar[i].dir == sm_direita)? 0 : 1);*/
                                        Soldado_militar[i].vida--;
                                        al_draw_tinted_bitmap_region(Soldado_militar[i].sprite.Imagem_walk_EAST,al_map_rgb(135,0,0),
                                                        Soldado_militar[i].sprite.curr_X, 0, Soldado_militar[i].sprite.Width,
                                                        Soldado_militar[i].sprite.Height, Soldado_militar[i].pos.x, 
                                                        Soldado_militar[i].pos.y, 0);
                                        hitted = false;
                                    }
                                    else if(Soldado_militar[i].action == sm_attack){
                                        al_draw_bitmap_region(Soldado_militar[i].sprite.Imagem_attack_EAST,
                                                                Soldado_militar[i].sprite.curr_X = 0,Soldado_militar[i].sprite.curr_Y = 0,
                                                                Soldado_militar[i].sprite.Width, Soldado_militar[i].sprite.Height,
                                                                Soldado_militar[i].pos.x, Soldado_militar[i].pos.y,
                                                                (Soldado_militar[i].dir == sm_direita)? 1: 0);
                                        //al_rest(13.0);
                                    }else{
                                         al_draw_bitmap_region(Soldado_militar[i].sprite.Imagem_walk_EAST,
                                                                Soldado_militar[i].sprite.curr_X,Soldado_militar[i].sprite.curr_Y = 0,
                                                                Soldado_militar[i].sprite.Width, Soldado_militar[i].sprite.Height,
                                                                Soldado_militar[i].pos.x, Soldado_militar[i].pos.y,
                                                                (Soldado_militar[i].dir == sm_direita)? 1: 0);
                                    }
                                }
                            }
                            if(!qtd_vivo){
                                //libera boss
                                hitted = false;
                                if(jogador.Acao == Attack && Esta_nas_proximidades(Boss_fase2.pos.x, Boss_fase2.pos.y, jogador.pos.x, jogador.pos.y, 20)){
                                    hitted = true;
                                }
                                vivo = true;
                                if(Boss_fase2.vida <= 0){
                                    vivo = false;
                                    passouFase2 = true;
                                }
                                else qtd_vivo++;
                                if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0 && vivo)){
                                    //timing = 0;
                                    if(Boss_fase2.dir == sm_direita && Boss_fase2.action == sm_walk){
                                        if(!Existe_Obstaculo(Boss_fase2.pos.x + Boss_fase2.pos.dx + 32, Boss_fase2.pos.y, bit_map_Fase2) && !HoraDoAtaque(Boss_fase2.pos.x,Boss_fase2.pos.y, curr_posicao_plyr)){  
                                            // printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                            Boss_fase2.pos.x += Boss_fase2.pos.dx;
                                        }
                                        else{ 
                                            Boss_fase2.dir = sm_esquerda;
                                        } 
                                    }
                                    if((Boss_fase2.dir == sm_esquerda  && Boss_fase2.action == sm_walk )){
                                        if(!Existe_Obstaculo(Boss_fase2.pos.x  - Boss_fase2.pos.dx, Boss_fase2.pos.y,bit_map_Fase2) && (!HoraDoAtaque(Boss_fase2.pos.x, Boss_fase2.pos.y, curr_posicao_plyr))){  
                                            //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                            Boss_fase2.pos.x -= Boss_fase2.pos.dx;
                                        }   
                                        else {
                                            //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                            Boss_fase2.dir = sm_direita;
                                        }
                                    }
                                    Boss_fase2.sprite.curr_Y = Boss_fase2.sprite.Height * Boss_fase2.action;
                                    if((Boss_fase2.sprite.curr_X + Boss_fase2.sprite.Width) < 64 && Boss_fase2.action == sm_walk){
                                        Boss_fase2.sprite.curr_X += Boss_fase2.sprite.Width;
                                    }
                                    else{
                                        Boss_fase2.sprite.curr_X  = 0;
                                    }
                                    if(HoraDoAtaque(Boss_fase2.pos.x, Boss_fase2.pos.y,curr_posicao_plyr)){  
                                        printf("\nHORA DE ATACAR\n");
                                        Boss_fase2.action = sm_attack;
                                        if(Boss_fase2.pos.x < curr_posicao_plyr.x){
                                            Boss_fase2.dir = sm_direita;
                                        }
                                        else{
                                            Boss_fase2.dir = sm_esquerda; // não recordo-me a direção original do sprite 
                                        }
                                        times_of_attack_enemy += 1;
                                    }
                                    //isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 20 && Boss_fase2.action == sm_attack){
                                        printf("\nParou o ataque\n");
                                        Boss_fase2.action = sm_walk;
                                        times_of_attack_enemy  = 0;
                                    }
                                    //Soldado_militar[i].action= sm_death;  
                                    //printf("EM Y_IMG %d X_IMG %d\n", Soldado_militar[i].sprite.curr_Y, Soldado_militar[i].sprite.curr_X);
                                }
                                if(vivo){
                                    if(hitted){
                                        // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                                        //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_militar[i].pos.x, Soldado_militar[i].pos.y);
                                        
                                        /*al_draw_bitmap_region(Boss_fase2.sprite.Imagem_walk_EAST,
                                                                Boss_fase2.sprite.curr_X,Boss_fase2.sprite.curr_Y,
                                                                Boss_fase2.sprite.Width, Boss_fase2.sprite.Height,
                                                                Boss_fase2.pos.x, Boss_fase2.pos.y,
                                                                (Boss_fase2.dir == sm_direita)? 0 : 1);*/
                                        Boss_fase2.vida--;

                                        al_draw_tinted_bitmap_region(Boss_fase2.sprite.Imagem_walk_WEST,al_map_rgb(135,0,0),
                                                                    Boss_fase2.sprite.curr_X, 0, Boss_fase2.sprite.Width,
                                                                    Boss_fase2.sprite.Height, Boss_fase2.pos.x, 
                                                                    Boss_fase2.pos.y, (Boss_fase2.dir == sm_direita)? 0 : 1);
                                    }
                                    else if(Boss_fase2.action == sm_attack){
                                        al_draw_bitmap_region(Boss_fase2.sprite.Imagem_attack_WEST,
                                                                0,0, Boss_fase2.sprite.Width, Boss_fase2.sprite.Height,
                                                                Boss_fase2.pos.x, Boss_fase2.pos.y,
                                                                (Boss_fase2.dir == sm_direita)? 1: 0);
                                        
                                        //al_rest(13.0);
                                    }else{
                                        al_draw_bitmap_region(Boss_fase2.sprite.Imagem_walk_WEST,
                                                                Boss_fase2.sprite.curr_X,Boss_fase2.sprite.curr_Y,
                                                                Boss_fase2.sprite.Width, Boss_fase2.sprite.Height,
                                                                Boss_fase2.pos.x, Boss_fase2.pos.y,
                                                                (Boss_fase2.dir == sm_direita)? 0 : 1);
                                    }
                                    n_soldados_militares = 0;
                                }
                            }
                            break; //break do case Fase2
                        
                        case Fase3:
                            for(int i = 0 ; i < n_inimigos ; i++){
                                // int timing = (al_get_time() - marcadorDeTempo) + timing;  
                                //libera boss
                                hitted = false;
                                if(jogador.Acao == Attack && Esta_nas_proximidades(Presidente.pos.x, Presidente.pos.y, jogador.pos.x, jogador.pos.y, 20)){
                                    hitted = true;
                                }
                                vivo = true;
                                if(Presidente.vida <= 0){
                                    vivo = false;
                                    passouFase3 = true;
                                }
                                else qtd_vivo++;
                                if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0 && vivo)){
                                    //timing = 0;
                                    if(Presidente.dir == sm_direita && Presidente.action == sm_walk){
                                        if(!Existe_Obstaculo(Presidente.pos.x + Presidente.pos.dx + 32, Presidente.pos.y,bit_map_Fase2) && !HoraDoAtaque(Presidente.pos.x,Presidente.pos.y, curr_posicao_plyr)){  
                                            // printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                            Presidente.pos.x += Presidente.pos.dx;
                                        }
                                        else{ 
                                            Presidente.dir = sm_esquerda;
                                        } 
                                    }
                                    if((Presidente.dir == sm_esquerda  && Presidente.action == sm_walk )){
                                        if(!Existe_Obstaculo(Presidente.pos.x  - Presidente.pos.dx, Presidente.pos.y,bit_map_Fase2) && (!HoraDoAtaque(Presidente.pos.x, Presidente.pos.y, curr_posicao_plyr))){  
                                            //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                            Presidente.pos.x -= Presidente.pos.dx;
                                        }   
                                        else {
                                            //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                            Presidente.dir = sm_direita;
                                        }
                                    }
                                    Presidente.sprite.curr_Y = Presidente.sprite.Height * Presidente.action;
                                    if((Presidente.sprite.curr_X + Presidente.sprite.Width ) < 64 && Presidente.action == sm_walk){
                                        Presidente.sprite.curr_X += Presidente.sprite.Width;
                                    }
                                    else{
                                        Presidente.sprite.curr_X  = 0;
                                    }
                                    if(HoraDoAtaque(Presidente.pos.x, Presidente.pos.y,curr_posicao_plyr)){  
                                        printf("\nHORA DE ATACAR\n");
                                        Presidente.action = sm_attack;
                                        if(Presidente.pos.x < curr_posicao_plyr.x){
                                            Presidente.dir = sm_direita;
                                        }
                                        else {
                                            Presidente.dir = sm_esquerda; // não recordo-me a direção original do sprite 
                                        }
                                        times_of_attack_enemy += 1;
                                    }
                                    //isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 20 && Presidente.action == sm_attack){
                                        printf("\nParou o ataque\n");
                                        Presidente.action = sm_walk;
                                        times_of_attack_enemy  = 0;
                                    }
                                    //Soldado_militar[i].action= sm_death;  
                                    //printf("EM Y_IMG %d X_IMG %d\n", Soldado_militar[i].sprite.curr_Y, Soldado_militar[i].sprite.curr_X);
                                }
                                if(vivo){
                                    if(hitted){
                                        // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                                        //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_militar[i].pos.x, Soldado_militar[i].pos.y);
                                        
                                        al_draw_bitmap_region(Presidente.sprite.Imagem_walk_EAST,
                                                                Presidente.sprite.curr_X,Presidente.sprite.curr_Y,
                                                                Presidente.sprite.Width, Presidente.sprite.Height,
                                                                Presidente.pos.x, Presidente.pos.y,
                                                                (Presidente.dir == sm_direita)? 0 : 1);
                                        Presidente.vida--;

                                        al_draw_tinted_bitmap_region(Presidente.sprite.Imagem_walk_EAST,al_map_rgb(135,0,0),
                                                                        Presidente.sprite.curr_X, 0, Presidente.sprite.Width,
                                                                        Presidente.sprite.Height, Presidente.pos.x, 
                                                                        Presidente.pos.y, 0);
                                    }
                                    else{
                                        al_draw_bitmap_region(Presidente.sprite.Imagem_attack_EAST,
                                                                Presidente.sprite.curr_X = 0, Presidente.sprite.curr_Y = 0,
                                                                Presidente.sprite.Width, Presidente.sprite.Height,
                                                                Presidente.pos.x, Presidente.pos.y,
                                                                (Presidente.dir == sm_direita)? 1: 0);
                                        //al_rest(13.0);
                                    }
                                // n_soldados_militares = 0;
                                }
                                // esse if verifica o intervalo para mudar de frame 
                                // esse numero esquisito ai é o intervalo
                                //printf("\n%lf",(timing));

                                if(((al_get_time() - marcadorDeTempo) > 0.03169) || (marcadorDeTempo == 0)){
                                    //timing = 0;
                                    if(Inimigos_fase3[i].dir == sm_direita && Inimigos_fase3[i].action == sm_walk){
                                        if(!Existe_Obstaculo(Inimigos_fase3[i].pos.x + Inimigos_fase3[i].pos.dx + 32, Inimigos_fase3[i].pos.y,bit_map_Fase3) && !HoraDoAtaque(Inimigos_fase3[i].pos.x, Inimigos_fase3[i].pos.y, curr_posicao_plyr)){
                                                printf("\nNAO EXISTE OBSTACULO A DIREITA \n");
                                                Inimigos_fase3[i].pos.x += Inimigos_fase3[i].pos.dx;
                                        }
                                        else{ 
                                                Inimigos_fase3[i].dir = sm_esquerda;
                                        } 
                                    }
                                    if((Inimigos_fase3[i].dir == sm_esquerda  && Inimigos_fase3[i].action == sm_walk )){
                                        if(!Existe_Obstaculo(Inimigos_fase3[i].pos.x - Inimigos_fase3[i].pos.dx, Inimigos_fase3[i].pos.y,bit_map_Fase1) && (!HoraDoAtaque(Inimigos_fase3[i].pos.x, Inimigos_fase3[i].pos.y, curr_posicao_plyr))){  
                                            //printf("\nNAO EXISTE OBSTACULO A ESQUERDA\n");
                                            Inimigos_fase3[i].pos.x -= Inimigos_fase3[i].pos.dx;
                                        }   
                                        else {
                                            //printf("EXISTE OBSTACULO A ESQUERDA\n");
                                            Inimigos_fase3[i].dir = sm_direita;
                                        }
                                    }
                                    //Inimigos_fase3[i].sprite.curr_Y = Soldado_medieval[i].sprite.Height * Soldado_medieval[i].action;
                                    if((Inimigos_fase3[i].sprite.curr_X + Inimigos_fase3[i].sprite.Width) < 64 && Inimigos_fase3[i].action != sm_death){
                                        Inimigos_fase3[i].sprite.curr_X += Inimigos_fase3[i].sprite.Width;
                                    }
                                    else{
                                        Inimigos_fase3[i].sprite.curr_X  = 0;
                                    }
                                    if(HoraDoAtaque(Inimigos_fase3[i].pos.x, Inimigos_fase3[i].pos.y,curr_posicao_plyr)){
                                        Inimigos_fase3[i].action = sm_attack;
                                        if(Inimigos_fase3[i].pos.x < curr_posicao_plyr.x){
                                            Inimigos_fase3[i].dir = sm_direita;
                                        }
                                        else{
                                            Inimigos_fase3[i].dir = sm_esquerda;
                                        }
                                        times_of_attack_enemy += 1;
                                    }
                                    // isso meio que  ta mensurando o tempo de ataque
                                    if(times_of_attack_enemy > 20){
                                        Inimigos_fase3[i].action = sm_walk;
                                        times_of_attack_enemy  = 0;
                                    }
                                    // a part e da morte não está funcionando muito bem
                                    if(Inimigos_fase3[i].vida  <= 0){
                                        Inimigos_fase3[i].action = sm_death;
                                    }
                                    if(Inimigos_fase3[i].action == sm_death){
                                        Inimigos_fase3[i].sprite.curr_Y = 0;
                                        Inimigos_fase3[i].sprite.curr_X = 0;
                                    }
                                    if(Inimigos_fase3[i].hitted == false ){
                                        // printf("\n\tPOSICAO JOGADOR : %d,%d \n\t POSICAO SOLDADO: %d, %d", 
                                        //curr_posicao_plyr.x, curr_posicao_plyr.y, Soldado_medieval[i].pos.x, Soldado_medieval[i].pos.y);
                                        switch (Inimigos_fase3[i].tipo){
                                            case 1:
                                                al_draw_bitmap_region(Inimigos_fase3[i].sprite.Imagem,
                                                Inimigos_fase3[i].sprite.curr_X,Inimigos_fase3[i].sprite.curr_Y,
                                                Inimigos_fase3[i].sprite.Width, Inimigos_fase3[i].sprite.Height,
                                                Inimigos_fase3[i].pos.x, Inimigos_fase3[i].pos.y,
                                                (Inimigos_fase3[i].dir == sm_direita)? 0: 1);
                                                break;
                                            default:
                                                al_draw_bitmap_region(Inimigos_fase3[i].sprite.Imagem, 0, 0,
                                                Inimigos_fase3[i].sprite.Width, Inimigos_fase3[i].sprite.Height,
                                                Inimigos_fase3[i].pos.x, Inimigos_fase3[i].pos.y,
                                                (Inimigos_fase3[i].dir == sm_direita)? 0: 1);
                                                break;
                                        }
                                    }
                                    //Soldado_medieval[i].action= sm_death;    
                                }
                            }
                            break; //break do case Fase3

                        default:
                            break;
                    }
                    al_draw_textf(fonte_creditos, al_map_rgb(255, 0, 0), 40, 20, ALLEGRO_ALIGN_LEFT, "Vidas: %d", jogador.vida);
                    printf("Quantidade de vida jogador : %d\n", jogador.vida);
                    al_flip_display();
                    marcadorDeTempo= al_get_time();
                    redraw = false;
                }
            }
        }
    }

    // Clean up
    free(Soldado_militar);
    free(Soldado_medieval);
    free(Inimigos_fase3);
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
