#ifndef _USER_
#define _USER_
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Helper.h"
using namespace std;

class User {
public:
	string username; // id
	string password;
	string role;
public:
	User() {}
	User(string username, string password) {
		this->username = username;
		this->password = password;
	}
	~User() {};

	void logout() {
		this->username = "";
		this->password = "";
		this->role = "";
	}
	bool isLogin() {
		if (this->username == "")return false;
		else return true;
	}
	string removeSpaces(string str)
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		return str;
	}
	bool checkNewPass(string np) {
		for (int i = 0; i < np.length(); i++) {
			if (np[i] == ',' || np[i] == '.' || np[i] == '?' || np[i] == '/' || np[i] == '>' || np[i] == '<' ||np[i] == '@' || np[i] == '#' || np[i] == '!') return false;
		}
		return true;
	}
	void changePassword(string newPassword) {
		this->password = newPassword;
	}
};

///--------------THIS IS FOR USER LIST----------------
class UserList :public arrayList<User> {
public:
	UserList() {};
	~UserList() {};

	inline User& operator[](int index) {
		return this->list[index];
	}

	int findUserByUsername(string username);
	bool authentication(User& random_user);
	void updateList(User& user);
};

bool cp(User user, arrayList<string> agvList, UserList &user_list);

#endif // !_USER_
