#include "controles.h"

bool Existe_Obstaculo(int pos_x, int pos_y, int Mapas[21][30]){    
    int col = floor(pos_x  / 32);
    int lin = floor(pos_y / 32);
    return Mapas[lin][col];
}