#include <iostream>
#include <iomanip> // pro std::setprecision
#include <cmath>   // pro zaokrouhovani
#include <string>  // pro praci s retezci

// Konstanty
const double DPH_RATE = 0.20; // DPH 20 %
const int POCET_ZNAMEK = 5;    // Pocet znamek pro ukol 2

void u1_1() {
    int pocetKusu; // Pocet kusu
    int cenaZaKus; // Cena za jeden kus 

    //  vstupy od uzivatel
    std::cout << "Zadejte pocet kusu: ";
    std::cin >> pocetKusu;
    std::cout << "Zadejte cenu za jeden kus bez DPH: ";
    std::cin >> cenaZaKus;

    // Vypocty
    double cenaS_DPH = cenaZaKus * (1 + DPH_RATE);
    double cenaBez_DPH = cenaZaKus * pocetKusu;
    double cenaS_DPH_total = cenaS_DPH * pocetKusu;

    // Zaokrouleni
    int cenaS_DPH_zaokrouhlena = std::round(cenaS_DPH);
    int cenaBez_DPH_zaokrouhlena = std::round(cenaBez_DPH);
    int cenaS_DPH_total_zaokrouhlena = std::round(cenaS_DPH_total);

    // Vypis vysledku
    std::cout << "\nUctenka\n";
    std::cout << "Cena bez DPH/ks: " << cenaZaKus << " Kc\t"
        << "Cena s DPH/ks: " << cenaS_DPH_zaokrouhlena << " Kc\n";
    std::cout << "Pocet kusu: " << pocetKusu << "\t"
        << "Cena bez DPH: " << cenaBez_DPH_zaokrouhlena << " Kc\t"
        << "Cena s DPH (20 %): " << cenaS_DPH_total_zaokrouhlena << " Kc\n";
}

void u1_2() {
    int znamky[POCET_ZNAMEK]; //  znamky
    int soucet = 0; // secteni znamek

    // Ziskani znamek 
    for (int i = 0; i < POCET_ZNAMEK; ++i) {
        std::cout << "Zadejte " << (i + 1) << ". znamku: ";
        std::cin >> znamky[i];
        soucet += znamky[i]; // Pridani znamky do souctu
    }

    // Vypocet prumeru
    double prumer = static_cast<double>(soucet) / POCET_ZNAMEK;

    // Vyhodnoceni prospechu
    bool vyznamenani = (prumer < 1.5); // Prospel s vyznamenanim
    bool prospech = (prumer < 2.0); // Prospel
    bool neprospel = (prumer >= 2.0); // Neprospel

    // Vypis vysledku
    std::cout << "\nZnamky: ";
    for (int i = 0; i < POCET_ZNAMEK; ++i) {
        std::cout << znamky[i] << (i < POCET_ZNAMEK - 1 ? "\t" : "");
    }

    std::cout << "\nPrumerna hodnota: " << std::fixed << std::setprecision(2) << prumer << "\n";
    std::cout << "Prospel s vyznamenanim: {" << (vyznamenani ? "1:Ano" : "0:Ne") << "}\n";
    std::cout << "Prospel: {" << (prospech ? "1:Ano" : "0:Ne") << "}\n";
    std::cout << "Neprospel: {" << (neprospel ? "1:Ano" : "0:Ne") << "}\n";
}

void u1_3() {
    std::string zkratkaMeny; // Zkratka meny
    double cenaZaMenu; // Cena za 1 menu v Kc
    int pocetMeny; // Pocet meny

    // Ziskani vstupu od uzivatele
    std::cout << "Zadejte zkratku meny: ";
    std::cin >> zkratkaMeny;
    std::cout << "Zadejte cenu za 1 " << zkratkaMeny << " v Kc: ";
    std::cin >> cenaZaMenu;
    std::cout << "Zadejte pocet " << zkratkaMeny << ": ";
    std::cin >> pocetMeny;

    // Vypocet celkove ceny
    double celkem = cenaZaMenu * pocetMeny;

    // Zaokrouleni na cele cislo
    int celkemZaokrouhlene = std::round(celkem);

    // Vypis vysledku
    std::cout << "\n1 " << zkratkaMeny << " = " << cenaZaMenu << " Kc\n";
    std::cout << "Nakup: " << pocetMeny << " " << zkratkaMeny << "\n";
    std::cout << "Celkem: " << pocetMeny << " x " << cenaZaMenu << " = " << celkem << " Kc\n";
    std::cout << "Zaokrouleno: " << celkemZaokrouhlene << " Kc\n";
}

int main() {
    // Zobrazeni informaci o mne
    std::cout << "Jmeno studenta: Autor\n";
    std::cout << "Login: xlogin00\n";
    std::cout << "Datum vytvoreni ulohy: " << __DATE__ << "\n";

    // Volani voidu
    u1_1();
    u1_2();
    u1_3();

    return 0; // Konec
}
