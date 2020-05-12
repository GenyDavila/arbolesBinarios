#include <iostream>
#include <cstdlib>

using namespace std;

/* Definición de la estructura del nodo*/
struct Nodo{
	int dato;
	Nodo *izq;
	Nodo *der;
	Nodo *padre;	
};

/* Prototipos de funciones*/
void menu();
struct Nodo* insertarNodo(int info,struct Nodo *raiz);
struct Nodo* crearNodo(int info);

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
				cout<<"Dato a ingresar:";
				cin>>info;
				raiz = insertarNodo(info,raiz);
			break;
			case 2:
			break;
			case 3:
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
 
/* Función que inserta un nodo en el árbol*/
struct Nodo* insertarNodo(int info,struct Nodo *raiz){
	
}

/* Función que inicializa las variables de la estructura para el nodo.
   El valor de nuevo->dato se inicializa con el que define el usuario*/
struct Nodo* crearNodo(int info){
	struct Nodo* nuevo = new struct Nodo;
	nuevo->dato = info;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	nuevo->padre = NULL;
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
