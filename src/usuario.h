#pragma once
/* Clase que define la función del usuario en el sistema */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

class Usuarios {
 public:
 //Constructores
  Usuarios() {}
  Usuarios(const std::string&, const std::string&);
<<<<<<< HEAD
  void Menu(const std::string&, const std::string&) const;
=======
 // Métodos
  void Menu(const std::string&) const;
>>>>>>> 95f376b5c65206f9adc5b2c00233ff5ffc2d4db0
  std::string DimeUnNombreDeCerradura() const;
 // Getters
  std::string get_id() const { return id_; }
  std::string& set_id() { return id_; }
  std::string get_passwd() const { return passwd_; }
 private:
 // Atributos
  std::string id_{};
  std::string passwd_{};
 // Método
  bool AbrirPuerta(const std::string&, const std::string&) const;
};
