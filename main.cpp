#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class MyExcept1 {};

class MyExcept2
{
	string msg;
public:
	MyExcept2(const string& s) : msg(s) {}
	const char* message() const { return msg.c_str(); }
};

class MyExcept3 : public invalid_argument
{
	int a, b, c;
public:
	MyExcept3(const string msg, int aa, int bb, int cc) : invalid_argument(msg) {}
	bool arg1() const { return a; }
	bool arg2() const { return b; }
	bool arg3() const { return c; }
};

void GetPerimeter1(int a, int b, int c)
{
	int p = a + b + c;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c 
		|| b >= a + c || c >= a + b || cin.fail())
		cerr << "Произошло исключение в функции GetPerimeter1" << endl;
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void GetPerimeter2(int a, int b, int c) throw(int)
{
	int p;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c
		|| b >= a + c || c >= a + b || cin.fail())
		throw - 1;
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void GetPerimeter3(int a, int b, int c) throw(invalid_argument)
{
	int p;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c
		|| b >= a + c || c >= a + b || cin.fail())
		throw invalid_argument("Треугольник не существует!");
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void GetPerimeter4_1(int a, int b, int c) throw(MyExcept1)
{
	int p;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c
		|| b >= a + c || c >= a + b || cin.fail())
		throw MyExcept1();
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void GetPerimeter4_2(int a, int b, int c) throw(MyExcept2)
{
	int p;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c
		|| b >= a + c || c >= a + b || cin.fail())
		throw MyExcept2("Треугольник не существует!");
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void GetPerimeter4_3(int a, int b, int c) throw(MyExcept3)
{
	int p;
	if (a <= 0 || b <= 0 || c <= 0 || a >= b + c
		|| b >= a + c || c >= a + b || cin.fail())
		throw MyExcept3("Треугольник не существует!", a, b, c);
	else
	{
		p = a + b + c;
		cout << "Периметр треугольника: " << p;
	}
}

void launcher(void (*func)(int, int, int))
{
	int a, b, c;
	cout << "Введите a: ";
	cin >> a;
	cout << "Введите b: ";
	cin >> b;
	cout << "Введите c: ";
	cin >> c;
	func(a, b, c);
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		launcher(GetPerimeter1);
	}

	catch (...)
	{
		cout << "Произошло исключение в функции GetPerimeter1" << endl;
	}

	try
	{
		launcher(GetPerimeter2);
	}

	catch (int)
	{
		cout << "Произошло исключение в функции GetPerimeter2" << endl;
	}

	try
	{
		launcher(GetPerimeter3);
	}

	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		launcher(GetPerimeter4_1);
	}

	catch (MyExcept1)
	{
		cout << "Произошло исключение MyExcept1 в функции GetPerimeter4_1" << endl;
	}

	try
	{
		launcher(GetPerimeter4_2);
	}
	catch (MyExcept2& e)
	{
		cout << e.message() << endl;
	}

	try
	{
		launcher(GetPerimeter4_3);
	}

	catch (MyExcept3& e)
	{
		cout << e.what() << " " << e.arg1() << " " << e.arg2() << " " << e.arg3() << endl;
	}
}
