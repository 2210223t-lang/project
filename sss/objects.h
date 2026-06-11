#pragma once
#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;


class Particle {
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 force;
	double mass;
	Vector3 previousposition;
public:
	Particle(const Vector3& position, const Vector3& velocity, const double mass)
		: position(position), velocity(velocity), mass(mass){}
	void updVelocity(const Vector3& a1) {
		velocity = velocity + a1;
	}
	void updForce(const Vector3& newForce) {
		force = force + newForce;
	}

	void cleanForce() {
		Vector3 s(0, 0, 0);
		force = s;
	}
	void setPosition(const Vector3& position) {
		this->position = position;
	}
	void setPreviousposition(const Vector3& previousposition) {
		this->previousposition = previousposition;
	}

	Vector3 getVelocity() const {
		return velocity;
	}
	Vector3 getPosition () const {
		return position;
	}
	Vector3 getPreviousposition() const {
		return previousposition;
	}
	Vector3 getForce() const {
		return force;
	}
	double getmass() {
		return mass;
	}
};

