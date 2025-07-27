#pragma once
class Multiplier
{
public:
	Multiplier(int f);
	int operator()(int value) const;
private:
	int factor_;
};

