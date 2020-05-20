#include <iostream>
#include <cstdlib>

using namespace std;

/* Definición de la estructura del nodo*/
struct Nodo{
	int dato;
	Nodo *izq;
	Nodo *der;
	Nodo *padre;
	int revision; // indica el número de veces que se ha pasado por un nodo al imprimir el árbol en pantalla
	int tipo; // indica si el nodo es un hijo izquierdo (1), derecho (2) o una raíz (0) 	
};

/* Prototipos de funciones*/
void menu();
struct Nodo* insertarNodo(int info,struct Nodo *raiz);
struct Nodo* crearNodo(int info);
void preorden(struct Nodo *raiz);
void inorden(struct Nodo *raiz);

/* Función principal*/
int main(){
	int op; // opción del menú seleccionada por el usuario
	struct Nodo *raiz = NULL; // definición de la raíz del árbol
	int info; // entero que el usuario añade al árbol
	do{
		menu();
		cin>>op;
		switch(op){
			case 1:
				cout<<"\tDato a ingresar: ";
				cin>>info;
				raiz = insertarNodo(info,raiz);
			break;
			case 2:
			break;
			case 3:
				preorden(raiz);
				inorden(raiz);
			break;
			case 4:
			break;
			case 5:
				cout<<"\n\tSaliendo del programa..."<<endl;
				cout<<"\t";
				system("PAUSE");
				return 0;
			break;
			default:
				cout<<"\n\tOpcion no valida.\n\tPor favor intentalo de nuevo"<<endl;
			break;
		}
		cout<<"\n\t";
		system("pause");
		system("cls");
	}while(op!=5);
}

/* Función que muestra el recorrido en inorden del árbol*/
void inorden(struct Nodo *raiz){
	cout<<"\n\tInorden: ";
	bool terminado = false;
	struct Nodo *nodo;
	nodo = raiz;
	while(!terminado){
		switch(nodo->revision){
			case 0: // revisa si el nodo tiene hijo izquierdo
				nodo->revision = 2;
				if(nodo->izq==NULL){
					cout<<" "<<nodo->dato;
				}else{
					nodo = nodo->izq;
				}
			break;
			case 1: // la revision=1 lo tienen los nodos raíz de los que ya se revisaron ambos lados de sus nodos hijos
				if(nodo->tipo==0){
					nodo->revision = 0;
					terminado = true;
				}else if(nodo->tipo==1){
					nodo->revision = 0;
					nodo = nodo->padre;
					cout<<" "<<nodo->dato;
					nodo->revision = 2;
				}else{
					nodo->revision = 0;
					nodo = nodo->padre;
					nodo->revision = 1;
				}
			break;
			case 2: // revisa si el nodo tiene hijo derecho
				nodo->revision = 0;
				if(nodo->der==NULL){
					if(nodo->tipo==1){
						nodo = nodo->padre;
						cout<<" "<<nodo->dato;
						nodo->revision = 2;
					}else if(nodo->tipo==0){
						terminado = true;
						nodo->revision = 0;
					}else{
						nodo = nodo->padre;
						/*cout<<"cambiando a nodo padre..."<<endl;
						cout<<"nodo padre: "<<nodo->dato<<endl;*/
						nodo->revision = 1;
						//cout<<"revision: "<<nodo->revision<<endl;
					}
				}else{
					//cout<<"  nodo: "<<nodo->dato<<endl;
					nodo = nodo->der;
					//system("pause");
				}
			break;
		}
	}
}

/* Función que muestra el recorrido en preorden del árbol*/
void preorden(struct Nodo *raiz){
	cout<<"\n\tPreorden: ";
	struct Nodo *nodo;
	nodo = raiz;
	while(raiz->revision<3){
		switch(nodo->revision){
			case 0:
				cout<<nodo->dato<<" ";
				nodo->revision = 1;
			break;
			case 1:
				nodo->revision = 2;
				if(nodo->izq!=NULL){
					nodo = nodo->izq;
				}
			break;
			case 2:
				if(nodo->der==NULL){
					if(nodo->tipo == 0){
						nodo->revision = 3;
					}else{
						nodo->revision = 0;
						//cout<<"nodo->revision: "<<nodo->revision<<endl;
						if(nodo->tipo==2){
							nodo->padre->revision = 3;
						}
						nodo = nodo->padre;
						//cout<<"nodoPadre: "<<nodo->dato;
					}
				}else{
					nodo = nodo->der;
				}
			break;
			case 3:
				nodo->revision = 0;
				if(nodo->tipo==2){
					nodo->padre->revision = 3;
				}
				nodo = nodo->padre;
			break;
		}
	}
	raiz->revision = 0;
}

/* Función que inserta un nodo en el árbol*/
struct Nodo* insertarNodo(int info,struct Nodo *raiz){
	struct Nodo *nodo;
	struct Nodo *nuevo;
	bool doble = false; // toma el valor true cuando se intentar ingresar un número que ya está en el árbol
	if(raiz==NULL){ // si el árbol está vacío
		raiz = crearNodo(info);
		raiz->tipo = 0;
		cout<<"\n\tEl nodo fue creado como la raiz del arbol..."<<endl;
	}else{
		nodo = raiz; // apuntar a la raíz del árbol
		nuevo = crearNodo(info);
		while(!doble && nuevo->padre==NULL){
			if(info == nodo->dato){
				cout<<"\n\tEl nodo ya se encuentra en el arbol..."<<endl;
				doble = true;
			}else if(info < nodo->dato){
				if(nodo->izq==NULL){
					nuevo->padre = nodo;
					nodo->izq = nuevo;
					nuevo->tipo = 1;
					cout<<"\n\tDato insertado correctamente..."<<endl;
					cout<<"\tNodo padre: "<<nuevo->padre->dato<<endl;
					cout<<"\tHijo: "<<nuevo->tipo<<endl;
				}else{
					nodo = nodo->izq;
				}
			}else{ //if(info>nodo->dato)
				if(nodo->der == NULL){
					nuevo->padre = nodo;
					nodo->der = nuevo;
					nuevo->tipo = 2;
					cout<<"\n\tDato insertado correctamente..."<<endl;
					cout<<"\tNodo padre: "<<nuevo->padre->dato<<endl;
					cout<<"\tHijo: "<<nuevo->tipo<<endl;
				}else{
					nodo = nodo->der;
				}
			}
		}
	}
	return raiz;
}

/* Función que inicializa las variables de la estructura para el nodo.
   El valor de nuevo->dato se inicializa con el que define el usuario*/
struct Nodo* crearNodo(int info){
	struct Nodo* nuevo = new struct Nodo;
	nuevo->dato = info;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	nuevo->padre = NULL;
	nuevo->revision = 0;
	return nuevo;
}

/* Función que muestra el menú para el usuario*/
void menu(){
	cout<<"\n\t\t\t=== ARBOLES BINARIOS ==="<<endl<<endl;
	cout<<"\tInsertar nodo.........................................[1]"<<endl;
	cout<<"\tMostrar arbol.........................................[2]"<<endl;
	cout<<"\tMostrar recorridos (inorden, preorden, postorden).....[3]"<<endl;
	cout<<"\tBuscar nodo...........................................[4]"<<endl;
	cout<<"\tSalir.................................................[5]"<<endl;
	cout<<"\n\tSeleccione una opcion: ";
}
