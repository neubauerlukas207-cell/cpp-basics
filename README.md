# Základy programování v C/C++

Úkoly z prvního ročníku (VŠPJ): **Základy strukturovaného programování** (ZS 2024/25) a **Objektově orientované programování** (LS 2024/25). Ukazují postup od procedurálního kódu k třídám.

| Složka | Obsah |
|---|---|
| `zsp/ukol-1` | výpočty s DPH, práce se vstupem, větvení a cykly, menu s podúlohami |
| `zsp/ukol-2` | výpočty z kinematiky – funkce s parametry, tabulka průběhu pohybu (`printf`) |
| `zsp/ukol-3` | evidence teplot v týdnu – pole, validace vstupu, statistiky (C) |
| `oop/ukol-1` | třída `Cisla` + `enum class Operace` – kalkulačka (součet, NSD, NSN, průměr …) |
| `oop/ukol-2` | třída `Ucet` – bankovní účet s vklady, výběry, limity a statistikou operací |

## Technologie

C / C++ · Visual Studio (`.vcxproj`) · g++

## Jak spustit

```bash
g++ -std=c++17 oop/ukol-2/Ukol2/Source.cpp -o ucet
./ucet
```

Projekty z OOP lze otevřít i ve Visual Studiu (`oop/ukol-2/Ukol2.sln`).

---
*Školní úkoly – každý commit odpovídá jednomu odevzdání v Moodlu (s původním datem).*
