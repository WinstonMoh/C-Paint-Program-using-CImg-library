/* Triple class.
 * To hold Pairs with their respective distances.
 */
#ifndef TRIPLE_H
#define TRIPLE_H
#include "Pair.h"
using namespace std;		// Don't forget to include this.

/* Definition part.
 * Class to add distance to Pair.
 * */
template <typename T>
class Triple : public Pair<T>		
   {
      public:
               Triple();
               Triple(const Triple &); //copy constructor.
               ~Triple();		//copy destructor.
               Triple(T,T,unsigned int);

               unsigned int getDistance();
               void setDistance(unsigned int);
               
               static int getTripleCount();

      private:
               unsigned int distance;
               static int tpc; //Triple pair counter.
   };


/* Implementation part.
 * */
template <typename T>
int Triple<T>::tpc=0;   // Initialize tpc to 0.
 
//default constructor.
template <typename T>
Triple<T>::Triple():Pair<T>()
	{
		distance = 0;
		tpc++;
	}

//Triple Pair copy constrcutor.
template <typename T>
Triple<T>::Triple(const Triple &other):Pair<T>(other) 
	{
		distance = other.distance;
		tpc++;
	}

//Triple Pair copy destructor.
template <typename T>
Triple<T>::~Triple()
	{
		tpc--;
	}

//constructor with distance d.
template <typename T>
Triple<T>::Triple(T x, T y, unsigned int d):Pair<T>(x, y)
	{
		distance = d;
		tpc++;
	}

//return distance value.
template <typename T>
unsigned int Triple<T>::getDistance()
	{
		return distance;
	}
 
//set pair distance.
template <typename T>
void Triple<T>::setDistance(unsigned int d)
	{
		distance = d;
	}
 
// get number of Triple pairs created.
template <typename T>
int Triple<T>::getTripleCount()
	{
		return tpc;
	}

#endif
