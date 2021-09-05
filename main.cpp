/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado, 2020
*/
#include <iostream>

using namespace std;

struct administrador {//Doubled linked list
    string usuario;
    string contrasenna;
    administrador *sigAdmin, *antAdmin;

    administrador(string usuario, string contrasenna){
        usuario = usuario;
        contrasenna = contrasenna;
        sigAdmin = NULL;
        antAdmin = NULL;
    }
} *ListaAdministradores;

