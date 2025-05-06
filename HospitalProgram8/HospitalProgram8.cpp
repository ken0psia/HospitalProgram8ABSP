//Sandra Pacheco & Angel Baldovinos - Program 8 (Hospital) - COMP-SCI 201R - Section 4
//Created: April 29, 2025 - Last Modified: May 6, 2025
//Sandra: File I/O, UI & Main
//Angel: Linked List & Classes
//Google Document of all detailed roles: https://docs.google.com/document/d/1rPUX-aEJ7NB56Tb-OtkPeiN6mJh1FOM29A1jtyxWHDQ/edit?usp=sharing

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Clinic.h"
using namespace std;

// Declare clinics
Clinic heart, pulmonary, plastic;

// Helper function: check if a string is numeric
bool isNumeric(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

static void loadInitialPatients(const string filename, ofstream& logFile) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string clinicCode, fname, lname, ssnStr;
        getline(ss, clinicCode, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, ssnStr);

        if (!isNumeric(ssnStr)) {
            logFile << "ERROR: Invalid SSN for " << fname << " " << lname << " (" << ssnStr << ")\n";
            continue;
        }

        int ssn = stoi(ssnStr);
        Patient newP = { fname, lname, ssn, 'R' };

        if (clinicCode == "HC") {
            if (heart.getLength() < 10) {
                heart.pushToEnd(newP);
                logFile << "Heart Clinic Patient (Regular): " << fname << " " << lname << " was added.\n";
            }
            else {
                logFile << "ERROR: Heart Clinic full for " << fname << " " << lname << "\n";
            }
        }
        else if (clinicCode == "PC") {
            if (pulmonary.getLength() < 10) {
                pulmonary.pushToEnd(newP);
                logFile << "Pulmonary Clinic Patient (Regular): " << fname << " " << lname << " was added.\n";
            }
            else {
                logFile << "ERROR: Pulmonary Clinic full for " << fname << " " << lname << "\n";
            }
        }
        else if (clinicCode == "PSC") {
            if (plastic.getLength() < 10) {
                plastic.pushToEnd(newP);
                logFile << "Plastic Surgery Clinic Patient (Regular): " << fname << " " << lname << " was added.\n";
            }
            else {
                logFile << "ERROR: Plastic Surgery Clinic full for " << fname << " " << lname << "\n";
            }
        }
        else {
            logFile << "ERROR: Invalid clinic code for " << fname << " " << lname << ": " << clinicCode << "\n";
        }
    }

    inFile.close();
}

void departmentMenu(Clinic& selectedClinic, ofstream& logFile, int clinicID, const string& clinicName) {
    int choice;
    do {
        cout << "\nWelcome to the " << clinicName << " Clinic\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Critical Patient\n";
        cout << "3. Take Patient for Operation\n";
        cout << "4. Cancel Patient\n";
        cout << "5. List All Patients\n";
        cout << "6. Exit Department\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            selectedClinic.addPatient(logFile, clinicID);
            break;
        case 2:
            selectedClinic.addCriticalPatient(logFile, clinicID);
            break;
        case 3:
            selectedClinic.operatePatient(clinicID);
            break;
        case 4: {
            int ssn;
            cout << "Enter SSN to cancel: ";
            cin >> ssn;
            selectedClinic.cancelPatient(ssn);
            break;
        }
        case 5:
            selectedClinic.listPatients();
            break;
        }
    } while (choice != 6);
}

void writeRemainingPatientsToFile(const string& filename, Clinic& clinic, const string& code) {
    ofstream outFile(filename, ios::app); // append mode so we can call it 3 times

    Node* current = clinic.getHead(); // We’ll expose the head pointer temporarily

    while (current != nullptr) {
        outFile << code << ","
            << current->data.fname << ","
            << current->data.lname << ","
            << current->data.ssn << "\n";
        current = current->next;
    }

    outFile.close();
}

int main()
{
    ofstream transaction("transaction.txt"); // log file
    loadInitialPatients("patient.csv", transaction);

    //Main menu
    int departmentChoice;
    do {
        cout << "\n---KC RESEARCH HOSPITAL---\n";
        cout << "1. Heart Clinic\n";
        cout << "2. Pulmonary Clinic\n";
        cout << "3. Plastic Surgery\n";
        cout << "4. Quit\n";
        cout << "Select department: ";
        cin >> departmentChoice;

        switch (departmentChoice) {
        case 1:
            departmentMenu(heart, transaction, 1, "Heart");
            break;
        case 2:
            departmentMenu(pulmonary, transaction, 2, "Pulmonary");
            break;
        case 3:
            departmentMenu(plastic, transaction, 3, "Plastic");
            break;
        }

    } while (departmentChoice != 4);


    transaction.close();

    // Write remaining patients to file at the end of the day
    writeRemainingPatientsToFile("end_of_day.csv", heart, "HC");
    writeRemainingPatientsToFile("end_of_day.csv", pulmonary, "PC");
    writeRemainingPatientsToFile("end_of_day.csv", plastic, "PSC");
    return 0;
}

