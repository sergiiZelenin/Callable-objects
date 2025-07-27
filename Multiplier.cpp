#include "Multiplier.h"

Multiplier::Multiplier(int f) : factor_(f) {}

int Multiplier::operator()(int value) const
{
	return value * factor_;
}


