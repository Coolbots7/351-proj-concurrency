//Intercection.h
//Brian Bugert

#include <iostream>
#include <windows.h>
using namespace std;


class Intersection {
private:

	HANDLE QuadrantSemaphores[4];

public:
	Intersection()
	{
		//initiallize the semaphore. Might move this onto main if necessary.
		//make 4 quadrants that are numbered 1-4 and set their states to not full
		for(int i = 0; i < 4; i++)
		{
			QuadrantSemaphores[i] = CreateSemaphore(NULL, 0, INFINITE, NULL);
		}

		printf("Intersection Created\n");

	}

	//functions to lock areas of intersection
	bool LockQuadrant(int Quadrant)//, int tid)
	{
		if(Quadrant < 0 || Quadrant >= 4)
			return false;


		WaitForSingleObject(QuadrantSemaphores[Quadrant], INFINITE);

		return true;

	}

	bool UnlockQuadrant(int Quadrant)
	{
		if(Quadrant < 0 || Quadrant >= 4)
			return false;

		ReleaseSemaphore(QuadrantSemaphores[Quadrant], 1, NULL);

		return true;
	}





};
