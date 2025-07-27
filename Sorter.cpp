#include "Sorter.h"

bool Sorter::compare_ascending(int a, int b) const
{
	return a < b;
}

bool Sorter::compare_descending(int a, int b) const
{
	return a > b;
}