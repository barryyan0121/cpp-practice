#include <iostream>
#include <string>

class Shape {
public:
	virtual ~Shape() {}
	virtual void Draw() = 0;
};

class Rectangle : public Shape {
public:
	void Draw() { std::cout << "Inside Rectangle::Draw() method." << std::endl; }
};

class Square : public Shape {
public:
	void Draw() { std::cout << "Inside Square::Draw() method." << std::endl; }
};

class Circle : public Shape {
public:
	void Draw() { std::cout << "Inside Circle::Draw() method." << std::endl; }
};

class Color {
public:
	virtual ~Color() {}
	virtual void Fill() = 0;
};

class Red : public Color {
public:
	void Fill() { std::cout << "Inside Red::Fill() method." << std::endl; }
};

class Green : public Color {
public:
	void Fill() { std::cout << "Inside Green::Fill() method." << std::endl; }
};

class Blue : public Color {
public:
	void Fill() { std::cout << "Inside Blue::Fill() method." << std::endl; }
};

class AbstractFactory {
public:
	virtual ~AbstractFactory() {}
	virtual Shape* GetShape(std::string type) = 0;
	virtual Color* GetColor(std::string type) = 0;
};

class ShapeFactory : public AbstractFactory {
public:
	Shape* GetShape(std::string type) override {
		if (type == "Rectangle") {
			return new Rectangle();
		} else if (type == "Square") {
			return new Square();
		} else if (type == "Circle") {
			return new Circle();
		}
		return nullptr;
	}

	Color* GetColor(std::string type) override { return nullptr; }
};

class ColorFactory : public AbstractFactory {
public:
	Color* GetColor(std::string type) override {
		if (type == "Red") {
			return new Red();
		} else if (type == "Green") {
			return new Green();
		} else if (type == "Blue") {
			return new Blue();
		}
		return nullptr;
	}

	Shape* GetShape(std::string type) override { return nullptr; }
};

class FactoryProducer {
public:
	static AbstractFactory* GetFactory(std::string type) {
		if (type == "Shape") {
			return new ShapeFactory();
		} else if (type == "Color") {
			return new ColorFactory();
		}
		return nullptr;
	}
};

int main() {
	AbstractFactory* shape_factory = FactoryProducer::GetFactory("Shape");
	Shape* rectangle = shape_factory->GetShape("Rectangle");
	rectangle->Draw();
	delete rectangle;

	Shape* square = shape_factory->GetShape("Square");
	square->Draw();
	delete square;

	Shape* circle = shape_factory->GetShape("Circle");
	circle->Draw();
	delete circle;

	AbstractFactory* color_factory = FactoryProducer::GetFactory("Color");
	Color* red = color_factory->GetColor("Red");
	red->Fill();
	delete red;

	Color* green = color_factory->GetColor("Green");
	green->Fill();
	delete green;

	Color* blue = color_factory->GetColor("Blue");
	blue->Fill();
	delete blue;

	return 0;
}