#include <iostream>
#include <memory>

class Strategy {
public:
	virtual ~Strategy() = default;
	virtual int doOperation(int num1, int num2) const = 0;
};

class OperationAdd : public Strategy {
public:
	int doOperation(int num1, int num2) const override {
		return num1 + num2;
	}
};

class OperationSubstract : public Strategy {
public:
	int doOperation(int num1, int num2) const override {
		return num1 - num2;
	}
};

class OperationMultiply : public Strategy {
public:
	int doOperation(int num1, int num2) const override {
		return num1 * num2;
	}
};

class Context {
public:
	Context(std::shared_ptr<Strategy> strategy) : strategy(std::move(strategy)) {}
	int executeStrategy(int num1, int num2) const {
		return strategy->doOperation(num1, num2);
	}

private:
	std::shared_ptr<Strategy> strategy;
};

int main() {
	std::shared_ptr<Context> context = std::make_shared<Context>(std::make_shared<OperationAdd>());
	std::cout << "10 + 5 = " << context->executeStrategy(10, 5) << std::endl;

	context = std::make_shared<Context>(std::make_shared<OperationSubstract>());
	std::cout << "10 - 5 = " << context->executeStrategy(10, 5) << std::endl;

	context = std::make_shared<Context>(std::make_shared<OperationMultiply>());
	std::cout << "10 * 5 = " << context->executeStrategy(10, 5) << std::endl;

	return 0;
}