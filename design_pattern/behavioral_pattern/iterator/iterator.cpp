#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual std::string next() = 0;
};

class NameIterator : public Iterator {
public:
	NameIterator(const std::vector<std::string>& names) : names(names), size(names.size()) {}
	bool hasNext() override {
		return index < size;
	}
	std::string next() override {
		if (hasNext()) {
			return names[index++];
		}
		return "";
	}

private:
	std::vector<std::string> names;
	int size;
	int index = 0;
};

class Container {
public:
    virtual std::unique_ptr<Iterator> getIterator() = 0;
};

class NameRepository : public Container {
public:
    NameRepository(const std::vector<std::string>& names) : names(names) {}
    std::unique_ptr<Iterator> getIterator() override {
        return std::make_unique<NameIterator>(names);
    }
private:
    std::vector<std::string> names;
};

int main() {
    std::vector<std::string> names = {"Robert", "John", "Julie", "Lora"};
    std::unique_ptr<Container> container = std::make_unique<NameRepository>(names);
    std::unique_ptr<Iterator> iter = container->getIterator();
    while (iter->hasNext()) {
        std::cout << iter->next() << std::endl;
    }
    return 0;
}