#include "ChatRoom.h"
#include "User.h"
#include <iostream>

User::User(std::string name) : name(std::move(name)) {}

std::string User::getName() const {
	return name;
}

void User::setName(std::string newName) {
	name = std::move(newName);
}

void User::sendMessage(const std::string& message) {
	ChatRoom::showMessage(*this, message);
}

void ChatRoom::showMessage(const User& user, const std::string& message) {
	std::cout << user.getName() << " sent a message: " << message << std::endl;
}

int main() {
	User robert("Robert");
	User john("John");
	robert.sendMessage("Hi! John!");
	john.sendMessage("Hello! Robert!");
	return 0;
}