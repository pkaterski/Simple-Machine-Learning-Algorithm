#include "Vector.h"
#include "myFunctions.h"

#pragma once
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class Perceptron {
private:
	Vector w;
public:
	Perceptron();
	Perceptron(Vector);

	int Predict(Vector);
	unsigned long Learn(Data*, int);
	Vector getVector();
	void setVector(Vector);
	Line getLine();

	void Reset();
};

#endif // !PERCEPTRON_H
