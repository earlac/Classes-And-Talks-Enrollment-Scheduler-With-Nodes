/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado,       
             Brenda Badilla Rodriguez,  
*/

#include <iostream>
#include <string>

using namespace std;

//-----------------------------------------------------------------------------------Estructuras

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

    struct enlazarCharla *charla;
    struct evaluacionesEntregadas *evaluacionEst; 

    estudiante(string nNombreEst, int nCarnet){
        nombreEst = nNombreEst;
        carnet = nCarnet;

        sigEst = NULL;
        gruposEstAux = NULL;
    }
} *listaEstudiantes;

struct grupo{//Simple linked list
    grupo *sigGrupo;
    // Al usuario se le pide el curso(abv+codigoNum) y el grupo(numGrupo)
    //a partir de ellos se crea idCurso
    int numGrupo;      //51 
    string abreviatura;//IC
    int codigoNum;     //3101
    int idCurso;       //310151
    struct curso *cursoActual; //Links to the class the group is in
    struct evaluaciones *evaluacionesEst; //Links to the evaluations the group has
    struct enlaceCurso *enlazarCurso; //Next group in the course

    grupo(int nNumGrupo, string nAbreviatura, int nCodigoNum){
        numGrupo = nNumGrupo;
        abreviatura = nAbreviatura;
        codigoNum = nCodigoNum;
        idCurso = (100*nCodigoNum) + nNumGrupo;

        cursoActual = NULL;
        evaluacionesEst = NULL;
        sigGrupo= NULL;
        enlazarCurso = NULL;
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
    int abreviatura;
    int presupuesto;
    semestre *sigSem;
    semestre *antSem;
    struct enlazarCharla *sigCharla;

    semestre(int nSemestre, int nAnno, int nCodigo, int nPresupuesto){
        numSemestre = nSemestre;
        anno = nAnno;
        abreviatura = nCodigo;
        presupuesto = nPresupuesto;
        listaCursos = NULL;
        sigSem = NULL;
        antSem = NULL;
    }
} *listaSemestres;

struct enlaceCurso{//Simple linked list
    struct grupo *sigGrupo; //Links to the course itself
    enlaceCurso *sig; //Orders the courses

    enlaceCurso(grupo *nSigGrupo){
        sigGrupo = nSigGrupo;
        sig = NULL;
    }
};

struct curso{ //Circular linked list 
    string nombre;      //Arquitectura de Computadores
    string abreviatura; //IC
    int codigoNum;      //3101
    
    curso *sigCurso;
    struct grupo *grupoCursando; //Links to a list of groups that're taking the class

    curso(string nNombre, string nAbv, int nCodigo){
        nombre = nNombre;
        abreviatura = nAbv;
        codigoNum = nCodigo;

        grupoCursando =  NULL;
        sigCurso      =  NULL;
    }

} *listaCursos;

struct evaluacionesEntregadas{//Simple linked list
    struct evaluacion *sigEvaluacion; //Links to the evaluations
    evaluacionesEntregadas *sig;
    
    evaluacionesEntregadas(evaluacion *nSigEv){
        sigEvaluacion   = nSigEv;
        sig             = NULL;
    }
};

struct evaluacion{//Simple linked list. Links to the different evaluations the group has 
    
    struct tarea    *sigTarea;
    struct examen   *sigExamen;
    struct proyecto *sigProyecto;
    struct gira     *sigGira;
    
    evaluacion *sigEv;

    evaluacion(tarea *nSigTarea, examen *nSigExamen, proyecto *nSigProyecto, gira *nSigGira){

        sigTarea=   nSigTarea;
        sigExamen = nSigExamen;
        sigProyecto=nSigProyecto;
        sigGira=    nSigGira;
        sigEv =     NULL;
    }
};

struct tarea{//Simple linked list.
    int     fechaEntrega; //Format: dd/mm/yyyy
    int     hora; //Format: militar, ie. 1600 = 4p.m
    string  idActividad; //Format: Tarea##, ie. Tarea#3
    bool    entregado = false; //If the student did it or not. Default is false. 

    tarea *sigTarea;
    
    tarea(int nFechaEntrega, string nIdActividad, int nHora, bool nEntregado){
        fechaEntrega=   nFechaEntrega;
        hora =          nHora;
        idActividad=    nIdActividad;
        entregado=      nEntregado;
        
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

struct enlaceCharla{
    struct charla *sigCharla; //Links to the course itself
    enlaceCharla *sig; //Orders the courses

    enlaceCharla(struct charla *nSigCharla){
        sigCharla= nSigCharla;
        sig = NULL;
    }
};

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

//-----------------------------------------------------------------------------------Methods


//------------------Periods' Methods---------------------------------
void menuAdminSemestre();

semestre* buscarSem(int nCodigo){
    semestre *temp = listaSemestres;
    while(temp != NULL){
        if(temp->abreviatura==nCodigo){
            return temp;
        }
        temp= temp->sigSem;
    }
    return NULL;
}

void insertarSemestre(){

    int annoS;
    cout<<"Ingrese el año del semestre: "<<endl;
    cin>>annoS;

    int semS;
    cout<<"Ingrese el semestre del año: "<<endl;
    cin>>semS;
    
    int presupuestoS;
    cout<<"Ingrese el presupuesto del semestre: "<<endl;
    cin>>presupuestoS;

    int codigoS;
    codigoS= 10*annoS+semS;

    semestre *nS = new semestre(semS, annoS, codigoS, presupuestoS);

    if(buscarSem(codigoS)!=NULL){
        cout<< "Ya existe un semestre con estas directrices."<<endl;
    }

    //if list is empty
    if(listaSemestres == NULL){
        cout<<"Lista vacia"<<endl;
        listaSemestres=nS;
        nS->sigSem=NULL;
        nS->antSem=NULL;
        cout<<"Semestre ingresado exitosamente."<<endl;
        menuAdminSemestre();
    }
    //Item goes first
    semestre *tempA= listaSemestres;
    if(tempA-> abreviatura> codigoS){
        cout<<"Primero"<< endl;
        nS->antSem= NULL;
        nS->sigSem= tempA;
        tempA-> antSem= nS;
        listaSemestres=nS;
        cout<<"Semestre ingresado exitosamente."<<endl;
        menuAdminSemestre();
    }
    //Item goes last
    semestre *tempB= listaSemestres;
    while(tempB->sigSem!= NULL){
        tempB= tempB-> sigSem;
    }
    if(tempB->abreviatura<codigoS){
        cout<<"Ultimo"<< endl;
        tempB->sigSem= nS;
        nS->antSem= tempB;
        nS-> sigSem= NULL;
        cout<<"Semestre ingresado exitosamente."<<endl;
        menuAdminSemestre();
    }
    //Item goes in between
    semestre *tempC= listaSemestres;
    while(tempC->sigSem!= NULL){
        if(tempC->abreviatura>codigoS){
            cout<<"Centro"<< endl;
            (tempC->antSem)->sigSem=nS;

            nS-> antSem= tempC-> antSem;
            nS-> sigSem= tempC;

            tempC->antSem= nS;
            cout<<"Semestre ingresado exitosamente."<<endl;
            menuAdminSemestre();
        }
        tempC= tempC->sigSem;
    }
    
    cout<<"El semestre ya se encuentra previamente registrado"<<endl;
    menuAdminSemestre();
}    

void modificarSemestre(){
    int annoS;
    cout<<"Ingrese el año del semestre: "<<endl;
    cin>>annoS;

    int semS;
    cout<<"Ingrese el semestre del año: "<<endl;
    cin>>semS;

    int codigoS;
    codigoS= 10*annoS+semS;

    semestre*nSem= buscarSem(codigoS);
    
    int nPresupuestoS;
    cout<<"Ingrese el nuevo presupuesto del semestre: "<<endl;
    cin>>nPresupuestoS;

    nSem->presupuesto= nPresupuestoS;
    cout<<"Presupuesto modificado correctamente."<<endl;

    menuAdminSemestre();
}

//------------------Courses' Methods---------------------------------

curso* buscarCurso(string codigo){
    string abv = codigo.substr(0,2);
    int numCurso = stoi(codigo.substr(2,4));
    if(listaCursos == NULL){
        return NULL;
    }
    else{
        curso *temp = listaCursos;
        do{
            if((temp->codigoNum == numCurso) && (temp->abreviatura == abv)){
                //cout<<"Encontrado: "<<temp->nombre<<endl;
                return temp;
            }
            temp = temp->sigCurso;
        }while(temp != listaCursos);
        return NULL;
    } 
}

void insertarCurso(){
    string nombreC;
    string abvC;//Abreviatura Curso 
    int codigoNumC;
    cout<<"Ingrese el nombre del curso: ";
    cin>>nombreC;
    cout<<"Ingrese la abreviatura del curso: ";
    cin>>abvC;
    cout<<"Ingrese el codigo del curso: ";
    cin>>codigoNumC;
    cout<<"Nombre: "<<nombreC<<"Abreviatura: "<<abvC<<"Codigo: "<<codigoNumC<<endl;
    curso *nC = new curso(nombreC, abvC, codigoNumC);
    if(listaCursos == NULL){
        cout<<"Lista vacia"<<endl;
        listaCursos=nC;
        nC->sigCurso=nC;
    }
    else{
        cout<<"No vacia"<<endl;
        nC->sigCurso = listaCursos;
        curso *temp = listaCursos;
        while(temp->sigCurso != listaCursos)
            temp = temp->sigCurso;
        temp->sigCurso = nC;
        nC->sigCurso = listaCursos;
        
        cout<<"Curso insertado existosamente"<<endl;
    }
}

void modificarCurso(){
    string codigo;
    cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
    cin>>codigo;

    curso* buscado = buscarCurso(codigo);
    
    if(buscado == NULL){
        cout<<"Elemento no encontrado"<<endl;
    }
    else{
        string nuevoNom;
        cout<<"Escriba el nuevo nombre: ";
        cin>>nuevoNom;
        buscado->nombre = nuevoNom;
        cout<<"Nombre del curso cambiado con exito"<<endl;
    } 
}

void eliminarCurso(){
    int codigoC;
    string abvC; //Abreviatura curso
    cout<<"Ingrese el codigo del curso a eliminar: "<<endl;
    cin>>codigoC;
    cout<<"Ingrese la abreviatura del curso a eliminar: "<<endl;
    cin>>abvC;
    if(listaCursos == NULL){
        cout<<"Lista vacia!"<<endl;
    }
    else{
        curso *temp = listaCursos;
        do{
            if(((temp->sigCurso)->codigoNum == codigoC) && ((temp->sigCurso)->abreviatura) == abvC){
                temp->sigCurso = (temp->sigCurso)->sigCurso;
                return;
            }
            temp = temp->sigCurso;
        }while(temp != listaCursos);
        cout<<"No se ha encontrado el curso"<<endl;
        return;
    } 
}

void mostrarCurso(){
    cout<<"Lista de cursos"<<endl;
    if(listaCursos == NULL){
        cout<<"Lista vacia!"<<endl;
    }
    else{
        curso *temp = listaCursos;
        do{
            cout<<temp->nombre<<endl;
            temp = temp->sigCurso;
        }while(temp != listaCursos);
    }
}


//------------------Students' Methods---------------------------------
estudiante* buscarEst(int carnetEst){
    //cout<<"t"<<endl;
    estudiante *temp = listaEstudiantes;
    while(temp != NULL){
        if (temp->carnet == carnetEst){
            //cout<< temp->carnet<<endl;
            //cout<<"u"<<endl;
            return temp;
        }
        temp = temp->sigEst;
    }
    //cout<<"v"<<endl;
    return NULL;
}

void menuAdminEst();

/*
void insertarEst(){
    int carnetEst;
    cout<< "Ingrese el carnet del estudiante por agregar:"<<endl;
    cin>> carnetEst;

    if((buscarEst(carnetEst)) != NULL){
        cout<<"El carnet ya se encuentra registrado bajo otro estudiante"<<endl;
        return;
    }
    else
    {
        string nombreEst;
        cout<< "Ingrese el nombre del estudiante por agregar: ";
        cin>> nombreEst;   

        estudiante*nEst = new estudiante(nombreEst, carnetEst);

        if(listaEstudiantes == NULL){//Lista vacia
            listaEstudiantes = nEst;
            cout<<"Lista vacia";
        }

        else if(carnetEst < (listaEstudiantes->carnet)){//Inicio de lista
            nEst->sigEst = listaEstudiantes;
            cout<<"Inicio de lista";
        }
        else{
            estudiante*temp = listaEstudiantes;

            while(temp != NULL){
                //En medio
                if((((temp->carnet) < carnetEst) && (((temp->sigEst)->carnet) > carnetEst))){
                    nEst->sigEst = temp->sigEst;
                    temp->sigEst = nEst;
                    cout<<"Medio";
                }
                //Final de la lista
                else if((temp->sigEst) == NULL){
                    temp->sigEst = nEst;
                    nEst->sigEst = NULL;
                    cout<<"Final";
                }
                temp = temp->sigEst;
            }
        }            
        cout<<"Estudiante ingresado exitosamente"<<endl;
    }
} 
*/

void insertarEst(){
    int carnetEst;
    cout<< "Ingrese el carnet del estudiante por agregar:"<<endl;
    cin>> carnetEst;
    //cout<<"i"<<endl;
    
        //cout<<"j"<<endl;
        string nombreEst;
        cout<< "Ingrese el nombre del estudiante por agregar: ";
        cin>> nombreEst;   

        estudiante*existe= buscarEst(carnetEst);
        //cout<<existe->carnet<<endl;
        if(existe != NULL){
            cout<<"El carnet ya se encuentra registrado bajo otro estudiante"<<endl;
            return;
        }
        //cout<<"Exitoso, no existe el estudiante"<<endl;
        estudiante*nEst= new estudiante(nombreEst, carnetEst);
        //Lista vacia
        if(listaEstudiantes==NULL){
            listaEstudiantes= nEst;
            nEst->sigEst=NULL;
            //cout<<"Lista vacia";
            menuAdminEst();
        }
        
        //Inicio de la lista
        //cout<<"Valorando primer elemento"<<endl;
        estudiante*primero=listaEstudiantes;
        //cout<<"b"<<endl;
        if(carnetEst< primero->carnet){
            //cout<<"e"<<endl;
            nEst->sigEst=listaEstudiantes;
            listaEstudiantes= nEst;
            //cout<<"Primer elemento insertado"<<endl;
            menuAdminEst();
        }

        //Final de la lista
        //cout<<"Valorando ultimo elemento"<<endl;
        estudiante*tempF= listaEstudiantes;
        //cout<<"c"<<endl;
        while(tempF->sigEst !=NULL){
            //cout<<"w"<<endl;
            tempF= tempF->sigEst;
        }
        //cout<<"a"<<endl;
        if(carnetEst> tempF->carnet){
            //cout<<"d"<<endl;
            tempF->sigEst= nEst;
            nEst->sigEst= NULL;
            //cout<<"ultimo elemento"<<endl;
        }
        
        //Media lista
        //cout<<"Valorando in elemento"<<endl;
        estudiante*temp= listaEstudiantes;
        while(temp->sigEst!=NULL){
            //cout<<"y"<<endl;
            if((temp->sigEst)->carnet > carnetEst){
                //cout<<"z"<<endl;
                nEst->sigEst= temp->sigEst;
                temp->sigEst= nEst;
                
                //cout<<"Elemento in lista"<<endl;
                menuAdminEst();
            }
            temp= temp->sigEst;
        }
        cout<<"Estudiante agregado exitosamente"<<endl;
}

void modificarEst(){
    
    int carnet;
    cout<<"\nIngrese el carnet del estudiante a modificar: ";
    cin>>carnet;
    estudiante*buscado = buscarEst(carnet);
    if(buscado == NULL){
        cout<<"\nEstudiante no encontrado"<<endl;
        return;
    }
    else{
        string nuevoNom;
        cout<<"\nIngrese el nuevo nombre del estudiante: ";
        cin>>nuevoNom;

        buscado->nombreEst = nuevoNom;
        cout<<"\nNombre de estudiante modificado con exito"<<endl;
        return;
    }
}

void eliminarEst(){

    int carnetEst;
    cout<<"\nIngrese el carnet del estudiante a eliminar: ";
    cin>>carnetEst;
    if(listaEstudiantes == NULL){
        cout<<"Lista Vacia"<<endl;
        return;
    }
    else{
        estudiante*buscar = buscarEst(carnetEst);
        if(buscar == NULL){
            cout<<"\nEstudiante no encontrado"<<endl;
            return;
        }
        else{
            if(listaEstudiantes->carnet == carnetEst){
                listaEstudiantes=listaEstudiantes->sigEst;
                return;
            }
            else{
                estudiante*temp = listaEstudiantes;
                estudiante*tempAnt;
                while(temp != NULL){
                    if(temp->carnet == carnetEst){
                        tempAnt->sigEst=temp->sigEst;
                        return;
                    }
                    tempAnt=temp;
                    temp=temp->sigEst;
                }
            }
        }
    }
}


//------------------Group's Methods----------------------------------

grupo* buscarGrupo(int nGrupo){
    grupo *temp = listaGrupos;
    while(temp != NULL){
        if(temp->codigoNum == nGrupo){
            return temp;
        }
        temp = temp->sigGrupo;
    }
    return NULL;
}

void insertarGrupo(){
    string codigo;
    cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
    cin>>codigo;

    curso* cursoG = buscarCurso(codigo);
    if(cursoG == NULL){
        cout<<"No se ha encontrado el curso"<<endl;
    }else{
        int numGrupo;
        cout<<"Ingrese el numero de grupo: ";
        cin>>numGrupo;

        string abv = codigo.substr(0,2);
        int numCurso = stoi(codigo.substr(2,4));

        struct grupo *nG = new grupo(numGrupo, abv, numCurso);
        //nG->sigGrupo = listaGrupos;//Lo agrego a los grupos
        //listaGrupos = nG;//Al inicio
        nG->cursoActual = cursoG;//Lo linkeo al curso que pertenece

        //enlaceCurso *nE = new enlaceCurso(nG);//Nuevo enlace
        nG->sigGrupo = cursoG->grupoCursando; //Inicio de la lista de grupos cursando el curso
        cursoG->grupoCursando = nG;

        cout<<"Grupo insertado con exito"<<endl;
    }

}

void reporteGrupo(){
    string codigo;
    cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
    cin>>codigo;

    curso* tempCurso = buscarCurso(codigo);

    cout<<"Nombre del curso: "<<tempCurso->nombre<<endl;
    cout<<"Grupos actuales: "<<endl;

    grupo *tempGrupo = tempCurso->grupoCursando;
    while(tempGrupo != NULL){
        cout<<"G"<<tempGrupo->numGrupo<<endl;
        cout<<"ID del curso: "<<tempGrupo->idCurso<<endl;
        tempGrupo = tempGrupo->sigGrupo;
    }
    cout<<"Fin de reporte"<<endl;

}


//------------------Admin Methods---------------------------------

administrador* buscarAdmin(string nombreA){
    administrador* temp = listaAdministradores;
    while(temp!= NULL){
        if (temp->usuario == nombreA)
            return temp;
        temp = temp->sigAdmin;
    }
    return NULL;
}

void insertarAdmin(string nombreA, string contrasennaA){
    
    administrador *nA = new administrador(nombreA, contrasennaA);
    nA->sigAdmin = listaAdministradores;
    listaAdministradores = nA;     
    cout<<"\nAdministrador insertado existosamente"<<endl;
}

void insertarAdminAux(){
    string nombreA;
    cout<<"Ingrese el nombre de usuario del nuevo administrador: ";
    cin>>nombreA;
    
    if((buscarAdmin(nombreA)) != NULL)
    {
        cout<<"El usuario ya se encuentra registrado"<<endl;
    }
    else
    {
    string contrasennaA;
    cout<<"Ingrese la contrasena del nuevo administrador: ";
    cin>>contrasennaA;

    insertarAdmin(nombreA, contrasennaA);
    }
}

//------------------Teachers' Methods---------------------------------

profesor* buscarProf(int cedulaP){
    profesor *temp = listaProfesores;
    while(temp != NULL){
        if (temp->cedulaProf == cedulaP)
            return temp;
        temp = temp->sigProf;
    }
    return NULL;
}

void insertarProf(){
    int cedulaP;
    cout<< "Ingrese la cedula del profesor a ingresar:"<<endl;
    cin>> cedulaP;

    if((buscarProf(cedulaP)) != NULL){
        cout<<"El profesor ya se encuentra registrado"<<endl;
    }
    else
    {
        string nombreP;
        cout<< "Ingrese el nombre del profesor a ingresar: ";
        cin>> nombreP;   

        profesor*nP = new profesor(nombreP, cedulaP);

        nP->sigProf = listaProfesores;

        if(listaProfesores != NULL)
            listaProfesores->antProf = nP;
        listaProfesores = nP;
        cout<<"\nProfesor insertado exitosamente"<<endl;
    } 
}

void modificarProf(){
    cout<< "Ingrese la cedula del profesor a modificar: "<<endl;
    int cedulaP;
    cin>> cedulaP;

    profesor *temp = buscarProf(cedulaP);
    
    if(temp == NULL){
        cout<<"\nEl profesor no existe, no se puede modificar"<<endl;
    }
    else{
        string nomProf;
        cout<<"Ingrese el nuevo nombre del profesor: "<<endl;
        cin>>nomProf;
        temp->nombreProf = nomProf;
        cout<<"Nombre del profesor modificado existosamente"<<endl;
    }
}

void eliminarProf(){
    cout<< "Ingrese la cedula del profesor a eliminar: "<<endl;
    int cedProf;
    cin>>cedProf;
    
    profesor *temp = buscarProf(cedProf);

    if(temp == NULL){
        cout<<"El profesor no existe, no se puede borrar"<<endl;
    }
    else{ //Eliminar inicio
        if(temp == listaProfesores){
            if(temp->sigProf == NULL)
                listaProfesores = NULL;
            else{
                listaProfesores = listaProfesores->sigProf;
                listaProfesores->antProf = NULL;
            }
        }
        else{//Recorrer lista
            if(temp->sigProf == NULL)//Ultimo
                temp->antProf->sigProf = NULL;
            else{//En medio
                temp->antProf->sigProf = temp->sigProf;
                temp->sigProf->antProf = temp->antProf;
            }
        }
        cout<<"Profesor eliminado exitosamente"<<endl;
    }
}


//------------------Printing Methods---------------------------------

void imprimirProfesores(){
    if(listaProfesores == NULL)
        cout<<"\nNo hay profesores en la lista"<<endl;
    else{
        profesor *temp = listaProfesores;
        cout<<"Lista de profesores: "<<endl;
        while(temp->sigProf != NULL){
            cout<<"Profesor: "<<temp->nombreProf<<", Cedula: " <<temp->cedulaProf<<endl;
            temp = temp->sigProf;
        }
        cout<<"Profesor: "<<temp->nombreProf<<", Cedula: " <<temp->cedulaProf<<endl;    
    }
}

void imprimirAdmins(){
    if(listaAdministradores == NULL)
        cout<<"\nNo hay administradores en la lista"<<endl;
    else{
        administrador *temp = listaAdministradores;
        cout<<"Lista de administradores: ";
        while(temp != NULL){
            cout<<temp->usuario<<", ";
            temp = temp->sigAdmin;
        }
        cout<<endl;
    }
}

void imprimirEstudiantes(){
    estudiante *temp = listaEstudiantes;
    cout<<"Lista de estudiantes: "<<endl;
    while(temp != NULL){
        cout<<"pasando al siguiente"<<endl;
        cout<<"Estudiante: "<<temp->nombreEst<<", Carnet: "<<temp->carnet<<endl;
        temp = temp->sigEst;
    }

}
void imprimirSemestres(){
    semestre *temp = listaSemestres;
    cout<<"Lista de semesetres: "<<endl;
    while(temp != NULL){
        cout<<"pasando al siguiente"<<endl;
        cout<<"Periodo: "<<temp->numSemestre<<", Año: "<<temp->anno<<endl;
        temp = temp->sigSem;
    }

}

//------------------Menus---------------------------------

void menuPrincipal();
void menuAdmin();

void menuAdminSemestre(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    
    cout<<"a- Insertar Semestre\nb- Modificar Semestre\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        insertarSemestre();
        menuAdminSemestre();
    }
    else if(opcion == "b"){
        modificarSemestre();
        menuAdminSemestre();
    }
    else if(opcion == "z"){
        imprimirSemestres();
        menuAdminSemestre();
    }
    else if(opcion == "1")
        menuAdmin();
    else if(opcion == "2")
        menuPrincipal();
    else{
        cout<<"Opcion Invalida"<<endl;
        menuAdminSemestre();
    }
}    

void menuAdminCurso(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    
    cout<<"a- Insertar curso\nb- Modificar curso\nc- Borrar curso\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        insertarCurso();
        menuAdminCurso();
    }
    else if(opcion == "b"){
        modificarCurso();
        menuAdminCurso();
    }
    else if(opcion == "c"){
        eliminarCurso();
        menuAdminCurso();
    }
    else if(opcion == "z"){
        mostrarCurso();
        menuAdminCurso();
    }
    else if(opcion == "1")
        menuAdmin();
    else if(opcion == "2")
        menuPrincipal();
    else{
        cout<<"Opcion Invalida"<<endl;
        menuAdminCurso();
    }
}    

void menuAdminEst(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    
    cout<<"a- Insertar estudiante\nb- Modificar estudiante\nc- Borrar estudiante\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        insertarEst();
        menuAdminEst();
    }
    else if(opcion == "b"){
        modificarEst();
        menuAdminEst();
    }
    else if(opcion == "c"){
        eliminarEst();
        menuAdminEst();
    }
    else if(opcion == "z"){
        imprimirEstudiantes();
        menuAdminEst();
    }
    else if(opcion == "1")
        menuAdmin();
    else if(opcion == "2")
        menuPrincipal();
    else{
        cout<<"Opcion Invalida"<<endl;
        menuAdminEst();
    }
}

void menuAdminProf(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Insertar profesor\nb- Modificar profesor\nc- Borrar profesor\n\n1-Volver al menu de administrador \n2-Volver al menu principal \nOpcion: ";
    string opcionMenuAdminProf;
    cin>> opcionMenuAdminProf;

    if (opcionMenuAdminProf== "a"){
        //cout<< "Insertar"<<endl;
        insertarProf();
    }else if(opcionMenuAdminProf=="b"){
        //cout<< "Modificar"<<endl;
        modificarProf();
        
    }else if(opcionMenuAdminProf=="c"){
        eliminarProf();
        //cout<< "Borrar"<<endl;

    }else if(opcionMenuAdminProf=="1"){
        //cout<<"Salir"<<endl;
        menuAdmin();
    }
    else if(opcionMenuAdminProf=="2"){
        menuPrincipal();
    }
    else if(opcionMenuAdminProf=="z"){
        imprimirProfesores();

    }else{
        cout<< "Ingrese una opcion valida"<<endl;
        menuAdminProf();
    }
    
    menuAdminProf();
}
void menuAdmin(){
    cout<<"\nEscoja e ingrese el caracter del objeto que desea modificar:"<<endl;
    cout<<"a- Insertar Administrador\nb- Profesores\nc- Estudiantes\nd- Semestres\ne- Cursos\nf- Insertar grupo\n\n0- Volver al menu principal\nOpcion: ";
    
    string opcionMenuAdmin;
    
    cin>> opcionMenuAdmin;
    
    if(opcionMenuAdmin =="a"){
        insertarAdminAux();
        menuAdmin();
    }
    else if(opcionMenuAdmin == "b"){
        //cout<< "Profesores"<<endl;
        menuAdminProf();
    }
    else if(opcionMenuAdmin == "c"){
        //cout<< "Estudiantes"<<endl;
        menuAdminEst();
    }
    else if(opcionMenuAdmin == "d"){
        menuAdminSemestre();
    }
    else if(opcionMenuAdmin == "e"){
        menuAdminCurso();
    }
    else if(opcionMenuAdmin == "f"){
        insertarGrupo();
        menuAdmin();
        //reporteGrupo();
    }
    else if(opcionMenuAdmin == "0"){
        menuPrincipal();
    }
    else if(opcionMenuAdmin == "z"){
        reporteGrupo();
        menuAdmin();
    }
    else{
        cout<<"Ingrese una opcion valida."<<endl;
        menuAdmin();
    }
}

void ingresarAdmin(){
    string nombreA;
    string contrasennaA;
    string opcion;
    administrador* temp = listaAdministradores;
    
    cout<<"Nombre de usuario: ";
    cin>>nombreA;

    if ((buscarAdmin(nombreA)) == NULL){
        cout<<"El usuario ingresado no existe. Si desea volver al menu principal digite 1"<<endl;
        cin>>opcion;
        if(opcion == "1"){
            menuPrincipal();
        }
        else{
            ingresarAdmin();
        }
    }
    else{
        cout<<"Contrasena: ";
        cin>>contrasennaA;
    
        temp = (buscarAdmin(nombreA));
        if ((temp->contrasenna != contrasennaA)){
            cout<<"Usuario o contrasena incorrecta"<<endl;
            menuPrincipal();
        }else{
            menuAdmin();
        }
    }
}

void menuPrincipal(){
    /*
    F: Displays the main menu for user to choose between Administrator or User.
    I: Number of choice.
    O: Respective function in the system.
    */
    cout<<"Bienvenido al sistema de Gestion de Actividades Curriculares"<<endl;
    cout<<"Ingrese el numero de la seccion deseada: \n 1- Administrador\n 2- Usuario \nNumero:";
    int opcion;
    cin>>opcion;
    if(opcion==1){
        //cout<<"Administrador: "<<endl;
        ingresarAdmin();
    }else if(opcion==2){
        cout<<"Usuario: "<<endl;
    }else{
        cout<<"Ingrese una opcion valida.";
        menuPrincipal();
    }
}

int main(){
    insertarAdmin("Maria", "123");
    insertarAdmin("Juan", "4567");
    insertarAdmin("Carlos", "930");
    imprimirAdmins();
    menuPrincipal();

    return 0;
}