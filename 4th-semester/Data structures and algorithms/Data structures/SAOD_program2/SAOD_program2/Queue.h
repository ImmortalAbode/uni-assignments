#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue
{
	static const int size{ 4 };
	double queue[size]{}; 
	int front{ -1 }; 
	int rear{ -1 };
};

#endif /*QUEUE_H_*/