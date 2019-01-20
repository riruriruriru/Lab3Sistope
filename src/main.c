#include "funciones.c"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "estructuras.h"

int main(int argc, char *argv[]){
	char caracteres[4] = {'F', '1', '0', '0'};
	//printf("UWU\n");
	lista l = crearLista();
	lista b = crearLista();
	for(int i = 0; i < 4; i++){
		b = insertar(b, caracteres[i], i);
		}
	printf("PROBANDO TRANSFORMAR HEX A BIN: \n");
	mostrar(b);
	l = traducirHexToBin(b);
	long int prueba = listaToInt(l, 0, 15);
	mostrar(l);
	printf("LONG INT: %li \n", prueba);
	printf("FIN PRUEBA\n");
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
	tpr = (TPR*)malloc(sizeof(TPR*));
	inicializarTPR(tpr, bitRaiz, bitSecundaria); //se inicializa una TPR
	tlb = (TLB*)malloc(sizeof(TLB*));
	inicializarTLB(tlb, entradasTLB);
	for(int i = 0;i<numeroMarcos;i++){ //se inicializan tantas listas como n° de marcos se deba leer
		arrayLista[i] = crearLista();
		}
	leerArchivoMarcos(bitRaiz, bitSecundaria, arrayLista); //se lee el archivo de marcos y se llena la lista "arrayLista"
	for(int i = 0;i<numeroMarcos;i++){
		arrayListaBin[i] = crearLista(); //se inicializa cada elemento de la lista de direcciones en binario
		arrayListaBin[i] =traducirHexToBin(arrayLista[i]);
		
		}
	
	llenarTR(tpr, arrayListaBin, bitRaiz, bitSecundaria, bitMarcos, bitOffset);
	for(int i=0;i<4;i++){
		l = insertar(l, caracteres[i], i);
		}
	
	direccionFisica(arrayListaDireccionesLogicasBin, numeroDireccionesLogicas, tpr, bitRaiz, bitSecundaria,entradasTLB,flag);
	return 0;
	}

