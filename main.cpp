#include <iostream>
#include <cstring>

using namespace std;

/// Clasa pentru masina
class Masina
{
private:
    char marca[50];
    char model[50];
    int an_de_fabricatie;
    double pret;
public:
    Masina()
    {
        marca[0] = '\0';
        model[0] = '\0';
        an_de_fabricatie = 0;
        pret = 0.0;
    }
    ///Constructor de copiere
    Masina(char* marca, char* model, int an_de_fabricatie, double pret)
    {
        strcpy(this->marca, marca);
        strcpy(this->model, model);
        this->an_de_fabricatie = an_de_fabricatie;
        this->pret = pret;
    }

    Masina(const Masina& masina)
    {
        strcpy(marca, masina.marca);
        strcpy(model, masina.model);
        an_de_fabricatie = masina.an_de_fabricatie;
        pret = masina.pret;
    }

    ///Getteri
    char* getMarca()
    {
        return marca;
    }

    char* getModel()
    {
        return model;
    }

    int getAndefabricatie()
    {
        return an_de_fabricatie;
    }

    double getPret()
    {
        return pret;
    }

    ///Settari
    void setMarca(char* marca)
    {
        strcpy(this->marca, marca);
    }

    void setModel(char* model)
    {
        strcpy(this->model, model);
    }

    void setAndefabricatie(int an_de_fabricatie)
    {
        this->an_de_fabricatie = an_de_fabricatie;
    }

    void setPret(double pret)
    {
        this->pret = pret;
    }

    void afisare() const
    {
        cout << "Marca: " << marca;
        cout << endl;
        cout << "Model: " << model;
        cout << endl;
        cout << "An de fabricatie: " << an_de_fabricatie;
        cout << endl;
        cout << "Pret: " << pret << "$ ";
        cout << endl;
    }
};

/// Clasa pentru showroom
class Showroom
{
private:
    char nume[50];
    Masina masini[100];
    int numar_masini;
public:
    Showroom()
    {
        nume[0] = '\0';
        numar_masini = 0;
    }

    Showroom(char* nume)
    {
        strcpy(this->nume, nume);
        numar_masini = 0;
    }

    char* getNume()
    {
        return nume;
    }

    void setNume(char* nume)
    {
        strcpy(this->nume, nume);
    }

    void adaugare_masina(const Masina& masinii)
    {
        if (numar_masini < 100)
        {
            masini[numar_masini++] = masinii;
        }
    }

    double getPretTotalMasiniNet()
    {
        double prettotal = 0.0;
        for (int i = 0; i < numar_masini; i++)
        {
            prettotal += masini[i].getPret();
        }
        return prettotal;
    }

    double getPretTotalMasiniBrut(double procentTVA)
    {
        double prettotal = getPretTotalMasiniNet();
        return prettotal * (1 + procentTVA);
    }

    void afisareMasini()
    {
        cout << "Masini in stocul " << nume << ":" << endl;
        cout << endl;
        for (int i = 0; i < numar_masini; i++)
        {
            masini[i].afisare();
            cout << endl;
        }
    }
};

/// Clasa pentru cumparator
class Cumparator
{
private:
    char nume[50];
    char adresa[50];
public:
    Cumparator()
    {
        nume[0] = '\0';
        adresa[0] = '\0';
    }

    Cumparator(char* nume, char* adresa)
    {
        strcpy(this->nume, nume);
        strcpy(this->adresa, adresa);
    }

    Cumparator(const Cumparator& cumparator)
    {
        strcpy(nume, cumparator.nume);
        strcpy(adresa,cumparator.adresa);
    }

    char* getNume()
    {
        return nume;
    }

    char* getAdresa()
    {
        return adresa;
    }

    void setNume(char* nume)
    {
        strcpy(this->nume, nume);
    }

    void setAdresa(char* adresa)
    {
        strcpy(this->adresa, adresa);
    }
};

/// Clasa pentru vanzator
class Vanzator
{
private:
    char nume[20];
public:
    Vanzator()
    {
        nume[0] = '\0';
    }

    Vanzator(char nume[])
    {
        strcpy(this->nume, nume);
    }

    char* getNume()
    {
        return nume;
    }

    void setNume(char nume[])
    {
        strcpy(this->nume, nume);
    }

    void display() const
    {
        cout << "Nume: " << nume << endl;
    }
};

/// Clasa pentru detalii cumparare masina
class Tranzactieefectuata
{
private:
    Cumparator cumparator;
    Masina masina;
    Vanzator vanzator;
    double pretplatitdupadiscounturi;
public:
    Tranzactieefectuata(const Cumparator& cumparator, const Masina& masina, const Vanzator& vanzator, double pretplatitdupadiscounturi)
    {
        this->cumparator = cumparator;
        this->masina = masina;
        this->vanzator = vanzator;
        this->pretplatitdupadiscounturi = pretplatitdupadiscounturi;
    }
    Cumparator getCumparator()
    {
        return cumparator;
    }

    Masina getMasina()
    {
        return masina;
    }

    Vanzator getVanzator() const
    {
        return vanzator;
    }

    double getPretplatitdupadiscounturi()
    {
        return pretplatitdupadiscounturi;
    }

    void setMasina(const Masina& masina)
    {
        this->masina = masina;
    }

    void setCumparator(const Cumparator& cumparator)
    {
        this->cumparator = cumparator;
    }

    void setVanzator(const Vanzator& vanzator)
    {
        this->vanzator = vanzator;
    }

    void setPretplatitdupadiscounturi(double pretplatitdupadiscounturi)
    {
        this->pretplatitdupadiscounturi = pretplatitdupadiscounturi;
    }

    void afisare()
    {
        cout << "DETALIILE TRANZACTIEI:" << endl;
        cout << endl;

        cout << "Nume vanzator:" << endl;
        cout << vanzator.getNume() << endl;
        cout << endl;

        cout << "Nume Cumparator: " << endl;
        cout << cumparator.getNume() << endl;
        cout << endl;

        cout << "Adresa cumparator: " << endl;
        cout << cumparator.getAdresa() << endl;
        cout << endl;

        cout << "Marca masinii: " << endl;
        cout << masina.getMarca() << endl;
        cout << endl;

        cout << "Model masina: " << endl;
        cout << masina.getModel() << endl;
        cout << endl;

        cout << "An de fabricatie al masini: " << endl;
        cout << masina.getAndefabricatie() << endl;
        cout << endl;

        cout << "Pret al masinii:" << endl;
        cout << masina.getPret() << "$ " << endl;
        cout << endl;

        cout << "Pret platit de cumparator: " << endl;
        cout << pretplatitdupadiscounturi << "$ " << endl;
    }
};

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


    showroom.adaugare_masina(masina1);
    showroom.adaugare_masina(masina2);
    showroom.adaugare_masina(masina3);
    showroom.adaugare_masina(masina4);
    showroom.adaugare_masina(masina5);
    showroom.adaugare_masina(masina6);
    showroom.adaugare_masina(masina7);
    showroom.adaugare_masina(masina8);
    showroom.adaugare_masina(masina9);
    showroom.adaugare_masina(masina10);
    showroom.adaugare_masina(masina11);
    showroom.adaugare_masina(masina12);
    showroom.adaugare_masina(masina13);
    showroom.adaugare_masina(masina14);
    showroom.adaugare_masina(masina15);


    ///Si le afisez
    showroom.afisareMasini();
    cout << endl;

    /// Aici calculez cat costa toate masiniile care sunt in showroom(pret Net)
    double prettotal = showroom.getPretTotalMasiniNet();
    cout << "MASINI DISPONIBILE PENTRU A FI CUMPARATE:"<<endl;
    cout << endl;
    cout << "Pret total al masiniilor din showroom(Net): " << prettotal << "$ " << endl;

    /// Aici calculez cat costa toate masiniile care sunt in showroom(pret Brut(adica cu TVA))
    double procentTVA = 0.19; // 19% TVA
    double prettotalcuTVA = showroom.getPretTotalMasiniBrut(procentTVA);
    cout << "Pret total al masiniilor din showroom(Brut): " << prettotalcuTVA << "$ " << endl;
    cout<<endl;
    cout << endl;

    /// Creez un cumparator
    Cumparator cumparator("Andrei Victor", "Strada Nr. 1");
    Vanzator vanzator("Alex Ion");

    /// Introduc datele pentru o tranzactie
    Tranzactieefectuata tranzactie(cumparator,masina4, vanzator, 197000);

    /// Si le afisez
    tranzactie.afisare();

    return 0;
}
