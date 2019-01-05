#include <stdio.h>
#include <stdlib.h>
int main(){
char c='D';
FILE *archivo_EntradaC;
archivo_EntradaC=fopen("Entrada.txt","w");
fprintf(archivo_EntradaC,"Cifrado\n");
fprintf(archivo_EntradaC,"WENOYKPASA");
fclose(archivo_EntradaC);
c=tolower(c);
printf("%c\n",c);
return 0;

}
