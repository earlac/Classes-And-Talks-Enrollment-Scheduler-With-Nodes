/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado,       
             Brenda Badilla Rodriguez,  
*/
#include <iostream>

using namespace std;

struct administrador {//Simple linked list
    string usuario; //username
    string contrasenna;
    
    administrador *sigAdmin;

    administrador(string nUsuario, string nContrasenna){
        usuario = nUsuario;
        contrasenna = nContrasenna;
        
        sigAdmin = NULL;
    }
} *listaAdministradores;

struct profesor{ //Double linked list
    string nombreProf;
    int cedulaProf;

    profesor *sigProf, *antProf;
    struct enlazarGrupo *gruposProfAux;//Links to list of groups the professor has. Same struct as Estudiante

    profesor(string nNombreProf, int nCedulaProf){
        nombreProf= nNombreProf;
        cedulaProf= nCedulaProf;

        sigProf= NULL;
        antProf= NULL;

        gruposProfAux= NULL;
    }

} *listaProfesores;

struct estudiante{//Simple linked list
    string nombreEst;
    int carnet;

    estudiante *sigEst;
    struct enlazarGrupo *gruposEstAux;//Links to list of groups the student is in. Uses the same struct as Profesor

    //struct enlazarCharla *charla;
    //struct evaluacionesEntregadas *; Hacer otro struct para entrega

    estudiante(string nNombreEst, int nCarnet){
        nombreEst = nNombreEst;
        carnet = nCarnet;

        sigEst = NULL;
        gruposEstAux = NULL;
    }
} *listaEstudiantes;

struct grupo{//Simple linked list
    grupo *sigGrupo;
    int numGrupo;    
    struct curso *cursoActual; //Links to the class the group is in
    struct evaluaciones *evaluacionesEst; //Links to the evaluations the group has
    
    grupo(int nNumGrupo){
        numGrupo= nNumGrupo;

        cursoActual = NULL;
        evaluacionesEst = NULL;
        sigGrupo= NULL;
    }

} *listaGrupos;

struct enlazarGrupo{//Simple linked list

    enlazarGrupo *sigEn;
    struct grupo *enlaceGrupo; //Links to to the list of groups the user is in. Used by Estudiante and Profesor
    

    enlazarGrupo(grupo *nEnlaceGrupo){
        sigEn= NULL;
        enlaceGrupo= nEnlaceGrupo;
    }
};

struct semestre{ //Simple linked list 
    struct curso *listaCursos; //Links to the list of courses given in that said semester
    int numSemestre;
    int anno;
    semestre *sigSem;
    //enlace a charlas, sin enlace

    semestre(int nSemestre, int nAnno){
        nSemestre= nSemestre;
        anno= nAnno;
        
        listaCursos= NULL;
        sigSem = NULL;
    }
} *listaSemestres;

struct enlaceCurso{//Simple linked list
    struct curso *sigCurso; //Links to the course itself
    enlaceCurso *sig; //Orders the courses

    enlaceCurso(curso *nSigCurso){
        sigCurso= nSigCurso;
        sig = NULL;
    }
};

struct curso{ //Circular linked list 
    string nombre;
    string codigo;
    
    curso *sigCurso;
    struct grupo *grupoCursando; //Links to a list of groups that're taking the class

    curso(string nNombre, string nCodigo){
        nombre= nNombre;
        codigo= nCodigo;

        grupoCursando=NULL;
        sigCurso = NULL;
    }

} *listaCursos;

struct evaluacion{//Simple linked list. Links to the different evaluations the group has 
    
    struct tarea *sigTarea;
    struct examen *sigExamen;
    struct proyecto *sigProyecto;
    struct gira *sigGira;
    
    evaluacion *sigEv;

    evaluacion(tarea *nSigTarea, examen *nSigExamen, proyecto *nSigProyecto, gira *nSigGira){

        sigTarea= nSigTarea;
        sigExamen = nSigExamen;
        sigProyecto= nSigProyecto;
        sigGira= nSigGira;
        sigEv = NULL;
    }
};

struct tarea{//Simple linked list.
    int fechaEntrega; //Format: dd/mm/yyyy
    int hora; //Format: militar, ie. 1600 = 4p.m
    string idActividad; //Format: Tarea##, ie. Tarea#3
    bool entregado = false; //If the student did it or not. Default is false. 

    tarea *sigTarea;
    
    tarea(int nFechaEntrega, string nIdActividad, int nHora, bool nEntregado){
        fechaEntrega= nFechaEntrega;
        hora = nHora;
        idActividad= nIdActividad;
        entregado= nEntregado;
        
        sigTarea= NULL;

    }
} *listaTareas;

struct examen{
    int fechaEntrega;
    int hora;
    string idActividad;//Format: Examen#
    bool entregado = false;
    
    examen *sigExamen;

    examen(int nfechaEntrega, string nIdAct, int nHora, bool nEntregado){
        fechaEntrega = nfechaEntrega;
        hora = nHora;
        idActividad = nIdAct;
        entregado = nEntregado;
        
        sigExamen = NULL;
    }
}*listaExamenes;

struct proyecto{
    int fechaEntrega;
    int hora;
    string idActividad;
    bool entregado = false;

    proyecto *sigProyecto;

    proyecto(int nFechaEntrega, string nIdAct, int nHora, bool nEntregado){
        fechaEntrega = nFechaEntrega;
        hora = nHora;
        idActividad = nIdAct;
        entregado = nEntregado;

        sigProyecto= NULL;
    }
}*listaProyectos;

struct gira{
    
    int fechaEntrega;
    int hora;
    string idActividad;
    bool entregado = false;

    gira *sigGira;
    
    gira(int nFechaEntrega, string nIdAct, int nHora, bool nEntregado){
        fechaEntrega = nFechaEntrega;
        hora = nHora;
        idActividad = nIdAct;
        entregado = nEntregado;

        sigGira = NULL;

    }
}*listaGiras;

struct charla{//Simple linked list 
    string nombreCharla;
    int fecha; //Format: dd/mm/yy
    int hora; //Militar: 1630 = 4p.m
    //Duracion puede ser fija, evaluaciones tambien 

    charla *sig;
    struct asistente *asistentes; //Links to list of students who went 

    charla(string nNombreCharla, int nFecha, int nHora, bool nAsistencia){
        nombreCharla= nNombreCharla;
        fecha= nFecha;
        hora = nHora;
    }

}*listaCharlas;

struct asistente{//Al reves, estudiante A charla
    struct estudiante *estudiante;
    //string nombre;
    //int carnet;
    asistente *sigAs;

    asistente(struct estudiante *nEstudiante){
        estudiante = nEstudiante;
        asistente *sigAs = NULL;
    }
};
