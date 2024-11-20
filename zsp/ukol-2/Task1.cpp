#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h> //vstupy vystupy
#include <math.h>  //matematicke funkce
#include <string.h>

// -- globální proměnné
char nazev_ukolu[255];
int uvod = 1;
// vstupní hodnoty
const double s0 = 0.0; // počáteční dráha
double v0;  // počáteční rychlost
double v1;  // rychlost v čase t0
double t0;  // počáteční čas
double t;   // konečný čas
// vystupní hodnoty
double a;   // zrychlení
double s;   // dráha ujetá v čase <t>
double v;   // rychlost v čase <t>
double pomer;   // poměr rychlostí v1 a v0
int typPohybu;  // identifikator typu pohybu {1 - zrychlený pohyb; 2 - konstantní pohyb; 3 - zpomalený pohyb}

void note()
// funkce zobrazí informace o autorovi a o realizaci úkolu
{
    strcpy(nazev_ukolu, "nazev ukolu: ZSP - Domaci ukol c. 2 - Kinematika");
    if (uvod == 1) {
        uvod = 0;
        printf("jmeno: Autor\n");    // zobrazit jméno a příjmení autora
        printf("login: xlogin00\n");    // zobrazit login autora
        printf("datum plneni ukolu: 20.11.2024\n");   // datum realizace úkolu ve tvaru např. 17.10.2022
        printf("%s", nazev_ukolu);
        printf("\n");
        printf("\n");
    }
}

int kinematika(); // deklarace funkce

int intro(float v0_p, float v1_p, float t0_p, float t_p)
// funkce, která zajišťuje vstupy uživatele a kontrolu jejich platnosti
{
    v0 = v0_p;
    v1 = v1_p;
    t0 = t0_p;
    t = t_p;

    // Kontrola, zda nejsou vstupní hodnoty záporné
    if (v0 < 0)
    {
        printf("Hodnoty nesmi byt zapornymi cisly.\n\n");
        printf("Uspesne neprovedeno.\n\n");
        return -1;
    }
    else if (v1 < 0)
    {
        printf("Hodnoty nesmi byt zapornymi cisly.\n\n");
        printf("Uspesne neprovedeno.\n\n");
        return -2;
    }
    else if (t0 < 0)
    {
        printf("Hodnoty nesmi byt zapornymi cisly.\n\n");
        printf("Uspesne neprovedeno.\n\n");
        return -3;
    }
    else if (t < 0)
    {
        printf("Hodnoty nesmi byt zapornymi cisly.\n\n");
        printf("Uspesne neprovedeno.\n\n");
        return -4;
    }
    else
    {
        kinematika(); // pokud jsou hodnoty platné, zavoláme funkci kinematika
        return 0;
    }
}

void kinematika_vypocet()
// funkce pro výpočty podle zadaných vzorců
{
    a = (v1 - v0) / t0;  // výpočet zrychlení
    v = v0 + a * t;  // výpočet rychlosti v čase t
    s = s0 + v0 * t + 0.5 * a * pow(t, 2);  // výpočet dráhy

    if (v0 == 0)
    {
        pomer = 0; // nelze dělit nulou
    }
    else
    {
        pomer = v1 / v0;  // výpočet poměru rychlostí
    }

    // Určení typu pohybu na základě zrychlení
    if (a < 0)
    {
        typPohybu = 1;  // zpomalený pohyb
    }
    else if (a == 0)
    {
        typPohybu = 2;  // konstantní pohyb
    }
    else
    {
        typPohybu = 3;  // zrychlený pohyb
    }
}

void kinematika_vypisPohybu()
// funkce pro výpis typu pohybu
{
    if (typPohybu == 1)
    {
        printf("Pohyb je zpomaleny.\n");
    }
    else if (typPohybu == 2)
    {
        printf("Pohyb je konstantni.\n");
    }
    else if (typPohybu == 3)
    {
        printf("Pohyb je zrychleny.\n");
    }
}

void kinematika_vypisTabulky()
// funkce pro výpis výsledků a přehledové tabulky
{
    printf("a = %.2fkm/h^2, v0 = %.2fkm/h, v1 = %.fkm/h  \n", a, v0, v1);
    printf("v(t = %.2f) = %.2f km/h\n", t, v);
    printf("s(t = %.2f) = %.2f km\n", t, s);
    printf("pomer v = %.2f%%\n", pomer * 100);
    printf("Prehledova tabulka\n");
    printf("\tv0 \t\t%.2fkm/h\n", v0);
    printf("\tv1 \t\t%.2fkm/h\n", v1);
    printf("\tt0 \t\t%.2fh\n", t0);
    printf("\tt \t\t%.2fh\n", t);
    printf("\ta \t\t%.2fkm/h^^2\n", a);
    printf("\tv \t\t%.2fkm/h\n", v);
    printf("\ts \t\t%.2fkm\n", s);
    printf("\tpomer v \t%.2f%%\n", pomer * 100);
    printf("Vypocet proveden uspesne.\n");
    printf("\n");
}

int kinematika()  // funkce pro výpočet a výpis
{
    note();  // zobrazí informace o úkolu
    kinematika_vypocet();  // provede výpočty
    printf("Vysledky\n");
    printf("\n");
    kinematika_vypisPohybu();  // výpis typu pohybu
    kinematika_vypisTabulky();  // výpis tabulky s výsledky
    return 1;
}

int main() {
    float v0, v1, t0, t;

    printf("Kinematika - program pro vypocet rovnomerne zrychleneho pohybu.");
    printf("\n");
    printf("\n");
    printf("Vstup dat");
    printf("\n");
    // Zadání hodnot od uživatele
    printf("Zadejte pocatecni a konecnou rychlost (hodnoty oddelene lomitkem): ");
    scanf("%f/%f", &v0, &v1);  // Načte obě hodnoty oddělené lomítkem
    printf("Zadejte dobu zrychlovani: ");
    scanf("%f", &t0);
    printf("Zadejte dobu pro vypocet drahy a okamzite rychlosti: ");
    scanf("%f", &t);

    // Volání funkce intro s argumenty
    int result = intro(v0, v1, t0, t);

    return 0;
}
