#include "Vector.h"

#pragma once
struct Data {
	Vector x;
	int y;
};

struct Line {
	// l: Ax + By + C = 0
	double A;
	double B;
	double C;

	Line(double A, double B, double C) {
		this->A = A;
		this->B = B;
		this->C = C;
	}
};

Data* generateData(int const, Line);

Vector generatePoint();

// Where does a line cross the box
Vector* getBoundry(Line);

Line generateLine();

double relativeToLine(Line, Vector);

int sign(double);

