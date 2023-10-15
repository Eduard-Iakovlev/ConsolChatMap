#include "Chat.h"



Chat::Chat()
{
	greeting();
}

Chat::Chat(std::string active_user_login, std::string active_recipient_login, std::string active_user_name, int active_user_ID, int active_recipirnt_ID) :
	_active_user_login(active_user_login), _active_recipient_login(active_recipient_login), _active_user_name(active_user_name), _active_user_ID(active_user_ID), _active_recipient_ID(active_recipirnt_ID) {}


void Chat::greeting(){
	std::cout << "\n          Добро пожаловать!\n\n";
}

void Chat::farewell(){
	std::cout << "\n\n          Всего хорошего.\n";
}

int Chat::logOrReg(){
	Universal_Input<int> inputLOR('1', '3');
	std::cout << "\n Вход - 1\n";
	std::cout << " Регистрация - 2 \n";
	std::cout << " Выход - 3 \n -> ";
	
	return inputLOR.input();
}

int Chat::menu_chat(){
	Universal_Input<int> inputMC('1', '3');
	std::cout << "\n Выбрать беседу - 1\n";
	std::cout << " Создать сообщение всем - 2 \n";
	std::cout << " Выход из аккаунта - 3 \n ";
	std::cout << " -> ";
	return inputMC.input();
}

void Chat::registration(int menu, bool* check_user){
	User user;
	Universal_Input<std::string> inputPL(_fsymbolLogPass, _lsymbolLogPass);
	Universal_Input<std::string> inputMessage(_fsymbolLogMessage, _lsymbolLogMessage);
	*check_user = false;
	// Вход в чат
	if (menu == 1){
		std::cout << "\n Введите логин: ";
		user.get_user_login(inputPL.input());
		std::cout << "\n Введите пароль: ";
		user.get_user_password(inputPL.input());
		int counter = 0;

		for (User i : _users)		{
			if (user.user_login() == i.user_login() && user.user_password() == i.user_password())			{
				get_user(counter, i.user_login(), i.user_name());
				system("cls");
				std::cout << "\n\n Вы вошли как:\n\n";
				_users.at(counter).showUser();
				*check_user = true;
			}
			counter++;
		}
		if (*check_user == false)		{
			std::cout << "\n Не верный логин или пароль!";
			Sleep(2000);
			return;
		}
	}
	// регистрация нового пользователя
	else{
		*check_user = true;
		std::cout << " Введите имя (только русский алфавит): ";
		user.get_user_name(inputMessage.input());
		std::cout << "\n Введите логин (латинский алфавит, цифры, символы): ";
		bool check_login;
		do		{
			check_login = true;
			user.get_user_login(inputPL.input());
			for (User i : _users)			{
				if (user.user_login() == i.user_login())				{
					user.clear_login();
					std::cout << "\n Данный логин занят, выберите другой: ";
					check_login = false;
					break;
				}
			}
		} while (!check_login);

		std::cout << "\n Введите пароль (латинский алфавит, цифры, символы): ";
		user.get_user_password(inputPL.input());

		_users.push_back(user);
		int size = _users.size() - 1;
		get_user(size, _users.at(size).user_login(), _users.at(size).user_name());
		system("cls");
		std::cout << "\n\n Вы зарегистрированы как:\n\n";
		_users.at(size).showUser();
	}
}

void Chat::reg_all_user(){
	User user;
	user.get_user_login("ALL_USERS");
	user.get_user_password("admin");
	user.get_user_name("общий чат");
	_users.push_back(user);
}

// вывод списка участников чата
void Chat::showListUsers(){
	int counter{ 0 };
	clear_show_user();
	std::cout << "\n Участники чата:\n\n";

	for (User user : _users){
		counter++;
		if ((counter - 1) == _active_user_ID) continue;
		std::cout << counter << " - ";
		if ((counter - 1) != 0) user.showUser();
		else{
			user.showUserName();
			std::cout << "\n";
		}
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

void Chat::get_user(int id, std::string login, std::string name)
{
	_active_user_ID = id;
	_active_user_login = login;
	_active_user_name = name;
}

void Chat::out_user(){
	_active_user_ID = 0;
	_active_user_login = '\0';
	_active_user_name = '\0';

}

void Chat::get_recipient(int menu){
	Universal_Input<int> inputID('0', '9');

	if (menu == 2) _active_recipient_login = "ALL_USERS";
	else{
		int id{ 0 };
		do{
			id = inputID.input();
			if (id < 1 || id > _users.size()){
				std::cout << "\n Не верный ID, повторите выбор: ";
			}
			else break;

		} while (true);
		id -= 1;
		_active_recipient_login = _users.at(id).user_login();
		_active_recipient_ID = id;
	}
}

int Chat::sizeList(){
	return _users.size();
}

void Chat::send_message(){
	Message message;
	std::string mess;
	char menu{ '\0' };
	std::cout << " Написать - \"Enter\", Выход - \"Esc\" -> ";
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
			std::cout << " Сообщение для ";
			if (_active_recipient_login == "ALL_USERS") std::cout << " всем";
			else _users.at(_active_recipient_ID).showUserName();
			std::cout << " отправлено \n";
			break;
		}
		else std::cout << " хм, можно повторить: ";
	}
}
// вывод беседы
void Chat::show_message_list(){
	clear_show_user();
	std::cout << "\n Беседа с \n";
	_users.at(_active_recipient_ID).showUser();
	for (Message i : _messages){
		if (_active_user_login == i.login_sender() && _active_recipient_login == i.login_recipient() && _active_recipient_login != "ALL_USERS"
			|| _active_user_login == i.login_recipient() && _active_recipient_login == i.login_sender()){

			i.show_message();
		}
		else if (_active_recipient_login == "ALL_USERS" && _active_recipient_login == i.login_recipient()) i.show_message();
	}
}

void Chat::one_user(){
	std::cout << " вы пока единственный пользователь. \n Зайдите попозже, когда ещё кто ни будь зарегистрируется.\n";
	out_user();
	Sleep(3000);
	system("cls");

}

void Chat::no_users(){
	std::cout << "\n Зарегистрированных пользователей пока нет. \n Пожалуйста сначала зарегистрируйтесь.\n ";
	Sleep(3000);
	system("cls");
}

void Chat::clear_show_user()
{
	system("cls");
	_users.at(_active_user_ID).showUser();
}
