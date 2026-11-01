// Lab_7_2_1.cpp
// Мацун Софія
// Лабораторна робота № 7.2.1
// Опрацювання багатовимірних масивів ітераційним способом.
// Варіант 19

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// формування матриці випадковими числами з діапазону [Low; High]
void Create(int** a, const int n, const int Low, const int High);

// виведення матриці у вигляді таблиці
void Print(int** a, const int n);

// пошук номера стовпчика максимального елемента рядка row
int SearchMaxCol(int** a, const int n, const int row);

// міняє місцями елементи рядків матриці так, щоб максимальні елементи
// по всіх рядках розмістилися на головній діагоналі
void MaxToDiagonal(int** a, const int n);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = -50;   // нижня межа значень елементів
    const int High = 50;   // верхня межа значень елементів

    int n;                 // розмірність матриці (n х n)
    cout << "n = "; cin >> n;

    // a – матриця цілих чисел (динамічний двовимірний масив)
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    Create(a, n, Low, High);
    Print(a, n);

    MaxToDiagonal(a, n);
    Print(a, n);

    // звільнення пам'яті
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int n, const int Low, const int High)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** a, const int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

int SearchMaxCol(int** a, const int n, const int row)
{
    int maxCol = 0;   // номер стовпчика максимального елемента
    for (int j = 1; j < n; j++)
        if (a[row][j] > a[row][maxCol])
            maxCol = j;
    return maxCol;
}

void MaxToDiagonal(int** a, const int n)
{
    int j;     // номер стовпчика максимального елемента поточного рядка
    int tmp;   // тимчасова змінна для обміну значень
    for (int i = 0; i < n; i++)
    {
        j = SearchMaxCol(a, n, i);
        tmp = a[i][i];
        a[i][i] = a[i][j];
        a[i][j] = tmp;
    }
}