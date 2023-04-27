#pragma once
#include <string>

using namespace std;



class person {
public:
	person(int id, int age, string name, string email, string phoneNum, bool isStudent) : personId(id), personAge(age), personName(name), personEmail(email), personPhoneNum(phoneNum), isPersonStudent(isStudent) {};
	int getId() const { return personId; }
	int getAge() const { return personAge; }
	string getName() const { return personName; }
	string getEmail() const { return personEmail; }
	string getPhone() const { return personPhoneNum; }
	bool isStudent() const { return isPersonStudent; }
private:
	int personId;
	int personAge;
	string personName;
	string personEmail;
	string personPhoneNum;
	bool isPersonStudent;
};