#pragma once
#ifdef ENABLE_OPENCV
//����� ��������� ������������ ����
class display
{
private:
	Mat background = imread("resources/background.JPG");
	Mat draw = Mat::zeros(background.rows, background.cols, CV_8UC3);
	Mat trace = Mat::zeros(background.rows, background.cols, CV_8UC3);
	Mat out = Mat::zeros(background.rows, background.cols, CV_8UC3);

	void merge_two_layers(Mat, Mat);
	void draw_forces(bullet_create* pointer);
	void draw_trace(bullet_create* pointer);
	void draw_bullet(bullet_create* pointer);
	void draw_bullet(bullet_create* pointer, int n);
	void draw_time(double T);
	void merge_layers();

public:
	int scale = 100;
	bool enable_trace = true;
	bool enable_forces = true;
	void start(String window_name);
	void show(String window_name);
	void draw_scalegrid();
	void draw_frame(bullet_create* pointer, double time);
	void draw_frame(bullet_create* pointer, double time, int bullet_number);
	void clear_draw();
};


// �������� ������������ ����
void display::start(String window_name)
{
	namedWindow(window_name);
	moveWindow(window_name, 300, 150);
}

// ����� �����
void display::show(String window_name)
{
	merge_layers();
	imshow(window_name.c_str(), out);
}

//������� ������������� �������� ���� ����
void display::merge_two_layers(Mat down_layer, Mat up_layer)
{
	for (int i = 0; i < down_layer.rows; i++)
	{
		uchar* ptr_up = (uchar*)(up_layer.data + i * up_layer.step);
		uchar* ptr_down = (uchar*)(down_layer.data + i * down_layer.step);
		for (int j = 0; j < down_layer.cols; j++)
		{
			// �� �� ������ ��������� ������������ � PpenCV, RGB = (0,0,0) ������������ � �������� ����������� �����
			// � ������ �������� ��� RGB = (1,0,0)
			if ((ptr_up[3 * j + 0] != 0) || (ptr_up[3 * j + 1] != 0) || (ptr_up[3 * j + 2] != 0))
			{
				ptr_down[3 * j + 0] = ptr_up[3 * j + 0];
				ptr_down[3 * j + 1] = ptr_up[3 * j + 1];
				ptr_down[3 * j + 2] = ptr_up[3 * j + 2];
			}
		}
	}
}

//����������� ���� �������
void display::merge_layers()
{
	out = background.clone();
	merge_two_layers(out, trace);
	merge_two_layers(out, draw);
};

//��������� ������������ �����
void display::draw_scalegrid()
{
	for (int i = 700; i > 0; i = i - scale)
	{
		line(background, Point(100, i), Point(background.cols, i), gray, 1, LINE_AA);
		String k = std::to_string(700 - i);
		putText(background, k, Point(50, i), FONT_HERSHEY_DUPLEX, 0.6, black, 0, 4, false);
	}


	for (int i = 100; i < background.cols; i = i + scale)
	{
		line(background, Point(i, 1), Point(i, 700), gray, 1, LINE_AA);
		String k = std::to_string(i - 100);
		putText(background, k, Point(i - 10, 730), FONT_HERSHEY_DUPLEX, 0.6, black, 0, 4, false);
	}

	arrowedLine(background, Point(100, 700), Point(background.cols, 700), black, 3, LINE_AA, 0, 0.016);
	arrowedLine(background, Point(100, 700), Point(100, 0), black, 3, LINE_AA, 0, 0.026);
};

//������� ��������� ���
void display::draw_forces(bullet_create* pointer)
{
	bullet_create& bull = *pointer;
	if (bull.life)
	{
		arrowedLine(draw, bull.cor, bull.resistanse, blue, 4, 8, 0, 0.15);
		putText(draw, "Fr", bull.resistanse - Point(30, 0), FONT_ITALIC, 0.8, blue, 0, LINE_AA, false);
		arrowedLine(draw, bull.cor, bull.mg, red, 4, 8, 0, 0.15);
		putText(draw, "mg", bull.mg - Point(50, 0), FONT_HERSHEY_DUPLEX, 0.8, red, 0, LINE_AA, false);
	}
	else
	{
		arrowedLine(draw, bull.cor, 2 * bull.cor - bull.mg, magneta, 4, 8, 0, 0.15);
		putText(draw, "N", 2 * bull.cor - bull.mg - Point(30, 0), FONT_ITALIC, 0.8, magneta, 0, LINE_AA, false);

		arrowedLine(draw, bull.cor, bull.mg, red, 4, 8, 0, 0.15);
		putText(draw, "mg", bull.mg - Point(50, 0), FONT_HERSHEY_DUPLEX, 0.8, red, 0, LINE_AA, false);
	}

};

//������� ��������� �����
void display::draw_trace(bullet_create* pointer)
{
	bullet_create& bull = *pointer;
	circle(trace, bull.cor, 2, bull.color_trace, -1, 8);//��������� ����� ���� �� ���� trace
};

//������� ��������� �������
void display::draw_bullet(bullet_create* pointer)
{
	bullet_create& bull = *pointer;
	circle(draw, bull.cor, 15, bull.color_main, -1, 8);//��������� ���� �� ���� draw
};

//������� ��������� �������
void display::draw_bullet(bullet_create* pointer, int n)
{
	bullet_create& bull = *pointer;
	circle(draw, bull.cor, 15, bull.color_main, -1, 8);//��������� ���� �� ���� draw
	String k = std::to_string(n + 1);
	putText(draw, k, bull.cor - Point(9, -8), FONT_HERSHEY_DUPLEX, 0.8, white, 0, 8, false);//����� �������
};

//������� ��������� ������� ���������
void display::draw_time(double T)
{
	String k = std::to_string(T);
	k = k.substr(0, k.size() - 2);
	String r = "t= " + k + " c";
	putText(draw, r, Point(200, 760), FONT_HERSHEY_SIMPLEX, 0.8, black, 2, 8, false);//����� �������
};

// ��������� �����. time - ����� ���������
void display::draw_frame(bullet_create* pointer, double time) {
	if (enable_forces) { draw_forces(pointer); }
	if (enable_trace) { draw_trace(pointer); }
	draw_bullet(pointer);
	draw_time(time);
}

// ��������� �����. time - ����� ���������, bullet_number - ����� �������
void display::draw_frame(bullet_create* pointer, double time, int bullet_number) {
	if (enable_forces) { draw_forces(pointer); }
	if (enable_trace) { draw_trace(pointer); }
	draw_bullet(pointer, bullet_number);
	draw_time(time);
}

// ������� ���� draw
void display::clear_draw() {
	draw = NULL;
}
#endif