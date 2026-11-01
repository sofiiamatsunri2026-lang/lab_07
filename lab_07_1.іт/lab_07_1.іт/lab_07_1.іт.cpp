// Lab_7_1.cpp
// Мацун Софія
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 19

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// формування матриці випадковими числами з діапазону [Low; High]
void Create(int** D, const int rowCount, const int colCount, const int Low, const int High);

// виведення матриці у вигляді таблиці
void Print(int** D, const int rowCount, const int colCount);

// впорядкування рядків матриці за ключами: 1-й стовпчик ↑, 2-й стовпчик ↓, 4-й стовпчик ↑
void Sort(int** D, const int rowCount, const int colCount);

// обмін місцями двох рядків матриці
void Change(int** D, const int row1, const int row2, const int colCount);

// обчислення кількості k та суми S елементів за критерієм: всі додатні, крім кратних 5,
// і заміна цих елементів нулями
void Calc(int** D, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = -31;      // нижня межа значень елементів
    const int High = 54;      // верхня межа значень елементів

    const int rowCount = 9;   // кількість рядків матриці
    const int colCount = 5;   // кількість стовпчиків матриці

    // D – матриця цілих чисел (динамічний двовимірний масив)
    int** D = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        D[i] = new int[colCount];

    Create(D, rowCount, colCount, Low, High);
    Print(D, rowCount, colCount);

    Sort(D, rowCount, colCount);
    Print(D, rowCount, colCount);

    int S = 0;   // сума елементів, що задовольняють критерію
    int k = 0;   // кількість елементів, що задовольняють критерію
    Calc(D, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(D, rowCount, colCount);

    // звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] D[i];
    delete[] D;

    return 0;
}

void Create(int** D, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            D[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** D, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << D[i][j];
        cout << endl;
    }
    cout << endl;
}

void Sort(int** D, const int rowCount, const int colCount)
{
    // метод обміну («бульбашки»): i0 – номер проходу, i1 – номер поточного рядка
    for (int i0 = 0; i0 < rowCount - 1; i0++)
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++)
            if ((D[i1][0] > D[i1 + 1][0])                 // 1-й стовпчик – за зростанням
                ||
                (D[i1][0] == D[i1 + 1][0] &&
                    D[i1][1] < D[i1 + 1][1])                 // 2-й стовпчик – за спаданням
                ||
                (D[i1][0] == D[i1 + 1][0] &&
                    D[i1][1] == D[i1 + 1][1] &&
                    D[i1][3] > D[i1 + 1][3]))                // 4-й стовпчик – за зростанням
                Change(D, i1, i1 + 1, colCount);
}

void Change(int** D, const int row1, const int row2, const int colCount)
{
    int tmp;   // тимчасова змінна для обміну значень
    for (int j = 0; j < colCount; j++)
    {
        tmp = D[row1][j];
        D[row1][j] = D[row2][j];
        D[row2][j] = tmp;
    }
}

void Calc(int** D, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (D[i][j] > 0 && !(D[i][j] % 5 == 0))
            {
                S += D[i][j];
                k++;
                D[i][j] = 0;
            }
}