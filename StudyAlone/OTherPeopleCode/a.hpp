#pragma once
#include<iostream>

using namespace std;

class B;

class A {
public:
	int v;
	B* b;
	
	void print();
};

#include"b.hpp"

void A::print() {
	cout << "class A : " << v << endl;

	if (b) {
		cout << b->str << endl;
	}
}

const A operator+(B b1, B b2) {
	cout << "operator +, A" << endl;
	A res;
	res.v = b1.str[0] + b2.str[0];
	return res;
}

const B operator+(const B& b, A& a) {
	cout << "class B = class B +  class A\n";
	cout << "v in class a : " << a.v;
	cout << "\nstr in class b : " << b.str << '\n';

	B res;
	res.str = "";
	res.a = &a;
	
	int temp = a.v;

	while (temp) {
		res.str += temp % 10 + '0';
		temp /= 10;
	}

	res.str = b.str + string(res.str.rbegin(), res.str.rend());

	return res;
}