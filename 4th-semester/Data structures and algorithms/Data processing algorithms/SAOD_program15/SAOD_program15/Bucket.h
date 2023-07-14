#ifndef BUCKET_H_
#define BUCKET_H_

struct Node
{
	int data{};
	Node* next{ nullptr };
};

struct Bucket
{
	Node* head_ptr{ nullptr };
	Node* last_element{ nullptr };
};

#endif /*BUCKET_H_*/
