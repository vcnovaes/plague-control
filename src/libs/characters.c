#include "characters.h"
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include "controles.h"


void Criar_Personagem(PERSONAGEM * jogador, char * Imagens_Andar[4], char * Imagens_Ataque[4],
 int x_inicial, int y_inicial){
    
    jogador->imagem_caminhar[North] = al_load_bitmap(Imagens_Andar[North]);
    jogador->imagem_caminhar[South] = al_load_bitmap(Imagens_Andar[South]);
    jogador->imagem_caminhar[East] = al_load_bitmap(Imagens_Andar[East]);
    jogador->imagem_caminhar[West] = al_load_bitmap(Imagens_Andar[West]);
    
    jogador->imagem_ataque[North] = al_load_bitmap(Imagens_Andar[North]);
    jogador->imagem_ataque[South] = al_load_bitmap(Imagens_Andar[South]);
    jogador->imagem_ataque[East] = al_load_bitmap(Imagens_Andar[East]);
    jogador->imagem_ataque[West] = al_load_bitmap(Imagens_Andar[West]);
    

    for(int i =0 ; i < 4; i++)
    if(al_load_bitmap(Imagens_Andar[West] )!= NULL){
        printf("%s\n", Imagens_Andar[i]);
    }

    jogador->pos.x = x_inicial;
    jogador->pos.y = y_inicial;
    jogador->pos.dx = 2;
    jogador->pos.dy = 2;

    jogador->loc.i = 0;
    jogador->loc.j = 0;
    jogador->vida = 3;

 }
void Personagem_SetFrames(PERSONAGEM * personagem, int numero_de_frames, int width_frame, int height_frame){
    
    personagem->frames.qtdFrames = numero_de_frames;
    personagem->frames.w_Frame = width_frame;
    personagem->frames.h_Frame = height_frame;
    personagem->frames.currentFrame = 0;
}

void Personagem_AtualizarPosicao(PERSONAGEM *personagem, bool keys[4], int map[21][30]){    
  //  if(!map[personagem->quadranteI][personagem->quadranteJ]){    
    /// tentando criar os obstaculos no mapa
    if(keys[UP]){
        
        if(!Existe_Obstaculo( personagem->pos.x,personagem->pos.y - personagem->pos.dy,map)
            && (personagem->pos.y -  personagem->pos.dy)  > 25 )
            personagem->pos.y -= keys[UP]*(personagem->pos.dy);

    }
    if(keys[DOWN]){
        if(!Existe_Obstaculo(personagem->pos.x,personagem->pos.y + personagem->pos.dy,map)
             && (personagem->pos.y +  personagem->pos.dy)  < Display_HEIGHT+ 25){
            personagem->pos.y += keys[DOWN]*(personagem->pos.dy);    
        }
    
    }
    if(keys[LEFT]){
         if(!Existe_Obstaculo( personagem->pos.x - personagem->pos.dx,personagem->pos.y ,map)
            && (personagem->pos.x -  personagem->pos.dx)  > 25 )
                personagem->pos.x -= keys[LEFT]*(personagem->pos.dx);
    }
    if(keys[RIGHT]){
        if(!Existe_Obstaculo( personagem->pos.x + personagem->pos.dx,personagem->pos.y ,map)
            && (personagem->pos.x +  personagem->pos.dx)  < Display_WIDTH + 25)
                personagem->pos.x += keys[RIGHT]*(personagem->pos.dx);
    
    }
    printf("Current position  : x   :  %d   y  : %d\n", personagem->pos.x, personagem->pos.y);    
    MudarFrame_Personagem(personagem,64);   

}

void Criar_Soldado_Medieval(SOLDADO_MEDIEVAL **Soldado_medieval, int n_soldados_medievais,
                            char * IMG_Soldado_Medieval[3], int map[21][30]){
    (*Soldado_medieval) = (SOLDADO_MEDIEVAL * )malloc(n_soldados_medievais*sizeof(SOLDADO_MEDIEVAL));
    if(Soldado_medieval ==NULL)exit(-1);
    for(int i  = 0 ;  i  <n_soldados_medievais; i++)
            {   
               // Carrega a imagem do soldado medieval,  i%3 é pq existem apenas tres
        // modelos de soldados diferentes/ assim  o modelo gerado no display seria
        // 'aleatório'
            
            (*Soldado_medieval)[i].sprite.Imagem =  al_load_bitmap(IMG_Soldado_Medieval[i%3]);
            if((*Soldado_medieval)[i].sprite.Imagem == NULL) exit(-1);
            (*Soldado_medieval)[i].sprite.Height = 64;
            (*Soldado_medieval)[i].sprite.Width  = 64;
            (*Soldado_medieval)[i].sprite.n_colunas   = 7;
            (*Soldado_medieval)[i].sprite.n_linhas    = 4;
            (*Soldado_medieval)[i].sprite.curr_X = 0;
            (*Soldado_medieval)[i].sprite.curr_Y = 0;
            (*Soldado_medieval)[i].pos.x = (rand() % (Display_WIDTH  + 1)) + 0;
            (*Soldado_medieval)[i].pos.y = (rand() % (Display_HEIGHT  - 150));
            //Esse loop assegura a posição inicial do soldado não ser um obstaculo
            
            
            (*Soldado_medieval)[i].pos.dx = 3;
            (*Soldado_medieval)[i].pos.dy = 3;
            while (Existe_Obstaculo((*Soldado_medieval)[i].pos.x + (*Soldado_medieval)[i].pos.dx,
                    (*Soldado_medieval)[i].pos.y + (*Soldado_medieval)[i].pos.dy, map))
            {
                (*Soldado_medieval)[i].pos.x = (rand() % (Display_WIDTH  - 100 + 1)) + 0;
                (*Soldado_medieval)[i].pos.y = (rand() % (Display_HEIGHT  - 150));
            
            }
            (*Soldado_medieval)[i].dir = sm_esquerda;
            (*Soldado_medieval)[i].action = sm_walk;
            (*Soldado_medieval)[i].vida = 4;
            (*Soldado_medieval)[i].hitted  = false;
        }

}

void Criar_Soldado_Militar(SOLDADO_MEDIEVAL **Soldado_militar, int n_soldados_militares,
                            char * Imagens_RUN[4], char * Imagens_ATTACK[4], int map[21][30]){
    (*Soldado_militar) = (SOLDADO_MEDIEVAL * )malloc(n_soldados_militares*sizeof(SOLDADO_MEDIEVAL));
    if(Soldado_militar ==NULL)exit(-1);
    for(int i  = 0 ;  i  <n_soldados_militares; i++)
            {   
               // Carrega a imagem do soldado medieval,  i%3 é pq existem apenas tres
        // modelos de soldados diferentes/ assim  o modelo gerado no display seria
        // 'aleatório'
            
            (*Soldado_militar)[i].sprite.Imagem_walk_NORTH =  al_load_bitmap(Imagens_RUN[North]);
            (*Soldado_militar)[i].sprite.Imagem_walk_SOUTH =  al_load_bitmap(Imagens_RUN[South]);
            (*Soldado_militar)[i].sprite.Imagem_walk_WEST =  al_load_bitmap(Imagens_RUN[West]);
            (*Soldado_militar)[i].sprite.Imagem_walk_EAST =  al_load_bitmap(Imagens_RUN[East]);
            (*Soldado_militar)[i].sprite.Imagem_attack_NORTH =  al_load_bitmap(Imagens_RUN[North]);
            (*Soldado_militar)[i].sprite.Imagem_attack_SOUTH =  al_load_bitmap(Imagens_RUN[South]);
            (*Soldado_militar)[i].sprite.Imagem_attack_EAST =  al_load_bitmap(Imagens_RUN[East]);
            (*Soldado_militar)[i].sprite.Imagem_attack_WEST =  al_load_bitmap(Imagens_RUN[West]);
            //if((*Soldado_medieval)[i].sprite.Imagem == NULL) exit(-1);
            (*Soldado_militar)[i].sprite.Height = 24;
            (*Soldado_militar)[i].sprite.Width  = 16;
            (*Soldado_militar)[i].sprite.n_colunas   = 1;
            (*Soldado_militar)[i].sprite.n_linhas    = 1;
            (*Soldado_militar)[i].sprite.curr_X = 0;
            (*Soldado_militar)[i].sprite.curr_Y = 0;
            (*Soldado_militar)[i].pos.x = (rand() % (Display_WIDTH  + 1)) + 0;
            (*Soldado_militar)[i].pos.y = (rand() % (Display_HEIGHT  - 150));
            //Esse loop assegura a posição inicial do soldado não ser um obstaculo
            
            
            (*Soldado_militar)[i].pos.dx = 3;
            (*Soldado_militar)[i].pos.dy = 3;
            while (Existe_Obstaculo((*Soldado_militar)[i].pos.x + (*Soldado_militar)[i].pos.dx,
                    (*Soldado_militar)[i].pos.y + (*Soldado_militar)[i].pos.dy, map))
            {
                (*Soldado_militar)[i].pos.x = (rand() % (Display_WIDTH  - 100 + 1)) + 0;
                (*Soldado_militar)[i].pos.y = (rand() % (Display_HEIGHT  - 150));
            
            }
            (*Soldado_militar)[i].dir = sm_esquerda;
            (*Soldado_militar)[i].action = sm_walk;
            (*Soldado_militar)[i].vida = 4;
            (*Soldado_militar)[i].hitted  = false;
        }

}




void MudarFrame_Personagem(PERSONAGEM * personagem, int IMG_total_W){
  //  int size_x_change_frame =  IMG_total_W / (personagem->frames.qtdFrames);
    if(personagem->frames.currentFrame <  IMG_total_W){
        personagem->frames.currentFrame += personagem->frames.w_Frame;
       
    }
    else
    {
        personagem->frames.currentFrame = 0;
    }
    // printf("%d\n",personagem->frames.currentFrame);
}
bool HoraDoAtaque(int pos_inimigo_x, int pos_inimigo_y, POSICAO pos_jogador){
    bool ataque = true;
    if(!Esta_nas_proximidades(pos_inimigo_x,pos_inimigo_y,pos_jogador.x,pos_jogador.y, 50)){
        ataque = false;
    }

    return ataque;
}