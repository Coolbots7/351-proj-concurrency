/* 351-04 Concurrency Project
Project Members:
Jonathan Bedoy
Joon Choi
Oscar Gallo
Beau Badilla
Bill Nazaroff
Brian Bugert

*/


#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>	
#include "car.h"
#include "intersection.h"
#include "lane.h"

using namespace std;

#define NUM_CARS 400
#define NUM_THREADS 4

intersection a;
CarList *North = new CarList();
CarList *South = new CarList();
CarList *East = new CarList();
CarList *West = new CarList();
void simN(Car b);
void simE(Car b);
void simS(Car b);
void simW(Car b);

int StraightCount;
int LeftCount;
int RightCount;
int UTurnCount;

void *simStart(void* threadid)
{
	long tid;
	tid = (long)threadid;
	bool exit = false;
	while(!exit)
	{
		if(threadid == (void*)0 && !North->isEmpty())
		{
			cout << threadid << ": ";
			simN(North->dequeue());
		}
		else if(threadid == (void*)1 && !East->isEmpty())
		{
			cout << threadid << ": ";
			simE(East->dequeue());
		}	
		else if(threadid == (void*)2 && !South->isEmpty())
		{
			cout << threadid << ": ";
			simS(South->dequeue());
		}
		else if(threadid == (void*)3 && !West->isEmpty())
		{
			cout << threadid << ": ";
			simW(West->dequeue());
		}
		else{exit = true;}
		
		usleep((rand()%2)* 1000 * 100);
	}
	
	pthread_exit(NULL);
}
int main(int argc, char *argv[]) {

	pthread_t threads[NUM_THREADS];
	int rc;
	int i;

	sem_t quad1;
	sem_t quad2;
	sem_t quad3;
	sem_t quad4;
	sem_t center;
	
	StraightCount = 0;
	LeftCount = 0;
	RightCount = 0;
	UTurnCount = 0;

	bool done = false;

	
	for (int i = 0; i < NUM_CARS; i++) {
		Car *car = new Car(i);
		
		switch(car->GetDesiredDirection()) {
			case STRAIGHT:
				StraightCount++;
				break;
			case LEFT:
				LeftCount++;
				break;
			case RIGHT:
				RightCount++;
				break;
			case UTURN:
				UTurnCount++;
				break;
		}
		
		switch (rand() % 4) {
			case 0:
				North->enqueue(car);
				break;
			case 1:
				South->enqueue(car);
				break;
			case 2:
				East->enqueue(car);
				break;
			case 3:
				West->enqueue(car);
				break;
		}
		
	}
	
	//Initialize semaphores
	for (i = 0; i < 4; i++)
	{
		sem_init(&readA[i], 0, 1);
	}
	
	//Start threads
	for (i = 0; i < NUM_THREADS; i++)
	{
		cout << "main (): creating thread: " << i << endl;
		rc = pthread_create(&threads[i], NULL, simStart, (void*) (intptr_t) i);
		if (rc)
		{
			cout << "unable to create thread: " << i << endl;
			exit(-1);
		}
	}
	for(int i=0;i<NUM_THREADS;i++) {
		pthread_join(threads[i], NULL);
	}
	
	
	//Destroy semaphores
	for (i = 0; i < 4; i++)
	{
		sem_destroy(&readA[i]);
	}
	
	
	printf("Straights: %i\n", StraightCount);
	printf("Left Turns: %i\n", LeftCount);
	printf("Right Turns: %i\n", RightCount);
	printf("U-Turns: %i\n", UTurnCount);
	printf("Total Cars: %i\n", StraightCount+LeftCount+RightCount+UTurnCount);
	
	return 0;

}


//only cars that are North will be here
void simN(Car b)
{
	
	switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			a.access(3);
			a.access(2);
			a.setFree(3);
			a.setFree(2);
			break;
		case LEFT:
			a.access(4);
			a.access(3);
			a.access(2);
			a.setFree(4);
			a.setFree(3);
			a.setFree(2);
			break;
		case UTURN:
			a.access(2);
			a.access(1);
			a.setFree(2);
			a.setFree(1);
			break;
		case RIGHT:
			a.access(2);
			a.setFree(2);
			break;

	}
	
	b.IsThroughIntersection();
}
void simE(Car b)
{
	
	switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			a.access(2);
			a.access(1);
			a.setFree(2);
			a.setFree(1);
			break;
		case LEFT:
			a.access(3);
			a.access(2);
			a.access(1);
			a.setFree(3);
			a.setFree(2);
			a.setFree(1);
			break;
		case UTURN:
			a.access(4);
			a.access(1);
			a.setFree(4);
			a.setFree(1);
			break;
		case RIGHT:
			a.access(1);
			a.setFree(1);
			break;

	}
	
	b.IsThroughIntersection();
}
void simS(Car b)
{
	
	switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			a.access(4);
			a.access(1);
			a.setFree(4);
			a.setFree(1);
			break;
		case LEFT:
			a.access(4);
			a.access(2);
			a.access(1);
			a.setFree(4);
			a.setFree(2);
			a.setFree(1);
			break;
		case UTURN:
			a.access(4);
			a.access(3);
			a.setFree(4);
			a.setFree(3);
			break;
		case RIGHT:
			a.access(4);
			a.setFree(4);
			break;

	}
	
	b.IsThroughIntersection();
}
void simW(Car b)
{
	
	switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			a.access(4);
			a.access(3);
			a.setFree(4);
			a.setFree(3);
			break;
		case LEFT:
			a.access(4);
			a.access(3);
			a.access(1);
			a.setFree(4);
			a.setFree(3);
			a.setFree(1);
			break;
		case UTURN:
			a.access(3);
			a.access(2);
			a.setFree(3);
			a.setFree(2);
			break;
		case RIGHT:
			a.access(3);
			a.setFree(3);
			break;

	}
	
	b.IsThroughIntersection();

}
