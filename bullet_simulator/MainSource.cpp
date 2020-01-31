/*Программа для симуляции и визуализации полёта снаряда, 
и расчёта максимальной дистанции полёта, с учётом сопротивления воздуха.
Маракулин Андрей 2018*/

#define ENABLE_OPENCV // Закомментируйте чтобы отключить привязку к OpenCV
#ifdef ENABLE_OPENCV
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#endif

#include <time.h>
#include <iostream>
#include <windows.h>
#include <random>

#include "headers/Colors.h"// Определение цветов
#include "headers/Physics.h"//набор функций отвечающий за расчёт физики
#include "headers/Display.h"//набор функций отвечающий за графику


double simulation_time = 0;
const double simulation_delay = 0.01857;// Влияет на точность и скорость симуляции. Меньше - точнее

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
	bullet_create bullet[N];//Создание N случайных снарядов

	//Определение характеристик 0-ого снаряда как пули автомата Калашникова
	bullet[0].SpeedDegree(800, 45); //[м/с] [градусы]
	bullet[0].radius = 0.00762; // [м]
	bullet[0].mass = 0.012;// [кг]
	bullet[0].drag_coefficient = 0.295; // безразмерная

	do{
		PHYSICS(bullet, simulation_delay, N);//ЗАПУСК ФИЗИЧЕСКОГО ДВИЖКА
		simulation_time += simulation_delay;

		#ifdef ENABLE_OPENCV
		window.draw_frame(bullet, simulation_time, N);
		window.show("Cannon");
		window.clear_draw();
		if (waitKey(1) == 27) return 0;
		#endif
	}
	while (LIFES_CHECK(simulation_time, bullet, N));

	COUT_WINNER(bullet, N);//Нахождение снаряда с лучше дистанцией
	system("pause");
}