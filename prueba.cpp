#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int semana(int anno, int mes, int dia){
    tm date={};
    date.tm_year=anno-1900;
    date.tm_mon=mes-1;
    date.tm_mday=dia;
    mktime(&date);

    return ((date.tm_yday-date.tm_wday+7)/7);
}

int date(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    return 10000*(now->tm_year + 1900) + 100*(now->tm_mon + 1)+ (now->tm_mday);
}

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
 
// Driver Code
int dayofweekaux()
{
    int dia = 6;
    int mes = 10;
    int anno = 2021;
    string diasSem[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
    int day = dayofweek(dia, mes, anno);
    cout<<"\n"<<day;
    cout<<"\n"<<diasSem[day];
    if(day>0){
        dia = dia-day;
        //cout<<dia;
        int domD = dia; 
        while(domD <= dia + 6){
            int sem = dayofweek(domD, mes, anno);//bruta
            cout<<domD<<" es "<<diasSem[sem]<<endl;
            domD = domD+1;
        }
    }
    return 0;
}

int main(){
    cout<<semana(2021, 9, 19)<<endl;
    dayofweekaux();
    cout<<date()<<endl;
    return 0;
}