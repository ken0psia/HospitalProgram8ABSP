#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Patient {
	string fname;
	string lname;
	int ssn;
	char status;
};

struct Node {
	Patient data;
	Node* next;
};


class Clinic {
public:
	//for credit
	Clinic();
	~Clinic();
	void addPatient(ostream& err, int selection);
	void addCriticalPatient(ostream& err, int selection);
	void operatePatient(int selection);
	void cancelPatient(int ssn);
	void listPatients();

	//for functionality
	void pushToEnd(Patient sick);
	void pushToFront(Patient sick);
	int getLength();


	Node* getHead() { return head; }

private:
	int maxPatients;
	Node* head;
};

