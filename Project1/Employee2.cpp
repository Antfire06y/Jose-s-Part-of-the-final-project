#include "Employee2.h"
#include "human.h"

using namespace std;

Employee2::Employee2() {
	password = "";
	id =1;
	role = "";
	hours = 1;
	salary = 0;
}
Employee2::Employee2(string password, int id, string role, int hours, double salary, string name) {
	this->password = password;
	this->id = id;
	this->role = role;
	this->hours = hours;
	this->salary = salary;
	this->name = name;
}
void Employee2::setRole(string role) {
	this->role = role;
}
void Employee2::setID(int id) {
	this->id = id;
}
void Employee2::setPasW(string password) {
	this->password = password;
}
void Employee2::setHours(int hours) {
	this->hours = hours;
}
string Employee2::getPasW() const {
	return password;
}
int Employee2::getH() const {
	return hours;
}
int Employee2::getID() const {
	return id;
}
string Employee2::getRole() const {
	return role;
}
void Employee2::setSalary(double salary) {
	this->salary = salary;
}
double Employee2::getSalary() const {
	return salary;
}
double Employee2::GetTotalP() const {
	return salary * hours;
}


