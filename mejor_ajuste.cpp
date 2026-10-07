#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Bloque {
    int id;
    int tamaño;
    bool libre;
    int idProceso;
};

void imprimirMemoria(const vector<Bloque>& memoria) {
    cout << "estado de la memoria:" << endl;
    cout << "id bloque\ttamaño\testado\t\tproceso" << endl;

    for (const auto& bloque : memoria) {
        cout << bloque.id << "\t\t"
             << bloque.tamaño << "\t";

        if (bloque.libre) {
            cout << "libre\t\t-";
        } else {
            cout << "ocupado\t\t" << bloque.idProceso;
        }

        cout << endl;
    }
}

void mejorAjuste(vector<Bloque>& memoria, int idProceso, int tamañoProceso) {
    int mejorIndice = -1;
    int menorSobra = INT_MAX;

    for (int i = 0; i < memoria.size(); i++) {
        if (memoria[i].libre &&
            memoria[i].tamaño >= tamañoProceso) {

            int sobra = memoria[i].tamaño - tamañoProceso;

            if (sobra < menorSobra) {
                menorSobra = sobra;
                mejorIndice = i;
            }
        }
    }

    if (mejorIndice != -1) {

        if (memoria[mejorIndice].tamaño > tamañoProceso) {
            Bloque sobrante;

            sobrante.id = memoria.size() + 1;
            sobrante.tamaño =
                memoria[mejorIndice].tamaño - tamañoProceso;
            sobrante.libre = true;
            sobrante.idProceso = -1;

            memoria[mejorIndice].tamaño = tamañoProceso;
            memoria[mejorIndice].libre = false;
            memoria[mejorIndice].idProceso = idProceso;

            memoria.insert(
                memoria.begin() + mejorIndice + 1,
                sobrante
            );

        } else {
            memoria[mejorIndice].libre = false;
            memoria[mejorIndice].idProceso = idProceso;
        }

        cout << "proceso " << idProceso
             << " (" << tamañoProceso << ") "
             << "asignado en bloque "
             << memoria[mejorIndice].id << endl;

    } else {
        cout << "proceso " << idProceso
             << " (" << tamañoProceso << ") "
             << "no asignado "
             << "sin espacio suficiente" << endl;
    }
}

int main() {

    vector<Bloque> memoria = {
        {1, 100, true, -1},
        {2, 500, true, -1},
        {3, 200, true, -1},
        {4, 300, true, -1},
        {5, 600, true, -1}
    };

    cout << "algoritmo mejor ajuste" << endl;

    imprimirMemoria(memoria);

    mejorAjuste(memoria, 1, 212);
    mejorAjuste(memoria, 2, 417);
    mejorAjuste(memoria, 3, 112);
    mejorAjuste(memoria, 4, 301);

    imprimirMemoria(memoria);

    return 0;
}
