#include <iostream>
#include <memory>
#include <string>

class Image {
public:
	virtual void display() = 0;
};

class RealImage : public Image {
public:
	RealImage(std::string fileName)
	    : fileName(fileName) {
		loadFromDisk(fileName);
	}

	void display() override {
		std::cout << "Displaying " << fileName << std::endl;
	}

private:
	void loadFromDisk(std::string fileName) {
		std::cout << "Loading " << fileName << std::endl;
	}
	std::string fileName;
};

class ProxyImage : public Image {
public:
	ProxyImage(std::string fileName)
	    : fileName(fileName) {}

	void display() override {
		if (realImage == nullptr) {
			realImage = std::make_shared<RealImage>(fileName);
		}
		realImage->display();
	}

private:
	std::shared_ptr<RealImage> realImage;
	std::string fileName;
};

int main() {
	auto image = std::make_shared<ProxyImage>("test_10mb.jpg");

	// image will be loaded from disk
	image->display();
	std::cout << std::endl;

	// image will not be loaded from disk
	image->display();
}
