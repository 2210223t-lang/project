#pragma once
using namespace std;
#include "objects.h"
void Verlet(Particle& a1, const double& timestep);
void Euler(Particle& a1, const double& timestep);
void RK4(Particle& a1, const double& timestep);
void VerletInitializing(Particle& a1, const double& timestep);