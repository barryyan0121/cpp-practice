// ComputerPart.h
#ifndef COMPUTERPART_H
#define COMPUTERPART_H

#include <iostream>
#include <string>
#include <memory>

class ComputerPartVisitor;

class ComputerPart {
public:
	virtual void accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) = 0;
	virtual ~ComputerPart() = default;
};

class Keyboard : public ComputerPart, public std::enable_shared_from_this<Keyboard> {
public:
	void accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override;
};

class Monitor : public ComputerPart, public std::enable_shared_from_this<Monitor> {
public:
	void accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override;
};

class Mouse : public ComputerPart, public std::enable_shared_from_this<Mouse> {
public:
	void accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override;
};

class Computer : public ComputerPart, public std::enable_shared_from_this<Computer> {
public:
	Computer();
	~Computer();
	void accept(std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override;

private:
	std::shared_ptr<ComputerPart> parts[3];
};

class ComputerPartVisitor {
public:
	virtual void visit(std::shared_ptr<Computer> computer) = 0;
	virtual void visit(std::shared_ptr<Mouse> mouse) = 0;
	virtual void visit(std::shared_ptr<Keyboard> keyboard) = 0;
	virtual void visit(std::shared_ptr<Monitor> monitor) = 0;
	virtual ~ComputerPartVisitor() = default;
};

class ComputerPartDisplayVisitor : public ComputerPartVisitor {
public:
	void visit(std::shared_ptr<Computer> computer) override;
	void visit(std::shared_ptr<Mouse> mouse) override;
	void visit(std::shared_ptr<Keyboard> keyboard) override;
	void visit(std::shared_ptr<Monitor> monitor) override;
};

#endif // COMPUTERPART_H
