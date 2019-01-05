#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#define ORDENmay "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ"
#define ORDENmin "abcdefghijklmnñopqrstuvwxyz"
#define MINmin 500
#define MINmay 500


typedef struct nodoLista{
	char valor;
	struct nodoLista *siguiente;
} nodo;

typedef struct datosLista{
	int tamanio;
	nodo *cabeza;
	nodo *fin;
} lista;


lista crearLista();
nodo *crearNodo(char elemento);
char obtener(lista actual, int posicion);
lista borrar(lista actual, int posicion);
nodo *siguiente(lista actual, int avanzar);
nodo *anterior(lista actual, int retroceder);
lista anular(lista actual);
nodo *primero(lista actual);
void mostrar(lista actual);

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
lista codificar(lista ordenada, lista original, lista final, int *des){
	lista cod;
	int i=0,z=0,contador=0,posicion2;
	int desfase=0;
	char letraOrig, letraOrd,aux,letraCod,letraIn;
	cod=crearLista();
	for(z=0;z<ordenada.tamanio;z++){
		aux=obtener(ordenada,z);
		cod=insertar(cod, aux,z);
		printf("MOSTRAR LISTA COD: \n");
		mostrar(cod);
		}
	for(i=0;i<original.tamanio;i++){
		printf("iteraciones: %d\n",i);
		letraOrig=obtener(original,i);
		posicion2=buscar(ordenada,letraOrig);
		printf("posicion %d en lista ordenada de letra original %c\n",posicion2,letraOrig);
		printf("POSICION2 %d mas contador corrimiento\n",posicion2);
		letraOrd=obtener(ordenada,posicion2);
		printf("letra obtenida en lista ordenada %c\n", letraOrd);
		letraCod=obtener(cod,posicion2);
		if(letraCod=='a'||letraCod=='e'||letraCod=='i'||letraCod=='o'||letraCod=='u'||letraCod==' '){
			letraIn=obtener(cod,posicion2);
			printf("wapupu %c\n",letraIn);
			final=insertar(final,letraIn,i);
			for(z=0;z<3;z++){
				cod=moverAtras(cod);
				}
			}
		else{
			letraIn=obtener(cod,posicion2);
			printf("wapupu %c\n",letraIn);
			final=insertar(final,letraIn,i);
			cod=mover(cod);
			contador++;
			}
		}
	printf("mostrar ordenada: ");
	mostrar(ordenada);
	printf("mostrar cod: ");
	mostrar(cod);
	letraCod=obtener(ordenada,0);
	for(z=0;z<cod.tamanio;z++){
		letraOrd=obtener(cod,z);
		if(letraCod==letraOrd){
			break;
			}
		}
	*des=z;
	return final;
	}
lista decodificar(lista letrasOrdenada, lista palabra, lista final, int desfase, int *des2){
	
	lista dec,listaAux;
	nodo *nodoPos;
	int i=palabra.tamanio, contador=0,z=0,posicion,desfase2=0;
	char aux, letraListaOrd,letraPalabra,letraListaFinal,letraDec=0;
	listaAux=crearLista();
	dec=crearLista();
	printf("tamanio palabra a descifrar: %d\n",i);
	mostrar(letrasOrdenada);
	mostrar(palabra);
	for(z=0;z<letrasOrdenada.tamanio;z++){
		aux=obtener(letrasOrdenada,z);
		dec=insertar(dec, aux,z);
		printf("MOSTRAR LISTA DEC: \n");
		mostrar(dec);
		}
	if(desfase>0){
		for(i=0;i<desfase;i++){
			printf("UGUU\n");
			dec=mover(dec);
			}
		}
	else if(desfase < 0){
		desfase =desfase*(-1);
		for(i=0;i<desfase;i++){
			dec=mover(dec);
			}
		}
	mostrar(dec);
	for(i=palabra.tamanio-1;i>=0;i--){
		letraPalabra=obtener(palabra,i);
		printf("LETRA A DECODIFICAR: %c\n",letraPalabra);
		posicion=buscar(dec,letraPalabra);
		letraDec=obtener(dec,posicion);
		letraListaOrd=obtener(letrasOrdenada,posicion);
		printf("letra obtenida en lista ordenada %c, letra palabra original %c y letra lista decodificar %c\n", letraListaOrd,letraPalabra,letraDec);
		if(letraPalabra=='a'||letraPalabra=='e'||letraPalabra=='i'||letraPalabra=='o'||letraPalabra=='u'||letraPalabra==' '){
			for(z=0;z<3;z++){
				dec=mover(dec);
				}
			posicion=buscar(dec,letraDec),
			letraListaOrd=obtener(letrasOrdenada,posicion);
			printf("NUEVA LETRA EN LISTA ORDENADA %c, NUEVA LETRA LISTA DEC %c\n",letraListaOrd,letraDec);
			letraListaFinal=obtener(letrasOrdenada,posicion);
			final=insertar(final,letraListaFinal,contador);
			desfase2 = desfase2+3;
		}
		else{
			dec=moverAtras(dec);
			posicion=buscar(dec,letraDec),
			letraListaOrd=obtener(letrasOrdenada,posicion);
			printf("NUEVA LETRA EN LISTA ORDENADA %c, NUEVA LETRA LISTA DEC %c\n",letraListaOrd,letraDec);
			letraListaFinal=obtener(letrasOrdenada,posicion);
			final=insertar(final,letraListaFinal,contador);
			desfase2=desfase2-1;
			}
			contador++;
		}
	*des2=desfase2;
	nodoPos=final.fin;
	for(i=0;i<final.tamanio;i++){
		listaAux=insertar(listaAux,nodoPos->valor,i);
		nodoPos=anterior(final,final.tamanio-i-1);
		}
	printf("contador: %d\n",contador);
	mostrar(listaAux);
	return listaAux;
	}
		 
int main(){
	FILE *archivo_EntradaC;
	FILE *archivo_EntradaD;
	FILE *archivo_Salida;
	int estado, desfase;
	int d,i,d2;
	int contador=0;
	char tipoArchivo, letra, aux;
	archivo_Salida = fopen("Salida.txt","w");
	lista listaPalabra;
	lista listaOrdenada;
	lista listaAuxiliar;
	lista listaCodificada;
	lista listaLetras;
	lista listaCifrada;
	lista listaDecodificada;
	listaCifrada=crearLista();
	listaLetras=crearLista();
	listaOrdenada = crearLista();
	listaPalabra = crearLista();
	listaAuxiliar = crearLista();
	listaCodificada=crearLista();
	listaDecodificada=crearLista();
	printf("nihaha\n");
	do{ 
		printf("ingrese accion que desea realizar (cifrado = c, C descifrado = d, D)\n");
		scanf("%c",&tipoArchivo);
		if(tipoArchivo=='c'||tipoArchivo=='C'){
			estado=1;
			printf("cifrado\n");
			archivo_EntradaC = fopen("Entrada.txt","r");
			fscanf(archivo_EntradaC, "Cifrado\n");
			while(feof(archivo_EntradaC)==0){
				letra = fgetc(archivo_EntradaC);
				letra=tolower(letra);
				printf("%c\n", letra);
				if(letra==EOF){
					break;
				}
				else{
					listaPalabra = insertar(listaPalabra, letra, contador);
					listaAuxiliar = insertar(listaAuxiliar, letra, contador);
				}
				contador++;
			}
			fclose(archivo_EntradaC);
			mostrar(listaAuxiliar);
			listaOrdenada=ordenar(listaAuxiliar);
			printf("lista ordenada: ");
			mostrar(listaOrdenada);
			listaCodificada=codificar(listaOrdenada,listaPalabra,listaCodificada,&d);
			printf("LIStA CODIFICADA: ");
			mostrar(listaCodificada);
			printf("desfase: %d\n",d);
			for(i=0;i<listaCodificada.tamanio;i++){
				aux=obtener(listaCodificada,i);
				fprintf(archivo_Salida,"%c",aux);
				}
			fprintf(archivo_Salida,"\n");
			fprintf(archivo_Salida,"%d",d);
		}
		else if(tipoArchivo=='d'||tipoArchivo=='D'){
			estado=1;
			contador=0;
			printf("descifrado\n");
			archivo_EntradaD = fopen("Entrada2.txt","r");
			fscanf(archivo_EntradaD,"Descifrado\n");
			fscanf(archivo_EntradaD, "%d\n",&desfase);
			printf("ESTA WEA ES EL DESFASE: %d\n", desfase);
			while(feof(archivo_EntradaD)==0){
				letra = fgetc(archivo_EntradaD);
				letra=tolower(letra);
				printf("%c\n", letra);
				if(letra=='\n'){
					printf("ASDFASDFASDF\n");
					break;
				}
				else{
					listaCifrada = insertar(listaCifrada, letra, contador);
				}
				contador++;
			}
			contador=0;
			while(feof(archivo_EntradaD)==0){
				printf("SEGUNDA LECTURA\n");
				letra = fgetc(archivo_EntradaD);
				letra=tolower(letra);
				printf("%c\n", letra);
				if(letra==EOF){
					break;
				}
				else{
					listaLetras = insertar(listaLetras, letra, contador);
					listaAuxiliar = insertar(listaAuxiliar, letra, contador);
				}
				contador++;
			}
			fclose(archivo_EntradaD);
			printf("LISTA PALABRA CIFRADA: ");
			mostrar(listaCifrada);
			printf("LISTA LETRAS: ");
			mostrar(listaLetras);
			listaLetras=ordenar(listaLetras);
			printf("LISTA LETRAS ORDENADA: ");
			mostrar(listaLetras);
			listaDecodificada=decodificar(listaLetras,listaCifrada,listaDecodificada,desfase,&d2);
			printf("PALABRA DECODIFICADA: ");
			mostrar(listaDecodificada);
			for(i=0;i<listaDecodificada.tamanio;i++){
				aux=obtener(listaDecodificada,i);
				fprintf(archivo_Salida,"%c",aux);
				}
			fprintf(archivo_Salida,"\n");
			fprintf(archivo_Salida,"%d",d2);
		}
		else{
			printf("ingrese una letra correcta\n");
			estado=0;
		}
		}while(estado==0);
	
	printf("FIN");
	fclose(archivo_Salida);
	listaPalabra=anular(listaPalabra);
	listaOrdenada=anular(listaOrdenada);
	listaCifrada=anular(listaCifrada);
	listaLetras=anular(listaLetras);
	listaCodificada=anular(listaCodificada);
	listaDecodificada=anular(listaDecodificada);
	return 0;
}
