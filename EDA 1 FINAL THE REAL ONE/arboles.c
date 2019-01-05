#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct nodo{
	int **dato;
	int dimension;
	int uni;
	int tam;
	struct nodo* nw;
	struct nodo* ne;
	struct nodo* sw;
	struct nodo* se;
};


void darMemoria(int ***matriz, int filas, int columnas);
void liberarMemoria(int **matriz, int dimension);
struct nodo* crearNodo(int tam,int **matriz);
void igualarMatrices(int **mat1,int **mat2, int tam);
void mostrarPreorden(struct nodo* nodo){
	if(nodo==NULL){
		return;
	}
	mostrarMatriz(nodo->dato,nodo->dimension);
	mostrarPreorden(nodo->ne);
	mostrarPreorden(nodo->nw);
	mostrarPreorden(nodo->se);
	mostrarPreorden(nodo->sw);
}

void darMemoria(int ***matriz, int filas, int columnas){
	int i=0;
	*matriz=(int **)malloc(filas * sizeof(*matriz));
	for(i=0;i<filas;i++){
		(*matriz)[i]=(int*)malloc(columnas * sizeof(*matriz[i]));
	}
	return;
}
//nodoQtree *raiz()
void liberarMemoria(int **matriz, int dimension){
	int i=0;
	for(i=0;i<dimension;i++){
		free(matriz[i]);
	}
	free(matriz);
	return;
}

struct nodo* crearNodo(int tam,int **matriz){
	struct nodo* nuevo = (struct nodo*)malloc(sizeof(struct nodo));
	darMemoria(&nuevo->dato,tam,tam);
	igualarMatrices(nuevo->dato,matriz,tam);
	nuevo->dimension=tam;
	nuevo->nw=NULL;
	nuevo->ne=NULL;
	nuevo->sw=NULL;
	nuevo->se=NULL;
	return (nuevo);
}
void igualarMatrices(int **mat1,int **mat2, int tam){
	int i,j;
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			mat1[i][j]=mat2[i][j];
		}
	}
}
void llenarMatriz(int **matriz,int i, int j,int elemento){
	matriz[i][j]=elemento;
	return;
}
void mostrarMatriz(int **matriz,int tam){
	int i=0,j=0;
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			printf("%d, ",matriz[i][j]);
		}
		printf("\n");
	}
	return;
}
void vaciarMatriz(int **matriz,int dimension){
	int i=0,j=0;
	for(i=0;i<dimension;i++){
		for(j=0;j<dimension;j++){
			matriz[i][j]=0;
		}
	}
	
	return;
}
int mayor(int **matriz,int alto, int ancho){
	int m=0,i,j;
	for(i=0;i<alto;i++){
		for(j=0;j<ancho;j++){
			if(matriz[i][j]>m){
				m=matriz[i][j];
			}
		}
	}
	return m;
}
int menor(int **matriz,int alto, int ancho){
	int m=257,i,j;
	for(i=0;i<alto;i++){
		for(j=0;j<ancho;j++){
			if(matriz[i][j]<m){
				m=matriz[i][j];
			}
		}
	}
	return m;
}
int comprobarUniformidad(int **matriz, int alto,int ancho, int uniformidad){
	int min, max;
	int **subMatriz;
	min=menor(matriz,alto,ancho);
	max=mayor(matriz,alto,ancho);
	if(max-min>uniformidad){
		return max-min;
	}
	else{
		return max-min;
	}	
}
void llenarCeros(int **matriz,int dimension){
	int n,m;
	for(n=0;n<dimension;n++){
		for(m=0;m<dimension;m++){
			matriz[n][m]=-1;
		}
	}
}
void mostrarMatrizNoCuadrada(int **matriz,int alto,int ancho){
	int i,j;
	for(i=0;i<alto;i++){
		for(j=0;j<ancho;j++){
			printf("%d, ",matriz[i][j]);
		}
		printf("\n");
	}
}
void division(int **matriz,int dimension, int uniformidad,int **subMatrizFinal,int dimensionOriginal,int *corrimiento,int **matrizOriginal, struct nodo* nodo){
	int i, j, anchoNuevo=0, altoNuevo=0,numElementos,contador=0,zonas,nuevaDimension,contador2=10,subzona=0,ric=0,ric2=0,cont=0,coordenada;
	int **subMatriz,**subMatriz2;
	numElementos = (dimension*dimension)/4;
	zonas=(dimension*dimension)/numElementos;
	nuevaDimension=sqrt(numElementos);
	darMemoria(&subMatriz2,dimensionOriginal,dimensionOriginal);
	llenarCeros(subMatriz2,dimensionOriginal);
	if((dimension)*(dimension)%4==0&&dimension*dimension/4!=1&&comprobarUniformidad(matriz,dimension,dimension,uniformidad)>uniformidad){
		printf("dimension %d\n",dimension);
		printf("nueva dimension %d\n",nuevaDimension);
		printf("num elementos %d\n",numElementos);
		darMemoria(&subMatriz,sqrt(numElementos),sqrt(numElementos));
		while(contador<zonas){
			(*corrimiento)++;
			for(i=0;i<sqrt(numElementos);i++){
				for(j=0;j<sqrt(numElementos);j++){
					subMatriz[i][j]=matriz[i+altoNuevo][j+anchoNuevo];
					subMatrizFinal[i+altoNuevo][j+anchoNuevo]=contador+1;
					subMatriz2[i+altoNuevo][j+anchoNuevo]=matriz[i+altoNuevo][j+anchoNuevo];
					//printf("%d, ",matrizOriginal[i+anchoNuevo][j+altoNuevo]);
				}
				//printf("\n");
			}
			//printf("mostrando matriz zona: %d\n",contador+1);
			//mostrarMatriz(subMatriz,sqrt(numElementos));
			if(contador==0){
				nodo->nw=crearNodo(sqrt(numElementos),subMatriz);
				mostrarMatriz(nodo->nw->dato,sqrt(numElementos));
			}
			else if(contador==1){
				nodo->ne=crearNodo(sqrt(numElementos),subMatriz);
				mostrarMatriz(nodo->ne->dato,sqrt(numElementos));
			}
			else if(contador==2){
				nodo->sw=crearNodo(sqrt(numElementos),subMatriz);
				mostrarMatriz(nodo->sw->dato,sqrt(numElementos));
			}
			else{
				nodo->se=crearNodo(sqrt(numElementos),subMatriz);
				mostrarMatriz(nodo->se->dato,sqrt(numElementos));
			}
			//printf("mostrando submatriz zona %d subzona %d completa\n",contador+1,subzona+1);
			//mostrarMatriz(subMatriz2,dimensionOriginal);
			contador++;
			if(comprobarUniformidad(subMatriz,nuevaDimension,nuevaDimension,uniformidad)>uniformidad){
			
				subzona=subzona+1;
				//printf("RECURSION\n");
				if(contador==0){
				division(subMatriz,nuevaDimension,uniformidad,subMatrizFinal,dimensionOriginal,corrimiento,matrizOriginal,nodo->nw);	
				}
				else if(contador==1){
				division(subMatriz,nuevaDimension,uniformidad,subMatrizFinal,dimensionOriginal,corrimiento,matrizOriginal,nodo->ne);	
				}
				else if(contador==2){
				division(subMatriz,nuevaDimension,uniformidad,subMatrizFinal,dimensionOriginal,corrimiento,matrizOriginal,nodo->sw);	
				}
				else{
				division(subMatriz,nuevaDimension,uniformidad,subMatrizFinal,dimensionOriginal,corrimiento,matrizOriginal,nodo->se);	
				}
				//(*corrimiento)--;
			}
			if(contador==0){
				anchoNuevo=0;
				altoNuevo=0;
				ric=0;
				ric2=0;
			}
			
			else if(contador==1){
				anchoNuevo=nuevaDimension;
				altoNuevo=0;
				ric=0;
				ric2=numElementos;
				
			}
			else if(contador==2){
				anchoNuevo=0;
				altoNuevo=nuevaDimension;
				ric2=0;
				ric=numElementos;
			
			}
			else if(contador==3){
				anchoNuevo=nuevaDimension;
				altoNuevo=nuevaDimension;
				ric=numElementos;
				ric2=numElementos;
		
			}
			llenarCeros(subMatriz2,dimensionOriginal);
		
		}
		
		
		}
		else if(dimension*dimension%4==0&&dimension*dimension/4==1){
			printf("NYANPASSU\n");
			printf("dimension %d\n",dimension);
			printf("nueva dimension %d\n",nuevaDimension);
			zonas=(dimension*dimension)/numElementos;
			while(contador<zonas){
				(*corrimiento)++;
			//printf("matriz zona: %d(fin recursion, caso un elemento)\n",contador+1);
			for(i=0;i<1;i++){
				for(j=0;j<1;j++){
					//printf("%d,",matriz[i+altoNuevo][j+anchoNuevo]);
					subMatriz[i][j]=matriz[i+altoNuevo][j+anchoNuevo];
					subMatriz2[i+altoNuevo][j+anchoNuevo]=matriz[i+altoNuevo][j+anchoNuevo];
				}
				//printf("\n");
			}
			//printf("mostrando matriz zona(caso un elemento): %d\n",contador+1);
			//mostrarMatriz(subMatriz,1);
			//printf("mostrando matriz completa zona(caso un elemento): %d\n",contador+1);
			//mostrarMatriz(subMatriz2,dimensionOriginal);
			contador++;
			if(contador==1){
				anchoNuevo=1;
				altoNuevo=0;
			}
			else if(contador==2){
				anchoNuevo=0;
				altoNuevo=1;
			}
			else if(contador==3){
				anchoNuevo=1;
				altoNuevo=1;
			
			}
			llenarCeros(subMatriz2,dimensionOriginal);
		
		}
		}
		else{
			printf("Matriz de entrada no se puede subdividir\n");
			return;
		}
	//printf("submatriz final con zonas: \n");
	//mostrarMatriz(subMatrizFinal,dimensionOriginal);	
}

void division2(int **matriz,int dimension, int uniformidad,int quad,int **subMatrizFinal,int dimensionOriginal,int *corrimiento,int alto, int ancho,int ric, int ric2,int ric3,int ric4){
	int i, j, anchoNuevo=0, altoNuevo=0,numElementos,contador=0,zonas,nuevaDimension,contador2=10,subzona=0,cont=0,corr,limAltura,limAncho;
	int **subMatriz,**subMatriz2;
	numElementos = (dimension*dimension);
	zonas=(dimension*dimension)/4;
	if(dimension==1){
		nuevaDimension=1;
	}
	else{
		nuevaDimension=sqrt(numElementos)/2;
	}
	corr=dimensionOriginal-nuevaDimension;
	darMemoria(&subMatriz2,dimensionOriginal,dimensionOriginal);
	llenarCeros(subMatriz2,dimensionOriginal);
	limAltura=dimensionOriginal-ric3;
	limAncho=dimensionOriginal-ric4;
	//printf("limite altura y limite ancho = %d, %d\n",limAltura,limAncho);
	if(((numElementos==4)||(dimension%4==0))){
	
		printf("dimension %d, nueva dimensuon %d\n",dimension,nuevaDimension);
		//printf("numeroElementos %d\n",numElementos);
		printf("uguu\n");
		for(i=ric;i<limAltura;i++){
			for(j=ric2;j<limAncho;j++){
				printf("%d, ",matriz[i][j]);
			}
				printf("\n");
		}
		division2(matriz,nuevaDimension, uniformidad,0,subMatrizFinal,dimensionOriginal,corrimiento,dimensionOriginal,dimensionOriginal,0,0,dimension/2,dimension/2);
		division2(matriz,nuevaDimension, uniformidad,1,subMatrizFinal,dimensionOriginal,corrimiento,dimensionOriginal,dimensionOriginal,0,dimension/2,dimension/2,0);
		division2(matriz,nuevaDimension, uniformidad,2,subMatrizFinal,dimensionOriginal,corrimiento,dimensionOriginal,dimensionOriginal,dimension/2,0,0,dimension/2);
		division2(matriz,nuevaDimension, uniformidad,3,subMatrizFinal,dimensionOriginal,corrimiento,dimensionOriginal,dimensionOriginal,dimension/2,dimension/2,0,0);
		contador++;
		if(contador==1){
				anchoNuevo=dimension;
				altoNuevo=0;
			}
			else if(contador==2){
				anchoNuevo=0;
				altoNuevo=nuevaDimension;
			}
			else if(contador==3){
				anchoNuevo=nuevaDimension;
				altoNuevo=nuevaDimension;
			}
			llenarCeros(subMatriz2,dimensionOriginal);
			
}
	if(dimension==1){
		//printf("caso final, corr %d, dimension %d, dimension original %d\n",corr,nuevaDimension,dimensionOriginal);
		for(i=ric;i<limAltura;i++){
			for(j=ric2;j<limAncho;j++){
				printf("%d, ",matriz[i][j]);
			}
				printf("\n");
		}
	}
	(*corrimiento)++;
}
	
	
	

int main(){
	FILE *archivo_Entrada, *archivo_Salida;
	int n,i,j,rgb,**matriz,uni=2,z=16,raiz,numeroElementos,caso=0,**subMatrizFinal,corrimiento=0,ric=0,ric2=0,ric3=0,ric4=0; 
	raiz=sqrt(z);
	printf("%d\n",raiz);
	char aux;
	archivo_Entrada=fopen("Entrada.txt","r");
	printf("uguu\n");
	fscanf(archivo_Entrada,"%d\n",&n);
	printf("uguu\n");
	printf("Dimension matriz: %d\n",n);
	darMemoria(&matriz, n, n);
	darMemoria(&subMatrizFinal,n,n);
	numeroElementos=n*n;
	if(n<=0){
		printf("Formato de archivo incorrecto, dimensión matriz es menor o igual a 0");
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(archivo_Entrada,"%d%c",&rgb,&aux);
			llenarMatriz(matriz,i,j,rgb);
				if(aux=='\r'){
					aux=fgetc(archivo_Entrada);
				}
		}
	}
	mostrarMatriz(matriz,n);
	struct nodo *root=crearNodo(n,matriz);
	division(matriz,n, uni,subMatrizFinal,n,&corrimiento,matriz,root);
	//division2(matriz,n, uni,caso,subMatrizFinal,n,&corrimiento,n,n,ric,ric2,ric3,ric4);
	printf("contador corrimiento: %d\n",corrimiento);
	fclose(archivo_Entrada);
	printf("FIN\n");
	mostrarPreorden(root);
	
	return 0;
}
