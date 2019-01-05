#include <stdio.h>
#include <stdlib.h>
int main(){
FILE *archivo_EntradaC;
int desfase=4;
archivo_EntradaC=fopen("Entrada2.txt","w");
fprintf(archivo_EntradaC,"Descifrado\n");
fprintf(archivo_EntradaC,"%d\n",desfase);
fprintf(archivo_EntradaC,"WAPPYEWEAW\n");
fprintf(archivo_EntradaC,"WENOYKPAS");
fclose(archivo_EntradaC);
return 0;

}
