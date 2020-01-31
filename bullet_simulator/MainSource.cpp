/*��������� ��� ��������� � ������������ ����� �������, 
����������� �� �����, � ������ ������������� �������.
��������� ������ 2018*/

//#define ENABLE_OPENCV // ��������������� ����� ��������� �������� � OpenCV

#ifdef ENABLE_OPENCV
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#endif

#include <math.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/Colors.h"// ����������� ������
#include "headers/Physics.h"//����� ������� ���������� �� ������ ������
#include "headers/Display.h"//����� ������� ���������� �� �������


double simulation_time = 0;
const double simulation_delay = 0.01857;// (��� ��������� ������� ��� ����� �������  0.01857) 0.05


const int N = 3;
bullet_create bullet[N];//�������� N��� ���������� ���


#include "headers/AssistFunction.h"
int main()
{
	#ifdef ENABLE_OPENCV
	display window;
	window.start("Cannon");
	window.draw_scalegrid();
	window.enable_trace = false;
	window.enable_forces = false;
	#endif

	SET_BULLET_PARAMETRS();
	do
	{
		for (int n = 0; n < N; n++)
		{
			PHYSICS(&bullet[n], simulation_delay);//������ ����������� ������ ���������� ���������� �������� � ����������
			#ifdef ENABLE_OPENCV
			window.draw_frame(&bullet[n], simulation_time, n);
			#endif
		}
		simulation_time += simulation_delay;
		
		#ifdef ENABLE_OPENCV
		window.show("Cannon"); //����� ���������� �����������
		window.clear_draw();
		if (waitKey(1) == 27) return 0; //���������� ����� ���������� ������� == ����� �������
		#endif
	}
	while (LIFES_CHECK(simulation_time));

	COUT_WINNER();//���������� ���������� � ���������
	system("pause");
}