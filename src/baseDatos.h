#pragma once
/* Clase que define tanto la base de datos de los usuarios, como
 * la de las cerraduras y todas las operaciones que se pueden realizar
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>

#include "usuario.h"

class Datos {
  public:
   /// Métodos de comrpobación
   Usuarios IdentificacionUsuario() const;
   std::string DimeUnNombreDeUsuario() const;
   std::string DimeUnPassword() const;
   bool ComprobarUsrYPwd(const Usuarios&, const std::string&) const;
   bool ComprobarUsuario(const std::string&, const std::string&) const;
   bool ComprobarCerraduraEnSistema(const std::string&, const std::string&) const;
   void CerradurasDeUsuarioExistente(const std::string&, const std::string&, std::vector<std::string>&);
   bool ComprobarEncriptacion(const std::string&) const;

   /// Métodos de operaciones
   void DarAltaUsuario(const std::string&, const std::string&);
   void DarAltaCerraduraEnUsuarioExistente(const std::string&, const std::string&);
   void DarBajaUsuario(const std::string&);
   void DarBajaCerraduraEnUsuarioExistente(const std::string&);
   void CambiarPasswdUsuarioExistente(const std::string&);
   void AltaCerraduraEnSistema(const std::string&);
   void BajaCerraduraEnSistema(const std::string&, const std::string&);
   void CambiarNombreUsuarioExistente(const std::string&);
   void Encriptar(const std::string&);
   void DesEncriptar(const std::string&);
   std::string DesEncriptaLinea(const std::string&) const;
   std::string EncriptaLinea(const std::string&) const;   
  private:
   /// Métodos privados de actualizaciones
   void ActualizarAltaUsuarioFich(const Usuarios&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarCerraduraEnUsuarioExistente(const std::string&, const std::string&, const std::vector<std::string>&) const;
   void ActualizarPasswordEnUsuarioExistente(const std::string&, const std::string&, const std::string&) const;
   void ActualizarNombreDeUsuarioExistente(const std::string&, const std::string&, const std::string&) const;
};