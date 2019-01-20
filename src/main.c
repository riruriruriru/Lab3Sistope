#include "funciones.c"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "estructuras.h"

int main(int argc, char *argv[]){
	char caracteres[4] = {'2', '3', '0', '0'};
	//printf("UWU\n");
	lista l = crearLista();
	lista b = crearLista();
	TPR *tpr;
	int bitRaiz, bitSecundaria, entradasTLB, flag=0;
	TLB *tlb;
	getArguments(argc, argv, &bitRaiz, &bitSecundaria, &entradasTLB, &flag); //se reciben los argumentos ingresados por consola
	int numeroMarcos = pow(2,bitRaiz)*pow(2,bitSecundaria); //se calcula el numero de marcos que hay que leer
	int bitOffset = 16-bitRaiz - bitSecundaria; //se calcula el numero de bits en direcciones de 16bits que corresponden al offset
	int bitMarcos = 16-bitOffset; //se calcula el numero de bits en direcciones de 16 bits que corresponden al marco
	//printf("BITS PARA OFFSET: %d - BITS PARA MARCOS: %d - NUMERO MARCOS: %d\n", bitOffset, bitMarcos, numeroMarcos);
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
	//printf("NUMERO DE MARCOS: %d\n", numeroMarcos);
	//printf("mostrando TPR y TP\n");
	tpr = (TPR*)malloc(sizeof(TPR*));
	inicializarTPR(tpr, bitRaiz, bitSecundaria); //se inicializa una TPR
	//mostrarTPR(tpr);
	//printf("finalizando mostrar TPR y TP\n");
	tlb = (TLB*)malloc(sizeof(TLB*));
	//printf("antes TLB\n");
	inicializarTLB(tlb, entradasTLB);
	//mostrarTLB(tlb);
	//printf("DESPUES TLB\n");
	//printf("MOSTRANDO ARREGLO LISTAS: \n");
	for(int i = 0;i<numeroMarcos;i++){ //se inicializan tantas listas como n° de marcos se deba leer
		arrayLista[i] = crearLista();
		//printf("owo\n");
		}
	//printf("iwi\n");
	leerArchivoMarcos(bitRaiz, bitSecundaria, arrayLista); //se lee el archivo de marcos y se llena la lista "arrayLista"
	/*for(int i =0;i<numeroMarcos;i++){
		mostrar(arrayLista[i]);
		}*/
	//printf("TRADUCCIONDE HEX A BIN: \n");
	for(int i = 0;i<numeroMarcos;i++){
		arrayListaBin[i] = crearLista(); //se inicializa cada elemento de la lista de direcciones en binario
		arrayListaBin[i] =traducirHexToBin(arrayLista[i]);
		//mostrar(arrayListaBin[i]);
		
		}
	
	//printf("$$$$$$$$$$$$$$$$$$$$$$$$\n");
	//TP *tabla;
	//tabla = (TP *)malloc(sizeof(TP*));
	//inicializarTP(tabla, 5, 6);
	//printf("%d\n", tabla->numEntradas);
	//printf("%d\n", tabla->tamEntradas);
	llenarTR(tpr, arrayListaBin, bitRaiz, bitSecundaria, bitMarcos, bitOffset);
	//mostrarTPR(tpr);
	for(int i=0;i<4;i++){
		l = insertar(l, caracteres[i], i);
		}
	/*lista off = crearLista();
	lista bin = crearLista();
	printf("bits de raiz\n");
	int i = obtenerIndiceTPR(arrayListaDireccionesLogicasBin[1], bitRaiz);
	printf("Indice raiz: %d\n",i);
	int j = obtenerIndiceTP(arrayListaDireccionesLogicasBin[1],bitRaiz, bitSecundaria);
	printf("Indice secundaria: %d\n",j);
	off = obtenerOffset(arrayListaDireccionesLogicasBin[1],bitRaiz, bitSecundaria);
	long int mr = tpr->entradas[101]->entradas[0];
	bin  = memoriaFisica(off,mr,bitRaiz+bitSecundaria);
	printf("hex: %s\n",BinToHex(bin));*/
	
	direccionFisica(arrayListaDireccionesLogicasBin, numeroDireccionesLogicas, tpr, bitRaiz, bitSecundaria,entradasTLB,flag);
	
	
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

