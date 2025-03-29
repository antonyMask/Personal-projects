#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <cctype>
#include <stdlib.h>
using namespace std;

// ==================== VARIABLES GLOBALES ==================== //
// Vectores para almacenar informacion de clientes
vector<string> codigosClientes;    // Almacena códigos únicos de clientes
vector<string> nombresClientes;    // Almacena nombres completos de clientes
vector<int> edadesClientes;        // Almacena edades de clientes
vector<char> generosClientes;      // Almacena géneros de clientes (M/F)
vector<int> tiposClientes;         // Almacena tipos de cliente (1:Mayorista, 2:Empresa, 3:Detalle)
vector<int> diasRegistro;          // Almacena días de registro (1-7 para Lunes-Domingo)

// Vectores para informacion de productos
vector<string> productos = {"Martillo", "Destornillador", "Pala", "Cinta Metrica"};
vector<double> precios = {50.00, 40.00, 100.00, 30.00};
vector<int> stock = {150, 200, 80, 120};

// Vectores para el carrito de compras
vector<string> itemsComprados;     // Productos en el carrito
vector<int> cantidadesCompradas;   // Cantidades de cada producto
vector<double> preciosItems;       // Subtotal por cada producto
double subtotal = 0;               // Subtotal de la compra

// ==================== FUNCIONES DE UTILIDAD ==================== //


//Limpia la pantalla de la consola
void limpiarPantalla() {
    system("cls"); // Comando para limpiar pantalla en Windows
}

void esperarEnter() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // Espera entrada del usuario
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

        // Validar que no esté vacío
        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacio.\n";
            valido = false;
            continue;
        }

        // Validar que solo contenga letras y espacios
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

        // Validar que la entrada sea un solo carácter
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Entrada invalida. Ingrese solo 'M' o 'F'\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        genero = toupper(genero); // Convertir a mayúscula
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
        cout << "Tipo cliente (1:Mayorista / 2:Empresa / 3:Detalle): ";
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
        cout << "*   SELECCIONE EL DIA DE COMPRA  *\n";
        cout << "*********************************\n";
        cout << "* 1. Lunes                      *\n";
        cout << "* 2. Martes                     *\n";
        cout << "* 3. Miercoles                  *\n";
        cout << "* 4. Jueves                     *\n";
        cout << "* 5. Viernes                    *\n";
        cout << "* 6. Sabado                     *\n";
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

// ==================== FUNCIONES DE CLIENTES ==================== //


// Genera un codigo único para cada cliente (CLI-1, CLI-2, etc.)
string generarCodigo() {
    static int contador = 1; // Mantiene su valor entre llamadas
    return "CLI-" + to_string(contador++);
}


// Permite ingresar nuevos clientes al sistema
void ingresarCliente() {
    char otro;
    
    do {
        limpiarPantalla();
        cout << "*********************************\n";
        cout << "*      REGISTRO DE CLIENTE      *\n";
        cout << "*********************************\n";
        
        // Generar y mostrar código automático
        string codigo = generarCodigo();
        cout << "Codigo del cliente: " << codigo << endl;
        codigosClientes.push_back(codigo);
        
        // Solicitar y validar datos del cliente
        cin.ignore();
        nombresClientes.push_back(validarNombre("Nombre completo: "));
        edadesClientes.push_back(validarEdad());
        generosClientes.push_back(validarGenero());
        tiposClientes.push_back(validarTipoCliente());
        diasRegistro.push_back(validarDiaSemana());
        
        cout << "\nCliente registrado exitosamente!\n";
        cout << "¿Desea agregar otro cliente? (1:Si / 2:No): ";
        otro = validarSiNo();
    } while(otro == 1);
}


// Busca un cliente por su codigo y muestra sus datos

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
    // Buscar el cliente en el vector de códigos
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

/**
 * Muestra una lista de todos los clientes registrados
 */
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

/**
 * Menú para gestionar las operaciones con clientes
 */
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

// ==================== FUNCIONES DE FACTURACION ==================== //


// Verifica si un producto esta en el carrito
bool contieneProducto(const string& producto) {
    for(const auto& item : itemsComprados) {
        if(item == producto) return true;
    }
    return false;
}


// Procesa el pago segun el metodo seleccionado

void procesarPago(double total, int tipoCliente, const string& nombreCliente, int diaCompra, int edad, bool pagoConVisa) {
    int opcion;
    double monto;
    string tipoTarjeta = "";
    
    while(true) {
        limpiarPantalla();
        cout << "=================================\n";
        cout << "      SELECCIONE FORMA DE PAGO    \n";
        cout << "=================================\n";
        cout << "1. Efectivo\n";
        cout << "2. Tarjeta de credito\n";
        cout << "3. Tarjeta de debito\n";
        cout << "=================================\n";
        cout << "Total a pagar: L." << fixed << setprecision(2) << total << "\n";
        
        while(true) {
            cout << "Opcion (1-3): ";
            if(!(cin >> opcion) || opcion < 1 || opcion > 3) {
                cout << "Error: Ingrese un numero entre 1 y 3\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch(opcion) {
            case 1: { // Pago en efectivo
                while(true) {
                    cout << "\nIngrese monto recibido (L.): ";
                    if(!(cin >> monto)) {
                        cout << "Error: Ingrese un monto valido\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    if(monto <= 0) {
                        cout << "Error: El monto debe ser positivo\n";
                    } else if(monto < total) {
                        cout << "Monto insuficiente. Faltan L." 
                            << fixed << setprecision(2) << (total - monto) << "\n";
                    } else {
                        break;
                    }
                }
                
                // Mostrar recibo de pago en efectivo
                cout << "\n=================================\n";
                cout << "       COMPROBANTE DE PAGO     \n";
                cout << "---------------------------------\n";
                cout << "Cliente: " << nombreCliente << "\n";
                cout << "Metodo:  Efectivo\n";
                cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
                cout << "Recibido:L." << fixed << setprecision(2) << monto << "\n";
                cout << "Cambio:  L." << fixed << setprecision(2) << (monto - total) << "\n";
                cout << "=================================\n";
                return;
            }
                
            case 2: { // Pago con tarjeta de crédito
                while(true) {
                    cout << "\nTipo de tarjeta (Visa/Mastercard): ";
                    getline(cin, tipoTarjeta);
                    
                    // Convertir a mayúsculas
                    for(char &c : tipoTarjeta) c = toupper(c);
                    
                    if(tipoTarjeta == "VISA" || tipoTarjeta == "MASTERCARD") {
                        pagoConVisa = (tipoTarjeta == "VISA");
                        break;
                    }
                    cout << "Error: Solo aceptamos Visa o Mastercard\n";
                }
                
                // Mostrar recibo de pago con tarjeta
                cout << "\n=================================\n";
                cout << "       COMPROBANTE DE PAGO     \n";
                cout << "---------------------------------\n";
                cout << "Cliente: " << nombreCliente << "\n";
                cout << "Metodo:  Tarjeta " << tipoTarjeta << "\n";
                cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
                cout << "=================================\n";
                return;
            }
                
            case 3: { // Pago con tarjeta de débito
                if(tipoCliente != 1) {
                    cout << "\nError: Solo clientes mayoristas pueden pagar con debito\n";
                    esperarEnter();
                    continue;
                }
                
                // Mostrar recibo de pago con débito
                cout << "\n=================================\n";
                cout << "       COMPROBANTE DE PAGO     \n";
                cout << "---------------------------------\n";
                cout << "Cliente: " << nombreCliente << "\n";
                cout << "Metodo:  Tarjeta debito\n";
                cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
                cout << "=================================\n";
                return;
            }
        }
    }
}


// Muestra una factura detallada con todos los gastos

void mostrarFacturaDetallada(int indiceCliente) {
    limpiarPantalla();
    
    if(itemsComprados.empty()) {
        cout << "*********************************************\n";
        cout << "*               FACTURACION               *\n";
        cout << "*********************************************\n";
        cout << "*  No hay productos en el carrito          *\n";
        cout << "*********************************************\n";
        esperarEnter();
        return;
    }

    // Obtener datos del cliente
    int tipoCliente = tiposClientes[indiceCliente];
    int diaCompra = diasRegistro[indiceCliente];
    int edadCliente = edadesClientes[indiceCliente];
    
    // Calcular descuentos base según tipo de cliente
    double descuentoBase = 0.0;
    string descuentosAplicados = "";

    if(tipoCliente == 1) { // Mayorista 10%
        descuentoBase = subtotal * 0.10;
        descuentosAplicados += "- Descuento Mayorista (10%)\n";
    } else if(tipoCliente == 2) { // Empresa 15%
        descuentoBase = subtotal * 0.15;
        descuentosAplicados += "- Descuento Empresa (15%)\n";
    }
    
    // Calcular descuentos adicionales
    double descuentoAdicional = 0.0;
    
    // Descuento por día y producto específico
    if(tipoCliente == 3 && (diaCompra == 3 || diaCompra == 5) && contieneProducto("Cinta Metrica")) {
        descuentoAdicional = subtotal * 0.02;
        descuentosAplicados += "- Descuento 2% miercoles/viernes con Cinta Metrica\n";
    }
    else if(tipoCliente == 1 && (diaCompra == 6 || diaCompra == 7) && 
           (contieneProducto("Martillo") || contieneProducto("Destornillador"))) {
        descuentoAdicional = subtotal * 0.04;
        descuentosAplicados += "- Descuento 4% sabados/domingos con Martillo/Destornillador\n";
    }
    
    // Descuento para mayores de 60 años
    if(edadCliente > 60) {
        double descuentoEdad = subtotal * 0.06;
        descuentoAdicional += descuentoEdad;
        descuentosAplicados += "- Descuento 6% adulto mayor\n";
    }

    // Calcular impuesto (15%) sobre el subtotal menos descuentos
    double impuesto = (subtotal - descuentoBase - descuentoAdicional) * 0.15;
    double total = subtotal - descuentoBase - descuentoAdicional + impuesto;

    // Mostrar encabezado de la factura
    cout << "*********************************************\n";
    cout << "*          FACTURA DETALLADA              *\n";
    cout << "*********************************************\n";
    cout << "* CLIENTE: " << left << setw(31) << nombresClientes[indiceCliente] << "*\n";
    cout << "* CODIGO: " << left << setw(32) << codigosClientes[indiceCliente] << "*\n";
    cout << "* TIPO:   " << left << setw(32);
    switch(tipoCliente) {
        case 1: cout << "Mayorista"; break;
        case 2: cout << "Empresa"; break;
        case 3: cout << "Detalle"; break;
    }
    cout << "*\n";
    cout << "* DIA:    " << left << setw(32);
    switch(diaCompra) {
        case 1: cout << "Lunes"; break;
        case 2: cout << "Martes"; break;
        case 3: cout << "Miercoles"; break;
        case 4: cout << "Jueves"; break;
        case 5: cout << "Viernes"; break;
        case 6: cout << "Sabado"; break;
        case 7: cout << "Domingo"; break;
    }
    cout << "*\n";
    cout << "* EDAD:   " << left << setw(32) << to_string(edadCliente) + " años" << "*\n";
    cout << "*********************************************\n";
    
    // Mostrar detalle de productos
    cout << "*               DETALLE DE GASTOS          *\n";
    cout << "*********************************************\n";
    cout << "* PRODUCTO          CANT   PRECIO U.  SUBTOTAL *\n";
    cout << "*********************************************\n";
    
    for(size_t i = 0; i < itemsComprados.size(); i++) {
        cout << "* " << left << setw(16) << itemsComprados[i] 
             << " " << right << setw(4) << cantidadesCompradas[i]
             << "   L." << right << setw(6) << fixed << setprecision(2) 
             << preciosItems[i]/cantidadesCompradas[i]
             << "  L." << right << setw(8) << preciosItems[i] << " *\n";
    }
    
    // Mostrar totales y descuentos
    cout << "*********************************************\n";
    cout << "* SUBTOTAL:                     L." << right << setw(8) << subtotal << " *\n";
    
    if(descuentoBase > 0) {
        cout << "* DESCUENTO BASE:              -L." << right << setw(8) << descuentoBase << " *\n";
    }
    
    if(descuentoAdicional > 0) {
        cout << "* DESCUENTO ADICIONAL:         -L." << right << setw(8) << descuentoAdicional << " *\n";
    }
    
    cout << "* IMPUESTO (15%):                L." << right << setw(8) << impuesto << " *\n";
    cout << "*********************************************\n";
    cout << "* TOTAL A PAGAR:                 L." << right << setw(8) << total << " *\n";
    cout << "*********************************************\n";
    
    // Mostrar descuentos aplicados
    if(!descuentosAplicados.empty()) {
        cout << "* DESCUENTOS APLICADOS:\n";
        cout << "* " << left << setw(41) << descuentosAplicados << "*\n";
    }
    
    // Pie de factura
    cout << "*                                           *\n";
    cout << "*  ¡GRACIAS POR SU COMPRA!                  *\n";
    cout << "*                                           *\n";
    cout << "*********************************************\n";
}

/**
 * Menu para gestionar el proceso de facturación
 */
void menuFacturacion() {
    int opcion;
    int clienteSeleccionado = -1; // -1 indica que no hay cliente seleccionado
    
    do {
        limpiarPantalla();
        cout << "*********************************************\n";
        cout << "*         MENU DE FACTURACION              *\n";
        cout << "*********************************************\n";
        cout << "* 1. Seleccionar cliente                   *\n";
        cout << "* 2. Ver factura detallada                 *\n";
        cout << "* 3. Procesar pago                         *\n";
        cout << "* 0. Regresar al menu principal            *\n";
        cout << "*********************************************\n";
        
        // Mostrar cliente actual si hay uno seleccionado
        if(clienteSeleccionado != -1) {
            cout << "* Cliente actual: " << left << setw(24) << nombresClientes[clienteSeleccionado] << "*\n";
            cout << "*********************************************\n";
        }
        
        cout << "Opcion: ";
        cin >> opcion;
        
        // Validar entrada
        if(cin.fail() || opcion < 0 || opcion > 3) {
            cout << "Opcion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();
            continue;
        }
        
        switch(opcion) {
            case 1: { // Seleccionar cliente
                limpiarPantalla();
                cout << "*********************************************\n";
                cout << "*        SELECCIONE UN CLIENTE             *\n";
                cout << "*********************************************\n";
                
                // Mostrar lista de clientes
                for(size_t i = 0; i < codigosClientes.size(); i++) {
                    cout << "* " << i+1 << ". " << left << setw(20) << nombresClientes[i] 
                         << " (" << codigosClientes[i] << ") ";
                    switch(tiposClientes[i]) {
                        case 1: cout << "Mayorista"; break;
                        case 2: cout << "Empresa"; break;
                        case 3: cout << "Detalle"; break;
                    }
                    cout << " *\n";
                }
                cout << "*********************************************\n";
                cout << "Seleccione el cliente (1-" << codigosClientes.size() << "): ";
                
                int seleccion;
                cin >> seleccion;
                
                // Validar selección
                if(cin.fail() || seleccion < 1 || seleccion > (int)codigosClientes.size()) {
                    cout << "Seleccion invalida!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    esperarEnter();
                } else {
                    clienteSeleccionado = seleccion - 1;
                    cout << "Cliente seleccionado: " << nombresClientes[clienteSeleccionado] << endl;
                    esperarEnter();
                }
                break;
            }
                
            case 2: { // Ver factura detallada
                if(clienteSeleccionado == -1) {
                    cout << "Primero seleccione un cliente.\n";
                    esperarEnter();
                } else {
                    mostrarFacturaDetallada(clienteSeleccionado);
                    esperarEnter();
                }
                break;
            }
                
            case 3: { // Procesar pago
                if(clienteSeleccionado == -1) {
                    cout << "Primero seleccione un cliente.\n";
                    esperarEnter();
                } else if(itemsComprados.empty()) {
                    cout << "No hay productos en el carrito.\n";
                    esperarEnter();
                } else {
                    // Obtener datos necesarios para el pago
                    int tipoCliente = tiposClientes[clienteSeleccionado];
                    int diaCompra = diasRegistro[clienteSeleccionado];
                    int edad = edadesClientes[clienteSeleccionado];
                    bool pagoConVisa = false;
                    
                    // Calcular total (similar a mostrarFacturaDetallada)
                    double descuentoBase = 0.0;
                    if(tipoCliente == 1) descuentoBase = subtotal * 0.10;
                    else if(tipoCliente == 2) descuentoBase = subtotal * 0.15;
                    
                    double descuentoAdicional = 0.0;
                    if(tipoCliente == 3 && (diaCompra == 3 || diaCompra == 5) && contieneProducto("Cinta Metrica")) {
                        descuentoAdicional = subtotal * 0.02;
                    }
                    else if(tipoCliente == 1 && (diaCompra == 6 || diaCompra == 7) && 
                           (contieneProducto("Martillo") || contieneProducto("Destornillador"))) {
                        descuentoAdicional = subtotal * 0.04;
                    }
                    
                    if(edad > 60) {
                        descuentoAdicional += subtotal * 0.06;
                    }
                    
                    double impuesto = (subtotal - descuentoBase - descuentoAdicional) * 0.15;
                    double total = subtotal - descuentoBase - descuentoAdicional + impuesto;
                    
                    // Procesar el pago
                    procesarPago(total, tipoCliente, nombresClientes[clienteSeleccionado], diaCompra, edad, pagoConVisa);
                    
                    // Vaciar carrito y resetear cliente seleccionado
                    itemsComprados.clear();
                    cantidadesCompradas.clear();
                    preciosItems.clear();
                    subtotal = 0;
                    clienteSeleccionado = -1;
                    
                    esperarEnter();
                }
                break;
            }
                
            case 0: { // Regresar al menú principal
                return;
            }
        }
    } while(true);
}

// ==================== FUNCIONES DE INVENTARIO ==================== //


int seleccionarCliente() {
    limpiarPantalla();
    
    if(codigosClientes.empty()) {
        cout << "No hay clientes registrados. Registre clientes primero.\n";
        esperarEnter();
        return -1;
    }
    
    cout << "*********************************************\n";
    cout << "*        SELECCIONE UN CLIENTE             *\n";
    cout << "*********************************************\n";
    for(size_t i = 0; i < codigosClientes.size(); i++) {
        cout << "* " << i+1 << ". " << left << setw(20) << nombresClientes[i] 
             << " (" << codigosClientes[i] << ") ";
        switch(tiposClientes[i]) {
            case 1: cout << "Mayorista"; break;
            case 2: cout << "Empresa"; break;
            case 3: cout << "Detalle"; break;
        }
        cout << " *\n";
    }
    cout << "*********************************************\n";
    cout << "Seleccione el cliente (1-" << codigosClientes.size() << "): ";
    
    int clienteSeleccionado;
    cin >> clienteSeleccionado;
    
    if(cin.fail() || clienteSeleccionado < 1 || clienteSeleccionado > (int)codigosClientes.size()) {
        cout << "Seleccion invalida!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        esperarEnter();
        return -1;
    }
    
    return clienteSeleccionado - 1;
}

/**
 * Menu para gestionar el inventario y las compras
 */
void menuInventario() {
    int clienteActual = -1; // -1 indica que no hay cliente seleccionado
    
    while(true) {
        if(clienteActual == -1) {
            clienteActual = seleccionarCliente();
            if(clienteActual == -1) return;
            
            limpiarPantalla();
            cout << "Cliente seleccionado: " << nombresClientes[clienteActual] << "\n";
            esperarEnter();
        }
        
        int opcionInventario;
        do {
            limpiarPantalla();
            
            // Mostrar información del cliente actual
            if(clienteActual != -1) {
                cout << "Cliente actual: " << nombresClientes[clienteActual] << " (";
                switch(tiposClientes[clienteActual]) {
                    case 1: 
                        cout << "Mayorista - Puede comprar entre 6-12 productos";
                        break;
                    case 2: 
                        cout << "Empresa - Debe comprar minimo 13 productos";
                        break;
                    case 3: 
                        cout << "Detalle - Puede comprar cualquier cantidad de producto";
                        break;
                }
                cout << ")\n";
            }
            else {
                cout << "No hay cliente seleccionado (registre clientes primero)\n";
            }
            
            // Mostrar carrito actual si hay productos
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
            
            // Mostrar inventario disponible
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
            
            // Mostrar opciones del menú
            if(clienteActual != -1) {
                cout << "* 1. Comprar producto                    *\n";
                cout << "* 2. Vaciar carrito (restaurar stock)    *\n";
                cout << "* 3. Cambiar cliente                     *\n";
            }
            else {
                cout << "* (Registre clientes para habilitar compras) *\n";
            }
            cout << "* 0. Regresar al menu principal          *\n";
            cout << "*********************************************\n";
            cout << "Opcion: ";
            
            cin >> opcionInventario;
            
            // Validar opción según si hay cliente seleccionado
            int maxOpcion = (clienteActual != -1) ? 3 : 0;
            if(cin.fail() || opcionInventario < 0 || opcionInventario > maxOpcion) {
                cout << "¡Opcion invalida! ";
                if(clienteActual != -1) {
                    cout << "Seleccione 0-3.\n";
                }
                else {
                    cout << "Solo puede regresar (0).\n";
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                esperarEnter();
                continue;
            }
            
            switch(opcionInventario) {
                case 1: { // Comprar producto
                    if(clienteActual == -1) break;
                    
                    cout << "Seleccione producto (1-" << productos.size() << "): ";
                    int productoElegido;
                    cin >> productoElegido;
                    
                    // Validar selección de producto
                    if(cin.fail() || productoElegido < 1 || productoElegido > (int)productos.size()) {
                        cout << "¡Producto invalido! Debe ser entre 1 y " << productos.size() << endl;
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
                        
                        // Validar cantidad
                        if(cin.fail() || cantidad <= 0) {
                            cout << "¡Cantidad invalida! Debe ser un numero positivo.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            esperarEnter();
                        } else if(cantidad > stock[indice]) {
                            cout << "¡No hay suficiente stock! Solo hay " << stock[indice] << " unidades.\n";
                            esperarEnter();
                        } else {
                            // Validar límites según tipo de cliente (excepto para detalle)
                            int totalTemp = cantidad;
                            for(int cant : cantidadesCompradas) totalTemp += cant;
                            
                            bool limiteExcedido = false;
                            switch(tiposClientes[clienteActual]) {
                                case 1: // Mayorista
                                    if(totalTemp > 12) {
                                        cout << "¡Limite excedido! Mayorista maximo 12 productos.\n";
                                        limiteExcedido = true;
                                    }
                                    break;
                                case 2: // Empresa
                                    if(totalTemp < 13) {
                                        cout << "¡Minimo requerido! Empresa debe comprar al menos 13 productos.\n";
                                        limiteExcedido = true;
                                    }
                                    break;
                                // No hay validación para clientes de detalle
                            }
                            
                            if(!limiteExcedido) {
                                // Actualizar stock y carrito
                                stock[indice] -= cantidad;
                                itemsComprados.push_back(productos[indice]);
                                cantidadesCompradas.push_back(cantidad);
                                double subtotalItem = precios[indice] * cantidad;
                                preciosItems.push_back(subtotalItem);
                                subtotal += subtotalItem;
                                
                                cout << "\n¡Compra realizada con exito!\n";
                                cout << "Se agregaron " << cantidad << " " << productos[indice] 
                                    << " al carrito (L." << subtotalItem << ")\n";
                            }
                            esperarEnter();
                        }
                    }
                    break;
                }
                
                case 2: { // Vaciar carrito
                    if(clienteActual == -1) break;
                    
                    // Restaurar stock de productos
                    for(size_t i = 0; i < itemsComprados.size(); i++) {
                        for(size_t j = 0; j < productos.size(); j++) {
                            if(itemsComprados[i] == productos[j]) {
                                stock[j] += cantidadesCompradas[i];
                                break;
                            }
                        }
                    }
                    
                    // Vaciar vectores del carrito
                    itemsComprados.clear();
                    cantidadesCompradas.clear();
                    preciosItems.clear();
                    subtotal = 0;
                    
                    cout << "Carrito vaciado y stock restaurado exitosamente.\n";
                    esperarEnter();
                    break;
                }
                
                case 3: { // Cambiar cliente
                    if(clienteActual == -1) break;
                    clienteActual = -1; // Resetear cliente seleccionado
                    break;
                }
                
                case 0: { // Regresar al menú principal
                    return;
                }
            }
        } while(true);
    }
}


// ==================== MENU PRINCIPAL ==================== //
// Función principal que muestra el menú principal
int main() {
    int opcionPrincipal;
    do {
        limpiarPantalla();
        // Mostrar menu principal
        cout << "*******************************************\n";
        cout << "*      FERRETERIA CONSTRU-PUMA           *\n";
        cout << "*           MENU PRINCIPAL               *\n";
        cout << "*******************************************\n";
        cout << "* 1. Clientes                            *\n";
        cout << "* 2. Facturacion                         *\n";
        cout << "* 3. Inventario                          *\n";
        cout << "* 0. Salir                               *\n";
        cout << "*******************************************\n";
        cout << "Opcion: ";
        
        cin >> opcionPrincipal;
        
        // Validar opcion del menu principal
        if(cin.fail() || opcionPrincipal < 0 || opcionPrincipal > 3) {
            cout << "Opcion invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            esperarEnter();
            continue;
        }
        
        // Procesar opcion seleccionada
        switch(opcionPrincipal) {
            case 1: // Menú de clientes
                menuClientes();
                break;
                
            case 2: // Menu de facturación
                if(codigosClientes.empty()) {
                    cout << "Debe registrar clientes primero.\n";
                    esperarEnter();
                } else {
                    menuFacturacion();
                }
                break;
                
            case 3: // Menu de inventario
                menuInventario();
                break;
                
            case 0: // Salir del sistema
                cout << "Saliendo del sistema...\n";
                break;
        }
    } while(opcionPrincipal != 0);
    
    return 0;
}
