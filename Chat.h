#pragma once
#include <vector>
#include <map>
#include "User.h"
#include "Message.h"
#include "Consol_Input.h"
#include <cstdlib>
#include "Windows.h"

class Chat
{
public:
	Chat();
	Chat(std::string, std::string, std::string);
	void greeting();
	void farewell();
	int logOrReg();
	int menu_chat();

	bool finding(std::string);
	bool check_password(std::string, std::string);
	void registration(int, bool*);
	void reg_all_user();

	void showListUsers();
	std::string active_user_login();
	std::string active_user_name();
	std::string active_recipient_login();


	void get_user(std::string, std::string);
	void out_user();
	void get_recipient(int);


	int sizeList();

	void send_message();
	void show_message_list();

	void one_user();
	void no_users();

	void clear_show_user();


private:
	std::map <std::string, User> _users;
	std::vector<Message> _messages;
	std::string _active_user_login;
	std::string _active_recipient_login;
	std::string _active_user_name;
	char _fsymbolLogPass = 48;
	char _lsymbolLogPass = 126;
	char _fsymbolLogMessage = 192;
	char _lsymbolLogMessage = 255;
};

