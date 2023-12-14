#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Person {
private:
	std::string name;
	std::string gender;
	std::string maritalStatus;

public:
	Person(std::string name, std::string gender, std::string maritalStatus)
	    : name(name)
	    , gender(gender)
	    , maritalStatus(maritalStatus) {}

	std::string getName() {
		return name;
	}

	std::string getGender() {
		return gender;
	}

	std::string getMaritalStatus() {
		return maritalStatus;
	}

	bool operator==(const Person& other) const {
		return name == other.name && gender == other.gender && maritalStatus == other.maritalStatus;
	}
};

class Criteria {
public:
	virtual std::vector<Person> meetCriteria(std::vector<Person> persons) const = 0;
};

class AndCriteria : public Criteria {
private:
	std::shared_ptr<Criteria> criteria;
	std::shared_ptr<Criteria> otherCriteria;

public:
	AndCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria)
	    : criteria(criteria)
	    , otherCriteria(otherCriteria) {}
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> firstCriteriaPersons = criteria->meetCriteria(persons);
		return otherCriteria->meetCriteria(firstCriteriaPersons);
	}
};

class OrCriteria : public Criteria {
private:
	std::shared_ptr<Criteria> criteria;
	std::shared_ptr<Criteria> otherCriteria;

public:
	OrCriteria(std::shared_ptr<Criteria> criteria, std::shared_ptr<Criteria> otherCriteria)
	    : criteria(criteria)
	    , otherCriteria(otherCriteria) {}
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> firstCriteriaItems = criteria->meetCriteria(persons);
		std::vector<Person> otherCriteriaItems = otherCriteria->meetCriteria(persons);

		for (auto person : otherCriteriaItems) {
			if (std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()) {
				firstCriteriaItems.push_back(person);
			}
		}
		return firstCriteriaItems;
	}
};

class CriteriaMale : public Criteria {
public:
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> malePersons;
		for (auto person : persons) {
			if (person.getGender() == "male") {
				malePersons.push_back(person);
			}
		}
		return malePersons;
	}
};

class CriteriaFemale : public Criteria {
public:
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> femalePersons;
		for (auto person : persons) {
			if (person.getGender() == "female") {
				femalePersons.push_back(person);
			}
		}
		return femalePersons;
	}
};

class CriteriaSingle : public Criteria {
public:
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> singlePersons;
		for (auto person : persons) {
			if (person.getMaritalStatus() == "single") {
				singlePersons.push_back(person);
			}
		}
		return singlePersons;
	}
};

class CriteriaMarried : public Criteria {
public:
	std::vector<Person> meetCriteria(std::vector<Person> persons) const override {
		std::vector<Person> marriedPersons;
		for (auto person : persons) {
			if (person.getMaritalStatus() == "married") {
				marriedPersons.push_back(person);
			}
		}
		return marriedPersons;
	}
};

static void PrintPersons(std::vector<Person> persons) {
	std::string str;
	for (auto person : persons) {
		str += "Name: " + person.getName() + ", ";
		str += "Gender: " + person.getGender() + ", ";
		str += "Marital Status: " + person.getMaritalStatus() + "\n";
	}
	std::cout << str << std::endl;
}

int main() {
	std::vector<Person> persons;
	persons.push_back(Person("Robert", "male", "single"));
	persons.push_back(Person("Laura", "female", "married"));
	persons.push_back(Person("John", "male", "married"));
	persons.push_back(Person("Diana", "female", "single"));
	persons.push_back(Person("Mike", "male", "single"));
	persons.push_back(Person("Bobby", "male", "single"));
	auto male = std::make_shared<CriteriaMale>();
	auto female = std::make_shared<CriteriaFemale>();
	auto single = std::make_shared<CriteriaSingle>();
	auto married = std::make_shared<CriteriaMarried>();
	auto singleMale = std::make_shared<AndCriteria>(single, male);
	auto singleOrFemale = std::make_shared<OrCriteria>(single, female);
    std::cout << "Male: " << std::endl;
	PrintPersons(male->meetCriteria(persons));
    std::cout << "Female: " << std::endl;
	PrintPersons(female->meetCriteria(persons));
    std::cout << "Single: " << std::endl;
	PrintPersons(single->meetCriteria(persons));
    std::cout << "Married: " << std::endl;
	PrintPersons(married->meetCriteria(persons));
    std::cout << "Single Male: " << std::endl;
	PrintPersons(singleMale->meetCriteria(persons));
    std::cout << "Single Or Female: " << std::endl;
	PrintPersons(singleOrFemale->meetCriteria(persons));
}