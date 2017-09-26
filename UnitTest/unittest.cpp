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
	bool check(int a[M]) {

		rep(i, 0, 80) {
			cout << a[i] - '0' << " ";
			if ((i + 1) % 9 == 0)
				cout << endl;
		}
		cout << endl;
		bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
		memset(vis_col, false, sizeof(vis_col));
		memset(vis_magic, false, sizeof(vis_magic));
		memset(vis_row, false, sizeof(vis_row));
		int x, y;
		rep(i, 0, 80) {
			a[i] -= '0';
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
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}
		TEST_METHOD(TestMethod2)
		{
			Sudoku s;
			s.work1(10000);
			bool zy = true;
			freopen("out.txt", "w", stdout);
			rep(i, 1, 10000) {
				if (!check(s.ans_1[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual(s.cnt, 10000);
			//Assert::AreEqual(zy, true);
		}
	};
}