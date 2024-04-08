#ifndef CHATROOM_H
#define CHATROOM_H

#include "User.h"
#include <string>

class ChatRoom {
public:
	static void showMessage(const User& user, const std::string& message);
};

#endif // CHATROOM_H
