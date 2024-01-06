#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Expression {
public:
	virtual bool interpret(const std::string& context) = 0;
};

class TerminalExpression : public Expression {
public:
	TerminalExpression(const std::string& data) : data(data) {}
	bool interpret(const std::string& context) override {
		return context.find(data) != std::string::npos;
	}

private:
	std::string data;
};

class OrExpression : public Expression {
public:
	OrExpression(std::unique_ptr<Expression> expr1, std::unique_ptr<Expression> expr2)
	    : expr1(std::move(expr1))
	    , expr2(std::move(expr2)) {}
	bool interpret(const std::string& context) override {
		return expr1->interpret(context) || expr2->interpret(context);
	}

private:
	std::unique_ptr<Expression> expr1;
	std::unique_ptr<Expression> expr2;
};

class AndExpression : public Expression {
public:
	AndExpression(std::unique_ptr<Expression> expr1, std::unique_ptr<Expression> expr2)
	    : expr1(std::move(expr1))
	    , expr2(std::move(expr2)) {}
	bool interpret(const std::string& context) override {
		return expr1->interpret(context) && expr2->interpret(context);
	}

private:
	std::unique_ptr<Expression> expr1;
	std::unique_ptr<Expression> expr2;
};

class InterpreterPatternDemo {
public:
	static std::unique_ptr<Expression> getMaleExpression() {
		std::unique_ptr<Expression> robert = std::make_unique<TerminalExpression>("Robert");
		std::unique_ptr<Expression> john = std::make_unique<TerminalExpression>("John");
		return std::make_unique<OrExpression>(std::move(robert), std::move(john));
	}

	static std::unique_ptr<Expression> getMarriedWomanExpression() {
		std::unique_ptr<Expression> julie = std::make_unique<TerminalExpression>("Julie");
		std::unique_ptr<Expression> married = std::make_unique<TerminalExpression>("Married");
		return std::make_unique<AndExpression>(std::move(julie), std::move(married));
	}

	static void run() {
		std::unique_ptr<Expression> isMale = getMaleExpression();
		std::unique_ptr<Expression> isMarriedWoman = getMarriedWomanExpression();
		std::cout << "John is male? " << isMale->interpret("John") << std::endl;
		std::cout << "Julie is a married woman? " << isMarriedWoman->interpret("Married Julie") << std::endl;
	}
};

int main() {
	InterpreterPatternDemo::run();
	return 0;
}
