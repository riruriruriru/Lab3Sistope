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
	int reloj;
	nodo *cabeza;
	nodo *fin;
} lista;
//Una tabla de pagina representa una tabla de pagina secundaria, por lo tanto contiene 2^bitSecundaria entradas
typedef struct TablaPagina{
	int numEntradas;//se guarda el numero de entradas
	int tamEntradas; //esto creo que se puede borrar uwu
	long int *entradas;//esta es la entrada en si, es long int debido a que puede ser de hasta 15 digitos, lo cual no es soportado por un int normal
	int elementosUsados; //tambien puede borrarse esto, creo
	
	}TP;
//Falta mejorar la logica de la TLB, por ahora es solo una struct con una matriz y una lista de listas pero no hace mucho mas que eso
//por ahora la logica es que la TLB contiene n listas, segun n sea la cantidad de elementos que pueda tener
//esas listas guardaran entradas de tablas de pagina, osea valores de marcos
//la matriz seria lo mismo, hay que ver si es mejor usar matriz o lista de listas uwu
typedef struct TLB{
	int numElementos;
	int elementosUsados;
	int **matrizTLB;
	lista *listaTLB;
	
	}TLB;
//Tabla de pagina raiz de 2^bitRaiz entradas, contiene las tablas de paginas secundarias
typedef struct TablaPaginaRaiz{
	int numEntradas;
	int tamEntradas;//no es necesario
	TP **entradas;
	int elementosUsados;//no es necesario
	
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
lista insertar(lista actual, char elemento, int posicion);
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria);

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
	tlb->listaTLB = (lista *)malloc(16*entradasTLB*sizeof(lista*));
	printf("antes primera memoria a matriz, num entradas: %d\n", entradasTLB);
	tlb->matrizTLB = (int **)malloc(entradasTLB*sizeof(int*));
	tlb->elementosUsados = 0;
	printf("adespues primera memoria a matriz\n");
	//*tabla = (Casilla**)malloc(row*sizeof(Casilla));
	for(int i=0;i<entradasTLB;i++){
		tlb->matrizTLB[i] = (int*)malloc(16*sizeof(int));
		tlb->listaTLB[i] = crearLista();
		}
	//printf("despues darle memoria a matriz\n");
	for(int i= 0;i<entradasTLB;i++){
		for(int  j = 0;j<16;j++){
			//printf("indices i-j; %d-%d\n",i,j);
			tlb->matrizTLB[i][j] = 0;
			tlb->listaTLB[i] = insertar(tlb->listaTLB[i], '0', j);
			}
		
		}
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
void mostrarTLB(TLB *tlb){
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
	}
//Entradas: bits de informacion y puntero a tabla de pagina
//Funcionamiento: inicializa una tabla de pagina con un arreglo de long int de tanto largo como entradas pueda tener la tabla de paginas
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria){
	tabla->tamEntradas = pow(2,16-bitRaiz-bitSecundaria);
	tabla->numEntradas = pow(2,bitSecundaria);
	tabla->entradas = (long int*)malloc(tabla->numEntradas*sizeof(long int*));
	for(int i=0;i<tabla->numEntradas;i++){
		tabla->entradas[i] = 0;
		}
	printf("TP\n");
	printf("tamanio entradas TP %d\n", tabla->tamEntradas);
	printf("numero entradas TP %d\n", tabla->numEntradas);
	printf("TP\n");
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
		   printf("BITS RAIZ: %d", bitsR);
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
		//printf("the worst\n");
		printf("%c%c%c%c%c%c%c", aux1,aux2,hex1,hex2,hex3,hex4,aux3);
		l[contador] = insertar(l[contador],hex1, 0);
		l[contador] = insertar(l[contador],hex2, 1);
		l[contador] = insertar(l[contador],hex3, 2);
		l[contador] = insertar(l[contador],hex4, 3);
		//printf("the worst2\n");
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

int main(int argc, char *argv[]){
	char caracteres[4] = {'2', '3', '0', '0'};
	printf("UWU\n");
	lista l = crearLista();
	lista b = crearLista();
	TPR *tpr;
	int bitRaiz, bitSecundaria, entradasTLB, flag=0;
	TLB *tlb;
	getArguments(argc, argv, &bitRaiz, &bitSecundaria, &entradasTLB, &flag); //se reciben los argumentos ingresados por consola
	int numeroMarcos = pow(2,bitRaiz)*pow(2,bitSecundaria); //se calcula el numero de marcos que hay que leer
	int bitOffset = 16-bitRaiz - bitSecundaria; //se calcula el numero de bits en direcciones de 16bits que corresponden al offset
	int bitMarcos = 16-bitOffset; //se calcula el numero de bits en direcciones de 16 bits que corresponden al marco
	printf("BITS PARA OFFSET: %d - BITS PARA MARCOS: %d - NUMERO MARCOS: %d\n", bitOffset, bitMarcos, numeroMarcos);
	lista *arrayLista = (lista*)malloc(numeroMarcos*16*sizeof(lista*)); //lista listas donde se guardaran las direcciones fisicas en hexadecimal
	lista *arrayListaBin = (lista*)malloc(numeroMarcos*16*sizeof(lista*)); //lista de listas donde se guardaran las direcciones fisicas en binario
	int numeroDireccionesLogicas = lineasArchivo();
	lista *arrayListaDireccionesLogicas = (lista*)malloc(numeroMarcos*16*sizeof(lista*));
	lista *arrayListaDireccionesLogicasBin = (lista*)malloc(numeroMarcos*16*sizeof(lista*));
	for(int i = 0; i<numeroDireccionesLogicas;i++){
		arrayListaDireccionesLogicas[i] = crearLista();
		arrayListaDireccionesLogicasBin[i] = crearLista(); //se lee archivo de direcciones logicas
		}
	leerArchivoEntrada(arrayListaDireccionesLogicas); //se llenan listas con direcciones logicas en HEX
	for(int i = 0; i<numeroDireccionesLogicas;i++){
		arrayListaDireccionesLogicasBin[i] =traducirHexToBin(arrayListaDireccionesLogicas[i]);//se transforman las listas a  binario
		}
	printf("NUMERO DE MARCOS: %d\n", numeroMarcos);
	printf("mostrando TPR y TP\n");
	tpr = (TPR*)malloc(sizeof(TPR*));
	inicializarTPR(tpr, bitRaiz, bitSecundaria); //se inicializa una TPR
	mostrarTPR(tpr);
	printf("finalizando mostrar TPR y TP\n");
	tlb = (TLB*)malloc(sizeof(TLB*));
	printf("antes TLB\n");
	inicializarTLB(tlb, 10);
	mostrarTLB(tlb);
	printf("DESPUES TLB\n");
	printf("MOSTRANDO ARREGLO LISTAS: \n");
	for(int i = 0;i<numeroMarcos;i++){ //se inicializan tantas listas como n° de marcos se deba leer
		arrayLista[i] = crearLista();
		printf("owo\n");
		}
	printf("iwi\n");
	leerArchivoMarcos(bitRaiz, bitSecundaria, arrayLista); //se lee el archivo de marcos y se llena la lista "arrayLista"
	for(int i =0;i<numeroMarcos;i++){
		mostrar(arrayLista[i]);
		}
	printf("TRADUCCIONDE HEX A BIN: \n");
	for(int i = 0;i<numeroMarcos;i++){
		arrayListaBin[i] = crearLista(); //se inicializa cada elemento de la lista de direcciones en binario
		arrayListaBin[i] =traducirHexToBin(arrayLista[i]);
		mostrar(arrayListaBin[i]);
		
		}
	
	printf("$$$$$$$$$$$$$$$$$$$$$$$$\n");
	//TP *tabla;
	//tabla = (TP *)malloc(sizeof(TP*));
	//inicializarTP(tabla, 5, 6);
	//printf("%d\n", tabla->numEntradas);
	//printf("%d\n", tabla->tamEntradas);
	llenarTR(tpr, arrayListaBin, bitRaiz, bitSecundaria, bitMarcos, bitOffset);
	mostrarTPR(tpr);
	for(int i=0;i<4;i++){
		l = insertar(l, caracteres[i], i);
		}
	//mostrar(l);
	//printf("LISTA B:\n");
	//b = traducirHexToBin(l);
	//mostrar(b);
	//long int entero = listaToInt(b, 0, 16);
	//long int entero2 = listaToInt(b, 0, bitMarcos);
	//printf("lista a entero: %li\n", entero);
	//printf("lista a entero cortado: %li\n", entero2);
	//int bool =compareList(b, b, 0, 0);
	//printf("comparacion: %d\n", bool);
	//b = modificar(b, '1', 1);
	//printf("B modificada: \n");
	//mostrar(b);
	//printf("TABLAS DE PAGINA: %f\n", pow(2,bitRaiz));
	return 0;
	}
