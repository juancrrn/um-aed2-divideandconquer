#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Solucion {
    public:
        int posicion;
        int apariciones;
};

Solucion SolucionDirecta(string A, int m, char C, int ini) {
    int maxposicion;
    int maxapariciones = -1;

    for (int i = 0; i <= (A.length() - m); i++) {
        int apariciones = 0;
        if ((A[i] == C || i == A.length() - m)) {
            for (int j = 0; j < m; j++) {
                if (A[i + j] == C) {
                    apariciones++;
                }
            }
        
            if (apariciones > maxapariciones) {
                maxposicion = i;
                maxapariciones = apariciones;
            }
        }
    }

    Solucion s;
    s.posicion = maxposicion + 1 + ini;
    s.apariciones = maxapariciones;
    
    return s;
}

bool Pequeno(string A, int m) {
    int n = A.length();
    if (n >= 2 * m) {
        return false;
    } else {
        return true;
    }
}

Solucion Combinar(Solucion s1, Solucion s2, string A, int m, char C, int
ini) {
    ini = ini + ceil(float(A.length()) / 2) - m + 1;
    string frontera = A.substr(ceil(float(A.length()) / 2) - m + 1, (m - 1) * 2);
    Solucion s3 = SolucionDirecta(frontera, m, C, ini);
    
    if (s1.apariciones > s2.apariciones) {
        s2 = s1;
    }

    if (s2.apariciones > s3.apariciones) {
        return s2;
    } else {
        return s3;
    }
}

Solucion DivideVenceras(string A, int m, char C, int ini = 0) {
    if (Pequeno(A, m)) {
        return SolucionDirecta(A, m, C, ini);
    } else {
        int lon = ceil(float(A.length()) / 2);
        string A1 = A.substr(0, lon);
        string A2 = A.substr(lon, A.length() / 2);
        
        return Combinar(DivideVenceras(A1, m, C, ini),
                        DivideVenceras(A2, m, C, ini + lon),
                        A, m, C, ini);
    }
}

int main() {
    string A;
    int m, ncasos;
    char C;
    
    cin >> ncasos;
    
    for (int i = 0 ; i < ncasos; i++){
        cin >> C;
        cin >> m;
        cin >> A;
        
        Solucion s = DivideVenceras(A, m, C);
        
        cout << "Caso: " << i + 1 << endl;
        cout << "Posicion: " << s.posicion << endl;
        cout << "Apariciones: " << s.apariciones << endl;
    }
    
    return 0;
}