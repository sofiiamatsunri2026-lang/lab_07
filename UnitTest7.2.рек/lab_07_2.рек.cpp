// Lab_7_2_2.cpp
// Мацун Софія
// Лабораторна робота № 7.2.2
// Опрацювання багатовимірних масивів рекурсивним способом.
// Варіант 19

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// формування матриці випадковими числами з діапазону [Low; High];
// i, j – індекси поточного елемента
void Create(int** a, const int N, const int Low, const int High, int i, int j)
{
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j < N - 1)
        Create(a, N, Low, High, i, j + 1);
    else
        if (i < N - 1)
            Create(a, N, Low, High, i + 1, 0);
}

// виведення матриці у вигляді таблиці; i, j – індекси поточного елемента
void Print(int** a, const int N, int i, int j)
{
    cout << setw(4) << a[i][j];
    if (j < N - 1)
        Print(a, N, i, j + 1);
    else
        if (i < N - 1)
        {
            cout << endl;
            Print(a, N, i + 1, 0);
        }
        else
            cout << endl << endl;
}

// пошук номера стовпчика максимального елемента рядка rowNo;
// colNo – номер поточного стовпчика
int SearchMaxCol(int** a, const int N, const int rowNo, int colNo)
{
    if (colNo == N - 1)
        return colNo;
    int maxCol = SearchMaxCol(a, N, rowNo, colNo + 1);
    if (a[rowNo][colNo] >= a[rowNo][maxCol])
        return colNo;
    return maxCol;
}

// міняє місцями елементи рядків матриці так, щоб максимальні елементи
// по всіх рядках розмістилися на головній діагоналі; rowNo – номер поточного рядка
void MaxToDiagonal(int** a, const int N, int rowNo)
{
    int j = SearchMaxCol(a, N, rowNo, 0);   // номер стовпчика максимального елемента рядка
    int tmp = a[rowNo][rowNo];              // тимчасова змінна для обміну значень
    a[rowNo][rowNo] = a[rowNo][j];
    a[rowNo][j] = tmp;
    if (rowNo < N - 1)
        MaxToDiagonal(a, N, rowNo + 1);
}

int main()
{
    srand((unsigned)time(NULL));

    const int Low = -50;   // нижня межа значень елементів
    const int High = 50;   // верхня межа значень елементів

    int N;                 // розмірність матриці (N х N)
    cout << "N = "; cin >> N;
    cout << endl;

    // a – матриця цілих чисел (динамічний двовимірний масив)
    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];

    Create(a, N, Low, High, 0, 0);
    Print(a, N, 0, 0);

    MaxToDiagonal(a, N, 0);
    Print(a, N, 0, 0);

    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}