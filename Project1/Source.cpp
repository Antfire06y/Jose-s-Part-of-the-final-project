#include <iostream>
//fstream for file input and output
#include <fstream>
#include <vector>
#include <string>
//stdlib.h for changing colour of terminal and text (purely cosmetic)
#include <stdlib.h>
using namespace std;

//simple class for testing purposes -> probably needs to be expanded with more data fields, functions, and expanded into more inherited classes
class Employee {
	string password;
	string name;
	string role;
public:
	//constructor for data fields
	Employee(string password, string name, string role) {
		this->password = password;
		this->name = name;
		this->role = role;
	}
	//default constructor with blank datafields
	Employee() {
		password = "";
		name = "";
		role = "";
	}

	//setters and getters for data fields
	void setName(string name) {
		this->name = name;
	}

	void setRole(string role) {
		this->role = role;
	}

	void setPassword(string password) {
		this->password = password;
	}

	string getName() {
		return name;
	}

	string getRole() {
		return role;
	}

	string getPassword() {
		return password;
	}
};

//Method used to save new employee into file. Only used when adding an employee, not when editing or erasing current employees. 
//This method just appends to the end of existing file the new employee, rather than rewriting whole file
void SaveEmployeeToFile(Employee employee) {
	//fstream is object for outputting and inputting
	fstream output;
	//ios::app opens the file without overwriting, and appends the data to the end of the file
	output.open("EmployeeData.txt", ios::app);
	//write to the file employee password, name, and role
	output << employee.getPassword() << " " << employee.getName() << " " << employee.getRole() << endl;
	output.close();
}

//Other method used for saving. This one is used for when editing or deleting current employees. This method rewrites the entire file from scratch.
void OverwriteSaveFile(vector<Employee> employees) {
	fstream output;
	output.open("EmployeeData.txt", ios::out);
	for (int i = 0; i < employees.size(); i++) {
		output << employees[i].getPassword() << " " << employees[i].getName() << " " << employees[i].getRole() << endl;
	}
	output.close();
}

//Method to add new employees. Needs to be changed to only be accessible to managers
Employee AddEmployee() {
	string password;
	string name;
	//Name has to be combined from first and last name since cin only takes one word at a time. Alternatively getline can be used, but can be finicky when combined with cin.
	string firstName;
	string lastName;
	string role;
	//ask user for new employees password, name, and role. Then make new employee object from these inputs, and return it. Also save to the file this new employee
	cout << "Set employee password: " << endl;
	cin >> password;
	cout << "Enter employee name:" << endl;
	cin >> firstName >> lastName;
	name += firstName + " " + lastName;
	cout << "Enter the employees role: " << endl;
	cin >> role;
	cout << name << endl << password << endl << role << endl;
	Employee employeeToAdd(password, name, role);
	SaveEmployeeToFile(employeeToAdd);
	return employeeToAdd;
}

//Loop through the employee array, and print out each employee and their datafields
void ViewEmployees(vector<Employee> employees) {
	for (int i = 0; i < employees.size(); i++) {
		cout << employees[i].getName() << " " << employees[i].getPassword() << " " << employees[i].getRole() << endl;
	}
}

//Used for both editing and deleting employees. Whether editing or removing is decided from the 'editOrRemove' parameter
void EditEmployees(vector<Employee> employees, string editOrRemove) {
	string id;
	int index;
	bool found = false;
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



	//Search array for employee id, if found return index of employee
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getPassword() == id) {
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

			cout << "Employee to edit: " << employees[index].getName() << endl;
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
				employees[index].setName(name);
			}
			else if (input == "2") {
				//Change the password of the account of index the user wants to change 
				string password;
				cout << "Enter the new password: " << endl;
				cin >> password;
				employees[index].setPassword(password);
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
			cout << "Employee to remove: " << employees[index].getName() << endl;
			cout << "Are you sure you want to remove them? (y/n)" << endl;
			cin >> removeInput;
			if (removeInput == "y" or removeInput == "Y") {
				cout << "Removed " << employees[index].getName() << endl;
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

//Load employee vector from the file, if the file exists
vector<Employee> LoadEmployees() {
	vector<Employee> employees;
	fstream input;
	input.open("EmployeeData.txt");
	if (input.fail()) {
		cout << "Could not open save file." << endl;
	}
	else {
		//Keep looping until end of file, and read the data from file one word at a time. Create the employee objects from this file data, and pushback to employee vector each object
		while (!input.eof()) {
			string name;
			string firstName;
			string lastName;
			string role;
			string password;
			input >> password;
			input >> firstName;
			input >> lastName;
			input >> role;
			name = firstName + " " + lastName;
			Employee employee(password, name, role);
			employees.push_back(employee);
		}
	}
	//close file
	input.close();
	return employees;
}

//main loop that all other functions are childed to
void MainLoop() {
	while (true) {
		system("Color 9F");
		//vector of all employees. Filled by the file, if the file exists
		vector<Employee> employees = LoadEmployees();
		//prompt user for input
		cout << "1: Add Employee" << endl;
		cout << "2: Remove Employee" << endl;
		cout << "3: Edit Employee" << endl;
		cout << "4: View Employees" << endl;
		string input;
		cin >> input;
		if (input == "1") {
			employees.push_back(AddEmployee());
		}
		else if (input == "2") {
			EditEmployees(employees, "remove");
		}
		else if (input == "3") {
			EditEmployees(employees, "edit");
		}
		else if (input == "4") {
			ViewEmployees(employees);
		}
		else {

		}
	}

}

int main() {
	//Changes colour of output background and text, respectively
	/* 1-blue 2-green 3-aqua 4-red 5-purple 6-yellow 7-white 8-gray 9-lightblue 0-black A-lightgreen B-lightaqua C-lightred D-lightpurple E-lightYellow F-brightwhite
	*/
	//3F is nice home menu colouring
	//9F is also nice home colouring
	//C is nice background colour for remove employee
	//E is relatively nice colour for viewing things
	MainLoop();
	/*
	fstream employeeData;
	employeeData.open("EmployeeData.txt");
	employeeData.close();
	*/
}