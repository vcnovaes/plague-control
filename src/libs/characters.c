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
        if(personagem->loc.i > 0){
            if(personagem->pos.y <= (personagem->loc.i) *32){
                personagem->loc.i --;
            }
        }
        if(personagem->pos.y > 0 && map[personagem->loc.i][personagem->loc.j])
            personagem->pos.y -= keys[UP]*(personagem->pos.dy);

    }
    if(keys[DOWN]){
        if(personagem->loc.i < 21){
            if(personagem->pos.y > (personagem->loc.i) *32){
                personagem->loc.i ++;
            }
        }

        if(personagem->pos.y < Display_HEIGHT - 30 && !map[personagem->loc.i][personagem->loc.j] )
            personagem->pos.y += keys[DOWN]*(personagem->pos.dy);    
    
    }
    if(keys[LEFT]){
        if(personagem->pos.x  > 0)
            personagem->pos.x -= keys[LEFT]*(personagem->pos.dx);
    }
    if(keys[RIGHT]){
        if(personagem->pos.x < Display_WIDTH -30) 
            personagem->pos.x += keys[RIGHT]*(personagem->pos.dx);
    
    }


   /*     if(keys[LEFT] || keys[DOWN]){
            if(!((personagem->pos.x < (personagem->quadranteI +1)*32
                && personagem->pos.x > personagem->quadranteI*32) ||
                (personagem->pos.y < (personagem->quadranteJ +1)*32
                && personagem->pos.y > personagem->quadranteJ*32))){
                if(!(personagem->pos.x < (personagem->quadranteI +1)*32
                    && personagem->pos.x > personagem->quadranteI*32)){ 
                        //if(personagem->quadranteI < 21)
                          //  personagem->quadranteI++;
                    }
                    if(!((personagem->pos.y < (personagem->quadranteJ +1)*32
                    && personagem->pos.y > personagem->quadranteJ*32))) 
                    {
                    if(personagem->quadranteJ <30)
                          personagem->quadranteJ++;
                    }
                }
            }
        if(keys[UP] || keys[DOWN]){
            if(!((personagem->pos.x < (personagem->quadranteI +1)*32
                && personagem->pos.x > personagem->quadranteI*32) ||
                (personagem->pos.y < (personagem->quadranteJ +1)*32
                && personagem->pos.y > personagem->quadranteJ*32))){
                if(!(personagem->pos.x < (personagem->quadranteI +1)*32
                    && personagem->pos.x > personagem->quadranteI*32)){ 
                      if(personagem->quadranteI > 0)
                            personagem->quadranteI--;
                    }
                    if(!((personagem->pos.y < (personagem->quadranteJ +1)*32
                    && personagem->pos.y > personagem->quadranteJ*32))) 
                    {
                    if(personagem->quadranteJ > 0 )
                            personagem->quadranteJ--;
                    }
                }
        }*/
        printf("ESTA EM %d   x  %d\n", personagem->loc.i,personagem->loc.j);
        //for(int i  = 0; i < 10000; i++){}
        MudarFrame_Personagem(personagem,64);   

}

void Criar_Soldado_Medieval(SOLDADO_MEDIEVAL **Soldado_medieval, int n_soldados_medievais,
                            char * IMG_Soldado_Medieval[3]){
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
            (*Soldado_medieval)[i].pos.x = (rand() % (Display_WIDTH - 0 + 1)) + 0;
            (*Soldado_medieval)[i].pos.y = (rand() % (Display_HEIGHT + 1));
            (*Soldado_medieval)[i].pos.dx = 3;
            (*Soldado_medieval)[i].pos.dy = 3;
            (*Soldado_medieval)[i].dir = sm_direita;
            (*Soldado_medieval)[i].action = sm_walk;
            (*Soldado_medieval)[i].vida = 4;
            (*Soldado_medieval)[i].hitted  = false;
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