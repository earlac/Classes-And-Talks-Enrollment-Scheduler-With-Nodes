/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado, 2020
*/
#include <iostream>

using namespace std;

struct administrador {
    string usuario;
    string contrasenna;
    administrador *sigAdmin;

    administrador(string usuario, string contrasenna){
        usuario = usuario;
        contrasenna = contrasenna;
        sigAdmin = NULL;
    }
} *ListaAdministradores;



