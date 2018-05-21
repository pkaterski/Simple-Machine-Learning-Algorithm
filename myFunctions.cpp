#include "stdafx.h"
#include "myFunctions.h"

#include <cstdlib> //  srand, rand
#include <ctime> // time

#include <iostream>
using namespace std;

Data* generateData(int const N, Line l) {
	Data *data = new Data[N];

	double x[3];
	x[0] = 1;

	for (int i = 0; i < N; i++) {
		data[i].x = generatePoint();
		data[i].y = sign(relativeToLine(l, data[i].x));
	}

	return data;
}


Vector generatePoint() {
	double x[3];
	x[0] = 1;

	x[1] = 1 - 2 * ((double)rand() / (double)RAND_MAX);
	x[2] = 1 - 2 * ((double)rand() / (double)RAND_MAX);
	return Vector(x, 3);
}

Line generateLine() {
	// vector = [1, x, y]
	Vector x1 = generatePoint(); // [1, x0, y0]
	Vector x2 = generatePoint(); // [1, u0, v0]

	while (x1 == x2) {
		x2 = generatePoint();
	}
	cout << "2 vectors for line: " << x1 << ", " << x2 << endl;

	double x0 = x1.getArray()[1];
	double y0 = x1.getArray()[2];
	double u0 = x2.getArray()[1];
	double v0 = x2.getArray()[2];

	// the coeficient infront of x should be positive
	// y0 - v0 > 0
	if (y0 < v0) {
		double tempX = x0;
		double tempY = y0;
		x0 = u0;
		u0 = tempX;
		y0 = v0;
		v0 = tempY;
	}

	// l: (y0 - u0)x + (v0 - x0)y + u0x0 -v0y0
	return Line(
		y0 - v0,
		u0 - x0,
		v0 * x0 - u0 * y0);
}

double relativeToLine(Line l, Vector vector) {
	// the form of the vector v = [1, x, y]
	double *v = vector.getArray();
	double x = v[1];
	double y = v[2];
	return (l.A * x + l.B * y + l.C);
}

int sign(double a) {
	if (a > 0) return 1;
	if (a == 0) return 0;
	return -1;
}

Vector* getBoundry(Line l) {
	Vector *b = new Vector[2];
	Vector b1;
	Vector b2;
	// intersections with the continuaton of the box [-1, 1] x [-1, 1]
	double x1; // y = 1
	double x2; // y = -1
	double y1; // x = 1
	double y2; // x = -1

	// vector is of form [1, x, y]
	// l: Ax + By + C = 0

	// boudry y = 1
	// x = -(B + C) / A
	x1 = l.A == 0 ? 1000 : -(l.B + l.C) / l.A;

	// boudry y = -1
	// x = (B - C) / A
	x2 = l.A == 0 ? 1000 : (l.B - l.C) / l.A;

	// boudry x = 1
	// y = -(A + C) / B
	y1 = l.B == 0 ? 1000 : -(l.A + l.C) / l.B;

	// boudry x = -1
	// y = (A - C) / B
	y2 = l.B == 0 ? 1000 : (l.A - l.C) / l.B;

	if (x1 <= 1 && x1 >= -1) {
		double v1[3] = { 1, x1, 1 };
		b1 = Vector(v1, 3);

		if (x2 <= 1 && x2 >= -1) {
			double v2[3] = { 1, x2, -1 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}

		if (y1 <= 1 && y1 >= -1) {
			double v2[3] = { 1, 1, y1 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}

		if (y2 <= 1 && y2 >= -1) {
			double v2[3] = { 1, -1, y2 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}
	}

	if (x2 <= 1 && x2 >= -1) {
		double v1[3] = { 1, x2, -1 };
		b1 = Vector(v1, 3);

		if (y1 <= 1 && y1 >= -1) {
			double v2[3] = { 1, 1, y1 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}

		if (y2 <= 1 && y2 >= -1) {
			double v2[3] = { 1, -1, y2 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}
	}

	if (y1 <= 1 && y1 >= -1) {
		double v1[3] = { 1, 1, y1 };
		b1 = Vector(v1, 3);

		if (y2 <= 1 && y2 >= -1) {
			double v2[3] = { 1, -1, y2 };
			b2 = Vector(v2, 3);
			b[0] = b1;
			b[1] = b2;
			return b;
		}
	}

	return nullptr;
}