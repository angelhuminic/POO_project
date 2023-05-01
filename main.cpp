#include <iostream>
#include <cstring>
#include <exception>

using namespace std;

/// Clasa pentru exceptie custom
class CarException : public exception
{
    virtual const char* what() const throw()
    {
        return "CarException occurred!";
    }
};

/// Clasa pentru exceptie custom pentru cand nu gasim o masina in showroom
class CarNotFoundException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Car not found!";
    }
};

/// Clasa de baza abstracta
class Automobil
{
protected:
    char marca[50];
    char model[50];
    int an_de_fabricatie;
public:
    Automobil()
    {

    }

    Automobil(const char* marca, const char* model, int an_de_fabricatie)
    {
        strcpy(this->marca, marca);
        strcpy(this->model, model);
        this->an_de_fabricatie = an_de_fabricatie;
    }

    virtual void afisare()=0; /// metoda virtuala

    virtual double getPret()=0; /// metoda virtuala

    virtual ~Automobil() /// destructor virtual
    {

    }
};

/// Clasa interfata
class MesajAfisat
{
public:
    virtual void afisare2()=0; /// metoda virtuala

    virtual ~MesajAfisat() /// destructor virtual
    {

    }
};

/// Clasa interfata 2
class AltAutomobil
{
public:
    virtual ~AltAutomobil()
    {

    }
    virtual void start()=0;

    virtual void stop()=0;
};

/// Clasa pentru un sistem Start/Stop care se foloseste de interfata de AltAutomobil
class Start_Stop : public AltAutomobil
{
public:
    void start()
    {
        cout << "Car started" << endl;
    }

    void stop()
    {
        cout << "Car stopped" << endl;
    }
};

/// Clasa pentru masina care mosteneste clasa Automobil si implementeaza clasa MesajAfisat
class Masina : public Automobil, public MesajAfisat
{
private:
    double pret;
public:
    Masina()
    {

    }

    Masina(const char* marca,const char* model,int an_de_fabricatie,double pret) : Automobil(marca,model,an_de_fabricatie)
    {
        this->pret=pret;
    }

    void afisare()
    {
        cout<<"Marca: "<<marca;
        cout<<endl;

        cout<<"Model: "<<model;
        cout<<endl;

        cout<<"An de fabricatie: "<<an_de_fabricatie;
        cout<<endl;

        cout<<"Pret: "<<pret<<"$ ";
        cout<<endl;
    }

    double getPret()
    {
        return pret;
    }

    void afisare2()
    {
        cout<<"This is a car"<<endl;
    }

    /*
    double getPrice()
    {
        return pret;
    }
    */
    void setPrice(double pret)
    {
        this->pret=pret;
    }
};

/// Clasa pentru showroom
class Showroom
{
private:
    char nume[50];
    int nr_masini;
    Masina* masini[100];
    static int totalNumCars;
public:
    Showroom()
    {

    }

    Showroom(const char* nume)
    {
        strcpy(this->nume, nume);
        nr_masini=0;
    }

    void adaugare_masina(Masina* masina)
    {
        masini[nr_masini++]=masina;
        totalNumCars++;
    }

    double getPretTotalMasiniNet()
    {
        double prettotal=0.0;
        for (int i=0;i<nr_masini;i++)
        {
            prettotal+=masini[i]->getPret();
        }
        return prettotal;
    }

    double getPretTotalMasiniBrut(double procentTVA)
    {
        double prettotal=getPretTotalMasiniNet();
        return prettotal*(1+procentTVA);
    }

    void afisareMasini()
    {
        cout<<"Masini in stocul "<<nume<<":"<<endl;
        cout<<endl;
        for(int i=0;i<nr_masini;i++)
        {
            masini[i]->afisare();
            cout << endl;
        }
    }

    static int getTotalNumCars()
    {
        return totalNumCars;
    }
};

/// Clasa pentru cumparator
class Cumparator
{
private:
    char nume[50];
    char adresa[50];
    char numar_de_telefon[15];
public:
    Cumparator()
    {

    }

    Cumparator(char* _nume,char* _adresa,char* _numar_de_telefon)
    {
        strcpy(nume, _nume);
        strcpy(adresa, _adresa);
        strcpy(numar_de_telefon, _numar_de_telefon);
    }

    Cumparator(const Cumparator& other)
    {
        strcpy(nume, other.nume);
        strcpy(adresa, other.adresa);
        strcpy(numar_de_telefon, other.numar_de_telefon);
    }

    char* getNume()
    {
        return nume;
    }

    void setNume(char* _nume)
    {
        strcpy(nume, _nume);
    }

    char* getAdresa()
    {
        return adresa;
    }

    void setAdresa(char* _adresa)
    {
        strcpy(adresa, _adresa);
    }

    char* getNumardetelefon()
    {
        return numar_de_telefon;
    }

    void setNumardetelefon(char* _numar_de_telefon)
    {
        strcpy(numar_de_telefon, _numar_de_telefon);
    }

    void display() const
    {
        cout<<"Nume: "<<nume;
        cout<<endl;

        cout<<"Adresa: "<<adresa;
        cout<<endl;

        cout<<"Numar de telefon: "<<numar_de_telefon;
        cout<<endl;
    }
};

/// Clasa pentru vanzator
class Vanzator
{
private:
    char nume[50];
    char numar_de_telefon[20];
    int nr_vanzari_facute;
public:
    Vanzator()
    {

    }

    Vanzator(const char* nume,const char* numar_de_telefon)
    {
        strcpy(this->nume, nume);
        strcpy(this->numar_de_telefon, numar_de_telefon);
        nr_vanzari_facute=0;
    }

    void afisare()
    {
        cout<<"Nume: "<<nume;
        cout<<endl;

        cout<<"Numar de telefon: "<<numar_de_telefon;
        cout<<endl;

        cout<<"Vanzari incheiate: "<<nr_vanzari_facute;
        cout<<endl;
    }

    int getNrVanzari()
    {
        return nr_vanzari_facute;
    }

    void setNrVanzari(int nr_vanzari_facute)
    {
        this->nr_vanzari_facute=nr_vanzari_facute;
    }
};

/// Clasa pentru detalii cumparare masina care mosteneste clasa Automobil
class Tranzactieefectuata : public Automobil
{
private:
    char nume_cumparator[50];
    char nume_vanzator[50];
    double pretplatitdupadiscounturi;
public:
    Tranzactieefectuata()
    {

    }

    Tranzactieefectuata(const char* marca, const char* model, int an_de_fabricatie, const char* nume_cumparator, const char* nume_vanzator, double pretplatitdupadiscounturi) : Automobil(marca, model, an_de_fabricatie)
    {
        strcpy(this->nume_cumparator, nume_cumparator);
        strcpy(this->nume_vanzator, nume_vanzator);
        this->pretplatitdupadiscounturi = pretplatitdupadiscounturi;
    }

    void afisare()
    {
        cout<<"DETALIILE TRANZACTIEI:"<<endl;
        cout<<endl;

        cout<<"Marca: "<<marca;
        cout<<endl;

        cout<<"Model: "<<model;
        cout<<endl;

        cout<<"An de fabricatie: "<<an_de_fabricatie;
        cout<<endl;

        cout<<"Nume Client: "<<nume_cumparator;
        cout<<endl;

        cout<<"Nume Vanzator: "<<nume_vanzator;
        cout<<endl;

        cout<<"Sale Price: "<<pretplatitdupadiscounturi;
        cout<<endl;
    }

    double getPret()
    {
        return pretplatitdupadiscounturi;
    }
};

/// Variabila membru statica pentru clasa Showroom
int Showroom::totalNumCars=0;

int main()
{
    /// Creez un showroom (ii dam numele aici)
    Showroom showroom("BMW M Romania");

    /// Apoi adaug masini in showroom
    Masina masina1("BMW", "M2", 2017, 51000);
    Masina masina2("BMW", "M2 Competition", 2016, 55000);
    Masina masina3("BMW", "M3 Coupe", 2022, 112600);
    Masina masina4("BMW", "M4 CSL", 2022, 207900);
    Masina masina5("BMW", "M4 Cabriolet", 2016, 59000);
    Masina masina6("BMW", "M5", 2020, 90000);
    Masina masina7("BMW", "M5 Competition", 2021, 106000);
    Masina masina8("BMW", "M8 Competition", 2022, 149000);
    Masina masina9("BMW", "M760 Li", 2016, 58900);
    Masina masina10("BMW", "X3 40d", 2021, 69000);
    Masina masina11("BMW", "X5 50d", 2015, 39800);
    Masina masina12("BMW", "X5 50d", 2019, 59700);
    Masina masina13("BMW", "X7 50i", 2021, 87299);
    Masina masina14("BMW", "X6M", 2021, 99500);
    Masina masina15("BMW", "X6M", 2023, 161200);

    showroom.adaugare_masina(&masina1);
    showroom.adaugare_masina(&masina2);
    showroom.adaugare_masina(&masina3);
    showroom.adaugare_masina(&masina4);
    showroom.adaugare_masina(&masina5);
    showroom.adaugare_masina(&masina6);
    showroom.adaugare_masina(&masina7);
    showroom.adaugare_masina(&masina8);
    showroom.adaugare_masina(&masina9);
    showroom.adaugare_masina(&masina10);
    showroom.adaugare_masina(&masina11);
    showroom.adaugare_masina(&masina12);
    showroom.adaugare_masina(&masina13);
    showroom.adaugare_masina(&masina14);
    showroom.adaugare_masina(&masina15);

    ///Si le afisez
    showroom.afisareMasini();
    cout<<endl;

    cout << "Numar total de masini in stoc: " << Showroom::getTotalNumCars() << endl;

    double prettotal=showroom.getPretTotalMasiniNet();
    cout<<endl;
    cout<<"Pret total al masiniilor din showroom(Net): "<<prettotal<<"$ "<<endl;

    /// Aici calculez cat costa toate masiniile care sunt in showroom(pret Brut(adica cu TVA))
    double procentTVA=0.19; // 19% TVA
    double prettotalcuTVA=showroom.getPretTotalMasiniBrut(procentTVA);
    //cout << "Total price of cars: " << showroom.getPretTotalMasiniNet() << "$ " << endl;
    cout<<"Pret total al masiniilor din showroom(Brut): "<<prettotalcuTVA<<"$ "<<endl;

    /// Creez un cumparator
    Cumparator cumparator("Andrei Victor","Strada Nr. 1", "111111");
    cout<<endl;

    /// Creez un vanzator
    Vanzator vanzator("Alex Ion", "222222");
    cout<<endl;

    /// Introduc datele pentru o tranzactie
    Tranzactieefectuata tranzactie("BMW", "M4 CSL", 2022, "Andrei Victor", "Alex Ion", 197000);
    cout<<endl;


    //cout << "Cars in inventory: " << endl;
    //showroom.afisareMasini();

    cout<<"Detalii cumparator: "<<endl;
    cout<<endl;
    cumparator.display();
    cout<<endl;

    cout<<"Detalii vanzator: "<<endl;
    cout<<endl;
    vanzator.afisare();
    cout<<endl;

    tranzactie.afisare();
    cout<<endl;

    /// Cream un sistem de start/stop care foloseste interfata de AltAutomobil
    Start_Stop sistemstartstop;

    /// Folosim sistemul de Start/Stop al masinii, care foloseste interfata de AltAutomobil
    sistemstartstop.start();
    sistemstartstop.stop();
    cout<<endl;

    /// Exceptii
    try
    {
        throw CarNotFoundException();
    }
    catch (exception& e)
    {
        cout<<"Eroare: "<<e.what()<<endl;
    }

    cout<<endl;

    try
    {
        throw CarException();
    }
    catch (exception& e)
    {
        cout<<"Eroare: "<<e.what()<<endl;
    }

    cout<<endl;

    try
    {
        throw runtime_error("Runtime error occurred");
    }
    catch (exception& e)
    {
        cout<<"Caught exception: "<<e.what();
        cout<<endl;
        throw logic_error("Logic error occurred");
    }

    return 0;
}

///Polimorfism la execuție în proiectul dat:
/*
    ->Apelul metodei afisare() în clasa Masina prin intermediul pointerului MesajAfisat* mesaj.
    ->Apelul metodei afisare2() în clasa Showroom prin intermediul pointerului MesajAfisat* mesaj.
    ->În clasa Showroom, în metoda adaugare_masina(), se primește un obiect de tipul clasei Automobil
și se adaugă un pointer la acel obiect într-un array de pointeri de tipul clasei Masina.
    ->În clasa Masina, în metoda getPret(), se suprascrie metoda din clasa de bază Automobil.
*/


///Upcasting în proiectul dat:
/*
    ->În metoda afisareMasini() din clasa Showroom, se apelează metoda afisare() a clasei Masina pe fiecare
element din array-ul de pointeri de tipul Automobil* masini.
    ->În clasa Start_Stop, se apelează metodele start() și stop() ale clasei AltAutomobil, deși obiectul este de fapt
de tipul Start_Stop.
    ->În metoda adaugare_masina() din clasa Showroom, se primește un pointer la un obiect de tipul Automobil și se adaugă
un pointer la acel obiect într-un array de pointeri de tipul Masina.
    ->În metoda getPretTotalMasiniNet() din clasa Showroom, se apelează metoda getPret() a clasei Automobil pe fiecare
element din array-ul de pointeri de tipul Masina.
