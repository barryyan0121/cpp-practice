#include <iostream>

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
		rectangle = new Rectangle();
		square = new Square();
		circle = new Circle();
	}

	~ShapeMaker() {
		delete rectangle;
		delete square;
		delete circle;
	}

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
	Shape* rectangle;
	Shape* square;
	Shape* circle;
};

int main() {
	ShapeMaker* shapeMaker = new ShapeMaker();
	shapeMaker->drawRectangle();
	shapeMaker->drawSquare();
	shapeMaker->drawCircle();
	delete shapeMaker;
	return 0;
}