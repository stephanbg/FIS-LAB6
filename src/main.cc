#include <iostream>

#include "usuario.h"
#include "baseDatos.h"

//std::vector<Usuarios>

int main() {
  int contadorIntentos = 1;
  while (true) {
    Datos baseDatos;
    Usuarios usuario = baseDatos.IdentificacionUsuario();
    std::string fich = "BASE_DATOS.txt";
    if (baseDatos.ComprobarUsrYPwd(usuario, fich)) {
      std::cout << "¡¡¡CORRECTO!!!\n";
      contadorIntentos = 1;
      usuario.Menu(fich);      
    } else {
        std::cout << "Usuario o Contraseña incorrectos.\n";
        if (contadorIntentos < 5) std::cout << "Te quedan " << 5 - contadorIntentos << " intentos.\n";
        if (contadorIntentos == 5) {
          std::cout << "ERROR DE LOGIN. Se ha equivocado 5 veces. Llame al servicio técnico.\n";
          return EXIT_FAILURE;
        }      
        contadorIntentos++;
    }
    std::cout << std::endl;
  }
  return 0;
}