#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <cctype>
#include <stdlib.h>
using namespace std;

// Variables globales para clientes
vector<string> codigosClientes;
vector<string> nombresClientes;
vector<int> edadesClientes;
vector<char> generosClientes;
vector<int> tiposClientes;  // 1: Mayorista, 2: Empresa, 3: Detalle
vector<int> diasRegistro;

// Variables globales para inventario
vector<string> productos = {"Martillo", "Destornillador", "Pala", "Cinta Metrica"};
vector<double> precios = {50.00, 40.00, 100.00, 30.00};
vector<int> stock = {150, 200, 80, 120};

// Variables para el carrito de compras
vector<string> itemsComprados;
vector<int> cantidadesCompradas;
vector<double> preciosItems;
double subtotal = 0;

// Funciones de utilidad
void limpiarPantalla() {
    system("cls");
}

void esperarEnter() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

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

int validarEdad() {
    int numero;
    while (true) {
        cout << "Edad: (1 a 100): ";
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

        cout << "Entrada invalida. Ingrese solo 'M' o 'F'\n";
    }
}

int validarTipoCliente() {
    int opcion;
    while (true) {
        cout << "Tipo cliente (1: Mayorista / 2: Empresa / 3: Detalle): ";
        cin >> opcion;
        
        if (cin.fail() || opcion < 1 || opcion > 3) {
            cout << "Opcion invalida. Ingrese 1, 2 o 3\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        }
    }
}

int validarDiaSemana() {
    int dia;
    do {
        limpiarPantalla();
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
            esperarEnter();
        } else {
            return dia;
        }
    } while(true);
}

// Funciones para clientes
string generarCodigo() {
    static int contador = 1;
    return "CLI-" + to_string(contador++);
}

void ingresarCliente() {
    char otro;
    
    do {
        limpiarPantalla();
        cout << "*********************************\n";
        cout << "*      REGISTRO DE CLIENTE      *\n";
        cout << "*********************************\n";
        
        string codigo = generarCodigo();
        cout << "Codigo del cliente: " << codigo << endl;
        codigosClientes.push_back(codigo);
        
        cin.ignore();
        nombresClientes.push_back(validarNombre("Nombre completo: "));
        edadesClientes.push_back(validarEdad());
        generosClientes.push_back(validarGenero());
        tiposClientes.push_back(validarTipoCliente());
        diasRegistro.push_back(validarDiaSemana());
        
        cout << "\nCliente registrado exitosamente!\n";
        cout << "¿Desea agregar otro cliente? (1: Si / 2: No): ";
        otro = validarSiNo();
    } while(otro == 1);
}

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

int main() {
    int opcionPrincipal;
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
        
        cin >> opcionPrincipal;
        
        if(cin.fail() || opcionPrincipal < 0 || opcionPrincipal > 4) {
            cout << "Opcion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();
            continue;
        }
        
        switch(opcionPrincipal) {
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
            case 3: {
                int opcionInventario;
                do {
                    limpiarPantalla();
                    
                    // Mostrar tabla de compras actual
                    if(!itemsComprados.empty()) {
                        cout << "\n*********************************************\n";
                        cout << "*               COMPRAS ACTUALES          *\n";
                        cout << "*********************************************\n";
                        cout << "*   Producto            | Cant | Subtotal  *\n";
                        cout << "*********************************************\n";
                        
                        for(size_t i = 0; i < itemsComprados.size(); i++) {
                            cout << "* " << left << setw(20) << itemsComprados[i] 
                                << "| " << right << setw(4) << cantidadesCompradas[i]
                                << " | L." << right << setw(7) << fixed << setprecision(2) 
                                 << preciosItems[i] << " *\n";
                        }
                        
                        cout << "*********************************************\n";
                        cout << "* SUBTOTAL:           |     | L." << right << setw(7) 
                             << subtotal << " *\n";
                        cout << "*********************************************\n\n";
                    }
                    
                    // Mostrar inventario
                    cout << "*********************************************\n";
                    cout << "*           INVENTARIO DISPONIBLE          *\n";
                    cout << "*********************************************\n";
                    cout << "*  # | Producto         | Precio  | Stock  *\n";
                    cout << "*********************************************\n";
                    
                    for(size_t i = 0; i < productos.size(); i++) {
                        cout << "* " << right << setw(2) << i+1 << " | " << left << setw(16) << productos[i]
                            << "| L." << right << setw(6) << fixed << setprecision(2) << precios[i]
                             << " | " << right << setw(6) << stock[i] << " *\n";
                    }
                    
                    cout << "*********************************************\n";
                    
                    if(codigosClientes.empty()) {
                        cout << "*   REGISTRE CLIENTES PARA HACER COMPRAS  *\n";
                        cout << "*********************************************\n";
                        cout << "* 0. Regresar                            *\n";
                        cout << "*********************************************\n";
                        cout << "Opcion: ";
                        
                        cin >> opcionInventario;
                        
                        if(opcionInventario != 0) {
                            cout << "Opción inválida! Debe registrar clientes primero.\n";
                            esperarEnter();
                        }
                    } else {
                        cout << "* 1. Comprar producto                    *\n";
                        cout << "* 2. Vaciar carrito (restaurar stock)    *\n";
                        cout << "* 0. Regresar                            *\n";
                        cout << "*********************************************\n";
                        cout << "Opcion: ";
                        
                        cin >> opcionInventario;
                        
                        if(opcionInventario == 1) {
                            // CÓDIGO CORREGIDO PARA COMPRAR
                            cout << "Seleccione producto (1-" << productos.size() << "): ";
                            int productoElegido;
                            cin >> productoElegido;
                            
                            if(cin.fail() || productoElegido < 1 || productoElegido > (int)productos.size()) {
                                cout << "¡Producto inválido! Debe ser entre 1 y " << productos.size() << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                esperarEnter();
                            } else {
                                int indice = productoElegido - 1;
                                cout << "Producto seleccionado: " << productos[indice] << endl;
                                cout << "Precio unitario: L." << precios[indice] << endl;
                                cout << "Stock disponible: " << stock[indice] << endl;
                                cout << "Ingrese cantidad a comprar: ";
                                
                                int cantidad;
                                cin >> cantidad;
                                
                                if(cin.fail() || cantidad <= 0) {
                                    cout << "¡Cantidad inválida! Debe ser un número positivo.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                } else if(cantidad > stock[indice]) {
                                    cout << "¡No hay suficiente stock! Solo hay " << stock[indice] << " unidades.\n";
                                } else {
                                    // Procesar compra correctamente
                                    stock[indice] -= cantidad;
                                    itemsComprados.push_back(productos[indice]);
                                    cantidadesCompradas.push_back(cantidad);
                                    double subtotalItem = precios[indice] * cantidad;
                                    preciosItems.push_back(subtotalItem);
                                    subtotal += subtotalItem;
                                    
                                    cout << "\n¡Compra realizada con éxito!\n";
                                    cout << "Se agregaron " << cantidad << " " << productos[indice] 
                                        << " al carrito (L." << subtotalItem << ")\n";
                                }
                                esperarEnter();
                            }
                        } 
                        else if(opcionInventario == 2) {
                            // Vaciar carrito y restaurar stock
                            for(size_t i = 0; i < itemsComprados.size(); i++) {
                                for(size_t j = 0; j < productos.size(); j++) {
                                    if(itemsComprados[i] == productos[j]) {
                                        stock[j] += cantidadesCompradas[i];
                                        break;
                                    }
                                }
                            }
                            
                            itemsComprados.clear();
                            cantidadesCompradas.clear();
                            preciosItems.clear();
                            subtotal = 0;
                            
                            cout << "Carrito vaciado y stock restaurado exitosamente.\n";
                            esperarEnter();
                        }
                        else if(opcionInventario != 0) {
                            cout << "¡Opción inválida! Seleccione 0, 1 o 2.\n";
                            esperarEnter();
                        }
                    }
                } while(opcionInventario != 0);
                break;
            }
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
    } while(opcionPrincipal != 0);
    
    return 0;
}
