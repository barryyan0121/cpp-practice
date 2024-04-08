#include <iostream>
#include <memory>
#include <string>

class AbstractCustomer {
public:
	virtual ~AbstractCustomer() = default;
	virtual bool isNil() const = 0;
	virtual std::string getName() const = 0;

protected:
	std::string name;
};

class RealCustomer : public AbstractCustomer {
public:
	RealCustomer(const std::string& name) {
		this->name = name;
	}
	bool isNil() const override {
		return false;
	}
	std::string getName() const override {
		return name;
	}
};

class NullCustomer : public AbstractCustomer {
public:
	bool isNil() const override {
		return true;
	}
	std::string getName() const override {
		return "Not Available in Customer Database";
	}
};

class CustomerFactory {
public:
	static std::unique_ptr<AbstractCustomer> getCustomer(const std::string& name) {
		for (int i = 0; i < 3; ++i) {
			if (names[i] == name) {
				return std::make_unique<RealCustomer>(name);
			}
		}
		return std::make_unique<NullCustomer>();
	}

private:
	static std::string names[3];
};

std::string CustomerFactory::names[3] = {"Rob", "Joe", "Julie"};

int main() {
	std::unique_ptr<AbstractCustomer> customer1 = CustomerFactory::getCustomer("Rob");
	std::unique_ptr<AbstractCustomer> customer2 = CustomerFactory::getCustomer("Bob");
	std::unique_ptr<AbstractCustomer> customer3 = CustomerFactory::getCustomer("Julie");
	std::unique_ptr<AbstractCustomer> customer4 = CustomerFactory::getCustomer("Laura");

	std::cout << "Customers: " << std::endl;
	std::cout << customer1->getName() << std::endl;
	std::cout << customer2->getName() << std::endl;
	std::cout << customer3->getName() << std::endl;
	std::cout << customer4->getName() << std::endl;

	return 0;
}