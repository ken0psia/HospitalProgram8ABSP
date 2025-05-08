#include "Clinic.h"
bool isDigits(const string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}
Clinic::Clinic() {
	maxPatients = 10;
	head = nullptr;
}

Clinic::~Clinic() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}
void Clinic::pushToFront(Patient sick) {
	Node* newNode = new Node;
	newNode->data = sick;
	newNode->next = nullptr;
	if (head == nullptr || head->data.status != 'C') {//if there are no critical patients, add to front
		newNode->next = head;
		head = newNode;
		return;
	}
	//go to the last critical patient, next is the anticipated location of new patient
	Node* current = head;
	while (current->next != nullptr && current->next->data.status == 'C') {
		current = current->next;
	}
	//insert
	newNode->next = current->next;
	current->next = newNode;
}
void Clinic::pushToEnd(Patient sick) {
	Node* newNode = new Node;
	newNode->data = sick;
	newNode->next = nullptr;
	if (this->head == nullptr) {
		this->head = newNode;
	}
	else {
		Node* current = this->head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void Clinic::addPatient(ostream& err, int selection) { 
	//selection will indicate which clinic is being used and display name of clinic in terminal
	//selection should be a main or global variable // caught from first user input
	if (getLength() >= maxPatients) {
		cout << "Clinic is full. Cannot add more patients.\n";
		return;
	}
	string ssn;
	Node* newNode = new Node;
	cout << "Enter Patient's First Name: ";
	cin >> newNode->data.fname;
	cout << "Enter Patient's Last Name: ";
	cin >> newNode->data.lname;
	cout << "Enter Patient's SSN: ";
	cin >> ssn;
	while (!isDigits(ssn)) {
		cout << "Invalid SSN, Please reenter valid SSN: ";
		cin >> ssn;
	}
	newNode->data.ssn = stoi(ssn);
	newNode->data.status = 'R';
	switch (selection) {
	case 1:
		cout << "Heart Clinic Patient (Regular): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	case 2:
		cout << "Pulmonary Clinic Patient (Regular): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	case 3:
		cout << "Plastic Surgery Clinic Patient (Regular): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	default:
		err << "Invalid clinic selection at addPatient.\n";
		delete newNode;
		return;
	}

	this->pushToEnd(newNode->data);
	delete newNode;
}

void Clinic::addCriticalPatient(ostream& err, int selection) {
	//selection will indicate which clinic is being used and display name of clinic in terminal
	//selection should be a main or global variable // caught from first user input
	if (getLength() >= maxPatients) {
		cout << "Clinic is full. Cannot add more patients.\n";
		return;
	}
	string ssn;
	Node* newNode = new Node;
	cout << "Enter Patient's First Name: ";
	cin >> newNode->data.fname;
	cout << "Enter Patient's Last Name: ";
	cin >> newNode->data.lname;
	cout << "Enter Patient's SSN: ";
	cin >> ssn;
	while (!isDigits(ssn)) {
		cout << "Invalid SSN, Please reenter valid SSN: ";
		cin >> ssn;
	}
	newNode->data.ssn = stoi(ssn);
	newNode->data.status = 'C';
	switch (selection) {
	case 1:
		cout << "Heart Clinic Patient (Critical): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	case 2:
		cout << "Pulmonary Clinic Patient (Critical): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	case 3:
		cout << "Plastic Surgery Clinic Patient (Critical): " << newNode->data.fname <<
			" " << newNode->data.lname << " was added to the waiting room." << endl;
		break;
	default:
		err << "Invalid clinic selection at addPatient.\n";
		delete newNode;
		return;
	}

	this->pushToFront(newNode->data);
	delete newNode;
}
void Clinic::operatePatient(int selection) {
	//selection will indicate which clinic is.... u get the point.
	if (head == nullptr) {
		cout << "No patients in the waiting room.\n";
		return;
	}
	else {
		Node* temp = head;
		head = head->next;
		switch (selection) {
		case 1:
			cout << "Heart Clinic Patient: " << temp->data.fname << " " << temp->data.lname << " was taken to the operating room." << endl;
			break;
		case 2:
			cout << "Pulmonary Clinic Patient: " << temp->data.fname << " " << temp->data.lname << " was taken to the operating room." << endl;
			break;
		case 3:
			cout << "Plastic Surgery  Patient: " << temp->data.fname << " " << temp->data.lname << " was taken to the operating room." << endl;
			break;
		}
		delete temp;
	}
}
void Clinic::cancelPatient(int ssn) {
	if (head == nullptr) {
		cout << "No patients in the waiting room." << endl;
		return;
	}
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr && current->data.ssn != ssn) {//copilot
		previous = current;
		current = current->next;
	}

	if (current == nullptr) {
		cout << ssn << " not found in the waiting room." << endl;
		return;
	}

	if (previous == nullptr) {
		// The patient to remove is the first in the list
		head = current->next;
	} else {
		// The patient to remove is in the middle or end of the list
		previous->next = current->next;
	}

	cout << current->data.fname<< " " << current->data.lname << " has been removed from the waiting room." << endl;
	delete current;
}

void Clinic::listPatients() {
	if (head == nullptr) {
		cout << "No patients in the waiting room." << endl;
		return;
	}
	Node* current = head;
	cout << "Patient List" << endl;
	while (current != nullptr) {
		cout << setw(10) << current->data.fname << setw(15) << current->data.lname << setw(5)
			<< current->data.ssn << setw(5) << current->data.status << endl;
		current = current->next;
	}
}
int Clinic::getLength() {
	Node* current = head;
	int length = 0;
	while (current != nullptr) {
		length++;
		current = current->next;
	}
	return length;
}

