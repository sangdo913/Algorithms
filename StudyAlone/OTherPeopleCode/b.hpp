#pragma once
#include<string>
using namespace std;

class A;

class B {
public:
	A* a;
	string str;
	
	void print() const;
};

#include"a.hpp"

void B::print() const{
	cout << "--print--\nstr in class B : " << str << endl;

	if (a) {
		cout << "v in classB : " <<  a->v << endl;
	}
	cout << '\n';
}

const B operator+(const A& a1, const A& a2) {
	B res;
	cout << "B operator + (class A + class A)" << endl;
	int t[2] = { a1.v, a2.v };
	int temp = a1.v + a2.v;
	while (t[0]) {
		res.str += t[0] % 10 + '0';
		t[0] /= 10;
	}

	res.str = string(res.str.rbegin(), res.str.rend());
	string b;

	while (t[1]) {
		b += t[1] % 10 + '0';
		t[1] /= 10;
	}
	b = string(b.rbegin(), b.rend());
	res.str += " " + b;

	res.a = 0;
	return res;
}