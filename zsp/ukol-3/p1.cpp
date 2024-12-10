#include "pch.h"
#include "p1.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>

#define CRT_SECURE_NO_WARNINGS
#define POCET_TEPLOT_TYDEN 7

// Overi, zda je cislo dne v platnem rozmezi
int test_id_dne(int id_dne) {
    return id_dne > 0 && id_dne <= POCET_TEPLOT_TYDEN;
}

// Vraci nazev dne podle cisla dne
char* nazev_dne(int id_dne) {
    const char nazvyDnu[POCET_TEPLOT_TYDEN][10] = {
        "Pondeli", "Utery", "Streda", "Ctvrtek", "Patek", "Sobota", "Nedele"
    };

    if (test_id_dne(id_dne)) {
        char* s = (char*)malloc(10 * sizeof(char)); // Dynamicka alokace pameti
        if (s == NULL) return NULL; // Kontrola alokace
        strcpy_s(s, 10, nazvyDnu[id_dne - 1]); // Kopirovani nazvu dne
        return s;
    }
    return NULL;
}

// Zapisuje teplotu pro dany den
int zapis_teplotu(double* teploty_tyden, int pocet_teplot, int id_dne, double teplota) {
    if (test_id_dne(id_dne)) {
        teploty_tyden[id_dne - 1] = teplota;
        return 1; // Uspesny zapis
    }
    return 0; // Chybny vstup
}

// Cte teplotu z pole pro dany den
int precti_teplotu(double* teploty_tyden, int pocet_teplot, int id_dne, double* teplota) {
    if (test_id_dne(id_dne)) {
        *teplota = teploty_tyden[id_dne - 1];
        return 1; // Uspesne cteni
    }
    return 0; // Chybny vstup
}

// Vypocita prumernou teplotu tydne
double prumerna_teplota(double* teploty_tyden, int pocet_teplot) {
    double suma = 0.0;
    for (int i = 0; i < pocet_teplot; i++) {
        suma += teploty_tyden[i];
    }
    return suma / pocet_teplot;
}

// Najde maximalni teplotu v tydnu
double maximalni_teplota(double* teploty_tyden, int pocet_teplot) {
    double max = teploty_tyden[0];
    for (int i = 1; i < pocet_teplot; i++) {
        if (teploty_tyden[i] > max) {
            max = teploty_tyden[i];
        }
    }
    return max;
}

// Najde pozici prvniho vyskytu dane teploty
int pozice_teploty(double* teploty_tyden, int pocet_teplot, double teplota) {
    for (int i = 0; i < pocet_teplot; i++) {
        if (teploty_tyden[i] == teplota) {
            return i + 1; // Vraci index dne (1-7)
        }
    }
    return -1; // Teplota nebyla nalezena
}

// Ulozi teploty do souboru
void uloz_do_souboru_teploty(const char* soubor, double* teploty_tyden, int pocet_teplot) {
    FILE* file;
    fopen_s(&file, soubor, "w"); // Otevreni souboru pro zapis
    if (file != NULL) {
        for (int i = 0; i < pocet_teplot; i++) {
            fprintf(file, "%.2f\n", teploty_tyden[i]); // Zapis teplot
        }
        fclose(file); // Zavreni souboru
    }
}

// Nacte teploty ze souboru
int nacti_ze_souboru_teploty(const char* soubor, double* teploty_tyden, int pocet_teplot) {
    FILE* file;
    fopen_s(&file, soubor, "r"); // Otevreni souboru pro cteni
    if (file != NULL) {
        for (int i = 0; i < pocet_teplot; i++) {
            if (fscanf_s(file, "%lf", &teploty_tyden[i]) != 1) {
                fclose(file);
                return 0; // Chyba cteni
            }
        }
        fclose(file);
        return 1; // Uspesne nacteni
    }
    return 0; // Soubor nelze otevrit
}

// Hlavni funkce pro operace
void operace(double* teploty_tyden) {
    int volba;
    do {
        printf("1. Zadat teplotu\n");
        printf("2. Zjistit prumernou teplotu\n");
        printf("3. Najit maximalni teplotu\n");
        printf("4. Najit den s urcitou teplotou\n");
        printf("5. Ulozit teploty do souboru\n");
        printf("6. Nacist teploty ze souboru\n");
        printf("7. Konec\n");
        printf("Vyberte moznost: ");
        scanf_s("%d", &volba);

        switch (volba) {
        case 1: {
            int id_dne;
            double teplota;
            printf("Zadejte cislo dne (1-7): ");
            scanf_s("%d", &id_dne);
            printf("Zadejte teplotu: ");
            scanf_s("%lf", &teplota);
            if (zapis_teplotu(teploty_tyden, POCET_TEPLOT_TYDEN, id_dne, teplota)) {
                printf("Teplota byla zapsana.\n");
            }
            else {
                printf("Chyba: Neplatne cislo dne.\n");
            }
            break;
        }
        case 2: {
            printf("Prumerna teplota: %.2f\n", prumerna_teplota(teploty_tyden, POCET_TEPLOT_TYDEN));
            break;
        }
        case 3: {
            printf("Maximalni teplota: %.2f\n", maximalni_teplota(teploty_tyden, POCET_TEPLOT_TYDEN));
            break;
        }
        case 4: {
            double teplota;
            printf("Zadejte teplotu: ");
            scanf_s("%lf", &teplota);
            int pozice = pozice_teploty(teploty_tyden, POCET_TEPLOT_TYDEN, teplota);
            if (pozice != -1) {
                printf("Teplota %.2f byla nalezena v den: %d\n", teplota, pozice);
            }
            else {
                printf("Teplota nebyla nalezena.\n");
            }
            break;
        }
        case 5: {
            uloz_do_souboru_teploty("teploty.txt", teploty_tyden, POCET_TEPLOT_TYDEN);
            printf("Teploty byly ulozeny do souboru.\n");
            break;
        }
        case 6: {
            if (nacti_ze_souboru_teploty("teploty.txt", teploty_tyden, POCET_TEPLOT_TYDEN)) {
                printf("Teploty byly nacteny ze souboru.\n");
            }
            else {
                printf("Chyba: Nelze nacist teploty ze souboru.\n");
            }
            break;
        }
        case 7: {
            printf("Konec programu.\n");
            break;
        }
        default: {
            printf("Neplatna volba. Zkuste to znovu.\n");
            break;
        }
        }
    } while (volba != 7);
}