#include <stdio.h>
int main(){
	int filas, columnas,i,j;
	FILE *archivo;
	archivo=fopen("imagenPrincipal4.txt","w");
	printf("Ingresar numero filas \n");
	scanf("%d",&filas);
	printf("%d\n",filas);
	printf("Ingresar numero columnas \n");
	scanf("%d",&columnas);
	fprintf(archivo,"%d %d\n",filas, columnas);
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			fprintf(archivo, "0,0,0 ");
		}
		fprintf(archivo, "\n");
	}
	return 0;
}
