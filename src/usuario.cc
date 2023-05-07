#include "usuario.h"
#include "baseDatos.h"

// Implementación del constructor de la clase Usuarios
Usuarios::Usuarios(const std::string& id, const std::string& passwd) {
  id_ = id;
  passwd_ = passwd;
}

// Implementación del método DimeUnNombreDeCerradura cuya funcionalidad es asignar un ID/Nombre a una cerradura.
std::string Usuarios::DimeUnNombreDeCerradura() const {
  std::cout << "Tiene que escribir Cerr seguido de un número.\n"; 
  std::cout << "Nº de cerradura: ";
  std::string numCerradura = "";
  std::regex expresion("^Cerr\\d+");
  while (getline(std::cin, numCerradura)) {
    if (!std::regex_match(numCerradura, expresion)) {
      /// Volver a solicitar una entrada
      std::cout << "Entrada no válida. Inténtalo de nuevo.\n";
      std::cout << "Nº de cerradura: ";
    } else break; 
  }
  return numCerradura;
}

/* 
Implementación del método AbrirPuerta.
   Parámetros: const std::string& numCerradura (nombre de la cerradura), const std::string& nombreFichero (fichero de entrada).
   Cuya funcionalidad es comprobar si es posible abrir una puerta o no, en caso de éxito se procederá a abrir la misma.
*/
bool Usuarios::AbrirPuerta(const std::string& numCerradura, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "";
  bool abierta = false;
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == this->get_id()) {
      ss >> word; /// Me salto password
      while (ss >> word) {
        if (word == numCerradura) {
          abierta = true;
          break;
        }
      }
    }
    if (abierta == true) break;
  }
  return abierta;
}

/*
  Implementación del método Menu.
  Parámetro: const std::string& nombreFichero (fichero de entrada).
  Cuya funcionalidad es mostrar y seleccionar todas las funciones posibles dentro del programa. 
  Cada caso llamará a un método de la clase baseDatos.
*/
void Usuarios::Menu(const std::string& nombreFichero) const {
  std::string opcion = "";
  while (opcion != "0") {
    if (id_ == "Admin") {
      Datos baseDatos;
      std::cout << "\nOPCIONES ADMIN:\n";
      std::cout << "[0] Cerrar Sesión.\n";
      std::cout << "[1] Dar de Alta Usuario.\n";
      std::cout << "[2] Dar de Alta Cerradura en usuario existente.\n";
      std::cout << "[3] Dar de Baja Usuario.\n";
      std::cout << "[4] Dar de Baja Cerradura en usuario existente.\n";
      std::cout << "[5] Cambiar contraseña en usuario existente.\n";
      /// std::cout << "[X] Modificar Nombre de Usuario.\n";
      /// std::cout << "[X] Modificar Password de Usuario.\n";
      /// std::cout << "[X] Modificar Cerradura de Usuario.\n";
      
      std::cout << "\nIntroduzca opción: ";
      while (getline(std::cin, opcion) && ((opcion < "0") || (opcion > "5"))) {
        std::cout << "Solo se permiten las opciones en el rango [0-5].\n";
        std::cout << "Introduzca opción: ";
      }
      switch (stoi(opcion)) {
        case 1:
          baseDatos.DarAltaUsuario(nombreFichero);
          break;
        case 2:
          baseDatos.DarAltaCerraduraEnUsuarioExistente(nombreFichero);
          break;
        case 3:
          baseDatos.DarBajaUsuario(nombreFichero);
          break;
        case 4:
          baseDatos.DarBajaCerraduraEnUsuarioExistente(nombreFichero);
          break;
        case 5:
          baseDatos.CambiarPasswdUsuarioExistente(nombreFichero);
          break;          
        default: /// 0
          std::cout << "\nSalir del sistema.\n";
          break;                                  
      }
    } else {
        std::cout << "\nOPCIONES CLIENTE:\n";
        std::cout << "[0] Cerrar Sesión.\n";
        std::cout << "[1] Abrir Cerradura.\n";
        std::cout << "\nIntroduzca opción: ";      
        while (getline(std::cin, opcion) && ((opcion < "0") || (opcion > "1"))) {
          std::cout << "Solo se permiten las opciones en el rango [0-1].\n";
          std::cout << "Introduzca opción: ";
        }
        std::string cerradura = "";
        switch (stoi(opcion)) {
          case 1:
            std::cout << "\nAbrir Cerradura.\n\n";
            std::cout << "Que cerradura quiere abrir.\n";
            cerradura = DimeUnNombreDeCerradura();
            if (AbrirPuerta(cerradura, nombreFichero)) {
              std::cout << "\nAcceso permitido. (Luz verde y abrir puerta)\n";
            } else std::cout << "\nAcceso denegado (Luz roja y pitido de alarma).\n";            
            break;
          default: /// 0
            std::cout << "\nSalir del sistema.\n";
            break;
        }
    }
  }
}
