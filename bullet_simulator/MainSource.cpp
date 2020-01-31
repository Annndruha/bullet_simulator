/*��������� ��� ��������� � ������������ ����� �������, 
����������� �� �����, � ������ ������������� �������.
��������� ������ 2018*/


#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace cv;

#include "headers/Colors.h"//����� ������� ���������� �� �����
#include "headers/Physics.h"//����� ������� ���������� �� ������ ������
#include "headers/Display.h"//����� ������� ���������� �� �������

bool EnableAnimation = true;
const double SIMULATION_DELAY = 0.01857;// (��� ��������� ������� ��� ����� �������  0.01857) 0.05
double T = 0;
int SPACE = 1; //���������� SPACE-1 ������

const int N = 3;
bullet_create bullet[N];//�������� N��� ���������� ���

display window;
#include "headers/AssistFunction.h"
int main()
{
	String window1 = { "Cannon" };
	if (EnableAnimation) {
		window.start(window1);
		DRAW_BACKGROUND(&window);
	}
	else { cout << "If you want animation, change EnableAnimation to true in line 23\n"; }

	SET_BULLET_PARAMETRS();

	int frame = 0;
	bool l_c = LIFES_CHECK(T);
	while (l_c)
	{
		l_c = LIFES_CHECK(T);
		for (int n = 0; n < N; n++)
		{
			PHYSICS(&bullet[n], SIMULATION_DELAY);//������ ����������� ������ ���������� ���������� �������� � ���������� 
			if ((frame % SPACE == 0) && (EnableAnimation))
			{
				DRAW_FORSES(&window, &bullet[n]); //��������� ��� ����������� �� ����
				DRAW_TRACE(&window, &bullet[n]);//��������� �����
				DRAW_BULLET(&window, &bullet[n], n);//��������� �������� � �� �������
				DRAW_TIME(&window, T);//��������� �������� �������
			}
		}
		T += SIMULATION_DELAY;
		
		if ((frame % SPACE == 0) && (EnableAnimation)) //����������� ��������� ������
		{
			MERGE(&window.out, &window.background, 3);//���������������� ��������� ���� c ������ �������
			MERGE(&window.out, &window.trace, 3);
			MERGE(&window.out, &window.draw, 3);
			window.show(window1); //����� ���������� �����������
			if (waitKey(1) == 27) return 0;//���������� ����� ���������� ������� == ����� �������
		}
		else if (EnableAnimation)
		{
			window.draw = NULL;
		}
		frame++;
	}
	if (EnableAnimation) { if (waitKey(1) == 27) return 0; }

	COUT_WINNER();//���������� ���������� � ���������
	system("pause");
}