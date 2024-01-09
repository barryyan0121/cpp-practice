#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
	User(std::string name);
	std::string getName() const;
	void setName(std::string newName);
	void sendMessage(const std::string& message);

private:
	std::string name;
};

#endif // USER_H
