#include <iostream>
#include <memory>
#include <string>

class Vehicle {
public:
	virtual ~Vehicle() {}
	virtual std::string GetType() = 0;
};

class Car : public Vehicle {
public:
	std::string GetType() override {
		return "New Car";
	}
};

class Bus : public Vehicle {
public:
	std::string GetType() override {
		return "New Bus";
	}
};

class Bike : public Vehicle {
public:
	std::string GetType() override {
		return "New Bike";
	}
};

class VehicleFactory {
public:
	static std::unique_ptr<Vehicle> CreateVehicle(const std::string& type) {
		if (type == "Car") {
			return std::make_unique<Car>();
		} else if (type == "Bus") {
			return std::make_unique<Bus>();
		} else if (type == "Bike") {
			return std::make_unique<Bike>();
		} else {
			return nullptr;
		}
	}
};

int main() {
	auto car = VehicleFactory::CreateVehicle("Car");
	std::cout << "Car: " << car->GetType() << std::endl;

	auto bus = VehicleFactory::CreateVehicle("Bus");
	std::cout << "Bus: " << bus->GetType() << std::endl;

	auto bike = VehicleFactory::CreateVehicle("Bike");
	std::cout << "Bike: " << bike->GetType() << std::endl;

	return 0;
}