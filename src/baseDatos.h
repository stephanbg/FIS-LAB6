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
   std::string DimeUnPassword() const;
   bool ComprobarUsrYPwd(const Usuarios&, const std::string&) const;
   bool ComprobarUsuario(const std::string&, const std::string&) const;
   void CerradurasDeUsuarioExistente(const std::string&, const std::string&, std::vector<std::string>&);

   void DarAltaUsuario(const std::string&);
   void DarAltaCerraduraEnUsuarioExistente(const std::string&);
   void DarBajaUsuario(const std::string&);
   void DarBajaCerraduraEnUsuarioExistente(const std::string&);
   void CambiarPasswdUsuarioExistente(const std::string&);
  private:
   void ActualizarAltaUsuarioFich(const Usuarios&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarCerraduraEnUsuarioExistente(const std::string&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarPasswordEnUsuarioExistente(const std::string&, const std::string&, const std::string&) const;
};