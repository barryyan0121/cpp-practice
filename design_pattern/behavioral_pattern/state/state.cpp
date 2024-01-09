#include <iostream>
#include <memory>
#include <string>

class Context; // Forward declaration

class State {
public:
	virtual ~State() = default;
	virtual void doAction(Context& context) = 0;
	virtual std::string getStateName() const = 0;
};

class Context {
public:
	Context() : state(nullptr) {}
	void setState(std::unique_ptr<State> newState) {
		state = std::move(newState);
	}
	State* getState() const {
		return state.get();
	}

private:
	std::unique_ptr<State> state;
};

class StartState : public State {
public:
	void doAction(Context& context) override {
		context.setState(std::make_unique<StartState>());
	}
	std::string getStateName() const override {
		return "Start State";
	}
};

class StopState : public State {
public:
	void doAction(Context& context) override {
		context.setState(std::make_unique<StopState>());
	}
	std::string getStateName() const override {
		return "Stop State";
	}
};

int main() {
	Context context;

	std::unique_ptr<State> startState = std::make_unique<StartState>();
	startState->doAction(context);
	std::cout << "Current state: " << context.getState()->getStateName() << std::endl;

	std::unique_ptr<State> stopState = std::make_unique<StopState>();
	stopState->doAction(context);
	std::cout << "Current state: " << context.getState()->getStateName() << std::endl;

	return 0;
}
