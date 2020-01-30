#pragma once

//������������ ��������� ���������� ��������
void SET_BULLET_PARAMETRS()
{

	bullet[0].VelocityDegree(200, 45); // �������� ���������� ���� � �������� ��� 0-�� ����
	bullet[0].color_trace = red;//�������� ����� �����
	bullet[0].formula = true;//������� �������������
	bullet[0].radius = 0.01;
	bullet[0].mass = 0.05;
	
	bullet[1].VelocityDegree(200, 38);
	bullet[1].color_trace = magneta;
	bullet[1].formula = true;
	bullet[1].radius = 0.00762;
	bullet[1].mass = 0.017;
	
	bullet[2].VelocityDegree(500, 45);
	bullet[2].color_trace = darkgreen;
	bullet[2].formula = true;
	bullet[2].radius = 0.00762;
	bullet[2].mass = 0.017;
};

//������� ������� "�����" ���� ��������
bool LIFES_CHECK(double T)
{
	bool lifes = false;
	for (int n = 0; n < N; n++)
	{
		if (bullet[n].life && !((bullet[n].cor.y <= 700) && (bullet[n].cor.x >= 0)))
		{
			bullet[n].life = false;
			cout << "Distance[" << n + 1 << "]= " << bullet[n].c_x - 100 << "\tt= " << T << endl;//����� � ������� ���������� ����� ��������
		}

		if (bullet[n].life == true) { lifes = true; }//���� ���� ����� �� ����� �� ��� ������, ���� ���� ���� ���� �����, �� while ��������
	}
	return lifes;
};

//������� ���������� "������� - ����������"
void COUT_WINNER()
{
	int k = 0;
	double d_max = 0;
	for (int n = 0; n < N; n++)
	{
		
		if (bullet[n].c_x > d_max) { k = n; d_max = bullet[n].c_x; }
	}
	cout << endl << "Win= [" << k+1 << "] Disctance= " << d_max- 100 << endl;
};

