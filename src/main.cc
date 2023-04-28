#include <iostream>

#include "usuario.h"
#include "baseDatos.h"

int main() {
  std::cout << std::endl <<
  "**************************** PROGRAMA REALIZADO POR ****************************\n"
  "*                                                                              *\n"
  "* Stephan Brommer Gutiérrez (Programador)        ---  alu0101493497@ull.edu.es *\n"
  "* Adrián Abreu Alonso (Programador)              ---  alu0101327570@ull.edu.es *\n"
  "* Alejandro Valencia Hernández (Programador)     ---  alu0101500386@ull.edu.es *\n"
  "* Alejandro Cruz Quiralte (Programador)          ---  alu0101424545@ull.edu.es *\n"
  "* Fernando Manuel González Perdomo (Programador) ---  alu0101506371@ull.edu.es *\n"
  "* Gabriel Albelo Fabelo (Cliente)                ---  alu0101472911@ull.edu.es *\n"
  "* Isaac Domínguez Fajardo (Mánager)              ---  alu0101474960@ull.edu.es *\n"
  "*                                                                              *\n"
  "********************************************************************************\n\n";
  
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