
}

int menuPrincipal(){
    /*
    F: Displays the main menu for user to choose between Administrator or User.
    I: Number of choice.
    O: Respective function in the system.
    */
    cout<<"Bienvenido al sistema de Gestion de Actividades Curriculares"<<endl;
    cout<<"Ingrese \n1- Administrador\n 2-Usuario"<<endl;
    int opcion;
    cin>>opcion;
    if(opcion=="1"){
        cout<<"Administrador"<<endl;
        ingresarAdmin();
    }else if(opcion=="2"){
        cout<<"Usuario"<<endl;
    }else{
        cout<<"Ingrese una opcion valida.";
        menuPrincipal();
    }
}

void main(){
    menuPrincipal();
}