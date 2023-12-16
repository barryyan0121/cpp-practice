#include <iostream>
#include <memory>
#include <string>

class Shape {
public:
	virtual void draw() const = 0;
};

class Rectangle : public Shape {
public:
	void draw() const override {
		std::cout << "Shape: Rectangle" << std::endl;
	}
};

class Circle : public Shape {
public:
	void draw() const override {
		std::cout << "Shape: Circle" << std::endl;
	}
};

class ShapeDecorator : public Shape {
private:
	std::unique_ptr<Shape> shape;

public:
	ShapeDecorator(std::unique_ptr<Shape> shape)
	    : shape(std::move(shape)) {}
	void draw() const override {
		shape->draw();
	}
};

class RedShapeDecorator : public ShapeDecorator {
public:
	RedShapeDecorator(std::unique_ptr<Shape> shape)
	    : ShapeDecorator(std::move(shape)) {}
	void draw() const override {
		ShapeDecorator::draw();
		setRedBorder();
	}
	void setRedBorder() const {
		std::cout << "Border Color: Red" << std::endl;
	}
};

int main() {
	std::unique_ptr<Shape> circle = std::make_unique<Circle>();
	std::unique_ptr<Shape> redCircle = std::make_unique<RedShapeDecorator>(std::make_unique<Circle>());
	std::unique_ptr<Shape> redRectangle = std::make_unique<RedShapeDecorator>(std::make_unique<Rectangle>());

	std::cout << "Circle with normal border" << std::endl;
	circle->draw();

	std::cout << "\nCircle of red border" << std::endl;
	redCircle->draw();

	std::cout << "\nRectangle of red border" << std::endl;
	redRectangle->draw();

	return 0;
}
