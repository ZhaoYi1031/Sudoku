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

typedef long long ll;
#define rep(i,a,b) for (int i = (a); i <= (b); ++i)
#define rep2(i,a,b) for (int i = (a); i >= (b); --i)
int belonging(int x, int y) { return x / 3 * 3 + y / 3 + 1; }
int Position(int x, int y) { return 9 * x + y; };
using namespace std;

const int N = 11;
const int M = 82;
int tot, x[M], a[M][N], a_backup[M][M][N], aaa[M];
bool hasAnswer, modifyElement(int pos, int r), modifyElement(int pos, int r);
FILE *out;

string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}
void printTime() {
	string time;
	time = getTime();
	cout << time;


	ftime(&tb);
	printf(".%03d\n", tb.millitm);
}
bool deleteElement(int pos, int r) {
	//    cout << "delete" << pos << " " << r << endl;
	int i;
	if (a[pos][r] == 1)
		return true;
	a[pos][r] = 1;
	if (++a[pos][0] == 9)
		return false;
	if (a[pos][0] == 8)
	{
		for (i = 1; i <= 9; ++i) {
			if (a[pos][i] == 0)
				break;
		}
		if (!modifyElement(pos, i))
			return false;
	}
	return true;
}
bool modifyElement(int pos, int r) {
	//    cout << "modify" << pos << " " << r << endl;
	//    if (a[pos][0]==9||a[pos][r] == 1)
	//        return false;
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
		if (h != pos && !deleteElement(h, r)) {
			return false;
		}
	}
	rep(i, 0, 8) {
		h = Position(i, q);
		if (h != pos && !deleteElement(h, r)) {
			return false;
		}
	}

	rep(i, 0, 2)
		rep(j, 0, 2)
	{
		h = (3 * (p / 3) + i) * 9 + (3 * (q / 3) + j);
		if (h != pos && !deleteElement(h, r)) {
			return false;
		}
	}

	return true;
}
void dfs(int k) {
	int mx = -1, mxi;
	rep(i, 0, 80) {
		if (a[i][0]<8 && a[i][0]>mx) {
			mx = a[i][0];
			mxi = i;
		}
	}
	char ans[300];
	int len = 0;
	if (mx == -1) {
		rep(i, 0, 80) {
			//            cout << x[i];
			ans[len++] = x[i] + '0';
			ans[len++] = (((i + 1) % 9) == 0) ? '\n' : ' ';
			//            putchar(x[i]+'0');
			//            printf("%d", x[i]);
		}
		ans[len] = '\0';
		fputs(ans, out);
		//        printf("\n");
		hasAnswer = true;
		return;
	}

	memcpy(a_backup[k], a, sizeof(a));
	rep(i, 1, 9) {
		if (a[mxi][i] == 0) {

			if (modifyElement(mxi, i))
				dfs(k + 1);
			memcpy(a, a_backup[k], sizeof(a));
			//            a[mxi][0]++;
			//            a[mxi][i] = 1;
		}
		if (hasAnswer)
			return;
	}
}
//const int N = 11;
int value, cnt, ans, n, m;//value代表要输出的矩阵的个数
char aa[N][N];
char str[N][N];
bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];

inline bool find(int x, int y, int z) {
	return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]);
}

void dfs2(int k) {
	int x, y;
	x = k / 9;
	y = k % 9;

	if (k > 80) {

		int siz = 0;
		string out_s = "";
		rep(i, 0, 80) {

			//cout << aaa[i] << " ";
			//if (((i + 1) % 9) == 0)
			//cout << endl;
			out_s += aaa[i];
			out_s += (((i + 1) % 9) == 0) ? "\n" : " ";
		}

		out_s += "\0";
		//fputs(out_s.data(), out);
		fprintf(out, "%s\n\n", out_s.data());

		//fputs(" ", out);
		//fprintf(out, "\n");
		if (++cnt >= value) {
			printTime();
			exit(0);
		}
		//            return ;
		return;
	}
	rep(i, 1, 9) {
		if (find(x, y, i)) {
			aaa[k] = i + '0';
			vis_row[x][i] = vis_col[y][i] = vis_magic[belonging(x, y)][i] = true;
			//printf("%d %d %d %d\n", k, x, y, i);
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


	//freopen("sudoku.txt", "w", stdout);
	if (argc != 3)
		exit_invalid("Too many or too few arguments!");
	if (strlen(argv[1]) < 2)
		exit_invalid("Invalid arguments!");
	out = fopen("sudoku.txt", "w");
	if (argv[1][1] == 'c')
	{
		printTime();
		value = 1;
		//        value = atoi(argv[2])
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
		dfs2(1);
	}
	else if (argv[1][1] == 's')
	{

		freopen(argv[2], "r", stdin);
		//        freopen("puzzlefile.txt", "r", stdin);
		//    printTime();

		char ch;
		while (scanf("%c", &ch) > 0 && ch != 'e')
		{
			//            if (ch=='.')
			//                ch = '0';
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

		//    printTime();
	}

	/*
	FILE *in;
	in = fopen("worldcitiespop.txt", "r");
	freopen("in.txt", "r", stdin);
	string str;
	while (fgets(str, 100010, in) != NULL){
	while ((scanf("%d", &x))!=EOF){
	cout << x << endl;
	}*/

	return 0;
}
