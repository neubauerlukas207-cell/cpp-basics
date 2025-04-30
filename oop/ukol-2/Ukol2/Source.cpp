#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Ucet {
private:
    string majitel;
    int cisloUctu;
    double zustatek;
    int pocetVkladu;
    int pocetVyberu;
    double soucetVkladu;
    double soucetVyberu;
    int maxOperaci;

    vector<double> historieVkladu;
    vector<double> historieVyberu;

    static constexpr double MAX_VYBER = 5000.0;

public:
    // Konstruktor
    Ucet(string majitel, int cisloUctu, int maxOperaci)
        : majitel(majitel), cisloUctu(cisloUctu), zustatek(0),
        pocetVkladu(0), pocetVyberu(0), soucetVkladu(0),
        soucetVyberu(0), maxOperaci(maxOperaci) {}

    // Konstruktor z dat
    Ucet() = default;

    bool vloz(double castka) {
        if (castka <= 0 || to_string(castka).find(":);") != string::npos) {
            cout << "Neplatna castka nebo podezreni na utok.\n";
            return false;
        }
        if ((int)historieVkladu.size() >= maxOperaci) {
            cout << "Nelze ulozit dalsi vklad. Limit operaci vycerpan.\n";
            return false;
        }
        zustatek += castka;
        pocetVkladu++;
        soucetVkladu += castka;
        historieVkladu.push_back(castka);
        cout << "Vklad uspesne proveden.\n";
        return true;
    }

    bool vyber(double castka) {
        if (castka <= 0 || castka > MAX_VYBER || castka > zustatek) {
            cout << "Neplatny vyber. Prekrocen limit nebo nedostatek penez.\n";
            return false;
        }
        if ((int)historieVyberu.size() >= maxOperaci) {
            cout << "Nelze ulozit dalsi vyber. Limit operaci vycerpan.\n";
            return false;
        }
        zustatek -= castka;
        pocetVyberu++;
        soucetVyberu += castka;
        historieVyberu.push_back(castka);
        cout << "Vyber uspesne proveden.\n";
        return true;
    }

    void vypisDetailni() const {
        cout << "\nMajitel: " << majitel << "\nCislo uctu: " << cisloUctu
            << "\nZustatek: " << zustatek << " Kc"
            << "\nPocet vkladu: " << pocetVkladu
            << "\nPocet vyberu: " << pocetVyberu
            << "\nSoucet vkladu: " << soucetVkladu
            << "\nSoucet vyberu: " << soucetVyberu
            << "\nHistorie vkladu: ";
        for (double x : historieVkladu) cout << x << "; ";
        cout << "\nHistorie vyberu: ";
        for (double x : historieVyberu) cout << x << "; ";
        cout << "\n";
    }

    void vypisSouhrn() const {
        cout << "\nUcet: " << cisloUctu << ", Majitel: " << majitel
            << ", Zustatek: " << zustatek << " Kc"
            << ", Vklady: " << pocetVkladu
            << ", Vybery: " << pocetVyberu
            << ", Vlozeno: " << soucetVkladu
            << ", Vybrano: " << soucetVyberu << "\n";
    }

    void ulozDoSouboru(const string& filename) const {
        ofstream fout(filename);
        fout << cisloUctu << "\n" << majitel << "\n" << fixed << zustatek << "\n"
            << pocetVkladu << "\n" << pocetVyberu << "\n"
            << soucetVkladu << "\n" << soucetVyberu << "\n"
            << maxOperaci << "\n";

        for (double x : historieVkladu) fout << x << ";";
        fout << "\n";
        for (double x : historieVyberu) fout << x << ";";
        fout << "\n";
        fout.close();
    }

    bool nactiZeSouboru(const string& filename) {
        ifstream fin(filename);
        if (!fin) return false;

        getline(fin, majitel);
        fin >> cisloUctu >> zustatek >> pocetVkladu >> pocetVyberu
            >> soucetVkladu >> soucetVyberu >> maxOperaci;
        fin.ignore();

        historieVkladu.clear();
        historieVyberu.clear();

        string radek;
        getline(fin, radek);
        parseHistorie(radek, historieVkladu);
        getline(fin, radek);
        parseHistorie(radek, historieVyberu);
        return true;
    }

private:
    void parseHistorie(const string& radek, vector<double>& historie) {
        size_t start = 0, end;
        while ((end = radek.find(';', start)) != string::npos) {
            double val = stod(radek.substr(start, end - start));
            historie.push_back(val);
            start = end + 1;
        }
    }
};

// --- Hlavní funkce ---
int main(int argc, char* argv[]) {
    Ucet ucet;
    string soubor;

    if (argc > 1) {
        soubor = argv[1];
        if (!ucet.nactiZeSouboru(soubor)) {
            cout << "Chyba pri nacitani souboru.\n";
            return 1;
        }
    }
    else {
        string jmeno;
        int cislo, maxop;
        cout << "Zadejte jmeno majitele: ";
        getline(cin, jmeno);
        cout << "Zadejte cislo uctu (100001-109999): ";
        cin >> cislo;
        cout << "Zadejte max. pocet operaci: ";
        cin >> maxop;
        ucet = Ucet(jmeno, cislo, maxop);
    }

    while (true) {
        cout << "\nMENU:\n"
            << "1. Detailni vypis uctu\n"
            << "2. Souhrn informaci\n"
            << "3. Vklad\n"
            << "4. Vyber\n"
            << "0. Konec\n"
            << "Volba: ";
        int volba;
        cin >> volba;

        switch (volba) {
        case 0: {
            if (soubor.empty()) {
                cout << "Zadej jmeno souboru pro ulozeni: ";
                cin >> soubor;
            }
            ucet.ulozDoSouboru(soubor);
            cout << "Data ulozena. Konec.\n";
            return 0;
        }
        case 1:
            ucet.vypisDetailni();
            break;
        case 2:
            ucet.vypisSouhrn();
            break;
        case 3: {
            double castka;
            cout << "Zadejte castku k vkladu: ";
            cin >> castka;
            ucet.vloz(castka);
            break;
        }
        case 4: {
            double castka;
            cout << "Zadejte castku k vyberu: ";
            cin >> castka;
            ucet.vyber(castka);
            break;
        }
        default:
            cout << "Neplatna volba.\n";
        }
    }
}
