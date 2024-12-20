//Elizabeth Palmer
//Contact List Project
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include<algorithm>
#include "stringmanip.hpp" //Sourced from Dr. Foust -- includes trim() and lowercase(), which are used throughout the program
using namespace std;

struct Contact {
	string lastName;
	string firstName;
	string phone;
	string email;
};

struct ContactList {
	vector<Contact> contacts;
};
bool contactExists(const ContactList& list, const string& firstName, const string& lastName) {
	bool exists = false;
	string lowerFirst = lowercase(firstName);
	string lowerLast = lowercase(lastName);
	for (auto contact : list.contacts) {
		if (lowercase(contact.firstName) == lowerFirst && lowercase(contact.lastName) == lowerLast) {
			exists = true;
		}
	}
	return exists;
}
Contact storeContactInfo() {
	Contact newContact;
	string input;
	cout << "Last Name: " << endl;
	getline(cin, input);
	newContact.lastName = trim(input);
	cout << "First Name: " << endl;
	getline(cin, input);
	newContact.firstName = trim(input);
	cout << "Phone: " << endl;
	getline(cin, input);
	newContact.phone = trim(input);
	cout << "Email: " << endl;
	getline(cin, input);
	newContact.email = trim(input);

	return newContact;
}
void add(ContactList& list) {
	
	Contact newContact = storeContactInfo();
	
	if (newContact.firstName.size() > 0 && newContact.lastName.size() > 0) {
		if (contactExists(list, newContact.firstName, newContact.lastName)) {
			cout << "\nAdd contact failed: contact already exists\n" << endl;
		}
		else {
			list.contacts.push_back(newContact);
			cout << "\nContact added\n" << endl;
		}
	}
	else {
		cout << "\nInvalid contact data\n" << endl;
	}
	
}

void show(string firstName, string lastName, ContactList & list) {
	string lowerFirst = lowercase(firstName);
	string lowerLast = lowercase(lastName);
	if (contactExists(list, firstName, lastName)) {
		for (auto contact : list.contacts) {
			if (lowercase(contact.firstName) == lowerFirst && lowercase(contact.lastName) == lowerLast) {
				cout << "Last Name:  " << contact.lastName << endl;
				cout << "First Name: " << contact.firstName << endl;
				cout << "Phone:      " <<  contact.phone << endl;
				cout << "Email:      " <<contact.email << '\n'<<endl;
			}
		}
	}
	else {
		cout << '\n'<<firstName << " " << lastName << " not found" << endl;
	}
}

void listNames(const ContactList& list) {
	int nameCount = 0;
	for (auto contact : list.contacts) {
		cout << contact.firstName << " " << contact.lastName << endl;
		nameCount++;
		
	}
	if (nameCount == 0) {
		cout << "No contacts found" << endl;
	}
	cout << endl;
	
}

void update(ContactList& list) {
	Contact updated = storeContactInfo();
	string firstName = updated.firstName;
	string lastName = updated.lastName;
	if (!contactExists(list, firstName, lastName)) {
		cout << "\nUpdate contact failed: contact does not exist\n" << endl;
	}
	if (updated.firstName.size() > 0 && updated.lastName.size() > 0) {
		string lowerFirst = lowercase(firstName);
		string lowerLast = lowercase(lastName);
		for (auto& contact : list.contacts) {
			if (lowercase(contact.firstName) == lowerFirst && lowercase(contact.lastName) == lowerLast) {
				contact.phone = updated.phone;
				contact.email = updated.email;
				cout << "\nContact updated\n" << endl;
			}
		}
	}
	else {
		cout << "Invalid contact data" << endl;
	}
}
bool compareByFirst(const Contact& a, const Contact& b) {

	bool isFirst = false;
	if (a.firstName < b.firstName) {
		isFirst = true;
	}
	return isFirst;
}

bool compareByLast(const Contact& a, const Contact& b) {
	bool isFirst = false;
	if (a.lastName < b.lastName) {
		isFirst = true;
	}
	return isFirst;
}

bool compareByPhone(const Contact& a, const Contact& b) {
	bool isFirst = false;
	if (a.phone < b.phone) {
		isFirst = true;
	}
	return isFirst;
}

bool compareByEmail(const Contact& a, const Contact& b) {
	bool isFirst = false;
	if (a.email < b.email) {
		isFirst = true;
	}
	return isFirst;
}

void sortByFirst(ContactList& list) {
	stable_sort(list.contacts.begin(), list.contacts.end(), compareByFirst);
	cout << "Contacts sorted\n" << endl;
}

void sortByLast(ContactList& list) {
	stable_sort(list.contacts.begin(), list.contacts.end(), compareByLast);
	cout << "Contacts sorted\n" << endl;
}

void sortByPhone(ContactList& list) {
	stable_sort(list.contacts.begin(), list.contacts.end(), compareByPhone);
	cout << "Contacts sorted\n" << endl;
}

void sortByEmail(ContactList& list) {
	stable_sort(list.contacts.begin(), list.contacts.end(), compareByEmail);
	cout << "Contacts sorted\n" << endl;
}

bool doesContain(Contact contact, string toFind) {

	string toFindLower = lowercase(toFind);
	bool contains = false;
	if (lowercase(contact.firstName).find(toFindLower) != string::npos
		|| lowercase(contact.lastName).find(toFindLower)!= string::npos
		|| lowercase(contact.email).find(toFindLower)!= string::npos
		|| lowercase(contact.phone).find(toFindLower)!=string::npos) {
		contains = true;
	}
	return contains;
}

void findContact(ContactList& list, string toFind) {
	ContactList contactsContain;
	for (auto contact : list.contacts) {
		if (doesContain(contact, toFind)) {
			contactsContain.contacts.push_back(contact);
		}

	}

	listNames(contactsContain);
}

bool openFile(ContactList& list) {
	bool fileSuccess = true;
	ifstream fin("contacts.csv");
	if (!fin) {
		cout << "Could not open contacts.csv" << endl;
		cout << "Starting new contacts list\n" << endl;

	}
	else {

		string firstLine;
		string line;
		getline(fin, firstLine);
		firstLine = trim(firstLine);

		if (firstLine != "Last Name,First Name,Phone,Email") {
			cout << "File contacts.csv has invalid format\n" << endl;
			fileSuccess = false;

		}

		while (getline(fin, line)&&fileSuccess == true) {
			istringstream intake(line);
			Contact contact;
			getline(intake, contact.lastName, ',');
			contact.lastName = trim(contact.lastName);
			getline(intake, contact.firstName, ',');
			contact.firstName = trim(contact.firstName);
			getline(intake, contact.phone, ',');
			contact.phone = trim(contact.phone);
			getline(intake, contact.email, ',');
			contact.email = trim(contact.email);

			
			list.contacts.push_back(contact);

		}

		cout << "Read " << list.contacts.size() << " contacts from contacts.csv\n" << endl;

	}

	return fileSuccess;
	
	
}

void writeToFile(ContactList& contactList) {
	ofstream fout("contacts.csv");
	fout << "Last Name,First Name,Phone,Email\n";
	for (auto contact : contactList.contacts) {
		fout << contact.lastName 
			<< ',' 
			<< contact.firstName 
			<< ',' 
			<< contact.phone 
			<< ',' 
			<< contact.email 
			<< '\n';
	}
	cout << "Saved contacts.csv\n" << endl;
}

void readCommand(ContactList& list) {
	

	bool stop = false;

	while (!stop) {

		string line;
		if (!getline(cin, line)) {
		
			stop = true;
		}
		
		vector<string>words;
		istringstream iss(line);
		string word;
		while (iss >> quoted(word)) {
			word = trim(word);
			words.push_back(word);
		}

		if (!words.empty()) {
			if (words.size() == 1 && lowercase(words[0])=="add") {
				
				add(list);
			}
			else if (words.size() == 3 && lowercase(words[0])== "show") {

				show(words[1], words[2], list);
			}
			else if (words.size() == 1 && lowercase(words[0]) == "list") {
				
				listNames(list);
			}
			else if (words.size() == 1 && lowercase(words[0]) == "update") {
				update(list);
			}
			else if (lowercase(words[0]) == "sort" && words.size() == 2) {
				if (lowercase(words[1]) == "first") {
					sortByFirst(list);
				}
				else if (lowercase(words[1]) == "last") {
					sortByLast(list);
				}
				else if (lowercase(words[1]) == "phone") {
					sortByPhone(list);
				}
				else if (lowercase(words[1]) == "email") {
					sortByEmail(list);
				}
				
				
			}
			else if (words.size() == 2 && lowercase(words[0])=="find") {

				findContact(list, words[1]);

			}
			else if (words.size() == 1 && lowercase(words[0]) == "save") {
				writeToFile(list);
			}

			else if (words.size() == 1 && lowercase(words[0]) == "quit") {
				stop = true;
				
			}

			else {
				cout << "Command not recognized\n\n";
			}
			
			
		}
	}
}
int main() {
	ContactList list;
	if (openFile(list)) {
		readCommand(list);
	}
	
	
}