#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "usuario.h"

class Datos {
  public:
   Usuarios IdentificacionUsuario() const;
   bool ComprobarUsrYPwd(const Usuarios&, const std::string&) const;
   bool ComprobarUsuario(const Usuarios&, const std::string&) const;
   //bool ComprobarCerradura(const Usuarios&, const std::string&, const std::string&) const;
   void DarAltaUsuario(const std::string&);
   void InsertaCerraduraEnUsuarioExistente(const std::string&);
   void DarBajaUsuario(const std::string&);
   //void DarBajaCerradura(const std::string&);
  private:
   void ActualizarAltaUsuarioFich(const Usuarios&, const std::string&, const std::vector<std::string>&) const;
};