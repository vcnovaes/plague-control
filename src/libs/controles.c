#include "controles.h"
#include <stdio.h>

bool Existe_Obstaculo(int pos_x, int pos_y, int Mapas[21][30]){    
    int col = ((pos_x) / 32) + 1;
    int lin = ((pos_y) / 32) + 1;

    bool ta_na_bordinha = false;
  //  printf("Col : %d , linha : %d  %s\n", col, lin, Mapas[lin][col]?"OBSTACULO":"LIVRE");
    if(pos_x >= Display_WIDTH - 100){
        ta_na_bordinha = true;
    }
    if(pos_y >= Display_HEIGHT - 100){
        ta_na_bordinha = true;
    } 
    if(pos_x <= 25){
        ta_na_bordinha = true;
    }
    if(pos_y <= 25){
        ta_na_bordinha = true;
    }

    return (Mapas[lin][col] || ta_na_bordinha);
}

bool Esta_nas_proximidades(int pos_x, int pos_y, int ply_x, int ply_y, int range){
    bool resp = false;
    //Lembrar que as imagens do inimigo e do player tem 32x32 pixels
    //temos 8 casos, partindo da perspectiva do inimigo, o player pode estar a direita, esquerda, acima, abaixo, diagonais
    //Caso 1 : se o player estiver a esquerda do inimigo, tera x menor e mesmo y
    //Caso 2 : se o player estiver a direita do inimigo, tera x maior e mesmo y
    //Caso 3 : se o player estiver acima do inimigo, tera mesmo x e y menor
    //Caso 4 : se o player estiver abaixo do inimigo, tera mesmo x e y maior
    //Caso 5 : se o player estiver na diagonal esquerda acima do inimigo, tera menor x e menor y
    //Caso 6 : se o player estiver na diagonal direita acima do inimigo, tera maior x e menor y
    //Caso 7 : se o player estiver na diagonal esquerda abaixo do inimigo, tera menor x e maior y
    //Caso 8 : se o player estiver na diagonal direita abaixo do inimigo, tera maior x e maior y

    if(ply_x < pos_x && ply_y == pos_y){ //Caso 1
        if(ply_x + 32 + range >= pos_x)
            resp = true;
    }
    else if(ply_x > pos_x && ply_y == pos_y){ //Caso 2
        if(ply_x - range <= pos_x)
            resp = true;
    }
    else if(ply_x == pos_x && ply_y < pos_y){ //Caso 3
        if(ply_y + 32 + range >= pos_y)
            resp = true;
    }
    else if(ply_x == pos_x && ply_y > pos_y){ //Caso 4
        if(ply_y - range <= pos_y)
            resp = true;
    }
    else if(ply_x < pos_x && ply_y < pos_y){ //Caso 5
        if((ply_x + 32 + range >= pos_x) && (ply_y + 32 + range >= pos_y))
            resp = true;
    }
    else if(ply_x > pos_x && ply_y < pos_y){ //Caso 6
        if((ply_x - range <= pos_x) && (ply_y + 32 + range >= pos_y))
            resp = true;
    }
    else if(ply_x < pos_x && ply_y > pos_y){ //Caso 7
        if((ply_x + 32 + range >= pos_x) && (ply_y  - range <= pos_y))
            resp = true;
    }
    else if(ply_x > pos_x && ply_y > pos_y){ //Caso 8
        if((ply_x  - range <= pos_x) && (ply_y  - range <= pos_y))
            resp = true;
    }
    return resp;
}
