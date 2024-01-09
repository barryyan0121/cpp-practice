#include <iostream>
#include <string>
#include <memory>


class Game {
public:
	virtual void initialize() = 0;
	virtual void startPlay() = 0;
	virtual void endPlay() = 0;

	// template method
	virtual void play() final {
		initialize();
		startPlay();
		endPlay();
	}
};

class Cricket : public Game {
public:
	void initialize() override {
		std::cout << "Cricket Game Initialized! Start playing." << std::endl;
	}

	void startPlay() override {
		std::cout << "Cricket Game Started. Enjoy the game!" << std::endl;
	}

	void endPlay() override {
		std::cout << "Cricket Game Finished!" << std::endl;
	}
};

class Football : public Game {
public:
	void initialize() override {
		std::cout << "Football Game Initialized! Start playing." << std::endl;
	}

	void startPlay() override {
		std::cout << "Football Game Started. Enjoy the game!" << std::endl;
	}

	void endPlay() override {
		std::cout << "Football Game Finished!" << std::endl;
	}
};

int main() {
	std::unique_ptr<Game> cricket = std::make_unique<Cricket>();
	cricket->play();

	std::unique_ptr<Game> football = std::make_unique<Football>();
	football->play();

	return 0;
}