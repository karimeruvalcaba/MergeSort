
/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>  // Para isatty y fileno
using namespace std;

void merge_arrays(vector<double>& arr, int left, int mid, int right) {
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

void merge_sort(vector<double>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge_arrays(arr, left, mid, right);
    }
}

// Entrada desde archivo (txt)
void process_txt_input() {
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

        merge_sort(valores, 0, N - 1);

        cout << "\nResultado:\nValores ordenados de mayor a menor:\n";
        for (double val : valores) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Entrada manual
void manual_input() {
    int N;

    cout << "Ingrese el número de valores a ordenar: ";
    cin >> N;

    vector<double> valores(N);

    cout << "\nIngrese " << N << " valores (reales o enteros), uno por línea:\n";
    for (int i = 0; i < N; i++) {
        cin >> valores[i];
    }

    merge_sort(valores, 0, N - 1);

    cout << "\nResultado:\nValores ordenados de mayor a menor:\n";
    for (double val : valores) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    if (isatty(fileno(stdin))) {
        // Entrada manual
        manual_input();
    } else {
        // Entrada desde archivo txt
        process_txt_input();
    }

    return 0;
}
