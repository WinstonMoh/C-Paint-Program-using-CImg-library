// Queue.h
// Queue class template
#ifndef QUEUE_H
#define QUEUE_H

#include "QNode.h"
using namespace std;

template <typename T>
class Queue
   {
      public:
               Queue();
               Queue(T);
               ~Queue();
               Queue(const Queue &);
               Queue& operator=(const Queue &q);

               void enQ(T);
               void deQ(T &);
               bool isEmpty();
			   int size();
               static int getQueueCount();
               

      private:
               QNode<T> *front,*back;
               static int n;		// Number of Queue instances.
               int qsize;
   };

template <typename T>
int Queue<T>::n = 0;

// Empty constructor.
template <typename T>
Queue<T>::Queue()
   {
      front = back = NULL;
      n++;
      qsize = 0;
   }

// Constructor with node(s).
template <typename T>
Queue<T>::Queue(T x)
   {
      front = back = new QNode<T> (x);
      n++;
      qsize = 0;
   }

// Destructor.
template <typename T>
Queue<T>::~Queue()
	{
		n--;
		T x;	//create dummy variable.
		while (!isEmpty())
			deQ(x);	//deQ into dummy variable.
	}

// Copy constructor.
template <typename T>
Queue<T>::Queue(Queue<T> const &other)
	{
		n++;
		qsize = 0;
		front = back = NULL;
		//size = 0;
		for (QNode<T> *cur = other.front; cur!=NULL; cur = cur->next)
			enQ(cur->data); 
	}

// Assignment operator.
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T> const &other)
	{
	T x; 	//dummy variable.
	if (this != &other)
	{
		QNode<T> *temp = other.front;
		while (!isEmpty()) {deQ(x);}
		while (temp != NULL)
		{
			enQ(temp->data);
			temp = temp->next;
		}
	}
	return *this;
	}

template <typename T>
void Queue<T>::enQ(T x)
	{
		if (isEmpty())
			{
				//create the first node in the Queue;
				front = new QNode<T> (x);
				back = front;
			}
		else 
		{
			//append at the end of the Queue.
			back->next = new QNode<T> (x);
			back = back->next;
		}
		qsize++;
	}
	
template <typename T>
void Queue<T>::deQ(T &x)
	{
		if (!isEmpty())
		{		
			x = (*front).data;
			QNode<T> *t = front;
			front = (*t).next;
			delete t;
			qsize--;
			if (front == NULL)	
				{
					back = NULL;
				}		
		}
	}

template <typename T>
bool Queue<T>::isEmpty()
	{
		return (back==NULL && front==NULL);
	}

// Return number of Queue instances.
template <typename T>
int Queue<T>::getQueueCount()
	{
		return n;
	}

// return size of queue.
template <typename T>
int Queue<T>::size()
	{
		return qsize;
	}

#endif
