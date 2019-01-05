#include <stdio.h>
int main(){
FILE *archivo_Salida;
archivo_Salida=fopen("Entrada.txt","w");
int i=0,j=0,n,cont=1;
n=64;
fprintf(archivo_Salida,"%d\n",n);
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		if(cont==256){
			cont=0;
		}
		if(j==n-1){
			fprintf(archivo_Salida,"%d\n",(cont++));
			}
		else if(j==n-1&&i==n-1){
			fprintf(archivo_Salida,"%d",(cont++));
			}
		
		else{
			fprintf(archivo_Salida,"%d ",(cont++));
		}}
}
return 0;
}
