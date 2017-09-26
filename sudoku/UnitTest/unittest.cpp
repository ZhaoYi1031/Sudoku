#include "stdafx.h"
#include "CppUnitTest.h"
#include "sudoku.h"
#include <iostream>
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
#define rep(i,a,b) for (int i = (a); i <= (b); ++i)
namespace UnitTest
{
	bool check(int a[M]) {//判断终盘是不是一个数独
		rep(i, 0, 80) {
			a[i] -= '0';
			if (a[i] < 0 || a[i] > 9)
				return false;
			/*cout << a[i] << " ";
			if ((i + 1) % 9 == 0)
				cout << endl;*/
		}
		cout << endl;
		bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
		memset(vis_col, false, sizeof(vis_col));
		memset(vis_magic, false, sizeof(vis_magic));
		memset(vis_row, false, sizeof(vis_row));
		int x, y;
		rep(i, 0, 80) {
			x = i / 9;
			y = i % 9;
			if (vis_col[x][a[i]] || vis_row[y][a[i]] || vis_magic[belonging(x, y)][a[i]])
				return false;
			vis_col[x][a[i]] = true;
			vis_row[y][a[i]] = true;
			vis_magic[belonging(x, y)][a[i]] = true;
		}
		return true;
	}

	bool check2(int a[M], int b[M]) {
		rep(i, 0, 80) {
			if (b[i] > 0 && a[i] != b[i])
				return false;
		}
		return true;
	}
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Sudoku s;
			s.work1(1);
			bool zy = true;
			s.out = fopen("unit_out_1.txt", "w");
			rep(i, 1, 1) {
				s.out_file(ans_1[i]);
				if (!check(ans_1[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual(zy, true);
		}
		TEST_METHOD(TestMethod2)
		{
			Sudoku s;
			s.work1(10);
			bool zy = true;
			s.out = fopen("unit_out_2.txt", "w");
			rep(i, 1, 10) {
				s.out_file(ans_1[i]);
			}
			Assert::AreEqual(s.cnt, 10);
		}
		TEST_METHOD(TestMethod3)
		{
			Sudoku s;
			s.work1(100);
			bool zy = true;
			s.out = fopen("unit_out_3.txt", "w");
			rep(i, 1, 100) {
				s.out_file(ans_1[i]);
			}
			Assert::AreEqual(s.value, 100);
		}
		TEST_METHOD(TestMethod4)
		{
			Sudoku s;
			s.work1(1000);
			bool zy = true;
			s.out = fopen("unit_out_4.txt", "w");
			rep(i, 1, 1000) {
				s.out_file(ans_1[i]);
				if (!check(ans_1[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual(zy, true);
		}
		TEST_METHOD(TestMethod5)
		{
			Sudoku s;
			s.work1(10000);
			bool zy = true;
			s.out = fopen("unit_out_5.txt", "w");
			rep(i, 1, 10000) {
				s.out_file(ans_1[i]);
				if (!check(ans_1[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual(zy, true);
		}

		
		TEST_METHOD(TestMethod6)
		{
			Sudoku s;
			int a[82] = {
				4, 0, 0, 0, 0, 0, 8, 0, 5,
				0, 3, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 7, 0, 0, 0, 0, 0,
				0, 2, 0, 0, 0, 0, 0, 6, 0,
				0, 0, 0, 0, 8, 0, 4, 0, 0,
				0, 0, 0, 0, 1, 0, 0, 0, 0,
				0, 0, 0, 6, 0, 3, 0, 7, 0,
				5, 0, 0, 2, 0, 0, 0, 0, 0,
				1, 0, 4, 0, 0, 0, 0, 0, 0
			};
			memcpy(s.x, a, sizeof(a));
			s.work2();
			s.out = fopen("unit_out_6.txt", "w");
			s.out_file(ans_2[1]);
			Assert::AreEqual(check(ans_2[1]), true);
		}
		TEST_METHOD(TestMethod7)
		{
			Sudoku s;
			int a[82] = {
				5, 2, 0, 0, 0, 6, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 7, 0, 1,
				3, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 4, 0, 0, 8, 0, 0,
				6, 0, 0, 0, 0, 0, 0, 5, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 4, 1, 8, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 3, 0, 0, 2, 0,
				0, 0, 8, 7, 0, 0, 0, 0, 0
			};
			memcpy(s.x, a, sizeof(a));
			s.work2();
			s.out = fopen("unit_out_7.txt", "w");
			s.out_file(ans_2[1]);
			Assert::AreEqual(check(ans_2[1]), true);
		}
		TEST_METHOD(TestMethod8)
		{
			Sudoku s;
			int a[82] = {
				6, 0, 0, 0, 0, 0, 8, 0, 3,
				0, 4, 0, 7, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 5, 0, 4, 0, 7, 0,
				3, 0, 0, 2, 0, 0, 0, 0, 0,
				1, 0, 6, 0, 0, 0, 0, 0, 0,
				0, 2, 0, 0, 0, 0, 0, 5, 0,
				0, 0, 0, 0, 8, 0, 6, 0, 0,
				0, 0, 0, 0, 1, 0, 0, 0, 0
			};
			memcpy(s.x, a, sizeof(a));
			s.work2();
			s.out = fopen("unit_out_8.txt", "w");
			s.out_file(ans_2[1]);
			Assert::AreEqual(check(ans_2[1]), true);
		}
		TEST_METHOD(TestMethod9)
		{
			Sudoku s;
			int a[82] = {
				0, 2, 7, 3, 8, 0, 0, 1, 0,
				0, 1, 0, 0, 0, 6, 7, 3, 5,
				0, 0, 0, 0, 0, 0, 0, 2, 9,
				3, 0, 5, 6, 9, 2, 0, 8, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 6, 0, 1, 7, 4, 5, 0, 3,
				6, 4, 0, 0, 0, 0, 0, 0, 0,
				9, 5, 1, 8, 0, 0, 0, 7, 0,
				0, 8, 0, 0, 6, 5, 3, 4, 0
			};
			memcpy(s.x, a, sizeof(a));
			s.work2();
			s.out = fopen("unit_out_9.txt", "w");
			s.out_file(ans_2[1]);
			Assert::AreEqual(check(ans_2[1]), true);
		}
		TEST_METHOD(TestMethod10)
		{
			Sudoku s;
			int a[82] = {
				0, 0, 0, 0, 0, 0, 5, 2, 0,
				0, 8, 0, 4, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 0, 9, 0, 0, 0,
				5, 0, 1, 0, 0, 0, 6, 0, 0,
				2, 0, 0, 7, 0, 0, 0, 0, 0,
				0, 0, 0, 3, 0, 0, 0, 0, 0,
				6, 0, 0, 0, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 7, 0, 4,
				0, 0, 0, 0, 0, 0, 0, 3, 0
			};
			memcpy(s.x, a, sizeof(a));
			s.work2();
			s.out = fopen("unit_out_10.txt", "w");
			s.out_file(ans_2[1]);
			Assert::AreEqual(check(ans_2[1]), true);
			Assert::AreEqual(check2(ans_2[1], a), true);
		}
	};
}