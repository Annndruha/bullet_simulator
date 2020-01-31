/*Программа для симуляции и визуализации полёта снаряда, 
выпущенного из пушки, с учётом сопротивления воздуха.
Маракулин Андрей 2018*/

//#define ENABLE_OPENCV // Закомментируйте чтобы отключить привязку к OpenCV

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

#include "headers/Colors.h"// Определение цветов
#include "headers/Physics.h"//набор функций отвечающий за расчёт физики
#include "headers/Display.h"//набор функций отвечающий за графику


double simulation_time = 0;
const double simulation_delay = 0.01857;// (для реального времени без лагов ставить  0.01857) 0.05


const int N = 3;
bullet_create bullet[N];//Создание Nого количества тел


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
			PHYSICS(&bullet[n], simulation_delay);//ЗАПУСК ФИЗИЧЕСКОГО ДВИЖКА Выполнение физической итерации с интервалом
			#ifdef ENABLE_OPENCV
			window.draw_frame(&bullet[n], simulation_time, n);
			#endif
		}
		simulation_time += simulation_delay;
		
		#ifdef ENABLE_OPENCV
		window.show("Cannon"); //показ полученого изображения
		window.clear_draw();
		if (waitKey(1) == 27) return 0; //Промежуток между ожиданиями клавиши == между кадрами
		#endif
	}
	while (LIFES_CHECK(simulation_time));

	COUT_WINNER();//Нахождение победителя и дистанции
	system("pause");
}