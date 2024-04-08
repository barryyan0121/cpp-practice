#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <vector>

// Forward declaration of Subject to resolve circular dependency
class Subject;

// Full definition of Observer and its derived classes
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update() = 0;

protected:
	Subject* subject;
};

class BinaryObserver : public Observer {
public:
	BinaryObserver(Subject* subject);
	void update() override;
};

class OctalObserver : public Observer {
public:
	OctalObserver(Subject* subject);
	void update() override;
};

class HexaObserver : public Observer {
public:
	HexaObserver(Subject* subject);
	void update() override;
};

// Full definition of Subject
class Subject {
public:
	void attach(Observer* observer) {
		observers.push_back(observer);
	}
	void notifyAllObservers() {
		for (auto observer : observers) {
			observer->update();
		}
	}
	int getState() const {
		return state;
	}
	void setState(int state) {
		this->state = state;
	}

private:
	int state;
	std::vector<Observer*> observers;
};

// Definitions of member functions of derived Observer classes
inline BinaryObserver::BinaryObserver(Subject* subject) {
	this->subject = subject;
	this->subject->attach(this);
}

inline void BinaryObserver::update() {
	std::cout << "Binary String: " << subject->getState() << std::endl;
}

inline OctalObserver::OctalObserver(Subject* subject) {
	this->subject = subject;
	this->subject->attach(this);
}

inline void OctalObserver::update() {
	std::cout << "Octal String: " << subject->getState() << std::endl;
}

inline HexaObserver::HexaObserver(Subject* subject) {
	this->subject = subject;
	this->subject->attach(this);
}

inline void HexaObserver::update() {
	std::cout << "Hexa String: " << subject->getState() << std::endl;
}

#endif // OBSERVER_H
