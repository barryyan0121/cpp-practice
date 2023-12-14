#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract class
class Packing {
public:
	virtual std::string pack() const = 0;
	~Packing() = default;
};

// Wrapper is one of the packing
class Wrapper : public Packing {
public:
	std::string pack() const override {
		return "Wrapper";
	}
};

// Bottle is one of the packing
class Bottle : public Packing {
public:
	std::string pack() const override {
		return "Bottle";
	}
};

// Abstract class
class Item {
public:
	virtual std::string name() const = 0;
	virtual std::unique_ptr<Packing> packing() const = 0;
	virtual float price() const = 0;
	~Item() = default;
};

//
class Burger : public Item {
public:
	std::unique_ptr<Packing> packing() const override {
		return std::make_unique<Wrapper>();
	}
};

class VegBurger : public Burger {
public:
	std::string name() const override {
		return "Veggie Burger";
	}
	float price() const override {
		return 25.0f;
	}
};

class ChickenBurger : public Burger {
public:
	std::string name() const override {
		return "Chicken Burger";
	}
	float price() const override {
		return 50.5f;
	}
};

class ColdDrink : public Item {
public:
	std::unique_ptr<Packing> packing() const override {
		return std::make_unique<Bottle>();
	}
};

class Coke : public ColdDrink {
public:
	std::string name() const override {
		return "Coke";
	}
	float price() const override {
		return 30.0f;
	}
};

class Pepsi : public ColdDrink {
public:
	std::string name() const override {
		return "Pepsi";
	}
	float price() const override {
		return 35.0f;
	}
};

// Meal is a collection of items
class Meal {
private:
	std::vector<std::shared_ptr<Item>> items;

public:
	void addItem(std::shared_ptr<Item> item) {
		items.push_back(item);
	}
	float getCost() const {
		float cost = 0.0f;
		for (auto& item : items) {
			cost += item->price();
		}
		return cost;
	}
	void showItems() const {
		for (auto& item : items) {
			std::cout << "Item: " << item->name() << std::endl;
			std::cout << "Packing: " << item->packing()->pack() << std::endl;
			std::cout << "Price: " << item->price() << std::endl;
		}
	}
};

class MealBuilder {
public:
	Meal prepareVegMeal() {
		Meal meal;
		meal.addItem(std::make_shared<VegBurger>());
		meal.addItem(std::make_shared<Coke>());
		return meal;
	}

	Meal prepareNonVegMeal() {
		Meal meal;
		meal.addItem(std::make_shared<ChickenBurger>());
		meal.addItem(std::make_shared<Pepsi>());
		return meal;
	}
};

int main() {
	MealBuilder mealBuilder;
	Meal vegMeal = mealBuilder.prepareVegMeal();
	std::cout << "Veg Meal" << std::endl;
	vegMeal.showItems();
	std::cout << "Total Cost: " << vegMeal.getCost() << std::endl;
	std::cout << std::endl;
	Meal nonVegMeal = mealBuilder.prepareNonVegMeal();
	std::cout << "Non-Veg Meal" << std::endl;
	nonVegMeal.showItems();
	std::cout << "Total Cost: " << nonVegMeal.getCost() << std::endl;

	return 0;
}