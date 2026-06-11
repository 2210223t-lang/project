#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Vector3 {
public:
	double x, y, z;
	Vector3(double ax, double ay, double az)
		:x(ax), y(ay), z(az) {
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
	Vector3 operator/(double scalar) const {
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
};
ostream& operator<<(ostream& ss, Vector3 const& c) {
	ss << "( " << c.x << ", " << c.y << ", " << c.z << ")";
	return ss;
};
istream& operator>>(istream& ss, Vector3& c) {
	ss >> c.x >> c.y >> c.z;
	return ss;
};





class Particle {
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 force;
	Vector3 prevpos;
	double mass;
public:
	Particle(const Vector3& position,const Vector3& prevpos, const Vector3& velocity, const double mass,const Vector3& force)
		: position(position),prevpos(prevpos),velocity(velocity),force(force),mass(mass){}
	void printPosition()const {
		cout << position;
	}
	void printVelocity()const {
		cout << velocity;
	}
	void printForce()const {
		cout << force;
	}
	void printMass()const {
		cout << mass;
	}


	void updForce(const Vector3& newForce) {
		force = force + newForce;
	}
	void TimePass(const double& time) {
		Vector3	acceleration = force / mass;
		Vector3 neww = position * 2 - prevpos + acceleration * time * time;
		prevpos = position;
		position = neww;
		force = Vector3(0, 0, 0);
	}



	void cleanForce() {
		Vector3 s(0, 0, 0);
		force = s;
	}
	void setPosition(const Vector3& position) {
		this->position = position;
	}
	void setVelocity(const Vector3& velocity) {
		this->velocity = velocity;
	}
	void setForce(const Vector3& force) {
		this->force = force;
	}
	void setMass(const double mass) {
		this->mass = mass;
	}

	double getx() const{
		return position.x;
	}
	double gety() const{
		return position.y;
	}
	double getz() const{
		return position.z;
	}
	double getmass() const{
		return mass;
	}
	Vector3 getPosition() const{
		return position;
	}
	Vector3 getVelocity() const {
		return velocity;
	}
	Vector3 getprevPos() const {
		return prevpos;
	}
};




void NewtonGravityupd(Particle& particle1, Particle& particle2) {
	Vector3 dist(0, 0, 0);
	dist = particle2.getPosition() - particle1.getPosition();
	double G = 6.67428e-11;
	if (dist.magnitude() < 1e-6) {
		particle1.updForce(Vector3(0, 0, 0));
		particle2.updForce(Vector3(0, 0, 0));
	}
	else {
		double k = G * particle1.getmass() * particle2.getmass() / pow(dist.magnitude(), 3);
		Vector3 result = dist * k;
		particle1.updForce(result);
		particle2.updForce(result * -1);
	}
};


void repget(Particle& a1, Particle& a2) {
	double mass;
	Vector3 position(0, 0, 0), velocity(0, 0, 0), force(0, 0, 0),prevpos(0,0,0);
		cout << "Enter mass, position (x y z), velocity (x y z) and force of massive particle: \n";
		cin >> mass >> position >>prevpos>> velocity >> force;
		Particle massi(position,, velocity, mass, force);
		cout << "Enter mass, position (x y z), velocity (x y z) and force of satelite: \n";
		cin >> mass >> position>>prevpos >> velocity >> force;
		Particle sat(position,prevpos, velocity, mass, force);
		a1 = massi;
		a2 = sat;
}

double dist(const Particle& p1,const Particle& p2) {
	return(sqrt(pow(p1.getx() - p2.getx(), 2) + pow(p1.gety() - p2.gety(), 2) + pow(p1.getz() - p2.getz(), 2)));
};


int check(const Particle& a1, const Particle& a2) {
	if (dist(a1, a2) > 1e-4) {
		return 1;
	}
	else {
		return 0;
	}
}

double potentialEnergy(const Particle& a1, const Particle& a2) {
	return -6.67428e-11 * a1.getmass() * a2.getmass() / dist(a1, a2);
}


int main() {
	double mass, time, timestep, energy;
	int explode = 0;
	Vector3 position(0, 0, 0), velocity(0, 0, 0), force(0, 0, 0),prevpos(0,0,0);
	cout << "Enter time of simulation and timestep: \n";
	cin >> time >> timestep;
	int flag = 1;

		cout << "Enter mass, position (x y z), velocity (x y z) and force of massive particle: \n";
		cin >> mass >> position>>velocity >> force;
		Particle massi(position,position - velocity * timestep, velocity, mass, force);
		cout << "Enter mass, position (x y z), velocity (x y z) and force of satelite: \n";
		cin >> mass >> position >>prevpos>>velocity >> force;
		Particle sat(position,position - velocity * timestep, velocity, mass, force);
		if (check(massi, sat) == 1) {
			flag = 0;
		}
		else {
			cout << "Particles are too close. Please, enter the parameters again.\n";
		}

		while (flag == 1) {
			repget(massi, sat);
			if (check(massi, sat) == 1) {
				flag = 0;
			}
			else {
				cout << "Particles are too close. Please, enter the parameters again.\n";
			}
		}

		energy = 0.5 * sat.getmass() * sat.getVelocity().magnitude() * sat.getVelocity().magnitude() - 6.6743e-11 * sat.getmass() * massi.getmass() / dist(sat, massi);
		if (energy >= 0) {
			cout << "Escaping orbit\n";
		}
		else {
			cout << "Captured by orbit\n";
		}


		double initialEnergy = 0.5 * sat.getmass() * sat.getVelocity().magnitude()	* sat.getVelocity().magnitude()	+ potentialEnergy(sat, massi);

	while (time > timestep && explode == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = i + 1; j < 2; j++) {
				NewtonGravityupd(massi, sat);
			}
		}
		massi.TimePass(timestep);
		sat.TimePass(timestep);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (dist(massi, sat) < 1e-4) {
					explode = 1;
					cout << "Boom";
				}
			}
		}
		time -= timestep;

	}
	double finalEnergy = 0.5 * sat.getmass() * sat.getVelocity().magnitude() * sat.getVelocity().magnitude() + potentialEnergy(sat, massi);
	
	if (explode != 1) {
		cout << "Final position of massive particle: " << massi.getPosition() << endl;
		cout << "Final position of satelite: " << sat.getPosition() << endl;

	}
	cout << "Initial energy: " << initialEnergy << endl;
	cout << "Final energy: " << finalEnergy << endl;
	cout << "Energy error: "<< abs(finalEnergy - initialEnergy)<< endl;