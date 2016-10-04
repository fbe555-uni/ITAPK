#include <iostream>
#include <list>
#include <functional>

#include "SmallObjectAllocator.hpp"

int main()
{
	{
		std::list<int, SmallObjectAllocator<int> > l;

		std::cout << "inserting...";
		for( int i = 0; i < 1000000; i++ )
			l.push_back( i );
		std::cout << "done" << std::endl;

		l.reverse();

		std::cout << "destroying list ... ";
	}
	std::cout << "done" << std::endl;
}
