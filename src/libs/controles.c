#include "controles.h"
#include <stdio.h>

bool Existe_Obstaculo(int pos_x, int pos_y, int Mapas[21][30]){    
    int col = floor(pos_x  / 32);
    int lin = floor(pos_y / 32);
    bool on_limit_of_map = false;
    printf("Col : %d , linha : %d  %s\n", col, lin, Mapas[lin][col]?"OBSTACULO":"LIVRE");
    if(pos_x >= Display_WIDTH - 100){
        on_limit_of_map = true;
    }
    if(pos_y >= Display_HEIGHT - 100){
        on_limit_of_map = true;
    }
    if(pos_x <= 25){
        on_limit_of_map = true;
    }
    if(pos_y <= 25){
        on_limit_of_map = true;
    }

    return (Mapas[lin][col] || on_limit_of_map);
}

bool Esta_nas_proximidades(int pos_x, int pos_y, int ply_x, int ply_y, int range){
    bool res = false;
    printf("\n\tPOSICAO DO INIMIGO : (%d,%d) \n\tPOSICAO DO PLAYER : (%d,%d)\n",pos_x,pos_y,ply_x,ply_y);
    if(((pos_x - range < ply_x) && ply_x < (pos_x + range) ) &&
        ((pos_y - range < ply_y) &&  ply_y  <  (pos_y - range) )){
            res = true;
            printf("\nEsta nas proximidades \n");
        }else{
            printf("\nNao Esta nas proximidades \n");
        }
    return res;

}