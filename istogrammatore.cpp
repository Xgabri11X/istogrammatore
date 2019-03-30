#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

class isto {

    string nome;
    int ndat;
    double *dati;


    void contodati()
    {
        ifstream leggimi(nome.c_str());

        if(leggimi.fail()){
            cout<<"pirlone ti sei dimenticato di dare il nome"<<endl;
            cout<<"oppure il nome e' sbagliato  "<<nome<<endl;
        }
        else{
            cout<<"il file esiste! evviva ;)"<<endl;
        }
        ndat=0;
        double a;
        while (leggimi>>a)ndat++;
        return;
    }

    double * caricodati()
    {
        ifstream leggimi(nome.c_str());

        if(leggimi.fail()){
            cout<<"pirlone ti sei dimenticato di dare il nome"<<endl;
            cout<<"oppure il nome e' sbagliato  "<<nome<<endl;
        }
        else{
            cout<<"il file esiste! evviva ;)"<<endl;
        }
        double *pippo = new double[ndat];
        int i=0;
        double a;
        while(leggimi>>a){
            pippo[i]=a;
            i++;
        }
        return pippo;
    }

    public:

    isto() {                  //costruttore1

        cout<<"questa classe per funzionare ha bisogno del nome del file"<<endl;
        cout<<"ricordati di usare il metodo dammiilnome prima di chiedere roba \n"<<endl;
    }

    isto(string pippo) {     //costruttore2

        nome=pippo;
        contodati();
        dati = caricodati();

    }




    void dammiilnome(string pippo) {    //metodo utile per poter analizzare un altro file oltre dati_Lug.dat

        nome=pippo;
        contodati();
        dati = caricodati();
        return;
    }

    string ilnome() {

        return nome;
    }

    void stampoilnome() {

        cout<<nome<<endl;
        return;
    }

    void motistampouncasino() {
        for(int i=0;i<ndat;i++){
            cout<<dati[i]<<endl;
            return;
        }

    }

    int contadati() {
        return ndat;
    }

    double dammiilmassimo() {
        double massimo=dati[0];
        for(int i=1;i<ndat;i++){
            if(massimo<dati[i])massimo=dati[i];
        }
        return massimo;
    }

    double dammiilminimo() {
        double minimo=dati[0];
        for(int i=1;i<ndat;i++){
            if(minimo>dati[i])minimo=dati[i];
        }
        return minimo;

    }



    double lamedia() {

        double sommatoria=0;

        for(int i=0;i<ndat;i++){
            sommatoria=sommatoria+dati[i];
        }

        return sommatoria/double(ndat);
    }

    double devstandard() {

        double media= lamedia();

        double sommascarti=0;

        for(int i=0;i<ndat;i++){
            sommascarti=sommascarti+pow(media-dati[i],2);
        }

        return pow((sommascarti/double(ndat)),0.5);
    }

    double devstandardmedia() {

        double deviazionestandard=devstandard();
        double devstandardmedia=(deviazionestandard)/pow(double(ndat),0.5);

        return devstandardmedia;
    }


    int istogrammatoressolimit(int numdiv, double pino, double pina) {

        //vettore contenente le frequenze assolute dell'istogramma
        int isto[numdiv];
        double minimo =pino;
        double massimo = pina;
        //inizializziamo a zero i contatori dei bin dell'istogramma
        for(int i=0; i<numdiv; i++){
            isto[i]=0;
        }



        //ampiezza dell'intervallo
        double delta = (massimo-minimo)/double(numdiv);

        //loop per computare l'istogramma
        for(int j=0; j<ndat;j++){
            for(int k=0; k<numdiv; k++){
                if(dati[j]>=minimo+double(k)*delta && dati[j]< minimo +double(k+1)*delta){
                    isto[k]++;
                }
            }
        }

        isto[numdiv-1]++; //per tenere conto del massimo assoluto.

        //stampo il centroide dell'intervallo dell'istogramma e la frequenza assoluta dello stesso
        for(int i=0; i<numdiv; i++){
            cout<<minimo+delta/2+double(i)*delta<<" "<<isto[i]<<endl;

        }
    }


    int istogrammatoresso(int numdiv) {
        cout<<"carissima/o, vedi che istogramma tra massimo e minimo"<<endl;
        //vettore contenente le frequenze assolute dell'istogramma
        int isto[numdiv];
        double minimo = dammiilminimo();
        double massimo = dammiilmassimo();
        //inizializziamo a zero i contatori dei bin dell'istogramma
        for(int i=0; i<numdiv; i++){
            isto[i]=0;
        }


        //ampiezza dell'intervallo
        double delta = (massimo-minimo)/double(numdiv);

        //loop per computare l'istogramma
        for(int j=0; j<ndat;j++){
            for(int k=0; k<numdiv; k++){
                if(dati[j]>=minimo+double(k)*delta && dati[j]< minimo +double(k+1)*delta){
                    isto[k]++;
                }
            }
        }

        isto[numdiv-1]++; //per tenere conto del massimo assoluto.

        //stampo il centroide dell'intervallo dell'istogramma e la frequenza assoluta dello stesso
        for(int i=0; i<numdiv; i++){
            cout<<minimo+delta/2+double(i)*delta<<" "<<isto[i]<<endl;

        }
    }


    double simmetria() {                 //detta skewness, tale numero misura l' asimmetria della distribuzione rispetto al valor medio;
        //se è s=0 la curva è simmetrica ;se s>0 ci sarò un maggior numero di dati alla sinistra del valor medio
        //se s<0 ci saranno più dati a destra del valor medio

        double deviazionestandard=devstandard();
        double media=lamedia();
        double scarticubi=0;

        for(int j=0; j<ndat;j++){

            scarticubi=scarticubi+pow(media-dati[j],3);
        }

        return (scarticubi/double (ndat)*pow(deviazionestandard,3));
    }



};


int main(){

    isto pino("dati_Lug.txt");
    pino.motistampouncasino();
    /*
       double minimo=pino.dammiilminimo();
       double massimo=pino.dammiilmassimo();
       int contami=pino.contadati();
       */
    cout<<"Il file da analizzare e' "<<pino.ilnome()<<endl;

    string operazione;

    string ripeti2;

    do {
        cout<<"Scegliere l'operazione da effettuare tra le seguenti: conteggio, media, massimo, minimo, deviazione standard, deviazione standard della media, skewness, istogramma"<<endl;
        cin>>operazione;


        if (operazione=="conteggio") {
            cout<<"il numero di valori nel file e' "<<pino.contadati()<<endl;
        }

        if (operazione=="media") {
            cout<<"la media e' "<<pino.lamedia()<<endl;
        }

        if (operazione=="massimo") {
            cout<<"il massimo nel file e' "<<pino.dammiilmassimo()<<endl;
        }

        if (operazione=="minimo") {
            cout<<"il minimo nel file e' "<<pino.dammiilminimo()<<endl;
        }

        if (operazione=="deviazione standard") {
            cout<<"la deviazione standard e' "<<pino.devstandard()<<endl;
        }

        if (operazione=="deviazione standard della media") {
            cout<<"la deviazione standard della media e' "<<pino.devstandardmedia()<<endl;
        }

        if (operazione=="skewness") {
            cout<<"la skewness della distribuzione e' "<<pino.simmetria()<<endl;
        }


        if (operazione=="istogramma") {

            //cout<<"L'istogramma dei dati è: "<<endl;




            int numero_divisioni=20;
            int ripeti;
            do{

                cout<<"Inserire il numero di divisioni desiderate"<<endl;

                cin>>numero_divisioni;
                while(numero_divisioni<=0){
                    cout<<"OhOOOHHHHHHH dammi un numero di divisioni maggiore di zero \n";
                    cin>>numero_divisioni;

                }

                cout<<"carissima/o se vuoi istogrammare tra massimo e minimo digita 1, altrimenti 0 \n";
                int scelta=10;
                cin>>scelta;
                while(!(scelta==1||scelta==0)){
                    cout<<"ohhohohohoooo  dammi 1 o 0\n";
                    cin>>scelta;
                }

                if(scelta==1){
                    pino.istogrammatoresso(numero_divisioni);
                }

                if(scelta==0){
                    double low,up;
                    cout<<"dammi gli estremi inferiore e superiore\n";

                    cin>>low>>up;

                    pino.istogrammatoressolimit(numero_divisioni,low,up);

                }

                cout<<"vuoi rifare l'esercizio con un numero diverso di divisioni?"<<endl;
                cout<<"si, allora digita 1, altrimenti qualunque altro numero"<<endl;
                cin>>ripeti;
            }while(ripeti==1);

        }

        cout<<"Si desidera effettuare un'altra operazione?"<<endl;
        cout<<"In tal caso rispondi SI, altrimenti inserisci NO"<<endl;

        cin>>ripeti2;
    } while( ripeti2=="SI");


    return 0;
}


