#pragma once

//����� ��� �������� ������������� �������
class bullet_create
{
public:
	//���������
	double c_x = 100;
	double c_y = 700;
	double v_x = 200;
	double v_y = 200;

	Point cor;//���������� ����
	Point mg;//���������� ����� ������� ���� �������
	Point resistanse;//���������� ����� ������� ���� �������������

	//����������� ��������������
	Scalar color_main = black;
	Scalar color_trace = gray;
	double radius_draw = 15;

	//���������� ��������������
	bool life = true; //������� ���� �� ������ �����
	double mass = 1;//����� �� ���������
	double radius = 0.00545;//������ �� ���������
	bool formula = true; //��������� ������� ������� ������������� -(����� true, a ������ false)

	void VelocityDegree(double v, double a)//������� �������� ��� ����� � ��������
	{
		v_x = v * cos(a*3.141592/180);
		v_y = -v * sin(a*3.141592 / 180);
	}

	bullet_create() // ����������� �� ���������
	{
		VelocityDegree(200, 45);
	}
	bullet_create(double velocity, double degree, double m=1, double r=0.01, Scalar ct = gray) // ����������� � �����������
	{
		VelocityDegree(velocity, degree);
		mass = m;
		radius = r;
		color_trace = ct;
	}
};

//������� ������
double force_resistance_stocks(bullet_create *pointer)
{
	bullet_create &bull = *pointer;
	return 6 * 3.1415 * 0.0000186 * bull.radius * sqrt(pow(bull.v_x, 2) + pow(bull.v_y, 2));
};

//���������� ������� �� ���������
double force_resistance_drag(bullet_create *pointer)
{
	bullet_create &bull = *pointer;
	return  0.3 * 1.2041 * (pow(bull.v_x, 2) + pow(bull.v_y, 2)) * 3.1415 * pow(bull.radius, 2) / 2;
};

//�������� ������� ����������� �������� �������
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

		// ��� ��������� �������� ���
		double zoom = 350;
		bull.resistanse.x = bull.cor.x + F_x * zoom-1;
		bull.resistanse.y = bull.cor.y + (F_y - bull.mass*9.81) * zoom;

		bull.mg.x = bull.cor.x;
		bull.mg.y = bull.cor.y + zoom * bull.mass*9.81;
	}
}