#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <set>
#include <limits>
using namespace std;
void generarGrafo(const int* A, int numNodos) {
    ofstream archivoDOT("grafo.dot");
    if (!archivoDOT) {   
        cout << "Error al abrir el archivo DOT." << endl;
        return;
    }
    archivoDOT << "graph Grafo {" << std::endl;
    for (int i = 0; i < numNodos; i++) {
        archivoDOT << "    " << i + 1 << endl;
    }
    for (int i = 0; i < numNodos; i++) {
        for (int j = i + 1; j < numNodos; j++) {
            if (*(A + i * numNodos + j) == 1) {
                archivoDOT << "    " << i + 1 << " -- " << j + 1 << endl;
            }
        }
    }
    archivoDOT << "}" << endl;
    archivoDOT.close();	
    system("dot -Tpng grafo.dot -o grafo.png");
    cout << "Grafo generado correctamente." << endl;
}

void numero_amigos(const int* A, int num, int numNodos){
    int n_amigos = 0;
    int i = num - 1;
    for(int j = 0; j < numNodos; j++){
        if(*(A + i * numNodos + j) == 1){
            n_amigos++; 
        }
    }
    cout << "La Persona" << num << " tiene " << n_amigos << " amigos";
}

void escrib_amigos(const int* A, int num, int numNodos) {
    int n_amigos = 0;
    int i = num - 1;
    bool hay_amigos = false; // Variable para verificar si se encontraron amigos
    for (int j = 0; j < numNodos; j++) {
        if (*(A + i * numNodos + j) == 1) {
            cout << "Persona" << j + 1 << " ";
            hay_amigos = true; // Se encontraron amigos
        }
    }
    if (!hay_amigos) {
        cout << "No hay amigos" << endl;
    }
}

void sug_amigos(const int* A, int num, int numNodos) {
    set<int> amigos_de_amigos;
    set<int> amigos_directos;

    int i = num - 1;
    // Obtener los amigos directos del individuo principal
    for (int j = 0; j < numNodos; j++) {
        if (*(A + i * numNodos + j) == 1) {
            amigos_directos.insert(j + 1);
        }
    }
    // Obtener los amigos de los amigos
    for (int j = 0; j < numNodos; j++) {
        if (*(A + i * numNodos + j) == 1) {
            for (int k = 0; k < numNodos; k++) {
                if (k != i && *(A + j * numNodos + k) == 1 && amigos_directos.count(k + 1) == 0) {
                    amigos_de_amigos.insert(k + 1);
                }
            }
        }
    }
    // Mostrar los amigos de los amigos que no son amigos directos
    if (amigos_de_amigos.empty()) {
        cout << "No hay amigos sugeridos";
    } else {
        set<int>::iterator it;
        for (it = amigos_de_amigos.begin(); it != amigos_de_amigos.end(); ++it) {
            cout << "Persona" << *it << " ";
        }
    }
}

int main() {
    srand(time(NULL));
    int n;
    cout << "Ingrese el numero de miembros de la red social: ";
    cin >> n;
    while(cin.fail()){ // Verificar si la entrada es inválida
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
            cout << "Entrada invalida. Por favor, ingrese un numero valido: ";
            cin >> n;
        }
    int A[n][n];
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(i == j || j == i){
                A[i][j] = 0;
            } else {
                A[i][j] = rand() % 2;
                A[j][i] = A[i][j];
            }
        }
    }
    cout << "\nEscribiendo la matriz de adyacencia del grafo de orden "<<n<<"x"<<n<<" \n" << endl;
    for(int i = 0; i < n + 1; i++){
        if(i < 10){
            if(i == 1){
                cout << " ";
            }
            cout << i;
            if(i == 0){
                cout << "  ";
            } else {
                if(i < 9){
                    cout << "  ";
                } else {
                    if(i == 9){
                        cout << " ";
                    }
                }
            }
        } else {
            cout << i << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < n + 1; i++){
        if(i == 0){
            cout << "  ";
        } else {
            if(i < 10){
                if(i == 1){
                    cout << "-";
                }
                if(i < 9){
                    cout << "---";
                } else {
                    if(i == 9){
                        cout << "--";
                    }
                }
            } else {
                if(i == n){
                    cout << "--";
                } else {
                    cout << "---";
                }
            }
        }
    }
    cout << "-" << endl;
    for(int i = 0; i < n; i++){
        cout << i + 1;
        if(i + 1 < 9){
            cout << " |";
        } else {
            if(i + 1 == 9){
                cout << " ";
            }
            cout << "|";
        }
        for(int j = 0; j < n; j++){
            cout << " " << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    generarGrafo(&A[0][0], n);

    int num_per;
    int m = 0;
    int bus = 0;
    while(m == 0){
        cout << "\nIngrese el numero de persona a buscar: Persona";
        cin >> num_per;
		 while(cin.fail()){ // Verificar si la entrada es inválida
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
            cout << "Entrada invalida. Por favor, ingrese un numero valido: ";
            cin >> num_per;
        }
        cout << "\n- Opciones a elegir para la Persona" << num_per;
        cout << "\n  + Numero de amigos de Persona" << num_per << " (1)";
        cout << "\n  + Amigos de Persona" << num_per << " (2)";
        cout << "\n  + Amigos sugeridos para la Persona" << num_per << " (3)";

        while(bus == 0){
            cout << "\n*Seleccione que quiere buscar: ";
            cin >> bus;
         while(cin.fail()){ // Verificar si la entrada es inválida
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
            cout << "Entrada invalida. Por favor, ingrese un numero valido: ";
            cin >> bus;
        }
            if(bus == 1){
                cout << "      -";
                numero_amigos(&A[0][0], num_per, n);
                bus = 0;
            } else if(bus == 2){
                cout << "      -Los amigos de la Persona" << num_per << " son: ";
                escrib_amigos(&A[0][0], num_per, n);
                bus = 0;
            } else if(bus == 3){
                cout << "      -Los amigos sugeridos para Persona" << num_per << ": ";
                sug_amigos(&A[0][0], num_per, n);
                bus = 0;
            } else {
                bus = 0;
                cout << "      -Opcion no encontrada";
            }      
        cout << "\n\nQuiere continuar con Persona" << num_per << "? Si(0) No(Otro numero): ";
        cin >> bus;
		
        while(cin.fail()){ // Verificar si la entrada es inválida
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
            cout << "Entrada invalida. Por favor, ingrese un numero valido: ";
            cin >> bus;
        }
    }


    cout << "\nSalio de la Persona" << num_per;
    cout << "\nQuiere elegir a otra Persona? Si(0) No(Otro numero): ";
    cin >> m;
    while(cin.fail()){ // Verificar si la entrada es inválida
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
        cout << "Entrada invalida. Por favor, ingrese un numero valido: ";
        cin >> m;
    }  
    if(m == 0){
    	cout << "\nSalio de la Persona" << num_per;
        cout << "\n---------------------------------------------------------------";
        bus=0;
    }
}
	cout<<"\nSaliendo del programa"<<endl;
    return 0;
}


