#include "User.h"

using namespace std;

inline bool operator==(User &lhs, User &rhs) {
	return lhs.username == rhs.username;
}
inline bool operator==(User &lhs, string &rhs) {
	return lhs.username == rhs;
}
inline bool operator==(string &lhs, User &rhs) {
	return lhs == rhs.username;
}
inline bool operator!=(User &lhs, User &rhs) {
	return !(lhs.username == rhs.username);
}
inline bool operator!=(User &lhs, string &rhs) {
	return !(lhs.username == rhs);
}
inline bool operator!=(string &lhs, User &rhs) {
	return !(lhs == rhs.username);
}
//-----------------------USER_LIST--------------------
int UserList::findUserByUsername(string username) {
	for (size_t i = 0; i < size; i++) {
		if (this->list[i] == username)return i;
	}
	return -1;
}

bool UserList::authentication(User& random_user) {
	int index = findUserByUsername(random_user.username);
	if (index != -1) {
		if (random_user.password == this->list[index].password) {
			random_user.role = this->list[index].role;
			return true;
		}
		else return false;
	}
	else return false;
}
void UserList::updateList(User& user) {
	int index = findUserByUsername(user.username);
	if (index == -1);
	else {
		this->list[index].username = user.username;
		this->list[index].password = user.password;
	}
}



bool cp(User user, arrayList<string> agvList, UserList &user_list) {
	string newPassword;
	if (agvList.size != 1) {
		for (int i = 1; i < agvList.size; i++) newPassword += agvList.list[i];
	}
	else if (agvList.size == 1) {
		cout << "Input your new password: ";
		getline(cin, newPassword);
		newPassword = user.removeSpaces(newPassword);
	}
	if (!user.checkNewPass(newPassword)) {
		cout << "NEW PASSWORD MUST NOT CONTAIN ', . ? @ $ # ...' CHARATER (SYSTEM REQUIRE),TRY AGAIN LATER.\n";
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else {
		user.changePassword(newPassword);
		user_list.updateList(user);
		cout << "CHANGE PASSWORD SUCCESSFULLY--YOUR NEWPASS (please remember it): " << newPassword << endl;
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
}