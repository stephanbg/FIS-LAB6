#include <iostream>

#include "usuario.h"
#include "baseDatos.h"

/*
 * Funcion principal
 */
int main() { /// Main Original
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
  std::cout << "Usuario Inicial: Admin\n";
  std::cout << "Contraseña Inicial: 0000\n\n";
  int contadorIntentos = 1;
  while (true) { //Bucle pricipal de programa
    Datos baseDatos;
    std::string fich1 = "BASE_DATOS.txt", fich2 = "SISTEMA.txt";
    if (baseDatos.ComprobarEncriptacion(fich1) == false) baseDatos.Encriptar(fich1); /// Comprueba si la primera vez que se accede ya está encriptado
    Usuarios usuario = baseDatos.IdentificacionUsuario();
    if (baseDatos.ComprobarUsrYPwd(usuario, fich1)) { // Revisión de usuario y contraseña
      std::cout << "¡¡¡CORRECTO!!!\n";
      contadorIntentos = 1;
      usuario.Menu(fich1, fich2); // Entramos al menu     
    } else { // No existe usuario introducido o contraseña incorrecta
        std::cout << "Usuario o Contraseña incorrectos.\n";
        if (contadorIntentos < 5) std::cout << "Te quedan " << 5 - contadorIntentos << " intentos.\n";
        if (contadorIntentos == 5) { // Numero de intentos maximo alcanzado
          std::cout << "ERROR DE LOGIN. Se ha equivocado 5 veces. Llame al servicio técnico.\n";
          return EXIT_FAILURE;
        }      
        contadorIntentos++;
    }
    std::cout << std::endl;
  }
  return 0;
}