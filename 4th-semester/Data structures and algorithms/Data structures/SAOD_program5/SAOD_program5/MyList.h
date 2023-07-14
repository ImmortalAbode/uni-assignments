#ifndef MYLIST_H_
#define MYLIST_H_

const int necessity{ 1 };
const int size{ 10 + necessity };

struct List
{
	int data[size]{};
	int index[size]{};
};

#endif /*MYLIST_H_*/