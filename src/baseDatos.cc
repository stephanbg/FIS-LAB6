#include "baseDatos.h"

Usuarios Datos::IdentificacionUsuario() const {
    std::cout << "Usuario: ";
    std::string id = "";
    while (getline(std::cin, id) && (id == "USUARIOS")) {
      std::cout << "Usuario no permitido.\n";
      std::cout << "Usuario: ";
    }
    std::cout << "Contraseña: ";
    std::string passwd = "";
    while (getline(std::cin, passwd) && ((passwd.size() != 4) || (passwd.find_first_not_of("0123456789") != std::string::npos))) {
      std::cout << "Requisitos, 4 dígitos: ";
    }
    std::cout << std::endl;
    Usuarios usuario(id, passwd);
    return usuario;
}

bool Datos::ComprobarUsrYPwd(const Usuarios& usuario, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "", usr = "", pwd = "";
  bool usuarioYPasswdOK = false;
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    int contador = 0;
    while ((ss >> word) && (contador < 2)) { /// Extrae las 2 primeras palabras de cada linea (usuario y contraseña)
        if (contador == 0) usr = word;
        else pwd = word;
        contador++;
    }
    if ((usr == usuario.get_id()) && (pwd == usuario.get_passwd())) {
      usuarioYPasswdOK = true;
      break;
    }    
  }
  return usuarioYPasswdOK;
}

bool Datos::ComprobarUsuario(const Usuarios& usuario, const std::string& nombreFichero) const {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "", usr = "";
  bool usuarioOK = false;
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == usuario.get_id()) {
      usuarioOK = true;
      break;
    }    
  }
  return usuarioOK;
}

/*bool ComprobarCerradura(const Usuarios& usuario, const std::string& nombreFichero, const std::string& cerradura) const {

}*/

void Datos::DarAltaUsuario(const std::string& nombreFichero) {
  std::cout << "\nDar de Alta Usuario.\n";
  bool yaExisteUsr;
  do {
    yaExisteUsr = false;
    Usuarios usuario = this->IdentificacionUsuario();
    std::vector<std::string> todasCerraduras;
    if (this->ComprobarUsuario(usuario, nombreFichero)) {
      std::cout << "Usuario existente.\n";
      yaExisteUsr = true;
      std::string opcion = "";
      do {
        std::cout << "Reintentar o Salir [R/S]: ";
      } while (getline(std::cin, opcion) && ((opcion != "R") && (opcion != "S")));
      if (opcion == "S") break;
    } else {
        bool encuentroCerradura;
        std::string opcion, insertarCerradura;
        do {
          std::string cerradura = usuario.QueCerraduraDeseaAbrir();
          encuentroCerradura = false;
          for (int i = 0; i < todasCerraduras.size(); ++i) {
            if (todasCerraduras[i] == cerradura) {
              encuentroCerradura = true;
              break;
            }
          }
          opcion = "", insertarCerradura = "";
          if (encuentroCerradura == false) {
            todasCerraduras.push_back(cerradura);
            std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
            while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
              std::cout << "Tiene que responder [S/N].\n";
              std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
            }
            if (insertarCerradura == "N") break;
          } else {
              std::cout << "Cerradura existente en el usuario: " << usuario.get_id() << "\n";
              do {
                std::cout << "Reintentar o Salir [R/S]: ";
              } while (getline(std::cin, opcion) && ((opcion != "R") && (opcion != "S")));
              if (opcion == "S") break;            
          }
        } while ((encuentroCerradura == true) || (opcion == "R") || (insertarCerradura == "S"));
    }
    if (yaExisteUsr == false) {
      ActualizarAltaUsuarioFich(usuario, nombreFichero, todasCerraduras);
    }
  } while (yaExisteUsr == true);
}

void Datos::CerradurasDeUsuarioExistente(const Usuarios& usuario, const std::string& nombreFichero, std::vector<std::string>& todasCerraduras) {
  std::ifstream fichero(nombreFichero);
  std::string cadaLinea = "";
  while (getline(fichero, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == usuario.get_id()) {
      ss >> word;
      while (ss >> word) {
        todasCerraduras.push_back(word);
      }
      break;
    }
  }
}

void Datos::InsertaCerraduraEnUsuarioExistente(const std::string& nombreFichero) {
  std::cout << "\nInsertar Cerradura en usuario existente.\n";
  Usuarios usuario = this->IdentificacionUsuario();
  std::vector<std::string> cerradurasDeUsuario;
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario = this->IdentificacionUsuario();
  }
  if (this->ComprobarUsuario(usuario, nombreFichero) == false) {
    std::cout << "Usuario inexistente.\n";
  } else {
      CerradurasDeUsuarioExistente(usuario, nombreFichero, cerradurasDeUsuario);
      bool yaExisteCerradura;
      std::string insertarCerradura = "";
      do {    
        yaExisteCerradura = false;
        std::string cerradura = usuario.QueCerraduraDeseaAbrir();
        for (int i = 0; i < cerradurasDeUsuario.size(); ++i) {
          if (cerradura == cerradurasDeUsuario[i]) {
            yaExisteCerradura = true;
            std::cout << "Esa cerradura ya podía ser abierta por: " << usuario.get_id() << std::endl << std::endl;
            break;
          }
        }
        if (yaExisteCerradura == false) {
          cerradurasDeUsuario.push_back(cerradura);
          std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
          while (getline(std::cin, insertarCerradura) && ((insertarCerradura != "S") && (insertarCerradura != "N"))) {
            std::cout << "Tiene que responder [S/N].\n";
            std::cout << "¿Desea añadir más cerraduras al usuario? [S/N]: ";
          }
        }
      } while ((yaExisteCerradura == true) || (insertarCerradura == "S"));
      ActualizarFichNuevaCerraduraEnUsuarioExistente(usuario, nombreFichero, cerradurasDeUsuario);
      /// Metodo devuelve vector cerraduras de un usuario
  }
}

void Datos::DarBajaUsuario(const std::string& nombreFichero) {
  std::cout << "\nDar de Baja Usuario.\n";
  Usuarios usuario = this->IdentificacionUsuario();
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario = this->IdentificacionUsuario();
  }
  if (this->ComprobarUsuario(usuario, nombreFichero)) {
    std::ifstream fichero1(nombreFichero);
    std::string cadaLinea = "";
    std::vector<std::string> lineas;
    while (getline(fichero1, cadaLinea)) {
      std::stringstream ss(cadaLinea);
      std::string word;
      ss >> word;
      if (word != usuario.get_id()) lineas.push_back(cadaLinea);
    }
    fichero1.close();
    std::ofstream fichero2(nombreFichero);
    for (int i = 0; i < lineas.size(); ++i) {
      fichero2 << lineas[i];
      if (i < lineas.size() - 1) fichero2 << "\n";
    }
    fichero2.close();
  } else {
      std::cout << "Usuario inexistente.\n";
  }
}

/*void Datos::DarBajaCerradura(const std::string& nombreFichero) {
  std::cout << "\nDar de Baja Cerradura.\n";
}*/

void Datos::ActualizarAltaUsuarioFich(const Usuarios& usuario, const std::string& nombreFichero, const std::vector<std::string>& todasCerraduras) const {
  std::ofstream fichero(nombreFichero, std::ios_base::app);
  fichero << "\n" << usuario.get_id() << "\t\t" << usuario.get_passwd() << "\t ";
  for (int i = 0; i < todasCerraduras.size(); ++i) {
    fichero << todasCerraduras[i];
    if (i < todasCerraduras.size() - 1) fichero << " ";
  }
  fichero.close();
}

void Datos::ActualizarFichNuevaCerraduraEnUsuarioExistente(const Usuarios& usuario, const std::string& nombreFichero,
                                                           const std::vector<std::string>& todasCerraduras) const {
  std::vector<std::string> lineas;
  std::ifstream fichero1(nombreFichero);
  std::string cadaLinea = "";
  bool estoyEnLineaAModificar;
  while (getline(fichero1, cadaLinea)) {
    std::stringstream ss(cadaLinea);
    std::string word;
    ss >> word;
    if (word == usuario.get_id()) {
      std::string lineaAMeter = "";
      lineaAMeter += usuario.get_id() + "\t\t" + usuario.get_passwd() + "\t ";
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