#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sys/timeb.h>
#include <time.h>

#include <QApplication>
#include<QLabel>
#include <QObject>
#include<QLineEdit>
#include<qdebug.h>
#include<algorithm>
#include<ctime>



#define random(x) (rand()%x)

#define rep(i,a,b) for (int i = (a); i <= (b); ++i)
inline int belonging(int x, int y) { return x / 3 * 3 + y / 3 + 1; }
inline int Position(int x, int y) { return 9 * x + y; }
const int N = 11;
const int M = 82;
using namespace std;

class Sudoku : public QObject {
	Q_OBJECT
public:
	int ans_2[110][M], ans_1[110][M];
	int tot, x[M], a[M][N], a_backup[M][M][N], aaa[M], game[M], square[N];
	bool hasAnswer = false, debug = true;
	FILE *out;

	int value, cnt, n, m, len = 0;//value´ú±íÒªÊä³öµÄ¾ØÕóµÄ¸öÊý
	char ch, aa[N][N];
	bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
	inline bool find(int x, int y, int z) { return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]); }

	double p;
	int id, num_0;
	QLineEdit lineEdit[N][N];
	bool isEmpty[M];

	bool deleteElement(int pos, int r) {
		int i;
		if (a[pos][r] == 1)
			return true;
		a[pos][r] = 1;
		if (++a[pos][0] == 9)
			return false;
		if (a[pos][0] == 8)
		{
			for (i = 1; i <= 9; ++i)
				if (a[pos][i] == 0)
					break;
			if (!modifyElement(pos, i))
				return false;
		}
		return true;
	}
	bool modifyElement(int pos, int r) {
		int p = pos / 9;
		int q = pos % 9;
		int h;
		x[pos] = r + '0';
		rep(i, 1, 9)
			a[pos][i] = 1;
		a[pos][0] = 8;
		a[pos][r] = 0;
		rep(j, 0, 8) {
			h = Position(p, j);
			if (h != pos && !deleteElement(h, r))
				return false;
		}
		rep(i, 0, 8) {
			h = Position(i, q);
			if (h != pos && !deleteElement(h, r))
				return false;
		}
		rep(i, 0, 2)
			rep(j, 0, 2)
		{
			h = (3 * (p / 3) + i) * 9 + (3 * (q / 3) + j);
			if (h != pos && !deleteElement(h, r))
				return false;
		}
		return true;
	}
	void dfs2(int k) {
		int mx = -1, mxi;
		rep(i, 0, 80) {
			if (a[i][0]<8 && a[i][0]>mx) {
				mx = a[i][0];
				mxi = i;
			}
		}
		if (mx == -1) {
			cnt++;
			memcpy(ans_1[cnt], x, sizeof(x));
			hasAnswer = true;
			return;
		}
		memcpy(a_backup[k], a, sizeof(a));
		rep(i, 1, 9) {
			if (a[mxi][i] == 0) {
				if (modifyElement(mxi, i))
					dfs2(k + 1);
				memcpy(a, a_backup[k], sizeof(a));
			}
			if (hasAnswer)
				return;
		}
	}
	void dfs1(int k) {
		if (hasAnswer) return;
		int x, y;
		x = k / 9;
		y = k % 9;
		if (k > 80) {
			if (++cnt >= value) {
				hasAnswer = true;
				//exit(0);
			}
			memcpy(ans_1[cnt], aaa, sizeof(aaa));
			return;
		}
		rep(i, 1, 9) {
			if (find(x, y, i)) {
				aaa[k] = i + '0';
				vis_row[x][i] = vis_col[y][i] = vis_magic[belonging(x, y)][i] = true;
				dfs1(k + 1);
				vis_row[x][i] = vis_col[y][i] = vis_magic[belonging(x, y)][i] = false;
			}
		}
	}
	bool calc(char* s) {
		value = 0;
		for (int i = 0; s[i]; ++i) {
			if (s[i] < '0' || s[i] > '9')
				return false;
			value = value * 10 + s[i] - '0';
		}
		return true;
	}

	void work1(int value_t) {

		memset(vis_magic, false, sizeof(vis_magic));
		memset(vis_col, false, sizeof(vis_col));
		memset(vis_row, false, sizeof(vis_row));

		int sta = random(9) + 1;
		cnt = 0;
		vis_row[0][sta] = vis_col[0][sta] = vis_magic[belonging(0, 0)][sta] = true;
		aaa[0] = sta + '0';

		value = value_t;
		dfs1(1);


	}
	void work2() {
		cnt = 0;
		while (scanf("%c", &ch) > 0)
		{
			if (ch < '0' || ch > '9')
				continue;
			x[tot++] = ch - '0';
			if (tot == 81) {
				rep(i, 0, 80)
					if (x[i] > 0)
						modifyElement(i, x[i]);

				dfs2(1);
				tot = 0;
				hasAnswer = false;
				memset(a, 0, sizeof(a));
			}
		}
	}

	bool check(int a[M]) {//ÅÐ¶ÏÖÕÅÌÊÇ²»ÊÇÒ»¸öÊý¶À
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
	bool find() {//ÅÐ¶ÏÖÕÅÌÊÇ²»ÊÇÒ»¸öÊý¶À
		return true;
		rep(i, 1, 9)
			if (square[i] < 2)
				return false;
		return true;
	}
	void work3(int num_0_t, int id_t, double p_t) {
		freopen("Ans.txt", "w", stdout);
		memset(isEmpty, true, sizeof(isEmpty));
		id = id_t;
		p = p_t;
		num_0 = num_0_t;
		while (true) {
			memset(game, 0, sizeof(game));
			memset(square, 0, sizeof(square));
			dfs3(0, 0);
			if (find()) {
				rep(i, 0, 80) {
					if (game[i]) {
						game[i] -= '0';
						isEmpty[i] = false;
					}
					cout << (ans_1[id][i]-'0') << " ";
					if (((i + 1) % 9) == 0)
						cout << endl;
				}
				return;
			}
		}
	}

	double getRandData(int min, int max)
	{
		double m1 = (double)(rand() % 101) / 101;                        // 计算 0，1之间的随机小数,得到的值域近似为(0,1)
		min++;                                                                             //将 区间变为(min+1,max),
		double m2 = (double)((rand() % (max - min + 1)) + min);    //计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
		m2 = m2 - 1;                                                                        //令值域为[min,max-1]
		return m1 + m2;                                                                //返回值域为(min,max),为所求随机浮点数
	}

	void dfs3(int k, int tot) {
		if (k > 80)
			return;
		int num = 1e9;
		int x;
		double t;
		//x = random(num) + 1;
		//t = 1.0 * x / num;
		t = getRandData(0, 1);
		if ((tot == num_0 || t >= p) && (80 - k + 1 >= num_0 - tot + 1))
		{
			game[k] = ans_1[id][k];

			dfs3(k + 1, tot);

		}
		else {
			square[belonging(k / 9, k % 9)]++;
			dfs3(k + 1, tot + 1);
		}
	}

	public slots:
	void update();
};