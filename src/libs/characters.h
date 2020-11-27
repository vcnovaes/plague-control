#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <allegro5/allegro.h>

#include <allegro5/allegro_image.h>
/////ESSE  ARQUIVO CONTEM A ESTRUTURA DOS PERSONAGENS DO JOGO

// A variavel vel indica a velocidade em que o personagem vai se mover na tela, está como constante
//
// essa função cria o jogador, o motivo de ter uma função para criar exclusivamente 
//const int enemy_vel = 3;
//const int velocidade_padrao = 3;

typedef struct Sprite{
    ALLEGRO_BITMAP * Imagem; 
    ALLEGRO_BITMAP * Imagem_attack_NORTH;
    ALLEGRO_BITMAP * Imagem_attack_SOUTH;
    ALLEGRO_BITMAP * Imagem_attack_EAST;
    ALLEGRO_BITMAP * Imagem_attack_WEST;
    ALLEGRO_BITMAP * Imagem_walk_NORTH;
    ALLEGRO_BITMAP * Imagem_walk_SOUTH;
    ALLEGRO_BITMAP * Imagem_walk_EAST;
    ALLEGRO_BITMAP * Imagem_walk_WEST;

    int curr_X;   // posicao de leitura na imagem na coordenada x
    int curr_Y;     // posicao de leitura na imagem na coordenada y
    int Height; // Altura de cada frame
    int Width;// Largura de cada frame de cada frame
    int n_colunas;  // Numero de colunas de frames
    int n_linhas; // Numero de linhas de frames
}SPRITE;


typedef struct posicao{
    int x;
    int y;
    int dx;
    int dy;
}POSICAO;

// enum das direções
enum Direcoes {
    North = 0,
    South,
    East,
    West
};
typedef struct  localizacao_matriz
{
    int i;
    int j;
}MATRIZ_LOCALIZACAO;

enum Actions{
    Attack,
    Walk,
    Nothing
};
// estrutura para os frames

typedef struct  frames
{
    int qtdFrames;
    int currentFrame;
    int h_Frame;
    int w_Frame;
}FRAMES;
/// estrutura para personagem
typedef struct personagem{
    ALLEGRO_BITMAP * imagem_caminhar[4];
    ALLEGRO_BITMAP * imagem_ataque[4];
    FRAMES frames;
    
    POSICAO pos;
    int Acao;
    int CurrentDir;
    int vida;
    MATRIZ_LOCALIZACAO loc;

}PERSONAGEM;


typedef struct Soldado_Medieval{
    SPRITE sprite;   // sprite do soldado
    int vida;   // vida do soldado inicial 3
    POSICAO pos;    ///posicao do soldado no display principal 
    int dir;    // direação do soldado
    int action;   //acao do soldado
    int tipo;
    bool hitted;  // se o soldado levou hit
     // Se o soldado levou um hit o ideal é que ele pisquer para indicar que foi  atingdido

    // Sugestão de adicionar o campo IsDead para ver se o soldado está vivo
    // bool IsDead;
}SOLDADO_MEDIEVAL;


void Criar_Personagem(PERSONAGEM * jogador, char * Imagens_Andar[4], char * Imagens_Ataque[4],
 int x_inicial, int y_inicial);

void Personagem_SetFrames(PERSONAGEM * personagem, int numero_de_frames, int width_frame, int height_frame);

void Personagem_AtualizarPosicao(PERSONAGEM *personagem, bool keys[4], int map[21][30]);

void Criar_Soldado_Medieval(SOLDADO_MEDIEVAL **Soldado_medieval, int n_soldados_medievais,
                            char * IMG_Soldado_Medieval[3], int map[21][30]);
/*
char * IMG_Soldado_Medieval[3]  ={
    "src/Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 sword 1.png",
    "src/Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 sword 2.png",
    "src/Graficos/Pixel_Art_Gamejam/Fase 1/Soldier/Knight Character Pack by RgsDev/Knight 1/knight 1 axe.png"
    };
    */
void MudarFrame_Personagem(PERSONAGEM  * personagem , int IMG_total_W);
// Verfica se o inimigo deve atacar
bool HoraDoAtaque(int pos_inimigo_x, int pos_inimigo_y, POSICAO jogador);
void Criar_Soldado_Militar(SOLDADO_MEDIEVAL **Soldado_militar, int n_soldados_militares,
                            char * Imagens_RUN[4], char * Imagens_ATTACK[4], int map[21][30]);

void Criar_InimigosFase3(SOLDADO_MEDIEVAL **InimigosF3, int n_inimigos, char *Imagens[2], int map[21][30]);
void Criar_BossFase2(SOLDADO_MEDIEVAL *Boss, char *Imagens_walk[4],char  * Imagens_attack[4], int map[21][30]);
void Criar_BossFase3(SOLDADO_MEDIEVAL *Presidente, char *Imagens_walk[2],char  * Imagens_attack[2], int map[21][30])


#endif