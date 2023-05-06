#include "baseDatos.h"

Usuarios Datos::IdentificacionUsuario() const {
    std::string id = "", passwd = "";
    id = DimeUnNombreDeUsuario();
    passwd = DimeUnPassword();
    std::cout << std::endl;
    Usuarios usuario(id, passwd);
    return usuario;
}

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
  while (getline(std::cin, passwd) && ((passwd.size() != 4) || (passwd.find_first_not_of("0123456789") != std::string::npos))) {
    std::cout << "Contraseña no permitida. Requisitos, 4 dígitos.\n";
    std::cout << "Contraseña: ";
  }
  return passwd;
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

void Datos::DarAltaUsuario(const std::string& nombreFichero) {
  std::cout << "\nDar de Alta Usuario.\n";
  bool yaExisteUsr;
  do {
    yaExisteUsr = false;
    Usuarios usuario = this->IdentificacionUsuario();
    std::vector<std::string> todasCerraduras;
    if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) {
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
          std::cout << "Que cerradura quiere abrir.\n";
          std::string cerradura = usuario.DimeUnNombreDeCerradura();
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

void Datos::DarAltaCerraduraEnUsuarioExistente(const std::string& nombreFichero) {
  std::cout << "\nInsertar Cerradura en usuario existente.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario();
  std::vector<std::string> cerradurasDeUsuario;
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero) == false) {
    std::cout << "Usuario inexistente.\n";
  } else {
      CerradurasDeUsuarioExistente(usuario.get_id(), nombreFichero, cerradurasDeUsuario);
      bool yaExisteCerradura;
      std::string insertarCerradura = "";
      do {    
        yaExisteCerradura = false;
        std::cout << "Que cerradura quiere abrir.\n";
        std::string cerradura = usuario.DimeUnNombreDeCerradura();
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
      ActualizarCerraduraEnUsuarioExistente(usuario.get_id(), nombreFichero, cerradurasDeUsuario);
      /// Metodo devuelve vector cerraduras de un usuario
  }
}

void Datos::DarBajaUsuario(const std::string& nombreFichero) {
  std::cout << "\nDar de Baja Usuario.\n";
  Usuarios usuario;
  usuario.set_id() = this->DimeUnNombreDeUsuario();
  while (usuario.get_id() == "Admin") {
    std::cout << "Este usuarios no es válido. Inténtelo de nuevo.\n";
    usuario.set_id() = this->DimeUnNombreDeUsuario();
  }
  if (this->ComprobarUsuario(usuario.get_id(), nombreFichero)) {
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

void Datos::ActualizarAltaUsuarioFich(const Usuarios& usuario, const std::string& nombreFichero, const std::vector<std::string>& todasCerraduras) const {
  std::ofstream fichero(nombreFichero, std::ios_base::app);
  fichero << "\n" << usuario.get_id() << "\t\t" << usuario.get_passwd() << "\t ";
  for (int i = 0; i < todasCerraduras.size(); ++i) {
    fichero << todasCerraduras[i];
    if (i < todasCerraduras.size() - 1) fichero << " ";
  }
  fichero.close();
}

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