#pragma once
#include <string>
class Character
{
public:
	Character(const std::string&);


	void jump();
	void attack();
	void defend();

private:
	std::string name_;
};

