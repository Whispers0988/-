#include "UserManager.h"
#include <fstream>

User::User() {

}

User::User(std::string username, std:: string password, std::array<std::array<int, 3>, 3> info)
	:mUserName(username), mPassword(password), mInfomation(info) {

}


void UserManager::loadFile() {
	std::fstream fs(USER_FILE_PATH, std::ios::in);
	if (fs.is_open()) {
		fs >> mUserCount;
		for (int i = 0; i < mUserCount; i++) {
			std::string username;
			std::string password;
			std::array<std::array<int, 3>, 3> info;
			fs >> username;
			fs >> password;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					fs >> info[j][k];
				}
			}
			User* u = new User(username, password, info);
			mUsers.push_back(u);
		}
		fs.close();
	}
}

void UserManager::saveFile() {
	std::fstream fs(USER_FILE_PATH,std::ios::out);
	if (fs.is_open()) {
		fs << mUserCount << std::endl;
		for (int i = 0; i < mUserCount; i++) {
			fs << mUsers[i]->getUserName().c_str() << std::endl;
			fs << mUsers[i]->getPassword().c_str() << std::endl;
			auto info = mUsers[i]->getInfo();
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					fs << info[j][k] << " ";
				}
				fs << std::endl;
			}
			fs << std::endl;
		}
		fs.close();
	}
}

bool UserManager::addNewUser(std::string username, std::string password) {
	for (const auto& user : mUsers) {
		if (user->getUserName() == username) {
			return false;
		}
	}

	std::array<std::array<int, 3>, 3> info{ 0,0,0,0,0,0,0,0,0 };
	User* u = new User(username, password, info);
	mUsers.push_back(u);
	mUserCount++;
	saveFile();
	return true;
}

UserManager::LOGINSTATE UserManager::userLogin(std::string username, std::string password) {
	for (const auto& user : mUsers) {
		if (user->getUserName() == username) {
			if (user->getPassword() == password) {
				return SUCCESS;
			}
			else {
				return PASSWORDFAIL;
			}
		}
	}
	return USERNAMEFAIL;
}

User* UserManager::getUserByName(std::string username) {
	for (auto& user : mUsers) {
		if (user->getUserName() == username) {
			return user;
		}
	}
	return nullptr;
}