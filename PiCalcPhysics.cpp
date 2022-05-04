#include <iostream>
#include <math.h>
#include <chrono>
#include <string>

const unsigned int STEP = 35000;
const int DIGITS = 9;
const long double START_VELOCITY = -0.125;  // Needs to be negative
const std::chrono::steady_clock::time_point START = std::chrono::steady_clock::now();

struct Object
{
	long double vel;
	long double pos;
	long double mass;

	Object(long double vel, long double pos, long double mass)
	{
		this->vel = vel;
		this->pos = pos;
		this->mass = mass;
	}

	void move()
	{
		pos += vel / STEP;
	}
};

class Simulation
{
	Object smallObject{ 0, 100, 1 };
	Object largeObject{ START_VELOCITY, 400, pow(100, DIGITS - 1)};

	long long bounces = 0;

	void collision()
	{
		// Perform a perfectly elastic collision between the two objects
		// For all the formulas: https://courses.lumenlearning.com/boundless-physics/chapter/collisions/
		
		// Define vars for shorter lines
		long double m1 = smallObject.mass;

		long double m2 = largeObject.mass;

		long double v1i = smallObject.vel;
		long double v2i = largeObject.vel;

		// Use equation 6 from the link
		long double part1 = ((2 * m1) / (m2 + m1));
		long double v2f = ((2 * m1) / (m2 + m1)) * v1i + ((m2 - m1)/(m2 + m1)) * v2i;

		// Use equation 4 from the link
		long double v1f = v2f + v2i - v1i;

		// Apply the final velocities to the objects
		smallObject.vel = v1f;
		largeObject.vel = v2f;
	}

	void collisionCheck()
	{
		if (smallObject.pos <= 0)
		{
			smallObject.vel *= -1;
			bounces++;
		}

		if (smallObject.pos >= largeObject.pos)
		{
			collision();
			bounces++;
		}
	}

	void statusUpdate()
	{
		double percentCompleted = bounces / (3.1416 * pow(10, DIGITS - 1));
		
		std::cout << percentCompleted * 100 << "% complete";
		
		// Calculate expected time
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - START).count();
		double expectedTime = (1 / (percentCompleted)) * elapsedTime - elapsedTime;
		std::cout << " | ETA: " << expectedTime << " seconds\n";
	}

public:
	void runSimulation()
	{
		while (abs(smallObject.vel) > largeObject.vel || smallObject.vel < 0 && smallObject.mass != largeObject.mass)
		{
			collisionCheck();
			smallObject.move();
			largeObject.move();

			if (bounces % 100000000 == 0 && bounces != 0)
			{
				statusUpdate();
			}
		}

		std::cout << "Bounces: " << bounces << std::endl;
	}
};

int main()
{
	Simulation sim;
	sim.runSimulation();
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(end - START).count() << " seconds" << std::endl;
	return 0;
}
