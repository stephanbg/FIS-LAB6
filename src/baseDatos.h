#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "usuario.h"

class Datos {
  public:
   Usuarios IdentificacionUsuario() const;
   std::string DimeUnNombreDeUsuario() const;
   bool ComprobarUsrYPwd(const Usuarios&, const std::string&) const; /// Le paso Usuarios porque voy a comprobar nombre y passwd
   bool ComprobarUsuario(const std::string&, const std::string&) const; /// Le paso string porque sólo voy a comprobar nombre
   void CerradurasDeUsuarioExistente(const std::string&, const std::string&, std::vector<std::string>&);

   void DarAltaUsuario(const std::string&);
   void DarAltaCerraduraEnUsuarioExistente(const std::string&);
   void DarBajaUsuario(const std::string&);
   void DarBajaCerraduraEnUsuarioExistente(const std::string&);
  private:
   void ActualizarAltaUsuarioFich(const Usuarios&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarCerraduraEnUsuarioExistente(const std::string&, const std::string&, const std::vector<std::string>&) const;
};