#include <iostream>
#include <string>
#include <vector>


class Memento {
public:
    Memento(std::string state) : state(std::move(state)) {}
    std::string getState() const {
        return state;
    }
private:
    std::string state;
};

class CareTaker {
public:
    void add(Memento memento) {
        mementoList.push_back(std::move(memento));
    }
    Memento get(int index) const {
        return mementoList[index];
    }
private:
    std::vector<Memento> mementoList;
};

class Originator {
public:
    void setState(std::string state) {
        this->state = std::move(state);
    }
    std::string getState() const {
        return state;
    }
    Memento saveStateToMemento() {
        return Memento(state);
    }
    void getStateFromMemento(const Memento& memento) {
        state = memento.getState();
    }
private:
    std::string state;
};

int main() {
    Originator originator;
    CareTaker careTaker;
    originator.setState("State #1");
    originator.setState("State #2");
    careTaker.add(originator.saveStateToMemento());
    originator.setState("State #3");
    careTaker.add(originator.saveStateToMemento());
    originator.setState("State #4");
    std::cout << "Current State: " << originator.getState() << std::endl;
    originator.getStateFromMemento(careTaker.get(0));
    std::cout << "First saved State: " << originator.getState() << std::endl;
    originator.getStateFromMemento(careTaker.get(1));
    std::cout << "Second saved State: " << originator.getState() << std::endl;
    return 0;
}
