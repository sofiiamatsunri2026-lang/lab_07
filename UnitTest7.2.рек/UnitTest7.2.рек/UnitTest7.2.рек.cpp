// UnitTest_7_2_2.cpp
// Мацун Софія
// Unit-тест функцій SearchMaxCol та MaxToDiagonal (Лабораторна робота № 7.2.1, рекурсивний спосіб).
// Варіант 19

#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab_07_2.рек.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_7_2_2
{
    // створення матриці n х n зі значень масиву values (по рядках)
    int** MakeMatrix(const int n, const int* values)
    {
        int** a = new int* [n];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[n];
            for (int j = 0; j < n; j++)
                a[i][j] = values[i * n + j];
        }
        return a;
    }

    void DeleteMatrix(int** a, const int n)
    {
        for (int i = 0; i < n; i++)
            delete[] a[i];
        delete[] a;
    }

    TEST_CLASS(UnitTest_7_2_2)
    {
    public:

        // номер стовпчика максимального елемента рядка
        TEST_METHOD(TestSearchMaxCol)
        {
            const int n = 3;
            const int values[9] = { 1, 9, 3,
                                    4, 2, 8,
                                    7, 5, 6 };
            int** a = MakeMatrix(n, values);

            Assert::AreEqual(1, SearchMaxCol(a, n, 0, 0));
            Assert::AreEqual(2, SearchMaxCol(a, n, 1, 0));
            Assert::AreEqual(0, SearchMaxCol(a, n, 2, 0));

            DeleteMatrix(a, n);
        }

        // від'ємні елементи та однакові максимальні елементи (береться перший)
        TEST_METHOD(TestSearchMaxColNegativeAndEqual)
        {
            const int n = 3;
            const int values[9] = { -5, -2, -9,
                                     2,  7,  7,
                                     3,  1,  2 };
            int** a = MakeMatrix(n, values);

            Assert::AreEqual(1, SearchMaxCol(a, n, 0, 0));
            Assert::AreEqual(1, SearchMaxCol(a, n, 1, 0));
            Assert::AreEqual(0, SearchMaxCol(a, n, 2, 0));

            DeleteMatrix(a, n);
        }

        // максимальні елементи всіх рядків мають опинитися на головній діагоналі
        TEST_METHOD(TestMaxToDiagonal)
        {
            const int n = 3;
            const int values[9] = { 1, 9, 3,
                                    4, 2, 8,
                                    7, 5, 6 };
            const int expected[9] = { 9, 1, 3,
                                      4, 8, 2,
                                      6, 5, 7 };
            int** a = MakeMatrix(n, values);

            MaxToDiagonal(a, n, 0);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    Assert::AreEqual(expected[i * n + j], a[i][j]);

            DeleteMatrix(a, n);
        }

        // максимальні елементи вже на головній діагоналі – матриця не змінюється
        TEST_METHOD(TestMaxToDiagonalNoChange)
        {
            const int n = 2;
            const int values[4] = { 9, 1,
                                    2, 8 };
            int** a = MakeMatrix(n, values);

            MaxToDiagonal(a, n, 0);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    Assert::AreEqual(values[i * n + j], a[i][j]);

            DeleteMatrix(a, n);
        }
    };
}