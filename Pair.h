// Pair.h
// Pair class template
#ifndef PAIR_H
#define PAIR_H

using namespace std;

template <typename T>
class Pair
   {
      public:
               Pair();
               Pair(T,T);
               
               ~Pair();
               Pair(const Pair &);
               Pair& operator=(const Pair &);
               
               T getFirst();
               T getSecond();
               
               void setFirst(T);
               void setSecond(T);
               
               void setFS(T,T);
               void getFS(T&,T&);
               
               static int getPairCount();
               
      private:
               T first,second;
               
               static int pairct;
               
   };

template <typename T>
int Pair<T>::pairct = 0;

// Constructor.
template <typename T>
Pair<T>::Pair()
	{
		pairct++;
	}
	
template <typename T>	
Pair<T>::Pair(T x, T y)
	{
		first = x;
		second = y;
		pairct++;
	}

// Destructor.
template <typename T>
Pair<T>::~Pair()
	{
		pairct--;
	}

// Copy constructor.		
template <typename T>
Pair<T>::Pair(const Pair<T> &other)
	{
		first = other.first;
		second = other.second;
		pairct++;
	}

// Assignment operator.
template <typename T>
Pair<T>& Pair<T>::operator=(const Pair<T> &rhs)
	{
		if (this == &rhs)
			return *this;
		else 
		{
			//first = NULL;  //Don't know how to nuke lhs but code works!
			//second = NULL;
			first = rhs.first;
			second = rhs.second;
			return *this;
		}
	}

template <typename T>	
T Pair<T>::getFirst()
	{
		return first;
	}
	
template <typename T>
T Pair<T>::getSecond()
	{
		return second;
	}

template <typename T>
void Pair<T>::setFirst(T x)
	{
		first = x;
	}

template <typename T>
void Pair<T>::setSecond(T x)
	{
		second = x;
	}
	
template <typename T>
void Pair<T>::setFS(T x, T y)
	{
		first = x;
		second = y;
	}	
	
template <typename T>
void Pair<T>::getFS(T &x, T &y)
	{
		x = first;
		y = second;
	}		

template <typename T>
int Pair<T>::getPairCount()
	{
		return pairct;
	}
	
#endif	
	
	
