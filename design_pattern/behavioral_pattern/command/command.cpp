#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Stock {
public:
	void buy() {
		std::cout << "Stock buy" << std::endl;
	}
	void sell() {
		std::cout << "Stock sell" << std::endl;
	}

private:
	std::string name;
	int quantity;
};

class Order {
public:
	virtual void execute() = 0;
};

class BuyStock : public Order {
public:
	BuyStock(std::shared_ptr<Stock> stock) : stock(stock) {}
	void execute() override {
		stock->buy();
	}

private:
	std::shared_ptr<Stock> stock;
};

class SellStock : public Order {
public:
	SellStock(std::shared_ptr<Stock> stock) : stock(stock) {}
	void execute() override {
		stock->sell();
	}

private:
	std::shared_ptr<Stock> stock;
};

class Broker {
public:
	void takeOrder(std::shared_ptr<Order> order) {
		orderList.push_back(order);
	}

	void placeOrders() {
		for (auto order : orderList) {
			order->execute();
		}
		orderList.clear();
	}

private:
	std::vector<std::shared_ptr<Order>> orderList;
};

int main() {
    auto abcStock = std::make_shared<Stock>();

    auto buyStockOrder = std::make_shared<BuyStock>(abcStock);
    auto sellStockOrder = std::make_shared<SellStock>(abcStock);

    auto broker = std::make_shared<Broker>();
    broker->takeOrder(buyStockOrder);
    broker->takeOrder(sellStockOrder);

    broker->placeOrders();
}