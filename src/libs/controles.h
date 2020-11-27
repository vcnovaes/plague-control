#ifndef CONTROLES_H
#define CONTROLES_H
#include <stdbool.h>
#include <math.h>
#define Display_WIDTH 960
#define Display_HEIGHT 672

#define FPS 30

//const int enemy_vel = 3;




//Nesse arquivo ficariam os controles  graficos, como as mudanças de frame dos objetos
enum sm_dir { sm_direita, sm_esquerda};
enum soldado_militar_linha_de_acao {sm_jump,sm_walk, sm_attack, sm_death};
enum KEYS{UP, DOWN, LEFT, RIGHT};

bool Existe_Obstaculo(int pos_x, int pos_y, int Mapas[21][30]);
bool Esta_nas_proximidades(int pos_x, int pos_y, int ply_x, int ply_y, int range);

#endif
