#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Employee {
private:
	std::string name;
	std::string dept;
	int salary;
	std::vector<std::shared_ptr<Employee>> subordinates;

public:
	Employee(std::string name, std::string dept, int sal)
	    : name(name)
	    , dept(dept)
	    , salary(sal) {}
	void add(std::shared_ptr<Employee> e) {
		subordinates.push_back(e);
	}
	void remove(std::shared_ptr<Employee> e) {
		for (auto it = subordinates.begin(); it != subordinates.end(); ++it) {
			if (*it == e) {
				subordinates.erase(it);
				break;
			}
		}
	}
	const std::vector<std::shared_ptr<Employee>>& getSubordinates() const {
		return subordinates;
	}
	friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
		os << "Employee :[ Name : " << e.name << ", dept : " << e.dept << ", salary :" << e.salary << " ]";
		return os;
	}
};

int main() {
	auto CEO = std::make_shared<Employee>("John", "CEO", 30000);
	auto headSales = std::make_shared<Employee>("Robert", "Head Sales", 20000);
	auto headMarketing = std::make_shared<Employee>("Michel", "Head Marketing", 20000);
	auto clerk1 = std::make_shared<Employee>("Laura", "Marketing", 10000);
	auto clerk2 = std::make_shared<Employee>("Bob", "Marketing", 10000);
	auto salesExecutive1 = std::make_shared<Employee>("Richard", "Sales", 10000);
	auto salesExecutive2 = std::make_shared<Employee>("Rob", "Sales", 10000);

	CEO->add(headSales);
	CEO->add(headMarketing);

	headSales->add(salesExecutive1);
	headSales->add(salesExecutive2);

	headMarketing->add(clerk1);
	headMarketing->add(clerk2);

	std::cout << *CEO << std::endl;
	for (auto headEmployee : CEO->getSubordinates()) {
		std::cout << *headEmployee << std::endl;
		for (auto employee : headEmployee->getSubordinates()) {
			std::cout << *employee << std::endl;
		}
	}
	return 0;
}