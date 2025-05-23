#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>

using namespace std;

// Definición de la clase Avion
class Avion
{
private:
    // Atributos privados del avión
    string matricula;
    string modelo;
    string fabricante;
    int capacidad;

public:
    // Constructor que inicializa los atributos del avión
    Avion(string mat, string mod, string fab, int cap)
        : matricula(mat), modelo(mod), fabricante(fab), capacidad(cap) {}

    // Métodos getter para obtener los atributos del avión
    string getMatricula() const { return matricula; }
    string getModelo() const { return modelo; }
    string getFabricante() const { return fabricante; }
    int getCapacidad() const { return capacidad; }

    // Método para mostrar la información del avión
    void mostrar() const
    {
        cout << "Avion: " << modelo << " (" << matricula << ")\n";
        cout << "Fabricante: " << fabricante << "\n";
        cout << "Capacidad: " << capacidad << " asientos\n";
    }
};

// Definición de la clase Pasajero
class Pasajero
{
private:
    string nombre;

public:
    Pasajero(string nom)
        : nombre(nom) {};

    string getNombre() const { return nombre; }
};

// Definición de la clase Vuelo
class Vuelo
{
private:
    // Información general del vuelo
    string terminal;
    string numero;
    string ciudad;
    string pais;
    string tipo; // nacional o internacional
    float km;
    Avion avion; // Avión asignado al vuelo
    // Constantes para el cálculo del precio (deben definirse fuera de la clase)
    static const float PRECIO_BASE;
    static const float TARIFA_KM;

    // Vector de punteros inteligentes para almacenar los pasajeros
    vector<unique_ptr<Pasajero>> asientos_; // Arreglo asientos para agregar pasajeros
    // Contador de pasajeros registrados
    size_t pasajerosRegistrados_ = 0;

public:
    // Constructor del vuelo
    Vuelo(string term, string num, string ciu, string pa, string tip, float dist, Avion av, size_t cantidadAsientos)
        : terminal(term), numero(num), ciudad(ciu), pais(pa), tipo(tip), km(dist), avion(av)
    {
        asientos_.resize(cantidadAsientos); // Reserva espacio para los asientos
    }

    // Métodos getter
    string getNumero() const { return numero; }
    string getDestino() const { return ciudad + ", " + pais; }
    float getDistancia() const { return km; }
    int getPasajerosRegistrados() const { return pasajerosRegistrados_; }

    // Calcula el precio base del boleto según el tipo de vuelo
    float calcularPrecio() const
    {
        float total = PRECIO_BASE;
        if (tipo == "nacional")
            total += TARIFA_KM * km * 0.20;
        else
            total += TARIFA_KM * km * 0.10;
        return total;
    };
    // Calcula las ganancias totales estimadas del vuelo
    float calcularTotalGanancias() const
    {
        float precioBase = calcularPrecio();

        size_t primeraClase = pasajerosRegistrados_ * 0.15;
        size_t ejecutiva = pasajerosRegistrados_ * 0.25;
        size_t economica = pasajerosRegistrados_ - primeraClase - ejecutiva;

        float ingresoTotal = (primeraClase * precioBase * 1.5) +
                             (ejecutiva * precioBase * 1.25) +
                             (economica * precioBase);

        return ingresoTotal;
    };
    // Muestra el estado de ocupación de cada asiento
    void mostrarDisponibilidad() const
    {
        cout << "\n========================================\n";
        cout << " DISPONIBILIDAD DEL VUELO " << numero << "\n";
        cout << "========================================\n";
        cout << left << setw(10) << "Asiento"
             << setw(20) << "Estado / Nombre del Pasajero\n";
        cout << "----------------------------------------\n";

        for (size_t i = 0; i < asientos_.size(); ++i)
        {
            cout << left << setw(10) << i;
            if (asientos_[i])
            {
                // Si el asiento está ocupado, muestra el nombre del pasajero
                cout << setw(20) << asientos_[i]->getNombre();
            }
            else
            {
                // Si el asiento está libre
                cout << setw(20) << "[libre]";
            }
            cout << "\n";
        }

        cout << "========================================\n";
    };

    // Asigna un pasajero a un asiento si está libre y dentro de los límites
    bool asignarPasajero(int numAsiento, unique_ptr<Pasajero> pasajero)
    {
        if (numAsiento < 0 || static_cast<size_t>(numAsiento) >= asientos_.size())
        {
            return false;
        }
        if (asientos_[numAsiento])
        {
            return false; // asiento ocupado
        }
        asientos_[numAsiento] = move(pasajero); // asigna el pasajero al asiento
        pasajerosRegistrados_++;
        return true;
    };

    // Muestra la información general del vuelo
    void mostrar() const
    {
        cout << "\n--- VUELO " << numero << " ---\n";
        cout << "Terminal: " << terminal << "\n";
        cout << "Destino: " << getDestino() << "\n";
        cout << "Tipo: " << tipo << "\n";
        cout << "Distancia: " << km << " km\n";
        cout << "Precio estimado: $" << fixed << setprecision(2) << calcularPrecio() << "\n";
        avion.mostrar();
        cout << "---------------------------\n";
    }
};

// Definicion constantes para calcular precio
const float Vuelo::PRECIO_BASE = 50.0;
const float Vuelo::TARIFA_KM = 0.25;

// Funcion para mostrar menu
void mostrarMenu()
{
    cout << "\n==== MENU PRINCIPAL UAPA AIRLINES ====\n";
    cout << "1. Nuevo avion\n";
    cout << "2. Nuevo vuelo\n";
    cout << "3. Nuevo pasajero\n";
    cout << "4. Ver vuelos\n";
    cout << "5. Precio de pasaje\n";
    cout << "6. Total Ganancias Venta Boletas\n";
    cout << "7. Salir\n";
    cout << "Elige una opcion: ";
}

// Funcion para registrar un nuevo Avion
void registrarAvion(vector<Avion> &aviones)
{
    string mat, mod, fab;
    int cap;

    cout << "\nRegistro de avion\n";
    cout << "Matricula: ";
    getline(cin, mat);
    cout << "Modelo: ";
    getline(cin, mod);
    cout << "Fabricante: ";
    getline(cin, fab);

    string input;
    while (true)
    {
        cout << "Capacidad: ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> cap && ss.eof())
        {
            break;
        }
        else
        {
            cout << "Por favor, introduce un numero valido \n";
        }
    }
    // Agrega el avion al arreglo de aviones
    aviones.push_back(Avion(mat, mod, fab, cap));
    cout << "Avion guardado correctamente.\n";
    cin.ignore();
}

// Funcion para regustrar nuevo Vuelo
void registrarVuelo(vector<Vuelo> &vuelos, const vector<Avion> &aviones)
{
    if (aviones.empty())
    {
        cout << "Primero debes registrar un avion.\n";
        return;
    }

    string term, num, ciu, pa, tip;
    float dist;
    int idx;

    cout << "\nRegistro de vuelo\n";
    cout << "Terminal: ";
    getline(cin, term);
    cout << "Numero de vuelo: ";
    getline(cin, num);
    cout << "Ciudad destino: ";
    getline(cin, ciu);
    cout << "Pais destino: ";
    getline(cin, pa);

    do
    {
        cout << "tipo de vuelo (nacional/internacional): ";
        getline(cin, tip);
    } while (tip != "nacional" && tip != "internacional");

    string input;
    while (true)
    {
        cout << "Distancia en km: ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >> dist && ss.eof())
        {
            break;
        }
        else
        {
            cout << "Por favor, introduce un numero valido \n";
        }
    }

    // Asignar avion al vuelo
    cout << "\nSelecciona un avion:\n";
    for (size_t i = 0; i < aviones.size(); ++i)
        cout << i + 1 << ". " << aviones[i].getModelo() << " (" << aviones[i].getMatricula() << ")\n";

    cout << "Opcion: ";
    cin >> idx;
    cin.ignore();

    if (idx < 1 || idx > aviones.size())
    {
        cout << "indice invalido.\n";
        return;
    }

    // Agrega el vuelo al arreglo de vuelos
    vuelos.push_back(Vuelo(term, num, ciu, pa, tip, dist, aviones[idx - 1], aviones[idx - 1].getCapacidad()));
    cout << "vuelo registrado.\n";
}

// Funcion para registrar un nuevo pasajero a un vuelo
void registrarPasajero(vector<Vuelo> &vuelos)
{
    if (vuelos.empty())
    {
        cout << "Primero debes registrar un vuelo\n";
        return;
    }

    string nombre;

    cout << "\nRegistro de pasajero\n";
    cout << "Nombre: ";
    getline(cin, nombre);

    // Crear nuevo pasajero dinámicamente
    auto pasajero = make_unique<Pasajero>(nombre);
    size_t indice;
    do
    {
        cout << "\nSelecciona un vuelo disponible:\n";
        for (size_t i = 0; i < vuelos.size(); ++i)
        {
            cout << i + 1 << ". " << vuelos[i].getNumero() << " (" << vuelos[i].getDestino() << ")\n";
        }

        cout << "Ingresa el numero del vuelo: ";
        cin >> indice;

        if (indice < 1 || indice > vuelos.size())
        {
            cout << "Indice invalido. Intenta nuevamente.\n";
        }
    } while (indice < 1 || indice > vuelos.size());

    // Crea instancia del vuelo seleccionado con el indice
    Vuelo &vueloSeleccionado = vuelos[indice - 1];
    vueloSeleccionado.mostrarDisponibilidad();

    int numAsiento;
    cout << "\nSeleccione numero de asiento: ";
    cin >> numAsiento;

    // Asigna el pasajero en un asiento del vuelo seleccionado
    if (vueloSeleccionado.asignarPasajero(numAsiento, move(pasajero)))
    {
        cout << "Pasajero registrado exitosamente en el asiento " << numAsiento << ".\n";
    }
    else
    {
        cout << "No se pudo asignar el asiento. Ya esta ocupado o fuera de rango.\n";
    }
};

// Funcion mostrar un listado de los aviones registrados
void mostrarVuelos(const vector<Vuelo> &vuelos)
{
    if (vuelos.empty())
    {
        cout << "no hay vuelos registrados.\n";
        return;
    }

    cout << "\nListado de vuelos:\n";
    for (const auto &vuelo : vuelos)
        vuelo.mostrar();
};

// Funcion para calcular precio estimado de la boleta aerea
void calcularPrecio(const vector<Vuelo> &vuelos)
{
    if (vuelos.empty())
    {
        cout << "no hay vuelos disponibles.\n";
        return;
    }

    cout << "\nSelecciona un vuelo:\n";
    for (size_t i = 0; i < vuelos.size(); ++i)
        cout << i + 1 << ". Vuelo " << vuelos[i].getNumero() << " a " << vuelos[i].getDestino() << "\n";

    int opcion;
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || opcion > vuelos.size())
    {
        cout << "seleccion invalida.\n";
        return;
    }

    // Calcula el precio con la boleta con la funcion calculaPrecio dentro de cada vuelo
    float precio = vuelos[opcion - 1].calcularPrecio();
    cout << "precio estimado del pasaje: $" << fixed << setprecision(2) << precio << "\n";
};

// Funcion para calculat el total de gananacias por venta de boletas del vuelo seleccioando
void calcularGananciaTotalBoletas(vector<Vuelo> &vuelos)
{
    if (vuelos.empty())
    {
        cout << "no hay vuelos disponibles.\n";
        return;
    }

    size_t indice;
    do
    {
        cout << "\nSelecciona un vuelo:\n";
        for (size_t i = 0; i < vuelos.size(); ++i)
        {
            cout << i + 1 << ". " << vuelos[i].getNumero() << " (" << vuelos[i].getDestino() << ")\n";
        }

        cout << "Ingresa el numero del vuelo: ";
        cin >> indice;

        if (indice < 1 || indice > vuelos.size())
        {
            cout << "Indice invalido. Intenta nuevamente.\n";
        }
    } while (indice < 1 || indice > vuelos.size());

    // Crea instancia del vuelo seleccionado
    Vuelo &vueloSeleccionado = vuelos[indice - 1];

    // Calcula los precios de las boletas y el total por la cantidad vendida o pasajeros registrados
    cout << "Boletas aeras vendidas del vuelo " << vueloSeleccionado.getNumero() << ": " << vueloSeleccionado.getPasajerosRegistrados() << "\n";
    float precio = vueloSeleccionado.calcularPrecio();
    cout << "Precio estimado de la boleta: $" << fixed << setprecision(2) << precio << "\n";
    cout << "Total ganancias estimadas por venta de boletas: $" << vueloSeleccionado.calcularTotalGanancias() << "\n";
};

// Funcion main presenta menu en bucle
int main()
{
    vector<Avion> aviones;
    vector<Vuelo> vuelos;
    int opcion;

    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            registrarAvion(aviones);
            break;
        case 2:
            registrarVuelo(vuelos, aviones);
            break;
        case 3:
            registrarPasajero(vuelos);
            break;
        case 4:
            mostrarVuelos(vuelos);
            break;
        case 5:
            calcularPrecio(vuelos);
            break;
        case 6:
            calcularGananciaTotalBoletas(vuelos);
            break;
        case 7:
            cout << "cerrando sistema...\n";
            break;
        default:
            cout << "opcion no valida.\n";
        }

    } while (opcion != 7);

    return 0;
}
