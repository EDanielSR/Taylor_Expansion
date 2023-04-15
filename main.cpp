#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <windows.h>
using namespace std;

class Polinomio
{
    public:
        Polinomio();
        ~Polinomio();
        void derivar_polinomio();
        void imprimir_polinomio();
        void imprimir_matriz();
        double evaluar_polinomio();
        double fx;
        void evaluar_origen();
        double factorial(int num);
        double expansion(int g);
        double error_verdadero(int g);
        void imprimir_resultados();
        void gotoxy(int x,int y){
          HANDLE hcon;
          hcon = GetStdHandle(STD_OUTPUT_HANDLE);
          COORD dwPos;
          dwPos.X = x;
          dwPos.Y= y;
          SetConsoleCursorPosition(hcon,dwPos);
        };
    private:
        int m;
        int n;
        int filas;
        int columnas;
        double** matA;
        int x0;
        int x;
        double* fx0;
};

Polinomio::Polinomio(){
    cout<<"  Ingresa el grado del polinomio: "; cin>>m;
    cout<<"  Ingresa el grado de aproximacion del polinomio: "; cin>>n;
    cout<<"  Ingresa el punto de origen de la aproximacion: "; cin>>x0;
    cout<<"  Ingresa el punto a evaluar: "; cin>>x;
                //-- matriz --
                filas=n+1;
                columnas=2*(m+1);

                matA= new double*[filas];
                for( int i=0; i<filas; i++ )
                  matA[i] = new double[columnas];

                for(int i=0; i<filas;i++){
                    for(int j=0;j<columnas;j++){
                        matA[i][j]=0;
                    }
                }
    int exp=m;
    cout<<endl;
    for(int j=0; j<columnas;j=j+2){
        cout<<"  Ingresa el coeficiente de x^"<<exp<<"= ";
        cin>>matA[0][j];
        matA[0][j+1]=exp;
        exp--;
    }
}

Polinomio::~Polinomio(){
     for(int i = 0; i <n+1; i++){
            delete [] matA[i];
        }
        delete [] matA;
}

void Polinomio::imprimir_polinomio(){
    cout<<"\n  El polinomio ingresado es:  ";
    for(int k=0;k<columnas;k=k+2){
        cout<<matA[0][k];
        if(k+2<columnas)
            cout<<" x^"<<matA[0][k+1]<<" + ";
    }
    cout<<endl;
}

void Polinomio::derivar_polinomio(){
    for(int i=0;i<filas-1;i++){
        for(int j=0;j<columnas;j=j+2){
            matA[i+1][j]=matA[i][j+1]*matA[i][j];
                if (matA[i][j+1]==0){
                    matA[i+1][j+1]=0;
                }
                else{
                    matA[i+1][j+1]=(matA[i][j+1])-1;
                }
        }
    }
}

void Polinomio::imprimir_matriz(){
    for(int i=0; i<filas;i++){
        for(int j=0;j<columnas;j++){
            cout<<"["<<matA[i][j]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

double Polinomio::evaluar_polinomio(){
    double fx=0;
    for(int j=0;j<columnas;j=j+2){
        fx=fx+matA[0][j]*(pow(x,matA[0][j+1]));
    }
    return fx;
}

void Polinomio::evaluar_origen(){
    fx0= new double [filas];

    for(int j=0;j<filas;j++){
        fx0[j]=0;
    }

    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j=j+2){
            fx0[i]=fx0[i]+matA[i][j]*(pow(x0,matA[i][j+1]));
        }
    }
}

double Polinomio::factorial(int num){
    int n=num;
    double factorial=1;

    for(int i=1;i<=n;i++)
        factorial=factorial*i;

    return factorial;
}

double Polinomio::expansion(int g){
    int aprox=g;
    double serie=0;
    int tam_paso=x-x0;

    for(int c=0;c<=aprox;c++){
        serie=serie+((fx0[c]/factorial(c))*(pow(tam_paso,c)));
    }

    return serie;
}

double Polinomio::error_verdadero(int g){
    int aprox=g;
    double error;
    double serie=expansion(aprox);

    error=abs(((fx-serie)/fx)*100);

    return error;
}

void Polinomio::imprimir_resultados(){
    int posy=6;
    gotoxy(1,posy);cout<<"-----------------------------------------------------------------";
    gotoxy(1,posy-1);cout<<"  Grado de aprox."<<endl;
    for(int i=0;i<=n;i++){
        gotoxy(10,posy+1);cout<<i;
        cout<<endl;
        posy++;
    }
    posy=6;
    gotoxy(25,posy-1);cout<<"f(x)"<<endl;
    for(int i=0;i<=n;i++){
        gotoxy(25,posy+1);cout<<fx;
        cout<<endl;
        posy++;
    }
    posy=6;
    gotoxy(40,posy-1);cout<<"fn(x)"<<endl;
    for(int i=0;i<=n;i++){
        gotoxy(40,posy+1);cout<<expansion(i);
        cout<<endl;
        posy++;
    }
    posy=6;
    gotoxy(55,posy-1);cout<<"  Ev"<<endl;
    for(int i=0;i<=n;i++){
        gotoxy(55,posy+1);cout<<error_verdadero(i)<<"%";
        cout<<endl;
        posy++;
    }
}

int main()
{
    cout<<endl<<"\t\tEXPANSION DE TAYLOR-MCLAURIN"<<endl<<endl;

    //-- Genesis del polinomio --
    Polinomio p;
    p.derivar_polinomio();
    p.fx=p.evaluar_polinomio();
    p.evaluar_origen();

    cout<<endl<<"  ";
    system("pause");
    system("cls");

    p.imprimir_polinomio();
    cout<<endl;
    cout<<"  La serie de expansion de Taylor es:"<<endl<<endl;
    p.imprimir_resultados();


    cout<<endl<<endl<<"  ";
    system("pause");
    return 0;
}
