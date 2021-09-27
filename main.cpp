/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado,       
             Brenda Badilla Rodriguez,  
*/

#include <iostream>
#include <string>
#include <ctime>

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

    struct enlaceCharla *charla;
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
    struct evaluacion *listaEvaluacion; //Links to the evaluations the group has
    struct enlaceCurso *enlazarCurso; //Next group in the course

    grupo(int nNumGrupo, string nAbreviatura, int nCodigoNum){
        numGrupo = nNumGrupo;
        abreviatura = nAbreviatura;
        codigoNum = nCodigoNum;
        idCurso = (100*nCodigoNum) + nNumGrupo;

        cursoActual = NULL;
        listaEvaluacion = NULL;
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



struct enlaceCurso{//Simple linked list
    struct curso *sigCurso; //Links to the course itself
    enlaceCurso *sig; //Orders the courses

    enlaceCurso(curso *nSigCurso){
        sigCurso = nSigCurso;
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
    int     fechaEntrega; //Format: yyyy/mm/dd
    int     hora; //Format: militar, ie. 1600 = 4p.m
    string idActividad; //Format: Tarea#, ie. Tarea3 Identificador
    string tipo;
    string numeroAct;     
    evaluacion *sigEv;
    int nota;                 //Percentage of the evaluation
    evaluacion(int fecha, int nHora, string nTipo, string nNumAct){
        fechaEntrega = fecha;
        hora = nHora;
        tipo = nTipo;
        numeroAct = nNumAct;
        idActividad = tipo.append(numeroAct);
        nota = 0;

        sigEv = NULL;
    }
};

struct charla{//Simple linked list 
    string nombreCharla;
    string idCharla;
    int fecha; //Format: yyyy/mm/dd
    int hora;  //Militar: 1630 = 4p.m
    //Duracion puede ser fija, evaluaciones tambien
    charla* sigCharla = NULL;
    charla(string nNombreCharla, int nFecha, int nHora, int semestre){
        nombreCharla= nNombreCharla;
        fecha= nFecha;
        hora = nHora;
        idCharla = (to_string(semestre)).append(nombreCharla);
    }

};

struct enlaceCharla{
    charla *enCharla; //Links to the course itself
    enlaceCharla *sig; //Orders the courses

    enlaceCharla(struct charla *nEnCharla){
        enCharla= nEnCharla;
        sig = NULL;
    }
};

struct semestre{ //Simple linked list 
    //struct curso *listaCursos; //Links to the list of courses given in that said semester
    int numSemestre;//1 o 2
    int anno;//2020
    int abreviatura;//20201
    int presupuesto;
    semestre *sigSem;
    semestre *antSem;
    charla *listaCharlas;
    enlaceCurso *listaCursos; //Links to the list of courses given in said semester
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

//-----------------------------------------------------------------------------------Methods

int pedirAnnoSem(){
    int annoS;
    cout<<"Ingrese el anno del semestre: "<<endl;
    cin>>annoS;   
    return annoS; 
}

int pedirNumSem(){
    int semS;
    cout<<"Ingrese el semestre del anno: "<<endl;
    cin>>semS;
    return semS;
}

int pedirpresupuestoSem(){
    int presupuestoS;
    cout<<"Ingrese el presupuesto del semestre: "<<endl;
    cin>>presupuestoS;
    return presupuestoS;    
}
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

void insertarSemestre(int annoS, int semS, int presupuestoS){
    int codigoS;
    codigoS= 10*annoS+semS;

    semestre *nS = new semestre(semS, annoS, codigoS, presupuestoS);

    if(buscarSem(codigoS)!=NULL){
        cout<< "Ya existe un semestre con estas directrices."<<endl;
    }

    //if list is empty
    if(listaSemestres == NULL){
        //cout<<"Lista vacia"<<endl;
        listaSemestres=nS;
        nS->sigSem=NULL;
        nS->antSem=NULL;
        cout<<"Semestre ingresado exitosamente."<<endl;
        return;
    }
    //Item goes first
    semestre *tempA= listaSemestres;
    if(tempA-> abreviatura> codigoS){
        //cout<<"Primero"<< endl;
        nS->antSem= NULL;
        nS->sigSem= tempA;
        tempA-> antSem= nS;
        listaSemestres=nS;
        cout<<"Semestre ingresado exitosamente."<<endl;
        return;
    }
    //Item goes last
    semestre *tempB= listaSemestres;
    while(tempB->sigSem!= NULL){
        tempB= tempB-> sigSem;
    }
    if(tempB->abreviatura<codigoS){
        //cout<<"Ultimo"<< endl;
        tempB->sigSem= nS;
        nS->antSem= tempB;
        nS-> sigSem= NULL;
        cout<<"Semestre ingresado exitosamente."<<endl;
        return;
    }
    //Item goes in between
    semestre *tempC= listaSemestres;
    while(tempC->sigSem!= NULL){
        if(tempC->abreviatura>codigoS){
            //cout<<"Centro"<< endl;
            (tempC->antSem)->sigSem=nS;

            nS-> antSem= tempC-> antSem;
            nS-> sigSem= tempC;

            tempC->antSem= nS;
            cout<<"Semestre ingresado exitosamente."<<endl;
            return;
        }
        tempC= tempC->sigSem;
    }
    cout<<"El semestre ya se encuentra previamente registrado"<<endl;
    return;
}    

/*
void insertarSem(int annoS, int semS, int presupuestoS){
    int codigo = 10*annoS + semS;

    semestre* buscar = buscarSem(codigo);
    if(buscar != NULL){
        cout<<"Semestre ya se encuentra registrado"<<endl;
        return;
    }else{  
        semestre* nS = new semestre(semS, annoS, codigo, presupuestoS);
        if(listaSemestres==NULL){//Empty list
            listaSemestres = nS;
            nS->sigSem = NULL;
            cout<<"Semestre insertado exitosamente!"<<endl;
            return;
        }else{//Beginning of the list
            semestre* tempSem = listaSemestres;
            if(codigo < tempSem->abreviatura){
                nS->sigSem = listaSemestres;
                listaSemestres = nS;
                cout<<"Semestre insertado satisfactoriamente!"<<endl;
            }

        }
    }

    

}
*/

/*

        
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
*/

void insertarSemestreAux(){
    int annoS = pedirAnnoSem();
    int semS = pedirNumSem();
    int presupuestoS = pedirpresupuestoSem();
    insertarSemestre(annoS, semS, presupuestoS);
}

void modificarSemestre(int codigoS){
    semestre*nSem= buscarSem(codigoS);
    
    int nPresupuestoS;
    cout<<"Ingrese el nuevo presupuesto del semestre: "<<endl;
    cin>>nPresupuestoS;

    nSem->presupuesto= nPresupuestoS;
    cout<<"Presupuesto modificado correctamente."<<endl;
}

void modificarSemestreAux(){
    int annoS = pedirAnnoSem();
    int semS = pedirNumSem();
    int codigoS = 10*annoS+semS;
    modificarSemestre(codigoS);  
}

curso* buscarCurso(string codigo);

void relacionarCurso(int codSem){   
    semestre* tempS = buscarSem(codSem);         //Revisamos si semestre existe
    if(tempS == NULL){
        cout<<"Semestre no encontrado"<<endl;
        return;
    }
    else{                                       //Revisamos si curso existe
        string codigo;
        cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
        cin>>codigo;

        curso* tempC = buscarCurso(codigo);
        if(tempC == NULL){
            cout<<"Curso no encontrado"<<endl;
            return;
        }
        else{                               //Semestre y curso existen, enlace
            enlaceCurso* nE = new enlaceCurso(tempC); //Creo el nuevo enlace
            nE->sig = tempS->listaCursos;           //Que apunte al primer elemento de la lista de cursos de semestre
            tempS->listaCursos = nE;                //Insercion al inicio de lista simple
            cout<<"\nCurso asignado satisfactoriamente"<<endl;
        }
    }
}

void relacionarCursoAux(){
    int annoS = pedirAnnoSem();
    int semS = pedirNumSem();
    int codigoS = 10*annoS+semS;
    relacionarCurso(codigoS);
}

int pedirCodigoSem(){
    int codigoS;
    cout<<"Inserte el codigo del semestre (Ej. 20201): ";
    cin>>codigoS;
    return codigoS;
}

void reporteCursosSem(){
    int codigoS = pedirCodigoSem();
    semestre* tempSem = buscarSem(codigoS);
    if(tempSem == NULL){
        cout<<"Semestre no encontrado"<<endl;
        return;
    }
    else{
        cout<<"Anno: "<<tempSem->anno<<" Semestre: "<<tempSem->numSemestre<<endl;
        cout<<"Cursos: "<<endl;
        enlaceCurso* tempCurso = tempSem->listaCursos;
        while(tempCurso != NULL){
            cout<<"Nombre: "<<tempCurso->sigCurso->nombre<<endl;
            cout<<"Codigo: "<<tempCurso->sigCurso->abreviatura<<tempCurso->sigCurso->codigoNum<<endl;
            tempCurso = tempCurso->sig;
        }
        cout<<"\nFinal de reporte"<<endl;
    }

}

/*
    if(tempEst == NULL){
        cout<<"Estudiante no encontrado"<<endl;
        return;
    }else{
        cout<<"Grupos asignados: "<<endl;
        cout<<"Estudiante: "<<tempEst->nombreEst<<" Carnet: "<<tempEst->carnet<<endl;
        enlazarGrupo* tempG = tempEst->gruposEstAux;
        while(tempG != NULL){
            cout<<"G"<<tempG->enlaceGrupo->numGrupo<<endl;
            cout<<"Curso: "<<tempG->enlaceGrupo->cursoActual->nombre<<endl;
            cout<<"ID de grupo: "<<tempG->enlaceGrupo->idCurso<<endl;
            tempG = tempG->sigEn;
        }
        cout<<"\nFinal de reporte"<<endl;
    }    
*/

//------------------Courses' Methods---------------------------------

string pedirNomCurso(){
    string nombreC;
    cout<<"Ingrese el nombre del curso: ";
    cin>>nombreC;
    return nombreC;
}

string pedirAbvCurso(){
    string abvC;
    cout<<"Ingrese la escuela del curso (Ej. IC, MA..): ";
    cin>>abvC;
    return abvC;
}

int pedirCodCurso(){
    int codigoC;
    cout<<"Ingrese el codigo del curso (Ej. 3101): ";
    cin>>codigoC;
    if(cin.fail()){
        cout<<"Solo ingresar un numero de cuatro digitos: ";
        pedirCodCurso();
        return 0;
    }else{
        return codigoC;
    }
}

string pedirCodigoCurso(){
    string codigo;
    cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
    cin>>codigo;
    return codigo;
}

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

void insertarCurso(string nombreC, string abv, int codigoNumC){
    curso *nC = new curso(nombreC, abv, codigoNumC);
    if(listaCursos == NULL){
        listaCursos=nC;
        nC->sigCurso=nC;
        cout<<"Curso insertado existosamente"<<endl;
    }
    else{
        nC->sigCurso = listaCursos;
        curso *temp = listaCursos;
        while(temp->sigCurso != listaCursos)
            temp = temp->sigCurso;
        temp->sigCurso = nC;
        nC->sigCurso = listaCursos;
        
        cout<<"Curso insertado existosamente"<<endl;
    }
}

void insertarCursoAux(){
    string nombreC = pedirNomCurso();
    string abvC = pedirAbvCurso();
    int codigo = pedirCodCurso();

    insertarCurso(nombreC, abvC, codigo);
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

void eliminarCurso(int codigoC, string abvC){
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

void eliminarCursoAux(){
    string abv = pedirAbvCurso();
    int codigo = pedirCodCurso();

    eliminarCurso(codigo, abv); 
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
int pedirCarnetEst(){
    int carnetEst;
    cout<<"Ingrese el carnet del estudiante: ";
    cin>>carnetEst;
    return carnetEst;
}

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

void insertarEst(int carnetEst, string nombreEst){

    estudiante*nEst= new estudiante(nombreEst, carnetEst);
    //Lista vacia
    if(listaEstudiantes==NULL){
        listaEstudiantes= nEst;
        nEst->sigEst=NULL;
        //cout<<"Lista vacia";
        cout<<"Estudiante agregado satisfactoriamente"<<endl;
        return;
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
        cout<<"Estudiante agregado satisfactoriamente"<<endl;
        return;
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
        cout<<"Estudiante agregado satisfactoriamente"<<endl;
        return;
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
            
            cout<<"Estudiante agregado satisfactoriamente"<<endl;
            return;
        }
        temp= temp->sigEst;
    }
    //cout<<"Estudiante agregado exitosamente"<<endl;
}


void insertarEstAux(){
    int carnetEst = pedirCarnetEst();

    estudiante*existe= buscarEst(carnetEst);
    //cout<<existe->carnet<<endl;
    if(existe != NULL){
        cout<<"El carnet ya se encuentra registrado bajo otro estudiante"<<endl;
        return;
    }else{
        string nombreEst;
        cout<< "Ingrese el nombre del estudiante por agregar: ";
        cin>> nombreEst;   

        insertarEst(carnetEst, nombreEst);
    }
}

void modificarEst(){
    
    int carnet = pedirCarnetEst();
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

void eliminarEst(){//Delete on simple linked list

    int carnetEst = pedirCarnetEst();
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

grupo* encontrarGrupo(string codigo, int numGrupo);

void relacionarGrupoEst(estudiante* tempE, grupo* tempG){
    enlazarGrupo* nE = new enlazarGrupo(tempG);
    nE->sigEn = tempE->gruposEstAux;
    tempE->gruposEstAux = nE;
    cout<<"Estudiante asignado a grupo satisfactoriamente"<<endl;
    return;
}

int pedirNumGrupo();

void relacionarGrupoEstAux(){
    int carnetEst = pedirCarnetEst();

    estudiante* tempE = buscarEst(carnetEst);

    if(tempE == NULL){
        cout<<"Estudiante no encontrado"<<endl;
        return;
    }
    
    string codigo = pedirCodigoCurso();
    int numG = pedirNumGrupo();

    grupo* tempG = encontrarGrupo(codigo, numG);
    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }else{
        relacionarGrupoEst(tempE, tempG);
    }
}

void borrarGrupoEst(){
    if(listaEstudiantes == NULL){
        cout<<"No hay estudiantes registrados"<<endl;
        return;
    }else{
        int carnetEst = pedirCarnetEst();
        estudiante* tempEst = buscarEst(carnetEst);
        if(tempEst == NULL){
        cout<<"Estudiante no encontrado"<<endl;
        return;
        }else{
            string codigo;
            int numG;

            cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
            cin>>codigo;

            cout<<"Ingrese el numero de grupo: ";
            cin>>numG;

            grupo* tempG = encontrarGrupo(codigo, numG);
            if(tempG == NULL){
                cout<<"Grupo no encontrado"<<endl;
                return;
            }else{//Group and student exist
                int idG = 100*(stoi(codigo.substr(2,4))) + numG;
                if(tempEst->gruposEstAux->enlaceGrupo->idCurso == idG){//Delet the beginning of the list
                    tempEst->gruposEstAux = tempEst->gruposEstAux->sigEn; 
                    cout<<"Curso desvinculado del estudiante exitosamente"<<endl;
                    return;
                }else{                                                  //Delete middle or end of list
                    enlazarGrupo* tempEn = tempEst->gruposEstAux;
                    while(tempEn->sigEn != NULL){
                        if(tempEn->sigEn->enlaceGrupo->idCurso == idG){
                            tempEn->sigEn = tempEn->sigEn->sigEn;
                            cout<<"Curso desvinculado del estudiante exitosamente"<<endl;
                            return;
                        }
                        tempEn = tempEn->sigEn;
                    }
                    cout<<"Ha occurrido un error al desvincular el grupo"<<endl;
                }
            
            }

        }   

    }

}

void reporteGruposEst(){
    int carnetEst;
    cout<<"Escriba el carnet del estudiante: "<<endl;
    cin>>carnetEst;

    estudiante* tempEst = buscarEst(carnetEst);

    if(tempEst == NULL){
        cout<<"Estudiante no encontrado"<<endl;
        return;
    }else{
        cout<<"Grupos asignados: "<<endl;
        cout<<"Estudiante: "<<tempEst->nombreEst<<" Carnet: "<<tempEst->carnet<<endl;
        enlazarGrupo* tempG = tempEst->gruposEstAux;
        while(tempG != NULL){
            cout<<"G"<<tempG->enlaceGrupo->numGrupo<<endl;
            cout<<"Curso: "<<tempG->enlaceGrupo->cursoActual->nombre<<endl;
            cout<<"ID de grupo: "<<tempG->enlaceGrupo->idCurso<<endl;
            tempG = tempG->sigEn;
        }
        cout<<"\nFinal de reporte"<<endl;
    }    
}

//------------------Group's Methods----------------------------------

void insertarGrupo(string codigo, curso* cursoG, int numGrupo){

    string abv = codigo.substr(0,2);
    int numCurso = stoi(codigo.substr(2,4));
    
    struct grupo *nG = new grupo(numGrupo, abv, numCurso);
    
    nG->cursoActual = cursoG; //Lo linkeo al curso que pertenece
    nG->sigGrupo = cursoG->grupoCursando;
    cursoG->grupoCursando = nG;
    
    cout<<"Grupo insertado con exito"<<endl;

}

void insertarGrupoAux(){
    string codigo = pedirCodigoCurso();

    curso* cursoG = buscarCurso(codigo);
    if(cursoG == NULL){
        cout<<"No se ha encontrado el curso"<<endl;
    }else{
        int numGrupo;
        cout<<"Ingrese el numero de grupo: ";
        cin>>numGrupo;

        insertarGrupo(codigo, cursoG, numGrupo);
    }
}

void reporteGrupo(){
    string codigo = pedirCodigoCurso();

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

grupo* encontrarGrupo(string codigo, int numGrupo){

    curso* tempCurso = buscarCurso(codigo);

    grupo *tempGrupo = tempCurso->grupoCursando;

    while(tempGrupo != NULL){
        if(tempGrupo->numGrupo == numGrupo)
            return tempGrupo;
        tempGrupo = tempGrupo->sigGrupo;
    }
    return NULL;
}

grupo* buscarGrupoEst(int carnetEst, int codG){
    estudiante* tempEst = buscarEst(carnetEst);

    if(tempEst == NULL){
        return NULL;
    }else{
        if(tempEst->gruposEstAux == NULL){
            return NULL;
        }else{
            enlazarGrupo* tempG = tempEst->gruposEstAux;
            while(tempG->enlaceGrupo != NULL){
                if(tempG->enlaceGrupo->idCurso = codG){
                    return tempG->enlaceGrupo;
                }
                tempG = tempG->sigEn;
            }
            return NULL;
        }
    }    
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
    cout<<"Administrador insertado existosamente"<<endl;
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

int pedirCedulaProf(){
    int cedulaP;
    cout<<"Ingrese la cedula del profesor: ";
    cin>>cedulaP;
    return cedulaP;
}

profesor* buscarProf(int cedulaP){
    profesor *temp = listaProfesores;
    while(temp != NULL){
        if (temp->cedulaProf == cedulaP)
            return temp;
        temp = temp->sigProf;
    }
    return NULL;
}

string pedirNombreProf(){
    string nombreProf;
    cout<<"Ingrese el nombre del profesor: ";
    cin>>nombreProf;
    return nombreProf;
}

void insertarProf(int cedulaP, string nombreP){

    profesor*nP = new profesor(nombreP, cedulaP);
    
    nP->sigProf = listaProfesores;
    
    if(listaProfesores != NULL)
        listaProfesores->antProf = nP;
    
    listaProfesores = nP;
    cout<<"\nProfesor insertado exitosamente"<<endl;
}

void insertarProfAux(){
    int cedulaP = pedirCedulaProf();

    if((buscarProf(cedulaP)) != NULL){
        cout<<"El profesor ya se encuentra registrado"<<endl;
        return;
    }
    else
    {
        string nombre = pedirNombreProf();
        insertarProf(cedulaP, nombre);
    }
}

void modificarProf(){
    int cedulaP = pedirCedulaProf();
    profesor *temp = buscarProf(cedulaP);
    
    if(temp == NULL){
        cout<<"\nEl profesor no existe, no se puede modificar"<<endl;
    }
    else{
        string nomProf = pedirNombreProf();
        temp->nombreProf = nomProf;
        cout<<"Nombre del profesor modificado existosamente"<<endl;
    }
}

void eliminarProf(){
    int cedProf = pedirCedulaProf();
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

int pedirNumGrupo(){
    int numGrupoBuscar;
    cout<<"Ingrese el numero del grupo por buscar: ";
    cin>> numGrupoBuscar;
    return numGrupoBuscar;
}
void relacionarGrupoProf(profesor* tempP, grupo* tempG){
    enlazarGrupo* nE = new enlazarGrupo(tempG);
    nE->sigEn = tempP->gruposProfAux;
    tempP->gruposProfAux = nE;
    cout<<"\nProfesor asignado a grupo satisfactoriamente"<<endl;

}

void relacionarGrupoProfAux(){
    int cedulaP = pedirCedulaProf();

    profesor* tempP = buscarProf(cedulaP);

    if(tempP == NULL){
        cout<<"Profesor no encontrado"<<endl;
        return;
    }
    
    string codigo = pedirCodigoCurso();
    int numG = pedirNumGrupo();

    grupo* tempG = encontrarGrupo(codigo, numG);
    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }

    relacionarGrupoProf(tempP, tempG);
}

void borrarGrupoProf(){
    if(listaProfesores == NULL){
        cout<<"No hay profesores registrados"<<endl;
        return;
    }else{
        int cedulaP = pedirCedulaProf();
        profesor* tempProf = buscarProf(cedulaP);

        if(tempProf == NULL){
        cout<<"Profesor no encontrado"<<endl;
        return;
        }else{
            string codigo;
            int numG;

            cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
            cin>>codigo;

            cout<<"Ingrese el numero de grupo: ";
            cin>>numG;

            grupo* tempG = encontrarGrupo(codigo, numG);
            if(tempG == NULL){
                cout<<"Grupo no encontrado"<<endl;
                return;
            }else{//Group and student exist
                int idG = 100*(stoi(codigo.substr(2,4))) + numG;
                if(tempProf->gruposProfAux->enlaceGrupo->idCurso == idG){//Delet the beginning of the list
                    tempProf->gruposProfAux = tempProf->gruposProfAux->sigEn; 
                    cout<<"Curso desvinculado del estudiante exitosamente"<<endl;
                    return;
                }else{                                                  //Delete middle or end of list
                    enlazarGrupo* tempEn = tempProf->gruposProfAux;
                    while(tempEn->sigEn != NULL){
                        if(tempEn->sigEn->enlaceGrupo->idCurso == idG){
                            tempEn->sigEn = tempEn->sigEn->sigEn;
                            cout<<"Curso desvinculado del estudiante exitosamente"<<endl;
                            return;
                        }
                        tempEn = tempEn->sigEn;
                    }
                    cout<<"Ha occurrido un error al desvincular el grupo"<<endl;
                }
            
            }

        }   

    }

}

void reporteGruposProfe(){
    int cedulaP = pedirCedulaProf();

    profesor* tempP = buscarProf(cedulaP);

    if(tempP == NULL){
        cout<<"Profesor no encontrado"<<endl;
        return;
    }else{
        cout<<"Grupos asignados: "<<endl;
        cout<<"Profesor: "<<tempP->nombreProf<<" Cedula: "<<tempP->cedulaProf<<endl;
        enlazarGrupo* tempG = tempP->gruposProfAux;
        while(tempG != NULL){
            cout<<"G"<<tempG->enlaceGrupo->numGrupo<<endl;
            cout<<"Curso: "<<tempG->enlaceGrupo->cursoActual->nombre<<endl;
            cout<<"ID de grupo: "<<tempG->enlaceGrupo->idCurso<<endl;
            tempG = tempG->sigEn;
        }
        cout<<"\nFinal de reporte"<<endl;
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
        //cout<<"pasando al siguiente"<<endl;
        cout<<"Periodo: "<<temp->numSemestre<<", Anno: "<<temp->anno<<", Presupuesto: "<<temp->presupuesto<<" millones de colones"<<endl;
        temp = temp->sigSem;
    }

}

//------------------------------------------------Evaluation's Methods---------------------------

/*
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
*/
void menuPrincipal();
void menuProfesor();

void ingresarProfesor(){
    string nombreP = pedirNombreProf();
    int cedulaProf = pedirCedulaProf();
    string opcion;
    
    profesor* tempProf = buscarProf(cedulaProf);

    if(tempProf == NULL){
        cout<<"Usuario no encontrado"<<endl;
    }
    else{
        if (nombreP != tempProf->nombreProf){
            cout<<"Usuario o contrasenna incorrectos /nDesea volver al menu principal? (S/n): "; 
            cin>>opcion;
            if(opcion == "S"){
                menuPrincipal();
            }else{
                ingresarProfesor();
            }
        }else{
            menuProfesor();
        }
    }

}

grupo* buscarGrupoProfe(int cedulaP, string codCurso){
    profesor* tempP = buscarProf(cedulaP);

    if(tempP == NULL){
        cout<<"Profesor no encontrado"<<endl;
        return NULL;
    }else{
        enlazarGrupo* tempG = tempP->gruposProfAux;
        if(buscarCurso(codCurso) == NULL){
            cout<<"Curso no encontrado"<<endl;
            return NULL;
        }
        else{
            int numG = pedirNumGrupo();
            int idG = 100*(stoi(codCurso.substr(2,4))) + numG;
            while(tempG != NULL){
                if(tempG->enlaceGrupo->idCurso == idG){
                    return tempG->enlaceGrupo;
                }
                tempG = tempG->sigEn;
            }
            cout<<"Grupo no encontrado"<<endl;
            return NULL;
        } 
    }    
}


string pedirTipoAct(){
    string tipoAct;
    string opcion;
    cout<<"\nIngrese el numero correspondiente al tipo de actividad: \n1-Tarea\n2-Proyecto\n3-Examen\n4-Giras\nOpcion: ";
    cin>>opcion;
    if(opcion=="1"){
        tipoAct = "Tarea";
    }else if(opcion=="2"){
        tipoAct = "Proyecto";
    }else if(opcion=="3"){
        tipoAct = "Examen";
    }else if(opcion=="4"){
        tipoAct = "Gira";
    }else{
        cout<<"Ingrese una opción valida por favor.";
        pedirTipoAct();
    }
    return tipoAct;
}

string pedirNumAct(){
    string num;
    cout<<"Ingrese el numero de actividad: ";
    cin>>num;
    return num;
}

int pedirFechaAct(){
    int anno;
    int mes;
    int dia;
    cout<<"Dia de entrega: ";
    cin>>dia;
    cout<<"-1 Enero\n-2 Febrero\n-3 Marzo\n-4 Abril\n-5 Mayo\n-6 Junio\n-7 Julio\n-8 Agosto\n-9 Setiembre\n-10 Octubre\n-11 Noviembre\n-12 Diciembre\nIngrese el numero del mes: ";
    cin>>mes;
    cout<<"Anno de entrega: ";
    cin>>anno;
    
    int codigo;
    codigo= anno*10000 + mes*100 + dia;
    
    return codigo;
}

int pedirHoraAct(){
    int hora;
    cout<<"Ingrese la hora de entrega (Formato militar. Ejemplo: 1600 (4:00p.m.)): ";
    cin>>hora;
    return hora;
}

int pedirNota(){
    int nota;
    cout<<"Ingrese la nota del estudiante: ";
    cin>>nota;
    return nota;
}

string mostrarMesAct(evaluacion* actividad){
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Setiembre", "Octubre", "Noviembre", "Diciembre"};
    string mes = meses[(((actividad->fechaEntrega)%10000)/100)-1];
    return mes;
}

int calcularMesAct(evaluacion* actividad){
    int mes = ((actividad->fechaEntrega)%10000)/100;
    return mes;
}

int calcularDiaAct(evaluacion* actividad){
    int dia = (actividad->fechaEntrega)%100;
    return dia;
}

int calcularAnnoAct(evaluacion* actividad){
    int anno = (actividad->fechaEntrega)/10000;
    return anno;
}

int calcularSemAct(evaluacion* actividad){
    int anno = calcularAnnoAct(actividad);
    int mes = calcularMesAct(actividad);
    int dia = calcularDiaAct(actividad);
    
    tm date={};
    date.tm_year=anno-1900;
    date.tm_mon=mes-1;
    date.tm_mday=dia;
    mktime(&date);

    return ((date.tm_yday-date.tm_wday+7)/7);
}

/*
void insertarActividad(){
    grupo* tempG = buscarGrupoProfe();

    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }
    else{
        string tipoAct = pedirTipoAct();
        string numAct = pedirNumAct();        
        int fechaAct = pedirFechaAct();
        int horaAct = pedirHoraAct();
        
        evaluacion* nEv = new evaluacion(fechaAct, horaAct, tipoAct, numAct);
        
        if(tempG->listaEvaluacion == NULL){//Empty list
            tempG->listaEvaluacion = nEv;
            cout<<"Actividad creada con exito vacia"<<endl;
            return;
        }else{
            evaluacion* tempEv = tempG->listaEvaluacion;
            cout<<tempEv->fechaEntrega<<" vs "<<nEv->fechaEntrega<<endl;
            if(tempEv->fechaEntrega > nEv->fechaEntrega){//Insert beginning of linked list
                cout<<tempEv->fechaEntrega<<" > "<<nEv->fechaEntrega<<endl;
                nEv->sigEv = tempEv;
                tempEv = nEv;
                cout<<"Actividad creada con exito inicio"<<endl;
                return;
            }
            while(tempEv->sigEv != NULL){
                tempEv = tempEv->sigEv;
            }
            if(tempEv->fechaEntrega < nEv->fechaEntrega){
                cout<<tempEv->fechaEntrega<<" < "<<nEv->fechaEntrega<<endl;
                tempEv->sigEv = nEv;
                nEv->sigEv = NULL;
                cout<<"Actividad creada con exito al final"<<endl;
                return;
            }
            evaluacion* temp = tempG->listaEvaluacion;
            while(tempEv->sigEv != NULL){
                if(temp->sigEv->fechaEntrega > nEv->fechaEntrega){
                    cout<<tempEv->fechaEntrega<<" > "<<nEv->fechaEntrega<<endl;
                    nEv->sigEv = temp->sigEv;
                    temp->sigEv = nEv;
                    cout<<"Actividad creada con exito en el medio"<<endl;
                    return;
                }
                temp = temp->sigEv;
            }
            cout<<"Algo paso"<<endl;
        }        
    }
}
*/
void insertarActProf(grupo* tempG, string tipoAct, string numAct, int fechaAct, int horaAct){
    evaluacion* nEv = new evaluacion(fechaAct, horaAct, tipoAct, numAct);
    
    if(tempG->listaEvaluacion == NULL){//Empty list
        tempG->listaEvaluacion = nEv;
        nEv->sigEv = NULL;
        cout<<"Actividad creada con exito"<<endl;
        return;
    }else{
        evaluacion* tempEv = tempG->listaEvaluacion;
        
        if(nEv->fechaEntrega < tempEv->fechaEntrega){//Insert beginning of linked list
            nEv->sigEv = tempG->listaEvaluacion;
            tempG->listaEvaluacion = nEv;
            cout<<"Actividad creada con exito"<<endl;
            return;
        }
        else{
            while((tempEv->sigEv != NULL) && (tempEv->sigEv->fechaEntrega < nEv->fechaEntrega)){//Insert in the middle or the end
                tempEv = tempEv->sigEv;
            }
            nEv->sigEv = tempEv->sigEv;
            tempEv->sigEv = nEv;
            cout<<"Actividad creada con exito"<<endl;
            return;
        }
    }        
}

void insertarActProfAux(){
    int cedulaProf = pedirCedulaProf();
    string codigoCurso = pedirCodigoCurso();
    
    grupo* tempG = buscarGrupoProfe(cedulaProf, codigoCurso);

    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }
    else{
        string tipoAct = pedirTipoAct();
        string numAct = pedirNumAct();        
        int fechaAct = pedirFechaAct();
        int horaAct = pedirHoraAct();

        insertarActProf(tempG, tipoAct, numAct, fechaAct, horaAct);
    }
}

evaluacion* buscarEvaluacionProf(string idAct, int cedulaP, string codCurso){

    grupo* tempG = buscarGrupoProfe(cedulaP, codCurso);

    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return NULL;
    }
    else{
        evaluacion *tempEv = tempG->listaEvaluacion;
        while(tempEv != NULL){
            if(tempEv->idActividad == idAct){
                return tempEv;
            }
            tempEv = tempEv->sigEv;
        }
        return NULL;
    }
}

void modificarActProf(){
    int cedulaP = pedirCedulaProf();
    string codCurso = pedirCodigoCurso();
    string tipo = pedirTipoAct();
    string numAct = pedirNumAct();
    string idAct = tipo.append(numAct);
    
    evaluacion* tempEv = buscarEvaluacionProf(idAct, cedulaP, codCurso);
    
    if(tempEv == NULL){
        cout<<"Actividad no encontrada"<<endl;
    }else{
        int nNota = pedirNota();
        tempEv->nota = nNota;
        cout<<"\nNota de la actividad cambiada con exito"<<endl;
    }   
}

void borrarActProf(){    
    int cedulaP = pedirCedulaProf();
    string codCurso = pedirCodigoCurso();
    grupo* tempG = buscarGrupoProfe(cedulaP, codCurso);

    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }
    else{//Agregar si la lista de actividades esta vacia
        string tipo = pedirTipoAct();
        string numAct = pedirNumAct();
        string idAct = tipo.append(numAct);
        if(tempG->listaEvaluacion->idActividad == idAct){
            tempG->listaEvaluacion = tempG->listaEvaluacion->sigEv;
            cout<<"Actividad eliminada con exito"<<endl;
            return;
        }else{
            evaluacion *tempEv = tempG->listaEvaluacion;
            evaluacion *tempAnt;
            while(tempEv != NULL){
                if(tempEv->idActividad == idAct){
                    tempAnt->sigEv = tempEv->sigEv;
                    cout<<"Actividad eliminada con exito"<<endl;
                }
                tempAnt = tempEv;
                tempEv = tempEv->sigEv;
            }
        }
    }
}

void imprimirActProf(){
    int cedulaP = pedirCedulaProf();
    string codCurso = pedirCodigoCurso();
    grupo* tempG = buscarGrupoProfe(cedulaP, codCurso);
    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }
    else{
        evaluacion* tempEv = tempG->listaEvaluacion;
        cout<<"Actividades: "<<endl;
        while(tempEv != NULL){
            cout<<"Tipo: "<<tempEv->tipo<<" Numero: "<<tempEv->numeroAct<< " Fecha de Entrega: "<<tempEv->fechaEntrega<<" Hora: "<<tempEv->hora<<endl;
            tempEv = tempEv->sigEv;
        }
        cout<<"Fin de reporte"<<endl;
    }
}

//-------------------------------------------------------Conferences' Methords--------

string pedirNomCharla(){
    string nom;
    cout<<"Ingrese el nombre de la charla: ";
    cin>>nom;
    return nom;
}

charla* buscarCharla(int codigoS, string idCh){
    semestre* tempSem = buscarSem(codigoS);
    if(tempSem == NULL){
        return NULL;
    }else{
        if(tempSem->listaCharlas == NULL){
            return NULL;
        }
        charla* tempCh = tempSem->listaCharlas;
        while(tempCh != NULL){
            if(tempCh->idCharla == idCh){
                return tempCh;
            }
            tempCh = tempCh->sigCharla;
        }
        return NULL;
    }
}

void insertarCharlaProf(semestre* tempSem, string nomCh, int fechaCh, int horaCh){//Inserts conference on semester
    charla* nCh = new charla(nomCh, fechaCh, horaCh, tempSem->abreviatura);
    
    if(tempSem->listaCharlas == NULL){//Empty list
        tempSem->listaCharlas = nCh;
        nCh->sigCharla = NULL;
        cout<<"Charla creada con exito"<<endl;
        return;
    
    }else{//There're conferences in the list, we must go through it 
        charla* tempCh = tempSem->listaCharlas;

        if(nCh->fecha < tempCh->fecha){//Sonner than the first date, goes in the beginning of the list
            nCh->sigCharla = tempSem->listaCharlas;
            tempSem->listaCharlas = nCh;
            cout<<"Charla creada con exito"<<endl;
            return;
        
        }else{//Either the middle or the end of the list
            
            //Find the element right before the one the conference is later, or the end of the list
            while((tempCh->sigCharla != NULL)&&(tempCh->sigCharla->fecha < nCh->fecha)){
                tempCh = tempCh->sigCharla;
            }
            
            nCh->sigCharla = tempCh->sigCharla;
            tempCh->sigCharla = nCh;
            cout<<"Actividad creada con exito"<<endl;
            return;
        }
    }
}

void insertarChProfAux(){
    int codigoS = pedirCodigoSem();//20201
    semestre* tempSem = buscarSem(codigoS);
    
    if(tempSem == NULL){
        cout<<"Semestre no encontrado";
        return;
    }else{
        string nomCh = pedirNomCharla();
        
        string idCh = (to_string(tempSem->abreviatura)).append(nomCh);
        cout<<"ID CHARLA: "<<tempSem->abreviatura;
        charla* buscar = buscarCharla(tempSem->abreviatura, idCh);
        if(buscar != NULL){
            cout<<"La charla llamada "<<nomCh<<" ya se encuentra registrada en el semestre"<<endl;
            return;
        }else{
            int fechaCh = pedirFechaAct();
            int horaCh = pedirHoraAct();
            
            insertarCharlaProf(tempSem, nomCh, fechaCh, horaCh);
        }
    }    
}

void modificarChProf(){//Inserts conference on semester

    int codigoS = pedirCodigoSem();
    semestre* tempSem = buscarSem(codigoS);

    if(tempSem == NULL){
        cout<<"Semestre no encontrado";
        return;
    }else{
        string nomCh = pedirNomCharla();
        
        string idCh = (to_string(tempSem->abreviatura)).append(nomCh);
        charla* buscar = buscarCharla(codigoS, idCh);

        if(buscar == NULL){
            cout<<"La charla llamada "<<nomCh<<" no se encuentra registrada en el semestre"<<endl;
            return;
        }else{
            string nuevoNom;
            cout<<"Ingrese el nuevo nombre de la charla"<<endl;
            cin>>nuevoNom;
            string nuevoId = (to_string(tempSem->abreviatura)).append(nuevoNom);
            buscar->nombreCharla = nuevoNom;
            buscar->idCharla = nuevoId;
            cout<<"Nombre de charla cambiado con exito"<<endl;
            return;
        }
    }
}

void borrarChProf(){//Deletes conference on semester

    int codigoS = pedirCodigoSem();
    semestre* tempSem = buscarSem(codigoS);

    if(tempSem == NULL){
        cout<<"Semestre no encontrado";
        return;
    }else{
        string nomCh = pedirNomCharla();
        
        string idCh = (to_string(tempSem->abreviatura)).append(nomCh);
        charla* buscar = buscarCharla(codigoS, idCh);

        if(buscar == NULL){
            cout<<"La charla llamada "<<nomCh<<" no se encuentra registrada en el semestre"<<endl;
            return;
        }else{
            if(tempSem->listaCharlas == NULL){//Empty list
                cout<<"No hay charlas registradas"<<endl;
                return;
            }else if(tempSem->listaCharlas->idCharla == idCh){
                tempSem->listaCharlas = tempSem->listaCharlas->sigCharla;
                cout<<"Charla eliminada con exito"<<endl;
                return;
            }else{//We must go through the list 
                charla* tempCh = tempSem->listaCharlas;
                charla* tempAnt;
                while(tempCh != NULL){
                    if(tempCh->idCharla == idCh){
                        tempAnt->sigCharla = tempCh->sigCharla;
                        cout<<"Charla eliminada con exito"<<endl;
                    }
                    tempAnt = tempCh;
                    tempCh = tempCh->sigCharla;
                }
            }
        }
    }
}

void mostrarCharlas(){
    int codigoS = pedirCodigoSem();
    semestre* tempSem = buscarSem(codigoS);
    if(tempSem == NULL){
        cout<<"Semestre no encontrado"<<endl;
        return;
    }else{
        if(tempSem->listaCharlas == NULL){
            cout<<"Lista vacia"<<endl;
            return;
        }
        charla* tempCh = tempSem->listaCharlas;
        cout<<"Charlas del semestre "<<tempSem->abreviatura<<endl;
        while(tempCh != NULL){
            cout<<"Nombre de la charla: "<<tempCh->nombreCharla<<" ID: "<<tempCh->idCharla<< "Fecha y hora: "<< tempCh->fecha<< " "<<tempCh->hora;
            tempCh = tempCh->sigCharla;
        }
        cout<<"Fin de reporte"<<endl;
        return;
    }
}

evaluacion* buscarAct(grupo* tempG, string tipoAct, string numAct){
    string idAct = tipoAct.append(numAct);
    if(tempG->listaEvaluacion == NULL){//Empty
        return NULL;
    }else{
        evaluacion* tempEn = tempG->listaEvaluacion;
        while(tempEn != NULL){
            if(tempEn->idActividad == idAct){
                return tempEn;
            }
            tempEn = tempEn->sigEv;
        }
        return NULL;
    }
}

void agregarActEst(){
    int carnetEst = pedirCarnetEst();
    estudiante* tempEst = buscarEst(carnetEst);
    if(tempEst == NULL){//Check if student exists
        cout<<"Estudiante no encontrado"<<endl;
        return;
    }else{//group exists
        int codigoNum = pedirCodCurso();
        int numGp = pedirNumGrupo();
        int idC = (100*codigoNum)+numGp;
        grupo* tempG = buscarGrupoEst(carnetEst, idC);

        if(tempG == NULL){
            cout<<"Grupo no encontrado"<<endl;
            return;
        }else{//Check if activity exists
            string tipoAct = pedirTipoAct();
            string numAct = pedirNumAct();
            
            evaluacion* tempEv = buscarAct(tempG, tipoAct, numAct);

            if(tempEv == NULL){
                cout<<"Actividad no encontrada"<<endl;
                return;
            }else{//Everything exists, add the activity to the list
                evaluacionesEntregadas* nEv = new evaluacionesEntregadas(tempEv);

                if(tempEst->evaluacionEst == NULL){//Empty list
                    tempEst->evaluacionEst = nEv;
                    cout<<"Actividad agregada con exito"<<endl;
                    return;
                }else{//List has elements, we must go through the beginning, middle and end 
                    evaluacionesEntregadas* tempEntregada = tempEst->evaluacionEst;

                    if(nEv->sigEvaluacion->fechaEntrega < tempEntregada->sigEvaluacion->fechaEntrega){//Insert at the beginning 
                        nEv->sig = tempEntregada->sig;
                        tempEntregada->sig = nEv;
                        cout<<"Actividad realizada con exito"<<endl;
                        return;
                    }else{//Middle or end
                        while((tempEntregada->sig != NULL)&&(tempEntregada->sig->sigEvaluacion->fechaEntrega < nEv->sigEvaluacion->fechaEntrega)){
                            tempEntregada = tempEntregada->sig;
                        }
                        nEv->sig = tempEntregada->sig;
                        tempEntregada->sig = nEv;
                        cout<<"Actividad realizada con exito"<<endl;
                        return;
                    }
                }
            }
        }
    }
}

void insertarCharlaEst(){
    int carnetEst = pedirCarnetEst();
    estudiante* tempEst = buscarEst(carnetEst);
    if(tempEst == NULL){//Check if student exists
        cout<<"Estudiante no encontrado"<<endl;
        return;
    }else{//Check if semester exists
        int codigoS = pedirCodigoSem();
        semestre* tempSem = buscarSem(codigoS);

        if(tempSem == NULL){
            cout<<"Semestre no encontrado"<<endl;
            return;
        }else{
            string nomCh = pedirNomCharla();
            string idCh = (to_string(tempSem->abreviatura)).append(nomCh);
            charla* tempCh = buscarCharla(codigoS, idCh);
            if(tempCh == NULL){
                cout<<"Charla no encontrada";
                return;
            }else{
                enlaceCharla* nEnCh = new enlaceCharla(tempCh); 
                
                if(tempEst->charla == NULL){//Empty list
                    tempEst->charla = nEnCh;
                    cout<<"Charla asistida con exito"<<endl;
                    return;    
                }else{//Insert at the beginning
                    nEnCh->sig = tempEst->charla->sig;
                    tempEst->charla->sig = nEnCh;
                    cout<<"Charla asistida con exito"<<endl;
                    return;
                }
            }
        }
    }
}
//------------------Reports---------------------------------

void reporte2(){
    int numSem= pedirNumSem();
    int annoSem= pedirAnnoSem();
    int codigoS = 10*annoSem+numSem;

    semestre*tempS= listaSemestres;
    while(tempS!=NULL){
        if(tempS->abreviatura==codigoS){
            int cedulaP = pedirCedulaProf();
            string codCurso = pedirCodigoCurso();
            grupo* tempG = buscarGrupoProfe(cedulaP, codCurso);
            if(tempG == NULL){
                cout<<"Grupo no encontrado"<<endl;
                return;
            }
            else{
                evaluacion* tempEv = tempG->listaEvaluacion;
                cout<<"Actividades: "<<endl;
                while(tempEv != NULL){
                    cout<<"Tipo: "<<tempEv->tipo<<" Numero: "<<tempEv->numeroAct<< " Fecha de Entrega: "<<tempEv->fechaEntrega<<" Hora: "<<tempEv->hora<<endl;
                    tempEv = tempEv->sigEv;
                }
                cout<<"Fin de reporte"<<endl;
                return;
            }
        }
        tempS=tempS->sigSem;
    }
    cout<<"No existe este semestre indicado, o bien ningún profesor tiene actividades registradas."<<endl;

    
}


//------------------Reportes--------------------------------------------------------------------------------------------------




//------------------Menus-----------------------------------------------------------------------------------------------------

void menuPrincipal();

void menuEstudiante(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Realizar Actividad\nb- Participar en Charla\n\n1- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    

    if(opcion == "a"){
        agregarActEst();
        menuEstudiante();
    }
    else if(opcion == "b"){
        insertarCharlaEst();
        menuEstudiante();
    }
    else if(opcion == "1"){
        menuPrincipal();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuEstudiante();
    }
}

void menuProfesorAct(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Crear Actividad\nb- Modificar Actividad\nc- Borrar Actividad\n\n1- Volver al menu de profesor\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    

    if(opcion == "a"){
        insertarActProfAux();
        menuProfesor();
    }
    else if(opcion == "b"){
        modificarActProf();
        menuProfesor();
    }
    else if(opcion == "c"){
        borrarActProf();
        menuProfesor();
    }
    else if(opcion == "2"){
        menuPrincipal();
    }
    else if(opcion == "1"){
        menuProfesor();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuProfesor();
    }
}

void menuProfesorCh(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Crear Charla\nb- Modificar Charla\nc- Borrar Charla\n\n1- Volver al menu de profesor\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    

    if(opcion == "a"){
        insertarChProfAux();
        menuProfesorCh();
    }
    else if(opcion == "b"){
        modificarChProf();
        menuProfesorCh();
    }
    else if(opcion == "c"){
        borrarChProf();
        menuProfesorCh();
    }
    else if(opcion == "2"){
        menuPrincipal();
    }
    else if(opcion == "1"){
        menuProfesor();
    }
    else if(opcion == "z"){
        mostrarCharlas();
        menuProfesorCh();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuProfesor();
    }
}

void menuProfesor(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Actividades\nb- Charlas\n\n1- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    

    if(opcion == "a"){
        menuProfesorAct();
        //menuProfesor();
    }
    else if(opcion == "b"){
        menuProfesorCh();
        //menuProfesor();
    }
    else if(opcion == "1"){
        menuPrincipal();
    }
    else if(opcion == "z"){
        reporte2();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuProfesor();
    }
}
void menuAdmin();

void menuAdminSemestre(){
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    
    cout<<"a- Insertar Semestre\nb- Modificar Semestre\nc- Insertar Curso\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        insertarSemestreAux();
        menuAdminSemestre();
    }
    else if(opcion == "b"){
        modificarSemestreAux();
        menuAdminSemestre();
    }
    else if(opcion == "c"){
        relacionarCursoAux();
        menuAdminSemestre();
    }
    else if(opcion == "z"){
        reporteCursosSem();
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
        insertarCursoAux();
        menuAdminCurso();
    }
    else if(opcion == "b"){
        modificarCurso();
        menuAdminCurso();
    }
    else if(opcion == "c"){
        eliminarCursoAux();
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
    
    cout<<"a- Insertar estudiante\nb- Modificar estudiante\nc- Borrar estudiante\nd- Asignar a grupo\ne- Desvincular a grupo\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        insertarEstAux();
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
    else if(opcion == "d"){
        relacionarGrupoEstAux();
        menuAdminEst();
    }else if(opcion == "e"){
        borrarGrupoEst();
        menuAdminEst();
    }else if(opcion == "z"){
        reporteGruposEst();
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
    cout<<"a- Insertar profesor\nb- Modificar profesor\nc- Borrar profesor\nd- Asignar a grupo\n\n1-Volver al menu de administrador \n2-Volver al menu principal \nOpcion: ";
    string opcionMenuAdminProf;
    cin>> opcionMenuAdminProf;

    if (opcionMenuAdminProf== "a"){
        //cout<< "Insertar"<<endl;
        insertarProfAux();
        menuAdminProf();
    }else if(opcionMenuAdminProf=="b"){
        //cout<< "Modificar"<<endl;
        modificarProf();
        menuAdminProf();
        
    }else if(opcionMenuAdminProf=="c"){
        eliminarProf();
        menuAdminProf();
        //cout<< "Borrar"<<endl;

    }else if(opcionMenuAdminProf=="d"){
        relacionarGrupoProfAux();
        menuAdminProf();
    }else if(opcionMenuAdminProf=="e"){
        borrarGrupoProf();
        menuAdminProf();
    }else if(opcionMenuAdminProf=="1"){
        //cout<<"Salir"<<endl;
        menuAdmin();
    }
    else if(opcionMenuAdminProf=="2"){
        menuPrincipal();
    }
    else if(opcionMenuAdminProf=="z"){
        reporteGruposProfe();
        menuAdminProf();
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
        insertarGrupoAux();
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
    cout<<"Ingrese el numero de la seccion deseada: \n 1- Administrador\n 2- Usuario: Profesor\n 3- Usuario: Estudiante \n 4- Salir\nNumero:";
    string opcion;
    cin>>opcion;
    if(opcion=="1"){
        //cout<<"Administrador: "<<endl;
        ingresarAdmin();
    }else if(opcion=="2"){
        menuProfesor();
    }else if(opcion=="3"){
        menuEstudiante();
    }else if(opcion=="4"){
        cout<<"\n\nSaliendo...";
        return;
    }else{
        cout<<"Ingrese una opcion valida.";
        menuPrincipal();
    }
}

int main(){
    cout<<"\n\n\t\tCargando Datos...\n\n";
    cout<<"\tInsertando Administradores\n";    
    insertarAdmin("Maria", "123");
    insertarAdmin("Juan", "4567");
    insertarAdmin("Carlos", "930");
    cout<<"\tInsertando Semestres\n"; 
    insertarSemestre(2020, 2, 300);
    insertarSemestre(2020, 1, 250);
    insertarSemestre(2021, 1, 350);
    insertarSemestre(2021, 2, 100);
    insertarSemestre(2022, 1, 300);
    cout<<"\tInsertando Cursos\n"; 
    insertarCurso("Datos", "IC", 2040);
    insertarCurso("Arqui", "IC", 3101);
    insertarCurso("Discreta", "MA", 2089);
    insertarCurso("Probabilidad", "MA", 3098);
    insertarCurso("POO", "IC", 5021);
    cout<<"\tInsertando Profesores\n";
    insertarProf(11833, "Jose");
    insertarProf(12345, "Marta");
    insertarProf(48503, "Pedro");
    insertarProf(84728, "Gerardo");
    insertarProf(40284, "Lucia");
    cout<<"\tInsertando Estudiantes\n";
    insertarEst(202006, "Brenda");
    insertarEst(202105, "Earl");
    insertarEst(201935, "Crystel");
    insertarEst(201919, "Josefina");
    insertarEst(201705, "Carmen");
    cout<<"\tInsertanto Grupos\n";
    insertarGrupo("IC3101", buscarCurso("IC3101"), 50);
    insertarGrupo("IC3101", buscarCurso("IC3101"), 51);
    cout<<"\tAsignado profesores a grupos\n";
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC3101", 50));
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC3101", 51));
    cout<<"\tAsignado estudiantes a grupos\n";
    relacionarGrupoEst(buscarEst(202006), encontrarGrupo("IC3101", 50));
    relacionarGrupoEst(buscarEst(202105), encontrarGrupo("IC3101", 51));
    cout<<"\tCreando actividades\n";
    insertarActProf(encontrarGrupo("IC3101", 50), "Tarea", "1", 20211020, 1400);
    insertarActProf(encontrarGrupo("IC3101", 50), "Tarea", "2", 20210515, 1600);
    cout<<"\tCreando charlas\n";
    insertarCharlaProf(buscarSem(20211), "Charla1", 20211030, 1300);
    insertarCharlaProf(buscarSem(20211), "Charla2", 20210503, 1600);   
    //imprimirAdmins();
    //imprimirSemestres();
    menuPrincipal();

    return 0;
}