//Krzysztof Wydrzynski

#include <iostream>

int main () {

    // int punktyA, punktyB, punktyC, punktyD;
    int wynik;
    std::string g1, g2, g;
    int r1, r2, r3, r4;
    int w1, w2;
    float suma;


    int wa = 0, wb = 0, wc = 0, wd = 0, we = 0;
    int pa = 0, pb = 0, pc = 0, pd = 0, pe = 0;
    int ra = 0, rb = 0, rc = 0, rd = 0, re = 0;

    int n;
    std::cin >> n;
    if (n < 0) {
        return 0;
    }
    int max = 0;
    int i = 0;
    int j = 0, fgh = 0;
    int sumaOczek, max1, sumaOczek1;
    
    while (i < n) {
        j = 0;
        while (j < 2) {
            std::cin >> g >> r1 >> r2 >> r3 >> r4;
            wynik = 6;
            max = r1;
            if (r1 == r2 && r1 == r3 && r1 == r4) { // cztery takie same
                // std::cout << " " << 1 << " ";
                wynik = 1;
                max = r1;
                sumaOczek = r1 * 4;
            } else if (r1 != r2 && r1 != r3 && r1 != r4 && r2 != r3 && r2 != r4 && r3 != r4) { // brak powtorzen
                // std::cout << " " << 2 << " ";
                wynik = 2;
                sumaOczek = r1 + r2 + r3 + r4;
                max = r1;
                if (r2 > max) max = r2;
                if (r3 > max) max = r3;
                if (r4 > max) max = r4;
            } else if ((r1 == r2 && r3 == r4) || (r1 == r3 && r2 == r4) || (r2 == r3 && r1 == r4)) { // dwie pary powtorzen
                // std::cout << " " << 3 << " ";
                wynik = 3;
                max = r1;
                if (r2 > max) max = r2;
                if (r3 > max) max = r3;
                if (r4 > max) max = r4;
                sumaOczek = r1 + r2 + r3 + r4;
            } else if ((r1 == r2 && r1== r3) || (r1 == r2 && r1 == r4) || (r1 == r3 && r1 == r4) || (r2 == r3 && r2 == r4)) { // trzy takie same liczby
                // std::cout << " " << 4 << " ";
                wynik = 4;
                if (r1 == r2 && r1 == r3) {
                    sumaOczek = r4;
                }

               if (r1 == r2 && r1 == r4) {
                    sumaOczek = r3;
                }

               if (r1 == r3 && r1 == r4) {
                    sumaOczek = r2;
                }
               if (r2 == r3 && r2 == r4) {
                    sumaOczek = r1;
                }

            } else if (r1 == r2 || r1 == r3 || r1 == r4 || r2 == r3 || r2 == r4 || r3 == r4) { // dwie takie same liczby
                // std::cout << " " << 5 << " ";
                wynik = 5;
                max = r1;
                if (r1 == r2) {
                    sumaOczek = r3 + r4;
                    max = r3;
                    if (r4 > max) max = r4;
                }

                if (r1 == r3) {
                    sumaOczek = r2 + r4;
                    max = r2;
                    if (r4 > max) max = r4;
                }

                if (r1 == r4) {
                    sumaOczek = r2 + r3;
                    max = r2;
                    if (r3 > max) max = r3;
                }

                if (r2 == r3) {
                    sumaOczek = r1 + r4;
                    max = r1;
                    if (r4 > max) max = r4;
                }

                if (r2 == r4) {
                    sumaOczek = r1 + r3;
                    max = r3;
                    if (r1 > max) max = r1;
                }

                if (r3 == r4) {
                    sumaOczek = r2 + r1;
                    max = r1;
                    if (r2 > max) max = r2;
                }
            }

            if (j == 0) {
                g1 = g;
                w1 = wynik;
                max1 = max;
                sumaOczek1 = sumaOczek;
            } else {
                g2 = g;
                w2 = wynik;
                if (w1 == w2) {
                    if (w1 == 5 || w1 == 4) {
                        // std::cout << " suma oczek1: " << sumaOczek1 << " suma oczek2: " << sumaOczek << std::endl;
                        if (sumaOczek1 > sumaOczek) {
                            w1--;
                        } else if (sumaOczek1 < sumaOczek) {
                            w2--;
                        }
                    } else {
                        // std::cout << " max1: " << max1 << " max2: " << max << std::endl;
                        if (w1 == 3) {
                            if (max1 > max) {
                              w1--;
                            } else if (max1 < max) {
                               w2--;
                            } else {
                                 if (sumaOczek1 > sumaOczek) {
                                    w1--;
                                } else if (sumaOczek1 < sumaOczek) {
                                    w2--;
                                }
                            }
                        }
                        else if (max1 > max) {
                            w1--;
                        } else if (max1 < max) {
                            w2--;
                        }
                        
                    }
                }
            }
            j++;
        }
        if (w1 < w2) {
            if (g1 == g2) {
                if (g1 == "a") {
                // std::cout << " wygrana: a\n ";
                wa++;
                } else if (g1 == "b") {
                    // std::cout << " wygrana: b\n ";
                    wb++;
                } else if (g1 == "c") {
                    // std::cout << " wygrana: c\n ";
                    wc++;
                } else if (g1 == "d") {
                    // std::cout << " wygrana: d\n ";
                    wd++;
                } else if (g1 == "e") {
                    // std::cout << " wygrana: e\n ";
                    we++;
                }
            }
            else if (g1 == "a") {
                // std::cout << " wygrana: a\n ";
                wa++;
            } else if (g1 == "b") {
                // std::cout << " wygrana: b\n ";
                wb++;
            } else if (g1 == "c") {
                // std::cout << " wygrana: c\n ";
                wc++;
            } else if (g1 == "d") {
                // std::cout << " wygrana: d\n ";
                wd++;
            } else if (g1 == "e") {
                // std::cout << " wygrana: e\n ";
                we++;
            }
            if (g2 == "a") {
                // std::cout << " przegrana: a\n ";
                pa++;
            } else if (g2 == "b") {
                // std::cout << " przegrana: b\n ";
                pb++;
            } else if (g2 == "c") {
                // std::cout << " przegrana: c\n ";
                pc++;
            } else if (g2 == "d") {
                // std::cout << " przegrana: d\n ";
                pd++;
            } else if (g2 == "e") {
                // std::cout << " przegrana: e\n ";
                pe++;
            }
        } else if (w2 < w1) {
            if (g1 == g2) {
                
            }
            else if (g2 == "a") {
                // std::cout << " wygrana: a\n ";
                wa++;
            } else if (g2 == "b") {
                // std::cout << " wygrana: b\n ";
                wb++;
            } else if (g2 == "c") {
                // std::cout << " wygrana: c\n ";
                wc++;
            } else if (g2 == "d") {
                // std::cout << " wygrana: d\n ";
                wd++;
            } else if (g2 == "e") {
                // std::cout << " wygrana: e\n ";
                we++;
            }
            if (g1 == "a") {
                // std::cout << " przegrana: a\n ";
                pa++;
            } else if (g1 == "b") {
                // std::cout << " przegrana: b\n ";
                pb++;
            } else if (g1 == "c") {
                // std::cout << " przegrana: c\n ";
                pc++;
            } else if (g1 == "d") {
                // std::cout << " przegrana: d\n ";
                pd++;
            } else if (g1 == "e") {
                // std::cout << " przegrana: e\n ";
                pe++;
            }
        } else {
            if (g1 == g2) {
                if (g2 == "a") {
                    // std::cout << " remis a\n";
                    ra++;
                } else if (g2 == "b") {
                    // std::cout << " remis b\n";
                    rb++;
                } else if (g2 == "c") {
                    // std::cout << " remis c\n";
                    rc++;
                } else if (g2 == "d") {
                    // std::cout << " remis d\n";
                    rd++;
                } else if (g2 == "e") {
                    // std::cout << " remis e\n";
                    re++;
                }
            }
            if (g2 == "a") {
                // std::cout << " remis a\n";
                ra++;
            } else if (g2 == "b") {
                // std::cout << " remis b\n";
                rb++;
            } else if (g2 == "c") {
                // std::cout << " remis c\n";
                rc++;
            } else if (g2 == "d") {
                // std::cout << " remis d\n";
                rd++;
            } else if (g2 == "e") {
                // std::cout << " remis e\n";
                re++;
            }
            if (g1 == g2) {

            }
            else if (g1 == "a") {
                // std::cout << " remis a\n";
                ra++;
            } else if (g1 == "b") {
                // std::cout << " remis b\n";
                rb++;
            } else if (g1 == "c") {
                // std::cout << " remis c\n";
                rc++;
            } else if (g1 == "d") {
                // std::cout << " remis d\n";
                rd++;
            } else if (g1 == "e") {
                // std::cout << " remis e\n";
                re++;
            }
        }
        i++;
    }
    
    if (wa > 0 || pa > 0 || ra > 0) {
        suma = wa + pa + ra;
        std::cout << "gracz a\n";
        if (wa > 0) std::cout << "    wygrane: " << ( wa / suma ) * 100 << "%\n";
        if (ra > 0) std::cout << "    remisy: " << ( ra / suma ) * 100 << "%\n";
        if (pa > 0) std::cout << "    przegrane: " << ( pa / suma ) * 100 << "%\n";
        std::cout << "\n";
    }

    if (wb > 0 || pb > 0 || rb > 0) {
        suma = wb + pb + rb;
        std::cout << "gracz b\n";
        if (wb > 0) std::cout << "    wygrane: " << ( wb / suma ) * 100 << "%\n";
        if (rb > 0) std::cout << "    remisy: " << ( rb / suma ) * 100 << "%\n";
        if (pb > 0) std::cout << "    przegrane: " << ( pb / suma ) * 100 << "%\n";
        std::cout << "\n";
    }

    if (wc > 0 || pc > 0 || rc > 0) {
        suma = wc + pc + rc;
        std::cout << "gracz c\n";
        if (wc > 0) std::cout << "    wygrane: " << ( wc / suma ) * 100 << "%\n";
        if (rc > 0) std::cout << "    remisy: " << ( rc / suma ) * 100 << "%\n";
        if (pc > 0) std::cout << "    przegrane: " << ( pc / suma ) * 100 << "%\n";
        std::cout << "\n";
    }

    if (wd > 0 || pd > 0 || rd > 0) {
        suma = wd + pd + rd;
        std::cout << "gracz d\n";
        if (wd > 0) std::cout << "    wygrane: " << ( wd / suma ) * 100 << "%\n";
        if (rd > 0) std::cout << "    remisy: " << ( rd / suma ) * 100 << "%\n";
        if (pd > 0) std::cout << "    przegrane: " << ( pd / suma ) * 100 << "%\n";
        std::cout << "\n";
    }

    if (we > 0 || pe > 0 || re > 0) {
        suma = we + pe + re;
        std::cout << "gracz e\n";
        if (we > 0) std::cout << "    wygrane: " << ( we / suma ) * 100 << "%\n";
        if (re > 0) std::cout << "    remisy: " << ( re / suma ) * 100 << "%\n";
        if (pe > 0) std::cout << "    przegrane: " << ( pe / suma ) * 100 << "%\n";
        std::cout << "\n";
    }

    return 0;
}