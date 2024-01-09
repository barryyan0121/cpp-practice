#include "observer.h"

int main() {
	Subject* subject = new Subject();

	new HexaObserver(subject);
	new OctalObserver(subject);
	new BinaryObserver(subject);

	std::cout << "First state change: 15" << std::endl;
	subject->setState(15);
	subject->notifyAllObservers();

	std::cout << "Second state change: 10" << std::endl;
	subject->setState(10);
	subject->notifyAllObservers();

	delete subject;
	return 0;
}
