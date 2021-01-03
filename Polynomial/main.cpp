#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Polynomial
{
private:
	struct term
	{
		int c = 0;
		int e = 0;
		term* n = nullptr;
		term(int _c, int _e);
	};

	int n = 0;
	term* p = nullptr;
	term* t = nullptr;

	void Create(int _n);
	void Delete();
	void AddTail(int _c, int _e);

public:
	Polynomial();
	Polynomial(int _n);
	Polynomial(const Polynomial& p);

	~Polynomial();

	const Polynomial& operator=(const Polynomial& rhs);

	Polynomial operator+(const Polynomial& rhs);
	Polynomial operator-(Polynomial lhs);

	void Print();
};

int main()
{
	Polynomial p1(3);
	Polynomial p2(3);
	
	p1.Print();
	cout << " - ";
	p2.Print();

	Polynomial p3 = p1 - p2;

	p3.Print();

	return 0;
}

Polynomial::term::term(int _c, int _e)
{
	c = _c;
	e = _e;
	n = nullptr;
}

void Polynomial::Create(int _n)
{
	n = _n;

	string _c, _e;
	cout << "Enter constant and exponent: ";
	cin >> _c;
	cin >> _e;
	p = new term(stoi(_c), stoi(_e));
	t = p;

	for (int i = 0; i < n - 1; ++i)
	{
		cout << "Enter next constant and expoent: ";
		cin >> _c;
		cin >> _e;

		AddTail(stoi(_c), stoi(_e));
	}
}

void Polynomial::Delete()
{
	term* ptr = p;
	
	while (ptr != nullptr)
	{
		term* temp = ptr;
		ptr = ptr->n;
		delete temp;
	}
}

void Polynomial::AddTail(int _c, int _e)
{
	term* add = new term(_c, _e);
	t->n = add;
	t = add;
}

Polynomial::Polynomial()
{
	n = 0;
	p = nullptr;
	t = nullptr;
}

Polynomial::Polynomial(int _n)
{
	Create(_n);
}

Polynomial::Polynomial(const Polynomial& cpy)
{
	n = cpy.n;
	p = new term(cpy.p->c, cpy.p->e);
	t = p;
	
	term* ptr_c = cpy.p->n;

	while (ptr_c != nullptr)
	{
		AddTail(ptr_c->c, ptr_c->e);
		ptr_c = ptr_c->n;
	}
}

Polynomial::~Polynomial()
{
	term* ptr = p;
	
	while (ptr != nullptr)
	{
		term* temp = ptr;
		ptr = ptr->n;
		delete temp;
	}
}

const Polynomial& Polynomial::operator=(const Polynomial& rhs)
{
	Delete();

	n = rhs.n;
	p = new term(rhs.p->c, rhs.p->e);
	t = p;
	
	term* ptr_c = rhs.p->n;

	while (ptr_c != nullptr)
	{
		AddTail(ptr_c->c, ptr_c->e);
		ptr_c = ptr_c->n;
	}

	return *this;
}

Polynomial Polynomial::operator+(const Polynomial& rhs)
{
	Polynomial result;
	result.n = n + rhs.n;

	if (p->e > rhs.p->e)
		result.p = new term(p->c, p->e);
	else if (rhs.p->e > p->e)
		result.p = new term(rhs.p->c, rhs.p->e);
	else
		result.p = new term((p->c + rhs.p->c), p->e);

	result.t = result.p;

	term* ptr_r = rhs.p->n;
	term* ptr_l = p->n;

	while (ptr_l != nullptr && ptr_r != nullptr)
	{
		if (ptr_l->e > ptr_r->e)
			result.AddTail(ptr_l->c, ptr_l->e);
		else if (ptr_r->e > ptr_l->e)
			result.AddTail(ptr_r->c, ptr_r->e);
		else
			result.AddTail((ptr_l->c + ptr_r->c), ptr_l->e);

		ptr_r = ptr_r->n;
		ptr_l = ptr_l->n;
	}

	while (ptr_l != nullptr)
	{
		result.AddTail(ptr_l->c, ptr_l->e);
		ptr_l = ptr_l->n;
	}

	while (ptr_r != nullptr)
	{
		result.AddTail(ptr_r->c, ptr_r->e);
		ptr_r = ptr_r->n;
	}

	return result;
}

Polynomial Polynomial::operator-(Polynomial rhs)
{
	Polynomial result;
	result.n = n + rhs.n;

	if (p->e > rhs.p->e)
		result.p = new term(p->c, p->e);
	else if (rhs.p->e > p->e)
		result.p = new term(rhs.p->c, rhs.p->e);
	else
		result.p = new term((p->c - rhs.p->c), p->e);

	result.t = result.p;

	term* ptr_r = rhs.p->n;
	term* ptr_l = p->n;

	while (ptr_l != nullptr && ptr_r != nullptr)
	{
		if (ptr_l->e > ptr_r->e)
			result.AddTail(ptr_l->c, ptr_l->e);
		else if (ptr_r->e > ptr_l->e)
			result.AddTail(ptr_r->c, ptr_r->e);
		else
			result.AddTail((ptr_l->c - ptr_r->c), ptr_l->e);

		ptr_r = ptr_r->n;
		ptr_l = ptr_l->n;
	}

	while (ptr_l != nullptr)
	{
		result.AddTail(ptr_l->c, ptr_l->e);
		ptr_l = ptr_l->n;
	}

	while (ptr_r != nullptr)
	{
		result.AddTail(ptr_r->c, ptr_r->e);
		ptr_r = ptr_r->n;
	}

	return result;
}

void Polynomial::Print()
{
	term* ptr = p;

	while (ptr->n != nullptr)
	{
		cout << ptr->c << "x^" << ptr->e << " + ";
		ptr = ptr->n;
	}

	cout << ptr->c << "x^" << ptr->e << endl;
}