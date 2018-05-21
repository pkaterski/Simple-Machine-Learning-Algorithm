#include "stdafx.h"
#include "Vector.h"
#include <iostream>

Vector::Vector() {
	this->v = new double[1];
	this->v[0] = 0;
	this->len = 1;
}

Vector::Vector(double *v, int len) {
	this->v = new double[len];
	for (int i = 0; i < len; i++) {
		this->v[i] = v[i];
	}
	this->len = len;
}

Vector::Vector(Vector const &vector) {
	this->v = new double[vector.len];
	for (int i = 0; i < vector.len; i++) {
		this->v[i] = vector.v[i];
	}
	this->len = vector.len;
}

Vector::~Vector() {
	delete[] this->v;
}

void Vector::setVector(double *v, int len) {
	delete[] this->v;
	this->v = new double[len];
	for (int i = 0; i < len; i++) {
		this->v[i] = v[i];
	}
	this->len = len;
}

Vector Vector::operator=(Vector const &vector) {
	this->setVector(vector.v, vector.len);

	return *this;
}

double* Vector::getArray() const {
	return this->v;
}

int Vector::getLength() const {
	return this->len;
}

bool Vector::operator==(Vector const &vector) {
	if (this->len != vector.len) return false;
	if (this->v == nullptr && vector.v != nullptr) return false;
	if (this->v != nullptr && vector.v == nullptr) return false;
	if (this->v == nullptr && vector.v == nullptr) return true;

	for (int i = 0; i < this->len; i++) {
		if (this->v[i] != vector.v[i]) return false;
	}
	return true;
}

bool Vector::operator!=(Vector const &vector) {
	return !this->operator==(vector);
}

double Vector::operator*(Vector const &vector) {
	if (this->len != vector.getLength()) {
		return 0;
	}

	double sum = 0;
	for (int i = 0; i < this->len; i++) {
		sum += (this->v[i] * vector.getArray()[i]);
	}

	return sum;
}

Vector Vector::operator*(double a) {
	double* prod = new double[this->len];
	for (int i = 0; i < this->len; i++) {
		prod[i] = this->v[i] * a;
	}

	return Vector(prod, this->len);
}

Vector Vector::operator+(Vector const &vector) {
	if (this->len != vector.getLength()) {
		return Vector();
	}
	double* sum = new double[this->len];
	for (int i = 0; i < this->len; i++) {
		sum[i] = this->v[i] + vector.getArray()[i];
	}

	return Vector(sum, this->len);
}

Vector Vector::operator-(Vector const &vector) {
	if (this->len != vector.getLength()) {
		return Vector();
	}
	double* diff = new double[this->len];
	for (int i = 0; i < this->len; i++) {
		diff[i] = this->v[i] - vector.getArray()[i];
	}

	return Vector(diff, this->len);
}

std::ostream& operator<<(std::ostream& os, Vector const &vector) {
	os << "[";
	for (int i = 0; i < vector.getLength() - 1; i++) {
		os << vector.getArray()[i] << ", ";
	}
	os << vector.getArray()[vector.getLength() - 1] << "]";

	return os;
}

std::istream& operator>>(std::istream& is, Vector &vector) {
	int len;
	double* v;

	is >> len;
	v = new double[len];
	for (int i = 0; i < len; i++) {
		is >> v[i];
	}
	vector.setVector(v, len);

	return is;
}