//Krzysztof Wydrzynski
#include <iostream>

int wymiar;
int srodek;
long long uklad[32][32][32];

int prostopadloscian (int l, int v, int p, int h, int w, int d) {
    int poziom = l < srodek ? l + h : l - h;
    if (l > poziom) {
        int hold = poziom;
        poziom = l;
        l = hold;
    }

    int pion = v < srodek ? v + w : v - w;
    if (v > pion) {
        int hold = pion;
        pion = v;
        v = hold;
    }

    int panel = p < srodek ? p + d : p - d;
    if (p > panel) {
        int hold = panel;
        panel = p;
        p = hold;
    }

    int suma = 0;
    for (int i = l; i <= poziom; i++) {
        for (int j = v; j <= pion; j++) {
            for (int k = p ; k <= panel; k++) {
                if (i < wymiar && j < wymiar && k < wymiar && i >= 0 && j >= 0 && k >= 0) {
                    suma += uklad[i][j][k];
                }
            }
        }
    }
    return suma;
}

int czworoscian (int l, int v, int p, int e) {
    int poziom = l < srodek ? l + e : l - e;
    if (l > poziom) {
        int hold = poziom;
        poziom = l;
        l = hold;
    }

    int pion = v < srodek ? v + e : v - e;
    if (v > pion) {
        int hold = pion;
        pion = v;
        v = hold;
    }

    int panel = p < srodek ? p + e : p - e;
    if (p > panel) {
        int hold = panel;
        panel = p;
        p = hold;
    }

    int suma = 0;
    int a, b, c;

    for (int i = l; i <= poziom; i++) {
        for (int j = v; j <= pion; j++) {
            for (int k = p ; k <= panel; k++) {
                if (i < wymiar && j < wymiar && k < wymiar && i >= 0 && j >= 0 && k >= 0) {
                    a = i - l;
                    b = j - v;
                    c = k - p;
                    if (a + b + c <= e) {
                        suma += uklad[i][j][k];
                    }

                }
            }
        }
    }

    return suma;
}

int oktal (int l, int v, int p, int r) {
    int poziom = l < srodek ? l + r : l - r;
    if (l > poziom) {
        int hold = poziom;
        poziom = l;
        l = hold;
    }

    int pion = v < srodek ? v + r : v - r;
    if (v > pion) {
        int hold = pion;
        pion = v;
        v = hold;
    }

    int panel = p < srodek ? p + r : p - r;
    if (p > panel) {
        int hold = panel;
        panel = p;
        p = hold;
    }

    int suma = 0;
    int a, b, c;

    for (int i = l; i <= poziom; i++) {
        for (int j = v; j <= pion; j++) {
            for (int k = p ; k <= panel; k++) {
                if (i < wymiar && j < wymiar && k < wymiar && i >= 0 && j >= 0 && k >= 0) {
                    a = i - l;
                    b = j - v;
                    c = k - p;
                    if (a * a + b * b + c * c <= r * r) {
                        suma += uklad[i][j][k];
                    }
                }
            }
        }
    }

    return suma;
}

long long wyznacznik (long long arr[][32], int dl) {
    long long suma = 0;
    
    if (dl == 2) {
        return arr[0][0] * arr[1][1] - (arr[0][1] * arr[1][0]);
    } else {
        long long newArr[32][32];
        for (int i = 0; i < dl; i++) {
            if (arr[i][0] != 0) {
                int licznik = 0;
                for (int j = 0; j < dl; j++) {
                    if (j == i) j++;
                    for (int k = 1; k < dl; k++) {
                        newArr[licznik][k - 1] = arr[j][k];
                    }
                    licznik++;
                    
                }
                int znak = i % 2 == 0 ? 1 : -1;
                suma += arr[i][0] * znak * wyznacznik(newArr, dl - 1);
            }

        }
    }
    return suma;

}

int main () {
    char s;
    int l, v, p, h, w, d, n, e, r;
    long long wynik;
    char m;

    std::cin >> wymiar;
    srodek = wymiar / 2;

    for (int i = 0; i < wymiar; i++) {
        for (int j = 0; j < wymiar; j++) {
            for (int k = 0; k < wymiar; k++) {
                std::cin >> uklad[j][k][i];
            }
        }
    }


    std::cin >> s;
    while (s != 'E') {
        switch(s) {
            case 'C': // Prostopadloscian
                std::cin >> l >> v >> p >> h >> w >> d;
                wynik = prostopadloscian(l, v, p , h, w, d);
                std::cout << wynik << "\n";
                break;

            case 'T': // Czworoscian
                std::cin >> l >> v >> p >> e;
                wynik = czworoscian(l, v, p ,e);
                std::cout << wynik << "\n";
                break;

            case 'O': // Oktal
                std::cin >> l >> v >> p >> r;
                wynik = oktal(l , v, p, r);
                std::cout << wynik << "\n";
                break;

            case 'D': // Wyznacznik
                std::cin >> m >> n;
                long long tab[32][32];
                switch(m) {
                    case 'l': // pion
                        for (int i = 0; i < wymiar; i++) {
                            for (int j = 0; j < wymiar; j++) {
                                tab[i][j] = uklad[n][i][j];
                            }
                        }
                        break;

                    case 'v': // poziom
                        for (int i = 0; i < wymiar; i++) {
                            for (int j = 0; j < wymiar; j++) {
                                tab[i][j] = uklad[i][n][j];
                            }
                        }
                        break;

                    case 'p': // panel
                        for (int i = 0; i < wymiar; i++) {
                            for (int j = 0; j < wymiar; j++) {
                                tab[i][j] = uklad[i][j][n];
                            }
                        }
                        break;
                }

                wynik = wyznacznik(tab, wymiar);
                std::cout << wynik << "\n";
                break;
        }
        std::cin >> s;
    }

    return 0;
}