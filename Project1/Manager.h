#pragma once
#include "Employee2.h"
#include <iostream>
#include <fstream>
#include <time.h>

class Manager:public Employee2
{
private:
	string P1;
public:
	Manager();
	Manager(string P1);
	void SetP1(string P1);
	string getP1() const;
	Employee2 AddEmployee();
	void ViewEmployees(vector<Employee2> employees);
	void EditEmployees(vector<Employee2> employees, string editOrRemove);
	vector<Employee2> LoadEmployees();
	void OverwriteSaveFile(vector<Employee2> employees);
	void SaveEmployeeToFile(Employee2 employee);
		
};

