#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<limits>
#include<cctype>
#include<stdlib.h>
using namespace std;


// Variables globales para almacenar clientes (usando vectores separados)
vector<string> codigosClientes;
vector<string> nombresClientes;
vector<int> edadesClientes;
vector<char> generosClientes;
vector<int> tiposClientes;  // 1: Mayorista, 2: Empresa, 3: Detalle
vector<int> diasRegistro;

// FUNCIONES PARA VALIDACIONES
void limpiarPantalla() {
    system("cls"); // Comando para sistemas Windows
}

// Pausa el programa hasta que el usuario presione Enter
void esperarEnter() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Valida respuestas Sí/No (1 o 2)
int validarSiNo() {
    int opcion;
    while (true) {
        cout << "1. Si\n2. No\nOpcion: ";
        cin >> opcion;
        
        if (cin.fail() || (opcion != 1 && opcion != 2)) {
            cout << "Opcion invalida. Ingrese 1 o 2\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        }
    }
}

// Valida que el nombre solo contenga letras y espacios
string validarNombre(string mensaje) {
    string nombre;
    bool valido;
    do {
        valido = true;
        cout << mensaje;
        getline(cin, nombre);

        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacio.\n";
            valido = false;
            continue;
        }

        for (char c : nombre) {
            if (!isalpha(c) && c != ' ') {
                cout << "Error: Solo se permiten letras y espacios.\n";
                valido = false;
                break;
            }
        }
    } while (!valido);
    return nombre;
}

// Valida que la edad esté entre 1 y 100
int validarEdad() {
    int numero;
    while (true) {
        cout << "Edad: (Ingresar unicamente valores entre 1 a 100): ";
        cin >> numero;
        
        if (cin.fail()) {
            cout << "Error al ingresar la edad. Intente de nuevo\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (numero < 1 || numero > 100) {
            cout << "Error: La edad debe estar entre 1 y 100\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return numero;
}

// Valida el género (M/F)
char validarGenero() {
    char genero;
    while (true) {
        cout << "Genero (M/F): ";
        cin >> genero;

        if (cin.fail() || cin.peek() != '\n') {
            cout << "Entrada invalida. Ingrese solo 'M' o 'F'\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        genero = toupper(genero);
        if (genero == 'M' || genero == 'F') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return genero;
        }

        cout << "Entrada invalida. Ingrese solo 'M' para masculino o 'F' para femenino\n";
    }
}

// Valida el tipo de cliente (1. Mayorista / 2. Empresa / 3. Detalle)
int validarPedido() {
    int opcion;
    while (true) {
        cout << "Tipo de cliente (1. MAYORISTA / 2. EMPRRESA / 3. DETALLE): ";
        cin >> opcion;
        
        if (cin.fail() || (opcion != 1 && opcion != 2 && opcion !=3)) {
            cout << "Opcion invalida. Ingrese 1, 2 o 3\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        }
    }
}

// Valida el dia que el cliente hizo la compra
int validarDiaSemana() {
    int dia;
    do {
        limpiarPantalla();  // Usa tu función existente
        cout << "*********************************\n";
        cout << "*   SELECCIONE EL DÍA DE COMPRA  *\n";
        cout << "*********************************\n";
        cout << "* 1. Lunes                      *\n";
        cout << "* 2. Martes                     *\n";
        cout << "* 3. Miércoles                  *\n";
        cout << "* 4. Jueves                     *\n";
        cout << "* 5. Viernes                    *\n";
        cout << "* 6. Sábado                     *\n";
        cout << "* 7. Domingo                    *\n";
        cout << "*********************************\n";
        cout << "Ingrese el numero del dia (1-7): ";
        
        cin >> dia;
        
        if(cin.fail() || dia < 1 || dia > 7) {
            cout << "Error! Debe ingresar un numero del 1 al 7.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();  // Usa tu función existente
        } else {
            return dia;
        }
    } while(true);
}

// Función para generar un código automático
string generarCodigo() {
    static int contador = 1;
    return "CLI-" + to_string(contador++);
}

// Función para ingresar un nuevo cliente
void ingresarCliente() {
    char otro;
    
    do {
        limpiarPantalla();
        cout << "*********************************\n";
        cout << "*      REGISTRO DE CLIENTE      *\n";
        cout << "*********************************\n";
        
        // Generar y mostrar código
        string codigo = generarCodigo();
        cout << "Codigo del cliente: " << codigo << endl;
        codigosClientes.push_back(codigo);
        
        // Validar y almacenar datos
        cin.ignore();
        nombresClientes.push_back(validarNombre("Nombre completo: "));
        edadesClientes.push_back(validarEdad());
        generosClientes.push_back(validarGenero());
        tiposClientes.push_back(validarPedido());
        diasRegistro.push_back(validarDiaSemana());
        
        cout << "\nCliente registrado exitosamente!\n";
        cout << "¿Desea agregar otro cliente? (1: Si / 2: No): ";
        otro = validarSiNo();
    } while(otro == 1);
}

// Función para buscar un cliente por código
void buscarCliente() {
    limpiarPantalla();
    cout << "*********************************\n";
    cout << "*       BUSCAR CLIENTE          *\n";
    cout << "*********************************\n";
    
    if(codigosClientes.empty()) {
        cout << "No hay clientes registrados.\n";
        esperarEnter();
        return;
    }
    
    string codigo;
    cout << "Ingrese el codigo del cliente: ";
    cin >> codigo;
    
    bool encontrado = false;
    for(size_t i = 0; i < codigosClientes.size(); i++) {
        if(codigosClientes[i] == codigo) {
            cout << "\nDatos del cliente:\n";
            cout << "Codigo: " << codigosClientes[i] << endl;
            cout << "Nombre: " << nombresClientes[i] << endl;
            cout << "Edad: " << edadesClientes[i] << endl;
            cout << "Genero: " << generosClientes[i] << endl;
            cout << "Tipo: ";
            switch(tiposClientes[i]) {
                case 1: cout << "Mayorista"; break;
                case 2: cout << "Empresa"; break;
                case 3: cout << "Detalle"; break;
            }
            cout << "\nDia registro: ";
            switch(diasRegistro[i]) {
                case 1: cout << "Lunes"; break;
                case 2: cout << "Martes"; break;
                case 3: cout << "Miercoles"; break;
                case 4: cout << "Jueves"; break;
                case 5: cout << "Viernes"; break;
                case 6: cout << "Sabado"; break;
                case 7: cout << "Domingo"; break;
            }
            cout << endl;
            encontrado = true;
            break;
        }
    }
    
    if(!encontrado) {
        cout << "Cliente no encontrado.\n";
    }
    
    esperarEnter();
}

// Función para mostrar todos los clientes
void mostrarClientes() {
    limpiarPantalla();
    cout << "*********************************\n";
    cout << "*       LISTA DE CLIENTES       *\n";
    cout << "*********************************\n";
    
    if(codigosClientes.empty()) {
        cout << "No hay clientes registrados.\n";
    } else {
        for(size_t i = 0; i < codigosClientes.size(); i++) {
            cout << "Codigo: " << codigosClientes[i] << endl;
            cout << "Nombre: " << nombresClientes[i] << endl;
            cout << "Tipo: ";
            switch(tiposClientes[i]) {
                case 1: cout << "Mayorista"; break;
                case 2: cout << "Empresa"; break;
                case 3: cout << "Detalle"; break;
            }
            cout << "\n---------------------------\n";
        }
    }
    
    esperarEnter();
}

// Menú de clientes
void menuClientes() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "*********************************\n";
        cout << "*        MENU DE CLIENTES       *\n";
        cout << "*********************************\n";
        cout << "* 1. Ingresar cliente           *\n";
        cout << "* 2. Buscar cliente             *\n";
        cout << "* 3. Mostrar clientes           *\n";
        cout << "* 4. Salir                      *\n";
        cout << "*********************************\n";
        cout << "Opcion: ";
        
        cin >> opcion;
        
        if(cin.fail() || opcion < 1 || opcion > 4) {
            cout << "Opcion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();
            continue;
        }
        
        switch(opcion) {
            case 1: ingresarCliente(); break;
            case 2: buscarCliente(); break;
            case 3: mostrarClientes(); break;
            case 4: break;
        }
    } while(opcion != 4);
}

// Menú principal
void menuPrincipal() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "*******************************************\n";
        cout << "*      FERRETERIA CONSTRU-PUMA           *\n";
        cout << "*           MENU PRINCIPAL               *\n";
        cout << "*******************************************\n";
        cout << "* 1. Clientes                            *\n";
        cout << "* 2. Facturacion                         *\n";
        cout << "* 3. Inventario                          *\n";
        cout << "* 4. Descuentos                          *\n";
        cout << "* 0. Salir                               *\n";
        cout << "*******************************************\n";
        cout << "Opcion: ";
        
        cin >> opcion;
        
        if(cin.fail() || opcion < 0 || opcion > 4) {
            cout << "Opcion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();
            continue;
        }
        
        switch(opcion) {
            case 1: menuClientes(); break;
            case 2: 
                if(codigosClientes.empty()) {
                    cout << "Debe registrar clientes primero.\n";
                    esperarEnter();
                } else {
                    cout << "Facturacion (en desarrollo)\n";
                    esperarEnter();
                }
                break;
            case 3: 
                cout << "Inventario (en desarrollo)\n";
                esperarEnter();
                break;
            case 4: 
                if(codigosClientes.empty()) {
                    cout << "Debe registrar clientes primero.\n";
                    esperarEnter();
                } else {
                    cout << "Descuentos (en desarrollo)\n";
                    esperarEnter();
                }
                break;
            case 0: cout << "Saliendo del sistema...\n"; break;
        }
    } while(opcion != 0);
}

int main() {
    menuPrincipal();
    return 0;
}
