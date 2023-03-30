#pragma once
#include <iostream>
using namespace std;
class human
{
public:
	human();
	human(string name, string address);
	string getn() const;
	string getA() const;
	void setN(string name);
	void SetA(string address);
protected:
	string name;
	string address;
};

