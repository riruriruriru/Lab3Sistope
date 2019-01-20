
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

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
	long int *entradas;
	long int *nPagina;
	
	}TLB;
//Tabla de pagina raiz de 2^bitRaiz entradas, contiene las tablas de paginas secundarias
typedef struct TablaPaginaRaiz{
	int numEntradas;
	int tamEntradas;//no es necesario
	TP **entradas;
	int elementosUsados;//no es necesario
	//lista **entradas;
	
	}TPR;

#endif
