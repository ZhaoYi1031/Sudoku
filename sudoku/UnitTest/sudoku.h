#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sys/timeb.h>
#include <time.h>
struct timeb tb;
#define rep(i,a,b) for (int i = (a); i <= (b); ++i)
inline int belonging(int x, int y) { return x / 3 * 3 + y / 3 + 1; }
inline int Position(int x, int y) { return 9 * x + y; }
const int N = 11;
const int M = 82;
int ans_2[10010][M], ans_1[10010][M];
using namespace std;
class Sudoku {
public:
	
	int tot, x[M], a[M][N], a_backup[M][M][N], aaa[M];
	bool hasAnswer = false, debug = true;
	

	int value, cnt, n, m, len = 0;//value代表要输出的矩阵的个数
	char ch, aa[N][N];
	bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
	inline bool find(int x, int y, int z) { return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]); }
	FILE *out;
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
		x[pos] = r;
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
			rep(i, 0, 80) {
				x[i] += '0';
			}
			memcpy(ans_2[cnt], x, sizeof(x));
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
		cnt = 0;
		vis_row[0][1] = vis_col[0][1] = vis_magic[belonging(0, 0)][1] = true;
		aaa[0] = 1 + '0';

		value = value_t;
		dfs1(1);
	}

	void out_file(int *s) {
		//FILE *out = fopen(str, "w");

		char ans[300];
		int len = 0;
		rep(i, 0, 80) {
			ans[len++] = s[i];
			ans[len++] = (((i + 1) % 9) == 0) ? '\n' : ' ';
			if (debug) {
				printf("%c ", s[i]);
				if ((i + 1) % 9 == 0)
					printf("\n");
			}
		}
		if (debug)
			printf("\n");

		ans[len++] = '\n';
		ans[len] = '\0';//ans[len] = '\0';//	fputs(ans, out); //	fputs("\n", out);
		fwrite(ans, 1, strlen(ans), out);//ans[len] = '\0'; //fprintf(out, "%s\n", ans);
	}

	void work2() {
		
		tot = 0;
		hasAnswer = false;
		memset(a, 0, sizeof(a));
		cnt = 0;
		rep(i, 0, 80)
			if (x[i] > 0)
				modifyElement(i, x[i]);

		dfs2(1);
	}
};