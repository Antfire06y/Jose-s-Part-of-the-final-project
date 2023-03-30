#pragma once
#include <iostream>
#include <vector>
#include "human.h"
using namespace std;
class Employee2:public human
{
protected:
	string password;
	int id;
	string role;
	double salary;
	int hours;
public:
	Employee2();
	Employee2(string password, int id, string role, int hours,double salary, string name);
	void setID(int id);
	void setPasW(string password);
	void setRole(string role);
	string getPasW()const;
	int getID() const;
	string getRole() const;
	void setHours(int hours);
	int getH() const;
	void setSalary(double salary);
	double getSalary()const;
	double GetTotalP() const;
};

