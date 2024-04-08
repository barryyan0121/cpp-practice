#include "ComputerPart.h"

void Keyboard::accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) {
    computerPartVisitor->visit(shared_from_this());
}

void Monitor::accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) {
	computerPartVisitor->visit(shared_from_this());
}

void Mouse::accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) {
	computerPartVisitor->visit(shared_from_this());
}

Computer::Computer() {
	parts[0] = std::make_shared<Mouse>();
	parts[1] = std::make_shared<Keyboard>();
	parts[2] = std::make_shared<Monitor>();
}

Computer::~Computer() {
    std::cout << "Computer destructor called." << std::endl;    
}

void Computer::accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) {
	for (int i = 0; i < 3; ++i) {
		parts[i]->accept(computerPartVisitor);
	}
	computerPartVisitor->visit(shared_from_this());
}

void ComputerPartDisplayVisitor::visit(std::shared_ptr<Computer> computer) {
	std::cout << "Displaying Computer." << std::endl;
}

void ComputerPartDisplayVisitor::visit(std::shared_ptr<Mouse> mouse) {
	std::cout << "Displaying Mouse." << std::endl;
}

void ComputerPartDisplayVisitor::visit(std::shared_ptr<Keyboard> keyboard) {
	std::cout << "Displaying Keyboard." << std::endl;
}

void ComputerPartDisplayVisitor::visit(std::shared_ptr<Monitor> monitor) {
	std::cout << "Displaying Monitor." << std::endl;
}

int main() {
	std::shared_ptr<ComputerPart> computer = std::make_shared<Computer>();
	computer->accept(std::make_shared<ComputerPartDisplayVisitor>());
	return 0;
}
