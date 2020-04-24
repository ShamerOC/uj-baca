//Krzysztof Wydrzynski

#include <iostream>

int main () {
    int dlugoscO, licznosc, odstep, pierwszy, ostatni, pierwszyM, klucz, g;
    double mediana;
    char filtr;
    int swap;

    std::cin >> dlugoscO;

    if (dlugoscO <= 0) {
        return 0;
    }

    double tabO[dlugoscO]; // tabO = oryginalna tablica

    for (int i = 0; i < dlugoscO; i++) {
        std::cin >> tabO[i]; // wczytanie do tablicy
    }

    std::cin >> licznosc;

    if (licznosc < 0 || licznosc > 21) {
        return 0;
    }

    double dane[licznosc];

    for (int i = 0; i < licznosc; i++) {
        std::cin >> dane[i];
    }
    std::cin >> odstep >> pierwszy >> ostatni >> filtr;
    // odstep += 1;
    int wartosc = licznosc / 2 * (odstep + 1);
    // std::cout << std::endl << a;
    int dlugosc = ostatni > pierwszy ? ostatni - pierwszy + 1 : ( dlugoscO - pierwszy ) + ostatni + 1;
    // int dlugosc;
    // if (pierwszy > ostatni) {
    //     dlugosc = dlugoscO - pierwszy + ostatni + 1;
    // } else {
    //     dlugosc = ostatni - pierwszy + 1;
    // }
    // int dlugosc = ostatni - pierwszy;
    // std::cout << "\n" << dlugosc << "\n";

    double tab[dlugosc];
    int tabI[dlugosc];
    int pomoc = 0;
    int z = pierwszy;
    // std::cout << "\n" << tabO[pierwszy] << "\n";
 
    do {
        z = z >= dlugoscO ? 0 : z;
        tab[pomoc] = tabO[z];
        tabI[pomoc] = z;
        z++;
        pomoc++;
        // std::cout << z << " ";
    } while (z - 1 != ostatni);
    

    // for (int i = 0; i < dlugosc; i++) {
    //     std::cout << tab[i] << " " ;
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;


    // for (int i = 0; i < dlugosc; i++) {
    //     std::cout << tabI[i] << " " ;
    // }

    // if (pierwszy > ostatni) {
    //     int swap = ostatni;
    //     ostatni = pierwszy;
    //     pierwszy = swap;
    // }

    double maska[licznosc];
    //   (dlugosc + (pierwszyM % dlugosc)) % dlugosc;
    int liczba, pierwsza;
    double suma = 0;
    double srednia;

    for (int i = 0; i < dlugosc; i++) {
        pierwsza = i - (licznosc / 2) * (odstep + 1);
        pierwsza = (dlugosc + (pierwsza % dlugosc)) % dlugosc;
        // std::cout << "\n" << pierwsza << "\n";
        for (int j = 0; j < licznosc; j++) {
            liczba = pierwsza + ( j * (odstep + 1) );
            liczba = (dlugosc + (liczba % dlugosc)) % dlugosc;
            // std::cout << liczba << " ";
            maska[j] = tab[liczba];
        }
        // std::cout << "\n";
        for (int j = 0; j < licznosc; j++) {
            // std::cout << maska[j] << " ";
        }
        // tutaj zaczynaja sie filtry dla masek
        // srednia ruchoma
        suma = 0;
        if (filtr == 'r') {
            for (int j = 0; j < licznosc; j++) {
                suma += maska[j];
                std::cout << maska[j] << " ";
            }
            srednia = (double)suma / (double)licznosc;
            tabO[tabI[i]] = (double)((int)(srednia * 100)) / 100;
        } else if (filtr == 'm') {
            for (int j = 1; j < licznosc; j++) {
                klucz = maska[j];
                g = j - 1;
                while(g > -1 && maska[g] > klucz) {
                    maska[g + 1] = maska[g];
                    g--;
                }
                maska[g + 1] = klucz;
            }
            for (int j = 0; j < licznosc; j++) {
                // std::cout << maska[j] << " ";
            }
            mediana = maska[licznosc / 2];
            // std::cout << " " << mediana;
            tabO[tabI[i]] = (double)((int)(mediana * 100)) / 100;
            for (int j = 0; j < licznosc; j++) {
            }
        } else if (filtr == 'w') {
            suma = 0;
            for (int j = 0; j < licznosc; j++) {
                suma += maska[j] * dane[j]; 
                // std::cout << " | " << maska[j] << " * " << dane[j] << " = " << maska[j] * dane[j];
            }
            // std::cout << " | " << suma;
            tabO[tabI[i]] = (double)((int)(suma * 100)) / 100;
        }
        std::cout << "\n";

    }
    // std::cout << std::endl;
    for (int i = 0; i < dlugoscO; i++) {
        std::cout << (double)tabO[i] << " ";
    }
    
    return 0;
}