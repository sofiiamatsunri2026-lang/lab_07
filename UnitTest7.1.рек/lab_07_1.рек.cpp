// Lab_7_1_rec.cpp
// Мацун Софія
// Лабораторна робота № 7.1 (рекурсивний спосіб).
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 19

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// формування матриці випадковими числами з діапазону [Low; High];
// i, j – індекси поточного елемента
void Create(int** D, const int rowCount, const int colCount, const int Low, const int High,
    int i, int j);

// виведення матриці у вигляді таблиці; i, j – індекси поточного елемента
void Print(int** D, const int rowCount, const int colCount, int i, int j);

// впорядкування рядків матриці за ключами: 1-й стовпчик ↑, 2-й стовпчик ↓, 4-й стовпчик ↑;
// i0 – номер поточного проходу
void Sort(int** D, const int rowCount, const int colCount, int i0);

// один прохід методу обміну («бульбашки»); i1 – номер поточного рядка
void SortPass(int** D, const int rowCount, const int colCount, const int i0, int i1);

// перевірка, чи стоять рядки row1 і row2 у неправильному порядку за ключами сортування
bool IsWrongOrder(int** D, const int row1, const int row2);

// обмін місцями двох рядків матриці; j – номер поточного стовпчика
void Change(int** D, const int row1, const int row2, const int colCount, int j);

// обчислення кількості k та суми S елементів за критерієм: всі додатні, крім кратних 5,
// і заміна цих елементів нулями; i, j – індекси поточного елемента
void Calc(int** D, const int rowCount, const int colCount, int& S, int& k, int i, int j);

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

    Create(D, rowCount, colCount, Low, High, 0, 0);

    cout << endl;
    Print(D, rowCount, colCount, 0, 0);

    Sort(D, rowCount, colCount, 0);

    cout << endl;
    Print(D, rowCount, colCount, 0, 0);

    int S = 0;   // сума елементів, що задовольняють критерію
    int k = 0;   // кількість елементів, що задовольняють критерію
    Calc(D, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << endl;
    Print(D, rowCount, colCount, 0, 0);

    // звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] D[i];
    delete[] D;

    return 0;
}

void Create(int** D, const int rowCount, const int colCount, const int Low, const int High,
    int i, int j)
{
    D[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(D, rowCount, colCount, Low, High, i, j + 1);
    else
        if (i < rowCount - 1)
            Create(D, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** D, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << D[i][j];
    if (j < colCount - 1)
        Print(D, rowCount, colCount, i, j + 1);
    else
        if (i < rowCount - 1)
        {
            cout << endl;
            Print(D, rowCount, colCount, i + 1, 0);
        }
        else
            cout << endl << endl;
}

void Sort(int** D, const int rowCount, const int colCount, int i0)
{
    SortPass(D, rowCount, colCount, i0, 0);
    if (i0 < rowCount - 2)
        Sort(D, rowCount, colCount, i0 + 1);
}

void SortPass(int** D, const int rowCount, const int colCount, const int i0, int i1)
{
    if (IsWrongOrder(D, i1, i1 + 1))
        Change(D, i1, i1 + 1, colCount, 0);
    if (i1 < rowCount - i0 - 2)
        SortPass(D, rowCount, colCount, i0, i1 + 1);
}

bool IsWrongOrder(int** D, const int row1, const int row2)
{
    return (D[row1][0] > D[row2][0])                      // 1-й стовпчик – за зростанням
        ||
        (D[row1][0] == D[row2][0] &&
            D[row1][1] < D[row2][1])                         // 2-й стовпчик – за спаданням
        ||
        (D[row1][0] == D[row2][0] &&
            D[row1][1] == D[row2][1] &&
            D[row1][3] > D[row2][3]);                        // 4-й стовпчик – за зростанням
}

void Change(int** D, const int row1, const int row2, const int colCount, int j)
{
    int tmp = D[row1][j];   // тимчасова змінна для обміну значень
    D[row1][j] = D[row2][j];
    D[row2][j] = tmp;
    if (j < colCount - 1)
        Change(D, row1, row2, colCount, j + 1);
}

void Calc(int** D, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (D[i][j] > 0 && !(D[i][j] % 5 == 0))
    {
        S += D[i][j];
        k++;
        D[i][j] = 0;
    }
    if (j < colCount - 1)
        Calc(D, rowCount, colCount, S, k, i, j + 1);
    else
        if (i < rowCount - 1)
            Calc(D, rowCount, colCount, S, k, i + 1, 0);
}