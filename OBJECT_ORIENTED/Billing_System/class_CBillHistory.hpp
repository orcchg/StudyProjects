#include <stdio.h>
#include "class_CBill.hpp"

//----------------------------------------------------------------------------
class CBillHistory
{
	public:
		CBillHistory(CBill array, int count)
		{
			callCount = count;
			costs = new double[callCount];
			
			for(int i = 0; i < callCount; ++i)
			{
				costs[i] = array.Cost();
			}
		}
		
		~CBillHistory(){}
		
		void Print();
		double TotalCost();
		
	private:
		int callCount;
		double* costs;
};

double CBillHistory::TotalCost()
{
	double cost = 0;
	
	for(int i = 0; i < callCount; ++i)
	{
		cost += costs[i];
	}
	
	return cost;
}

void CBillHistory::Print()
{
	printf("Total number of calls: %d",callCount);
	printf("\n\nTotal cost: %lf\n",TotalCost());
}