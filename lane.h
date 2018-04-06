//Linked List Class for car queue for each direction


class CarNode
{
	public:
	Car *hold;
	CarNode *next;
	CarNode (Car *niceone, CarNode *ptr = 0) 
	{
		hold = niceone;
		next = ptr;
	}
};

class CarList
{
	private:
	CarNode *end, *front;
	
	public:
	CarList();
	~CarList();
	
	void enqueue(Car*);	
	Car dequeue();
	
	
	bool isEmpty();
	
	void printAll() const;
	
};

CarList::CarList()
{
	end = front = 0;
}

CarList::~CarList()
{
	while (front != NULL)
	{
		CarNode *temp = front->next;
		delete[] front;
		front = temp;
	}
}

void CarList::enqueue(Car *add)
{
	if (end != 0)
	{
		end->next = new CarNode(add);
		end = end->next;
	}
	else
		front = end = new CarNode(add);
}

Car CarList::dequeue()
{
	Car *temp = front->hold;	
	CarNode *tmp = front;	

	if (front == end)		
		front = end = 0;	
	else
	{
		front = front->next;	
	}

	delete tmp;				
	return *temp;
}

void CarList::printAll() const // test purpose
{
	for (CarNode *tmp = front; tmp != 0; tmp = tmp->next)
		cout << tmp->hold->GetID() << " ";
	cout << endl;
}


bool CarList::isEmpty()
{
	if(front == 0){return true;}
	else{return false;}
}