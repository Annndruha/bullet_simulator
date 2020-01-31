#pragma once
std::default_random_engine generator(time(NULL));

int my_rangint_gen(int a, int b)
{
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

#ifdef ENABLE_OPENCV
using namespace cv;
//----------- B ---G--- R
Scalar white(255, 255, 255);
Scalar gray(128, 128, 128);
Scalar black(1, 0, 0);

Scalar red(0, 0, 255);
Scalar green(0, 255, 0);
Scalar blue(255, 0, 0);

Scalar darkred(0, 0, 127);
Scalar darkgreen(0, 127, 0);
Scalar darkblue(127, 0, 0);

Scalar yellow(0, 255, 255);
Scalar cyan(255, 255, 0);
Scalar magneta(255, 0, 255);

Scalar violet(255, 0, 128);

Scalar random_color() {
	switch (my_rangint_gen(0,11))
	{
		case 0: return gray;
		case 1: return black;
		case 2: return red;
		case 3: return green;
		case 4: return blue;
		case 5: return darkred;
		case 6: return darkgreen;
		case 7: return darkblue;
		case 8: return yellow;
		case 9: return cyan;
		case 10: return magneta;
		case 11: return	violet;
		default:gray;
	}
};
#endif