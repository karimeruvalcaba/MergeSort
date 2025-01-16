/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 * File: main.cpp
 * Description:
 * This program implements the Merge Sort algorithm to sort values
 * in descending order (highest to lowest). It supports two input modes:
 * manual input provided by the user and input redirection from a .txt file.
 *
 * Authors:
 * Carlos Ernesto Soto Alarcón (A01747990)
 * Karime Itzel Ruvalcaba Pérez (A01656188)
 * Sergio Alfonso Casillas Santoyo (A01424863)
 *
 * Date Created: January 15, 2025
 *
 * Program Details:
 * This program allows two modes of input:
 * 1. Manual: The user inputs the data interactively.
 * 2. From a .txt file: Reads the data from a file using input redirection.
 *
 * Computational Complexity:
 * 1. merge_sort:
 *    - Time Complexity: O(n log n), where "n" is the number of elements to sort.
 *      - Divides the array into halves (O(log n)).
 *      - Combines the halves linearly (O(n)).
 *    - Space Complexity: O(n), due to the temporary arrays used in merging.
 * 2. merge_arrays:
 *    - Time Complexity: O(n), where "n" is the size of the two subarrays combined.
 *    - Space Complexity: O(n), due to the temporary arrays.
 * 3. process_txt_input:
 *    - Time Complexity: O(k * n log n), where "k" is the number of test cases
 *      and "n" is the average number of values per case.
 *    - Space Complexity: O(n), due to the arrays created for each case.
 * 4. manual_input:
 *    - Time Complexity: O(n log n), where "n" is the number of values provided by the user.
 *    - Space Complexity: O(n), due to the arrays created during sorting.
 *
 * Notes:
 * The program detects automatically whether the input is manual or from a .txt file.
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
