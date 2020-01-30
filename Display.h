#pragma once

//Класс создания графического окна и слоёв внутри него
class display
{
public:
	//Инициализация графического окна
	void start(String n) 
	{
		namedWindow(n);
		moveWindow(n, 300, 150);
	}

	Mat background = imread("background.JPG");
	Mat draw = Mat::zeros(background.rows, background.cols, CV_8UC3);
	Mat trace = Mat::zeros(background.rows, background.cols, CV_8UC3);
	Mat out = Mat::zeros(background.rows, background.cols, CV_8UC3);
	
	//Показ кадра и очистка верхних слоёв
	void show(String n)
	{
		imshow(n.c_str(), out);
		draw = NULL;
		out = NULL;
	}

};

//Функция попиксильного сведения слоёв
void MERGE(Mat* out, Mat* up, int chanals)
{
	for (int i = 0; i < out->rows; i++)
	{
		uchar* ptr_up = (uchar*)(up->data + i * up->step);
		uchar* ptr_out = (uchar*)(out->data + i * out->step);
		for (int j = 0; j < out->cols; j++)
		{
			if ((ptr_up[chanals * j + 0] != 0) || (ptr_up[chanals * j + 1] != 0) || (ptr_up[chanals * j + 2] != 0))
			{
				ptr_out[chanals * j + 0] = ptr_up[chanals * j + 0];
				ptr_out[chanals * j + 1] = ptr_up[chanals * j + 1];
				ptr_out[chanals * j + 2] = ptr_up[chanals * j + 2];
			}
		}
	}

};

//Функция рисования заднего фона
void DRAW_BACKGROUND(display* wind)
{
	display &window = *wind;

	int web_step = 100;
	for (int i = 700; i > 0; i = i - web_step) 
	{
		line(window.background, Point(100, i), Point(window.background.cols, i), gray, 1, LINE_AA);
		String k = std::to_string(700-i);
		putText(window.background, k, Point(50,i), FONT_HERSHEY_DUPLEX, 0.6, black, 0, 4, false);
	}
	

	for (int i = 100; i < window.background.cols; i=i+ web_step)
	{
		line(window.background, Point(i, 1), Point(i, 700), gray, 1, LINE_AA);
		String k = std::to_string(i-100);
		putText(window.background, k, Point(i-10, 730), FONT_HERSHEY_DUPLEX, 0.6, black, 0, 4, false);
	}

	arrowedLine(window.background, Point(100, 700), Point(window.background.cols, 700), black, 3, LINE_AA, 0, 0.016);
	arrowedLine(window.background, Point(100, 700), Point(100, 0), black, 3, LINE_AA, 0, 0.026);
};

//Функция отрисовки сил
void DRAW_FORSES(display* wind, bullet_create* pointer)
{
	bullet_create &bull = *pointer;
	display &window= *wind;
	if (bull.life) 
	{
		arrowedLine(window.draw, bull.cor, bull.resistanse, blue, 4, 8, 0, 0.15);
		putText(window.draw, "Fr", bull.resistanse - Point(30, 0), FONT_ITALIC, 0.8, blue, 0, LINE_AA, false);
		arrowedLine(window.draw, bull.cor, bull.mg, red, 4, 8, 0, 0.15);
		putText(window.draw, "mg", bull.mg - Point(50, 0), FONT_HERSHEY_DUPLEX, 0.8, red, 0, LINE_AA , false);
	}
	else
	{
		arrowedLine(window.draw, bull.cor, 2*bull.cor -bull.mg, magneta, 4, 8, 0, 0.15);
		putText(window.draw, "N", 2 * bull.cor - bull.mg - Point(30, 0), FONT_ITALIC, 0.8, magneta, 0, LINE_AA , false);

		arrowedLine(window.draw, bull.cor, bull.mg, red, 4, 8, 0, 0.15);
		putText(window.draw, "mg", bull.mg - Point(50, 0), FONT_HERSHEY_DUPLEX, 0.8, red, 0, LINE_AA , false);
	}

};

//Функция отрисовки следа
void DRAW_TRACE(display* wind, bullet_create* pointer)
{
	bullet_create &bull = *pointer;
	display &window = *wind;

	circle(window.trace, bull.cor, 2, bull.color_trace, -1, 8);//рисование следа пули на слое trace
};

//Функция отрисовки снаряда
void DRAW_BULLET(display* wind, bullet_create* pointer, int n)
{
	bullet_create &bull = *pointer;
	display &window = *wind;

	circle(window.draw, bull.cor, bull.radius_draw, bull.color_main, -1, 8);//рисование пули на слое draw
	String k = std::to_string(n + 1);
	putText(window.draw, k, bull.cor - Point(9, -8), FONT_HERSHEY_DUPLEX, 0.8, white, 0, 8, false);//Номер снаряда
};

//Функция отрисовки времени
void DRAW_TIME(display* wind,  double T)
{
	display &window = *wind;
	String k = std::to_string(T);
	k = k.substr(0, k.size() - 2);
	String r = "t= " + k + " c";
	putText(window.draw, r, Point(200, 760), FONT_HERSHEY_SIMPLEX, 0.8, black, 2, 8, false);//Номер снаряда
};