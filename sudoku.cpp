//  sudoku
//  Created by ohazyi on 2017/9/19.

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
using namespace std;

const int N = 11;
const int M = 83;
int tot, x[M], a[M][N], a_backup[M][M][N], aaa[M];
bool hasAnswer=false, debug=false, debug_time=false, modifyElement(int pos, int r), deleteElement(int pos, int r);
FILE *out;

int value, cnt, n, m, len = 0;//value代表要输出的矩阵的个数
char ch;
bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];

inline bool find(int x, int y, int z) { return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]); }

string getTime()//得到当前时间的ms的时间
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}
void printTime(string str) {//得到当前时间
	cout << str << ": ";
	string time;
	time = getTime();
	cout << time;
	ftime(&tb);
	printf(".%03d\n", tb.millitm);
}
bool deleteElement(int pos, int r) {
	int i;
	if (a[pos][r] == 1)//代表之前已经不让填了
		return true;
	a[pos][r] = 1;
	if (++a[pos][0] == 9)//代表这个格子没有值可以填了
		return false;
	if (a[pos][0] == 8)
	{
		for (i = 1; i <= 9; ++i) 
			if (a[pos][i] == 0)//找到是谁可以填
				break;
		if (!modifyElement(pos, i))
			return false;
	}
	return true;
}
bool modifyElement(int pos, int r) {
	int p = pos / 9;//行号
	int q = pos % 9;//列号
	int h;
	x[pos] = r;
	rep(i, 1, 9)
		a[pos][i] = 1;
	a[pos][0] = 8;//代表只有一个元素可以填
	a[pos][r] = 0;//那就是r
	rep(j, 0, 8) {//增加同行的其它格子的限制
		h = Position(p, j);
		if (h != pos && !deleteElement(h, r)) 
			return false;
	}
	rep(i, 0, 8) {//增加同列的其它格子的限制
		h = Position(i, q);
		if (h != pos && !deleteElement(h, r)) 
			return false;
	}
	rep(i, 0, 2)//增加同九宫格的其它格子的限制
	rep(j, 0, 2)
	{
		h = (3 * (p / 3) + i) * 9 + (3 * (q / 3) + j);
		if (h != pos && !deleteElement(h, r)) 
			return false;
	}
	return true;
}  
void out_file(int *s) {
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
void dfs(int k) {
	int mx = -1, mxi;
	rep(i, 0, 80) {
		if (a[i][0]<8 && a[i][0]>mx) {
			mx = a[i][0];
			mxi = i;
		}
	}
	if (mx == -1) {
		rep(i, 0, 80) {
			x[i] += '0';
		}
		out_file(x);
		hasAnswer = true;
		return;
	}
	memcpy(a_backup[k], a, sizeof(a));
	rep(i, 1, 9) {
		if (a[mxi][i] == 0) {
			if (modifyElement(mxi, i))
				dfs(k + 1);
			memcpy(a, a_backup[k], sizeof(a));
		}
		if (hasAnswer)
			return;
	}
}
void dfs2(int k) {
	if (hasAnswer) return ;
	int x, y;
	x = k / 9;
	y = k % 9;
	if (k > 80) {
		out_file(aaa);
		if (++cnt >= value) {
			hasAnswer = true;
			//exit(0);
		}
		return;
	}
	rep(i, 1, 9) {
		if (find(x, y, i)) {
			aaa[k] = i + '0';
			vis_row[x][i] = vis_col[y][i] = vis_magic[belonging(x, y)][i] = true;
			dfs2(k + 1);
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
void exit_invalid(string s) {
	cout << s << endl;
	exit(0);
}
int main(int argc, char *argv[]) {
	if (argc != 3)
		exit_invalid("Too many or too few arguments!");
	if (strlen(argv[1]) < 2)
		exit_invalid("Invalid arguments!");
	out = fopen("sudoku.txt", "w");	//freopen("sudoku.txt", "w", stdout);
	if (argv[1][1] == 'c')
	{
		value = 1;//        value = atoi(argv[2])
		if (!calc(argv[2])) {
			puts("Invalid Command -c Number");
			return 0;
		}
		if (value<1 || value>1000000) {
			puts("Invalid -c number");
			return 0;
		}

		memset(vis_magic, false, sizeof(vis_magic));
		memset(vis_col, false, sizeof(vis_col));
		memset(vis_row, false, sizeof(vis_row));
		cnt = 0;
		vis_row[0][1] = vis_col[0][1] = vis_magic[belonging(0, 0)][1] = true;
		aaa[0] = 1 + '0';
		if (debug_time) printTime("起始时间");
		//value = 1000000;
		dfs2(1);
		if (debug_time) printTime("结束时间");
	}
	else if (argv[1][1] == 's')	
	{
		
		freopen(argv[2], "r", stdin);//freopen("puzzlefile.txt", "r", stdin);

		if (debug_time) printTime("起始时间");
		while (scanf("%c", &ch) > 0)
		{
			if (ch < '0' || ch > '9')
				continue;
			x[tot++] = ch - '0';
			if (tot == 81) {
				rep(i, 0, 80)
					if (x[i] > 0)
						modifyElement(i, x[i]);

				dfs(1);
				tot = 0;
				hasAnswer = false;
				memset(a, 0, sizeof(a));
			}
		}
		if (debug_time) printTime("结束时间");
	}

	return 0;
}
