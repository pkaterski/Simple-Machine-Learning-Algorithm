#include <iostream>

#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
	double* v;
	int len;
public:
	Vector();
	Vector(double*, int);
	Vector(Vector const&);
	~Vector();

	Vector operator=(Vector const&);

	void setVector(double*, int);

	double* getArray() const;
	int getLength() const;

	bool operator==(Vector const&);
	bool operator!=(Vector const&);
	double operator*(Vector const&);
	Vector operator*(double);
	Vector operator+(Vector const&);
	Vector operator-(Vector const&);

	friend std::ostream& operator<<(std::ostream&, Vector const&);
	friend std::istream& operator>>(std::istream&, Vector&);
};

#endif // !VECTOR_H
