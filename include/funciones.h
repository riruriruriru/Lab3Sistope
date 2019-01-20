#include "estructuras.h"

#ifndef FUNCIONES_H
#define FUNCIONES_H


int convertBinaryToDecimal(long long n);
int compareList(lista actual1, lista actual2, int initOffset, int finOffset);
long int listaToInt(lista actual, int initOffset, int finOffset);
void inicializarTPR(TPR *tpr, int bitRaiz, int bitSecundaria);
void mostrarTPR(TPR *tpr);
void inicializarTLB(TLB *tlb, int entradasTLB);
void llenarTR(TPR *tpr, lista *listaDireccionesBin, int bitRaiz, int bitSecundaria, int bitMarcos, int bitOffset);
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria);
lista crearLista();
nodo *crearNodo(char elemento);
lista modificar(lista actual, char elemento, int posicion);
int buscar(lista actual, char elemento);
lista mover(lista actual);
lista moverAtras(lista actual);
char obtener(lista actual, int posicion);
lista borrar(lista actual, int posicion);
nodo *siguiente(lista actual, int avanzar);
nodo *anterior(lista actual, int retroceder);
lista anular(lista actual);
nodo *primero(lista actual);
void mostrar(lista actual);
void mostrar_indefinidamente(lista actual);
void mostrar_indefinidamenteAlReves(lista actual);
lista insertar(lista actual, char elemento, int posicion);
void inicializarTP(TP *tabla, int bitRaiz, int bitSecundaria);

void getArguments(int argc, char *argv[], int *bitRaiz, int *bitSecundaria, int *entradasTLB, int *flag);
void intToBin(int dec, int bin[], int numBits);
lista reverseLista(lista actual);
lista traducirHexToBin(lista dirHex);
lista* leerArchivoEntrada(lista *l);
lista* leerArchivoMarcos(int bitsRaiz, int bitsSecundarias, lista *l);
int lineasArchivo();
int BintoInt(lista bin, int nBits);
char* BinToHex(lista bin);
int largoPalabra(char *palabra);
lista memoriaFisica(lista offset, long int marco, int nBits);
int obtenerIndiceTPR(lista dirLogicas, int bitRaiz);
int obtenerIndiceTP(lista dirLogicas, int bitRaiz, int bitSecundaria);
lista obtenerOffset(lista dirLogicas, int bitRaiz, int bitSecundaria);
int posMax(int *posRem, int nEntradas);
int buscarFIFOPos(int *posRem, int nEntradas);
void direccionFisica(lista *dirLog, int nLineas, TPR *tpr, int bitRaiz, int bitSecundaria, int nEntradas, int flag);


#endif
