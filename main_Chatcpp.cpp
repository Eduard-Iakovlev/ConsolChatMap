#include "Chat.h"
#include "User.h"
#include "Message.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool work{ true };
	bool check_user{ false };
	bool discussion{ true };
	int menu{ 0 };


	Chat chat;
	chat.reg_all_user(); // регистрация аккаунта общего чата

	while (work){

		menu = chat.logOrReg();
		system("cls");
		// выход из аккаунта
		if (menu == 3){
			chat.farewell();
			work = false;
			break;
		}
		// вход в аккаунт
		else if (menu == 1){
			if (chat.sizeList() == 1){
				chat.no_users();
				continue;
			}
			std::cout << " Вход \n";
			chat.registration(menu, &check_user);
			if (chat.sizeList() == 2){
				chat.one_user();
				continue;
			}

			if (check_user == false){
				Sleep(2500);
				system("cls");
				continue;
			}

		}
		//регистрация нового пользователя
		else{
			std::cout << " Регистрация:\n";
			chat.registration(menu, &check_user);
		}
		// проверка кол-ва зарегистрированных
		if (chat.sizeList() == 2){
			chat.one_user();
			continue;
		}

		// работа аккаунта
		do{
			menu = chat.menu_chat();
			discussion = true;
			switch (menu){
			case 1: // личная беседа
				chat.showListUsers();
				std::cout << " ID собеседника: ";
				chat.get_recipient(menu);
				chat.show_message_list();
				chat.send_message();
				break;
			case 2: // сообщение всем
				chat.get_recipient(menu);
				chat.send_message();
				break;
			case 3: // выход
				chat.out_user();
				system("cls");
				discussion = false;
				break;

			default:
				break;
			}

		} while (discussion);
	}
}
