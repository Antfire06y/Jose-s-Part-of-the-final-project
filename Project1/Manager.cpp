#include "Manager.h"
#include "Employee2.h"
#include <fstream>
#include <time.h>

using namespace std;

Manager::Manager() {
	P1 = "";
}
Manager::Manager(string P1) {
	this->P1 = P1;
}
Employee2 Manager::AddEmployee() {
	srand(NULL);
	string password;
	string name;
	//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
	string firstName;
	string lastName;
	string role;
	double salary;
	int hours;
	int id = 1000 % rand() + 2000;
	//ask user for new employees password, name, and role. Then make new employee object from these inputs, and return it. Also save to the file this new employee
	cout << "Set employee password: " << endl;
	cin >> password;
	cout << "Enter employee name:" << endl;
	cin >> firstName >> lastName;
	name += firstName + " " + lastName;
	cout << "Enter the employees role: " << endl;
	cin >> role;
	cout << "Enter the salary" << endl;
	cin >> salary;
	cout << "Enter the working hours" << endl;
	cin >> hours;
	cout << name << endl << password << endl << role << endl << "Hours: " << hours << endl << "Salary per hour: " << salary << endl << "Id=" << id;
	Employee2 employeeToAdd(password, id, role, hours, salary, name);
	SaveEmployeeToFile(employeeToAdd);
	return employeeToAdd;
}
void Manager::ViewEmployees(vector<Employee2> employees) {
	for (int i = 0; i < employees.size(); i++) {
		cout << "I.D= " << employees[i].getID() << endl;
		cout << "Name= " << employees[i].getn() << endl <<"Password= " << employees[i].getPasW() << endl <<"Role: " << employees[i].getRole() << endl;
		cout << "Salary: " << employees[i].getSalary() << endl << "Hours: " << employees[i].getH() << endl;
	}
}

void Manager::EditEmployees(vector<Employee2> employees, string editOrRemove) {
	int id;
	int index;
	bool found = false;
	string password;
	//change colour of output window and text depending on if editing or removing
	if (editOrRemove == "edit") {
		system("Color E0");
	}
	else if (editOrRemove == "remove") {
		system("Color C0");
	}
	//Ask for employee id
	cout << "Enter employees ID: " << endl;
	cin >> id;
	cout << "Enter the password" << endl;
	cin >> password;



	//Search array for employee id, if found return index of employee
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getPasW() == password) {
			index = i;
			found = true;
			break;
		}
	}

	//if the employee was found, ask for futher input
	if (found == true) {
		string input;
		//if editing, ask what the user wants to edit
		if (editOrRemove == "edit") {

			cout << "Employee to edit: " << employees[index].getn() << endl;
			cout << "What to edit? " << endl;
			cout << "1. Name" << endl;
			cout << "2. Password" << endl;
			cout << "3. Job" << endl;

			cin >> input;
			if (input == "1") {
				//Change the name of the index of the account the user wants to change
				string firstName;
				string lastName;
				string name;
				cout << "Enter the new name: " << endl;
				cin >> firstName >> lastName;
				name = firstName + " " + lastName;
				employees[index].setN(name);
			}
			else if (input == "2") {
				//Change the password of the account of index the user wants to change 
				string password;
				cout << "Enter the new password: " << endl;
				cin >> password;
				employees[index].setPasW(password);
			}
			else if (input == "3") {
				//Change the job [or role] of the account of index chosen by user
				string job;
				cout << "Enter the new job: " << endl;
				cin >> job;
				employees[index].setRole(job);
			}
			else {
				//if user chooses other invalid input, let them know, and break out of method
				cout << "Invalid input." << endl;
				return;
			}
		}
		else if (editOrRemove == "remove") {
			//Alternatively, if not editing but removing employees
			string removeInput;
			//Ask for confirmation they want to remove an employee
			cout << "Employee to remove: " << employees[index].getn() << endl;
			cout << "Are you sure you want to remove them? (y/n)" << endl;
			cin >> removeInput;
			if (removeInput == "y" or removeInput == "Y") {
				cout << "Removed " << employees[index].getn() << endl;
				//erase the employee at index found. vector.erase() method takes in a pointer value, so have to use vector.begin() then add the index
				employees.erase(employees.begin() + index);
			}
			else if (removeInput == "n" or removeInput == "N") {
				cout << "Cancelled remove." << endl;
				return;
			}
			else {
				cout << "Invalid input. Noone was removed." << endl;
				return;
			}
		}
		//Once employee is edited or removed, rewrite the file with new data
		OverwriteSaveFile(employees);
	}
	else {
		cout << "Could not find that id." << endl;
	}
}

void Manager::OverwriteSaveFile(vector<Employee2> employees) {
	fstream output;
	output.open("EmployeeData.txt", ios::out);
	for (int i = 0; i < employees.size(); i++) {
		output << employees[i].getPasW() << " " << employees[i].getn() << " " << employees[i].getRole() << endl;
	}
	output.close();
}







vector<Employee2> Manager::LoadEmployees(){
vector<Employee2> employees;
fstream input;
input.open("EmployeeData.txt");
if (input.fail()) {
	cout << "Could not open save file." << endl;
}
else {
	//Keep looping until end of file, and read the data from file one word at a time. Create the employee objects from this file data, and pushback to employee vector each object
	while (!input.eof()) {
		int id;
		int hours;
		double salary;
		string name;
		string firstName;
		string lastName;
		string role;
		string password;
		
		input >> salary;
		input >> id;
		input >> hours;
		input >> password;
		input >> firstName;
		input >> lastName;
		input >> role;
		name = firstName + " " + lastName;
		Employee2 employee(password,id, role, hours, salary, name);
		employees.push_back(employee);
	}
}
//close file
input.close();
return employees;
}
void Manager::SetP1(string P1) {
	this->P1 = P1;
}
string Manager::getP1() const {
	return P1;
}
void Manager::SaveEmployeeToFile(Employee2 employee) {
	//fstream is object for outputting and inputting
	fstream output;
	//ios::app opens the file without overwriting, and appends the data to the end of the file
	output.open("EmployeeData.txt", ios::app);
	//write to the file employee password, name, and role
	output << employee.getPasW() << " " << employee.getn() << " " << employee.getRole() << endl;
	output.close();
}

