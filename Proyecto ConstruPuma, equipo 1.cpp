/*GRUPO #1: CONSTRU-PUMA
JORGE ANTONIO MENDOZA MANUN-20241001415
DARWIN SAMUEL ESPINO ALVARADO-20211024422
LUIS ENRIQUE ELVIR LOPEZ-2022100710
ROSA BELINDA OSORIO ANDINO-20241000830
*/
#include <iostream>
#include <vector> //Permite trabajar mejor con los vectores
#include <string> // Manejo avanzado de strings (concatenacion, busqueda, etc.)
#include <iomanip> // Formateo de salida (setw para anchos fijos, fixed para decimales)
#include <limits> // Limites numericos (usado en cin.ignore para limpiar buffers)
#include <cctype> // Funciones para caracteres (validar entradas con isalpha())
#include <stdlib.h> // Funciones generales de C (limpieza de pantalla con system("cls"))
#include <ctime> // Funciones de manejo de tiempo (time(), clock())
using namespace std;

// ==================== VARIABLES GLOBALES ==================== //
// Vectores para almacenar informacion de clientes
vector<string> codigosClientes;       // Almacena codigos de clientes
vector<string> nombresClientes;       // Almacena nombres de clientes
vector<int> edadesClientes;           // Almacena edades de clientes
vector<int> generosClientes;          // Almacena generos de clientes (1: Masculino, 2: Femenino)
vector<int> tiposClientes;            // Almacena tipos de clientes (1: Mayorista, 2: Empresa, 3: Detalle)
vector<int> diasRegistro;             // Almacena dias de registro de clientes (1-7: Lunes-Domingo)

// Vectores para almacenar informacion de productos
vector<string> productos = {"Martillo", "Destornillador", "Pala", "Cinta Metrica"}; // Nombres de productos
vector<double> precios = {50.00, 40.00, 100.00, 30.00};                             // Precios de productos
vector<int> stock = {150, 200, 80, 120};                                           // Stock de productos

// Vectores para gestionar compras
vector<string> itemsComprados;         // Productos comprados en la transaccion actual
vector<int> cantidadesCompradas;       // Cantidades de productos comprados
vector<double> preciosItems;           // Precios totales por producto
vector<int> metodosPago;               // Metodos de pago (1: Efectivo, 2: Tarjeta credito, 3: Tarjeta debito)
vector<string> detallesTarjetas;       // Detalles de tarjetas (Visa, Mastercard)
vector<double> montosPagados;          // Montos pagados en transacciones
vector<vector<string>> historialCompras; // Historial de compras por cliente

double subtotal = 0;                   // Subtotal de la compra actual
int clienteActual = -1;                // indice del cliente actual en los vectores (-1: no seleccionado)

// ==================== FUNCIONES ESENCIALES ==================== //

// Limpia la pantalla de la consola
void limpiarPantalla() {
	system("cls");
}

// Espera a que el usuario presione Enter para continuar
void esperarEnter() {
	cout << "\nPresione Enter para continuar...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

// ==================== MODULO DE CLIENTES ==================== //

// Registra un nuevo cliente
void ingresarCliente() {
	int otro;
	do {
		limpiarPantalla();
		cout << "*********************************\n";
		cout << "*      REGISTRO DE CLIENTE      *\n";
		cout << "*********************************\n";
		
		static int contador = 1;
		string codigo = "CLI-" + to_string(contador); // Genera un codigo unico para el cliente
		contador++;
		codigosClientes.push_back(codigo);
		cout << "Codigo del cliente: " << codigo << endl;
		
		// Validacion del nombre
		string nombre;
		bool nombreValido;
		
		do {
			nombreValido = true; // Reiniciar validacion
			
			cout << "Nombre completo: ";
			
			// Limpiar buffer SOLO si hay contenido previo
			// Para evitar confusiones con el cin.ignore este segmento funciona solo cuando ya hay registro de un cliente
			// Se limpia para que el buffer de entrada se mantenga limpio y recibiendo nuevos datos para optimizar memoria
			if (cin.peek() == '\n') {
				cin.ignore(10000, '\n');
			}
			
			getline(cin, nombre);
			
			// Validaciones
			if (nombre.empty()) {
				cout << "Error: No puede estar vacio\n";
				nombreValido = false;
			} else if (nombre.find(' ') == string::npos) {
				cout << "Error: Debe incluir nombre y apellido\n";
				nombreValido = false;
			}
			
		} while (!nombreValido);
		
		nombresClientes.push_back(nombre);
		
		// Validacion de la edad
		int edad;
		do {
			cout << "Edad (1-100): ";
			if (!(cin >> edad)) {
				cout << "Error: Debe ingresar un numero valido.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			cin.ignore(10000, '\n');  // Limpia el buffer despues de ingresar un numero
			
			if (edad < 1 || edad > 100) {
				cout << "Error: La edad debe estar entre 1 y 100 anios.\n";
			}
		} while (edad < 1 || edad > 100);
		edadesClientes.push_back(edad);
		
		// Validacion del genero
		int genero;
		do {
			cout << "Genero:\n";
			cout << "1. Masculino\n";
			cout << "2. Femenino\n";
			cout << "Opcion (1-2): ";
			if (!(cin >> genero)) {
				cout << "Error: Opcion invalida.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			cin.ignore(10000, '\n');  // Limpia el buffer
			
			if (genero < 1 || genero > 2) {
				cout << "Error: Ingrese 1 o 2.\n";
			}
		} while (genero < 1 || genero > 2);
		generosClientes.push_back(genero);
		
		// Validacion del tipo de cliente
		int tipo;
		do {
			cout << "Tipo cliente:\n";
			cout << "1. Mayorista\n";
			cout << "2. Empresa\n";
			cout << "3. Detalle\n";
			cout << "Opcion (1-3): ";
			if (!(cin >> tipo)) {
				cout << "Error: Opcion invalida.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			cin.ignore(10000, '\n');  // Limpia el buffer
			
			if (tipo < 1 || tipo > 3) {
				cout << "Error: Ingrese 1, 2 o 3.\n";
			}
		} while (tipo < 1 || tipo > 3);
		tiposClientes.push_back(tipo);
		
		// Validacion del dia de compra
		int dia;
		do {
			limpiarPantalla();
			cout << "*********************************\n";
			cout << "*   SELECCIONE EL DIA DE COMPRA  *\n";
			cout << "*********************************\n";
			cout << "1. Lunes\n";
			cout << "2. Martes\n";
			cout << "3. Miercoles\n";
			cout << "4. Jueves\n";
			cout << "5. Viernes\n";
			cout << "6. Sabado\n";
			cout << "7. Domingo\n";
			cout << "*********************************\n";
			cout << "Ingrese el numero del dia (1-7): ";
			if (!(cin >> dia)) {
				cout << "Error: Dia invalido.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			cin.ignore(10000, '\n');  // Limpia el buffer
			
			if (dia < 1 || dia > 7) {
				cout << "Error: Ingrese un numero del 1 al 7.\n";
				esperarEnter();
			}
		} while (dia < 1 || dia > 7);
		diasRegistro.push_back(dia);
		
		cout << "\nCliente registrado exitosamente!\n";
		cout << "Desea agregar otro cliente?\n";
		cout << "1. Si\n";
		cout << "2. No\n";
		
		// Validacion de la opcion de continuar
		do {
			cout << "Opcion: ";
			if (!(cin >> otro)) {
				cout << "Error: Opcion invalida.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			cin.ignore(10000, '\n');  // Limpia el buffer
			
			if (otro != 1 && otro != 2) {
				cout << "Error: Ingrese 1 o 2.\n";
			}
		} while (otro != 1 && otro != 2);
		
	} while (otro == 1);
}

// Muestra la lista de clientes registrados
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
			cout << "Edad: " << edadesClientes[i] << endl;
			cout << "Genero: ";
			if(generosClientes[i] == 1) {
				cout << "Masculino";
			} else {
				cout << "Femenino";
			}
			cout << endl << "Tipo: ";
			if(tiposClientes[i] == 1) {
				cout << "Mayorista";
			} else if(tiposClientes[i] == 2) {
				cout << "Empresa";
			} else {
				cout << "Detalle";
			}
			cout << "\nDia registro: ";
			if(diasRegistro[i] == 1) {
				cout << "Lunes";
			} else if(diasRegistro[i] == 2) {
				cout << "Martes";
			} else if(diasRegistro[i] == 3) {
				cout << "Miercoles";
			} else if(diasRegistro[i] == 4) {
				cout << "Jueves";
			} else if(diasRegistro[i] == 5) {
				cout << "Viernes";
			} else if(diasRegistro[i] == 6) {
				cout << "Sabado";
			} else {
				cout << "Domingo";
			}
			cout << "\n---------------------------\n";
		}
	}
	esperarEnter();
}

// Busca un cliente por su codigo
void buscarClientePorCodigo() {
	limpiarPantalla();
	
	if(codigosClientes.empty()) {
		cout << "*********************************\n";
		cout << "*      BUSQUEDA DE CLIENTES     *\n";
		cout << "*********************************\n";
		cout << "No hay clientes registrados para buscar.\n";
		esperarEnter();
		return;
	}
	
	cout << "*********************************\n";
	cout << "*      BUSQUEDA DE CLIENTES     *\n";
	cout << "*********************************\n";
	
	string codigo;
	cout << "Ingrese codigo del cliente ( Ejemplo: cli-1  o CLI-1): ";
	cin >> codigo;
	
	// Convierte la entrada a mayusculas para comparacion insensible a mayusculas/minusculas
	for(char &c : codigo) {
		c = toupper(c);
	}
	
	bool encontrado = false;
	for(size_t i = 0; i < codigosClientes.size(); i++) {
		string codigoAlmacenado = codigosClientes[i];
		// Convierte el codigo almacenado a mayusculas para comparacion
		for(char &c : codigoAlmacenado) {
			c = toupper(c);
		}
		
		if(codigoAlmacenado == codigo) {
			encontrado = true;
			cout << "\nCLIENTE ENCONTRADO:\n";
			cout << "Codigo: " << codigosClientes[i] << endl;
			cout << "Nombre: " << nombresClientes[i] << endl;
			cout << "Edad: " << edadesClientes[i] << endl;
			cout << "Genero: ";
			if(generosClientes[i] == 1) {
				cout << "Masculino";
			} else {
				cout << "Femenino";
			}
			cout << endl << "Tipo: ";
			if(tiposClientes[i] == 1) {
				cout << "Mayorista";
			} else if(tiposClientes[i] == 2) {
				cout << "Empresa";
			} else {
				cout << "Detalle";
			}
			cout << "\nDia registro: ";
			if(diasRegistro[i] == 1) {
				cout << "Lunes";
			} else if(diasRegistro[i] == 2) {
				cout << "Martes";
			} else if(diasRegistro[i] == 3) {
				cout << "Miercoles";
			} else if(diasRegistro[i] == 4) {
				cout << "Jueves";
			} else if(diasRegistro[i] == 5) {
				cout << "Viernes";
			} else if(diasRegistro[i] == 6) {
				cout << "Sabado";
			} else {
				cout << "Domingo";
			}
			cout << "\n---------------------------\n";
			break;
		}
	}
	
	if(!encontrado) {
		cout << "\nNo se encontro cliente con ese codigo.\n";
	}
	
	esperarEnter();
}

// Menu de gestion de clientes
void menuClientes() {
	int opcionClientes;
	do {
		limpiarPantalla();
		cout << "*********************************\n";
		cout << "*        MENU DE CLIENTES       *\n";
		cout << "*********************************\n";
		cout << "1. Ingresar cliente\n";
		cout << "2. Mostrar clientes\n";
		cout << "3. Buscar cliente por codigo\n";
		cout << "4. Regresar\n";
		cout << "*********************************\n";
		cout << "Opcion: ";
		cin >> opcionClientes;
		
		if(opcionClientes == 1) {
			ingresarCliente();
		} else if(opcionClientes == 2) {
			mostrarClientes();
		} else if(opcionClientes == 3) {
			buscarClientePorCodigo();
		}
		
	} while(opcionClientes != 4);
}

// ==================== MODULO DE FACTURACION ==================== //

// Muestra una factura detallada de la compra actual
void mostrarFactura() {
	limpiarPantalla();
	
	if(itemsComprados.empty()) {
		cout << "No hay productos en el carrito.\n";
		esperarEnter();
		return;
	}
	
	int tipoCliente = tiposClientes[clienteActual]; // Tipo de cliente actual
	int diaCompra = diasRegistro[clienteActual];    // Dia de compra del cliente
	int edad = edadesClientes[clienteActual];       // Edad del cliente
	int genero = generosClientes[clienteActual];    // Genero del cliente
	
	double descuentoBase = 0.0;                     // Descuento base segun tipo de cliente
	string descuentos = "";                         // Cadena para almacenar descripciones de descuentos
	
	int totalProductos = 0;                         // Total de productos comprados
	for(size_t i = 0; i < cantidadesCompradas.size(); i++) {
		totalProductos = totalProductos + cantidadesCompradas[i];
	}
	
	// Aplica descuento segun tipo de cliente
	if(tipoCliente == 1) {
		descuentoBase = subtotal * 0.10;
		descuentos = descuentos + "- Descuento Mayorista (10%)\n";
	} else if(tipoCliente == 2) {
		descuentoBase = subtotal * 0.15;
		descuentos = descuentos + "- Descuento Empresa (15%)\n";
	}
	
	double descuentoAdicional = 0.0;                // Descuentos adicionales
	
	// Verifica si se compra la "Cinta Metrica"
	bool tieneCinta = false;
	for(size_t i = 0; i < itemsComprados.size(); i++) {
		if(itemsComprados[i] == "Cinta Metrica") {
			tieneCinta = true;
			break;
		}
	}
	
	// Aplica descuento adicional si es cliente de detalle y compra Cinta Metrica los miercoles o viernes
	if(tipoCliente == 3 && (diaCompra == 3 || diaCompra == 5) && tieneCinta) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.02);
		descuentos = descuentos + "- Descuento 2% miercoles/viernes con Cinta Metrica\n";
	}
	
	// Verifica si se compra "Martillo" o "Destornillador"
	bool tieneMartilloDestornillador = false;
	for(size_t i = 0; i < itemsComprados.size(); i++) {
		if(itemsComprados[i] == "Martillo" || itemsComprados[i] == "Destornillador") {
			tieneMartilloDestornillador = true;
			break;
		}
	}
	
	// Aplica descuento adicional si es mayorista y compra Martillo/Destornillador los sabados o domingos
	if(tipoCliente == 1 && (diaCompra == 6 || diaCompra == 7) && tieneMartilloDestornillador) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.04);
		descuentos = descuentos + "- Descuento 4% sabados/domingos con Martillo/Destornillador\n";
	}
	
	// Aplica descuento adicional si es empresa y compra los lunes (solo con Visa)
	if(tipoCliente == 2 && diaCompra == 1) {
		descuentos = descuentos + "- Descuento 8% lunes para empresas (aplicable con Visa)\n";
	}
	
	// Aplica descuento adicional si es adulto mayor (edad > 60)
	if(edad > 60) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.06);
		descuentos = descuentos + "- Descuento 6% adulto mayor\n";
	}
	
	// Aplica descuento adicional si es mujer y compra los fines de semana (solo con pago en efectivo)
	if(genero == 2 && (diaCompra == 6 || diaCompra == 7)) {
		descuentos = descuentos + "- Descuento 6% mujeres fines de semana (aplicable con pago en efectivo)\n";
	}
	
	// Calcula impuesto y total
	double impuesto = (subtotal - descuentoBase - descuentoAdicional) * 0.15;
	double total = (subtotal - descuentoBase - descuentoAdicional) + impuesto;
	
	if(total < 0) {
		total = 0;
		cout << "Advertencia: El total no puede ser negativo!\n";
	}
	
	// Muestra la factura detallada
	cout << "*********************************************\n";
	cout << "*          FACTURA DETALLADA              *\n";
	cout << "*********************************************\n";
	cout << "* CLIENTE: " << left << setw(31) << nombresClientes[clienteActual] << "*\n";
	cout << "* CODIGO: " << left << setw(32) << codigosClientes[clienteActual] << "*\n";
	cout << "* TIPO:   " << left << setw(32);
	if(tipoCliente == 1) {
		cout << "Mayorista";
	} else if(tipoCliente == 2) {
		cout << "Empresa";
	} else {
		cout << "Detalle";
	}
	cout << "*\n";
	cout << "* DIA:    " << left << setw(32);
	if(diaCompra == 1) {
		cout << "Lunes";
	} else if(diaCompra == 2) {
		cout << "Martes";
	} else if(diaCompra == 3) {
		cout << "Miercoles";
	} else if(diaCompra == 4) {
		cout << "Jueves";
	} else if(diaCompra == 5) {
		cout << "Viernes";
	} else if(diaCompra == 6) {
		cout << "Sabado";
	} else {
		cout << "Domingo";
	}
	cout << "*\n";
	cout << "* EDAD:   " << left << setw(32) << to_string(edad) + " anios" << "*\n";
	cout << "* GENERO: " << left << setw(32);
	if(genero == 1) {
		cout << "Masculino";
	} else {
		cout << "Femenino";
	}
	cout << "*\n";
	cout << "*********************************************\n";
	
	// Muestra los productos comprados
	cout << "* PRODUCTO          CANT   PRECIO U.  SUBTOTAL *\n";
	cout << "*********************************************\n";
	
	for(size_t i = 0; i < itemsComprados.size(); i++) {
		cout << "* " << left << setw(16) << itemsComprados[i] 
			<< " " << right << setw(4) << cantidadesCompradas[i]
			<< "   L." << right << setw(6) << fixed << setprecision(2) 
			<< preciosItems[i]/cantidadesCompradas[i]
			<< "  L." << right << setw(8) << preciosItems[i] << " *\n";
	}
	
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
	
	if(!descuentos.empty()) {
		cout << "* DESCUENTOS APLICADOS:\n";
		cout << descuentos;
		cout << "*********************************************\n";
	}
	
	esperarEnter();
}

// Procesa el pago de la compra actual
void procesarPago() {
	double total = 0.0;
	int tipoCliente = tiposClientes[clienteActual]; // Tipo de cliente actual
	int diaCompra = diasRegistro[clienteActual];    // Dia de compra del cliente
	int edad = edadesClientes[clienteActual];       // Edad del cliente
	int genero = generosClientes[clienteActual];    // Genero del cliente
	
	double descuentoBase = 0.0;                     // Descuento base segun tipo de cliente
	
	// Aplica descuento seg�n tipo de cliente
	if(tipoCliente == 1) {
		descuentoBase = subtotal * 0.10;
	} else if(tipoCliente == 2) {
		descuentoBase = subtotal * 0.15;
	}
	
	double descuentoAdicional = 0.0;                // Descuentos adicionales
	
	// Verifica si se compra "Cinta Metrica"
	bool tieneCinta = false;
	for(size_t i = 0; i < itemsComprados.size(); i++) {
		if(itemsComprados[i] == "Cinta Metrica") {
			tieneCinta = true;
			break;
		}
	}
	
	// Verifica si se compra "Martillo" o "Destornillador"
	bool tieneMartilloDestornillador = false;
	for(size_t i = 0; i < itemsComprados.size(); i++) {
		if(itemsComprados[i] == "Martillo" || itemsComprados[i] == "Destornillador") {
			tieneMartilloDestornillador = true;
			break;
		}
	}
	
	// Aplica descuento adicional si es cliente de detalle y compra Cinta Metrica los miercoles o viernes
	if(tipoCliente == 3 && (diaCompra == 3 || diaCompra == 5) && tieneCinta) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.02);
	}
	
	// Aplica descuento adicional si es mayorista y compra Martillo/Destornillador los sabados o domingos
	if(tipoCliente == 1 && (diaCompra == 6 || diaCompra == 7) && tieneMartilloDestornillador) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.04);
	}
	
	bool aplicaDescuentoVisa = false;
	if(tipoCliente == 2 && diaCompra == 1) {
		aplicaDescuentoVisa = true;
	}
	
	// Aplica descuento adicional si es adulto mayor (edad > 60)
	if(edad > 60) {
		descuentoAdicional = descuentoAdicional + (subtotal * 0.06);
	}
	
	// Calcula el total a pagar
	total = (subtotal - descuentoBase - descuentoAdicional) + ((subtotal - descuentoBase - descuentoAdicional) * 0.15);
	
	int opcion;
	do {
		limpiarPantalla();
		cout << "=================================\n";
		cout << "      SELECCIONE FORMA DE PAGO    \n";
		cout << "=================================\n";
		cout << "1. Efectivo\n";
		cout << "2. Tarjeta de credito\n";
		cout << "3. Tarjeta de debito\n";
		cout << "=================================\n";
		cout << "Total a pagar: L." << fixed << setprecision(2) << total << "\n";
		cout << "Opcion (1-3): ";
		cin >> opcion;
	} while(opcion < 1 || opcion > 3);
	
	// Procesa el pago en efectivo
	if(opcion == 1) {
		double monto;
		do {
			cout << "\nIngrese monto recibido (L.): ";
			cin >> monto;
			
			if(monto < total) {
				cout << "Monto insuficiente. Faltan L." << (total - monto) << "\n";
			}
		} while(monto < total);
		
		// Aplica descuento adicional si es mujer y compr� los fines de semana con pago en efectivo
		if(genero == 2 && (diaCompra == 6 || diaCompra == 7)) {
			double descuentoEfectivo = subtotal * 0.06;
			total = total - descuentoEfectivo;
			cout << "\nSe aplico descuento adicional del 6% por pago en efectivo los fines de semana (mujeres)\n";
			cout << "Nuevo total: L." << fixed << setprecision(2) << total << "\n";
		}
		
		metodosPago.push_back(1);                   // Registra el metodo de pago como efectivo
		detallesTarjetas.push_back("Efectivo");      // Registra el detalle como "Efectivo"
		montosPagados.push_back(total);              // Registra el monto pagado
		
		// Muestra el comprobante de pago
		cout << "\n=================================\n";
		cout << "       COMPROBANTE DE PAGO     \n";
		cout << "---------------------------------\n";
		cout << "Cliente: " << nombresClientes[clienteActual] << "\n";
		cout << "Metodo:  Efectivo\n";
		cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
		cout << "Recibido:L." << fixed << setprecision(2) << monto << "\n";
		cout << "Cambio:  L." << fixed << setprecision(2) << (monto - total) << "\n";
		cout << "=================================\n";
	}
	// Procesa el pago con tarjeta de credito
	else if(opcion == 2) {
		int tipoTarjeta;
		int anioTarjeta;
		do {
			cout << "\nTipo de tarjeta:\n";
			cout << "1. Visa\n";
			cout << "2. Mastercard\n";
			cout << "Opcion (1-2): ";
			cin >> tipoTarjeta;
		} while(tipoTarjeta < 1 || tipoTarjeta > 2);
		
		do {
			cout << "Anio de expiracion (YYYY): ";
			cin >> anioTarjeta;
			
			if(anioTarjeta < 2025) {
				cout << "Error: Tarjeta no aceptada (debe ser del anio 2025 o superior)\n";
			}
		} while(anioTarjeta < 2025);
		
		// Simula un rechazo aleatorio de la tarjeta (10% de probabilidad)
		if((rand() % 10) == 0) {
			cout << "Error: La tarjeta ha sido bloqueada o rechazada.\n";
			esperarEnter();
			return;
		}
		
		// Aplica descuento adicional si es empresa y compra los lunes con Visa
		if(tipoCliente == 2 && diaCompra == 1 && tipoTarjeta == 1) {
			double descuentoVisa = subtotal * 0.08;
			total = total - descuentoVisa;
			cout << "\nSe aplico descuento adicional del 8% por pago con Visa los lunes (empresas)\n";
			cout << "Nuevo total: L." << fixed << setprecision(2) << total << "\n";
		}
		
		metodosPago.push_back(2);                   // Registra el metodo de pago como tarjeta de credito
		if(tipoTarjeta == 1) {
			detallesTarjetas.push_back("Visa");     // Registra el detalle como "Visa"
		} else {
			detallesTarjetas.push_back("Mastercard"); // Registra el detalle como "Mastercard"
		}
		montosPagados.push_back(total);             // Registra el monto pagado
		
		// Muestra el comprobante de pago
		cout << "\n=================================\n";
		cout << "       COMPROBANTE DE PAGO     \n";
		cout << "---------------------------------\n";
		cout << "Cliente: " << nombresClientes[clienteActual] << "\n";
		cout << "Metodo:  Tarjeta ";
		if(tipoTarjeta == 1) {
			cout << "Visa";
		} else {
			cout << "Mastercard";
		}
		cout << "\n";
		cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
		cout << "=================================\n";
	}
	// Procesa el pago con tarjeta de debito
	else if(opcion == 3) {
		// Solo clientes mayoristas pueden pagar con tarjeta de debito
		if(tipoCliente != 1) {
			cout << "\nError: Solo clientes mayoristas pueden pagar con debito\n";
			esperarEnter();
			return;
		}
		
		metodosPago.push_back(3);                   // Registra el metodo de pago como tarjeta de debito
		detallesTarjetas.push_back("Debito");       // Registra el detalle como "Debito"
		montosPagados.push_back(total);             // Registra el monto pagado
		
		// Muestra el comprobante de pago
		cout << "\n=================================\n";
		cout << "       COMPROBANTE DE PAGO     \n";
		cout << "---------------------------------\n";
		cout << "Cliente: " << nombresClientes[clienteActual] << "\n";
		cout << "Metodo:  Tarjeta debito\n";
		cout << "Total:   L." << fixed << setprecision(2) << total << "\n";
		cout << "=================================\n";
	}
	
	// Registra la compra en el historial si hay un cliente seleccionado
	if(clienteActual != -1) {
		historialCompras.push_back(itemsComprados);
	}
	
	// Limpia los vectores de la compra actual
	itemsComprados.clear();
	cantidadesCompradas.clear();
	preciosItems.clear();
	subtotal = 0;
	clienteActual = -1;
	
	esperarEnter();
}

// ==================== MODULO DE INVENTARIO ==================== //

// Permite seleccionar un cliente para realizar una compra
void seleccionarCliente() {
	limpiarPantalla();
	
	if(codigosClientes.empty()) {
		cout << "No hay clientes registrados. Registre clientes primero.\n";
		esperarEnter();
		return;
	}
	
	cout << "*********************************************\n";
	cout << "*        SELECCIONE UN CLIENTE             *\n";
	cout << "*********************************************\n";
	for(size_t i = 0; i < codigosClientes.size(); i++) {
		cout << i+1 << ". " << nombresClientes[i] 
			<< " (" << codigosClientes[i] << ") - ";
		if(tiposClientes[i] == 1) {
			cout << "Mayorista";
		} else if(tiposClientes[i] == 2) {
			cout << "Empresa";
		} else {
			cout << "Detalle";
		}
		cout << "\n";
	}
	cout << "*********************************************\n";
	
	int seleccion;
	do {
		cout << "Seleccione el cliente (1-" << codigosClientes.size() << "): ";
		cin >> seleccion;
	} while(seleccion < 1 || seleccion > (int)codigosClientes.size());
	
	clienteActual = seleccion - 1; // Establece el cliente actual
	cout << "Cliente seleccionado: " << nombresClientes[clienteActual] << endl;
	esperarEnter();
}

// Permite comprar productos y actualizar el inventario
void comprarProducto() {
	limpiarPantalla();
	
	if(clienteActual == -1) {
		cout << "Debe seleccionar un cliente primero.\n";
		esperarEnter();
		return;
	}
	
	// Muestra el inventario disponible
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
	
	int productoElegido;
	do {
		cout << "Seleccione producto (1-" << productos.size() << "): ";
		cin >> productoElegido;
	} while(productoElegido < 1 || productoElegido > (int)productos.size());
	
	int indice = productoElegido - 1;
	cout << "Producto seleccionado: " << productos[indice] << endl;
	cout << "Precio unitario: L." << precios[indice] << endl;
	cout << "Stock disponible: " << stock[indice] << endl;
	
	int cantidad;
	do {
		cout << "Ingrese cantidad a comprar: ";
		cin >> cantidad;
		
		if(cantidad <= 0) {
			cout << "La cantidad debe ser mayor a 0!\n";
		} else if(cantidad > stock[indice]) {
			cout << "No hay suficiente stock!\n";
		}
	} while(cantidad <= 0 || cantidad > stock[indice]);
	
	// Calcula el total de productos en el carrito
	int totalProductos = cantidad;
	for(size_t i = 0; i < cantidadesCompradas.size(); i++) {
		totalProductos = totalProductos + cantidadesCompradas[i];
	}
	
	int tipoCliente = tiposClientes[clienteActual]; // Tipo de cliente actual
	bool error = false;
	
	// Valida restricciones segun el tipo de cliente
	if(tipoCliente == 1 && (totalProductos < 6 || totalProductos > 12)) {
		cout << "Error: Mayorista debe comprar entre 6-12 productos (actual: " << totalProductos << ")\n";
		error = true;
	} 
	else if(tipoCliente == 2 && totalProductos < 13) {
		cout << "Error: Empresa debe comprar minimo 13 productos (actual: " << totalProductos << ")\n";
		error = true;
	}
	
	if(error) {
		esperarEnter();
		return;
	}
	
	// Actualiza el stock y registra la compra
	stock[indice] = stock[indice] - cantidad;
	itemsComprados.push_back(productos[indice]);
	cantidadesCompradas.push_back(cantidad);
	double subtotalItem = precios[indice] * cantidad;
	preciosItems.push_back(subtotalItem);
	subtotal = subtotal + subtotalItem;
	
	cout << "\nCompra realizada con exito!\n";
	esperarEnter();
}

// ==================== MODULO DE REPORTES ==================== //

// Muestra un reporte de clientes por producto comprado
void mostrarReporteProductos() {
	limpiarPantalla();
	cout << "*********************************************\n";
	cout << "*    CLIENTES POR PRODUCTO COMPRADO        *\n";
	cout << "*********************************************\n";
	
	if(historialCompras.empty()) {
		cout << "No hay compras registradas.\n";
		esperarEnter();
		return;
	}
	
	// Itera sobre cada producto y muestra los clientes que lo compraron
	for(int i = 0; i < productos.size(); i++) {
		cout << "Producto: " << productos[i] << "\n";
		cout << "Clientes que lo compraron:\n";
		
		bool encontrado = false;
		for(size_t j = 0; j < historialCompras.size(); j++) {
			for(size_t k = 0; k < historialCompras[j].size(); k++) {
				if(historialCompras[j][k] == productos[i]) {
					cout << "- " << nombresClientes[j] << " (" << codigosClientes[j] << ")\n";
					encontrado = true;
					break;
				}
			}
		}
		
		if(!encontrado) {
			cout << "Ningun cliente ha comprado este producto.\n";
		}
		cout << "---------------------------------------------\n";
	}
	
	esperarEnter();
}

// Muestra un reporte de clientes que pagaron en efectivo
void mostrarReporteEfectivo() {
	limpiarPantalla();
	cout << "*********************************************\n";
	cout << "*    CLIENTES QUE PAGARON EN EFECTIVO      *\n";
	cout << "*********************************************\n";
	
	if(metodosPago.empty()) {
		cout << "No hay pagos registrados.\n";
		esperarEnter();
		return;
	}
	
	bool encontrado = false;
	// Itera sobre los metodos de pago y muestra los clientes que pagaron en efectivo
	for(size_t i = 0; i < metodosPago.size(); i++) {
		if(metodosPago[i] == 1) {
			cout << "- " << nombresClientes[i] << " (" << codigosClientes[i] << ")";
			cout << " - Monto: L." << fixed << setprecision(2) << montosPagados[i] << "\n";
			encontrado = true;
		}
	}
	
	if(!encontrado) {
		cout << "Ningun cliente ha pagado en efectivo.\n";
	}
	
	esperarEnter();
}

// ==================== MENU PRINCIPAL ==================== //

int main() {
	srand(time(0)); // Inicializa la semilla para numeros aleatorios
	int opcion;
	
	do {
		limpiarPantalla();
		cout << "*******************************************\n";
		cout << "*      FERRETERIA CONSTRU-PUMA           *\n";
		cout << "*           MENU PRINCIPAL               *\n";
		cout << "*******************************************\n";
		cout << "1. Clientes\n";
		cout << "2. Comprar productos\n";
		cout << "3. Facturacion\n";
		cout << "4. Reportes\n";
		cout << "0. Salir\n";
		cout << "*******************************************\n";
		cout << "Opcion: ";
		cin >> opcion;
		
		if(opcion == 1) {
			menuClientes(); // Muestra el menu de clientes
		}
		else if(opcion == 2) {
			if(codigosClientes.empty()) {
				cout << "Debe registrar clientes primero.\n";
				esperarEnter();
				continue;
			}
			
			if(clienteActual == -1) {
				seleccionarCliente(); // Permite seleccionar un cliente
				if(clienteActual == -1) {
					continue;
				}
			}
			
			comprarProducto(); // Permite comprar productos
		}
		else if(opcion == 3) {
			if(codigosClientes.empty()) {
				cout << "Debe registrar clientes primero.\n";
				esperarEnter();
				continue;
			}
			
			if(clienteActual == -1) {
				cout << "Debe seleccionar un cliente primero.\n";
				esperarEnter();
				continue;
			}
			
			if(itemsComprados.empty()) {
				cout << "No hay productos en el carrito.\n";
				esperarEnter();
				continue;
			}
			
			mostrarFactura(); // Muestra la factura
			
			int opcionPago;
			cout << "Desea procesar el pago ahora?\n";
			cout << "1. Si\n";
			cout << "2. No\n";
			cout << "Opcion: ";
			cin >> opcionPago;
			
			if(opcionPago == 1) {
				procesarPago(); // Procesa el pago
			}
		}
		else if(opcion == 4) {
			int opcionReportes;
			do {
				limpiarPantalla();
				cout << "*********************************************\n";
				cout << "*            MENU DE REPORTES              *\n";
				cout << "*********************************************\n";
				cout << "1. Clientes por producto comprado\n";
				cout << "2. Clientes que pagaron en efectivo\n";
				cout << "3. Regresar\n";
				cout << "*********************************************\n";
				cout << "Opcion: ";
				cin >> opcionReportes;
				
				if(opcionReportes == 1) {
					mostrarReporteProductos(); // Muestra reporte de productos
				} else if(opcionReportes == 2) {
					mostrarReporteEfectivo(); // Muestra reporte de pagos en efectivo
				}
				
			} while(opcionReportes != 3);
		}
		
	} while(opcion != 0);
	
	cout << "Saliendo del sistema... Muchas gracias por visitarnos. :)\n";
	return 0;
}
