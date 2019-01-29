#include "RPCClient.h"
#include "../../CarList.h"
#include "../../car.h"

int TRAVEL_TIME = 300;

class Lane {
private:
	int Direction;
	RPCClient* client;
	CarList* queue;

	void simN(Car b)
	{

		switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			/*a.access(3);
			a.access(2);
			a.setFree(3);
			a.setFree(2);*/

			client->LockQuadrant(2);
			client->LockQuadrant(1);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(2);
			client->UnlockQuadrant(1);
			break;
		case LEFT:
			/*a.access(4);
			a.access(3);
			a.access(2);
			a.setFree(4);
			a.setFree(3);
			a.setFree(2);*/

			client->LockQuadrant(3);
			client->LockQuadrant(2);
			client->LockQuadrant(1);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(2);
			client->UnlockQuadrant(1);
			break;
		case UTURN:
			/*a.access(2);
			a.access(1);
			a.setFree(2);
			a.setFree(1);*/
			
			client->LockQuadrant(1);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(1);
			client->UnlockQuadrant(0);
			break;
		case RIGHT:
			/*a.access(2);
			a.setFree(2);*/
			
			client->LockQuadrant(1);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(1);
			break;

		}

		b.IsThroughIntersection();
	}
	void simE(Car b)
	{

		switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			/*a.access(2);
			a.access(1);
			a.setFree(2);
			a.setFree(1);*/

			client->LockQuadrant(1);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(1);
			client->UnlockQuadrant(0);
			break;
		case LEFT:
			/*a.access(3);
			a.access(2);
			a.access(1);
			a.setFree(3);
			a.setFree(2);
			a.setFree(1);*/

			client->LockQuadrant(2);
			client->LockQuadrant(1);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(2);
			client->UnlockQuadrant(1);
			client->UnlockQuadrant(0);
			break;
		case UTURN:
			/*a.access(4);
			a.access(1);
			a.setFree(4);
			a.setFree(1);*/
			
			client->LockQuadrant(3);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(0);
			break;
		case RIGHT:
			/*a.access(1);
			a.setFree(1);*/
			
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(0);
			break;

		}

		b.IsThroughIntersection();
	}
	void simS(Car b)
	{

		switch (b.GetDesiredDirection()) {
		case STRAIGHT:
			/*a.access(4);
			a.access(1);
			a.setFree(4);
			a.setFree(1);*/

			client->LockQuadrant(3);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(0);
			break;
		case LEFT:
			/*a.access(4);
			a.access(2);
			a.access(1);
			a.setFree(4);
			a.setFree(2);
			a.setFree(1);*/

			client->LockQuadrant(3);
			client->LockQuadrant(1);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(1);
			client->UnlockQuadrant(0);
			break;
		case UTURN:
			/*a.access(4);
			a.access(3);
			a.setFree(4);
			a.setFree(3);*/
			
			client->LockQuadrant(3);
			client->LockQuadrant(2);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(2);
			break;
		case RIGHT:
			/*a.access(4);
			a.setFree(4);*/
			
			client->LockQuadrant(3);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			break;

		}

		b.IsThroughIntersection();
	}
	void simW(Car b)
	{

		switch (b.GetDesiredDirection()) {
		case STRAIGHT:
		/*	a.access(4);
			a.access(3);
			a.setFree(4);
			a.setFree(3);*/

			client->LockQuadrant(3);
			client->LockQuadrant(2);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(2);
			break;
		case LEFT:
			/*a.access(4);
			a.access(3);
			a.access(1);
			a.setFree(4);
			a.setFree(3);
			a.setFree(1);*/

			client->LockQuadrant(3);
			client->LockQuadrant(2);
			client->LockQuadrant(0);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(3);
			client->UnlockQuadrant(2);
			client->UnlockQuadrant(0);
			break;
		case UTURN:
			/*a.access(3);
			a.access(2);
			a.setFree(3);
			a.setFree(2);*/
			
			client->LockQuadrant(2);
			client->LockQuadrant(1);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(2);
			client->UnlockQuadrant(1);
			break;
		case RIGHT:
			/*a.access(3);
			a.setFree(3);*/
			
			client->LockQuadrant(2);
			
			Sleep(TRAVEL_TIME);

			client->UnlockQuadrant(2);
			break;

		}

		b.IsThroughIntersection();

	}

public:
	Lane(int direction) {
		Direction = direction;

		//Create RPCLient
		client = new RPCClient(direction);

		//Create CarList
		queue = new CarList();

		//Populate CarList
		for(int i=0;i<100;i++) {
			Car* car = new Car(i*(direction+1));
			queue->enqueue(car);
		}
	}

	void Run() {
		while(!queue->isEmpty()) {

			printf("Direction: %d - ", this->Direction);

			switch(Direction) {
				case 0:
					simN(queue->dequeue());
					break;
				case 1:
					simS(queue->dequeue());
					break;
				case 2:
					simE(queue->dequeue());
					break;
				case 3:
					simW(queue->dequeue());
					break;
			}
		}
	}

	void Close() {
		client ->Close();
	}

};