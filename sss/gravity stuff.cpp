using namespace std;
#include "objects.h"
#include <vector>
#include "integrations.h"



void NewtonGravityupd(vector <Particle>& a1, const int& integration, const double& timestep, double totaltime) {
	if (integration == 2) {
		for (auto a : a1) {
			VerletInitializing(a, timestep);
		}
	}



	for (int i = 0; i < a1.size(); i++) {
		for (int j = i + 1; j < a1.size(); j++) {
			Vector3 r = a1[i].getPosition() - a1[j].getPosition();
			double distance = r.magnitude();
			Vector3 forceDirection = r / distance;
			double forceMagnitude = 6.67428e-11 * a1[i].getmass() * a1[j].getmass() / (distance * distance);
			Vector3 force = forceDirection * forceMagnitude;
			a1[i].updForce(force * -1);
			a1[j].updForce(force);
		}
	}




	if (integration == 1) {
		for (int r = 0; r < a1.size(); r++) {
			Euler(a1[r], timestep);
			a1[r].cleanForce();
		}
	}
	else if (integration == 2) {
		for (int r = 0; r < a1.size(); r++) {
			Verlet(a1[r], timestep); \
				a1[r].cleanForce();
		}
	}
	else if (integration == 3) {
		for (int r = 0; r < a1.size(); r++) {
			RK4(a1[r], timestep);
			a1[r].cleanForce();
		}
	}
}