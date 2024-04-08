#include <iostream>
#include <memory>
#include <string>

class BusinessService {
public:
	virtual void doProcessing() = 0;
	virtual ~BusinessService() = default;
};

class EJBService : public BusinessService {
public:
	void doProcessing() override {
		std::cout << "Processing task by invoking EJB Service" << std::endl;
	}
};

class JMSService : public BusinessService {
public:
	void doProcessing() override {
		std::cout << "Processing task by invoking JMS Service" << std::endl;
	}
};

class BusinessLookUp {
public:
	std::unique_ptr<BusinessService> getBusinessService(const std::string& serviceType) {
		if (serviceType == "EJB") {
			std::cout << "Looking up and creating a new EJB Service object" << std::endl;
			return std::make_unique<EJBService>();
		} else if (serviceType == "JMS") {
			std::cout << "Looking up and creating a new JMS Service object" << std::endl;
			return std::make_unique<JMSService>();
		}
		return nullptr;
	}
};

class BusinessDelegate {
public:
	BusinessDelegate() = default;
	BusinessDelegate(const std::string& serviceType) : serviceType(serviceType) {}
	void doTask() {
		service = lookup.getBusinessService(serviceType);
		if (service) {
			service->doProcessing();
		}
	}
	void setServiceType(const std::string& serviceType) {
		this->serviceType = serviceType;
	}
	const std::string& getServiceType() const {
		return serviceType;
	}

private:
	std::string serviceType;
	BusinessLookUp lookup;
	std::unique_ptr<BusinessService> service;
};

class Client {
public:
	Client(BusinessDelegate& businessDelegate) : businessDelegate(businessDelegate) {}
	void doTask() {
		businessDelegate.doTask();
	}

private:
	BusinessDelegate& businessDelegate;
};

int main() {
	BusinessDelegate businessDelegate;
	businessDelegate.setServiceType("EJB");
	Client client(businessDelegate);
	client.doTask();
	businessDelegate.setServiceType("JMS");
	client.doTask();
	return 0;
}
