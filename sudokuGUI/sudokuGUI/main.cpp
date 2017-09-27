#include "sudokuGUI.h"
#include "sudoku.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <qstring.h>
#include <iostream>
#include <time.h>
#include <QObject>
#include <windows.h>
#include <string>
#include <Qpainter>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTableView>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFontDialog>
#include <QFrame>
#include <QVBoxLayout>
#include <QStackedWidget>


//#define rep (i,a,b) for (int i = (a); i <= (b); ++i)
#define random(x) (rand()%x)
const int width = 50, height = 50, NNN=9;
using namespace std;
int A[M];


void Sudoku::update() {
	int i, j, num;
	bool zy;
	rep(_, 0, 80) {
		i = _ / 9;
		j = _ % 9;
		if (isEmpty[_]) {
			zy = false;
			num = lineEdit[i][j].displayText().toInt(&zy, 10);
			if (zy)
				A[_] = num;
			else {
				MessageBox(NULL, TEXT("Fail"), TEXT("Result"), MB_OK);
				return;
			}
		}
		A[_] += '0';
	}
	if (check(A))
		MessageBox(NULL, TEXT("Success"), TEXT("Result"), MB_OK);
	else
		MessageBox(NULL, TEXT("Fail"), TEXT("Result"), MB_OK);
}
int main(int argc, char *argv[])
{
	
	srand((int)time(0));
	/*qapplication a(argc, argv);
	sudukogui w;
	w.show();
	return a.exec();*/
	QApplication app(argc, argv);

	QMainWindow w;
	w.setWindowTitle("sudoku");
	w.setFixedSize(width*NNN + 10+ 100, height*NNN + 10 + height*2);
	w.show();



	
	Sudoku s;

	s.work1(100);

	int id = random(100) + 1;
	
	int first = random(31) + 30;

	//first = 1;

	s.work3(first, id, 1.0*first / 81.0);
	memcpy(A, s.game, sizeof(A));
	
	QLabel label[NNN][NNN];
	//QLineEdit lineEdit[NNN][NNN];
	int i, j;
	rep(_, 0, 80) {
		i = _ / 9;
		j = _ % 9;
		if (A[_] == 0)
		{
			s.lineEdit[i][j].setParent(&w);
			s.lineEdit[i][j].setAlignment(Qt::AlignCenter);
			s.lineEdit[i][j].setGeometry(50 + j*width, 45 + i*height, width, height);

			if ((i == 2 && j == 2) || (i == 5 && j == 5) || (i == 2 && j == 5) || (i == 5 && j == 2))
				s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-right:2px solid #ff4d4d; border-bottom:2px solid #ff4d4d;");
			else if ((i == 2 && j == 3) || (i == 5 && j == 3) || (i == 2 && j == 6) || (i == 5 && j == 6))
				s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border:2px solid gray; border-left:2px solid #ff4d4d; border-bottom:2px solid #ff4d4d;");
			else if ((i == 3 && j == 3) || (i == 6 && j == 6) || (i == 3 && j == 6) || (i == 6 && j == 3))
				s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-left:2px solid #ff4d4d; border-top:2px solid #ff4d4d;");
			else if ((i == 3 && j == 2) || (i == 3 && j == 5) || (i == 6 && j == 2) || (i == 6 && j == 5))
				s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-right:2px solid #ff4d4d; border-top:2px solid #ff4d4d;");

			else if (i == 2 || i == 5)
					s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-bottom:2px solid #ff4d4d;");
			else
				if (j == 2 || j == 5)
					s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-right:2px solid #ff4d4d;");
			else if (i == 3 || i == 6)
					s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-top:2px solid #ff4d4d;");
			else if (j == 3 || j == 6)
					s.lineEdit[i][j].setStyleSheet("border:2px solid gray; border-left:2px solid #ff4d4d;");
			else
				s.lineEdit[i][j].setStyleSheet("border:2px solid gray;");
			

			QPalette pe;
			pe.setColor(QPalette::Text, Qt::black);
			s.lineEdit[i][j].setPalette(pe);

			s.lineEdit[i][j].setFont(QFont("Times New Roman", 17, QFont::Bold));

			//lineEdit[i][j].setStyleSheet("border:2px solid yellow;");


			s.lineEdit[i][j].show();
		}
		else {


			label[i][j].setAutoFillBackground(true);//设置背景充满，为设置背景颜色的必要条件
			QPalette pe;

			pe.setColor(QPalette::WindowText, Qt::blue);//设置字体颜色
			/*pe.setColor(QPalette::ButtonText, Qt::red);
			pe.setColor(QPalette::Background, Qt::black);*/


			label[i][j].setParent(&w);
			label[i][j].setText(QString::number(A[_], 10));
			QFont ft2("Times New Roman", 14);//Times New Roman
			label[i][j].setFont(ft2);
			label[i][j].setAlignment(Qt::AlignCenter);
			label[i][j].setGeometry(50 + j*width, 45 + i*height, width, height);

			label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray;");

			if (i == 2 || i == 5)
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-bottom:2px solid #ff4d4d;");
			if (j == 2 || j == 5)
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-right:2px solid #ff4d4d;");
			if ((i == 2 && j == 2) || (i == 5 && j == 5) || (i == 2 && j == 5) || (i == 5 && j == 2))
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-right:2px solid #ff4d4d; border-bottom:2px solid #ff4d4d;");
			if (i == 3 || i == 6)
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-top:2px solid #ff4d4d;");
			if (j == 3 || j == 6)
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-left:2px solid #ff4d4d;");
			if ((i == 3 && j == 3) || (i == 6 && j == 6) || (i == 3 && j == 6) || (i == 6 && j == 3))
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-left:2px solid #ff4d4d; border-top:2px solid #ff4d4d;");
			if ((i == 3 && j == 2) || (i == 3 && j == 5) || (i == 6 && j == 2)||(i==6&&j==5))
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-right:2px solid #ff4d4d; border-top:2px solid #ff4d4d;");
			if ((i == 2 && j == 3) || (i == 5 && j == 3) || (i == 2 && j == 6) || (i == 5 && j == 6))
				label[i][j].setStyleSheet("background-color: #A2B5CD; border:2px solid gray; border-left:2px solid #ff4d4d; border-bottom:2px solid #ff4d4d;");


			label[i][j].setPalette(pe);

			label[i][j].show();
			
			
		}
	}




	QPainter painter(&w);
	
	QPen ss;

	ss.setWidth(30);
	ss.setColor(Qt::red);
	painter.setPen(ss);
	
	painter.drawLine(0, 110, 20, 200);
	

	//QLabel result("result", &w);
	//result.setGeometry(5 + 2 * width, 5 + NNN*height, width, height / 2);
	//result.show();

	static QFont ft1("Times New Roman", 13);
	QPushButton btn("Test", &w);
	btn.setGeometry(5 * width, 5 + 10 * height + 7, width, 30);
	btn.setFont(ft1);
	btn.setMinimumSize(45, 20);
	btn.setStyleSheet("background-color: #9999ff");
	btn.show();

	QObject::connect(&btn, SIGNAL(clicked()), &s, SLOT(update()));
	return app.exec();
}
