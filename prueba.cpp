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

int main(){
    cout<<semana(2021, 9, 19)<<endl;
    return 0;
}