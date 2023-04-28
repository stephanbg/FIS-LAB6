#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

class Usuarios {
 public:
  Usuarios() {}
  Usuarios(const std::string&, const std::string&);
  void Menu(const std::string&) const;
  std::string DimeUnNombreDeCerradura() const;
  std::string get_id() const { return id_; }
  std::string& set_id() { return id_; }
  std::string get_passwd() const { return passwd_; }
 private:
  std::string id_{};
  std::string passwd_{};
  bool AbrirPuerta(const std::string&, const std::string&) const;
};