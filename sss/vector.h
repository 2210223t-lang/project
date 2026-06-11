#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Vector3 {
public:
	double x, y, z;
	Vector3(double ax, double ay, double az)
		:x(ax), y(ay), z(az) {
	}
	Vector3(){
		x = 0;
		y = 0;
		z = 0;
	}
	void parameters() const {
		cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
	}

	double magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 operator+(const Vector3& other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 operator-(const Vector3& other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	double operator* (const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	Vector3 operator*(double scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	Vector3 operator/(double scalar)const {
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
};