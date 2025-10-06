#include <iostream>
#include <string>

int* idPaquete = nullptr;
double* peso = nullptr;
std::string* destino = nullptr;
int* prioridad = nullptr;
char* estado = nullptr;

int capacidad = 50;
int frente = 0;
int final_idx = -1;
int contador = 0;

void inicializarSistema();
void agregarPaquete();
void despacharPaquete();
void inspeccionarFrente();
void reportePorDestino();
void liberarMemoria();
void duplicarCapacidad();
std::string obtenerPrioridadTexto(int p);
void mostrarMenu();

int main() {
    inicializarSistema();
    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;

        while (std::cin.fail()) {
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            mostrarMenu();
            std::cin >> opcion;
        }

        switch (opcion) {
            case 1:
                agregarPaquete();
                break;
            case 2:
                despacharPaquete();
                break;
            case 3:
                inspeccionarFrente();
                break;
            case 4:
                reportePorDestino();
                break;
            case 5:
                liberarMemoria();
                std::cout << "Sistema cerrado. ¡Memoria libre!\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}

void inicializarSistema() {
    std::cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes...\n";
    idPaquete = new int[capacidad];
    peso = new double[capacidad];
    destino = new std::string[capacidad];
    prioridad = new int[capacidad];
    estado = new char[capacidad];
}

void mostrarMenu() {
    std::cout << "\n--- Sistema de Despacho Logístico MegaEnvío (Modo Punteros) ---\n";
    std::cout << "Capacidad total: " << capacidad << ". Paquetes en cola: " << contador << ".\n\n";
    std::cout << "Seleccione una operación:\n";
    std::cout << "1. Agregar Paquete (Encolar)\n";
    std::cout << "2. Despachar Paquete (Desencolar)\n";
    std::cout << "3. Inspeccionar Frente de Cola\n";
    std::cout << "4. Reporte por Destino\n";
    std::cout << "5. Salir (Liberar Memoria)\n";
    std::cout << "\nOpción seleccionada: ";
}

void duplicarCapacidad() {
    int nuevaCapacidad = capacidad * 2;
    std::cout << "\nCapacidad insuficiente. Duplicando a " << nuevaCapacidad << "...\n";
    
    int* nuevoIdPaquete = new int[nuevaCapacidad];
    double* nuevoPeso = new double[nuevaCapacidad];
    std::string* nuevoDestino = new std::string[nuevaCapacidad];
    int* nuevaPrioridad = new int[nuevaCapacidad];
    char* nuevoEstado = new char[nuevaCapacidad];

    for (int i = 0; i < capacidad; ++i) {
        nuevoIdPaquete[i] = idPaquete[i];
        nuevoPeso[i] = peso[i];
        nuevoDestino[i] = destino[i];
        nuevoPrioridad[i] = prioridad[i];
        nuevoEstado[i] = estado[i];
    }

    delete[] idPaquete;
    delete[] peso;
    delete[] destino;
    delete[] prioridad;
    delete[] estado;

    idPaquete = nuevoIdPaquete;
    peso = nuevoPeso;
    destino = nuevoDestino;
    prioridad = nuevaPrioridad;
    estado = nuevoEstado;

    capacidad = nuevaCapacidad;
}

void agregarPaquete() {
    if (final_idx + 1 >= capacidad) {
        duplicarCapacidad();
    }

    final_idx++;

    std::cout << "Ingrese ID: ";
    std::cin >> idPaquete[final_idx];
    std::cout << "Ingrese Peso: ";
    std::cin >> peso[final_idx];
    std::cout << "Ingrese Destino: ";
    std::cin.ignore();
    std::getline(std::cin, destino[final_idx]);
    std::cout << "Ingrese Prioridad (1-Alta, 2-Media, 3-Baja): ";
    std::cin >> prioridad[final_idx];
    estado[final_idx] = 'E';

    contador++;
    std::cout << "Paquete " << idPaquete[final_idx] << " encolado. Espacios utilizados en memoria: " << final_idx + 1 << "/" << capacidad << ".\n";
}

void despacharPaquete() {
    if (contador == 0) {
        std::cout << "No hay paquetes en la cola para despachar.\n";
        return;
    }

    std::cout << "Despachando paquete...\n";
    estado[frente] = 'D';
    std::cout << "Paquete " << idPaquete[frente] << " despachado con éxito. Estado: 'D'.\n";

    frente++;
    contador--;
}

void inspeccionarFrente() {
    if (contador == 0) {
        std::cout << "La cola está vacía.\n";
        return;
    }

    std::cout << "Frente de la cola:\n";
    std::cout << "  ID: " << idPaquete[frente]
              << " | Peso: " << peso[frente] << " kg"
              << " | Destino: " << destino[frente]
              << " | Prioridad: " << obtenerPrioridadTexto(prioridad[frente]) << "\n";
}

void reportePorDestino() {
    if (contador == 0) {
        std::cout << "La cola está vacía. No se pueden generar reportes.\n";
        return;
    }
    
    std::string dest;
    std::cout << "Ingrese el destino para el reporte: ";
    std::cin.ignore();
    std::getline(std::cin, dest);

    int paquetesEnDestino = 0;
    double pesoTotal = 0.0;

    for (int i = frente; i <= final_idx; ++i) {
        if (estado[i] == 'E' && destino[i] == dest) {
            paquetesEnDestino++;
            pesoTotal += peso[i];
        }
    }

    std::cout << "Reporte para destino '" << dest << "':\n";
    if (paquetesEnDestino > 0) {
        double pesoPromedio = pesoTotal / paquetesEnDestino;
        std::cout << "  Paquetes En Cola: " << paquetesEnDestino << "\n";
        std::cout << "  Peso Promedio: " << pesoPromedio << " kg\n";
    } else {
        std::cout << "  No se encontraron paquetes en cola para este destino.\n";
    }
}

void liberarMemoria() {
    std::cout << "Liberando " << capacidad << " bloques de memoria asignada...\n";
    delete[] idPaquete;
    delete[] peso;
    delete[] destino;
    delete[] prioridad;
    delete[] estado;
    
    idPaquete = nullptr;
    peso = nullptr;
    destino = nullptr;
    prioridad = nullptr;
    estado = nullptr;
}

std::string obtenerPrioridadTexto(int p) {
    switch (p) {
        case 1: return "Alta";
        case 2: return "Media";
        case 3: return "Baja";
        default: return "Desconocida";
    }
}
