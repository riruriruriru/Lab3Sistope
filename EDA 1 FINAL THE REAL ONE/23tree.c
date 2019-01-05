#include <stdio.h>
#include <stdlib.h>

struct nodo{
	int valor;
	int minC;
	int minD;
	struct nodo* izq;
	struct nodo* der;
	struct nodo* centro;
}; 

struct nodo* crear_hoja(int dato);
struct nodo* crear_i();
struct nodo* buscar(struct nodo* raiz, int valor);
int es_hoja(struct nodo* raiz);
void ancestros(struct nodo* node, struct nodo* actual);
struct nodo* buscarPos(struct nodo* root, int dato);
struct nodo* insertGeneral(struct nodo* root, struct nodo* pos, struct nodo* insertado, int minInsertado);
struct nodo* insertGeneral2(struct nodo* root, struct nodo* pos, struct nodo* insertado, int minInsertado);
struct nodo* insertar(struct nodo* root, int valor);
void printHojas(struct nodo* root);
int maximo(struct nodo* root);
int minimo(struct nodo* root);
struct nodo* Padre(struct nodo* root, struct nodo* actual);
struct nodo* padre_subarbol(struct nodo* indice, struct nodo* padreIndice, struct nodo* actual);
struct nodo* buscarPos(struct nodo* root,int valor);

void printHojas(struct nodo* root){
	if(root==NULL){
		return;
	}
	if(es_hoja(root)==1){
		printf("Valor hoja: %d\n",root->valor);
		}
	
	printHojas(root->izq);
	printHojas(root->centro);
	printHojas(root->der);
	
	}

int minimo(struct nodo* root){
	printf("FUNCION MINIMO \n");
	struct nodo* actual=root;
	printf("FUNCION MINIMO 2\n");
	if(root==NULL){
		printf("FUNCION MINIMO IF NULL\n");
		return -9000;
	}
	while(actual->izq!=NULL){
		printf("FUNCION MINIMO WHILE\n");
		if(actual->izq->valor==-9000){
			return actual->valor;
		}
		else{
			actual=actual->izq;}
	}
	return actual->valor;
}

int maximo(struct nodo* root){
	struct nodo* actual=root;
	if(root==NULL){
		return root->valor;
	}
	while(actual->der!=NULL||actual->centro!=NULL){
		if(actual->der==NULL){
			actual=actual->centro;
		}
		else{
			actual=actual->der;
		}
	}
	return actual->valor;
}

struct nodo* padre_subarbol(struct nodo* indice, struct nodo* padreIndice, struct nodo* actual){
	if(indice==NULL){
		return NULL;
	}
	if(actual==indice->izq){
		return indice;
	}
	if(actual==indice->der){
		return padreIndice;
	}
	struct nodo* padreNodo=padre_subarbol(indice->izq,indice,actual);
	if(padreNodo==NULL){
		padreNodo=padre_subarbol(indice->der,padreIndice,actual);
	}
	return padreNodo;
}

struct nodo* Padre(struct nodo* root, struct nodo* actual){
	printf("FUNCION PADRE 1\n");
	struct nodo* pos=root;
	if(actual==root){
		printf("FUNCION PADRE PRIMER IF\n");
		return NULL;
	}
	if(pos->izq==actual||pos->centro==actual||pos->der==actual){
		printf("FUNCION PADRE SEGUNDO IF\n");
		return pos;
	}
	printf("FUNCION PADRE RECURSIVIDAD\n");
	if(pos->izq!=NULL){
		Padre(pos->izq,actual);
	}
	if(pos->centro!=NULL){
		Padre(pos->centro,actual);
	}
	if(pos->der!=NULL){
		Padre(pos->der,actual);
	}
	printf("FUNCION PADRE POST RECURSIVIDAD\n");
}

struct nodo* crear_hoja(int dato){
	struct nodo* hoja = (struct nodo*)malloc(sizeof(struct nodo));
	if(hoja!=NULL){
		hoja->valor=dato;
		hoja->minC=-1000;
		hoja->minD=-1000;
		hoja->centro=NULL;
		hoja->der=NULL;
		hoja->izq=NULL;
		
	}
	return hoja;
	
}
struct nodo* crear_i(){
	struct nodo* nuevo = (struct nodo*)malloc(sizeof(struct nodo));
	if(nuevo!=NULL){
		nuevo->valor=-9000;
		nuevo->minC=-1000;
		nuevo->minD=-1000;
		nuevo->izq=NULL;
		nuevo->der=NULL;
		nuevo->centro=NULL;
		
	}
	return nuevo;
}
int es_hoja(struct nodo* raiz){
	if(raiz->izq==NULL){
		return 1;
	}
	else{
		return 0;
	}
}
struct nodo* buscar(struct nodo* raiz, int valor){
	struct nodo* pos=raiz;
	if(raiz==NULL){
		return NULL;
	}
	if(valor>maximo(raiz)||valor<minimo(raiz)){
		return NULL;
	}
	while(es_hoja(pos)==0){
		if(valor<pos->minC){
			pos=pos->izq;
		}
		else if(valor < pos->minD||pos->der==NULL){
			pos=pos->centro;
		}
		else{
			pos=pos->der;
		}
	}
	if(pos->valor==valor){
		return pos;
	}
	else{
		return NULL;
	}
}
void ancestros(struct nodo* node, struct nodo* actual){
	printf("ANCESTROS FUNCION\n");
	struct nodo* padreActual=NULL;
	printf("ANCESTROS FUNCION 2\n");
	while(actual!=NULL){
		printf("ANCESTROS FUNCION WHILE\n");
		printf("DATOS ACTUAL DENTROD E WHILE: valor %d minc %d mind %d\n",actual->valor,actual->minC,actual->minD);
		actual->minC=minimo(actual->centro);
		printf("ANCESTROS FUNCION POST MINIMO\n");
		if(actual->der!=NULL){
			printf("ANCESTROS FUNCION IF 1\n");
			actual->minD=minimo(actual->der);
		}
		else{
			printf("ANCESTROS FUNCION ELSE 1\n");
			actual->minD=-1000;
			printf("ANCESTROS FUNCION ELSE 1-2\n");
		}
		printf("PRE PADRE ACTUAL\n");
		padreActual=Padre(node,actual);
		printf("POST PADRE ACTUAL\n");
		if(padreActual!=NULL&&actual==padreActual->izq){
			printf("ANCESTROS FUNCION IF 2\n");
			return;
		}
		printf("ANCESTROS FUNCION FINAL\n");
		actual=padreActual;
	}
	printf("ANCESTROS TERMINO WHILE \n");
}
struct nodo* buscarPos(struct nodo* root,int valor){
	struct nodo* posicion=root;
	while(posicion!=NULL&&es_hoja(posicion)==0){
		if(valor<posicion->minC){
			posicion=posicion->izq;
		}
		else if(posicion->der==NULL||valor<posicion->minD){
			posicion=posicion->centro;
		}
		else{
			posicion=posicion->der;
		}
	}
	return posicion;
}
struct nodo* insertGeneral(struct nodo* root, struct nodo* pos, struct nodo* insertado, int minInsertado){
	printf("FUNCION INSERTAR GENERAL \n");
	struct nodo* anterior=Padre(root,pos);
	printf("INSERTAR GENERAL POST PADRE\n");
	struct nodo* newRoot=crear_i();
	if(anterior==NULL){
		printf("NIHAHA\n");
	}
	else{
		printf("VALORES DEL PADRE DE POS: valor %d minc %d mind %d\n",anterior->valor,anterior->minC,anterior->minD);
	}
	if(anterior==root&&anterior->der==NULL||pos==root){
		printf("FUNCION INSERTAR GENERAL PRIMER IF\n");
		printf("VALORES ACTUALES POS: valor %d\n",pos->valor);
		struct nodo* nuevo=crear_i();
	
		if(pos->valor>minInsertado){
			printf("IF 1-1\n");
			nuevo->centro=anterior->der;
			nuevo->izq=anterior->centro;
			anterior->centro=anterior->izq;
			anterior->izq=insertado;
			anterior->minC=minimo(anterior->centro);
			anterior->der=NULL;
			anterior->minD=-1000;
			struct nodo* newRoot=crear_i();
			newRoot->izq=anterior;
			newRoot->centro=nuevo;
		}
		else if(pos==anterior->izq){
			printf("IF 1-2\n");
			nuevo->centro=anterior->der;
			nuevo->izq=anterior->centro;
			anterior->centro=insertado;
			anterior->minC=minInsertado;
			anterior->der=NULL;
			anterior->minD=-1000;
			struct nodo* newRoot=crear_i();
			newRoot->izq=anterior;
			newRoot->centro=nuevo;
		
		}
		else if(pos==anterior->centro){
			printf("IF 1-3\n");
			nuevo->centro=anterior->der;
			printf("UGUU 1\n");
			nuevo->izq=insertado;
			printf("UGUU 2\n");
			anterior->der=NULL;
			printf("UGUU 3\n");
			anterior->minD=-1000;
			printf("UGUU 4\n");
			struct nodo* newRoot=crear_i();
			printf("UGUU 5\n");
			newRoot->izq=anterior;
			printf("UGUU 6\n");
			newRoot->centro=nuevo;
			printf("UGUU 7\n");
		
		}
		else{
			printf("IF 1-4\n");
			nuevo->centro=insertado;
			nuevo->izq=anterior->der;
			anterior->der=NULL;
			anterior->minD=-1000;
			struct nodo* newRoot=crear_i();
			newRoot->izq=anterior;
			newRoot->centro=nuevo;
		}
		printf("DATOS NODO NUEVO: valor %d minc %d mind %d\n",nuevo->valor,nuevo->minC,nuevo->minD);
		printf("UGUU 8\n");
		root=newRoot;
		printf("DATOS NUEVA RAIZ: valor %d minc %d mind %d\n",root->valor,root->minC,root->minD);
		printf("UGUU 9\n");
		ancestros(root,nuevo);
		printf("UGUU 10\n");
		return root;
		}
	if(anterior->der==NULL){
		printf("FUNCION INSERTAR GENERAL SEGUNDO IF\n");
		if(pos->valor>minInsertado){
			anterior->der=anterior->centro;
			anterior->centro=anterior->izq;
			anterior->izq=insertado;
		}
		else if(pos==anterior->izq){
			anterior->der=anterior->centro;
			anterior->centro=insertado;
		}
		else{
			anterior->der=insertado;
		}
		ancestros(root,anterior);
		return root;
	}
	struct nodo* nuevo=crear_i();
	if(pos->valor>minInsertado){
		printf("FUNCION INSERTAR GENERAL TERCER IF\n");
		nuevo->centro=anterior->der;
		nuevo->izq=anterior->centro;
		anterior->centro=anterior->izq;
		anterior->izq=insertado;
		anterior->der=NULL;
		minInsertado=anterior->minC;
		
	}
	else if(pos==anterior->izq){
		printf("FUNCION INSERTAR GENERAL CUARTO IF\n");
		nuevo->centro=anterior->der;
		nuevo->izq=anterior->centro;
		anterior->centro=insertado;
		anterior->der=NULL;
		minInsertado=anterior->minC;
	}
	else if(pos==anterior->centro){
		printf("FUNCION INSERTAR GENERAL QUINTO IF\n");
		nuevo->centro=anterior->der;
		nuevo->izq=insertado;
		anterior->der=NULL;
	}
	else{
		printf("FUNCION INSERTAR GENERAL SEXTO IF\n");
		nuevo->centro=insertado;
		nuevo->minC=minInsertado;
		nuevo->izq=anterior->der;
		anterior->der=NULL;
		minInsertado=anterior->minD;
		
	}
	printf("ultimo before ancestros\n");
	printf("minInsertado %d\n",minInsertado);
	printf("NODO INSERTADO: %d\n",insertado->valor);
	ancestros(root,anterior);
	printf("post ancestros\n");
	printf("VALORES ANTERIOR POST ANCESTROS: %d\n",anterior->minC);
	printf("%d\n",anterior->centro->valor);
	return insertGeneral(root,anterior,nuevo,minInsertado);
	
}
struct nodo* insertar(struct nodo* root, int valor){
	printf("VALOR A INSERTAR: %d\n",valor);
	struct nodo* nuevo= crear_hoja(valor);
	if(root==NULL){
		return nuevo;
	}
	if(es_hoja(root)==1){
		struct nodo* intermedio=crear_i();
		if(valor<root->valor){
			intermedio->izq=nuevo;
			intermedio->centro=root;
			intermedio->minC=root->valor;
		}
		else{
			intermedio->izq=root;
			intermedio->centro=nuevo;
			intermedio->minC=valor;
		}
		root=intermedio;
		return root;
	}
	else if(es_hoja(root)==0&&root->der==NULL){
		struct nodo* hoja=crear_hoja(valor);
		root->der=hoja;
		root->minD=valor;
		return root;
	}
	struct nodo* pos=buscarPos(root,valor);
	printf("VALORES POS: valor %d minc %d mind %d\n",pos->valor,pos->minC,pos->minD);
	//root=insertGeneral(root,pos,nuevo,valor);
	root=insertGeneral2(root,pos,nuevo,valor);
	return root;
}

struct nodo* insertGeneral2(struct nodo* root, struct nodo* pos, struct nodo* insertado, int minInsertado){
	int minC, minC2, nuevo,cont;
	printf("FUNCION INSERTAR GENERAL \n");
	struct nodo* anterior2=pos;
	struct nodo* anterior=Padre(root,pos);
	printf("INSERTAR GENERAL POST PADRE\n");
	struct nodo* newRoot=crear_i();
	if(anterior->izq!=NULL&&anterior->centro!=NULL&&anterior->der!=NULL&&anterior==root){
		struct nodo* newNodo1=crear_i();
		struct nodo* newNodo2=crear_i();
		if(anterior->minD>minInsertado&&anterior->minC<minInsertado){
			minC = anterior->minC;
			minC2=anterior->minD;
			nuevo=minInsertado;
			newNodo1->minC=minC;
			newNodo2->minC=minC2;
			newNodo1->centro=crear_hoja(anterior->centro->valor);
			newNodo1->izq=crear_hoja(anterior->izq->valor);
			newNodo2->centro=crear_hoja(anterior->der->valor);
			newNodo2->izq=crear_hoja(minInsertado);
			root->minD=-1000;
			root->izq=newNodo1;
			root->centro=newNodo2;
			root->minC=nuevo;
			root->der=NULL;
			
			
		}
		else if(anterior->minD<minInsertado){
			minC2=minInsertado;
			minC=anterior->minC;
			nuevo=anterior->minD;
			newNodo1->minC=minC;
			newNodo2->minC=minC2;
			newNodo1->centro=crear_hoja(anterior->centro->valor);
			newNodo1->izq=crear_hoja(anterior->izq->valor);
			newNodo2->centro=crear_hoja(minInsertado);
			newNodo2->izq=crear_hoja(anterior->der->valor);
			root->minD=-1000;
			root->izq=newNodo1;
			root->centro=newNodo2;
			root->minC=nuevo;
			root->der=NULL;
		}
		else if(anterior->minC>minInsertado){
			nuevo=anterior->minC;
			minC=minInsertado;
			minC2=anterior->minD;
			newNodo1->minC=minC;
			newNodo2->minC=minC2;
			newNodo1->centro=crear_hoja(minInsertado);
			newNodo1->izq=crear_hoja(anterior->izq->valor);
			newNodo2->centro=crear_hoja(anterior->der->valor);
			newNodo2->izq=crear_hoja(anterior->centro->valor);
			root->minD=-1000;
			root->izq=newNodo1;
			root->centro=newNodo2;
			root->minC=nuevo;
			root->der=NULL;
		}
		return root;
		
	}
	if(anterior->der==NULL&&anterior!=root){
		printf("MISUZU\n");
		if(anterior==root->izq){
			root->izq=anterior;
		}
		else if(anterior==root->centro){
			root->centro=anterior;
		}
		else if(anterior == root->der){
			root->der=anterior;
		}
		if(minInsertado>anterior->minC){
			anterior->minD=minInsertado;
			struct nodo* hoja = crear_hoja(minInsertado);
			anterior->der=hoja;	
		}
		else if(minInsertado<anterior->minC&&minInsertado>anterior->izq->valor){
			struct nodo* hoja=crear_hoja(minInsertado);
			anterior->minD=anterior->minC;
			anterior->minC=minInsertado;
			anterior->der=anterior->centro;
			anterior->centro=hoja;
		}
		else if(minInsertado<anterior->minC&&minInsertado<anterior->izq->valor){
			struct nodo* hoja=crear_hoja(minInsertado);
			anterior->der=anterior->centro;
			anterior->centro=anterior->izq;
			anterior->izq=hoja;
			anterior->minC=anterior->centro->valor;
		}
		return root;
		
	}
	if(root!=anterior){
		printf("GG\n");
		while(Padre(root,anterior2)!=root){
			cont++;
		}
		
	}

}

int main(){
	struct nodo* root=NULL;
	int a,b,c;
	root=insertar(root,9);
	root=insertar(root,7);
	root=insertar(root,10);
	root=insertar(root,11);
	root=insertar(root,12);
	root=insertar(root,8);
	//root=insertar(root,13);
	/*root=insertar(root,14);
	root=insertar(root,15);
	a=root->valor;
	b=root->minC;
	c=root->minD;*/
	printf("uguu\n");
	//printf("valor root %d,minc root %d, mind root %d\n",a,b,c);
	//printf("valor root izq %d,minc root %d, mind root %d\n",root->izq->valor,root->izq->minC,root->izq->minD);
	//printf("valor root centro %d,minc root %d, mind root %d\n",root->centro->valor,root->centro->minC,root->centro->minD);
	//printf("valor root der %d,minc root %d, mind root %d\n",root->der->valor,root->der->minC,root->der->minD);
	printHojas(root);
	
	return 0;
}
