#include <iostream>

#include "usuario.h"
#include "baseDatos.h"

//std::vector<Usuarios>

int main(int argc, char* argv[]) {
  int contadorIntentos = 1;
  while (true) {
    Datos baseDatos;
    Usuarios usuario = baseDatos.IdentificacionUsuario();
    if (baseDatos.ComprobarUsrYPwd(usuario, argv[1])) {
      std::cout << "¡¡¡CORRECTO!!!\n";
      contadorIntentos = 1;
      usuario.Menu(argv[1]);      
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