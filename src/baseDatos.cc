#include "baseDatos.h"

//Pregunta al usuario del programa su nombre de usuario y su contraseña para introducirlo en la base de datos
Usuarios Datos::IdentificacionUsuario() const {
    std::string id = "", passwd = "";
    id = DimeUnNombreDeUsuario();
    passwd = DimeUnPassword();
    std::cout << std::endl;
    Usuarios usuario(id, passwd);
    return usuario;
}

// Pregunta al usuario un nombre de usuario
std::string Datos::DimeUnNombreDeUsuario() const {
  std::string nombreUsuario = "";
  std::cout << "Introduzca un nombre de usuario.\n";
  std::cout << "Usuario: ";
  while ((getline(std::cin, nombreUsuario)) && (nombreUsuario == "USUARIOS")) {
    std::cout << "Usuario no permitido.\n";
    std::cout << "Usuario: ";
  }
  return nombreUsuario;
}

std::string Datos::DimeUnPassword() const {
  std::cout << "Introduzca una contraseña.\n";
  std::cout << "Contraseña: ";
  std::string passwd = "";
  termios oldt, newt; // Estructuras para almacenar la configuración de terminal actual y la nueva
  tcgetattr(STDIN_FILENO, &oldt); // Obtener la configuración actual de la terminal
  newt = oldt;
  newt.c_lflag &= ~ECHO; // Deshabilitar la impresión de caracteres en pantalla
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Establecer la nueva configuración de la terminal  
  int i;
  char c;
  bool error = false;
  do {
    if (error) {
      std::cout << "\nContraseña no permitida. Requisitos, 4 dígitos.\n";
      std::cout << "Contraseña: ";
    }
    error = false;
    i = 0;
    while (true) {
      c = getchar();  /// Lee el siguiente carácter sin mostrarlo en la consola
      if (c == '\n') break; /// Si se presiona la tecla Enter, salimos del bucle
      passwd += c;
      ++i;
      std::cout << "*";
    }
    //passwd += '\0';  // Agrega el carácter nulo final para indicar el final de la cadena
    if ((passwd.size() != 4) || (passwd.find_first_not_of("0123456789") != std::string::npos)) {
      error = true;
      passwd = "";
    }
  } while (error);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /// Restaurar la configuración original de la terminal
  return passwd;
}

bool Datos::ComprobarUsrYPwd(const Usuarios& usuario, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "", usr = "", pwd = "";
  bool usuarioYPasswdOK = false;
  while (getline(fichero, cadaLinea)) { // Recorremos las lineas del fichero
    std::stringstream ss(cadaLinea);
    std::string word;
    int contador = 0;
    while ((ss >> word) && (contador < 2)) { /// Extrae las 2 primeras palabras de cada linea (usuario y contraseña)
        if (contador == 0) usr = word;
        else pwd = word;
        contador++;
    }
    if ((usr == usuario.get_id()) && (pwd == usuario.get_passwd())) { // Comprobacion de existencia de usuario y contraseña
      usuarioYPasswdOK = true;
      break;
    }    
  }
  return usuarioYPasswdOK;
}

// Comprueba en la base de datos la existencia del usuario introducido
bool Datos::ComprobarUsuario(const std::string& nombreUsuario, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "", usr = "";
  bool usuarioOK = false;
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == nombreUsuario) {
      usuarioOK = true;
      break;
    }    
  }
  return usuarioOK;
}

bool Datos::ComprobarCerraduraEnSistema(const std::string& cerradura, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "";
  while (getline(fichero, cadaLinea)) {
    if (cerradura == cadaLinea) return true;
  }
  return false;
}

// Dar de alta a un usuario nuevo
void Datos::DarAltaUsuario(const std::string& nombreFichero1, const std::string& nombreFichero2) {
  std::cout << "\nDar de Alta Usuario.\n";
  bool yaExisteUsr;
  do {
    yaExisteUsr = false;
    Usuarios usuario = this->IdentificacionUsuario(); // Introducimos usuario en la base de datos
    std::vector<std::string> todasCerraduras;
    if (this->ComprobarUsuario(usuario.get_id(), nombreFichero1)) { // Comprobamos que exista el usuario
      std::cout << "Usuario existente.\n";
      yaExisteUsr = true;
      std::string opcion = "";
      do {
        std::cout << "Reintentar o Salir [R/S]: ";
      } while (getline(std::cin, opcion) && ((opcion != "R") && (opcion != "S")));
      if (opcion == "S") break; // Opción de salida seleccionada
    } else { // Opcion de reintentar seleccionada
        bool encuentroCerradura;
        std::string opcion, insertarCerradura;
        do {
          std::cout << "Que cerradura quiere abrir.\n";
          std::string cerradura = usuario.DimeUnNombreDeCerradura(); // Preguntamos la cerradura que se deseaa abrir
          if (this->ComprobarCerraduraEnSistema(cerradura, nombreFichero2)) {
            encuentroCerradura = false;
            for (int i = 0; i < todasCerraduras.size(); ++i) { // Buscamos si existe la cerradura introducida
              if (todasCerraduras[i] == cerradura) {
                encuentroCerradura = true;
                break;
              }
            }
            opcion = "", insertarCerradura = "";
            if (encuentroCerradura == false) { // No se encuentra la cerradura introducida
              todasCerraduras.push_back(cerradura); // añadimos la cerradura
              std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
              while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
                std::cout << "Tiene que responder [S/N].\n";
                std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
              }
              if (insertarCerradura == "N") break; // No añadimos más cerraduras
            } else {
                std::cout << "Cerradura existente en el usuario: " << usuario.get_id() << "\n"; // Ya existe la cerradura
                do {
                  std::cout << "Reintentar o Salir [R/S]: ";
                } while (getline(std::cin, opcion) && ((opcion != "R") && (opcion != "S")));
                if (opcion == "S") break;            
            }
          } else {
              std::cout << "Esa cerradura no se encuentra disponible en el sistema.\n";
              std::cout << "¿Desea añadir otra cerradura distinta? [S/N]: ";
              while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
                std::cout << "Tiene que responder [S/N].\n";
                std::cout << "¿Desea añadir otra cerradura distinta? [S/N]: ";
              }
              if ((insertarCerradura == "N") && (todasCerraduras.size() == 0)) {
                std::cout << "El alta de un usuario requiere añadir 1 cerradura mínimo.\n";
                insertarCerradura = "S";
              }   
          }
        } while ((encuentroCerradura == true) || (opcion == "R") || (insertarCerradura == "S"));
    }
    if (yaExisteUsr == false) {
      ActualizarAltaUsuarioFich(usuario, nombreFichero1, todasCerraduras); // Actualizamos la base de datos
    }
  } while (yaExisteUsr == true);
}

// Obtiene las cerraduras del usuario introducido
void Datos::CerradurasDeUsuarioExistente(const std::string& nombreUsuario, const std::string& nombreFichero, std::vector<std::string>& todasCerraduras) {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "";
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == nombreUsuario) {
      ss >> word;
      while (ss >> word) {
        todasCerraduras.push_back(word);
      }
      break;
    }
  }
}

// Dar de alta nuevas cerraduras en un usuario ya existente
void Datos::DarAltaCerraduraEnUsuarioExistente(const std::string& nombreFichero1, const std::string& nombreFichero2) {
  std::cout << "\nInsertar Cerradura en usuario existente.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario(); // Preguntamos el usuario que en el que quiere añadir una cerradura
  std::vector<std::string> cerradurasDeUsuario;
  while (usuario.get_id() == "Admin") { // El usuario "Admin" no es válido
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero1) == false) { // No existe el usuario
    std::cout << "Usuario inexistente.\n";
  } else {
      CerradurasDeUsuarioExistente(usuario.get_id(), nombreFichero1, cerradurasDeUsuario); // Obtenemos las cerraduras del usuario
      bool yaExisteCerradura;
      std::string insertarCerradura = "";
      do {    
        yaExisteCerradura = false;
        std::cout << "Que cerradura quiere abrir.\n";
        std::string cerradura = usuario.DimeUnNombreDeCerradura(); // Preguntamos por la cerradura que se quiere añadir
        if (this->ComprobarCerraduraEnSistema(cerradura, nombreFichero2)) {
          for (int i = 0; i < cerradurasDeUsuario.size(); ++i) {
            if (cerradura == cerradurasDeUsuario[i]) { // Ya estaba en el vector de cerraduras
              yaExisteCerradura = true;
              std::cout << "Esa cerradura ya podía ser abierta por: " << usuario.get_id() << std::endl << std::endl;
              break;
            }
          }
          if (yaExisteCerradura == false) { // No estaba añadida la cerradura
            cerradurasDeUsuario.push_back(cerradura); // Añadimos la cerradura
            std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
            while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
              std::cout << "Tiene que responder [S/N].\n";
              std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
            }
          }
        } else {
            std::cout << "Esa cerradura no se encuentra disponible en el sistema.\n";
            std::cout << "¿Desea añadir otra cerradura distinta? [S/N]: ";
            while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
              std::cout << "Tiene que responder [S/N].\n";
              std::cout << "¿Desea añadir otra cerradura distinta? [S/N]: ";
            }            
        }
      } while ((yaExisteCerradura == true) || (insertarCerradura == "S"));
      ActualizarCerraduraEnUsuarioExistente(usuario.get_id(), nombreFichero1, cerradurasDeUsuario); // Actualizamos la base de datos
      /// Metodo devuelve vector cerraduras de un usuario
  }
}

void Datos::AltaCerraduraEnSistema(const std::string& nombreFichero2) {
  std::cout << "\nAlta de cerradura en el sistema.\n";
  Usuarios usuario;
  std::string cerradura = "";
  cerradura = usuario.DimeUnNombreDeCerradura();
  if (ComprobarCerraduraEnSistema(cerradura, nombreFichero2)) {
    std::cout << "La cerradura " << cerradura << " ya estaba en el sistema.\n";
  } else {
      std::ofstream fichero(nombreFichero2, std::ios_base::app);
      fichero << std::endl << cerradura;
      fichero.close();
  }
}

void Datos::BajaCerraduraEnSistema(const std::string& nombreFichero1, const std::string& nombreFichero2) {
  std::cout << "\nBaja de cerradura en el sistema.\n";
  Usuarios usuario;
  std::string cerradura = "";
  cerradura = usuario.DimeUnNombreDeCerradura();
  if (ComprobarCerraduraEnSistema(cerradura, nombreFichero2)) {
    std::vector<std::string> lineasfich2, lineasfich1;
    std::string cadaLinea = "";
    std::ifstream fichero2Lectura(nombreFichero2);
    while (getline(fichero2Lectura, cadaLinea)) {
      if (cadaLinea != cerradura) lineasfich2.push_back(cadaLinea);
    }
    fichero2Lectura.close();
    std::ofstream fichero2Escritura(nombreFichero2);
    for (int i = 0; i < lineasfich2.size(); ++i) {
      fichero2Escritura << lineasfich2[i];
      if (i < lineasfich2.size() - 1) fichero2Escritura << std::endl;
    }
    fichero2Escritura.close();
    std::ifstream fichero1Lectura(nombreFichero1);
    while (getline(fichero1Lectura, cadaLinea)) {
      std::stringstream ss(cadaLinea);
      std::vector<std::string> cerradurasCadaUsuario;
      std::string word, cerraduras = "";
      ss >> word;
      bool hayModificacion = false;
      CerradurasDeUsuarioExistente(word, nombreFichero1, cerradurasCadaUsuario);
      for (int i = 0; i < cerradurasCadaUsuario.size(); ++i) {
        if (cerradurasCadaUsuario[i] != cerradura) {
          cerraduras += cerradurasCadaUsuario[i];
          if (i < cerradurasCadaUsuario.size() - 1) cerraduras += ' ';
        } else hayModificacion = true;
      }
      if (hayModificacion == false) lineasfich1.push_back(cadaLinea);
      else {
        if (cerraduras[cerraduras.size() - 1] == ' ') cerraduras = cerraduras.substr(0, cerraduras.size() - 1);
        std::string lineaModi = "";
        lineaModi += word + "\t\t";
        ss >> word;
        lineaModi += word + "\t " + cerraduras;
        lineasfich1.push_back(lineaModi);
      }
    }
    fichero1Lectura.close();
    std::ofstream fichero1Escritura(nombreFichero1);
    for (int i = 0; i < lineasfich1.size(); ++i) {
      fichero1Escritura << lineasfich1[i];
      if (i < lineasfich1.size() - 1) fichero1Escritura << std::endl;
    }
    fichero1Escritura.close();  
  } else {
      std::cout << "La cerradura " << cerradura << " no estaba en el sistema.\n";
  }  
}

// Dar de baja a un usuario de la base de datos
void Datos::DarBajaUsuario(const std::string& nombreFichero) {
  std::cout << "\nDar de Baja Usuario.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario(); // Usuario a borrar
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) { // Comprobamos que el usuario exista en la base de datos
    std::ifstream fichero1(nombreFichero);
    std::string cadaLinea = "";
    std::vector<std::string> lineas;
    while (getline(fichero1, cadaLinea)) { // Recorremos la base de datos
      std::stringstream ss(cadaLinea);
      std::string word;
      ss >> word;
      if (word != usuario.get_id()) lineas.push_back(cadaLinea); // Copiamos las lineas de todos los usuario que no nos interesan
    }
    fichero1.close();
    std::ofstream fichero2(nombreFichero);
    for (int i = 0; i < lineas.size(); ++i) { // Reescribimos la base de datos sin el usuario
      fichero2 << lineas[i];
      if (i < lineas.size() - 1) fichero2 << "\n";
    }
    fichero2.close();
  } else { // El usuario que se quiere dar de baja no existe
      std::cout << "Usuario inexistente.\n";
  }
}

// Dar de baja cerraduras en un usuario ya existente
void Datos::DarBajaCerraduraEnUsuarioExistente(const std::string& nombreFichero) {
  std::cout << "\nDar de Baja Cerradura en usuario existente.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario();
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }  
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) {
    std::vector<std::string> listaCerraduras;
    CerradurasDeUsuarioExistente(usuario.get_id(), nombreFichero, listaCerraduras);
    std::cout << "Que cerradura quiere dar de baja.\n";
    std::string cerradura = usuario.DimeUnNombreDeCerradura();
    bool encuentraCerradura = false;
    for (int i = 0; i < listaCerraduras.size(); ++i) {
      if (cerradura == listaCerraduras[i]) {
        encuentraCerradura = true;
        listaCerraduras.erase(listaCerraduras.begin() + i);
        break;
      }
    }
    if (encuentraCerradura == true) {
      ActualizarCerraduraEnUsuarioExistente(usuario.get_id(), nombreFichero, listaCerraduras);
    } else std::cout << "Cerradura inexistente en el usuario: " << usuario.get_id() << std::endl;
  } else {
      std::cout << "Usuario inexistente.\n";
  }
}

void Datos::CambiarPasswdUsuarioExistente(const std::string& nombreFichero) {
  std::cout << "\nCambiar contraseña en usuario existente.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario();
  while (usuario.get_id() == "Admin") {
    std::cout << "A este usuario no se le puede cambiar la contraseña. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }  
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) {
    std::string passwd = DimeUnPassword();
    ActualizarPasswordEnUsuarioExistente(usuario.get_id(), passwd, nombreFichero);
  } else {
      std::cout << "Usuario inexistente.\n";
  }
}

void Datos::CambiarNombreUsuarioExistente(const std::string& nombreFichero) {
  std::cout << "\nCambiar nombre de usuario existente.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario();
  while (usuario.get_id() == "Admin") {
    std::cout << "A este usuario no se le puede cambiar el nombre. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }  
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) {
    do {
      std::cout << "Debe introducir un nuevo nombre.\n";
      std::string id = DimeUnNombreDeUsuario();
      if (id == usuario.get_id()) {
        std::cout << "El nuevo nombre coincide con el actual. No se modifica la base de datos.\n";
        return;
      } else {
          if (ComprobarUsuario(id, nombreFichero)) {
            std::cout << "El nuevo nombre coincide con un usuario ya existente.\n";
          } else {
              ActualizarNombreDeUsuarioExistente(usuario.get_id(), id, nombreFichero);
              return;
          }
      }
    } while (true);
  } else {
      std::cout << "Usuario inexistente.\n";
  }
}

void Datos::ActualizarAltaUsuarioFich(const Usuarios& usuario, const std::string& nombreFichero, const std::vector<std::string>& todasCerraduras) const {
  std::ofstream fichero(nombreFichero, std::ios_base::app);
  fichero << "\n" << usuario.get_id() << "\t\t" << usuario.get_passwd() << "\t ";
  for (int i = 0; i < todasCerraduras.size(); ++i) {
    fichero << todasCerraduras[i];
    if (i < todasCerraduras.size() - 1) fichero << " ";
  }
  fichero.close();
}

// Actualiza la base de datos con el apartado de cerraduras del usuario editado
void Datos::ActualizarCerraduraEnUsuarioExistente(const std::string& nombreUsuario, const std::string& nombreFichero,
                                                           const std::vector<std::string>& todasCerraduras) const {
  std::vector<std::string> lineas;
  std::ifstream fichero1(nombreFichero);
  std::string cadaLinea = "";
  bool estoyEnLineaAModificar;
  while (getline(fichero1, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == nombreUsuario) {
      std::string lineaAMeter = "";
      lineaAMeter += nombreUsuario + "\t\t";
      ss >> word;
      lineaAMeter += word + "\t ";
      for (int i = 0; i < todasCerraduras.size(); ++i) {
        lineaAMeter += todasCerraduras[i];
        if (i < todasCerraduras.size() - 1) lineaAMeter += " ";
      }
      lineas.push_back(lineaAMeter);
    } else lineas.push_back(cadaLinea);
  }
  fichero1.close();
  std::ofstream fichero2(nombreFichero);
  for (int i = 0; i < lineas.size(); ++i) {
    fichero2 << lineas[i];
    if (i < lineas.size() - 1) fichero2 << "\n";
  }
  fichero2.close();  
}

void Datos::ActualizarPasswordEnUsuarioExistente(const std::string& nombreUsuario, const std::string& passwdUsr,
                                                 const std::string& nombreFichero) const {
  std::vector<std::string> lineas;
  std::ifstream fichero1(nombreFichero);
  std::string cadaLinea = "";
  bool estoyEnLineaAModificar;
  while (getline(fichero1, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == nombreUsuario) {
      std::string lineaAMeter = "";
      lineaAMeter += nombreUsuario + "\t\t";
      ss >> word;
      if (word == passwdUsr) {
        std::cout << "La nueva contaseña coincide con la actual. No se modifica la base de datos.\n";
        fichero1.close();
        return;
      }
      lineaAMeter += passwdUsr + "\t ";
      while (ss >> word) {
        lineaAMeter += word + " ";
      }
      lineaAMeter = lineaAMeter.substr(0, lineaAMeter.size() - 1);
      lineas.push_back(lineaAMeter);
    } else lineas.push_back(cadaLinea);
  }
  fichero1.close();
  std::ofstream fichero2(nombreFichero);
  for (int i = 0; i < lineas.size(); ++i) {
    fichero2 << lineas[i];
    if (i < lineas.size() - 1) fichero2 << "\n";
  }
  fichero2.close(); 
}

void Datos::ActualizarNombreDeUsuarioExistente(const std::string& nombreUsuarioActual, const std::string& nombreUsuarioNuevo,
                                               const std::string& nombreFichero) const {
  std::vector<std::string> lineas;
  std::ifstream fichero1(nombreFichero);
  std::string cadaLinea = "";
  bool estoyEnLineaAModificar;
  while (getline(fichero1, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == nombreUsuarioActual) {
      std::string lineaAMeter = "";
      lineaAMeter += nombreUsuarioNuevo + "\t\t";
      ss >> word;
      lineaAMeter += word + "\t ";
      while (ss >> word) {
        lineaAMeter += word + " ";
      }
      lineaAMeter = lineaAMeter.substr(0, lineaAMeter.size() - 1);
      lineas.push_back(lineaAMeter);
    } else lineas.push_back(cadaLinea);
  }
  fichero1.close();
  std::ofstream fichero2(nombreFichero);
  for (int i = 0; i < lineas.size(); ++i) {
    fichero2 << lineas[i];
    if (i < lineas.size() - 1) fichero2 << "\n";
  }
  fichero2.close();  
}