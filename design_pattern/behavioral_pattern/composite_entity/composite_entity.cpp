#include <iostream>
#include <memory>
#include <string>
#include <vector>

class DependentObject1 {
public:
	void setData(std::string data) {
		this->data = data;
	}

	std::string getData() const {
		return data;
	}

private:
	std::string data;
};

class DependentObject2 {
public:
	void setData(std::string data) {
		this->data = data;
	}

	std::string getData() const {
		return data;
	}

private:
	std::string data;
};

class CoarseGrainedObject {
public:
	void setData(std::string data1, std::string data2) {
		do1.setData(data1);
		do2.setData(data2);
	}

	std::vector<std::string> getData() const {
		return {do1.getData(), do2.getData()};
	}

private:
	DependentObject1 do1;
	DependentObject2 do2;
};

class CompositeEntity {
public:
	void setData(std::string data1, std::string data2) {
		cgo.setData(data1, data2);
	}

	std::vector<std::string> getData() const {
		return cgo.getData();
	}

private:
	CoarseGrainedObject cgo;
};

class Client {
public:
	Client(std::shared_ptr<CompositeEntity> compositeEntity) : compositeEntity(compositeEntity) {}

	void printData() {
		for (auto& data : compositeEntity->getData()) {
			std::cout << "Data: " << data << std::endl;
		}
	}

	void setData(std::string data1, std::string data2) {
		compositeEntity->setData(data1, data2);
	}

private:
	std::shared_ptr<CompositeEntity> compositeEntity;
};

int main() {
	auto compositeEntity = std::make_shared<CompositeEntity>();
	auto client = std::make_shared<Client>(compositeEntity);

	client->setData("Test", "Data");
	client->printData();
	client->setData("Second Test", "Data1");
	client->printData();

	return 0;
}