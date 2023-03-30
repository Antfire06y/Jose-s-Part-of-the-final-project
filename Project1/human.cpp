#include "human.h"
#include <iostream>
using namespace std;


human::human() {
	name = "";
	address="";
}
human::human(string name, string address) {
	this->name = name;
	this->address = address;
}
string human::getA() const {
	return address;
}
string human::getn() const {
	return name;
}
void human::SetA(string address) {
	this->address = address;
}
void human::setN(string name) {
	this->name = name;
}