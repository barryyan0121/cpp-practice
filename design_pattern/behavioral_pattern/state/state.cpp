#include <iostream>
#include <typeinfo>

// Forward declaration of Context to resolve circular dependency
class Context;

class State {
public:
	virtual ~State() = default;
	virtual void doAction(Context& context) = 0;
	virtual std::string getStateName() const = 0;
};

class Context {
public:
	Context() : state(nullptr) {}
	void setState(State* state) {
		this->state = state;
	}
	State* getState() const {
		return state;
	}

private:
	State* state;
};

class StartState : public State {
public:
	void doAction(Context& context) override {
		context.setState(this);
	}
	std::string getStateName() const override {
		return "Start State";
	}
};

class StopState : public State {
public:
	void doAction(Context& context) override {
		context.setState(this);
	}
	std::string getStateName() const override {
		return "Stop State";
	}
};

int main() {
	Context context;
	StartState startState;
	StopState stopState;

	startState.doAction(context);
	std::cout << "Current state: " << context.getState()->getStateName() << std::endl;

	stopState.doAction(context);
	std::cout << "Current state: " << context.getState()->getStateName() << std::endl;

	return 0;
}
