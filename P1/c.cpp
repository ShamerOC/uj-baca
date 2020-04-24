//Krzysztof Wydrzynski

#include <iostream>

void Add (int a, int *tab) {
    int n = 0;
    bool add;

    while(tab[n] != -1) {
        n++;
    }

    add = a >= 1 && a <= 4095 ? true : false;

    for (int i = 0; i < n; i++) {
        if (tab[i] == a) add = false;
    }

    if (add) {
        tab[n] = a;
        tab[n + 1] = -1;
    }
}
 
void Intersection (int jeden[], int dwa[], int out[]) {
    int n = 0;
    int m = 0;

    while (jeden[n] != -1) {
        n++;
    }
    n++;

    while (dwa[m] != -1) {
        m++;
    }
    m++;

    int licznik = 0;
    int indeks = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (jeden[i] == dwa[j]) {
                licznik++;
            }
        }
        if (licznik > 0) {
            out[indeks] = jeden[i];
            indeks++;
        }
        licznik = 0;
    }

    for (int i = 0; i < indeks - 1; i++) {
        // std::cout << out[i] << " ";
    }
}

void Symmetric (int jeden[], int dwa[], int out[]) {
    int n = 0;
    int m = 0;

    while (jeden[n] != -1) {
        n++;
    }
    n++;

    while (dwa[m] != -1) {
        m++;
    }
    m++;
    int licznik = 0;
    int indeks = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (jeden[i] == dwa[j]) {
                licznik++;
            }
        }
        if (licznik == 0) {
            out[indeks] = jeden[i];
            indeks++;
        }
        licznik = 0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dwa[i] == jeden[j]) {
                licznik++;
            }
        }
        if (licznik == 0) {
            out[indeks] = dwa[i];
            indeks++;
        }
        licznik = 0;
    }

    out[indeks] = -1;


}

void Create (int n, int arr[], int out[]) {
    int indeks = 0;
    int licznik = 0;
    bool o = false;
    int liczba;

    for (int i = 0; i < n; i++) {
        o = false;
        liczba = arr[i];
        out[indeks] = liczba;
        for (int j = 0; j < indeks; j++) {
            if (out[j] == liczba) licznik++;
        }
        if (licznik == 0 && liczba <= 4095 && liczba >= 1) {
            indeks++;
            o = true;
        }
        licznik = 0;
    }
    if (o) {
        out[indeks - 1] = -1;
    } else out[indeks] = -1;
}

void Union (int jeden[], int dwa[], int out[]) {
    int n = 0;
    int m = 0;
    while (jeden[n] != -1) {
        n++;
    }
    n++;
    while (dwa[m] != -1) {
        m++;
    }
    m++;
    Create(n, jeden, out);

    for (int i = 0; i < m - 1; i++) {
        Add(dwa[i], out);
    }

    int ws = 0;
    while (out[ws] != -1) {
        ws++;
    }
    ws++;

}

void Difference(int jeden[], int dwa[], int out[]) {
    int n = 0;
    int m = 0;

    while (jeden[n] != -1) {
        n++;
    }
    n++;

    while (dwa[m] != -1) {
        m++;
    }
    m++;
    int licznik = 0;
    int indeks = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (jeden[i] == dwa[j]) {
                licznik++;
            }
        }
        if (licznik == 0) {
            out[indeks] = jeden[i];
            indeks++;
        }
        licznik = 0;
    }
    out[indeks] = -1;
}

void Complement(int jeden[], int dwa[]) {
    int n = 0;
    while (jeden[n] != -1) {
        n++;
    }
    n++;
    int licznik = 0;
    int indeks = 0;
    int max = jeden[n - 2];
    for (int i = 1; i <= 4095; i++) {
        for (int j = 0; j < n; j++) {
            if (jeden[j] == i) licznik++;
        }
        if (licznik == 0) {
            dwa[indeks] = i;
            indeks++;
        }
        licznik = 0;
    }
    dwa[indeks] = -1;
}

bool Subset(int jeden[], int dwa[]) {
    int n = 0;
    int m = 0;

    while (jeden[n] != -1) {
        n++;
    }
    n++;

    while (dwa[m] != -1) {
        m++;
    }
    m++;
    int licznik = 0;
    int wynik = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (jeden[i] == dwa[j]) {
                licznik++;
            }
        }
        if (licznik > 0) {
            wynik++;
        }
        licznik = 0;
    }
    return wynik == n ? true : false;
}

bool Equal(int jeden[], int dwa[]) {
    int n = 0;
    int m = 0;
    int licznik = 0;
    int wynik = 0;


    while (jeden[n] != -1) {
        n++;
    }
    n++;

    while (dwa[m] != -1) {
        m++;
    }
    m++;
    
    if (m != n) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (jeden[i] == dwa[j]) {
                licznik++;
            }
        }
        if (licznik > 0) wynik++;
        licznik = 0;
    }

    return wynik == n ? true : false;
}

bool Empty(int jeden[]) {
    if (jeden[0] == -1) {
        return true;
    }
    return false;
}

bool Nonempty(int jeden[]) {
    if (jeden[0] != -1) {
        return true;
    }
    return false;
}

bool Element(int el, int arr[]) {
    int n = 0;

    while (arr[n] != -1) {
        n++;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] == el) return true;
    }
    return false;
}

double Arithmetic(int arr[]) {
    if (Empty(arr)) return 0;
    int n = 0;
    double suma = 0;

    while (arr[n] != -1) {
        n++;
    }

    for (int i = 0; i < n; i++) {
        suma += arr[i];
    }

    return suma / n;
}

double Harmonic(int arr[]) {
    if (Empty(arr)) return 1;
    int n = 0;
    double suma = 0;

    while (arr[n] != -1) {
        n++;
    }

    for (int i = 0; i < n; i++) {
        suma += (double)1 / arr[i];
    }


    return n / suma;
}

void MinMax(int arr[], int *min, int &max) {
    int n = 0;
    while (arr[n] != -1) {
        n++;
    }

    if (Nonempty(arr)) {
        *min = arr[0];
        max = arr[0];
    }

    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        } else if(arr[i] > max) {
            max = arr[i];
        }
    }
}

void Cardinality(int arr[], int *moc) {
    int n = 0;
    while (arr[n] != -1) {
        n++;
    }
    *moc = n;
}

void Properties(int arr[], char a[], double &arit, double * harm, int & min, int * max, int & moc) {
    int n = 0;
    while (a[n] != '\0') {
        n++;
    }
    for(int i = 0; i < n; i++) {
        if (a[i] == 'a') arit = Arithmetic(arr);
        else if (a[i] == 'h') *harm = Harmonic(arr);
        else if (a[i] == 'm') MinMax(arr, &min, *max);
        else if (a[i] == 'c') Cardinality(arr, &moc);
    }
}