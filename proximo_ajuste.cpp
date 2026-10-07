#include <iostream>
#include <vector>

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

    for (const auto& b : memoria) {
        cout << b.id << "\t\t" << b.tamaño << "\t";

        if (b.libre)
            cout << "libre\t\t-";
        else
            cout << "ocupado\t\t" << b.idProceso;

        cout << endl;
    }
}

void proximoAjuste(
    vector<Bloque>& memoria,
    int idProceso,
    int tamañoProceso,
    int& punteroInicio
) {
    int n = memoria.size();
    int contador = 0;
    int indiceActual = punteroInicio;

    while (contador < n) {
        if (memoria[indiceActual].libre &&
            memoria[indiceActual].tamaño >= tamañoProceso) {

            if (memoria[indiceActual].tamaño > tamañoProceso) {
                Bloque sobrante;

                sobrante.id = memoria.size() + 1;
                sobrante.tamaño =
                    memoria[indiceActual].tamaño - tamañoProceso;
                sobrante.libre = true;
                sobrante.idProceso = -1;

                memoria[indiceActual].tamaño = tamañoProceso;
                memoria[indiceActual].libre = false;
                memoria[indiceActual].idProceso = idProceso;

                memoria.insert(
                    memoria.begin() + indiceActual + 1,
                    sobrante
                );
            } else {
                memoria[indiceActual].libre = false;
                memoria[indiceActual].idProceso = idProceso;
            }

            cout << "proceso " << idProceso
                 << " (" << tamañoProceso << ") "
                 << "asignado en bloque "
                 << memoria[indiceActual].id << endl;

            punteroInicio = (indiceActual + 1) % memoria.size();

            return;
        }

        indiceActual = (indiceActual + 1) % n;
        contador++;
    }

    cout << "proceso " << idProceso
         << " (" << tamañoProceso << ") "
         << "no asignado "
         << "(memoria llena)" << endl;
}

int main() {
    vector<Bloque> memoria = {
        {1, 100, true, -1},
        {2, 500, true, -1},
        {3, 200, true, -1},
        {4, 300, true, -1},
        {5, 600, true, -1}
    };

    int puntero = 0;

    cout << "algoritmo proximo ajuste" << endl;

    imprimirMemoria(memoria);

    proximoAjuste(memoria, 1, 212, puntero);
    proximoAjuste(memoria, 2, 417, puntero);
    proximoAjuste(memoria, 3, 112, puntero);
    proximoAjuste(memoria, 4, 301, puntero);

    imprimirMemoria(memoria);

    return 0;
}
