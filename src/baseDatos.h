#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <termios.h>
#include <unistd.h>

#include "usuario.h"

class Datos {
  public:
   Usuarios IdentificacionUsuario() const;
   std::string DimeUnNombreDeUsuario() const;
   std::string DimeUnPassword() const;
   bool ComprobarUsrYPwd(const Usuarios&, const std::string&) const;
   bool ComprobarUsuario(const std::string&, const std::string&) const;
   bool ComprobarCerraduraEnSistema(const std::string&, const std::string&) const;
   void CerradurasDeUsuarioExistente(const std::string&, const std::string&, std::vector<std::string>&);

   void DarAltaUsuario(const std::string&, const std::string&);
   void DarAltaCerraduraEnUsuarioExistente(const std::string&, const std::string&);
   void DarBajaUsuario(const std::string&);
   void DarBajaCerraduraEnUsuarioExistente(const std::string&);
   void CambiarPasswdUsuarioExistente(const std::string&);
   void AltaCerraduraEnSistema(const std::string&);
   void BajaCerraduraEnSistema(const std::string&, const std::string&);
   void CambiarNombreUsuarioExistente(const std::string&);
  private:
   void ActualizarAltaUsuarioFich(const Usuarios&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarCerraduraEnUsuarioExistente(const std::string&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarPasswordEnUsuarioExistente(const std::string&, const std::string&, const std::string&) const;
   void ActualizarNombreDeUsuarioExistente(const std::string&, const std::string&, const std::string&) const;
};