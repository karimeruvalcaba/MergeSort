/*
Carlos Ernesto Soto Alarcón A01747990
Karime Itzel Ruvalcaba Pérez A01656188
Sergio Alfonso Casillas Santoyo A01424863

Este programa implementa el algoritmo Merge Sort para ordenar valores de mayor a menor.
Permite dos modos de entrada:
1. Manual: El usuario introduce los datos interactivamente.
2. Desde archivo txt: Lee los datos desde un archivo utilizando redirección de entrada.

Complejidad computacional:
1. **mergeSort**:
   - Complejidad de tiempo: O(n log n), donde "n" es el número de elementos a ordenar.
     - Divide el arreglo en mitades (O(log n)).
     - Combina las mitades de manera lineal (O(n)).
   - Complejidad de espacio: O(n), debido a los arreglos temporales utilizados en la union

2. **merge**:
   - Complejidad de tiempo: O(n), donde "n" es el tamaño de los dos subarreglos combinados.
   - Complejidad de espacio: O(n), debido a los subarreglos temporales.

3. **ForTxt**:
   - Complejidad de tiempo: O(k * n log n), donde "k" es el número de casos de prueba y "n" es el número promedio de valores por caso.
   - Complejidad de espacio: O(n), debido a los subarreglos creados para cada caso.

4. **Manual**:
   - Complejidad de tiempo: O(n log n), donde "n" es el número de valores proporcionados por el usuario.
   - Complejidad de espacio: O(n), debido a los subarreglos creados durante el ordenamiento.

El programa detecta automáticamente si la entrada es manual o desde un archivo txt.
*/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>  // Para isatty y fileno
using namespace std;

void merge(vector<double>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> leftArr(n1);
    vector<double> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] >= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<double>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Entrada desde archivo (txt)
void ForTxt() {
    string line;
    while (getline(cin, line)) {
        if (line.empty())
            continue;

        int N = stoi(line);  // Leer número de valores
        vector<double> valores(N);

        for (int i = 0; i < N; i++) {
            getline(cin, line);
            valores[i] = stod(line);
        }

        mergeSort(valores, 0, N - 1);

        cout << "\nResultado:\nValores ordenados de mayor a menor:\n";
        for (double val : valores) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Entrada manual
void Manual() {
    int N;

    cout << "Ingrese el número de valores a ordenar: ";
    cin >> N;

    vector<double> valores(N);

    cout << "\nIngrese " << N << " valores (reales o enteros), uno por línea:\n";
    for (int i = 0; i < N; i++) {
        cin >> valores[i];
    }

    mergeSort(valores, 0, N - 1);

    cout << "\nResultado:\nValores ordenados de mayor a menor:\n";
    for (double val : valores) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    if (isatty(fileno(stdin))) {
        // Entrada manual
        Manual();
    } else {
        // Entrada desde archivo txt
        ForTxt();
    }

    return 0;
}
