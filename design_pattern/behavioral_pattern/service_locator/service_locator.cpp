#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Service {
public:
	virtual void execute() = 0;
	virtual std::string getName() const = 0;
	virtual ~Service() = default;
};

class Service1 : public Service {
public:
	void execute() override {
		std::cout << "Executing Service1" << std::endl;
	}
	std::string getName() const override {
		return "SERVICE1";
	}
};

class Service2 : public Service {
public:
	void execute() override {
		std::cout << "Executing Service2" << std::endl;
	}
	std::string getName() const override {
		return "SERVICE2";
	}
};

class InitialContext {
public:
	std::shared_ptr<Service> lookup(const std::string& jndiName) {
		if (jndiName == "SERVICE1") {
			std::cout << "Looking up and creating a new Service1 object" << std::endl;
			return std::make_shared<Service1>();
		} else if (jndiName == "SERVICE2") {
			std::cout << "Looking up and creating a new Service2 object" << std::endl;
			return std::make_shared<Service2>();
		}
		return nullptr;
	}
};

class Cache {
public:
	std::shared_ptr<Service> getService(const std::string& serviceName) {
		std::cout << "Cache :: getService()" << std::endl;
		for (auto& service : services) {
			if (service->getName() == serviceName) {
				std::cout << "Returning cached " << serviceName << " object" << std::endl;
				return service;
			}
		}
		return nullptr;
	}
	void addService(std::shared_ptr<Service> newService) {
		for (auto& service : services) {
			if (service->getName() == newService->getName()) {
				return;
			}
		}
		services.push_back(newService);
	}

private:
	std::vector<std::shared_ptr<Service>> services;
};

class ServiceLocator {
public:
	static std::shared_ptr<Service> getService(const std::string& jndiName) {
		auto service = cache->getService(jndiName);
		if (service != nullptr) {
			return service;
		}
		auto context = std::make_shared<InitialContext>();
		service = context->lookup(jndiName);
		if (service != nullptr) {
			cache->addService(service);
		}
		return service;
	}

private:
	static std::shared_ptr<Cache> cache;
};

std::shared_ptr<Cache> ServiceLocator::cache = std::make_shared<Cache>();

class ServiceLocatorPatternDemo {
public:
	static void main() {
		auto service = ServiceLocator::getService("SERVICE1");
		service->execute();
		service = ServiceLocator::getService("SERVICE2");
		service->execute();
		service = ServiceLocator::getService("SERVICE1");
		service->execute();
		service = ServiceLocator::getService("SERVICE2");
		service->execute();
		service = ServiceLocator::getService("SERVICE1");
		service->execute();
		service = ServiceLocator::getService("SERVICE2");
		service->execute();
		service = ServiceLocator::getService("SERVICE1");
		service->execute();
		service = ServiceLocator::getService("SERVICE2");
		service->execute();
	}
};

int main() {
	ServiceLocatorPatternDemo::main();
	return 0;
}