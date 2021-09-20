/*
Una lista doble de estudiantes, y una lista circular de Cursos. Necesitamos
una lista simple que muestre cada curso matriculado por cada estudiante. 

         Juan <-> Maria <-> Pedro <-> Luis
           |        |         |        |
       matricula matricula  matricula  matricula  (Casa uno apunta de un curso)
           
         Intro <-> POO <-> Arky <-> Datos
*/

#include <iostream>

using namespace std;

//.......................Estructuras...........................

struct estudiante{//Lista doble
    string nombre;
    estudiante *sig, *ant; //Puede ponerse struct estudiante *sig, *ant;
    struct matricula *suM;//su matricula. Si no llamamos al struct va a dar error porque se llama estando debajo
    
    estudiante(string n){
        nombre = n;
        sig = NULL;
        ant = NULL;
        suM = NULL;
    }
}*ListaEstudiante;//Lista doble: tiene sig y ant

struct curso{//Lista circular de los cursos por estudiante
    string nombre;
    curso *sig;

    curso(string c){
        nombre = c;
        sig = NULL;
    }
}*ListaCurso;

struct matricula{//Lista simple
    matricula *sig;
    curso *enlaceC; //Apunta al curso matriculado 

    matricula(curso *enlaceCurso){
        enlaceC = enlaceCurso;
        sig = NULL;
    }
};

//......................Metodos


//--------Metodos de Estudiante

//Inserta estudiante en una lista doble
//Insercion al incio 
estudiante *insertarInicioLD(string n){

    struct estudiante *nn = new estudiante(n); //Creamos un nuevo nodo que es el nuevo estudiante

    nn->sig = ListaEstudiante;

    if(ListaEstudiante != NULL) //Si esta vacia
        ListaEstudiante->ant = nn; //Como insertamos al inicio
                                //El anterior del incio es nuestro nuevo nodo
    
    ListaEstudiante = nn; //Sino esta vacia, el primer elemento es el nuevo

    return ListaEstudiante;
}

void imprimirEstudiantes(){

    struct estudiante *temp = ListaEstudiante; //Creamos el nodo que va a pasar por toda la lista. Por eso se iguala al primer nodo.

    while (temp != NULL){
        cout<<"\n Nombre: "<<temp->nombre;
        temp = temp->sig;
    }
}

estudiante *buscarEstudiante(string n){
    struct estudiante *temp = ListaEstudiante;
    while(temp != NULL){
        if(temp->nombre == n)
            return temp;
        temp = temp->sig;//Si no coincide avanza al siguiente
    }
    return NULL;//Si sale del while significa que paso por toda la lista sin coincidencias. No esta, retorna nulo.
}

//-------Metodos de Curso

//Inserta un curso al inicio de la lista circular ListaCurso
curso *insertarInicioLC(string n){
    struct curso *nn = new curso(n);

    if(ListaCurso == NULL){//Si esta vacia 
        ListaCurso = nn; //Al ser circular, se apunta a si misma
        ListaCurso->sig = ListaCurso;
    }
    else{//Si tiene elementos
        struct curso *temp = ListaCurso;//Nodo temporal para recorrer la lista
        while(temp->sig != ListaCurso){//Recorremos la lista hasta llegar al final. Ahi se inserta el nuevo nodo ya que es circular.
            temp = temp->sig;
        }
        temp->sig = nn; //Insertamos el nuevo nodo al final de la lista
        nn->sig = ListaCurso;// Lo enlazamos al inicio

        ListaCurso = nn; //Se asigna como el primer elemento de la lista
    }
    return ListaCurso;
}

void imprimirCursos(){
    if(ListaCurso==NULL)
        cout<<"\n Lista vacia. No hay cursos.";
    else{
        struct curso *temp = ListaCurso;
        do{
            cout<<"\n Curso: " <<temp->nombre;
            temp = temp->sig;
        }while(temp != ListaCurso);
    }
} 

curso *buscarCurso(string nom){
    if (ListaCurso == NULL)
        return NULL;
    
    struct curso *temp = ListaCurso;
    do{
        if(temp->nombre == nom)
            return temp;
        temp = temp->sig;
    }while(temp != ListaCurso);
    return NULL;
}

//--------------Metodos de Matricula

void matricular(string estudiante, string curso){
    struct curso *tempCurso = buscarCurso(curso);
    struct estudiante *tempEst = buscarEstudiante(estudiante);

    //Revisamos que ambos datos se encuentren en las listas
    if(tempCurso == NULL || tempEst == NULL){
        if(tempCurso == NULL)
            cout<<"\nCurso no existe";
        else if(tempEst == NULL)
            cout<<"\nEstudiante no existe";
        return ;
    }
    matricula *nnM = new matricula(tempCurso);
    nnM->sig = tempEst->suM;
    tempEst->suM = nnM; 

    //nnM->enlaceC = tempCurso;  : Al crear la matricula, enlazo el curso al ingresado. (Vease en el constructor)
    //nnM->sig = tempEst->suM;   : Para enlazarlo al estudiante, apuntamos al primer elemento de la lista de cursos matriculados
    //tempEst->suM = nnM;        : Finalmente, como insertamos al inicio, convertimos la nueva matricula al primer nodo de la lista.
}

void reporteMatricula(string nomEst){

    estudiante *tempEst = buscarEstudiante(nomEst);
    if(tempEst == NULL){
        cout<<"\n No existe el estudiante";
        return;
    }
    else{
        cout<<"\n-------Informe de Matricula--------\n";
        cout<<"\n Nombre del estudiante: " <<tempEst->nombre<<endl;
        cout<<"\n Cursos Matriculados: \n";
        matricula *tempM = tempEst->suM;
        while(tempM != NULL){
            cout<<tempM->enlaceC->nombre<<endl;
            tempM = tempM->sig;
        }
        cout<<"\n......Ultima Linea...........\n";
    }
}

//......................Programa Principal 

int main(){
    ListaEstudiante = insertarInicioLD("Pedro");
    ListaEstudiante = insertarInicioLD("Juan");
    ListaEstudiante = insertarInicioLD("Carlos");
    ListaEstudiante = insertarInicioLD("Ana");

    ListaCurso = insertarInicioLC("POO");
    ListaCurso = insertarInicioLC("Estructuras de Datos");
    ListaCurso = insertarInicioLC("Taller");
    ListaCurso = insertarInicioLC("Intro");

    imprimirEstudiantes();
    imprimirCursos();

    matricular("Juan", "Estructuras de Datos");
    matricular("Juan", "Taller");    
    matricular("Juan", "Intro");
    matricular("Juan", "POO");

    matricular("Ana", "Taller");
    matricular("Ana", "Intro");    

    reporteMatricula("Juan");
    reporteMatricula("Ana");


    return 0;   
}