#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Shape {
protected:
	std::string id;
	std::string type;

public:
	virtual ~Shape() {}
	virtual void Draw() const = 0;
	virtual std::shared_ptr<Shape> Clone() const = 0;
	std::string GetType() const {
		return type;
	}
	std::string GetId() const {
		return id;
	}
	void SetId(std::string id) {
		this->id = id;
	}
};

class Rectangle : public Shape {
public:
	Rectangle() {
		type = "Rectangle";
	}
	void Draw() const override {
		std::cout << "Inside Rectangle::Draw() method." << std::endl;
	}
	std::shared_ptr<Shape> Clone() const override {
		return std::make_shared<Rectangle>(*this);
	}
};

class Circle : public Shape {
public:
	Circle() {
		type = "Circle";
	}
	void Draw() const override {
		std::cout << "Inside Circle::Draw() method." << std::endl;
	}
	std::shared_ptr<Shape> Clone() const override {
		return std::make_shared<Circle>(*this);
	}
};

class Square : public Shape {
public:
	Square() {
		type = "Square";
	}
	void Draw() const override {
		std::cout << "Inside Square::Draw() method." << std::endl;
	}
	std::shared_ptr<Shape> Clone() const override {
		return std::make_shared<Square>(*this);
	}
};

class ShapeCache {
private:
	static std::unordered_map<std::string, std::shared_ptr<Shape>> shapeMap;

public:
	ShapeCache() {}

	static std::shared_ptr<Shape> GetShape(const std::string& shapeId) {
		auto it = shapeMap.find(shapeId);
		if (it != shapeMap.end()) {
			return it->second->Clone();
		}
		return nullptr;
	}

	void loadCache() {
		std::shared_ptr<Shape> circle = std::make_shared<Circle>();
		circle->SetId("1");
		shapeMap[circle->GetId()] = circle;

		std::shared_ptr<Shape> square = std::make_shared<Square>();
		square->SetId("2");
		shapeMap[square->GetId()] = square;

		std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>();
		rectangle->SetId("3");
		shapeMap[rectangle->GetId()] = rectangle;
	}
};

std::unordered_map<std::string, std::shared_ptr<Shape>> ShapeCache::shapeMap;

int main() {
	ShapeCache shapeCache;
	shapeCache.loadCache();
	std::shared_ptr<Shape> clonedShape1 = shapeCache.GetShape("1");
	std::cout << "Shape : " << clonedShape1->GetType() << std::endl;
	clonedShape1->Draw();
	std::shared_ptr<Shape> clonedShape2 = shapeCache.GetShape("2");
	std::cout << "Shape : " << clonedShape2->GetType() << std::endl;
	clonedShape2->Draw();
	std::shared_ptr<Shape> clonedShape3 = shapeCache.GetShape("3");
	std::cout << "Shape : " << clonedShape3->GetType() << std::endl;
	clonedShape3->Draw();
	return 0;
}
