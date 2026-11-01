// UnitTest_7_1.cpp
// Мацун Софія
// Unit-тест функції Calc (Лабораторна робота № 7.1, ітераційний спосіб).
// Варіант 19

#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_07_1.іт.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_7_1
{
    TEST_CLASS(UnitTest_7_1)
    {
    public:

        // перевірка суми S та кількості k, а також заміни елементів нулями
        TEST_METHOD(TestCalc)
        {
            const int rowCount = 3;
            const int colCount = 4;

            int source[rowCount][colCount] = {
                {  3,   5, -7, 10 },
                {  0,  12, -5, 54 },
                { 25, -31,  7,  8 }
            };
            int expected[rowCount][colCount] = {
                {  0,   5, -7, 10 },
                {  0,   0, -5,  0 },
                { 25, -31,  0,  0 }
            };

            int** D = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
            {
                D[i] = new int[colCount];
                for (int j = 0; j < colCount; j++)
                    D[i][j] = source[i][j];
            }

            int S = 0;
            int k = 0;
            Calc(D, rowCount, colCount, S, k);

            Assert::AreEqual(84, S);
            Assert::AreEqual(5, k);
            for (int i = 0; i < rowCount; i++)
                for (int j = 0; j < colCount; j++)
                    Assert::AreEqual(expected[i][j], D[i][j]);

            for (int i = 0; i < rowCount; i++)
                delete[] D[i];
            delete[] D;
        }

        // перевірка випадку, коли жоден елемент не задовольняє критерію
        TEST_METHOD(TestCalcNoElements)
        {
            const int rowCount = 2;
            const int colCount = 3;

            int** D = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                D[i] = new int[colCount];

            D[0][0] = -3; D[0][1] = 0;   D[0][2] = 5;
            D[1][0] = 10; D[1][1] = -25; D[1][2] = 50;

            int S = 1;
            int k = 1;
            Calc(D, rowCount, colCount, S, k);

            Assert::AreEqual(0, S);
            Assert::AreEqual(0, k);
            Assert::AreEqual(-3, D[0][0]);
            Assert::AreEqual(50, D[1][2]);

            for (int i = 0; i < rowCount; i++)
                delete[] D[i];
            delete[] D;
        }
    };
}