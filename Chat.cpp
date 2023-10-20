#include "Chat.h"



Chat::Chat()
{
	greeting();
}

Chat::Chat(std::string active_user_login, std::string active_recipient_login, std::string active_user_name) :
	_active_user_login(active_user_login), _active_recipient_login(active_recipient_login), _active_user_name(active_user_name){}


void Chat::greeting(){
	std::cout << "\n          ����� ����������!\n\n";
}

void Chat::farewell(){
	std::cout << "\n\n          ����� ��������.\n";
}

int Chat::logOrReg(){
	Universal_Input<int> inputLOR('1', '3');
	std::cout << "\n ���� - 1\n";
	std::cout << " ����������� - 2 \n";
	std::cout << " ����� - 3 \n -> ";
	
	return inputLOR.input();
}

int Chat::menu_chat(){
	Universal_Input<int> inputMC('1', '3');
	std::cout << "\n ������� ������ - 1\n";
	std::cout << " ������� ��������� ���� - 2 \n";
	std::cout << " ����� �� �������� - 3 \n ";
	std::cout << " -> ";
	return inputMC.input();
}

bool Chat::finding(std::string login){
	if (_users.find(login) == _users.end()) return true;
	else return false;
}

bool Chat::check_password(std::string password, std::string login){
	if (_users.at(login).user_password() == password) return true;
	else return false;
}

void Chat::registration(int menu, bool* check_user){
	User user;
	Universal_Input<std::string> inputPL(_fsymbolLogPass, _lsymbolLogPass);
	Universal_Input<std::string> inputMessage(_fsymbolLogMessage, _lsymbolLogMessage);
	*check_user = false;
	// ���� � ���
	if (menu == 1){
		std::cout << "\n ������� �����: ";
		user.get_user_login(inputPL.input());
		std::cout << "\n ������� ������: ";
		user.get_user_password(inputPL.input());
		int counter = 0;
		
		if (!finding(user.user_login()) && check_password(user.user_password(), user.user_login())) {
				system("cls");
				get_user(user.user_login(), _users.at(user.user_login()).user_name());
				std::cout << "\n\n �� ����� ���:\n\n";
				_users.at(_active_user_login).showUser();
				*check_user = true;
		}
		else {
			std::cout << "\n �� ������ ����� ��� ������!";
			Sleep(2000);
			return;
		}

	}
	// ����������� ������ ������������
	else{
		*check_user = true;
		std::cout << " ������� ��� (������ ������� �������): ";
		user.get_user_name(inputMessage.input());
		std::cout << "\n ������� ����� (��������� �������, �����, �������): ";
		bool check_login;
		do		{
			check_login = true;
			user.get_user_login(inputPL.input());
			if (!finding(user.user_login())) {
				user.clear_login();
				inputPL.clear();
				std::cout << "\n ������ ����� �����, �������� ������: ";
				check_login = false;
			}
		} while (!check_login);

		std::cout << "\n ������� ������ (��������� �������, �����, �������): ";
		user.get_user_password(inputPL.input());

		_users.emplace(user.user_login(), user);
		get_user(user.user_login(), user.user_name());

		system("cls");
		std::cout << "\n\n �� ���������������� ���:\n\n";
		_users.at(_active_user_login).showUser();
	}
}

void Chat::reg_all_user(){
	User user;
	user.get_user_login("ALL_USERS");
	user.get_user_password("admin");
	user.get_user_name("����� ���");
	_users.emplace(user.user_login(), user);
}

// ����� ������ ���������� ����
void Chat::showListUsers(){
	int counter{ 0 };
	clear_show_user();
	std::cout << "\n ��������� ����:\n\n";

	for (std::map<std::string, User>::iterator it = _users.begin(); it != _users.end(); it++) {
		counter++;
		if (it->second.user_login() == _active_user_login) continue;
		std::cout << counter << " - ";
		if (it->second.user_login() == "ALL_USERS") it->second.showUserName();
		else it->second.showUser();
		std::cout << "\n";
	}
}

std::string Chat::active_user_login(){
	return _active_user_login;
}

std::string Chat::active_user_name(){
	return _active_user_name;
}

std::string Chat::active_recipient_login(){
	return _active_recipient_login;
}

void Chat::get_user(std::string login, std::string name)
{
	_active_user_login = login;
	_active_user_name = name;
}

void Chat::out_user(){
	_active_user_login = '\0';
	_active_user_name = '\0';

}

void Chat::get_recipient(int menu){
	Universal_Input<int> inputID('0', '9');
	int counter = 0;

	if (menu == 2) _active_recipient_login = "ALL_USERS";
	else{
		int id{ 0 };
		do{
			id = inputID.input();
			if (id < 1 || id > _users.size()){
				std::cout << "\n �� ������ ID, ��������� �����: ";
			}
			else break;

		} while (true);

		std::map<std::string, User>::iterator it = _users.begin();
		for (; it != _users.end(); it++) {
			counter++;
			if (counter == id) break;
		}
		
		_active_recipient_login = it->second.user_login();
	}
}

int Chat::sizeList(){
	return _users.size();
}

void Chat::send_message(){
	Message message;
	std::string mess;
	char menu{ '\0' };
	std::cout << " �������� - \"Enter\", ����� - \"Esc\" -> ";
	while (true){
		menu = _getch();
		if (menu == 27){
			clear_show_user();
			break;
		}
		else if (menu == 13){
			std::cout << "\n ";
			getline(std::cin, mess);
			message.create_message(mess, _active_user_name, _active_user_login, _active_recipient_login);
			_messages.push_back(message);
			clear_show_user();
			std::cout << " ��������� ��� ";
			if (_active_recipient_login == "ALL_USERS") std::cout << " ����";
			else _users.at(_active_recipient_login).showUserName();
			std::cout << " ���������� \n";
			break;
		}
		else std::cout << " ��, ����� ���������: ";
	}
}
// ����� ������
void Chat::show_message_list(){
	clear_show_user();
	std::cout << "\n ������ � \n";
	_users.at(_active_recipient_login).showUser();
	for (Message i : _messages){
		if (_active_user_login == i.login_sender() && _active_recipient_login == i.login_recipient() && _active_recipient_login != "ALL_USERS"
			|| _active_user_login == i.login_recipient() && _active_recipient_login == i.login_sender()){

			i.show_message();
		}
		else if (_active_recipient_login == "ALL_USERS" && _active_recipient_login == i.login_recipient()) i.show_message();
	}
}

void Chat::one_user(){
	std::cout << " �� ���� ������������ ������������. \n ������� �������, ����� ��� ��� �� ���� ����������������.\n";
	out_user();
	Sleep(2000);
	system("cls");

}

void Chat::no_users(){
	std::cout << "\n ������������������ ������������� ���� ���. \n ���������� ������� �����������������.\n ";
	Sleep(3000);
	system("cls");
}

void Chat::clear_show_user()
{
	system("cls");
	_users.at(_active_user_login).showUser();
}
