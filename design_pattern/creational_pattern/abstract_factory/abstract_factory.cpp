#include <iostream>
#include <memory>
#include <string>

class Shape {
public:
	virtual ~Shape() {}
	virtual void Draw() = 0;
};

class Rectangle : public Shape {
public:
	void Draw() {
		std::cout << "Inside Rectangle::Draw() method." << std::endl;
	}
};

class Square : public Shape {
public:
	void Draw() {
		std::cout << "Inside Square::Draw() method." << std::endl;
	}
};

class Circle : public Shape {
public:
	void Draw() {
		std::cout << "Inside Circle::Draw() method." << std::endl;
	}
};

class Color {
public:
	virtual ~Color() {}
	virtual void Fill() = 0;
};

class Red : public Color {
public:
	void Fill() {
		std::cout << "Inside Red::Fill() method." << std::endl;
	}
};

class Green : public Color {
public:
	void Fill() {
		std::cout << "Inside Green::Fill() method." << std::endl;
	}
};

class Blue : public Color {
public:
	void Fill() {
		std::cout << "Inside Blue::Fill() method." << std::endl;
	}
};

class AbstractFactory {
public:
	virtual ~AbstractFactory() {}
	virtual std::unique_ptr<Shape> GetShape(std::string type) = 0;
	virtual std::unique_ptr<Color> GetColor(std::string type) = 0;
};

class ShapeFactory : public AbstractFactory {
public:
	std::unique_ptr<Shape> GetShape(std::string type) override {
		if (type == "Rectangle") {
			return std::make_unique<Rectangle>();
		} else if (type == "Square") {
			return std::make_unique<Square>();
		} else if (type == "Circle") {
			return std::make_unique<Circle>();
		}
		return nullptr;
	}

	std::unique_ptr<Color> GetColor(std::string type) override {
		return nullptr;
	}
};

class ColorFactory : public AbstractFactory {
public:
	std::unique_ptr<Color> GetColor(std::string type) override {
		if (type == "Red") {
			return std::make_unique<Red>();
		} else if (type == "Green") {
			return std::make_unique<Green>();
		} else if (type == "Blue") {
			return std::make_unique<Blue>();
		}
		return nullptr;
	}

	std::unique_ptr<Shape> GetShape(std::string type) override {
		return nullptr;
	}
};

class FactoryProducer {
public:
	static std::unique_ptr<AbstractFactory> GetFactory(std::string type) {
		if (type == "Shape") {
			return std::make_unique<ShapeFactory>();
		} else if (type == "Color") {
			return std::make_unique<ColorFactory>();
		}
		return nullptr;
	}
};

int main() {
	auto shape_factory = FactoryProducer::GetFactory("Shape");
	auto rectangle = shape_factory->GetShape("Rectangle");
	rectangle->Draw();

	auto square = shape_factory->GetShape("Square");
	square->Draw();

	auto circle = shape_factory->GetShape("Circle");
	circle->Draw();

	auto color_factory = FactoryProducer::GetFactory("Color");
	auto red = color_factory->GetColor("Red");
	red->Fill();

	auto green = color_factory->GetColor("Green");
	green->Fill();

	auto blue = color_factory->GetColor("Blue");
	blue->Fill();

	return 0;
}