// PLA.cpp : Defines the entry point for the console application.
//

// created by Parashkev Katerski™

#include "stdafx.h"
#include <iostream>
#include "myFunctions.h"
#include "Perceptron.h"

#include <cstdlib> //  srand, rand
#include <ctime> // time

using namespace std;


int main() {
	// Generate data
	Data *data;
	const int N = 100;

	srand(time(NULL));
	Line l = generateLine();
	data = generateData(N, l);
	cout << "line: A = " << l.A << " B = " << l.B << " C = " << l.C << endl;
	Vector *bound = getBoundry(l);
	cout << "boundry points: " << bound[0] << ", " << bound[1] << endl;

	int positive = 0;
	for (int i = 0; i < N; i++) {
		// cout << data[i].x << " ";
		// cout << data[i].y << endl;
		if (data[i].y == 1) positive++;
	}
	cout << "-1 : " << N - positive << "  |  +1 : " << positive << endl;


	// Learn
	cout << "\n\n\n--------------Learning--------------\n\n";
	Perceptron perceptron;
	cout << "Itterations: " << perceptron.Learn(data, N) << endl;


	Line g = perceptron.getLine();
	cout << "line L: A = " << l.A / l.A << " B = " << l.B / l.A << " C = " << l.C / l.A << endl;
	cout << "line G: A = " << g.A / g.A << " B = " << g.B / g.A << " C = " << g.C / g.A << endl;

	// some statistics
	cout << "\n\n\n--------------Stats--------------\n\n";
	const int SAMPLE = 10000;
	Data *dataF = generateData(SAMPLE, l);
	int correct = 0;
	int incorrect;

	for (int i = 0; i < SAMPLE; i++) {
		if (dataF[i].y == perceptron.Predict(dataF[i].x)) correct++;
	}
	incorrect = SAMPLE - correct;
	cout << "INCORRECT: " << incorrect << "  |  CORRECT: " << correct << endl;
	cout << "ERROR: " << (double)incorrect / (double)(correct + incorrect) << endl;

    return 0;
}

