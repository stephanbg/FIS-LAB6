#pragma once
/* Clase que define la función del usuario en el sistema */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>

class Usuarios {
 public:
 //Constructores
  Usuarios() {}
  Usuarios(const std::string&, const std::string&);
  void Menu(const std::string&, const std::string&) const;
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
