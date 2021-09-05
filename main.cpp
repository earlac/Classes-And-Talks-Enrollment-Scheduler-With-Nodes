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

    administrador(string nUsuario, string nContrasenna){
        usuario = nUsuario;
        contrasenna = nContrasenna;
        
        sigAdmin = NULL;
    }
} *listaAdministradores;

struct profesor{
    string nombreProf;
    int cedulaProf;

    profesor *sigProf, *antProf;
    struct enlazarGrupo *gruposProfAux;

    profesor(string nNombreProf, int nCedulaProf){
        nombreProf= nNombreProf;
        cedulaProf= nCedulaProf;

        sigProf= NULL;
        antProf= NULL;
        gruposProfAux= NULL;
        
    }

} *listaProfesores;

struct grupo{
    grupo *sigGrupo;
    int numGrupo;    
    struct curso *cursoActual;
    
    
    grupo(int nNumGrupo){
        numGrupo= nNumGrupo;
        
        sigGrupo= NULL;
    }
} *listaGrupos;

struct enlazarGrupo{

    enlazarGrupo *sigEn;
    struct grupo *enlaceGrupo;
    
    enlazarGrupo(){
        sigEn= NULL;
        enlaceGrupo= NULL;
    }
    
};

struct semestre{
    struct curso *listaCursos;
    int numSemestre;
    int anno;

    semestre(int nSemestre, int nAnno){
        nSemestre= nSemestre;
        anno= nAnno;
        
        listaCursos= NULL;
    }
} *listaSemestres;

struct enlaceCurso{
    string codigoCurso;
    struct curso *sigCurso;

    enlaceCurso(string nCodigoCurso){
        codigoCurso= nCodigoCurso;
        sigCurso= NULL;
    }

};

struct curso{
    string nombre;
    string codigo;
    
    curso *sigCurso;
    struct grupo *grupoCursando;
    curso(string nNombre, string nCodigo){
        nombre= nNombre;
        codigo= nCodigo;

        grupoCursando=NULL;


    }
} *listaCursos;

struct evaluacion{
    
    struct tarea *sigTarea;
    struct examen *sigExamen;
    struct proyecto *sigProyecto;
    struct gira *sigGira;
    
    evaluacion(){

        sigTarea= NULL;
        sigExamen = NULL;
        sigProyecto= NULL;
        sigGira= NULL;
        
    }
};

struct tarea{
    int fechaEntrega;
    string idActividad;
    bool entregado = false;

    tarea *sigTarea;
    
    tarea(int nFechaEntrega, string nIdActividad, bool nEntregado){
        fechaEntrega= nFechaEntrega;
        idActividad= nIdActividad;
        entregado= nEntregado;
        
        sigTarea= NULL;

    }
};

struct examen{
    int fechaEntrega;
    string idActividad;
    bool entregado = false;
    
    examen *sigExamen;

    examen(int nfechaEntrega, string nIdAct, bool nEntregado){
        fechaEntrega = nfechaEntrega;
        idActividad = nIdAct;
        entregado = nEntregado;
        
        sigExamen = NULL;
    }
};

struct proyecto{
    int fechaEntrega;
    string idActividad;
    bool entregado = false;

    proyecto *sigProyecto;

    proyecto(int nFechaEntrega, string nIdAct, bool nEntregado){
        fechaEntrega = nFechaEntrega;
        idActividad = nIdAct;
        entregado = nEntregado;

        sigProyecto= NULL;
    }
};

struct gira{
    
    int fechaEntrega;
    string idActividad;
    bool entregado = false;

    gira *sigGira;
    
    gira(int nFechaEntrega, string nIdAct, bool nEntregado){
        fechaEntrega = nFechaEntrega;
        idActividad = nIdAct;
        entregado = nEntregado;

        sigGira = NULL;

    }
};