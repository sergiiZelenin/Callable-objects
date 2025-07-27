#include <iostream>
#include "Character.h"

Character::Character(const std::string& name) : name_(name) {}

void Character::jump()
{
	std::cout << name_ << "  jumps...\n"; 
}

void Character::attack()
{
	std::cout << name_ << "  attacks...\n";
}

void Character::defend()
{
	std::cout << name_ << "  defends...\n";
}

