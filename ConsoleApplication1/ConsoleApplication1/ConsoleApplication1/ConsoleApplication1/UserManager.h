#ifndef  USERMANAGER_H
#define USERMANAGER_H

#define USER_FILE_PATH "UserInfo.txt"

#include <iostream>
#include <array>
#include <vector>

class User
{
public:
	User();
	User(std::string username, std::string password, std::array<std::array<int, 3>, 3> info);

	std::string getUserName() const {
		return mUserName;
	}

	std::string getPassword() const {
		return mPassword;
	}

	std::array<std::array<int, 3>, 3> getInfo() const {
		return mInfomation;
	}

	void setArray(std::array<std::array<int, 3>, 3> newArray) {
		mInfomation = newArray;
	}

private:
	std::string mUserName;
	std::string mPassword;
	std::array<std::array<int, 3>, 3> mInfomation;
};

class UserManager
{
public:

	enum LOGINSTATE
	{
		SUCCESS = 0,
		USERNAMEFAIL,
		PASSWORDFAIL
	};

	//读取用户文件
	void loadFile();
	//保存用户信息
	void saveFile();
	//注册新用户
	bool addNewUser(std::string username, std::string password);
	//bool addNewUser(const User& user);

	//获取用户指针
	User* getUserByName(std::string username);
	//登录
	LOGINSTATE userLogin(std::string username, std::string password);

private:
	std::vector<User*> mUsers;
	int mUserCount = 0;
};

#endif // ! USERMANAGER_H




