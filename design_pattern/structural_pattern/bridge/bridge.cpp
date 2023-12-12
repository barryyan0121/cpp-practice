#include <iostream>
#include <memory>

// interface
class DrawAPI {
public:
	virtual ~DrawAPI() = default;
	virtual void drawCircle(int radius, int x, int y) const = 0;
};

class RedCircle : public DrawAPI {
public:
	void drawCircle(int radius, int x, int y) const override {
		std::cout << "Drawing Circle[color: red, radius: " << radius << ", x: " << x << ", " << y << "]" << std::endl;
	}
};

class GreenCircle : public DrawAPI {
public:
	void drawCircle(int radius, int x, int y) const override {
		std::cout << "Drawing Circle[color: green, radius: " << radius << ", x: " << x << ", " << y << "]" << std::endl;
	}
};

class Shape {
protected:
	std::unique_ptr<DrawAPI> drawAPI;

public:
	Shape(std::unique_ptr<DrawAPI> drawAPI)
	    : drawAPI(std::move(drawAPI)) {}

	virtual ~Shape() = default;
	virtual void draw() const = 0;
};

class Circle : public Shape {
private:
	int x, y, radius;

public:
	Circle(int x, int y, int radius, std::unique_ptr<DrawAPI> drawAPI)
	    : Shape(std::move(drawAPI))
	    , x(x)
	    , y(y)
	    , radius(radius) {}

	void draw() const override {
		drawAPI->drawCircle(radius, x, y);
	}
};

int main() {
	std::unique_ptr<Shape> redCircle = std::make_unique<Circle>(100, 100, 10, std::make_unique<RedCircle>());
	std::unique_ptr<Shape> greenCircle = std::make_unique<Circle>(100, 100, 5, std::make_unique<GreenCircle>());

	redCircle->draw();
	greenCircle->draw();

	return 0;
}