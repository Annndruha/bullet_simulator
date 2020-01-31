/*Программа для симуляции и визуализации полёта снаряда, 
выпущенного из пушки, с учётом сопротивления воздуха.
Маракулин Андрей 2018*/


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

#include "headers/Colors.h"//набор функций отвечающий за цвета
#include "headers/Physics.h"//набор функций отвечающий за расчёт физики
#include "headers/Display.h"//набор функций отвечающий за графику

bool EnableAnimation = true;
const double SIMULATION_DELAY = 0.01857;// (для реального времени без лагов ставить  0.01857) 0.05
double T = 0;
int SPACE = 1; //Пропускать SPACE-1 кадров

const int N = 3;
bullet_create bullet[N];//Создание Nого количества тел

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
			PHYSICS(&bullet[n], SIMULATION_DELAY);//ЗАПУСК ФИЗИЧЕСКОГО ДВИЖКА Выполнение физической итерации с интервалом 
			if ((frame % SPACE == 0) && (EnableAnimation))
			{
				DRAW_FORSES(&window, &bullet[n]); //Отрисовка сил действующих на тела
				DRAW_TRACE(&window, &bullet[n]);//Отрисовка следа
				DRAW_BULLET(&window, &bullet[n], n);//Отрисовка снарядов и их номеров
				DRAW_TIME(&window, T);//Отрисовка текущего времени
			}
		}
		T += SIMULATION_DELAY;
		
		if ((frame % SPACE == 0) && (EnableAnimation)) //Пропускание некоторых кадров
		{
			MERGE(&window.out, &window.background, 3);//Последовательное наложение слоёв c числом каналов
			MERGE(&window.out, &window.trace, 3);
			MERGE(&window.out, &window.draw, 3);
			window.show(window1); //показ полученого изображения
			if (waitKey(1) == 27) return 0;//Промежуток между ожиданиями клавиши == между кадрами
		}
		else if (EnableAnimation)
		{
			window.draw = NULL;
		}
		frame++;
	}
	if (EnableAnimation) { if (waitKey(1) == 27) return 0; }

	COUT_WINNER();//Нахождение победителя и дистанции
	system("pause");
}