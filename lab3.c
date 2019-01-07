#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
typedef struct nodoLista{
	char valor;
	struct nodoLista *siguiente;
} nodo;

typedef struct datosLista{
	int tamanio;
	nodo *cabeza;
	nodo *fin;
} lista;
typedef struct TablaPagina{
	int numEntradas;
	int tamEntradas;
	int *entradas;
	
	}TP;
typedef struct TLB{
	int numElementos;
	int **matrizTLB;
	
	}TLB;

typedef struct TablaPaginaRaiz{
	int numEntradas;
	int tamEntradas;
	TP **entradas;
	
	}TPR;

lista crearLista();
nodo *crearNodo(char elemento);
char obtener(lista actual, int posicion);
lista borrar(lista actual, int posicion);
nodo *siguiente(lista actual, int avanzar);
nodo *anterior(lista actual, int retroceder);
lista anular(lista actual);
nodo *primero(lista actual);
void mostrar(lista actual);
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria);

int compareList(lista actual1, lista actual2, int initOffset, int finOffset){
	int aux1, aux2;
	int contador = actual1.tamanio - initOffset - finOffset;
	for(int i = initOffset; i<actual1.tamanio-finOffset; i++){
		aux1 = obtener(actual1, i);
		aux2 = obtener(actual2, i);
		if(aux1 == aux2){
			contador--;
			}
		
		}
	if(contador == 0){
		return 1;
		}
	return 0;
	}


int listaToInt(lista actual, int initOffset, int finOffset){
	//nodo *nodoPos;
	int entero=0;
	char buffer[17];
	char *aux;
	aux = (char*)malloc(17*sizeof(char*));
	for(int i=0; i<16;i++){
		buffer[i]=0;
		}
	buffer[16] = '\0';
	//nodoPos = actual.cabeza;
	for(int i = initOffset; i<actual.tamanio-finOffset; i++){
		buffer[i] = obtener(actual, i);
		
		}
	printf("buffer: %s\n", buffer);
	//entero = atoi(buffer);
	printf("%li",strtol(buffer, &aux, 17));
	entero = strtol(buffer, &aux, 17);
	return entero;
	}
void inicializarTPR(TPR *tpr, int bitRaiz, int bitSecundaria){
	tpr->numEntradas = pow(2, bitRaiz);
	tpr->tamEntradas = 0; //cambiar este valor por el valido o borrarlo porque quizas no sirve
	tpr->entradas = (TP**)malloc(tpr->numEntradas*sizeof(TP**));
	for(int i = 0;i<tpr->numEntradas;i++){
		tpr->entradas[i] = (TP*)malloc(sizeof(TP*));
		inicializarTP(tpr->entradas[i], bitRaiz, bitSecundaria);
		}
	}
void mostrarTPR(TPR *tpr){
	int iterador = tpr->numEntradas;
	printf("		");
	for(int i=0;i<tpr->entradas[0]->numEntradas;i++){
		printf("E%d	",i);
		}
	printf("\n");
	for(int i=0; i<iterador;i++){
		printf("Entrada %d	", i);
		for(int j = 0; j<tpr->entradas[i]->numEntradas;j++){
			printf("%d	", tpr->entradas[i]->entradas[j]);
			}
		printf("\n");
		}
	printf("\n");
	
	}

void inicializarTLB(TLB *tlb, int entradasTLB){
	tlb->numElementos = entradasTLB;
	printf("antes primera memoria a matriz, num entradas: %d\n", entradasTLB);
	tlb->matrizTLB = (int **)malloc(entradasTLB*sizeof(int*));
	printf("adespues primera memoria a matriz\n");
	//*tabla = (Casilla**)malloc(row*sizeof(Casilla));
	for(int i=0;i<entradasTLB;i++){
		tlb->matrizTLB[i] = (int*)malloc(16*sizeof(int));
		}
	printf("despues darle memoria a matriz\n");
	for(int i= 0;i<entradasTLB;i++){
		for(int  j = 0;j<16;j++){
			printf("indices i-j; %d-%d\n",i,j);
			tlb->matrizTLB[i][j] = 0;
			}
		
		}
	}
void mostrarTLB(TLB *tlb){
	for(int i= 0;i<tlb->numElementos;i++){
		for(int  j = 0;j<16;j++){
			printf("%d ", tlb->matrizTLB[i][j]);
			}
		printf("\n");
		}
	printf("\n");
	}
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria){
	tabla->tamEntradas = pow(2,16-bitRaiz-bitSecundaria);
	tabla->numEntradas = pow(2,16)/tabla->tamEntradas;
	tabla->entradas = (int*)malloc(tabla->numEntradas*sizeof(int*));
	for(int i=0;i<tabla->numEntradas;i++){
		tabla->entradas[i] = 0;
		}
	printf("tamanio entradas TP %d\n", tabla->tamEntradas);
	printf("numero entradas TP %d\n", tabla->numEntradas);
	}

lista crearLista(){
	lista nueva;
	nueva.cabeza = NULL;
	nueva.fin = NULL;
	nueva.tamanio=0;
	return nueva;
}
nodo *crearNodo(char elemento){
	nodo *nuevo = malloc(sizeof(nodo));
	if(!nuevo){
		return NULL;
	}
	nuevo->valor=elemento;
	nuevo->siguiente=NULL;
	return nuevo;
}

lista insertar(lista actual, char elemento, int posicion){
	nodo *nuevo=crearNodo(elemento);
	nodo *nodoPos=NULL;
	int contador;
	if(actual.tamanio==0){
		nuevo->siguiente=nuevo;
		actual.cabeza=nuevo;
		actual.fin=nuevo;
		actual.tamanio++;
		return actual;
		}
	if(posicion>actual.tamanio||posicion<0){
		return actual;
		}
	if(!nuevo){
		return actual;
		}
	if(posicion==0){
		nuevo->siguiente=actual.cabeza;
		actual.cabeza=nuevo;
		actual.tamanio++;
		return actual;
		}
	if(posicion!=0&&posicion==actual.tamanio){
		nuevo->siguiente=actual.cabeza;
		actual.fin=nuevo;
		}
	nodoPos=actual.cabeza;
	for(contador=0;contador<posicion-1;contador++){
		nodoPos=nodoPos->siguiente;
	}
	nuevo->siguiente=nodoPos->siguiente;
	nodoPos->siguiente=nuevo;
	actual.tamanio++;
	return actual;
	}
int buscar(lista actual, char elemento){
	nodo *nodoPos=actual.cabeza;
	int posicion=0;
	while(nodoPos){
		if(nodoPos->valor==elemento){
			return posicion;
		}
		nodoPos=nodoPos->siguiente;
		posicion++;
	}
	posicion=-1;
	return posicion;
}
char obtener(lista actual, int posicion){
	nodo *nodoPos=NULL;
	int contador;
	nodoPos=actual.cabeza;
	for(contador=0;contador<posicion;contador++){
		nodoPos=nodoPos->siguiente;
	}
	return nodoPos->valor;
}
lista borrar(lista actual, int posicion){
	nodo *nodoPos=actual.cabeza;
	nodo *auxiliar=NULL;
	int cuenta=0;
	if(posicion<0||posicion>=actual.tamanio){
		return actual;
		}
	if(posicion==0){
		if(actual.tamanio==1){
			actual.cabeza=NULL;
			actual.fin=NULL;
			free(nodoPos);
			actual.tamanio=0;
			return actual;
			}
		else{
			auxiliar=actual.cabeza;
			auxiliar->siguiente=nodoPos->siguiente;
			auxiliar=auxiliar->siguiente;
			actual.cabeza=nodoPos->siguiente;
			free(nodoPos);
			nodoPos=NULL;
			actual.tamanio--;
			return actual;
			}
		}
	while(cuenta<posicion-1){
		nodoPos=nodoPos->siguiente;
		cuenta++;
		}
	auxiliar=nodoPos->siguiente;
	nodoPos->siguiente=auxiliar->siguiente;
	free(auxiliar);
	auxiliar=NULL;
	actual.tamanio--;
	return actual;
	}
lista mover(lista actual){
	nodo *nodoPos=actual.cabeza;
	int i=0;
	
	if(actual.tamanio==0||actual.tamanio==1){
		return actual;
	}
	for(i=0;i<actual.tamanio;i++){
		if(i==actual.tamanio-1){
			actual.cabeza=nodoPos;
			}
		if(i==actual.tamanio-2){
			actual.fin=nodoPos;
			}
		nodoPos=nodoPos->siguiente;
		}
		
	
	return actual;
	}
lista moverAtras(lista actual){
	nodo *nodoPos=actual.cabeza;
	int i=0;
	if(actual.tamanio==0||actual.tamanio==1){
		return actual;
	}
	for(i=0;i<actual.tamanio;i++){
		if(i==1){
			actual.cabeza=nodoPos;
			}
		if(i==actual.tamanio-2){
			actual.fin=nodoPos;
			}
		nodoPos=nodoPos->siguiente;
		}	
	return actual;
}
nodo *siguiente(lista actual, int avanzar){
	nodo *nodoPos = actual.cabeza;
	int contador=0;
	for(contador=0;contador<avanzar;contador++){
		nodoPos=nodoPos->siguiente;
	}
	return nodoPos->siguiente;
}
nodo *anterior(lista actual, int retroceder){
	nodo *nodoPos = actual.cabeza;
	int contador=0;
	for(contador=0;contador<retroceder-1;contador++){
		nodoPos=nodoPos->siguiente;
	}
	return nodoPos;
}
lista anular(lista actual){
	while(actual.tamanio>0){
		actual=borrar(actual, 0);
	}
	return actual;
}
nodo *primero(lista actual){
	return actual.cabeza;
}
void mostrar(lista actual){
	nodo *nodoPos=actual.cabeza;
	int contador=0;
	while(nodoPos){
		printf("%c",nodoPos->valor);
		nodoPos=nodoPos->siguiente;
		contador++;
		if(contador==actual.tamanio){
			break;
		}
	}
	printf("\n");
}
void mostrar_indefinidamente(lista actual){
    nodo *nodoPos=actual.cabeza;
    int contador=0,contador2=0;
    while (1){
        printf ("%c", nodoPos->valor);
        nodoPos = nodoPos->siguiente;
        contador++;
		if(contador==actual.tamanio){
			printf("\n");
			printf("vuelta\n");
			contador=0;
			contador2++;
			if(contador2==5){
				break;
			}
		}
    }
}
void mostrar_indefinidamenteAlReves(lista actual){
    nodo *nodoPos=actual.fin;
    int contador=actual.tamanio,contador2=0;
    while (1){
		nodoPos=anterior(actual,contador);
        printf ("%c", nodoPos->valor);
        contador--;
		if(contador==0){
			printf("\n");
			printf("vuelta\n");
			contador=actual.tamanio;
			contador2++;
			if(contador2==5){
				break;
			}
		}
    }
}
lista ordenar(lista actual){
	lista ordenada;
	int contador=0;
	char aux;
	char menor=123;
	int i, pos;
	ordenada=crearLista();
	while(actual.tamanio>0){
		for(i=0;i<actual.tamanio;i++){
			aux=obtener(actual,i);
			printf("%c ",aux);
			if(aux<menor){
				menor=aux;
				pos=i;
			}
			else if(aux==menor){
				actual=borrar(actual, i);
				i--;
			}
		}
	printf("\n");
	i=0;
	ordenada=insertar(ordenada,menor,contador);
	mostrar(ordenada);
	contador++;
	actual = borrar(actual,pos);
	menor=123;
}
ordenada =insertar(ordenada,' ',contador);
actual=anular(actual);
return ordenada;
}
//Procedimiento que usa getopt para recibir argumentos respecto al numero de hijos y el flag -m que indica si debe mostrarse informacion por pantalla o no
//Entradas: recibe el numero de argumentos ingresados, los argumentos y un puntero a las variables numHijos y flag para modificarlas en el scope global del proceso
void getArguments(int argc, char *argv[], int *bitRaiz, int *bitSecundaria, int *entradasTLB, int *flag){
	int flags, opt;
	char *aux3, *aux1, *aux2;
	aux3 = malloc(10*sizeof(char));
	aux1 = malloc(10*sizeof(char));
	aux2 = malloc(10*sizeof(char));
	if(argc <7){//si se ingresa un numero de argumentos menor a 3, se finaliza la ejecucion del programa
		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n", argv[0]);
		exit(EXIT_FAILURE);
		}
	int nTLB = -1, bitsR = -1, bitsS = -1;
	flags = 0;
	while ((opt = getopt(argc, argv, "r:s:t:b")) != -1) {
	   switch (opt) {
	   case 'b'://se busca el flag -b, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
		   flags = 1;
		   break;
	   case 't': //se busca el flag -r
		   nTLB = strtol(optarg, &aux3, 10);//se parsea el argumento ingresado junto al flag -t a entero
		   if(optarg!=0 && nTLB==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n", argv[0]);
				exit(EXIT_FAILURE);
			   }
		   //printf("optarg: %s\n", optarg);
		   break;
		case 'r': //se busca el flag -r
		   bitsR = strtol(optarg, &aux1, 10);//se parsea el argumento ingresado junto al flag -r a entero
		   if(optarg!=0 && nTLB==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n", argv[0]);
				exit(EXIT_FAILURE);
			   }
		   //printf("optarg: %s\n", optarg);
		   break;
		case 's': //se busca el flag -r
		   bitsS = strtol(optarg, &aux2, 10);//se parsea el argumento ingresado junto al flag -t a entero
		   if(optarg!=0 && nTLB==0){//si no se ingresa un argumento junto a -h o si no se logra parsear el argumento ingresado, se considera como invalido
				fprintf(stderr, "Uso correcto: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n", argv[0]);
				exit(EXIT_FAILURE);
			   }
		   //printf("optarg: %s\n", optarg);
		   break;
	   default: /* '?' */
		   fprintf(stderr, "Uso correcto: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n",argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}

	if(flags==1){//si se encontro un flag -m, se setea la variable global flag = 1, respecto al scope del proceso principal
		(*flag) = 1;
		}
	(*bitRaiz) = nTLB; //se iguala la variable bitRaiz a nTLB
	(*bitSecundaria) = bitsS;
	(*entradasTLB) = bitsR;
	if(bitsS<0||bitsR<0||nTLB<0||bitsS+bitsR>16){
		fprintf(stderr, "Usage: %s [-r bitsRaiz][-s bitsSecundaria][-t entradasTLB] [-b]\n", argv[0]); //si la cantidad de hijos es negativa, se retorna un error
		exit(EXIT_FAILURE);
		}


}
void intToBin(int dec, int bin[], int numBits){
    for(int i = 0; i < numBits; i++){
        bin[i] = 1 & (dec >> i);
    }
}


lista reverseLista(lista actual){
	lista nueva = crearLista();
	int contador = actual.tamanio;
	int elementos = 0;
	while(contador>0){
		//int pos = 
		nueva = insertar(nueva, anterior(actual,contador)->valor, elementos);
		contador--;
		elementos++;
		}
	return nueva;
	}
lista traducirHexToBin(lista dirHex){
	lista listB = crearLista();
	int i = 0;
	int largo = 4;
	int j=0;
	char dec;
	int integer;
	for(i=0;i<largo;i++){
		dec = obtener(dirHex, 3-i);
		//printf("num a transformar: %c\n", dec);		
		if(dec == 'A'){
			integer = 10;
			}
		else if(dec == 'B'){
			integer = 11;
			}
		else if(dec == 'C'){
			integer = 12;
			}
		else if(dec == 'D'){
			integer = 13;
			}
		else if(dec == 'E'){
			integer = 14;
			}
		else if(dec == 'F'){
			integer = 15;
			}
		else{
			integer = (int)dec-'0';
			}
		for(j=0;j<4;j++){
			int aux =(integer >> j)&1;
			//printf("%d", aux);
			if(aux == 1){
				listB = insertar(listB, '1', j+4*i);
				}
			else{
				listB = insertar(listB, '0', j+4*i);
				}
			
			}
		}
	//printf("\n");
	//mostrar(listB);
	//printf("%d\n", listB.tamanio);
	listB = reverseLista(listB);
	return listB;
	
	}
lista* leerArchivoEntrada(lista *l){
	int contador = 0;
	printf("antes abrir\n");
	FILE *entrada = fopen("archivo1.txt", "r");
	printf("despues abrir\n");
	printf("abriendo archivo\n");
	if(entrada==NULL){
		printf("Archivo no existe\n");
		fclose(entrada);
		return l;
		}
	char aux1, aux2, aux3, hex1, hex2, hex3, hex4;
	while(fscanf(entrada, "%c%c%c%c%c%c%c", &aux1,&aux2,&hex1,&hex2,&hex3,&hex4,&aux3)==7){
		printf("the worst\n");
		printf("%c%c%c%c%c%c%c", aux1,aux2,hex1,hex2,hex3,hex4,aux3);
		l[contador] = insertar(l[contador],hex1, 0);
		l[contador] = insertar(l[contador],hex2, 1);
		l[contador] = insertar(l[contador],hex3, 2);
		l[contador] = insertar(l[contador],hex4, 3);
		printf("the worst2\n");
		contador++;
	}
	printf("the worst3\n");
	fclose(entrada);
	return l;
	}
lista* leerArchivoMarcos(int bitsRaiz, int bitsSecundarias, lista *l){
	printf("antes abrir\n");
	FILE *entrada = fopen("archivo2.txt", "r");
	printf("despues abrir\n");
	printf("abriendo archivo\n");
	if(entrada==NULL){
		printf("Archivo no existe\n");
		fclose(entrada);
		return l;
		}
	char aux1, aux2, aux3, hex1, hex2, hex3, hex4;
	int iteraciones = pow(2,bitsRaiz)*pow(2,bitsSecundarias), contador = 0;
	while(fscanf(entrada, "%c%c%c%c%c%c%c", &aux1,&aux2,&hex1,&hex2,&hex3,&hex4,&aux3)==7){
		printf("the worst\n");
		printf("%c%c%c%c%c%c%c", aux1,aux2,hex1,hex2,hex3,hex4,aux3);
		l[contador] = insertar(l[contador],hex1, 0);
		l[contador] = insertar(l[contador],hex2, 1);
		l[contador] = insertar(l[contador],hex3, 2);
		l[contador] = insertar(l[contador],hex4, 3);
		printf("the worst2\n");
		contador++;
		iteraciones--;
		if(iteraciones<=0){
			fclose(entrada);
			return l;
			}
		
	}
	printf("the worst3\n");
	fclose(entrada);
	return l;
	
	}

int main(int argc, char *argv[]){
	char caracteres[4] = {'2', '3', '0', '0'};
	printf("UWU\n");
	lista l = crearLista();
	lista b = crearLista();
	TPR *tpr;
	int numeroMarcos = pow(2,2)*pow(2,2);
	int bitRaiz, bitSecundaria, entradasTLB, flag=0;
	//lista *arrayLista = (lista*)malloc(5*sizeof(lista));
	//lista arrayLista[numeroMarcos];
	lista *arrayLista = (lista*)malloc(numeroMarcos*4*sizeof(lista*));
	lista *arrayListaBin = (lista*)malloc(numeroMarcos*16*sizeof(lista*));
	TLB *tlb;
	getArguments(argc, argv, &bitRaiz, &bitSecundaria, &entradasTLB, &flag);
	printf("mostrando TPR y TP\n");
	tpr = (TPR*)malloc(sizeof(TPR*));
	inicializarTPR(tpr, bitRaiz, bitSecundaria);
	mostrarTPR(tpr);
	printf("finalizando mostrar TPR y TP\n");
	tlb = (TLB*)malloc(sizeof(TLB*));
	printf("antes TLB\n");
	inicializarTLB(tlb, 10);
	mostrarTLB(tlb);
	printf("DESPUES TLB\n");
	printf("MOSTRANDO ARREGLO LISTAS: \n");
	for(int i = 0;i<numeroMarcos;i++){
		arrayLista[i] = crearLista();
		printf("owo\n");
		}
	printf("iwi\n");
	leerArchivoMarcos(2, 2, arrayLista);
	for(int i =0;i<numeroMarcos;i++){
		mostrar(arrayLista[i]);
		}
	printf("TRADUCCIONDE HEX A BIN: \n");
	for(int i = 0;i<numeroMarcos;i++){
		arrayListaBin[i] = crearLista();
		arrayListaBin[i] =traducirHexToBin(arrayLista[i]);
		mostrar(arrayListaBin[i]);
		
		}
	
	printf("$$$$$$$$$$$$$$$$$$$$$$$$\n");
	TP *tabla;
	tabla = (TP *)malloc(sizeof(TP*));
	inicializarTP(tabla, 5, 6);
	printf("%d\n", tabla->numEntradas);
	printf("%d\n", tabla->tamEntradas);
	for(int i=0;i<4;i++){
		l = insertar(l, caracteres[i], i);
		}
	mostrar(l);
	b = traducirHexToBin(l);
	mostrar(b);
	int entero = listaToInt(b, 0, 0);
	printf("lista a entero: %d\n", entero);
	int bool =compareList(b, b, 0, 0);
	printf("comparacion: %d\n", bool);
	return 0;
	}
