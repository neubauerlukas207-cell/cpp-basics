// Operace.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

enum class Operace {
    SOUCET = 1, ROZDIL, SOUCIN, PODIL,
    MAXIMUM, PRUMER, NSN, NSD,
    NULOVA, ZOBRAZ, DELENI_ZBYTEK,
    KONEC = 0
};

class Cisla {
private:
    const int a;
    const int b;

    int nsd(int x, int y) const {
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return abs(x);
    }

    int nsn(int x, int y) const {
        return abs(x * y) / nsd(x, y);
    }

public:
    Cisla(int x, int y) : a(x), b(y) {}

    int getA() const { return a; }
    int getB() const { return b; }

    int soucet() const { return a + b; }
    int rozdil() const { return a - b; }
    int soucin() const { return a * b; }

    double podil() const {
        return b != 0 ? static_cast<double>(a) / b : NAN;
    }

    int maximum() const {
        return (a > b) ? a : b;
    }

    double prumer() const {
        return (a + b) / 2.0;
    }

    int nejvetsiSpolecnyDelitel() const {
        return nsd(a, b);
    }

    int nejmensiSpolecnyNasobek() const {
        return nsn(a, b);
    }

    bool jeNula() const {
        return a == 0 || b == 0;
    }

    void deleniAZbytek(int& vysledek, int& zbytek) const {
        if (b != 0) {
            vysledek = a / b;
            zbytek = a % b;
        }
        else {
            vysledek = 0;
            zbytek = 0;
        }
    }

    void zobraz() const {
        cout << "Cisla: a = " << a << ", b = " << b << endl;
    }

    void operace(Operace op) const {
        cout << fixed << setprecision(2);
        cout << "------------------------------\n";
        zobraz();
        cout << "Operace: " << static_cast<int>(op) << endl;

        switch (op) {
        case Operace::SOUCET:
            cout << "Soucet: " << soucet() << endl;
            break;
        case Operace::ROZDIL:
            cout << "Rozdil: " << rozdil() << endl;
            break;
        case Operace::SOUCIN:
            cout << "Soucin: " << soucin() << endl;
            break;
        case Operace::PODIL:
            if (b != 0)
                cout << "Podil: " << podil() << endl;
            else
                cout << "Deleni nulou!" << endl;
            break;
        case Operace::MAXIMUM:
            cout << "Vetsi hodnota: " << maximum() << endl;
            break;
        case Operace::PRUMER:
            cout << "Prumer: " << prumer() << endl;
            break;
        case Operace::NSN:
            cout << "Nejmensi spolecny nasobek: " << nejmensiSpolecnyNasobek() << endl;
            break;
        case Operace::NSD:
            cout << "Nejvetsi spolecny delitel: " << nejvetsiSpolecnyDelitel() << endl;
            break;
        case Operace::NULOVA:
            // Spočítáno, výstup v main()
            break;
        case Operace::ZOBRAZ:
            break;
        case Operace::DELENI_ZBYTEK: {
            int vysl, zbyt;
            deleniAZbytek(vysl, zbyt);
            if (b != 0)
                cout << "Celociselne deleni: " << vysl << ", zbytek: " << zbyt << endl;
            else
                cout << "Deleni nulou!" << endl;
            break;
        }
        default:
            break;
        }
        cout << "------------------------------\n";
    }
};

int main() {
    int x, y;
    cout << "Zadej dve cela cisla: ";
    cin >> x >> y;

    Cisla* cisla = new Cisla(x, y);

    int volba;
    do {
        cout << "\nMenu:\n"
            << "1 ... Soucet\n"
            << "2 ... Rozdil\n"
            << "3 ... Soucin\n"
            << "4 ... Podil\n"
            << "5 ... Maximum\n"
            << "6 ... Prumer\n"
            << "7 ... NSN\n"
            << "8 ... NSD\n"
            << "9 ... Je aspon jedno cislo nulove?\n"
            << "10 ... Zobraz cisla\n"
            << "11 ... Celociselne deleni a zbytek\n"
            << "0 ... Konec\n"
            << "Zadej volbu: ";
        cin >> volba;

        if (volba >= 1 && volba <= 11) {
            Operace op = static_cast<Operace>(volba);
            if (op == Operace::NULOVA) {
                bool nul = cisla->jeNula();
                cout << "Obsahuje nulu? " << (nul ? "Ano" : "Ne") << endl;
            }
            else {
                cisla->operace(op);
            }
        }

    } while (volba != 0);

    delete cisla;
    return 0;
}
