/*��������� ��� ��������� � ������������ ����� �������, 
� ������� ������������ ��������� �����, � ������ ������������� �������.
��������� ������ 2018*/

#define ENABLE_OPENCV // ��������������� ����� ��������� �������� � OpenCV
#ifdef ENABLE_OPENCV
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#endif

#include <time.h>
#include <iostream>
#include <windows.h>
#include <random>

#include "headers/Colors.h"// ����������� ������
#include "headers/Physics.h"//����� ������� ���������� �� ������ ������
#include "headers/Display.h"//����� ������� ���������� �� �������


double simulation_time = 0;
const double simulation_delay = 0.01857;// ������ �� �������� � �������� ���������. ������ - ������

int main()
{
	#ifdef ENABLE_OPENCV
	display window;
	window.start("Cannon");
	window.draw_scalegrid();
	window.enable_trace = true;
	window.enable_forces = true;
	window.enable_bullet_number = true;
	#endif


	const int N = 4;
	bullet_create bullet[N];//�������� N ��������� ��������

	//����������� ������������� 0-��� ������� ��� ���� �������� �����������
	bullet[0].SpeedDegree(800, 45); //[�/�] [�������]
	bullet[0].radius = 0.00762; // [�]
	bullet[0].mass = 0.012;// [��]
	bullet[0].drag_coefficient = 0.295; // ������������

	do{
		PHYSICS(bullet, simulation_delay, N);//������ ����������� ������
		simulation_time += simulation_delay;

		#ifdef ENABLE_OPENCV
		window.draw_frame(bullet, simulation_time, N);
		window.show("Cannon");
		window.clear_draw();
		if (waitKey(1) == 27) return 0;
		#endif
	}
	while (LIFES_CHECK(simulation_time, bullet, N));

	COUT_WINNER(bullet, N);//���������� ������� � ����� ����������
	system("pause");
}