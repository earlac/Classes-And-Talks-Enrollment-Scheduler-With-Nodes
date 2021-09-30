/*
Instituto Tecnológico de Costa Rica, Estructuras de Datos
Proyecto 1: Gestión de actividades curriculares
Profesora: Lorena Valerio 
Estudiantes: Earl Areck Alvarado,       
             Brenda Badilla Rodriguez,  
*/

#include <string>
#include <ctime>
#include <iostream>
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
    charla* sigCharla;
    charla(string nNombreCharla, int nFecha, int nHora, int semestre){
        nombreCharla = nNombreCharla;
        fecha = nFecha;
        hora = nHora;
        idCharla = (to_string(semestre)).append(nombreCharla);//2021Charla1
        sigCharla = NULL;
    }
};

struct enlaceCharla{
    charla *enCharla; //Links to the course itself
    enlaceCharla *sig; //Orders the courses

    enlaceCharla(charla* nEnCharla){
        enCharla = nEnCharla;
        sig = NULL;
    }
};

struct estudiante{//Simple linked list
    string nombreEst;
    int carnet;

    estudiante *sigEst;
    enlazarGrupo *gruposEstAux;//Links to list of groups the student is in. Uses the same struct as Profesor

    enlaceCharla *charla;
    evaluacionesEntregadas *evaluacionEst; 

    estudiante(string nNombreEst, int nCarnet){
        nombreEst = nNombreEst;
        carnet = nCarnet;

        sigEst = NULL;
        gruposEstAux = NULL;

        charla= NULL;
        evaluacionEst=NULL;
    }
} *listaEstudiantes;

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

//------------------------------------------------------------------------------------Methods-------------------------------------------------

//------------------Periods' Methods---------------------------------
void menuAdminSemestre();

int pedirAnnoSem(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int annoS;
    cout<<"Ingrese el anno del semestre: ";
    while(!(cin>>annoS)){
        cin.clear();
        while(cin.get() != '\n')
            continue;   
        cout<<"Favor digitar solo numeros"<<endl;
        return pedirAnnoSem(); 
    }
    return annoS;
}

int pedirNumSem(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int semS;
    cout<<"Ingrese el semestre del anno (1 o 2): ";
    while((!(cin>>semS))||((semS != 1)&&(semS != 2))){
        cin.clear();
        while(cin.get() != '\n')
            continue;
        cout<<"Favor digitar solo 1 o 2"<<endl;
        return pedirNumSem();
    }
    return semS;
}

int pedirPresupuestoSem(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int presupuestoS;
    cout<<"Ingrese el presupuesto del semestre: ";
    while(!(cin>>presupuestoS)){
        cin.clear();
        while(cin.get() != '\n')
            continue;   
        cout<<"Favor digitar solo numeros"<<endl;
        return pedirPresupuestoSem(); 
    }
    return presupuestoS;   
}

int pedirCodigoSem(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int anno = pedirAnnoSem();
    int num = pedirNumSem();
    return (anno*10)+num;
}

semestre* buscarSem(int nCodigo){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoS;
    codigoS= 10*annoS+semS;

    semestre *nS = new semestre(semS, annoS, codigoS, presupuestoS);

    if(buscarSem(codigoS)!=NULL){
        cout<< "Ya existe un semestre con estas directrices."<<endl;
    }

    //if list is empty
    if(listaSemestres == NULL){
        
        listaSemestres=nS;
        cout<<"Semestre ingresado exitosamente."<<endl;
        return;
    }
    //Item goes first
    semestre *tempA= listaSemestres;
    if(tempA->abreviatura > codigoS){
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

void insertarSemestreAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int annoS = pedirAnnoSem();
    int semS = pedirNumSem();
    int presupuestoS = pedirPresupuestoSem();
    insertarSemestre(annoS, semS, presupuestoS);
}

void modificarSemestre(int codigoS){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    semestre*nSem= buscarSem(codigoS);
    
    int nPresupuestoS;
    cout<<"Ingrese el nuevo presupuesto del semestre (El programa agrega los millones): "<<endl;
    cin>>nPresupuestoS;

    nSem->presupuesto= nPresupuestoS;
    cout<<"Presupuesto modificado correctamente."<<endl;
}

void modificarSemestreAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int annoS = pedirAnnoSem();
    int semS = pedirNumSem();
    int codigoS = 10*annoS+semS;
    modificarSemestre(codigoS);  
}

//------------------Semester and subject's linking Methods---------------------------------

string pedirCodigoCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string codigo;
    cout<<"Ingrese el codigo del curso (Ej. IC3101): ";
    cin.sync();
    getline(cin, codigo);
    return codigo;
}

bool buscarCursoSem(semestre* tempSem, curso* tempC){
    enlaceCurso* tempEnC = tempSem->listaCursos;
    while(tempEnC != NULL){
        if(tempEnC->sigCurso == tempC){
            return true;
        }
        tempEnC = tempEnC->sig;
    }
    return false;
}

curso* buscarCurso(string codigo){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string abv = codigo.substr(0,2);
    int numCurso = stoi(codigo.substr(2,4));
    if(listaCursos == NULL){
        return NULL;
    }
    else{
        curso *temp = listaCursos;
        do{
            if((temp->codigoNum == numCurso) && (temp->abreviatura == abv)){
                return temp;
            }
            temp = temp->sigCurso;
        }while(temp != listaCursos);
        return NULL;
    } 
}

void relacionarCurso(int codSem){
/*
Inputs: 
        
Process:
        
Outputs:

*/   
    semestre* tempS = buscarSem(codSem);         //Check if semester exists
    if(tempS == NULL){
        cout<<"Semestre no encontrado"<<endl;
        return;
    }else{                                       //Check if subject exists
        string codigo = pedirCodigoCurso();
        curso* tempC = buscarCurso(codigo);
        if(tempC == NULL){
            cout<<"Curso no encontrado"<<endl;
            return;
        }
        else{                               //Semester and subject exist
            if(buscarCursoSem(tempS, tempC)){
                cout<<"El curso ya se encuentra registrado en este semestre"<<endl;
                return;
            }else{
                enlaceCurso* nE = new enlaceCurso(tempC); //Create new link 
                nE->sig = tempS->listaCursos;           //Point it to the beginning of the list
                tempS->listaCursos = nE;                //Insertion at the beginning of the list
                cout<<"\nCurso asignado satisfactoriamente"<<endl;
            }
            
        }
    }
}

void relacionarCursoAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoS = pedirCodigoSem();
    relacionarCurso(codigoS);
}

//------------------Courses' Methods---------------------------------

string pedirNomCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string nombreC;
    cout<<"Ingrese el nombre del curso: ";
    cin.sync();
    getline(cin,nombreC);
    return nombreC;
}

string pedirAbvCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string abvC;
    cout<<"Ingrese la escuela del curso (Ej. IC, MA..): ";
    cin.sync();
    getline(cin,abvC);
    return abvC;
}

int pedirCodCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoC;
    cout<<"Ingrese el codigo del curso (3101): ";
    while(!(cin>>codigoC)){
        cin.clear();
        while(cin.get() != '\n')
            continue;   
        cout<<"Favor digitar solo numeros"<<endl;
        return pedirCodCurso(); 
    }
    return codigoC;   
}

void insertarCurso(string nombreC, string abv, int codigoNumC){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string nombreC = pedirNomCurso();
    string abvC = pedirAbvCurso();
    int codigo = pedirCodCurso();
    curso* buscarC = buscarCurso(abvC + to_string(codigo));
    if(buscarC != NULL){
        cout<<"Curso ya se encuentra registrado"<<endl;
    }else{
        insertarCurso(nombreC, abvC, codigo);   
    }
}

void modificarCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string codigo = pedirCodigoCurso();
    curso* buscado = buscarCurso(codigo);
    
    if(buscado == NULL){
        cout<<"Curso no encontrado"<<endl;
    }
    else{
        string nuevoNom;
        cout<<"Escriba el nuevo nombre: ";
        cin.sync();
        getline(cin, nuevoNom);
        buscado->nombre = nuevoNom;
        cout<<"Nombre del curso cambiado con exito"<<endl;
    } 
}

void eliminarCurso(int codigoC, string abvC){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    if(listaCursos == NULL){
        cout<<"No existen cursos registrados"<<endl;
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string abv = pedirAbvCurso();
    int codigo = pedirCodCurso();

    eliminarCurso(codigo, abv); 
}

//------------------Students' Methods---------------------------------
int pedirCarnetEst(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int carnetEst;
    cout<<"Ingrese el carnet: ";
    while (!(cin >> carnetEst))
    {
        cin.clear();
        while (cin.get() != '\n') 
            continue;
        cout << "Por favor digite solo numeros"<<endl;
        return pedirCarnetEst();
    }
    return carnetEst;
}

int pedirNumGrupo(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int numG;
    cout<<"Ingrese el numero del grupo (Ej 50): ";
    while(!(cin>>numG)){
        cin.clear();
        while(cin.get()!='\n')
            continue;   
        cout<<"Favor digitar solo numeros"<<endl;
        return pedirNumGrupo(); 
    }
    return numG;
}

estudiante* buscarEst(int carnetEst){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void insertarEst(int carnetEst, string nombreEst){
/*
Inputs: 
        
Process:
        
Outputs:

*/

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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int carnetEst = pedirCarnetEst();

    estudiante*existe= buscarEst(carnetEst);
    //cout<<existe->carnet<<endl;
    if(existe != NULL){
        cout<<"El carnet ya se encuentra registrado bajo otro estudiante"<<endl;
        return;
    }else{
        string nombreEst;
        cout<< "Ingrese el nombre del estudiante por agregar: ";
        cin.sync();
        getline(cin, nombreEst);  
        insertarEst(carnetEst, nombreEst);
    }
}

void modificarEst(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    
    int carnet = pedirCarnetEst();
    estudiante*buscado = buscarEst(carnet);
    if(buscado == NULL){
        cout<<"\nEstudiante no encontrado"<<endl;
        return;
    }
    else{
        string nuevoNom;
        cout<<"\nIngrese el nuevo nombre del estudiante: ";
        cin.sync();
        getline(cin, nuevoNom);

        buscado->nombreEst = nuevoNom;
        cout<<"\nNombre de estudiante modificado con exito"<<endl;
        return;
    }
}

void eliminarEst(){//Delete on simple linked list
/*
Inputs: 
        
Process:
        
Outputs:

*/

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

grupo* buscarGrupoEst(int carnetEst, int codG){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    estudiante* tempEst = buscarEst(carnetEst);
    if(tempEst == NULL){
        return NULL;
    }else{
        if(tempEst->gruposEstAux == NULL){
            return NULL;
        }else{
            enlazarGrupo* tempG = tempEst->gruposEstAux;
            while(tempG != NULL){
                if(tempG->enlaceGrupo->idCurso == codG){
                    return tempG->enlaceGrupo;
                }
                tempG = tempG->sigEn;
            }
            return NULL;
        }
    }    
}

grupo* encontrarGrupo(string codigo, int numGrupo){
/*
Inputs: 
        
Process:
        
Outputs:

*/

    curso* tempCurso = buscarCurso(codigo);

    grupo *tempGrupo = tempCurso->grupoCursando;

    while(tempGrupo != NULL){
        if(tempGrupo->numGrupo == numGrupo)
            return tempGrupo;
        tempGrupo = tempGrupo->sigGrupo;
    }
    return NULL;
}

void relacionarGrupoEst(estudiante* tempE, grupo* tempG){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    if(buscarGrupoEst(tempE->carnet, tempG->idCurso) != NULL){
        cout<<"El estudiante ya se encuentra registrado a este grupo";
        return;
    }else{
        enlazarGrupo* nE = new enlazarGrupo(tempG);
        nE->sigEn = tempE->gruposEstAux;
        tempE->gruposEstAux = nE;
        cout<<"Estudiante asignado a grupo satisfactoriamente"<<endl;
        return;
    }
}

void relacionarGrupoEstAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void borrarGrupoEst(estudiante* tempEst, int idG){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void borrarGrupoEstAux(){
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
            string codigo = pedirCodigoCurso();
            int numG = pedirNumGrupo();

            grupo* tempG = encontrarGrupo(codigo, numG);
            if(tempG == NULL){
                cout<<"Grupo no encontrado"<<endl;
                return;
            }else{//Group and student exist
                int idG = 100*(stoi(codigo.substr(2,4))) + numG;
                borrarGrupoEst(tempEst, idG);
            }
        }
    }
}

//------------------Group's Methods----------------------------------


void insertarGrupo(string codigo, curso* cursoG, int numGrupo){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    if(encontrarGrupo(codigo, numGrupo) != NULL){
        cout<<"El grupo ya existe en este curso"<<endl;
        return;
    }else{
        string abv = codigo.substr(0,2);
        int numCurso = stoi(codigo.substr(2,4));

        struct grupo *nG = new grupo(numGrupo, abv, numCurso);

        nG->cursoActual = cursoG; //Links to the course it's part of
        nG->sigGrupo = cursoG->grupoCursando; //Then it's pointed to the begginning of the list of groups in the course
        cursoG->grupoCursando = nG;//Then it becomes the beginning of said list

        cout<<"Grupo insertado con exito"<<endl;
    }
}

void insertarGrupoAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string codigo = pedirCodigoCurso();

    curso* cursoG = buscarCurso(codigo);
    if(cursoG == NULL){
        cout<<"No se ha encontrado el curso"<<endl;
    }else{
        int numGrupo = pedirNumGrupo();

        insertarGrupo(codigo, cursoG, numGrupo);
    }
}

//------------------Admin Methods---------------------------------

administrador* buscarAdmin(string nombreA){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    administrador* temp = listaAdministradores;
    while(temp!= NULL){
        if (temp->usuario == nombreA)
            return temp;
        temp = temp->sigAdmin;
    }
    return NULL;
}

void insertarAdmin(string nombreA, string contrasennaA){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    
    administrador *nA = new administrador(nombreA, contrasennaA);
    nA->sigAdmin = listaAdministradores;
    listaAdministradores = nA;     
    cout<<"Administrador insertado existosamente"<<endl;
}

void insertarAdminAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string nombreA;
    cout<<"Ingrese el nombre de usuario del nuevo administrador: ";
    cin.sync();
    getline(cin,nombreA);
    
    if((buscarAdmin(nombreA)) != NULL)
    {
        cout<<"El usuario ya se encuentra registrado"<<endl;
    }
    else
    {
    string contrasennaA;
    cout<<"Ingrese la contrasena del nuevo administrador: ";
    cin.sync();
    getline(cin,contrasennaA);

    insertarAdmin(nombreA, contrasennaA);
    }
}

//------------------Teachers' Methods---------------------------------

int pedirCedulaProf(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int cedulaP;
    cout<<"Ingrese la cedula: ";
    while(!(cin>>cedulaP)){
        cin.clear();
        while (cin.get() != '\n') 
            continue;
        cout<<"Por favor digite solo numeros"<<endl;
        return pedirCedulaProf();
    }
    return cedulaP;
}

profesor* buscarProf(int cedulaP){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    profesor *temp = listaProfesores;
    while(temp != NULL){
        if (temp->cedulaProf == cedulaP)
            return temp;
        temp = temp->sigProf;
    }
    return NULL;
}

string pedirNombreProf(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string nombreProf;
    cout<<"Ingrese el nombre del profesor: ";
    cin.sync();
    getline(cin,nombreProf);
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int cedulaP = pedirCedulaProf();
    profesor *temp = buscarProf(cedulaP);
    
    if(temp == NULL){
        cout<<"\nEl profesor no existe, no se puede modificar"<<endl;
    }
    else{
        string nomProf;
        cout<<"Ingrese el nuevo nombre del profesor: ";
        cin.sync();
        getline(cin, nomProf);
        temp->nombreProf = nomProf;
        cout<<"Nombre del profesor modificado existosamente"<<endl;
    }
}

void eliminarProf(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int cedProf = pedirCedulaProf();
    profesor *temp = buscarProf(cedProf);

    if(temp == NULL){
        cout<<"El profesor no existe, no se puede borrar"<<endl;
    }
    else{ //Delete at the beginning of the list
        if(temp == listaProfesores){
            if(temp->sigProf == NULL)
                listaProfesores = NULL;
            else{
                listaProfesores = listaProfesores->sigProf;
                listaProfesores->antProf = NULL;
            }
        }
        else{//Middle or end of list
            if(temp->sigProf == NULL)//Last
                temp->antProf->sigProf = NULL;
            else{//Middle
                temp->antProf->sigProf = temp->sigProf;
                temp->sigProf->antProf = temp->antProf;
            }
        }
        cout<<"Profesor eliminado exitosamente"<<endl;
    }
}

grupo* buscarGrupoProfe(int cedulaP, string codCurso){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    profesor* tempP = buscarProf(cedulaP);

    if(tempP == NULL){
        return NULL;
    }else{
        enlazarGrupo* tempG = tempP->gruposProfAux;
        if(buscarCurso(codCurso) == NULL){
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
            return NULL;
        } 
    }    
}

void borrarGrupoProf(profesor* tempProf, int idG){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    if(tempProf->gruposProfAux->enlaceGrupo->idCurso == idG){//Delet the beginning of the list
        tempProf->gruposProfAux = tempProf->gruposProfAux->sigEn; 
        cout<<"Curso desvinculado del profesor exitosamente"<<endl;
        return;
    }else{                                                  //Delete middle or end of list
        enlazarGrupo* tempEn = tempProf->gruposProfAux;
        while(tempEn->sigEn != NULL){
            if(tempEn->sigEn->enlaceGrupo->idCurso == idG){
                tempEn->sigEn = tempEn->sigEn->sigEn;
                cout<<"Curso desvinculado del profesor exitosamente"<<endl;
                return;
            }
            tempEn = tempEn->sigEn;
        }
        cout<<"Ha occurrido un error al desvincular el grupo"<<endl;
    }
}

void borrarGrupoProfAux(){
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
            string codigo = pedirCodigoCurso();
            int numG = pedirNumGrupo();

            grupo* tempG = encontrarGrupo(codigo, numG);
            if(tempG == NULL){
                cout<<"Grupo no encontrado"<<endl;
                return;
            }else{//Group and student exist
                int idG = 100*(stoi(codigo.substr(2,4))) + numG;
                borrarGrupoProf(tempProf, idG);
            }
        }
    }
}

void relacionarGrupoProf(profesor* tempP, grupo* tempG){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    enlazarGrupo* nE = new enlazarGrupo(tempG);
    nE->sigEn = tempP->gruposProfAux;
    tempP->gruposProfAux = nE;
    cout<<"\nProfesor asignado a grupo satisfactoriamente"<<endl;
}

void relacionarGrupoProfAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
    }else{
        grupo* buscar = buscarGrupoProfe(cedulaP, codigo);
        if(buscar != NULL){
            cout<<"El profesor ya se encuentra asignado a este grupo"<<endl;
        }else{
            relacionarGrupoProf(tempP, tempG);
        }
    }
}

//------------------Printing Methods---------------------------------

void imprimirProfesores(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    estudiante *temp = listaEstudiantes;
    cout<<"Lista de estudiantes: "<<endl;
    while(temp != NULL){
        cout<<"pasando al siguiente"<<endl;
        cout<<"Estudiante: "<<temp->nombreEst<<", Carnet: "<<temp->carnet<<endl;
        temp = temp->sigEst;
    }

}
void imprimirSemestres(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    semestre *temp = listaSemestres;
    cout<<"Lista de semesetres: "<<endl;
    while(temp != NULL){
        //cout<<"pasando al siguiente"<<endl;
        cout<<"Periodo: "<<temp->numSemestre<<", Anno: "<<temp->anno<<", Presupuesto: "<<temp->presupuesto<<" millones de colones"<<endl;
        temp = temp->sigSem;
    }

}

void mostrarCurso(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void reporteGruposEst(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int carnetEst = pedirCarnetEst();

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

void reporteGrupo(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void reporteGruposProfe(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void reporteCursosSem(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
//------------------------------------------------Evaluation's Methods---------------------------

void menuPrincipal();
void menuProfesor();

void ingresarProfesor(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

string pedirTipoAct(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int num;
    cout<<"Ingrese el numero de actividad: ";
    while (!(cin>>num)){
        cin.clear();
        while(cin.get() != '\n')
            continue;
        cout<<"Digite solo numeros"<<endl;
        return pedirNumAct();
    }
    return to_string(num);
}

int pedirFechaAct(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int anno;
    int mes;
    int dia;
    cout<<"Dia: ";
    while(!(cin>>dia)){
        cin.clear();
        while(cin.get() != '\n')
            continue;
        cout<<"Solo digite numeros"<<endl;
        return pedirFechaAct();
    }
    cout<<"-1 Enero\n-2 Febrero\n-3 Marzo\n-4 Abril\n-5 Mayo\n-6 Junio\n-7 Julio\n-8 Agosto\n-9 Setiembre\n-10 Octubre\n-11 Noviembre\n-12 Diciembre\nIngrese el numero del mes: ";
    while(!(cin>>mes)){
        cin.clear();
        while(cin.get() != '\n')
            continue;
        cout<<"Solo digite el numero correspondiente al mes"<<endl;
        return pedirFechaAct();
    }
    cout<<"Anno: ";
    while(!(cin>>anno)){
        cin.clear();
        while(cin.get() != '\n')
            continue;
        cout<<"Solo digite numeros"<<endl;
        return pedirFechaAct();
    }
    int codigo;
    codigo= anno*10000 + mes*100 + dia;
    return codigo;
}

int pedirHoraAct(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int hora;
    cout<<"Ingrese la hora de entrega (Formato militar. Ejemplo: 1600 (4:00p.m.)): ";
    while (!(cin>>hora))
    {
        cin.clear();
        while(cin.get() != '\n') 
            continue;
        cout<<"Por favor digite solo numeros"<<endl;
        return pedirHoraAct();
    }
    return hora;
}

int pedirNota(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int nota;
    cout<<"Ingrese la nota del estudiante: ";
    while(!(cin>>nota)){
        cin.clear();
        while(cin.get() != '\n') 
            continue;
        cout<<"Por favor digite solo numeros"<<endl;
        return pedirNota();
    }
    return nota;
}

string mostrarMesAct(evaluacion* actividad){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Setiembre", "Octubre", "Noviembre", "Diciembre"};
    string mes = meses[(((actividad->fechaEntrega)%10000)/100)-1];
    return mes;
}

int calcularMesAct(evaluacion* actividad){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int mes = ((actividad->fechaEntrega)%10000)/100;
    return mes;
}

int calcularDiaAct(evaluacion* actividad){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int dia = (actividad->fechaEntrega)%100;
    return dia;
}

int calcularAnnoAct(evaluacion* actividad){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int anno = (actividad->fechaEntrega)/10000;
    return anno;
}

evaluacion* buscarAct(grupo* tempG, string tipoAct, string numAct){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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

void insertarActProf(grupo* tempG, string tipoAct, string numAct, int fechaAct, int horaAct){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
                if(tempEv->sigEv->fechaEntrega == nEv->fechaEntrega){
                    if(tempEv->sigEv->hora >= nEv->hora){
                        nEv->sigEv = tempEv->sigEv;
                        tempEv->sigEv = nEv;
                        cout<<"Actividad creada con exito"<<endl;
                        return;
                    }
                }
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/

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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int cedulaP = pedirCedulaProf();
    profesor* tempP = buscarProf(cedulaP);
    //string codCurso = pedirCodigoCurso();
    enlazarGrupo* tempEnG = tempP->gruposProfAux;
    
    while(tempEnG != NULL){
        cout<<"Grupo: "<<tempEnG->enlaceGrupo->idCurso<<endl;
    
        evaluacion* tempEv = tempEnG->enlaceGrupo->listaEvaluacion;
        cout<<"Actividades: "<<endl;
        while(tempEv != NULL){
            cout<<"Tipo: "<<tempEv->tipo<<" Numero: "<<tempEv->numeroAct<< " Fecha de Entrega: "<<tempEv->fechaEntrega<<" Hora: "<<tempEv->hora<<endl;
            tempEv = tempEv->sigEv;
        }
        tempEnG = tempEnG->sigEn;
    }    
    cout<<"Fin de reporte"<<endl;
}

void imprimirActEst(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int carnet = pedirCarnetEst();
    estudiante* tempEst = buscarEst(carnet);
    if(tempEst == NULL){
        cout<<"Estudiante no encontrado"<<endl;
    }
    int codCurso = pedirCodCurso();
    grupo* tempG = buscarGrupoEst(carnet, codCurso);
    if(tempG == NULL){
        cout<<"Grupo no encontrado"<<endl;
        return;
    }
    else{
        evaluacionesEntregadas* tempEvEn = tempEst->evaluacionEst;
        cout<<"Actividades Entregadas: "<<endl;
        while(tempEvEn != NULL){
            cout<<"Tipo: "<<tempEvEn->sigEvaluacion->tipo<<" Numero: "<<tempEvEn->sigEvaluacion->numeroAct<<" Fecha de Entrega: "<<tempEvEn->sigEvaluacion->fechaEntrega<<" Hora: "<<tempEvEn->sigEvaluacion->hora<<endl;
            tempEvEn = tempEvEn->sig;
        }
        cout<<"Fin de reporte"<<endl;
    }
}


//-------------------------------------------------------Conferences' Methords--------

string pedirNomCharla(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    
    string nom;
    cout<<"Ingrese el nombre de la charla: ";
    cin.sync();
    getline(cin, nom);
    return nom;
}

charla* buscarCharla(int codigoS, string idCh){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    
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
            while((tempCh->sigCharla != NULL)&&(tempCh->sigCharla->fecha <= nCh->fecha)){
                if(tempCh->sigCharla->fecha == nCh->fecha){
                    if(tempCh->sigCharla->hora >= nCh->hora){
                        nCh->sigCharla = tempCh->sigCharla;
                        tempCh->sigCharla = nCh;
                        cout<<"Actividad creada con exito"<<endl;
                        return;
                    }
                }
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoS = pedirCodigoSem();//20201
    semestre* tempSem = buscarSem(codigoS);
    
    if(tempSem == NULL){
        cout<<"Semestre no encontrado";
        return;
    }else{
        string nomCh = pedirNomCharla();
        
        string idCh = (to_string(tempSem->abreviatura)).append(nomCh);
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
/*
Inputs: 
        
Process:
        
Outputs:

*/

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
            cin.sync();
            getline(cin, nuevoNom);
            string nuevoId = (to_string(tempSem->abreviatura)).append(nuevoNom);
            buscar->nombreCharla = nuevoNom;
            buscar->idCharla = nuevoId;
            cout<<"Nombre de charla cambiado con exito"<<endl;
            return;
        }
    }
}

void borrarChProf(){//Deletes conference on semester
/*
Inputs: 
        
Process:
        
Outputs:

*/

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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
            cout<<"Nombre de la charla: "<<tempCh->nombreCharla<<" ID: "<<tempCh->idCharla<< "Fecha y hora: "<< tempCh->fecha<< " "<<tempCh->hora<<endl;
            tempCh = tempCh->sigCharla;
        }
        cout<<"Fin de reporte"<<endl;
        return;
    }
}

void agregarActEst(estudiante *tempEst, evaluacion* tempEv){
/*
Inputs: 
        
Process:
        
Outputs:

*/
//Everything exists, add the activity to the list
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

void agregarActEstAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
            }else{
                agregarActEst(tempEst, tempEv);
            }
        }
    }
}

void insertarCharlaEst(estudiante* tempEst, charla* tempCh){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    
    enlaceCharla* nEnCh = new enlaceCharla(tempCh); 
    if(tempEst->charla == NULL){//Empty list
        tempEst->charla = nEnCh;
        nEnCh = NULL;
        cout<<"Charla asistida con exito"<<endl;
        return;    
    }else{//List with elements
        nEnCh->sig = tempEst->charla;
        tempEst->charla = nEnCh;
        cout<<"Charla asistida con exito"<<endl;
        return;
    } 
}

void insertarCharlaEstAux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
                insertarCharlaEst(tempEst, tempCh);
            }
        }
    }
}
//------------------Reports---------------------------------

int fechaHoy(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
//Returns today's date in yyyy/mm/dd format
    time_t t = time(0);   // gets today's date but in UTC time, (global time)
    tm* now = localtime(&t); //converts it to our tz
    return 10000*(now->tm_year + 1900) + 100*(now->tm_mon + 1)+ (now->tm_mday);//makes the yyyy/mm/dd format
}

int numSemana(int d, int m, int y)
/*
Inputs: 
        
Process:
        
Outputs:

*/
{//Receives day, month and year in ints and calculates the day of the week in int
//0 for sunday, 1 for monday...
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

string nomSemana(int numSem){
/*
Inputs: 
        
Process:
        
Outputs:

*/
//Receives the number of the week and returns the name
    string diasSem[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
    return diasSem[numSem];
}

string nomMes(int numMes){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Setiembre", "Octubre", "Noviembre", "Diciembre"};
    return meses[numMes-1];
}
 
void reporte1(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    //DESPUES SUMARLE 7 A DIA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int fecha = fechaHoy();
    int dia = (fecha%100);//We go to next week according to the project's instructions
    int mes = (fecha%10000)/100;//get month, day and year separated 
    int anno = fecha/10000;

    int numSem = numSemana(dia, mes, anno);
    if(numSem > 0){//If today isn't sunday
        dia = dia - (numSem); //We need it to be sunday to start checking every day of the week  
    }
    int tempDia = dia; //Safe the value so that we can iterate it 
    int contAct = 0; //We need to know how many activities we have for each day
    
    int cedulaP = pedirCedulaProf();//First check if the teacher exists
    profesor* tempP = buscarProf(cedulaP);

    if(tempP == NULL){
        cout<<"No se ha encontrado al profesor"<<endl;
        return;
    }
    
    while(tempDia <= dia + 6){//Keep going until we reach saturday
        cout<<"\n"<<nomSemana(numSemana(tempDia, mes, anno))<<" "<<tempDia;//Print the day of the week. Ie. Lunes 27
        
        enlazarGrupo* tempG = tempP->gruposProfAux; //Now we need to go through all of his groups
        while(tempG != NULL){
                
            evaluacion* tempEv = tempG->enlaceGrupo->listaEvaluacion;    
            
            while(tempEv != NULL){
                    
                if(tempEv->fechaEntrega == anno*10000 + mes*100 + tempDia){//If the due date equals today's date
                    cout<<"\n\tEntrega de "<<tempEv->tipo<<" en "<<tempG->enlaceGrupo->cursoActual->nombre<<" con el grupo "<<tempG->enlaceGrupo->numGrupo;
                    contAct = contAct + 1;
                }
                tempEv = tempEv->sigEv;
            }
            tempG = tempG->sigEn;
        }
        if(contAct == 0){
            cout<<"\n\tNo hay actividades programadas";
        }
        contAct = 0; 
        tempDia = tempDia+1;
    }
}

void reporte2(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int numSem2 = 0;
    int fecha = fechaHoy();//Returns yyyy/mm/dd

    int mes = ((fecha%10000)/100); 
    int anno = fecha/10000;
    if(mes<=7){
        numSem2=1;
    }else{
        numSem2=2;
    }
    cout<<mes<<endl;
    cout<<anno<<endl;
    cout<<numSem2<<endl;

    int codigoS2 = (10*anno)+numSem2;
    cout<<"Codigo semana: ";
    cout<<codigoS2<<endl;
    semestre*tempS= listaSemestres;
    while(tempS!=NULL){
        if(tempS->abreviatura==codigoS2){
            int cedulaP = pedirCedulaProf();

            profesor* tempP = buscarProf(cedulaP);

            enlazarGrupo* tempG = tempP->gruposProfAux;
            cout<<"Actividades: "<<endl;
            while(tempG!=NULL){
                evaluacion* tempEv = tempG->enlaceGrupo->listaEvaluacion;
                    
                while(tempEv != NULL){
                    cout<<"Tipo: "<<tempEv->tipo<<" Numero: "<<tempEv->numeroAct<< " Fecha de Entrega: "<<tempEv->fechaEntrega<<" Hora: "<<tempEv->hora<<endl;
                    tempEv = tempEv->sigEv;
                }
                tempG = tempG->sigEn;
            }
     
        }
        tempS=tempS->sigSem;
    }
    return;
}

bool buscarActEst(estudiante* tempEst, evaluacion* tempEv){
/*
Inputs: 
        estudiante* tempEst: the student
        evaluacion* tempEv: the activity
Process: 
        Goes through the list of activities the student has done, if one of them is the activity we're
        looking for, then it returns it. Else, it returns NULL.

OutPut:
        NULL: If the student didn't do the activity
        evaluacionesEntregadas* tempEv: If the student did the activity
*/

    evaluacionesEntregadas* tempEvaEn = tempEst->evaluacionEst;

    if(tempEvaEn == NULL){
        return false;
    }else{

        while(tempEvaEn != NULL){

            if(tempEvaEn->sigEvaluacion == tempEv){
                return true; 
            }

            tempEvaEn = tempEvaEn->sig;
        }
        return false;
    }
}

void reporte3(profesor* tempP, int fecha){
/*
Inputs: 
        
Process:
        
Outputs:

*/
/*Goes through all the groups the teacher has, and thorugh all the evaluations in each group
if their due date is before today's date, then it's already done
then we go through all the students and check who has that evaluation done
*/
    int cantEst = 0;

    if(tempP->gruposProfAux == NULL){
        cout<<"El profesor no tiene grupos asignados"<<endl;
        return;
    }
    
    enlazarGrupo* tempG = tempP->gruposProfAux; //Now we need to go through all of his groups
    
    while(tempG != NULL){

        cout<<"\nGrupo: "<<tempG->enlaceGrupo->idCurso<<endl;
         
        evaluacion* tempEv = tempG->enlaceGrupo->listaEvaluacion;    

        while(tempEv != NULL){
                    
            if(tempEv->fechaEntrega <= fecha){//If the due date has already passed. It's a done activity. So we must check who did it and who didn't
                cout<<"\n\t"<<tempEv->tipo<<" "<< nomSemana(numSemana(calcularDiaAct(tempEv), calcularMesAct(tempEv), calcularAnnoAct(tempEv)))<<" "<<calcularDiaAct(tempEv)<<" de "<<mostrarMesAct(tempEv)<<" del "<<calcularAnnoAct(tempEv)<<" a las "<<tempEv->hora<<" de "<<tempG->enlaceGrupo->cursoActual->nombre<<endl;
                
                cout<<"\nEntregaron: "<<endl;

                estudiante* tempEst = listaEstudiantes;
                
                while(tempEst != NULL){//Go through the list checking who did it
                    if(tempG->enlaceGrupo == buscarGrupoEst(tempEst->carnet, tempG->enlaceGrupo->idCurso)){//if student is in the group
        
                        if(buscarActEst(tempEst, tempEv) == true){
                            cout<<tempEst->nombreEst<<endl;
                            cantEst = cantEst + 1;
                        }
                    }
                    tempEst = tempEst->sigEst;
                }
                if(cantEst == 0){
                    cout<<"Ningun estudiante entrego la actividad"<<endl;
                }
                tempEst = listaEstudiantes;//After going through all the students, we reset to do it again 
                cantEst = 0;
                cout<<"\nNo Entregaron: "<<endl;

                while(tempEst != NULL){//Same logic but with the students who don't have it donee
                    if(tempG->enlaceGrupo == buscarGrupoEst(tempEst->carnet, tempG->enlaceGrupo->idCurso)){
                        
                        if(buscarActEst(tempEst, tempEv) == false){
                            cout<<tempEst->nombreEst<<endl;
                            cantEst = cantEst + 1;
                        }
                    }
                    tempEst = tempEst->sigEst;
                }
                if(cantEst == 0){
                    cout<<"Todos los estudiantes entregaron la actividad"<<endl;
                }
            }
            //tempEst = listaEstudiantes;//Resets the student again, to go through it all again
            tempEv = tempEv->sigEv;//We go to check the next activity             
        }
        tempG = tempG->sigEn;//After going through all the activities, we check the activities of the next group 
    }    
}

void reporte3Aux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int fecha = fechaHoy();//today's date in yyyy/mm/dd format
    int cedulaP = pedirCedulaProf();//First check if the teacher exists
    profesor* tempP = buscarProf(cedulaP);
    if(tempP == NULL){
        cout<<"No se ha encontrado al profesor"<<endl;
        return;
    }else{
        reporte3(tempP, fecha); 
    }   
}

bool buscarCharlaEst(estudiante* tempEst, charla* tempCh){

    enlaceCharla* buscarCh = tempEst->charla;

    while(buscarCh != NULL){
        if(buscarCh->enCharla == tempCh)
            return true;
        buscarCh = buscarCh->sig;
    }
    return false;
}


void reporte4(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoS = pedirCodigoSem();
    semestre* tempSem = buscarSem(codigoS);
    if(tempSem == NULL){
        cout<<"Semestre no encontrado"<<endl;
    }else{
        cout<<"\nEstudiantes que han participado en todas las charlas del semestre "<<codigoS%10<<" del "<<codigoS/10<<"\n"<<endl;
        charla* tempCh = tempSem->listaCharlas;
        int cantCh = 0;
        while(tempCh != NULL){
            cantCh = cantCh + 1;
            tempCh = tempCh->sigCharla;
        }
        estudiante* tempEst = listaEstudiantes;
        
        while(tempEst != NULL){
            int cantChEst = 0;
            enlaceCharla* tempEnCh = tempEst->charla;
            while(tempEnCh != NULL){
                if(buscarCharlaEst(tempEst, tempEnCh->enCharla)==true){
                    cantChEst = cantChEst + 1; 
                }
                tempEnCh = tempEnCh->sig;
            }
            if(cantChEst == cantCh){
                cout<<"Estudiante: "<<tempEst->nombreEst<< "    Carnet: "<< tempEst->carnet<<endl;
            }
            tempEst = tempEst->sigEst;
        }
    }
}

void reporte5(profesor* tempP, curso* tempC){
/*
Inputs: 
        profesor* tempP: teacher 
        curso* tempC: subject 
Process:
        With the teacher and subject, we must go through all the groups the teacher is giving classes of that subject. 
        Then, in every group, we look for the students in that group. 
        We look for all of the activities, and check if the student has it in his evaluacionesEntregadas list.
        if not, then that evaluation is printed. 
Outputs:
        Prints the teacher, the course, the student, and every activity that said student hasn't done. 
*/
    int cantEv = 0;

    if(tempP->gruposProfAux == NULL){
        cout<<"El profesor no tiene grupos asignados"<<endl;
        return;
    }

    cout<<"\tProfesor: "<<tempP->nombreProf<<endl;
    cout<<"\t\t"<<tempC->nombre<<endl;
    
    enlazarGrupo* tempEnG = tempP->gruposProfAux; //Now we need to go through all of his groups
    
    while(tempEnG != NULL){

        if(tempEnG->enlaceGrupo->cursoActual == tempC){
            estudiante* tempEst = listaEstudiantes;
            
            while(tempEst != NULL){//Go through the list of students
            
                if(tempEnG->enlaceGrupo == buscarGrupoEst(tempEst->carnet, tempEnG->enlaceGrupo->idCurso)){//if student is in the group
                    cout<<"\n\t\t\t"<<tempEst->nombreEst<<" (G"<<tempEnG->enlaceGrupo->numGrupo<<")"<<" no ha entregado o participado en: \n"<<endl;

                    evaluacion* tempEv = tempEnG->enlaceGrupo->listaEvaluacion;
                    while(tempEv != NULL){

                        if(buscarActEst(tempEst, tempEv) == false){
                            cout<<"\t\t\t\t"<<tempEv->tipo<<" del "<<nomSemana(numSemana(calcularDiaAct(tempEv), calcularMesAct(tempEv), calcularAnnoAct(tempEv)))<<" "<<calcularDiaAct(tempEv)<<" de "<<mostrarMesAct(tempEv)<<endl;
                            cantEv = cantEv + 1;
                        }
                        tempEv = tempEv->sigEv;
                    }   
                    if(cantEv == 0){
                        cout<<"\t\t\t\t"<<"Ha entregado o participado en todas las actividades"<<endl;
                    }
                }
                tempEst = tempEst->sigEst;
                cantEv = 0;
            }            
        }
        tempEnG = tempEnG->sigEn;
    }
}

void reporte5Aux(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int cedula = pedirCedulaProf();
    profesor* tempP = buscarProf(cedula);

    if(tempP == NULL){
        cout<<"Profesor no encontrado"<<endl;
        return;
    }else{
        string idC = pedirCodigoCurso();
        curso* tempC = buscarCurso(idC);
        if(tempC == NULL){
            cout<<"Curso no encontrado"<<endl;
            return;
        }else{
            reporte5(tempP, tempC);
        }
    }
}

string grupoActEst(estudiante* tempEst, evaluacion* tempEv){

    enlazarGrupo* tempG = tempEst->gruposEstAux;

    while(tempG != NULL){

        evaluacion* tempEvG = tempG->enlaceGrupo->listaEvaluacion;
        while(tempEvG != NULL){

            if(tempEvG == tempEv){
                return tempG->enlaceGrupo->cursoActual->nombre;
            }
            tempEvG = tempEvG->sigEv;
        }
        tempG = tempG->sigEn;
    }
    return "";
}

charla* buscarSemFecha(int fechaSem){
    semestre* tempSem = listaSemestres;
    while(tempSem != NULL){
        charla* tempCh = tempSem->listaCharlas;
        while(tempCh != NULL){
            if(tempCh->fecha == fechaSem){
                return tempCh;
            }
            tempCh = tempCh->sigCharla;
        }
        tempSem = tempSem->sigSem;
    }
    return NULL;
}

void reporte6(){  
/*
Inputs: 
        
Process:
        
Outputs:

*/ 
    int carnetEst = pedirCarnetEst();
    estudiante* tempEst = buscarEst(carnetEst);

    if(tempEst == NULL){
        cout<<"El carnet ingresado no se encuentra registrado"<<endl;
        return;
    }else{
        cout<<"Digite una fecha de la semana que desea verificar: \n";
        int fecha = pedirFechaAct();
        int dia = (fecha%100);
        int mes = (fecha%10000)/100;//get month, day and year separated 
        int anno = fecha/10000;

        int numSem = numSemana(dia, mes, anno);
        if(numSem > 0){//If today isn't sunday
            dia = dia - numSem; //We need it to be sunday to start checking every day of the week  
        }
        int tempDia = dia; //Safe the value so that we can iterate it 
        cout<<"Semana del "<<dia<<" al "<<dia+6<<" de "<<nomMes(mes)<<" del "<<anno<<endl;
        while(tempDia <= dia + 6){
            int contAct = 0;
            int fechaChoque = 0;
            int horaChoque = 0;
            cout<<nomSemana(numSemana(tempDia, mes, anno))<<" "<<tempDia<<endl;
            enlazarGrupo* tempG = tempEst->gruposEstAux;
            while(tempG != NULL){
                evaluacion* tempEv = tempG->enlaceGrupo->listaEvaluacion;
                evaluacion* tempAnt;//We make this variable so that the user will see the schedule crash after it happens   
                while(tempEv != NULL){
                    if(tempEv->fechaEntrega == (anno*10000 + mes*100 + tempDia)){
                        fechaChoque = tempEv->fechaEntrega;
                        horaChoque = tempEv->hora;
                        contAct = contAct + 1;            
                        cout<<"\t"<<tempEv->tipo<<" a las "<<tempEv->hora<<" en "<<tempG->enlaceGrupo->cursoActual->nombre<<endl; 
                        if(tempAnt->fechaEntrega == (anno*10000 + mes*100 + tempDia)){
                            if((tempAnt->hora <= tempEv->hora)&&(tempEv->hora <= tempAnt->hora+200)){
                                cout<<"\tHay choque!"<<endl;
                            }
                        }
                    }
                    tempAnt = tempEv;
                    tempEv = tempEv->sigEv;
                }
                tempG = tempG->sigEn;
            }
            semestre* tempSem = listaSemestres;
            while(tempSem != NULL){
                charla* tempCh = tempSem->listaCharlas;
                charla* tempAntCh;
                while(tempCh != NULL){
                    if(tempCh->fecha == (anno*10000 + mes*100 + tempDia)){
                        contAct = contAct + 1;
                        cout<<"\t"<<tempCh->nombreCharla<<" a las "<<tempCh->hora<<endl;
                        if(fechaChoque == (anno*10000 + mes*100 + tempDia)){
                            if(((horaChoque <= tempCh->hora)&&(tempCh->hora <= (horaChoque + 200)))||((tempCh->hora <= horaChoque)&&(horaChoque <= (tempCh->hora + 200)))){
                                cout<<"\tHay choque!"<<endl;
                                fechaChoque = 0;
                                horaChoque = 0;
                            }
                        }
                        if(tempAntCh->fecha == (anno*10000 + mes*100 + tempDia)){
                            if((tempAntCh->hora <= tempCh->hora)&&(tempCh->hora <= (tempAntCh->hora+200))){
                                cout<<"\tHay choque!"<<endl;
                            }
                        }
                    }
                    tempAntCh = tempCh;
                    tempCh = tempCh->sigCharla;
                }
                tempSem = tempSem->sigSem;
            }
            if(contAct == 0){
                cout<<"\tNo hay entregas programadas"<<endl;
            }    
            tempDia = tempDia + 1;
        }
    }
}

void reporte7(){
/*
Inputs: 
        None
Process:
        We go through the list of students. 
        For every student, we go through all of his/her groups.
        For every group they're in, we go through all of the evaluations.
        We check if the student has done its activities. While keeping a counter. 
        If they haven't done any, then it prints the student and subject. 
Output:
        Students who haven't done any activities in a subject. 
*/
    if(listaEstudiantes == NULL){
        cout<<"No existen estudiantes"<<endl;
        return;
    }else{
        estudiante* tempEst = listaEstudiantes;
        while(tempEst != NULL){
            enlazarGrupo* tempEnG = tempEst->gruposEstAux;
            while(tempEnG != NULL){
                int actEst = 0;//Activities done by the student int actEst = 0;//Activities done by the student 
                evaluacion* tempEv = tempEnG->enlaceGrupo->listaEvaluacion;
                while(tempEv != NULL){

                    if(buscarActEst(tempEst, tempEv) == true){
                        actEst = actEst + 1;
                    }

                    tempEv = tempEv->sigEv;
                }
                if(actEst == 0){
                    cout<<tempEst->nombreEst<<" (G"<<tempEnG->enlaceGrupo->numGrupo<<")"<<" no ha entregado nada en "<<tempEnG->enlaceGrupo->cursoActual->nombre<<endl;
                }
                tempEnG = tempEnG->sigEn;
            }
            tempEst = tempEst->sigEst;
        }
    }
    
}

void reporte8(){
/*
Inputs: 
        
Process:
        
Outputs:

*/
    int codigoS = pedirCodigoSem();
    
    int a=0, b=0, c=0;
    string na, nb, nc;
    semestre*tempS= buscarSem(codigoS);
    if(tempS==NULL){
        cout<<"El semestre ingresado no existe."<<endl;
        return;
    }
  
    //for charla in semestre->listacharlas, for estudiante in lista estudiantes, if
    //estudiante asistio a charla, sumar uno, compararlo con abc, hasta llegar al final.
    charla*tempC= tempS->listaCharlas;
    while(tempC!= NULL){
        int contAsistentesCharla=0;
        estudiante*tempE= listaEstudiantes;
        while(tempE!=NULL){
            if (buscarCharlaEst(tempE, tempC)==true){
                contAsistentesCharla+=1;
            }
            tempE=tempE->sigEst;
        }
        if(contAsistentesCharla>a){
            a= contAsistentesCharla;
            na= tempC->nombreCharla;
        }else if(contAsistentesCharla>b){
            b= contAsistentesCharla;
            nb= tempC->nombreCharla;
        }else if(contAsistentesCharla>c){
            c= contAsistentesCharla;
            nc= tempC->nombreCharla;
        }
        
        tempC=tempC->sigCharla;

    }
    cout<<"Para el semestre "<<codigoS%10<<" del "<<codigoS/10<<" las 3 charlas con más asistencia fueron: "<<endl;
    cout<<"Charla#1: "<<na<<" con "<<a<<" estudiantes"<<endl;
    cout<<"Charla#2: "<<nb<<" con "<<b<<" estudiantes"<<endl;
    cout<<"Charla#3: "<<nc<<" con "<<c<<" estudiantes"<<endl;
}


//------------------Menus-----------------------------------------------------------------------------------------------------

void menuPrincipal();

void menuEstudiante(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.(Only for activities )
Outputs:
        Functionality chosen by the user.
*/
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Realizar Actividad\nb- Participar en Charla\nc- Reporte de actividades por semana\n\n1- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    

    if(opcion == "a"){
        agregarActEstAux();
        menuEstudiante();
    }
    else if(opcion == "b"){
        insertarCharlaEstAux();
        menuEstudiante();
    }
    else if(opcion == "c"){
        reporte6();
        menuEstudiante();
    }
    else if(opcion == "1"){
        menuPrincipal();
    }else if(opcion == "z"){
        menuEstudiante();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuEstudiante();
    }
}

void menuProfesorAct(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.(Only for activities )
Outputs:
        Functionality chosen by the user.
*/
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
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.(Only for conferences )
Outputs:
        Functionality chosen by the user.
*/
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

void menuProfesorRep(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.(Only for reports )
Outputs:
        Functionality chosen by the user.
*/
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Actividades para la proxima semana\nb- Actividades para todo el semestre\nc- Actividades concluidas\nd- Estudiantes que participaron en todas las charlas \ne- Estudiantes que no han entregado asignaciones\n\n1- Volver al menu de profesor\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;    
    if(opcion == "a"){
        reporte1();
        menuProfesorRep();
    }
    else if(opcion == "b"){
        cout<<"Entrando a reporte 2"<<endl;
        reporte2();
        menuProfesorRep();
    }
    else if(opcion == "c"){
        reporte3Aux();
        menuProfesorRep();
    }
    else if(opcion == "d"){
        reporte4();
        menuProfesorRep();
    }else if(opcion == "e"){
        reporte5Aux();
        menuProfesorRep();
    }else if(opcion == "z"){
        reporteGruposProfe();
        menuProfesorRep();
    }
    else if(opcion == "1")
        menuProfesor();
    else if(opcion == "2")
        menuPrincipal();
    else{
        cout<<"Opcion Invalida"<<endl;
        menuProfesorRep();
    }
}

void menuProfesor(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
    cout<<"\nEscoja e ingrese el caracter de la opcion que desea realizar:"<<endl;
    cout<<"a- Actividades\nb- Charlas\nc- Reportes\n\n1- Volver al menu principal\n\n\nOpcion: ";
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
    else if(opcion == "c"){
        menuProfesorRep();
    }
    else if(opcion == "1"){
        menuPrincipal();
    }
    else if(opcion == "z"){
        imprimirActProf();
        menuProfesor();
    }
    else{
        cout<<"Opcion invalida"<<endl;
        menuProfesor();
    }
}
void menuAdmin();

void menuAdminReportes(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
    cout<<"\nEscoja e ingrese el reporte que desea generar:"<<endl;
    
    cout<<"a- Estudiantes que no han entregado ninguna actividad en algun curso\nb- 3 charlas con mas asistencia de un semestre\n\n1- Volver al menu de administrador\n2- Volver al menu principal\n\n\nOpcion: ";
    string opcion;
    cin>> opcion;

    if(opcion == "a"){
        reporte7();
        menuAdminSemestre();
    }
    else if(opcion == "b"){
        reporte8();
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

void menuAdminSemestre(){
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
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
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
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
/*
Inputs: 
        string opcion.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
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
        borrarGrupoEstAux();
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
/*
Inputs: 
        string opcionMenuAdminProf.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
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
        borrarGrupoProfAux();
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
/*
Inputs: 
        string opcionMenuAdmin.
Process:
        Displays a menu, asks for input, leads user to option chosen.
Outputs:
        Menu chosen by the user.
*/
    cout<<"\nEscoja e ingrese el caracter del objeto que desea modificar:"<<endl;
    cout<<"a- Insertar Administrador\nb- Profesores\nc- Estudiantes\nd- Semestres\ne- Cursos\nf- Insertar grupo\ng- Reportes\n\n0- Volver al menu principal\nOpcion: ";
    
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
    else if(opcionMenuAdmin == "g"){
        menuAdminReportes();
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
/*
Inputs: 
        Username for manager
        Password for manager

Process:
        Processes the username and password in order to give user access to account
Outputs:
        Continues in the program, respective menu
*/
    string nombreA;
    string contrasennaA;
    string opcion;
    administrador* temp = listaAdministradores;
    
    cout<<"Nombre de usuario: ";
    cin.sync();
    getline(cin, nombreA);

    if ((buscarAdmin(nombreA)) == NULL){
        cout<<"El usuario ingresado no existe. Si desea volver al menu principal digite 1: ";
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
        cin.sync();
        getline(cin, contrasennaA);
    
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
    cout<<"\n\n"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Bienvenido al sistema de Gestion de Actividades Curriculares"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Ingrese el numero de la seccion deseada: \n 1- Administrador\n 2- Usuario: Profesor\n 3- Usuario: Estudiante \n 4- Salir\nNumero: ";
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
/*
Inputs: 
        
Process:
        
Outputs:

*/
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
    insertarCurso("Estructuras de Datos", "IC", 2040);
    insertarCurso("Arquitectura de Computadoras", "IC", 3101);
    insertarCurso("Matematica Discreta", "MA", 2089);
    insertarCurso("Probabilidad", "MA", 3098);
    insertarCurso("Programacion Orientada a Objetos", "IC", 5021);
    cout<<"\tInsertando Profesores\n";
    insertarProf(11833, "Jose Ortega Granados");
    insertarProf(12345, "Marta Sanchez Obviedo");
    insertarProf(48503, "Pedro Peralta Aguirre");
    insertarProf(84728, "Gerardo Gonzales Ferrero");
    insertarProf(40284, "Lucia Mata Mata");
    cout<<"\tInsertando Estudiantes\n";
    insertarEst(202006, "Brenda Badilla Rodriguez");
    insertarEst(202105, "Earl Areck Alvarado");
    insertarEst(201935, "Crystel Zamora Guerrero");
    insertarEst(201919, "Julia Segura Chacon");
    insertarEst(201705, "Carmen Hernandez Mendez");
    cout<<"\tInsertanto Grupos\n";
    insertarGrupo("IC3101", buscarCurso("IC3101"), 50);
    insertarGrupo("IC3101", buscarCurso("IC3101"), 51);
    insertarGrupo("IC2040", buscarCurso("IC2040"), 20);
    insertarGrupo("IC2040", buscarCurso("IC2040"), 35);
    insertarGrupo("MA2089", buscarCurso("MA2089"), 43);
    cout<<"\tAsignado profesores a grupos\n";
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC3101", 51));
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC3101", 50));
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC2040", 20));
    relacionarGrupoProf(buscarProf(11833), encontrarGrupo("IC2040", 35));
    cout<<"\tAsignado estudiantes a grupos\n";
    relacionarGrupoEst(buscarEst(202006), encontrarGrupo("IC3101", 50));//Brenda grupo 50
    relacionarGrupoEst(buscarEst(202105), encontrarGrupo("IC3101", 51));//Earl grupo 51
    relacionarGrupoEst(buscarEst(201935), encontrarGrupo("IC3101", 50));//Crystel grupo 50
    relacionarGrupoEst(buscarEst(201919), encontrarGrupo("IC3101", 50));//Julia grupo 50
    relacionarGrupoEst(buscarEst(201705), encontrarGrupo("IC3101", 51));//Carmen grupo 51
    cout<<"\tCreando actividades\n";
    insertarActProf(encontrarGrupo("IC3101", 50), "Tarea", "1", 20210927, 1400);//Solo la hizo Brenda, no la hizo Crystel
    insertarActProf(encontrarGrupo("IC3101", 50), "Tarea", "2", 20210927, 1500);
    insertarActProf(encontrarGrupo("IC3101", 51), "Proyecto", "1", 20210927, 1600);//Lo hizo solo Earl, no lo hizo Carmen
    insertarActProf(encontrarGrupo("IC3101", 50), "Gira", "1", 20210926, 1600);//La hicieron Brenda y Crystel
    insertarActProf(encontrarGrupo("IC3101", 50), "Examen", "1", 20210925, 1600);//Solo lo hizo Crystel, no lo hizo Brenda
    insertarActProf(encontrarGrupo("IC3101", 51), "Examen", "2", 20210924, 1600);//Solo lo hizo Carmen, no lo hizo Earl
    cout<<"\tAgregando las actividades realizadas por los estudiantes\n";
    agregarActEst(buscarEst(202006), buscarAct(encontrarGrupo("IC3101", 50), "Tarea", "1"));//Brenda 50 IC3101
    agregarActEst(buscarEst(202006), buscarAct(encontrarGrupo("IC3101", 50), "Gira", "1"));//Brenda 
    agregarActEst(buscarEst(202006), buscarAct(encontrarGrupo("IC3101", 50), "Tarea", "2"));//Brenda 
    //agregarActEst(buscarEst(202006), buscarAct(encontrarGrupo("IC3101", 50), "Examen", "1"));//Brenda
    agregarActEst(buscarEst(201935), buscarAct(encontrarGrupo("IC3101", 50), "Gira", "1"));//Crystel 50 IC3101
    //agregarActEst(buscarEst(201935), buscarAct(encontrarGrupo("IC3101", 50), "Examen", "1"));//Crystel
    agregarActEst(buscarEst(202105), buscarAct(encontrarGrupo("IC3101", 51), "Proyecto", "1"));//Earl 51 IC3101
    agregarActEst(buscarEst(201705), buscarAct(encontrarGrupo("IC3101", 51), "Proyecto", "1"));//Carmen 51 IC3101
    agregarActEst(buscarEst(201705), buscarAct(encontrarGrupo("IC3101", 51), "Examen", "2"));//Carmen 51 IC3101
    cout<<"\tCreando charlas\n";
    insertarCharlaProf(buscarSem(20212), "IEEE Introduction", 20210923, 1300); //2021 octubre 30                         
    insertarCharlaProf(buscarSem(20212), "IA en videojuegos", 20210927, 1600); //Noviembre 3
    insertarCharlaProf(buscarSem(20212), "Habilidades Blandas en Ing. en Computacion", 20210925, 1500); //Julio 13
    insertarCharlaProf(buscarSem(20212), "La industria de videojuegos en Costa Rica", 20210926, 1700); //Setiembre 10
    insertarCharlaProf(buscarSem(20212), "Intercambio estudiantil a Alemania", 20210927, 1700); //Diciembre 27
    
    cout<<"\tInsertando estudiantes en charlas\t"<<endl;
    insertarCharlaEst(buscarEst(201935), buscarCharla(20212, "20212IEEE Introduction")); ///Ch1-4 Ch2-3 Ch3-2 Ch4-2 ch5-5
    insertarCharlaEst(buscarEst(201935), buscarCharla(20212, "20212IA en videojuegos"));
    insertarCharlaEst(buscarEst(201935), buscarCharla(20212, "20212Habilidades Blandas en Ing. en Computacion"));
    insertarCharlaEst(buscarEst(201935), buscarCharla(20212, "20212La industria de videojuegos en Costa Rica"));
    insertarCharlaEst(buscarEst(201935), buscarCharla(20212, "20212Intercambio estudiantil a Alemania"));

    insertarCharlaEst(buscarEst(202105), buscarCharla(20212, "20212IEEE Introduction"));
    insertarCharlaEst(buscarEst(202105), buscarCharla(20212, "20212IA en videojuegos"));
    insertarCharlaEst(buscarEst(202105), buscarCharla(20212, "20212Habilidades Blandas en Ing. en Computacion"));
    insertarCharlaEst(buscarEst(202105), buscarCharla(20212, "20212La industria de videojuegos en Costa Rica"));
    insertarCharlaEst(buscarEst(202105), buscarCharla(20212, "20212Intercambio estudiantil a Alemania"));

    insertarCharlaEst(buscarEst(201705), buscarCharla(20212, "20212Intercambio estudiantil a Alemania"));
    insertarCharlaEst(buscarEst(201705), buscarCharla(20212, "20212IA en videojuegos"));

    insertarCharlaEst(buscarEst(202006), buscarCharla(20212, "20212IEEE Introduction"));
    insertarCharlaEst(buscarEst(202006), buscarCharla(20212, "20212Intercambio estudiantil a Alemania"));

    insertarCharlaEst(buscarEst(201919), buscarCharla(20212, "20212IEEE Introduction"));
    insertarCharlaEst(buscarEst(201919), buscarCharla(20212, "20212Intercambio estudiantil a Alemania"));
    
    menuPrincipal();

    return 0;
}