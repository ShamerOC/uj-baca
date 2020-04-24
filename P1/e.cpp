//Krzysztof Wydrzynski

#include <iostream>

#define MAX_TOWAR 65535
#define MAX_SHELF 128
#define MAX_RACK 128
#define MAX_PLACE 128
#define MAX_WAREHOUSE 128

long long sum = 0;

struct Places {
    unsigned short int towar;
    char etykieta[2];

    void Clear() {
        sum -= towar;
        towar = 0;
        etykieta[0] = 0;
        etykieta[1] = 0;
    }
};

struct Shelfs {
    unsigned short int iloscMiejsc;
    Places place[MAX_PLACE];

    void Clear(unsigned short int a, unsigned short int b) {
        for (int i = a; i < b; i++) {
            place[i].Clear();
        }
    }
};

struct Racks {
    unsigned short int iloscPolek;
    Shelfs shelf[MAX_SHELF];

    void Clear(unsigned short int a, unsigned short int b) {
        for (int i = a; i < b; i++) {
            shelf[i].Clear(0, 128);
        }
    }
};

struct Warehouses {
    unsigned short int iloscRegalow;
    Racks rack[MAX_RACK];
    Shelfs handyShelf;

    void Clear(unsigned short int a, unsigned short int b) {
        for (int i = a; i < b; i++) {
            rack[i].Clear(0, 128);
        }
    }
};

struct Sklad {
    unsigned short int iloscMagazynow;
    Warehouses warehouse[MAX_WAREHOUSE];
    Racks handyRack;
    Shelfs handyShelf;

    void Clear(unsigned short int a, unsigned short int b) {
        for (int i = a; i < b; i++) {
            warehouse[i].Clear(0, 128);
        }
    }

} sklad;

bool check_max(unsigned short a) {
    if (a > MAX_TOWAR) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_warehouses(unsigned short int w) {
    if (w >= sklad.iloscMagazynow) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_racks(unsigned short int w, unsigned short int r) {
    if (check_warehouses(w)) return true;
    if (r >= sklad.warehouse[w].iloscRegalow) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_shelfs(unsigned short int w, unsigned short int r, unsigned short int s) {
    if (check_warehouses(w)) return true;
    if (check_racks(w, r)) return true;
    if (s >= sklad.warehouse[w].rack[r].iloscPolek) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_places(int w, int r, int s, int p) {
    if (check_warehouses(w)) return true;
    if (check_racks(w, r)) return true;
    if (check_shelfs(w, r, s)) return true;

    if (p >= sklad.warehouse[w].rack[r].shelf[s].iloscMiejsc) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_handy_racks(int s) {
    if (s >= sklad.handyRack.iloscPolek) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_handy_racks_shelfs(int s, int p) {
    if (check_handy_racks(s)) return true;
    if (p >= sklad.handyRack.shelf[s].iloscMiejsc) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_handy_shelf(int p) {
    if (p >= sklad.handyShelf.iloscMiejsc) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

bool check_warehouse_handy_shelfs(int w, int p) {
    if (check_warehouses(w)) return true;
    if (p >= sklad.warehouse[w].handyShelf.iloscMiejsc) {
        std::cout << "error\n";
        return true;
    }
    return false;
}

void SET_AP(int w, int r, int s, int p) {
    if (check_shelfs(w, r, s)) return;
    int old = sklad.warehouse[w].rack[r].shelf[s].iloscMiejsc;
    sklad.warehouse[w].rack[r].shelf[s].Clear(p, old);
    sklad.warehouse[w].rack[r].shelf[s].iloscMiejsc = p;
}


void SET_AS(int w, int r, int s, int p) {
    if (check_racks(w, r)) return;
    int old = sklad.warehouse[w].rack[r].iloscPolek;
    sklad.warehouse[w].rack[r].Clear(s, old);
    sklad.warehouse[w].rack[r].iloscPolek = s;

    for (int i = 0; i < s; i++) {
        SET_AP(w, r, i, p);
    }
}

void SET_AR(int w, int r, int s, int p) {
    if (check_warehouses(w)) return;
    int old = sklad.warehouse[w].iloscRegalow;
    sklad.warehouse[w].Clear(r, old);
    sklad.warehouse[w].iloscRegalow = r;

    for (int i = 0; i < r; i++) {
        SET_AS(w, i, s, p);
    }
}

void SET_AW(int w, int r, int s, int p) {
    int old = sklad.iloscMagazynow;
    sklad.Clear(w, old);
    sklad.iloscMagazynow = w;

    for (int i = 0; i < w; i++) {
        SET_AR(i, r, s, p);
    }
}

void SET_HW(int w, int p) {
    if (check_warehouses(w)) return;
    int old = sklad.warehouse[w].handyShelf.iloscMiejsc;
    sklad.warehouse[w].handyShelf.Clear(p, old);
    sklad.warehouse[w].handyShelf.iloscMiejsc = p;
}

void SET_HR(int s, int p) {
    int old = sklad.handyRack.iloscPolek;
    sklad.handyRack.Clear(s, old);
    sklad.handyRack.iloscPolek = s;

    for (int i = 0; i < s; i++) {
        old = sklad.handyRack.shelf[i].iloscMiejsc;
        sklad.handyRack.shelf[i].Clear(p, old);
        sklad.handyRack.shelf[i].iloscMiejsc = p;
    }
}

void SET_HS(int p) {
    int old = sklad.handyShelf.iloscMiejsc;
    sklad.handyShelf.Clear(p, old);
    sklad.handyShelf.iloscMiejsc = p;
}

void PUT_W(int w, int r, int s, int p, int a) {
    if (check_places(w, r, s, p)) return;
    if (check_max(a)) return;
    int foo = sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
    foo += a;
    // foo = foo > MAX_TOWAR ? MAX_TOWAR : foo;
    if (foo > MAX_TOWAR) {
        sum += MAX_TOWAR - sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
        sklad.warehouse[w].rack[r].shelf[s].place[p].towar = MAX_TOWAR;
    } else {
        sum += a;
        sklad.warehouse[w].rack[r].shelf[s].place[p].towar = foo;
    }
}

void PUT_H(int w, int p, int a) {
    if (check_warehouse_handy_shelfs(w, p)) return;
    if (check_max(a)) return;
    int foo = sklad.warehouse[w].handyShelf.place[p].towar;    
    foo += a;
    // foo = foo > MAX_TOWAR ? MAX_TOWAR : foo;
    // sklad.warehouse[w].handyShelf.place[p].towar = foo;
    // sum += foo;
    if (foo > MAX_TOWAR) {
        sum += MAX_TOWAR - sklad.warehouse[w].handyShelf.place[p].towar;
        sklad.warehouse[w].handyShelf.place[p].towar = MAX_TOWAR;
    } else {
        sum += a;
        sklad.warehouse[w].handyShelf.place[p].towar = foo;
    }
}

void PUT_R(int s, int p, int a) {
    if (check_handy_racks_shelfs(s, p)) return;
    if (check_max(a)) return;
    int foo = sklad.handyRack.shelf[s].place[p].towar;
    foo += a;
    // foo = foo > MAX_TOWAR ? MAX_TOWAR : foo;
    // sklad.handyRack.shelf[s].place[p].towar = foo;
    // sum += foo;
    if (foo > MAX_TOWAR) {
        sum += MAX_TOWAR - sklad.handyRack.shelf[s].place[p].towar;
        sklad.handyRack.shelf[s].place[p].towar = MAX_TOWAR;
    } else {
        sum += a;
        sklad.handyRack.shelf[s].place[p].towar = foo;
    }
}

void PUT_S(int p, int a) {
    if (check_handy_shelf(p)) return;
    if (check_max(a)) return;
    int foo = sklad.handyShelf.place[p].towar;
    foo += a;
    // foo = foo > MAX_TOWAR ? MAX_TOWAR : foo;
    // sklad.handyShelf.place[p].towar = foo;
    // sum += foo;
    if (foo > MAX_TOWAR) {
        sum += MAX_TOWAR - sklad.handyShelf.place[p].towar;
        sklad.handyShelf.place[p].towar = MAX_TOWAR;
    } else {
        sum += a;
        sklad.handyShelf.place[p].towar = foo;
    }
}

void FILL(int w, int r, int s, int p, int a) {
    sum = 0;
    // sklad.Clear(0, sklad.iloscMagazynow);
    // sklad.handyRack.Clear(0, sklad.handyRack.iloscPolek);
    // sklad.handyShelf.Clear(0, sklad.handyShelf.iloscMiejsc);
    sklad.iloscMagazynow = w;
    sklad.handyRack.iloscPolek = s;
    sklad.handyShelf.iloscMiejsc = p;

    for (int i = 0; i < w; i++) {
        sklad.warehouse[i].iloscRegalow = r;
        for (int j = 0; j < r; j++) {
            sklad.warehouse[i].rack[j].iloscPolek = s;
            for (int k = 0; k < s; k++) {
                sklad.warehouse[i].rack[j].shelf[k].iloscMiejsc = p;
                sklad.handyRack.shelf[k].iloscMiejsc = p;
                sklad.warehouse[i].handyShelf.iloscMiejsc = p;
                for (int l = 0; l < p; l++) {
                    sklad.warehouse[i].rack[j].shelf[k].place[l].towar = a;
                    sklad.warehouse[i].rack[j].shelf[k].place[l].etykieta[0] = 0;
                    sklad.warehouse[i].rack[j].shelf[k].place[l].etykieta[1] = 0;
                    sum += a;

                    // sklad.handyRack.shelf[k].place[l].towar = a;
                    // sklad.handyRack.shelf[k].place[l].etykieta[0] = 0;
                    // sklad.handyRack.shelf[k].place[l].etykieta[1] = 0;

                    // sklad.warehouse[i].handyShelf.place[l].towar = a;
                    // sklad.warehouse[i].handyShelf.place[l].etykieta[0] = 0;
                    // sklad.warehouse[i].handyShelf.place[l].etykieta[1] = 0;

                    // sklad.handyShelf.place[l].towar = a;
                    // sklad.handyShelf.place[l].etykieta[0] = 0;
                    // sklad.handyShelf.place[l].etykieta[1] = 0;
                }
            }
        }
        for (int j = 0; j < p; j++) {
            sum += a;
            sklad.warehouse[i].handyShelf.place[j].towar = a;
            sklad.warehouse[i].handyShelf.place[j].etykieta[0] = 0;
            sklad.warehouse[i].handyShelf.place[j].etykieta[1] = 0;
        }
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < p; j++) {
            sum += a;
            sklad.handyRack.shelf[i].place[j].towar = a;
            sklad.handyRack.shelf[i].place[j].etykieta[0] = 0;
            sklad.handyRack.shelf[i].place[j].etykieta[1] = 0;
        }
    }

    for (int i = 0; i < p; i++) {
        sum += a;
        sklad.handyShelf.place[i].towar = a;
        sklad.handyShelf.place[i].etykieta[0] = 0;
        sklad.handyShelf.place[i].etykieta[1] = 0;
    }
    
}

void POP_W(int w, int r, int s, int p, int a) {
    if (check_places(w, r, s, p)) return;
    if (check_max(a)) return;
    int foo = sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
    foo -= a;
    // foo = foo < 0 ? 0 : foo;
    // sklad.warehouse[w].rack[r].shelf[s].place[p].towar = foo;
    if (foo < 0) {
        sum -= sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
        sklad.warehouse[w].rack[r].shelf[s].place[p].towar = 0;
    } else {
        sklad.warehouse[w].rack[r].shelf[s].place[p].towar = foo;
        sum -= a;
    }
}

void POP_H(int w, int p, int a) {
    if (check_warehouse_handy_shelfs(w, p)) return;
    if (check_max(a)) return;
    int foo = sklad.warehouse[w].handyShelf.place[p].towar;    
    foo -= a;
    if (foo < 0) {
        sum -= sklad.warehouse[w].handyShelf.place[p].towar;
        sklad.warehouse[w].handyShelf.place[p].towar = 0;
    } else {
        sklad.warehouse[w].handyShelf.place[p].towar = foo;
        sum -= a;
    }
}

void POP_R(int s, int p, int a) {
    if (check_handy_racks_shelfs(s, p)) return;
    if (check_max(a)) return;
    int foo = sklad.handyRack.shelf[s].place[p].towar;
    foo -= a;
    if (foo < 0) {
        sum -= sklad.handyRack.shelf[s].place[p].towar;
        sklad.handyRack.shelf[s].place[p].towar = 0;
    } else {
        sklad.handyRack.shelf[s].place[p].towar = foo;
        sum -= a;
    }
}

void POP_S(int p, int a) {
    if (check_handy_shelf(p)) return;
    if (check_max(a)) return;
    int foo = sklad.handyShelf.place[p].towar;
    foo -= a;
    if (foo < 0) {
        sum -= sklad.handyShelf.place[p].towar;
        sklad.handyShelf.place[p].towar = 0;
    } else {
        sklad.handyShelf.place[p].towar = foo;
        sum -= a;
    }
}

void MOV_W(int w, int r, int s, int wa, int ra, int sa, int p, int a) {
    if (check_places(w, r, s, p)) return;
    if (check_places(wa, ra, sa, p)) return;    
    int foo = sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
    int bar = sklad.warehouse[wa].rack[ra].shelf[sa].place[p].towar;
    int qty = a > foo ? foo : a;
    qty = bar + qty > MAX_TOWAR ? MAX_TOWAR - bar : qty;
    POP_W(w, r, s, p, qty);
    PUT_W(wa, ra, sa, p, qty);
}

void MOV_H(int w, int r, int s, int p, int a) {
    if (check_places(w, r, s, p)) return;
    if (check_warehouse_handy_shelfs(w, p)) return;
    int foo = sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
    int bar = sklad.warehouse[w].handyShelf.place[p].towar;
    int qty = a > foo ? foo : a;
    qty = bar + qty > MAX_TOWAR ? MAX_TOWAR - bar : qty;
    POP_W(w, r, s, p, qty);
    PUT_H(w, p, qty);
}

void MOV_R(int w, int r, int s, int sa, int p, int a) {
    if (check_places(w, r, s, p)) return;
    if (check_handy_racks_shelfs(sa, p)) return;
    int foo = sklad.warehouse[w].rack[r].shelf[s].place[p].towar;
    int bar = sklad.handyRack.shelf[sa].place[p].towar;
    int qty = a > foo ? foo : a;
    qty = bar + qty > MAX_TOWAR ? MAX_TOWAR - bar : qty;
    POP_W(w, r, s, p, qty);
    PUT_R(sa, p, qty);
}

void MOV_S(int s, int p, int a) {
    if (check_handy_racks_shelfs(s, p)) return;
    if (check_handy_shelf(p)) return;
    int foo = sklad.handyRack.shelf[s].place[p].towar;
    int bar = sklad.handyShelf.place[p].towar;
    int qty = a > foo ? foo : a;
    qty = bar + qty > MAX_TOWAR ? MAX_TOWAR - bar : qty;
    POP_R(s, p, qty);
    PUT_S(p, qty);
}

long long GET_SW(int w, int r, int s) {
    if (check_shelfs(w, r, s)) return -1;

    long long suma = 0;
    for (int i = 0; i < sklad.warehouse[w].rack[r].shelf[s].iloscMiejsc; i++) {
        suma += sklad.warehouse[w].rack[r].shelf[s].place[i].towar;
    }

    return suma;
}

long long GET_RW(int w, int r) {
    if (check_racks(w, r)) return -1;

    long long suma = 0;

    for (int i = 0; i < sklad.warehouse[w].rack[r].iloscPolek; i++) {
        suma += GET_SW(w, r, i);
    }

    return suma;
}

long long GET_SH(int w) {
    if (check_warehouses(w)) return -1;

    long long suma = 0;

    for (int i = 0; i < sklad.warehouse[w].handyShelf.iloscMiejsc; i++) {
        suma += sklad.warehouse[w].handyShelf.place[i].towar;
    }

    return suma;
}

long long GET_W(int w) {
    if (check_warehouses(w)) return -1;

    long long suma = 0;

    for (int i = 0; i < sklad.warehouse[w].iloscRegalow; i++) {
        suma += GET_RW(w, i);
    }

    suma += GET_SH(w);

    return suma;
}


unsigned long long GET_RH() {
    unsigned long long suma = 0;

    for (int i = 0; i < sklad.handyRack.iloscPolek; i++) {
        for(int j = 0; j < sklad.handyRack.shelf[i].iloscMiejsc; j++) {
            suma += sklad.handyRack.shelf[i].place[j].towar;
        }
    }

    return suma;
}


unsigned long long GET_SR(int s) {
    if (check_handy_racks(s)) return -1;
    unsigned long long suma = 0;

    for (int i = 0; i < sklad.handyRack.shelf[s].iloscMiejsc; i++) {
        suma += sklad.handyRack.shelf[s].place[i].towar;
    }

    return suma;
}

unsigned long long GET_S() {
    unsigned long long suma = 0;

    for (int i = 0; i < sklad.handyShelf.iloscMiejsc; i++) {
        suma += sklad.handyShelf.place[i].towar;
    }

    return suma;
}

long long GET_E() {

    // long long suma = 0;

    // for (int i = 0; i < sklad.iloscMagazynow; i++) {
    //     suma += GET_W(i);
    // }
    
    // suma += GET_RH();
    // suma += GET_S();

    return sum;
}

void SET_LW(int w, int r, int s, int p, char dd[]) {
    if (check_places(w, r, s, p)) return;
    sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[0] = dd[0];
    sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[1] = dd[1];
}

void SET_LH(int w, int p, char dd[]) {
    if (check_warehouse_handy_shelfs(w, p)) return;
    sklad.warehouse[w].handyShelf.place[p].etykieta[0] = dd[0];
    sklad.warehouse[w].handyShelf.place[p].etykieta[1] = dd[1];
}

void SET_LR(int s, int p, char dd[]) {
    if (check_handy_racks_shelfs(s, p)) return;
    sklad.handyRack.shelf[s].place[p].etykieta[0] = dd[0];
    sklad.handyRack.shelf[s].place[p].etykieta[1] = dd[1];
}

void SET_LS(int p, char dd[]) {
    if (check_handy_shelf(p)) return;
    sklad.handyShelf.place[p].etykieta[0] = dd[0];
    sklad.handyShelf.place[p].etykieta[1] = dd[1];
}

void GET_LW(int w, int r, int s, int p) {
    if (check_places(w, r, s, p)) return;
    if (sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[0] == 0 
    && sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[1] == 0) {
        std::cout << "--\n";
    } else {
        std::cout << sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[0] 
        << sklad.warehouse[w].rack[r].shelf[s].place[p].etykieta[1] << '\n';
    }
}

void GET_LH(int w, int p) {
    if (check_warehouse_handy_shelfs(w, p)) return;
    if (sklad.warehouse[w].handyShelf.place[p].etykieta[0] == 0
    && sklad.warehouse[w].handyShelf.place[p].etykieta[1] == 0) {
        std::cout << "--\n";
    } else {
        std::cout << sklad.warehouse[w].handyShelf.place[p].etykieta[0] 
        << sklad.warehouse[w].handyShelf.place[p].etykieta[1] << '\n';
    }
}

void GET_LR(int s, int p) {
    if (check_handy_racks_shelfs(s, p)) return;
    if (sklad.handyRack.shelf[s].place[p].etykieta[0] == 0 
    && sklad.handyRack.shelf[s].place[p].etykieta[1] == 0) {
        std::cout << "--\n";
    } else {
        std::cout << sklad.handyRack.shelf[s].place[p].etykieta[0] 
        << sklad.handyRack.shelf[s].place[p].etykieta[1] << '\n';
    }
}

void GET_LS(int p) {
    if (check_handy_shelf(p)) return;
    if (sklad.handyShelf.place[p].etykieta[0] == 0
    && sklad.handyShelf.place[p].etykieta[1] == 0) {
        std::cout << "--\n";
    } else {
        std::cout << sklad.handyShelf.place[p].etykieta[0] 
        << sklad.handyShelf.place[p].etykieta[1] << '\n';
    }
}

int main () {
    std::string polecenie = "\0";
    int w, r, s, p, a, wa, ra, sa;
    std::string dds;
    char dd[2];
    while (polecenie.substr(0, 3) != "END") {
        std::cin >> polecenie;
        if (polecenie.substr(0, 3) == "SET") {
            if (polecenie.substr(polecenie.find('-') + 1, 2) == "AP") {
                std::cin >> w >> r >> s >> p;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else
                SET_AP(w, r, s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "AS") {
                std::cin >> w >> r >> s >> p;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_AS(w, r, s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "AR") {
                std::cin >> w >> r >> s >> p;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_AR(w, r, s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "AW") {
                std::cin >> w >> r >> s >> p;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_AW(w, r, s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "HW") {
                std::cin >> w >> p;
                if (w > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_HW(w, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "HR") {
                std::cin >> s >> p;
                if (s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_HR(s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "HS") {
                std::cin >> p;
                if (p > 128) {
                    std::cout << "error\n";
                } else 
                SET_HS(p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LW") {
                std::cin >> w >> r >> s >> p >> dds;
                dd[0] = dds[0];
                dd[1] = dds[1];
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_LW(w, r, s, p, dd);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LH") {
                std::cin >> w >> p >> dds;
                dd[0] = dds[0];
                dd[1] = dds[1];
                if (w > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_LH(w, p, dd);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LR") {
                std::cin >> w >> p >> dds;
                dd[0] = dds[0];
                dd[1] = dds[1];
                if (w > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                SET_LR(w, p, dd);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LS") {
                std::cin >> p >> dds;
                dd[0] = dds[0];
                dd[1] = dds[1];
                if (p > 128) {
                    std::cout << "error\n";
                } else 
                SET_LS(p, dd);
            } 
        } else if (polecenie.substr(0, 3) == "PUT") {
            if (polecenie.substr(polecenie.find('-') + 1, 1) == "W") {
                std::cin >> w >> r >> s >> p >> a;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                PUT_W(w, r, s, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "H") {
                std::cin >> w >> p >> a;
                if (w > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                PUT_H(w, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "R") {
                std::cin >> s >> p >> a;
                if (s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                PUT_R(s, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "S") {
                std::cin >> p >> a;
                if (p > 128) {
                    std::cout << "error\n";
                } else 
                PUT_S(p, a);
            }
        } else if (polecenie.substr(0, 4) == "FILL") {
            std::cin >> w >> r >> s >> p >> a;
            if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
             } else 
            FILL(w, r, s, p, a);
        } else if (polecenie.substr(0, 3) == "POP") {
            if (polecenie.substr(polecenie.find('-') + 1, 1) == "W") {
                std::cin >> w >> r >> s >> p >> a;
                if (w > 128 || r > 128 || s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                POP_W(w, r, s, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "H") {
                std::cin >> w >> p >> a;
                if (w > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                POP_H(w, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "R") {
                std::cin >> s >> p >> a;
                if (s > 128 || p > 128) {
                    std::cout << "error\n";
                } else 
                POP_R(s, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "S") {
                std::cin >> p >> a;
                if (p > 128) {
                    std::cout << "error\n";
                } else 
                POP_S(p, a);
            }
        } else if (polecenie.substr(0, 3) == "MOV") {
            if (polecenie.substr(polecenie.find('-') + 1, 1) == "W") {
                std::cin >> w >> r >> s >> wa >> ra >> sa >> p >> a;
                MOV_W(w, r, s, wa, ra, sa, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "H") {
                std::cin >> w >> r >> s >> p >> a;
                MOV_H(w, r, s, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "R") {
                std::cin >> w >> r >> s >> sa >> p >> a;
                MOV_R(w, r, s, sa, p, a);
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "S") {
                std::cin >> s >> p >> a;
                MOV_S(s, p, a);
            }
        } else if (polecenie.substr(0, 3) == "GET") {
            long long wynik;
            if (polecenie.substr(polecenie.find('-') + 1, 2) == "RW") {
                std::cin >> w >> r;
                if (w > 128 || r > 128) {
                    std::cout << "error\n";
                } else {
                    wynik = GET_RW(w, r);
                    if (wynik != -1) {
                        std::cout << GET_RW(w, r) << '\n';
                    }
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "RH") {
                wynik = GET_RH();
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "SW") {
                std::cin >> w >> r >> s;
                wynik = GET_SW(w, r, s);
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "SH") {
                std::cin >> w;
                wynik = GET_SH(w);
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "SR") {
                std::cin >> s;
                wynik = GET_SR(s);
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "E") {
                wynik = GET_E();
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "W") {
                std::cin >> w;
                wynik = GET_W(w);
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 1) == "S") {
                wynik = GET_S();
                if (wynik != -1) {
                    std::cout << wynik << '\n';
                }
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LW") {
                std::cin >> w >> r >> s >> p;
                GET_LW(w, r, s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LH") {
                std::cin >> w >> p;
                GET_LH(w,p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LR") {
                std::cin >> s >> p;
                GET_LR(s, p);
            } else if (polecenie.substr(polecenie.find('-') + 1, 2) == "LS") {
                std::cin >> p;
                GET_LS(p);
            }
        }
    }

    // std::cout << "ilosc polek warehouse: " << 
    // std::cout << "ilosc polek handy rack: " << sklad.handyRack.iloscPolek << "\n";
    // std::cout << "ilosc miejsc handy shelf: " << sklad.handyShelf.iloscMiejsc << '\n';
    // std::cout << "ilosc polek: " << sklad.warehouse[0].rack[0].iloscPolek << '\n';
    // std::cout << "ilosc miejsc: " << sklad.warehouse[0].rack[0].shelf[0].iloscMiejsc << '\n';
    // std::cout << "aa: " << sklad.warehouse[0].rack[0].shelf[0].place[0].towar << "\n";
    // suma = 0;
    // GET_S();
    // std::cout << "sdf: " << suma << "\n";

    return 0;
}