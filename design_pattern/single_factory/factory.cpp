#include <iostream>
#include <string>

class Vehicle {
public:
	virtual ~Vehicle() {}
	virtual std::string GetType() = 0;
};

class Car : public Vehicle {
public:
	std::string GetType() override { return "New Car"; }
};

class Bus : public Vehicle {
public:
	std::string GetType() override { return "New Bus"; }
};

class Bike : public Vehicle {
public:
	std::string GetType() override { return "New Bike"; }
};

class VehicleFactory {
public:
	static Vehicle* CreateVehicle(const std::string& type) {
		if (type == "Car") {
			return new Car();
		} else if (type == "Bus") {
			return new Bus();
		} else if (type == "Bike") {
			return new Bike();
		} else {
			return nullptr;
		}
	}
};

int main() {
	Vehicle* car = VehicleFactory::CreateVehicle("Car");
	std::cout << "Car: " << car->GetType() << std::endl;
	delete car;

	Vehicle* bus = VehicleFactory::CreateVehicle("Bus");
	std::cout << "Bus: " << bus->GetType() << std::endl;
	delete bus;

	Vehicle* bike = VehicleFactory::CreateVehicle("Bike");
	std::cout << "Bike: " << bike->GetType() << std::endl;
	delete bike;

	return 0;
}