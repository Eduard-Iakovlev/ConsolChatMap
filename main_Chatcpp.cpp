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
	chat.reg_all_user(); // ����������� �������� ������ ����

	while (work){

		menu = chat.logOrReg();
		system("cls");
		// ����� �� ��������
		if (menu == 3){
			chat.farewell();
			work = false;
			break;
		}
		// ���� � �������
		else if (menu == 1){
			if (chat.sizeList() == 1){
				chat.no_users();
				continue;
			}
			std::cout << " ���� \n";
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
		//����������� ������ ������������
		else{
			std::cout << " �����������:\n";
			chat.registration(menu, &check_user);
		}
		// �������� ���-�� ������������������
		if (chat.sizeList() == 2){
			chat.one_user();
			continue;
		}

		// ������ ��������
		do{
			menu = chat.menu_chat();
			discussion = true;
			switch (menu){
			case 1: // ������ ������
				chat.showListUsers();
				std::cout << " ID �����������: ";
				chat.get_recipient(menu);
				chat.show_message_list();
				chat.send_message();
				break;
			case 2: // ��������� ����
				chat.get_recipient(menu);
				chat.send_message();
				break;
			case 3: // �����
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
