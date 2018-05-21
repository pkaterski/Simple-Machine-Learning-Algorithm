#include "stdafx.h"
#include "Perceptron.h"
#include "Vector.h"
#include "myFunctions.h"

#include <iostream>
using namespace std;

Perceptron::Perceptron() {
	double w[3] = { 0,0,0 };
	this->w = Vector(w, 3);
}

Perceptron::Perceptron(Vector w) {
	this->w = w;
}

Vector Perceptron::getVector() {
	return this->w;
}

void Perceptron::setVector(Vector w) {
	this->w = w;
}

Line Perceptron::getLine() {
	double *w = this->w.getArray();

	// w of type [w0, w1, w2]
	// x = [x0, x1, x2], x0 = 1;
	// wT * x = x1 * w1 + x2 * w2 + w0
	return Line(w[1], w[2], w[0]);
}

int Perceptron::Predict(Vector x) {
	// assure that x is a 3D vector
	if (x.getLength() != 3) return 0;

	return sign(this->w * x);
}

unsigned long Perceptron::Learn(Data *data, int size) {
	// # of itterations
	unsigned long itter = 0;
	const unsigned long MAX_ITTER = size * 100;

	// misclassified points
	int misclassSize;
	int *misclass = nullptr; // stores the index of a misclassified point

	do {
		// find which points are misclassified in this itteration
		misclassSize = 0;
		for (int i = 0; i < size; i++) {
			if (this->Predict(data[i].x) != data[i].y) {
				misclassSize++;
				if (misclass == nullptr) {
					misclass = new int[1];
					misclass[0] = i;
				}
				else {
					int *newMisclass = new int[misclassSize];
					for (int j = 0; j < misclassSize - 1; j++) {
						newMisclass[j] = misclass[j];
					}
					newMisclass[misclassSize - 1] = i;
					delete[] misclass;
					misclass = newMisclass;
				}
			}
		}

		if (misclassSize == 0) break;

		// chose a random misclassified point
		int randNum = rand() % misclassSize;
		int index = misclass[randNum];
		Vector misclassPoint = data[index].x;
		int misclassY = data[index].y;

		// adjust for error
		this->w = this->w + (misclassPoint * misclassY);
		
		itter++;

	} while (misclassSize != 0 && itter < MAX_ITTER);

	return itter;
}

void Perceptron::Reset() {
	double w[3] = { 0,0,0 };
	this->w = Vector(w, 3);
}