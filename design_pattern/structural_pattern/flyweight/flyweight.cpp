#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Shape {
public:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	Circle(std::string color)
	    : x(0)
	    , y(0)
	    , radius(0)
	    , color(color) {}

	void draw() override {
		std::cout << "Circle: Draw() [Color : " << color << ", x : " << x << ", y :" << y << ", radius :" << radius
		          << "]" << std::endl;
	}

	void setRadius(int radius) {
		this->radius = radius;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

private:
	int x, y, radius;
	std::string color;
};

class ShapeFactory {

public:
	static std::shared_ptr<Shape> getCircle(std::string color) {
		auto circle = circleMap[color];
		if (circle == nullptr) {
			std::cout << "Creating circle of color : " << color << std::endl;
			circle = std::make_shared<Circle>(color);
			circle->draw();
			circleMap[color] = circle;
				}
		return circle;
	}

private:
	static std::unordered_map<std::string, std::shared_ptr<Shape>> circleMap;
};

std::unordered_map<std::string, std::shared_ptr<Shape>> ShapeFactory::circleMap;

class FlyweightPatternDemo {
public:
	static void run() {
		std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
		for (int i = 0; i < 20; ++i) {
			std::string color = getRandomColor();
			std::shared_ptr<Shape> circle = ShapeFactory::getCircle(color);
			std::static_pointer_cast<Circle>(circle)->setX(getRandomX());
			std::static_pointer_cast<Circle>(circle)->setY(getRandomY());
			std::static_pointer_cast<Circle>(circle)->setRadius(100);
			circle->draw();
		}
	}

private:
	static std::string getRandomColor() {
		static std::string colors[] = {"Red", "Green", "Blue", "White", "Black"};
		return colors[std::rand() % 5];
	}

	static int getRandomX() {
		return std::rand() % 100;
	}

	static int getRandomY() {
		return std::rand() % 100;
	}
};

int main() {
	FlyweightPatternDemo::run();
	return 0;
}
