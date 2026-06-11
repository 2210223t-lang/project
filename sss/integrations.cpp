using namespace std;
#include "objects.h"


void VerletInitializing(Particle& a1, const double& timestep) {
	a1.setPreviousposition(a1.getPosition() - a1.getVelocity() * timestep - a1.getForce() / a1.getmass() * timestep * timestep / 2);
}


void Verlet(Particle& a1,const double& timestep)  {
	Vector3 newpos = a1.getPosition() * 2 - a1.getPreviousposition() + a1.getForce() * timestep * timestep / a1.getmass();
	a1.setPreviousposition(a1.getPosition());
	a1.setPosition(newpos);
}



void Euler(Particle& a1, const double& timestep) {
	Vector3 acceleration = a1.getForce() / a1.getmass();
	a1.updVelocity(acceleration);
	Vector3 newpos = a1.getPosition() + a1.getVelocity() * timestep;
	a1.setPreviousposition(a1.getPosition());
	a1.setPosition(newpos);
}



void RK4(Particle& a1, const double& timestep) {
	Vector3 k1 = a1.getForce() / a1.getmass();
	Vector3 k2 = (a1.getForce() + k1 * timestep / 2) / a1.getmass();
	Vector3 k3 = (a1.getForce() + k2 * timestep / 2) / a1.getmass();
	Vector3 k4 = (a1.getForce() + k3 * timestep) / a1.getmass();
	Vector3 newpos = a1.getPosition() + (k1 + k2 * 2 + k3 * 2 + k4) * timestep / 6;
	a1.setPreviousposition(a1.getPosition());
	a1.setPosition(newpos);
}