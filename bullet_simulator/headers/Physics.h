#pragma once

//Класс для описания характеристик снаряда
class bullet_create
{
public:
	//Положение
	double c_x = 100;
	double c_y = 700;
	double v_x = 200;
	double v_y = 200;

	Point cor;//Координата тела
	Point mg;//координата конца стрелки силы тяжести
	Point resistanse;//координата конца стрелки силы сопротивления

	//Графические характеристики
	Scalar color_main = black;
	Scalar color_trace = gray;
	double radius_draw = 15;

	//Физические характеристики
	bool life = true; //активен если не достиг земли
	double mass = 1;//масса по умолчанию
	double radius = 0.00545;//радиус по умолчанию
	bool formula = true; //установка формулы расчета сопротивления -(общая true, a стокса false)

	void VelocityDegree(double v, double a)//перевод скорости под углом в проекции
	{
		v_x = v * cos(a*3.141592/180);
		v_y = -v * sin(a*3.141592 / 180);
	}

	bullet_create() // Конструктор по умолчанию
	{
		VelocityDegree(200, 45);
	}
	bullet_create(double velocity, double degree, double m=1, double r=0.01, Scalar ct = gray) // Конструктор с параметрами
	{
		VelocityDegree(velocity, degree);
		mass = m;
		radius = r;
		color_trace = ct;
	}
};

//Формула Стокса
double force_resistance_stocks(bullet_create *pointer)
{
	bullet_create &bull = *pointer;
	return 6 * 3.1415 * 0.0000186 * bull.radius * sqrt(pow(bull.v_x, 2) + pow(bull.v_y, 2));
};

//Обобщенная формула из википедии
double force_resistance_drag(bullet_create *pointer)
{
	bullet_create &bull = *pointer;
	return  0.3 * 1.2041 * (pow(bull.v_x, 2) + pow(bull.v_y, 2)) * 3.1415 * pow(bull.radius, 2) / 2;
};

//Основная функция описывающая движение снаряда
void PHYSICS(bullet_create* pointer, double dt)
{
	bullet_create &bull = *pointer;
	if (bull.life == true)
	{
		double F_resistance = 0;
		if (bull.formula == true) 
		{
			F_resistance = force_resistance_drag(&bull);
		}
		else
		{
			F_resistance = force_resistance_stocks(&bull);
		}

		double F_x = -F_resistance * cos(atan(bull.v_y / bull.v_x));
		double F_y = -F_resistance * sin(atan(bull.v_y / bull.v_x)) + bull.mass*9.81;;

		double a_x = F_x / bull.mass;
		double a_y = F_y / bull.mass;

		bull.v_x += a_x * dt;
		bull.v_y += a_y * dt;

		bull.c_x += bull.v_x*dt;
		bull.c_y += bull.v_y*dt;


		bull.cor.x = bull.c_x;
		bull.cor.y = bull.c_y;

		// Для рисования векторов сил
		double zoom = 350;
		bull.resistanse.x = bull.cor.x + F_x * zoom-1;
		bull.resistanse.y = bull.cor.y + (F_y - bull.mass*9.81) * zoom;

		bull.mg.x = bull.cor.x;
		bull.mg.y = bull.cor.y + zoom * bull.mass*9.81;
	}
}