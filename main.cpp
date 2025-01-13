/*
Carlos Ernesto Soto Alarcón A01747990
Karime Itzel Ruvalcaba Pérez A01656188
Sergio Alfonso Casillas Santoyo A01424863
*/

#include <iostream>
#include <vector>
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

int main() {
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

    return 0;
}
