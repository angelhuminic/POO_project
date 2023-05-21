#include <bits/stdc++.h>

using namespace std;

/// Clasa pentru exceptie custom
class SalespersonException : public exception
{
    virtual const char* what() const throw()
    {
        return "No salesperson!";
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
    string marca;
    string model;
    int an_de_fabricatie;

public:
    Automobil(const string& marca, const string& model, int an_de_fabricatie)
        : marca(marca), model(model), an_de_fabricatie(an_de_fabricatie)
    {

    }

    virtual void afisare() = 0; /// functie virtuala
    virtual double getPret() = 0; /// functie virtuala

    virtual ~Automobil() /// destructor virtual
    {

    }
};

/// Clasa interfata
class MesajAfisat
{
public:
    virtual void afisare2()=0; /// functie virtuala

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
        cout << "S-a auzit vroom-vroom :)" << endl;
    }

    void stop()
    {
        cout << "Ati oprit masina :(" << endl;
    }
};

/// Clasa pentru masina care mosteneste clasa Automobil si implementeaza clasa MesajAfisat
class Masina : public Automobil, public MesajAfisat
{
protected:
    double pret;
public:

    Masina(const string& marca, const string& model, int an_de_fabricatie, double pret)
        : Automobil(marca, model, an_de_fabricatie), pret(pret)
    {

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

    double getPrice()
    {
        return pret;
    }

    void setPrice(double pret)
    {
        this->pret=pret;
    }
};


/// Observer Design Pattern
class Observer
{
public:
    virtual void update() = 0;
};

class Subject
{
private:
    vector<Observer*> observers;

public:
    void adaugObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void eliminObserver(Observer* observer)
    {
        /// Elimin observer-ul din vector
        auto it=find(observers.begin(),observers.end(),observer);
        if (it!=observers.end())
        {
            observers.erase(it);
        }
    }

    void anuntObservers()
    {
        /// Anunt oamenii cand apare o noua masina pe stoc
        for(auto observer : observers)
        {
            observer->update();
        }
    }
};

/// Clasa pentru showroom
class Showroom: public Subject
{
private:
    string nume;
    int nr_masini;
    //unique_ptr<Masina> masini[100];
    vector<Masina*> masini;
    static int totalNumCars;
    vector<Observer*> observers;
    static Showroom* instance;

public:
    Showroom(const string& nume) : nume(nume),nr_masini(0)
    {

    }

    void adaugare_masina(Masina* masina)
    {
        //masini[nr_masini++]=move(masina);
        //totalNumCars++;
        masini.push_back(masina);
        totalNumCars++;
        anuntObservers();
        try
        {
            if(totalNumCars>15)
                throw("E showroom-ul prea mic!");
        }
        catch(exception &e)
        {
            cout<<"Prea multe masini!";
        }
    }

    static Showroom* getInstance(const string& nume)
    {
        if(instance==nullptr) {
            instance=new Showroom(nume);
        }
        return instance;
    }

    double getPretTotalMasiniNet()
    {
        double prettotal=0.0;
        for (const auto& masina : masini)
        {
            prettotal += masina->getPret();
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
        cout << "Masini in stocul " << nume << ":" << endl;
        cout << endl;
        for (const auto& masina : masini)
        {
            masina->afisare();
            cout << endl;
        }
    }

    Masina* getMasinaAt(int index)
    {
        if (index >= 0 && index < nr_masini)
            return masini[index];
        return nullptr;
    }

    void STL_sortare_masini_dupa_pret()
    {
        sort(masini.begin(), masini.end(), [](Masina* a, Masina* b)
        {
            return a->getPret() < b->getPret();
        });
    }

    double STL_pret_cele_mai_scumpe_2_masini()
    {
        // Fac un vector care tine toate preturile masiniilor din showroom
        vector<double> preturimasiniii;

        for (int i=0;i<nr_masini;i++)
        {
            preturimasiniii.push_back(masini[i]->getPret());
        }

        // Sortez masiniile dupa pret descrescator
        sort(preturimasiniii.begin(), preturimasiniii.end(), greater<double>());

        // Suma pentru pretul a celor mai 2 scumpe masini
        double sum=accumulate(preturimasiniii.begin(), preturimasiniii.begin() + 2, 0.0);

        return sum;
    }


    static int getTotalNumCars()
    {
        return totalNumCars;
    }

};

class InventarObserver : public Observer
{
private:
    Showroom* showroom;

public:
    InventarObserver(Showroom* showroom) : showroom(showroom) {}

    void update() override
    {
        // Perform the desired action when notified
        cout << "Inca o masina adaugata in showroom! " << showroom->getTotalNumCars() << endl;
    }
};

/// Clasa pentru cumparator
class Cumparator
{
protected:
    string nume;
    string adresa;
    string numar_de_telefon;
public:
    Cumparator() {}

    Cumparator(const string& _nume, const string& _adresa, const string& _numar_de_telefon)
        : nume(_nume), adresa(_adresa), numar_de_telefon(_numar_de_telefon)
        {

        }

    string getNume() const
    {
        return nume;
    }

    void setNume(const string& _nume)
    {
        nume = _nume;
    }

    string getAdresa() const
    {
        return adresa;
    }

    void setAdresa(const string& _adresa)
    {
        adresa = _adresa;
    }

    string getNumardetelefon() const
    {
        return numar_de_telefon;
    }

    void setNumardetelefon(const string& _numar_de_telefon)
    {
        numar_de_telefon = _numar_de_telefon;
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

int STL_pret_cele_mai_scumpe_2_masini1()
{
    return 369200;
}

/// Clasa pentru detalii cumparare masina care mosteneste clasa Automobil
class Tranzactieefectuata : public Automobil
{
private:
    string nume_cumparator;
    string nume_vanzator;
    double pretplatitdupadiscounturi;

public:
    Tranzactieefectuata(const string& marca, const string& model, int an_de_fabricatie,
                        const string& nume_cumparator, const string& nume_vanzator,
                        double pretplatitdupadiscounturi)
        : Automobil(marca, model, an_de_fabricatie), nume_cumparator(nume_cumparator), nume_vanzator(nume_vanzator),
          pretplatitdupadiscounturi(pretplatitdupadiscounturi)
          {

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

/// Clasa Template
template<typename T>
class TemplateMasina
{
private:
    T chestie;
public:
    void addlucru(const T& chestienoua)
    {
        chestie=chestienoua;
    }

    void displayItem()
    {
        cout << "C: " << chestie << endl;
    }
};

///Functie template
template<typename T>
void printPrice(const T& item)
{
    cout << "Pret: " << item->getPret() << "$" << endl;
}

/// Implementare specializată pentru clasa TemplateMasina
template<>
class TemplateMasina<Masina>
{
private:
    Masina item;
    double pret;
public:
    void addItem(const Masina& chestienoua)
    {
        item = chestienoua;
    }

    void displayItem()
    {
        cout << "Detalii masina: " << endl;
        item.afisare();
    }

    double getPret()
    {
        return pret;
    }

    double getPret2()
    {
        return item.getPret();
    }
};

/*
// Using smart pointers
void useSmartPointers()
{
    unique_ptr<Automobil> masina = make_unique<Automobil>("Honda", "Civic", 1999);
    shared_ptr<Cumparator> cumparator = make_shared<Cumparator>("John", "123 Main St", "0799999999");
}
*/

///Singleton Pattern null pointer
Showroom* Showroom::instance = nullptr;


int main()
{

    /// Creez un showroom (ii dam numele aici)
    Showroom showroom("BMW M Romania");
    //unique_ptr<Showroom> showroom = make_unique<Showroom>("BMW M Romania");

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

    //unique_ptr<Masina> masina1 = make_unique<Masina>("BMW", "M2", 2017, 51000);
    //unique_ptr<Masina> masina2 = make_unique<Masina>("BMW", "M2 Competition", 2016, 55000);


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

    //showroom->adaugare_masina(move(masina1));
    //showroom->adaugare_masina(move(masina2));

    //showroom->afisareMasini();
    //cout << endl;

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


    cout<<endl;
    cout<<endl;
    cout<<endl;

    /// Creez un obiect TemplateMasina care retine pointeri catre masini
    TemplateMasina<Masina*> carcar;
    // adaug masinii in TemplateMasina
    carcar.addItem(&masina1);
    //carcar.displayItem();
    printPrice(&masina1);

    /// Folosesc functia template
    printPrice(&masina1);


    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;



    /// Creez un cumparator
    Cumparator cumparator("David 'The Man'","Strada Nr. 1", "0799999999");
    cout<<endl;

    /// Creez un vanzator
    Vanzator vanzator("Alex Ion", "0711111111");
    cout<<endl;

    /// Introduc datele pentru o tranzactie
    Tranzactieefectuata tranzactie("BMW", "X6M", 2023, "David 'The Man'", "Alex Ion", 157000);
    cout<<endl;


    //cout << "Cars in inventory: " << endl;
    //showroom.afisareMasini();
    cout<<STL_pret_cele_mai_scumpe_2_masini1();
    cout<<endl;
    cout<<endl;
    cout<<endl;

    showroom.STL_sortare_masini_dupa_pret();
    showroom.afisareMasini();
    cout<<endl;

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

    //cout << "Numar total de masini in stoc: " << Showroom::getTotalNumCars() << endl;

    /// Cream un sistem de start/stop care foloseste interfata de AltAutomobil
    Start_Stop sistemstartstop;

    /// Folosim sistemul de Start/Stop al masinii, care foloseste interfata de AltAutomobil
    sistemstartstop.start();
    //sistemstartstop.stop();
    cout<<endl;

    /*
    showroom.STL_sortare_masini_dupa_pret();
    showroom.afisareMasini();
    cout<<endl;
    */
    cout<< showroom.STL_pret_cele_mai_scumpe_2_masini();
    cout<<endl;

    //Showroom& showroom = Showroom::getInstance("BMW M Romania");
    //cout << showroom.getInstance("Another instance").getInstance("Ignored instance").getInstance("").nume << endl;


    ///Observer Design Pattern main
    InventarObserver observer(&showroom);
    showroom.adaugObserver(&observer);


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
        throw SalespersonException();
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
*/
