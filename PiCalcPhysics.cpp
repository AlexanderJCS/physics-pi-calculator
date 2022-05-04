#include <iostream>
#include <chrono>

const unsigned int STEP = 35000;
const double HITBOX = 49700;
const int digits = 11;
const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

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
	Object largeObject{ -0.125, 50000, pow(100, digits - 1)};

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

	void phaseCheck()
	{
		if (largeObject.pos <= 0)
		{
			std::cout << "WARNING: Large object likely phased through the small object" << std::endl;
			exit(0);
		}

		else if (smallObject.pos > largeObject.pos)
		{
			std::cout << "WARNING: Small object likely phased through the large object" << std::endl;
			exit(0);
		}
	}

	void collisionCheck()
	{
		if (smallObject.pos <= 0)
		{
			smallObject.vel *= -1;
			bounces++;
		}

		if (abs(smallObject.pos - largeObject.pos) <= HITBOX)
		{
			collision();
			bounces++;
		}
	}

	void statusUpdate()
	{
		double percentCompleted = (bounces / (3.1416 * pow(10, digits - 1))) * 100;
		std::cout << percentCompleted << "% complete\n";

		//std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		//auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - start).count();
		//double expectedTime = (1 / (percentCompleted)) * elapsedTime;
		//std::cout << "Expected time remaining: " << expectedTime << " seconds" << std::endl;
	}

public:
	void runSimulation()
	{
		while (abs(smallObject.vel) > largeObject.vel || smallObject.vel < 0 && smallObject.mass != largeObject.mass)
		{
			collisionCheck();
			phaseCheck();
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
	
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds" << std::endl;
	return 0;
}
