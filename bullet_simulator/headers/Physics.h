#pragma once

//����� ��� �������� ������������� �������
class bullet_create
{
public:
	double c_x = 100; //��������� � ��������
	double c_y = 700;
	double v_x = 200;
	double v_y = -200;

	#ifdef ENABLE_OPENCV
	Point cor;//���������� ����
	Point mg;//���������� ����� ������� ���� �������
	Point resistanse;//���������� ����� ������� ���� �������������	
	Scalar color_main = black; //����
	Scalar color_trace = gray; //���� �����
	#endif

	//���������� ��������������
	bool life = true; //������� ���� �� ������ �����
	double mass = 1;//����� �� ���������
	double radius = 0.02;//������ �� ���������
	double drag_coefficient = 0.295;

	void SpeedDegree(double v, double a)//������� �������� ��� ����� � ��������
	{
		v_x = v * cos(a*3.141592 / 180);
		v_y = -v * sin(a*3.141592 / 180);
	}
	bullet_create() 
	{
		SpeedDegree(my_rangint_gen(20, 300), my_rangint_gen(10,80));
		mass = my_rangint_gen(0, 20) / 100.0;
		#ifdef ENABLE_OPENCV
		color_trace = random_color();
		#endif
	}
};

//���������� ������� �� ���������
double resistance_force(bullet_create *pointer)
{
	bullet_create &bull = *pointer;
	return  bull.drag_coefficient * 1.2041 * (pow(bull.v_x, 2) + pow(bull.v_y, 2)) * 3.1415 * pow(bull.radius, 2) / 2;
};

//�������� ������� ����������� �������� �������
void PHYSICS(bullet_create *pointer, double dt, int N)
{
	for (int n = 0; n < N; n++)
	{
		bullet_create& bull = *(pointer + n);
		if (bull.life == true)
		{
			double F_resistance = resistance_force(&bull);


			double F_x = -F_resistance * cos(atan(bull.v_y / bull.v_x));
			double F_y = -F_resistance * sin(atan(bull.v_y / bull.v_x)) + bull.mass * 9.81;;

			double a_x = F_x / bull.mass;
			double a_y = F_y / bull.mass;

			bull.v_x += a_x * dt;
			bull.v_y += a_y * dt;

			bull.c_x += bull.v_x * dt;
			bull.c_y += bull.v_y * dt;

			#ifdef ENABLE_OPENCV
			bull.cor.x = bull.c_x;
			bull.cor.y = bull.c_y;

			// ��� ��������� �������� ���
			double zoom = 150;
			bull.resistanse.x = bull.cor.x + F_x * zoom - 1;
			bull.resistanse.y = bull.cor.y + (F_y - bull.mass * 9.81) * zoom;

			bull.mg.x = bull.cor.x;
			bull.mg.y = bull.cor.y + zoom * bull.mass * 9.81;
			#endif	
		}
	}
}

//������� ������� "�����" ���� ��������
bool LIFES_CHECK(double T, bullet_create *pointer, int N)
{
	
	bool lifes = false;
	for (int n = 0; n < N; n++)
	{
		bullet_create& bullet = *(pointer+n);
	
		if (bullet.life && !(int(bullet.c_y) < 700) && (int(bullet.c_x) >= 0))
		{
			bullet.life = false;
			std::cout << "Distance[" << n << "]= " << bullet.c_x - 100 << "\tt= " << T << std::endl;//����� � ������� ���������� ����� ��������
		}

		if (bullet.life == true) { lifes = true; }
	}
	return lifes;
};

//������� ���������� "������� - ����������"
void COUT_WINNER(bullet_create* pointer, int N)
{
	int k = 0;
	double d_max = 0;
	for (int n = 0; n < N; n++)
	{
		bullet_create& bullet = *(pointer + n);
		if (bullet.c_x > d_max) { k = n; d_max = bullet.c_x; }
	}
	std::cout << std::endl << "Win= [" << k << "] Disctance= " << d_max - 100 << std::endl;
};