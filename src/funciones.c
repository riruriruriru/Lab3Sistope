#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funciones.h"
#include "estructuras.h"

int convertBinaryToDecimal(long long n){
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
//Funcionamiento: Recibe dos listas de igual tamanio y compara sus valores entre los offset inicial y final ingresados, si todos los valores comparados son iguales, se retorna un 1
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
//Entradas: Recibe una lista con un binario de 16 digitos, ademas de un offset inicial y final: 0-16 para transformar el binario completo, x,y para transformar entre rangos x-y
//Funcionamiento: Recorre una lista de un binario y la guarda en un buffer, luego transforma ese buffer a un long int para representar el binario en forma de int, se borran los ceros a la izquierda
//Salida: Binario transformado a long int
//Ejemplo: binario en lista "0000000111110011" se transforma a long int: "111110011"
long int listaToInt(lista actual, int initOffset, int finOffset){
	//nodo *nodoPos;
	long int entero=0;
	char buffer[17];
	//mostrar(actual);
	for(int i=0; i<16;i++){
		buffer[i]=0;
		}
	buffer[16] = '\0';
	//nodoPos = actual.cabeza;
	for(int i = initOffset; i<finOffset; i++){
		buffer[i] = obtener(actual, i);
		entero = entero + (buffer[i]-'0')*pow(10,finOffset-i-1);
		//printf("entero: %li\n", entero);
		}
	//printf("buffer: %s\n", buffer);
	//entero = atoi(buffer);
	//printf("entero: %li", entero);
	//entero = convertBinaryToDecimal(entero); //por si es que fuera necesario usar el valor en decimal
	//printf("%ld\n",entero);
	return entero;
	}
//Entradas: puntero a tabla de pagina raiz, bits para tablas raiz y bits para tablas secundarias
//Funcionamiento: inicializa los valores de la TPR, calculando el numero de tablas de paginas que contiene: 2^bitsRaiz, luego inicializa cada tabla de pagina por separado
//Por lo tanto, la TPR contiene 2^bitRaiz tablas de pagina secundarias
void inicializarTPR(TPR *tpr, int bitRaiz, int bitSecundaria){
	tpr->numEntradas = pow(2, bitRaiz);
	tpr->tamEntradas = 0; //cambiar este valor por el valido o borrarlo porque quizas no sirve
	tpr->entradas = (TP**)malloc(tpr->numEntradas*sizeof(TP**));
	tpr->elementosUsados = 0;
	for(int i = 0;i<tpr->numEntradas;i++){
		tpr->entradas[i] = (TP*)malloc(sizeof(TP*));
		inicializarTP(tpr->entradas[i], bitRaiz, bitSecundaria); //se inicializan las tablas de pagina secundarias
		}
	}
//Entradas: Tabla de pagina raiz
//Funcionamiento: se muestra con formato una tabla de pagina raiz, mostrando en cada fila una tabla de pagina distinta y en cada columna una entrada de la tabla de pagina correspondiente
void mostrarTPR(TPR *tpr){
	int iterador = tpr->numEntradas;
	printf("		");
	for(int i=0;i<tpr->entradas[0]->numEntradas;i++){
		printf("E%d	",i);
		}
	printf("\n");
	for(int i=0; i<iterador;i++){
		printf("TablaP %d	", i);
		for(int j = 0; j<tpr->entradas[i]->numEntradas;j++){
			printf("%li	", tpr->entradas[i]->entradas[j]);
			}
		printf("\n");
		}
	printf("\n");
	
	}

void inicializarTLB(TLB *tlb, int entradasTLB){
	tlb->numElementos = entradasTLB;
	tlb->nPagina = (long int*)malloc(entradasTLB*sizeof(long int));
	tlb->entradas = (long int*)malloc(entradasTLB*sizeof(long int));
	//printf("antes primera memoria a matriz, num entradas: %d\n", entradasTLB);
	//printf("adespues primera memoria a matriz\n");
	//*tabla = (Casilla**)malloc(row*sizeof(Casilla));
	for(int i=0;i<entradasTLB;i++){
		tlb->nPagina[i] = -1;
		}
	//printf("despues darle memoria a matriz\n");
	}
//Entradas: tabla de pagina raiz, lista con direcciones de marcos en binario, bit raiz, bit secundaria y n° de bits de marcos
//Funcionamiento: Se recorre la lista de lista de direcciones en binario y se va llenando secuencialmente cada tabla de pagina secundaria
//Es decir, primero se llena la tabla secundaria de indice 0, cuando esta se llena completamente, se continua con la 1 y asi sucesivamente
void llenarTR(TPR *tpr, lista *listaDireccionesBin, int bitRaiz, int bitSecundaria, int bitMarcos, int bitOffset){
	int iteraciones = pow(2,bitRaiz)*pow(2,bitSecundaria);
	int numTablasPagina = pow(2, bitRaiz);
	int paginasXTabla = pow(2, bitSecundaria);
	int tablaPagina = 0;
	int iterador=0;
	int indiceTP = 0;
	while(iterador<iteraciones){
		if(indiceTP==paginasXTabla){
			indiceTP = 0;
			tablaPagina++;
			}
		tpr->entradas[tablaPagina]->entradas[indiceTP] = listaToInt(listaDireccionesBin[iterador], 0, bitMarcos);
		iterador++;
		indiceTP++;
		}
	
	
	}
/*void mostrarTLB(TLB *tlb){
	for(int i= 0;i<tlb->numElementos;i++){
		for(int  j = 0;j<16;j++){
			printf("%d ", tlb->matrizTLB[i][j]);
			}
		printf("\n");
		printf("LISTA %d TLB: ", i);
		mostrar(tlb->listaTLB[i]);
		printf("\n");
		}
	printf("\n");
	
	/*for(int i= 0;i<tlb->numElementos;i++){
		printf("\n");
		printf("N° de pagina TLB: %d", tlb->nPagina[i]);
		printf("\n");
		}
	printf("\n");*/
	
	//}
//Entradas: bits de informacion y puntero a tabla de pagina
//Funcionamiento: inicializa una tabla de pagina con un arreglo de long int de tanto largo como entradas pueda tener la tabla de paginas
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria){
	tabla->tamEntradas = pow(2,16-bitRaiz-bitSecundaria);
	tabla->numEntradas = pow(2,bitSecundaria);
	tabla->entradas = (long int*)malloc(tabla->numEntradas*sizeof(long int*));
	for(int i=0;i<tabla->numEntradas;i++){
		tabla->entradas[i] = 0;
		}
	//printf("TP\n");
	//printf("tamanio entradas TP %d\n", tabla->tamEntradas);
	//printf("numero entradas TP %d\n", tabla->numEntradas);
	//printf("TP\n");
	}

lista crearLista(){
	lista nueva;
	nueva.cabeza = NULL;
	nueva.reloj = 0;
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
lista modificar(lista actual, char elemento, int posicion){
	nodo *nodoPos = NULL;
	nodo *nuevo = crearNodo(elemento);
	if(posicion == 0){
		actual.cabeza->valor = elemento;
		return actual;
		}
	else if(posicion == actual.tamanio-1){
		actual.fin->valor = elemento;
		return actual;
		}
	nodoPos = actual.cabeza;
	for(int i = 0; i < posicion-1; i++){
		nodoPos = nodoPos->siguiente;
		}
	nuevo->siguiente = nodoPos->siguiente->siguiente;
	nodoPos->siguiente = nuevo;
	
	return actual;
	
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
	actual.reloj = 0;
	return actual;
	}
int buscar(lista actual, char elemento){
	nodo *nodoPos=actual.cabeza;
	int posicion=0;
	while(nodoPos){
		if(nodoPos->valor==elemento){
			actual.reloj = 1;
			return posicion;
		}
		nodoPos=nodoPos->siguiente;
		posicion++;
	}
	posicion=-1;
	actual.reloj = 0;
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
		   //printf("BITS RAIZ: %d", bitsR);
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
	(*bitRaiz) = bitsR; //se iguala la variable bitRaiz a nTLB
	(*bitSecundaria) = bitsS;
	(*entradasTLB) = nTLB;
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
	//printf("antes abrir\n");
	FILE *entrada = fopen("archivo1.txt", "r");
	//printf("despues abrir\n");
	//printf("abriendo archivo\n");
	if(entrada==NULL){
		printf("Archivo no existe\n");
		fclose(entrada);
		return l;
		}
	char aux1, aux2, aux3, hex1, hex2, hex3, hex4;
	while(fscanf(entrada, "%c%c%c%c%c%c%c", &aux1,&aux2,&hex1,&hex2,&hex3,&hex4,&aux3)==7){
		//printf("the worst\n");
		//printf("%c%c%c%c%c%c%c", aux1,aux2,hex1,hex2,hex3,hex4,aux3);
		l[contador] = insertar(l[contador],hex1, 0);
		l[contador] = insertar(l[contador],hex2, 1);
		l[contador] = insertar(l[contador],hex3, 2);
		l[contador] = insertar(l[contador],hex4, 3);
		//printf("the worst2\n");
		contador++;
	}
	//printf("the worst3\n");
	fclose(entrada);
	return l;
	}
lista* leerArchivoMarcos(int bitsRaiz, int bitsSecundarias, lista *l){
	//printf("antes abrir\n");
	FILE *entrada = fopen("archivo2.txt", "r");
	//printf("despues abrir\n");
	//printf("abriendo archivo\n");
	if(entrada==NULL){
		//printf("Archivo no existe\n");
		fclose(entrada);
		return l;
		}
	char aux1, aux2, aux3, hex1, hex2, hex3, hex4;
	int iteraciones = pow(2,bitsRaiz)*pow(2,bitsSecundarias), contador = 0;
	while(fscanf(entrada, "%c%c%c%c%c%c%c", &aux1,&aux2,&hex1,&hex2,&hex3,&hex4,&aux3)==7){
		//printf("the worst\n");
		//printf("%c%c%c%c%c%c%c", aux1,aux2,hex1,hex2,hex3,hex4,aux3);
		l[contador] = insertar(l[contador],hex1, 0);
		l[contador] = insertar(l[contador],hex2, 1);
		l[contador] = insertar(l[contador],hex3, 2);
		l[contador] = insertar(l[contador],hex4, 3);
		//printf("the worst2\n");
		contador++;
		iteraciones--;
		if(iteraciones<=0){
			fclose(entrada);
			return l;
			}
		
	}
	//printf("the worst3\n");
	fclose(entrada);
	return l;
	
	}
int lineasArchivo(){
	int contador = 0;
	char aux1, aux2, aux3, hex1, hex2, hex3, hex4;
	FILE *entrada;
	entrada = fopen("archivo1.txt", "r");
	while(fscanf(entrada, "%c%c%c%c%c%c%c", &aux1,&aux2,&hex1,&hex2,&hex3,&hex4,&aux3)==7){
		contador++;
	}
	rewind(entrada);
	fclose(entrada);
	return contador;
	}


int BintoInt(lista bin, int nBits){
		int potencia = nBits-1;
		int entero = 0;
		int pos = 0;
		while(potencia >= 0){
			if(obtener(bin,pos)=='0'){
				potencia--;
				pos++;
			}
			else{
				entero += pow(2,potencia);
				potencia--;
				pos++;
			}
			
		}
		return entero;
		
		
	}


char* BinToHex(lista bin){
	lista aux = crearLista();
	int entero;
	char *hex;
	hex = malloc(6*sizeof(char));
	char numero[2];
	hex[0] = '0';
	hex[1] = 'x';
	int pos = 0;
	int posHex = 2;
	for (int i=0;i<=16;i++){
		if (pos == 4){
			pos = 0;
			entero = BintoInt(aux,4);
			if (entero == 10){
				hex[posHex] = 'A';
				posHex++;
			}
			else if (entero == 11){
				hex[posHex] = 'B';
				posHex++;
			}
			else if (entero == 12){
				hex[posHex] = 'C';
				posHex++;
			}
			else if (entero == 13){
				hex[posHex] = 'D';
				posHex++;
			}
			else if (entero == 14){
				hex[posHex] = 'E';
				posHex++;
			}
			else if (entero == 15){
				hex[posHex] = 'F';
				posHex++;
			}
			else{
				sprintf(numero,"%d",entero);
				hex[posHex] = numero[0];
				posHex++;
			}
			if (i == 16){
				break;
			}
			
		}
		aux = insertar(aux,obtener(bin,i),pos);
		pos++;
		
	}
	return hex;
	
	
}

int largoPalabra(char *palabra){
	int contador = 0;
	while(palabra[contador] != '\0'){
		contador++;
	}
	return contador;
}

//Entradas: offset y marco en binario y numero de bits
//Funcionamiento: crea la memoria fisica a partir del marco y del offset
//Salida: direccion memoria fisica en binario
lista memoriaFisica(lista offset, long int marco, int nBits){
	lista memFis = crearLista();
	char buffer[nBits];
	char marcoR[nBits];
	sprintf(buffer,"%ld",marco);
	//printf("buffer: %s\n",buffer);
	int largo = largoPalabra(buffer);
	//printf("largo: %d\n",largo);
	int pos = 0;
	if (largo < nBits){
		for (int i = 0;i < nBits;i++){
			if ((nBits - largo) != 0){
				marcoR[i] = '0';
				largo++;
			}
			else{
				marcoR[i] = buffer[pos];
				pos++;
			}
		}
	}
	else{
		sprintf(marcoR,"%s",buffer);
	}
	//printf("marcoR: %s\n",marcoR);
	
	for (int i = 0; i<nBits; i++){
		memFis = insertar(memFis,marcoR[i],i);
	}
	pos = 0;
	for(int i = nBits;i<16;i++){
		memFis = insertar(memFis,obtener(offset,pos),i);
		pos++;
	}	
	//mostrar(memFis);
	return memFis;
}

//Entradas: direccion logica y los bits de la tabla raiz y secundaria
//Funcionamiento: busca el valor N1 dentro de la direccion logica
//Salida: valor N1 en binario
int obtenerIndiceTPR(lista dirLogicas, int bitRaiz){
		lista bitsTPR = crearLista();
		nodo *nodoPos=dirLogicas.cabeza;
		int contador=0;
		while(nodoPos){
			bitsTPR = insertar(bitsTPR, nodoPos->valor, contador);
			nodoPos=nodoPos->siguiente;
			contador++;
			if(contador==bitRaiz){
				break;
			}
		}
		//mostrar(bitsTPR);
		return BintoInt(bitsTPR,bitRaiz);
	
}

//Entradas: direccion logica y los bits de la tabla raiz y secundaria
//Funcionamiento: busca el valor N2 dentro de la direccion logica
//Salida: valor N2 en binario
int obtenerIndiceTP(lista dirLogicas, int bitRaiz, int bitSecundaria){
		lista bitsTP = crearLista();
		int contador=bitRaiz;
		int pos = 0;
		while(contador!=bitRaiz+bitSecundaria){
			bitsTP = insertar(bitsTP,obtener(dirLogicas,contador), pos);
			contador++;
			pos++;
		}
		//mostrar(bitsTP);
		return BintoInt(bitsTP,bitSecundaria);
	
}

//Entradas: direccion logica en binario y bits de tabla raiz y secundaria
//Funcionamiento: busca el offset dentro de la direccion logica
//Salida: offset en binario
lista obtenerOffset(lista dirLogicas, int bitRaiz, int bitSecundaria){
		lista offset = crearLista();
		int contador=bitRaiz+bitSecundaria;
		int pos = 0;
		while(contador!=16){
			offset = insertar(offset,obtener(dirLogicas,contador), pos);
			contador++;
			pos++;
		}
		//mostrar(offset);
		return offset;
	
}

//Entradas: Arreglo de prioridad y el numero de entradas de la TLB
//Funcionamiento: busca el valor de la maxima prioridad
//Salida: valor maximo
int posMax(int *posRem, int nEntradas){
	int max = posRem[0];
	int posM = 0;
	for (int i = 0; i<nEntradas;i++){
		if (posRem[i]>max){
			max = posRem[i];
			posM = i;
		}
	}
	return max;
}

//Entradas: Recibe arreglo que indica los potenciales paginas a ser reemplazadas dentro de la TLB y el numero de entradas para la TLB
//Funcionamiento: busca dentro del arreglo quien tiene menor prioridad y devuelve la posición de este para ser reemplazado
//Salida: Posición
int buscarFIFOPos(int *posRem, int nEntradas){
	int posAux = 0;
	int menor = posRem[0];
	for(int i = 0;i < nEntradas; i++){
		if (posRem[i] == 0){
			return i;
		}
		else{
			if(posRem[i] < menor){
				menor = posRem[i];
				posAux = i;
			}
		}
	}
	return posAux;
}

//Entradas: Recibe las direcciones logicas a traducir, la cantidad de direcciones, los bits de la tabla raiz y secundaria, el numero de entradas para la TLB y el flag para mostrar los hits
//Funcionamiento: Traduce las direcciones logicas a fisicas, mediante el uso de paginación multinivel y TLB con las 3 politicas de reemplazo, además crea los archivos de salida correspondientes
void direccionFisica(lista *dirLog, int nLineas, TPR *tpr, int bitRaiz, int bitSecundaria, int nEntradas, int flag){
	int Hfifo = 0;
	int Mfifo = 0;
	int Hlru = 0;
	int Mlru = 0;
	int Hclock = 0;
	int Mclock = 0;
	int puntero = 0;
	int auxFIFO = 0;
	int auxLRU = 0;
	int auxCLOCK = 0;
	int posAux;
	int max;
	
	TLB *tlbFIFO = malloc(sizeof(TLB*));
	TLB *tlbLRU = malloc(sizeof(TLB*));
	TLB *tlbCLOCK = malloc(sizeof(TLB*));
	
	inicializarTLB(tlbFIFO,nEntradas);
	inicializarTLB(tlbLRU,nEntradas);
	inicializarTLB(tlbCLOCK,nEntradas);
	
	int remfifo[nEntradas];
	int remlru[nEntradas];
	int remclock[nEntradas];
	
	for(int i=0;i<nEntradas;i++){
		remfifo[i] = 0;
		remlru[i] = 0;
		remclock[i] = 0;
	}
	
	lista offset = crearLista();
	lista dirFisica = crearLista();
	char hex[6];
	int N1;
	int N2;
	long int mr;
	int nPaginas;
	int posHit;
	int posHitClock;
	FILE *salida;
	FILE *salida2;
	salida = fopen("traduccion.txt","w");
	salida2 = fopen("tasas.txt","w");
	for (int i=0;i<nLineas;i++){
		nPaginas = obtenerIndiceTPR(dirLog[i],bitRaiz+bitSecundaria);
		//printf("nPaginas: %d\n",nPaginas);
		N1 = obtenerIndiceTPR(dirLog[i],bitRaiz);
		N2 = obtenerIndiceTP(dirLog[i], bitRaiz, bitSecundaria);
		offset = obtenerOffset(dirLog[i], bitRaiz, bitSecundaria);
		mr = tpr -> entradas[N1] ->entradas[N2];
		dirFisica = memoriaFisica(offset, mr, bitRaiz + bitSecundaria);
		sprintf(hex,"%s",BinToHex(dirFisica));
		fprintf(salida,"%s\n",hex);
		
		for (int j=0; j<nEntradas; j++){
			//printf("pagina encontrada: %ld\n",tlbFIFO->nPagina[i]);
			if (tlbFIFO->nPagina[j] == nPaginas){
				auxFIFO = 1;
			}
			if (tlbLRU->nPagina[j] == nPaginas){
				auxLRU = 1;
				posHit = j;
			}
			if (tlbCLOCK->nPagina[j] == nPaginas){
				auxCLOCK = 1;
				posHitClock = j;
			}
			
		}
		if (auxFIFO == 1){
			Hfifo ++;
			if (flag == 1){
				printf("HIT FIFO en direccion logica: ");
				mostrar(dirLog[i]);
				printf("\n");
			}
			
		}
		if (auxFIFO == 0){
			Mfifo++;
			posAux = buscarFIFOPos(remfifo,nEntradas);
			tlbFIFO->nPagina[posAux] = nPaginas;
			tlbFIFO->entradas[posAux] = mr;
			max = posMax(remfifo,nEntradas);
			remfifo[posAux] = max + 1;
		}
		auxFIFO = 0;
		if (auxLRU == 1){
			Hlru++;
			if (flag == 1){
				printf("HIT LRU en direccion logica: ");
				mostrar(dirLog[i]);
				printf("\n");
			}
			
			
			max = posMax(remlru,nEntradas);
			remlru[posHit] = max + 1;
		}
		if (auxLRU == 0){
			Mlru++;
			posAux = buscarFIFOPos(remlru,nEntradas);
			tlbLRU->nPagina[posAux] = nPaginas;
			tlbLRU->entradas[posAux] = mr;
			max = posMax(remlru,nEntradas);
			remlru[posAux] = max + 1;
		}
		auxLRU = 0;
		if (auxCLOCK == 1){
			Hclock ++;
			if (flag == 1){
				printf("HIT CLOCK en direccion logica: ");
				mostrar(dirLog[i]);
				printf("\n");
			}
			
			if (remclock[posHitClock] == 0){
				remclock[posHitClock] == 0;
			}
		}
		if (auxCLOCK == 0){
			Mclock ++;
			while(remclock[puntero] == 1){
				remclock[puntero] = 0;
				puntero++;
				if (puntero == nEntradas){
					puntero = 0;
				}
			}
			tlbCLOCK -> nPagina[puntero] = nPaginas;
			tlbCLOCK -> entradas[puntero] = mr;
			remclock[puntero] = 1;
			puntero++;
			if (puntero == nEntradas){
				puntero = 0;
			}
		}
		auxCLOCK = 0;
		
		
		
	}
	
	/*for (int i=0;i<nEntradas;i++){
		printf("Pagina FIFO: %ld\n",tlbFIFO->nPagina[i]);
	}
	
	for (int i=0;i<nEntradas;i++){
		printf("Pagina LRU: %ld\n",tlbLRU->nPagina[i]);
	}
	
	for (int i=0;i<nEntradas;i++){
		printf("Pagina CLOCK: %ld\n",tlbCLOCK->nPagina[i]);
	}*/
	
	fprintf(salida2,"FIFO\n");
	fprintf(salida2,"HIT: %d Miss: %d\n",Hfifo,Mfifo);
	fprintf(salida2,"%s","LRU\n");
	fprintf(salida2,"HIT: %d M: %d\n",Hlru,Mlru);
	fprintf(salida2,"%s","CLOCK\n");
	fprintf(salida2,"HIT: %d M: %d\n",Hclock,Mclock);
	fclose(salida);
	fclose(salida2);
}

