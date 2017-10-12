#include<iostream>
#include<fstream>
#include<iomanip>
#include "timespan.h"

using namespace std;
struct dato{
       float hora,min,seg,tam,dest,num;

       dato *next;


       };

int lee(dato *f,int &cant);
dato* creardato (void);
dato* agregardato  (dato *l, dato *n);
float cinco(dato *f,int cant);

void  mostrar (dato *d,int cant);
void borrar(dato *l);
int cuarto(dato *f,int cant,float &registro);

int main(){

    int begginingTimestamp = getMilliCount();
    dato info,*aux=NULL,*lista;
    int cant=0,error=0,i=0;
    float num=0.0;
error=lee(&info,cant);
if(error==1){cerr<<"hubo algun problema interno."<<endl;}

 cout << "Took " + to_string(getMilliSpan(begginingTimestamp)) + " milliseconds";
 return 0;
}

int lee(dato *f,int &cant){

    char nombre[30];
    dato *aux=NULL,*lista=NULL;
    int i=0,error=0,c=0;
    ifstream entrada;
    float num=0.0,flag=0.0,total=0.0;
    cout<<"ingrese nombre archivo: "<<endl;
    cin>>nombre;
    entrada.open(nombre);

    if(entrada.fail())
    { error=1;
    cerr<<"no se pudo abrir el archivo"<<endl;}
    else{


         while(!entrada.eof()){
         cant++;
          aux=creardato();



         entrada>>aux->hora;

         entrada>>aux->min;

         entrada>>aux->seg;

         entrada>>aux->tam;

         entrada>>aux->dest;
    lista=agregardato(lista,aux);


         }
           mostrar(lista,cant);

        c=cuarto(lista,cant,total);
     cout<<"la canidad de paquetes es: "<<c<<" son = "<<total<<" kilobytes "<<endl;
        cinco(lista,cant);
         entrada.close();
         cant--;

}
   return error;
}


dato* creardato (void) {
  dato *aux=NULL;

  aux = new dato;
  if (aux==NULL) {
    cerr << "Memoria insuficiente" << endl;
  }
  else {

    aux->next=NULL;
  }
   cout << "creando dato" << endl;
  return aux;
}


dato* agregardato  (dato *l, dato *n) {
  dato *aux=NULL;

  if (l==NULL) {
    l=n;
  }
  else {
    aux=l;
    while(aux->next!=NULL) {
      aux=aux->next;
    }
    aux->next=n;

  }
  return l;
}
void  mostrar (dato *d,int cant) {
      int  i=0;
  for(i=0;i<cant-1;i++){
    cout<<setw(7)<< d->hora <<setw(7)<< d->min<<setw(7)<< d->seg<<setw(7)<< d->tam<<setw(7)<< d->dest<<endl;
    d=d->next;

}
}
void borrar(dato *l){
     dato *aux=NULL;
     while(l!=NULL){
     aux=l;
     l=l->next;
     delete aux;
     }
}
int  cuarto(dato *f,int cant,float &total) {
      int c=0,i=0;
      float tam=0.0,dest=0.0;
      dest=f->dest;


  while(f!=NULL){
                 if(f->dest==dest)
                 {c++;
              tam+=f->tam;

                 }
              total=tam/1000;

f=f->next;

}
return c;
}
float cinco(dato *f,int cant){
      float *v=NULL,difh=0.0,tamvector=0.0,difm=0.0,difs=0.0,totalsegundos=0.0,hinicial=0.0,hfinal=0.0,minicial=0.0,mfinal=0.0,sinicial=0.0,sfinal=0.0;
     int i=0;
      hinicial=f->hora;
      minicial=f->min;
      sinicial=f->seg;

      for(i=0;i<cant-2;i++){
                     f=f->next;
                     hfinal=f->hora;
                     mfinal=f->min;
                     sfinal=f->seg;
                     }
                     difh=hfinal - hinicial;
                     difm=mfinal - minicial;
                     difs=sfinal - sinicial;
                     totalsegundos=difh*36000 + difm*60 + difs;
                     cout<<"hora inicial"<<totalsegundos<<"hora final"<<hfinal<<endl;
tamvector=totalsegundos/5;
v=new float[tamvector];



}
