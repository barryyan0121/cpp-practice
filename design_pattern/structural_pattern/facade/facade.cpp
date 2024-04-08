#include <iostream>
#include <memory>

class Shape {
public:
	virtual void draw() = 0;
};

class Rectangle : public Shape {
public:
	void draw() override {
		std::cout << "Rectangle::draw()" << std::endl;
	}
};

class Square : public Shape {
public:
	void draw() override {
		std::cout << "Square::draw()" << std::endl;
	}
};

class Circle : public Shape {
public:
	void draw() override {
		std::cout << "Circle::draw()" << std::endl;
	}
};

class ShapeMaker {
public:
	ShapeMaker() {
		rectangle = std::make_unique<Rectangle>();
		square = std::make_unique<Square>();
		circle = std::make_unique<Circle>();
	}

	~ShapeMaker() {}

	void drawRectangle() {
		rectangle->draw();
	}

	void drawSquare() {
		square->draw();
	}

	void drawCircle() {
		circle->draw();
	}

private:
	std::unique_ptr<Shape> rectangle;
	std::unique_ptr<Shape> square;
	std::unique_ptr<Shape> circle;
};

int main() {
	auto shapeMaker = std::make_unique<ShapeMaker>();
	shapeMaker->drawRectangle();
	shapeMaker->drawSquare();
	shapeMaker->drawCircle();
	return 0;
}