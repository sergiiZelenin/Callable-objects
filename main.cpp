#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <functional>
#include "CustomClass.h"
#include "Calculator.h"
#include "Character.h"
#include "Multiplier.h"
#include "Sorter.h"

typedef void (*fPtr)(const std::string&);


void greet(const std::string& name)
{
	std::cout << "Hello, " << name << " ! " << '\n';
}

typedef int (*funcPtr)(int, int);

void calculate(int x, int y, funcPtr operation)
{
	if (operation != nullptr)
		std::cout << operation(x, y) << '\n';
	else
		std::cout << "operation is not defined\n";
}

void calculate(int x, int y, std::function<int(int, int)> operation)
{
	if (operation != nullptr)
		std::cout << operation(x, y) << '\n';
	else
		std::cout << "operation is not defined\n";
}


void onSortComplete(const std::string& message)
{
	std::cout << "Callback: " << message << '\n';
}

using sortCallback = void (*)(const std::string&);

void SortAndNotify(std::vector<int>& data, sortCallback callback)
{
	time_t timestamp;
	time(&timestamp);
	std::cout << "Sort started..." << timestamp << '\n';
	std::sort(data.begin(), data.end());
	time(&timestamp);
	std::cout << "Sort end..." << timestamp << '\n';

	callback("Data sorting has been ended successfully!!!\n");
}


using function_pointer = void (*)();
using ActionFunc = void (CustomClass::*)();

void sayHello() { std::cout << "Hello!\n"; }
void sayGoodBye() { std::cout << "Goodbye!\n"; }
void sayHowAreYou() { std::cout << "How are you!\n"; }

using action = int (Calculator::*) (int, int);

typedef int (Calculator::* actionFunc)(int, int);

using CharacterAction = void (Character::*)();

void SortVector(std::vector<int>& v)
{
	std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
}


using sorter = bool(Sorter::*)(int, int);


void sort_array(int arr[], size_t size, Sorter* srt, sorter comparator)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (!(srt->*comparator)(arr[j], arr[j + 1]))
			{
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main()
{
	
	function_pointer actions[3];

	actions[0] = sayHello;
	actions[1] = sayGoodBye;
	actions[2] = sayHowAreYou;

	for (int i = 0; i < 3; ++i)
	{
		actions[i]();
	}

	fPtr greetPtr = greet;
	action addPtr = &Calculator::add;

	Calculator myCalc;

	greetPtr("World");

	int sum = (myCalc.*addPtr)(5, 3);
	std::cout << "sum = " << sum << '\n';


	(*greetPtr)("Donald Trump");
	
	srand(time(NULL));

	std::vector<int> numbers;

	while (numbers.size() < 100000)
	{
		numbers.push_back(rand() % 1000 + 1);
	}

	SortAndNotify(numbers, onSortComplete);

	std::cout << "Sorted vector: \n";

	for (auto element : numbers)
	{
		std::cout << element << " ";
	}

	std::cout << '\n';

	std::cout << "5 + 3 = ";

	calculate(5, 3, std::bind(&Calculator::add, &myCalc, std::placeholders::_1, std::placeholders::_1));
	
	std::cout << "5 - 3 = ";
	calculate(5, 3, std::bind(&Calculator::subtract, &myCalc, std::placeholders::_1, std::placeholders::_1)););

	std::cout << "5 * 3 = ";
	calculate(5, 3, std::bind(&Calculator::multiply, &myCalc, std::placeholders::_1, std::placeholders::_1)););

	std::cout << "5 / 3 = ";
	calculate(5, 3, std::bind(&Calculator::divide, &myCalc, std::placeholders::_1, std::placeholders::_1)););

	//next line is not compiled:
	ActionFunc method_ = &CustomClass::Method;

	Character player("Rambo");
	Character enemy("Zombie");

	std::map<std::string, CharacterAction> eventMap;

	eventMap["jump_button"] = &Character::jump;
	eventMap["attack_button"] = &Character::attack;
	eventMap["defend_button"] = &Character::defend;



	std::vector<std::string> events;
	events.push_back("jump_button");
	events.push_back("attack_button");

	for (auto event : events)
	{
		if (eventMap.count(event))
		{
			(player.*eventMap[event])();
		}
	}
	int x = 7;

	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };

	std::for_each(v.begin(), v.end(), [x](int n) {  std::cout << x << n * n << " "; });

	auto my_func = [&]() { std::cout << v[3]; };

	my_func();

	std::vector<int> numbers = { 1, 5, 2, 8, 3, 9, 4, 7, 6 };

	SortVector(numbers);

	for (auto number : numbers)
	{
		std::cout << number << " ";
	}

	std::function<void(const std::string&)> func_greeter = greet;
	func_greeter("World!!");

	std::function<int(int, int)> func_add = [](int a, int b) { return a + b; };
	std::cout << func_add(5, 3) << '\n';


	Multiplier two(2);
	std::function<int(int)> func_mult = two;

	std::cout << " 7 * 2 = " << func_mult(7) << '\n';

	return 0;
}

/*
Вказівник на метод класу - це спеціальний ти вказівника, якй зберігає не просто адресу початку коду методу, а 
зберігає інформацію, необхідну для виклику методу (!!!)з під конкретного об'єкту(!!!). 

key mapping



[capture](arguments) -> return_type
{
     ...body
};

Задача 1: Просте сортування
Умова: Дано вектор цілих чисел. Напишіть лямбда-вираз, який можна передати в std::sort 
для сортування вектора у (!!)порядку спадання.
Вхідні дані: std::vector<int> numbers = {1, 5, 2, 8, 3, 9, 4, 7, 6};
Очікуваний результат: Вектор numbers відсортований: {9, 8, 7, 6, 5, 4, 3, 2, 1}.



std::function


Мета: Написати функцію сортування (наприклад, бульбашкове сортування або сортування вибором), яка приймає масив, 
його розмір та вказівник на функцію порівняння. Це дозволить сортувати масив як за зростанням, так і за спаданням.

Вимоги:
1. Створити функцію compare_ascending(int a, int b), яка повертає true, якщо a має стояти перед b у відсортованому 
за зростанням масиві (тобто a < b), і false в іншому випадку.

2. Створити функцію compare_descending(int a, int b), яка повертає true, якщо a має стояти перед b у відсортованому 
за спаданням масиві (тобто a > b), і false в іншому випадку.

3. Оголосити тип вказівника на функцію порівняння, яка приймає два int і повертає bool.

4. Створити функцію sort_array(int arr[], int size, (вказівник на функцію порівняння) comparator).

5. У sort_array реалізувати будь - який простий алгоритм сортування, використовуючи передану функцію 
comparator для визначення порядку елементів.

6. У main створити масив, відсортувати його за зростанням, вивести, потім відсортувати його ж за спаданням і знову вивести.





*/