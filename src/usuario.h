#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

class Usuarios {
 public:
  Usuarios(const std::string&, const std::string&);
  void Menu(const std::string&) const;
  std::string QueCerraduraDeseaAbrir() const;
  std::string get_id() const { return id_; }
  std::string get_passwd() const { return passwd_; }
 private:
  std::string id_{};
  std::string passwd_{};
  bool AbrirPuerta(const std::string&, const std::string&) const;
};