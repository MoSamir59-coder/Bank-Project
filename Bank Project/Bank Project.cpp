#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "String funcs.h"
#include "File process.h"
#include "Client process.h"
#include "User process.h"
#include "Reading input.h"

using namespace std;


enum enum_chioce_client { client_list = 1, new_client = 2, delete_client = 3, update_client = 4, find_client = 5, transactions = 6, manage_users = 7, user_logout = 8, client_Exit = 9 };

enum enum_chioce_user { user_list = 1, new_user = 2, delete_user = 3, update_user = 4, find_user = 5, main_menue = 6 };

enum enum_chioce_ATM { en_quick_withdraw = 1, en_normal_withdraw = 2, en_deposit = 3, en_check_balance = 4, client_logout = 5, ATM_Exit = 6 };

enum enum_chioce_amount_to_withdraw { twenty = 1, fifty = 2, one_handred = 3, two_handred = 4, four_handred = 5, six_handred = 6, eight_handred = 7, one_thausand = 8, withdraw_Exit = 9 };

enum enum_main_entry { bank_management = 1, ATM = 2, final_Exit = 3 };

void login_for_users();

void login_for_clients();

void main_screen(user_lib::struct_user user);

void manage_users_screen(user_lib::struct_user user);

void ATM_main_screen(client_lib::struct_client client);

void main_entry();

void return_to_main_screen(user_lib::struct_user user)
{
	cout << "\n\n\n\nPress any key to return to main screen ... \n";
	system("pause>0");
	system("cls");
	main_screen(user);
}

void return_to_ATM_main_screen(client_lib::struct_client client)
{
	cout << "\n\n\n\nPress any key to return to main screen ... \n";
	system("pause>0");
	system("cls");
	ATM_main_screen(client);
}

void return_to_users_screen(user_lib::struct_user user)
{
	cout << "\n\n\n\nPress any key to return to manage users screen ... \n";
	system("pause>0");
	system("cls");
	manage_users_screen(user);
}

void access_denied(user_lib::struct_user user)
{
	system("cls");
	cout << "------------------------------------------------------------\n";
	cout << "Access Denied\n";
	cout << "You don't have permission to do that!!\n";
	cout << "Please contact your admin\n";
	cout << "------------------------------------------------------------\n\n\n";
	return_to_main_screen(user);
}

void show_client_list(user_lib::struct_user user)
{
	system("cls");
	client_lib::print_all_clients_data(file_lib::load_clients_data_from_file(file_lib::clients_file_name));
	return_to_main_screen(user);
}

void show_user_list(user_lib::struct_user user)
{
	system("cls");
	user_lib::print_all_users_data(file_lib::load_users_data_from_file(file_lib::users_file_name));
	return_to_users_screen(user);
}

void add_new_client(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Add Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char add_more = 'Y';
	string line = client_lib::convert_record_to_line(input_lib::read_new_client());
	file_lib::add_data_line_to_file(file_lib::clients_file_name, line);
	cout << "\n\n\nClient added successfully, do you want to add more clients ? Y / N ?  . \n";
	cin >> add_more;
	while (toupper(add_more) == 'Y')
		add_new_client(user);
	return_to_main_screen(user);
}

void add_new_user(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Add Users Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char add_more = 'Y';
	string line = user_lib::convert_record_to_line(input_lib::read_new_user());
	file_lib::add_data_line_to_file(file_lib::users_file_name, line);
	cout << "\n\n\nUser added successfully, do you want to add more users ? Y / N ?  . \n";
	cin >> add_more;
	while (toupper(add_more) == 'Y')
		add_new_user(user);
	return_to_users_screen(user);
}

void delete_client_from_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Delete Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	file_lib::delete_client_by_account_number(account_number, data);
	return_to_main_screen(user);
}

void delete_user_from_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Delete Users Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string user_name = input_lib::read_user_name();
	vector <user_lib::struct_user> data = file_lib::load_users_data_from_file(file_lib::users_file_name);
	file_lib::delete_user_by_name(user_name,data);
	return_to_users_screen(user);
}

void update_client_in_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Update Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	file_lib::update_client_by_account_number(account_number, data);
	return_to_main_screen(user);
}

void update_user_in_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Update Users Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string user_name = input_lib::read_user_name();
	vector <user_lib::struct_user> data = file_lib::load_users_data_from_file(file_lib::users_file_name);
	file_lib::update_user_by_name(user_name,data);
	return_to_users_screen(user);
}

void find_client_in_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Find Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char find_more = 'Y';
	client_lib::struct_client client;
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	if (file_lib::find_client_by_account_number(account_number, data, client))
	{
		client_lib::print_client_card(client);
		cout << "\n\nDo you want to find more clients ?  Y / N ?    ";
		cin >> find_more;
	}
	else
	{
		cout << "\nClient with account number (" << account_number << ") is Not Found!";
		cout << "\n\nDo you want to find more clients ?  Y / N ?    ";
		cin >> find_more;
	}
	while (toupper(find_more) == 'Y')
		find_client_in_list(user);
	return_to_main_screen(user);
}

void find_user_in_list(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Find Users Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char find_more = 'Y';
	user_lib::struct_user user_to_find;
	string user_name = input_lib::read_user_name();
	vector <user_lib::struct_user> data = file_lib::load_users_data_from_file(file_lib::users_file_name);
	if (file_lib::find_user_by_name(user_name, data, user_to_find))
	{
		user_lib::print_user_card(user);
		cout << "\n\nDo you want to find more users ?  Y / N ?    ";
		cin >> find_more;
	}
	else
	{
		cout << "\nUser (" << user_name << ") is Not Found!";
		cout << "\n\nDo you want to find more users ?  Y / N ?    ";
		cin >> find_more;
	}
	while (toupper(find_more) == 'Y')
		find_user_in_list(user);
	return_to_users_screen(user);
}

void deposit(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Deposit Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char deposit_more = 'Y';
	char sure = 'Y';
	double deposit_amount;
	client_lib::struct_client client;
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	if (file_lib::find_client_by_account_number(account_number, data, client))
	{
		client_lib::print_client_card(client);
		cout << "\nEnter deposit amount ---> ";
		cin >> deposit_amount;
		cout << "\nAre you sure to deposit this amount ?  Y / N ? ";
		cin >> sure;
		while (toupper(sure) == 'Y')
		{
			client.account_balance += deposit_amount;
			for (client_lib::struct_client &C : data)
			{
				if (C.account_number == client.account_number)
				{
					C = client;
					break;
				}
			}
			file_lib::save_clients_data_to_file(file_lib::clients_file_name, data);
			cout << "\nDeposit done successfully , new balance is " << client.account_balance << endl;
			break;
		}
		cout << "\n\nDo you want to deposit more ?  Y / N ?    ";
		cin >> deposit_more;
		while (toupper(deposit_more) == 'Y')
			deposit(user);
		return_to_main_screen(user);
		return;
	}
	else
	{
		cout << "\nClient with account number (" << account_number << ") is Not Found!";
		cout << "\n\nDo you want to try again ?  Y / N ?    ";
		cin >> deposit_more;
		while (toupper(deposit_more) == 'Y')
			deposit(user);
		return_to_main_screen(user);
	}
}

void ATM_deposit(client_lib::struct_client client)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Deposit Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char sure = 'Y';
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	double deposit_amount = input_lib::read_positive_number("Enter a positive deposit amount ----> ");
	cout << "\nAre you sure to deposit this amount ?  Y / N ? ";
	cin >> sure;
	while (toupper(sure) == 'Y')
	{
		client.account_balance += deposit_amount;
		for (client_lib::struct_client& C : data)
		{
			if (C.account_number == client.account_number)
			{
				C = client;
				break;
			}
		}
		file_lib::save_clients_data_to_file(file_lib::clients_file_name, data);
		cout << "\nDeposit done successfully , new balance is " << client.account_balance << endl;
		break;
	}
	return_to_ATM_main_screen(client);
	return;
}

void withdraw(user_lib::struct_user user)
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                      Withdraw Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	char withdraw_more = 'Y';
	char sure = 'Y';
	double withdraw_amount;
	client_lib::struct_client client;
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	if (file_lib::find_client_by_account_number(account_number, data, client))
	{
		client_lib::print_client_card(client);
		cout << "\nEnter withdraw amount ---> ";
		cin >> withdraw_amount;
		while (withdraw_amount > client.account_balance)
		{
			cout << "\nAmount exceeded the balance, you can withdraw up to " << client.account_balance << endl;
			cout << "Enter withdraw amount ---> ";
			cin >> withdraw_amount;
		}
		cout << "\nAre you sure to withdraw this amount ?  Y / N ? ";
		cin >> sure;
		while (toupper(sure) == 'Y')
		{
			client.account_balance -= withdraw_amount;
			for (client_lib::struct_client &C : data)
			{
				if (C.account_number == client.account_number)
				{
					C = client;
					break;
				}
			}
			file_lib::save_clients_data_to_file(file_lib::clients_file_name, data);
			cout << "\nWithdraw done successfully , new balance is " << client.account_balance << endl;
			break;
		}
		cout << "\n\nDo you want to Withdraw more ?  Y / N ?    ";
		cin >> withdraw_more;
		while (toupper(withdraw_more) == 'Y')
			withdraw(user);
		return_to_main_screen(user);
		return;
	}
	else
	{
		cout << "\nClient with account number (" << account_number << ") is Not Found!";
		cout << "\n\nDo you want to try again ?  Y / N ?    ";
		cin >> withdraw_more;
		while (toupper(withdraw_more) == 'Y')
			withdraw(user);
	}
}

void quick_withdraw(client_lib::struct_client client)
{
	system("cls");
	cout << "=========================================================\n\n";
	cout << "                    Quick Withdraw \n\n";
	cout << "=========================================================\n\n";
	cout << "       [1] 20			[2] 50 \n";
	cout << "       [3] 100			[4] 200 \n";
	cout << "       [5] 400			[6] 600 \n";
	cout << "       [7] 800			[8] 1000 \n";
	cout << "       [9] Exit \n";
	cout << "=========================================================\n";
	char sure = 'Y';
	int withdraw_amount;
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	cout << "Your Balance is " << client.account_balance << endl << endl;
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 9] ", 1, 9);
	if (choice == enum_chioce_amount_to_withdraw::twenty)
		withdraw_amount = 20;
	else if (choice == enum_chioce_amount_to_withdraw::fifty)
		withdraw_amount = 50;
	else if (choice == enum_chioce_amount_to_withdraw::one_handred)
		withdraw_amount = 100;
	else if (choice == enum_chioce_amount_to_withdraw::two_handred)
		withdraw_amount = 200;
	else if (choice == enum_chioce_amount_to_withdraw::four_handred)
		withdraw_amount = 400;
	else if (choice == enum_chioce_amount_to_withdraw::six_handred)
		withdraw_amount = 600;
	else if (choice == enum_chioce_amount_to_withdraw::eight_handred)
		withdraw_amount = 800;
	else if (choice == enum_chioce_amount_to_withdraw::one_thausand)
		withdraw_amount = 1000;
	else if (choice == enum_chioce_amount_to_withdraw::withdraw_Exit)
	{
		return_to_ATM_main_screen(client);
		return;
	}
	while (withdraw_amount > client.account_balance)
	{
		cout << "\nAmount exceeded the balance, Make another choice \n";
		cout << "\n\n\n\nPress any key to return to continue ... \n";
		system("pause>0");
		quick_withdraw(client);
	}
	cout << "\nAre you sure to withdraw this amount ?  Y / N ? ";
	cin >> sure;
	while (toupper(sure) == 'Y')
	{
		client.account_balance -= withdraw_amount;
		for (client_lib::struct_client& C : data)
		{
			if (C.account_number == client.account_number)
			{
				C = client;
				break;
			}
		}
		file_lib::save_clients_data_to_file(file_lib::clients_file_name, data);
		cout << "\nWithdraw done successfully , new balance is " << client.account_balance << endl;
		break;
	}
	return_to_ATM_main_screen(client);
	return;
}

void normal_withdraw(client_lib::struct_client client)
{
	system("cls");
	cout << "=========================================================\n\n";
	cout << "                    Normal Withdraw \n\n";
	cout << "=========================================================\n\n";
	char sure = 'Y';
	int withdraw_amount = input_lib::read_positive_number_multiplier_of(5);
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	while (withdraw_amount > client.account_balance)
	{
		cout << "\nAmount exceeded the balance, Make another choice \n";
		cout << "\n\n\n\nPress any key to return to continue ... \n";
		system("pause>0");
		normal_withdraw(client);
	}
	cout << "\nAre you sure to withdraw this amount ?  Y / N ? ";
	cin >> sure;
	while (toupper(sure) == 'Y')
	{
		client.account_balance -= withdraw_amount;
		for (client_lib::struct_client& C : data)
		{
			if (C.account_number == client.account_number)
			{
				C = client;
				break;
			}
		}
		file_lib::save_clients_data_to_file(file_lib::clients_file_name, data);
		cout << "\nWithdraw done successfully , new balance is " << client.account_balance << endl;
		break;
	}
	return_to_ATM_main_screen(client);
	return;
}

void total_balances(user_lib::struct_user user)
{
	system("cls");
	double counter = 0;
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	cout << "\n\t\t\t\t\tBalances List (" << data.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(20) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (client_lib::struct_client client : data)
	{
		cout << "| " << setw(20) << left << client.account_number;
		cout << "| " << setw(40) << left << client.name;
		cout << "| " << setw(20) << left << client.account_balance;
		cout << endl;
		counter += client.account_balance;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "                            Total Balances = " << counter << endl << endl;
	return_to_main_screen(user);
}

void ATM_check_balance(client_lib::struct_client client)
{
	system("cls");
	cout << "=========================================================\n\n";
	cout << "                    Check Balance Screen \n\n";
	cout << "=========================================================\n\n";
	cout << "Your Balance is " << client.account_balance << endl;
	return_to_ATM_main_screen(client);
}

void transactions_screen(user_lib::struct_user user)
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                       Transactions Screen \n";
	cout << "===========================================================\n";
	cout << "            [1] Deposit  \n";
	cout << "            [2] Withdraw  \n";
	cout << "            [3] Total Balances  \n";
	cout << "            [4] Main Screen \n";
	cout << "===========================================================\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 4] ", 1, 4);
	if (choice == 1)
		deposit(user);
	else if (choice == 2)
		withdraw(user);
	else if (choice == 3)
		total_balances(user);
	else if (choice == 4)
		main_screen(user);
}

void Exit_program()
{
	system("cls");
	cout << "-----------------------------------------------------\n\n";
	cout << "                      Program End.\n\n";
	cout << "-----------------------------------------------------\n\n";
	system("pause>0");
	return ;
}

void manage_users_screen(user_lib::struct_user user)
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                      Manage Users Screen \n";
	cout << "==============================================================\n";
	cout << "            [1] Show Users List  \n";
	cout << "            [2] Add New User  \n";
	cout << "            [3] Delete User  \n";
	cout << "            [4] Update User  \n";
	cout << "            [5] Find User \n";
	cout << "            [6] Main Screen  \n";
	cout << "==============================================================\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 6] ", 1, 6);
	if (choice == enum_chioce_user::user_list)
		show_user_list(user);
	else if (choice == enum_chioce_user::new_user)
		add_new_user(user);
	else if (choice == enum_chioce_user::delete_user)
		delete_user_from_list(user);
	else if (choice == enum_chioce_user::update_user)
		update_user_in_list(user);
	else if (choice == enum_chioce_user::find_user)
		find_user_in_list(user);
	else if (choice == enum_chioce_user::main_menue)
		main_screen(user);
	
}

void main_screen(user_lib::struct_user user)
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                       Main Screen \n";
	cout << "==============================================================\n";
	cout << "            [1] Show Client List  \n";
	cout << "            [2] Add New Client  \n";
	cout << "            [3] Delete Client  \n";
	cout << "            [4] Update Client Info  \n";
	cout << "            [5] Find Client \n";
	cout << "            [6] Transactions  \n";
	cout << "            [7] Manage Users  \n";
	cout << "            [8] Logout  \n";
	cout << "            [9] Exit  \n";
	cout << "==============================================================\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 9] ", 1, 9);
	if (choice == enum_chioce_client::client_list)
	{
		if (user.permissions_details.client_list == 0)
			access_denied(user);
		else
			show_client_list(user);
	}
	else if (choice == enum_chioce_client::new_client)
	{
		if (user.permissions_details.new_client == 0)
			access_denied(user);
		else
			add_new_client(user);
	}
	else if (choice == enum_chioce_client::delete_client)
	{
		if (user.permissions_details.delete_client == 0)
			access_denied(user);
		else
			delete_client_from_list(user);
	}
	else if (choice == enum_chioce_client::update_client)
	{
		if (user.permissions_details.update_client == 0)
			access_denied(user);
		else
			update_client_in_list(user);
	}
	else if (choice == enum_chioce_client::find_client)
	{
		if (user.permissions_details.find_client == 0)
			access_denied(user);
		else
			find_client_in_list(user);
	}
	else if (choice == enum_chioce_client::transactions)
	{
		if (user.permissions_details.transactions == 0)
			access_denied(user);
		else
			transactions_screen(user);
	}
	else if (choice == enum_chioce_client::manage_users)
	{
		if (user.permissions_details.manage_users == 0)
			access_denied(user);
		else
			manage_users_screen(user);
	}
	else if (choice == enum_chioce_client::user_logout)
		login_for_users();
	else if (choice == enum_chioce_client::client_Exit)
		main_entry();
}

void ATM_main_screen(client_lib::struct_client client)
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                      ATM Main Screen \n";
	cout << "==============================================================\n";
	cout << "            [1] Quick Withdraw  \n";
	cout << "            [2] Normal Withdraw  \n";
	cout << "            [3] Deposit  \n";
	cout << "            [4] Check Balance  \n";
	cout << "            [5] Logout \n";
	cout << "            [6] Exit \n";
	cout << "==============================================================\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 6] ", 1, 6);
	if (choice == enum_chioce_ATM::en_quick_withdraw)
		quick_withdraw(client);
	else if (choice == enum_chioce_ATM::en_normal_withdraw)
		normal_withdraw(client);
	else if (choice == enum_chioce_ATM::en_deposit)
		ATM_deposit(client);
	else if (choice == enum_chioce_ATM::en_check_balance)
		ATM_check_balance(client);
	else if (choice == enum_chioce_ATM::client_logout)
		login_for_clients();
	else if (choice == enum_chioce_ATM::ATM_Exit)
		main_entry();
}

void login_for_users()
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                       Login Screen \n";
	cout << "==============================================================\n\n\n";
	user_lib::struct_user user;
	vector<user_lib::struct_user> v_users = file_lib::load_users_data_from_file(file_lib::users_file_name);
	string user_name = input_lib::read_user_name();
	string password = input_lib::read_password();
	while (!file_lib::find_user_by_name_and_password(user_name, password, v_users, user))
	{
		cout << "Invalid User name / Password\n";
		user_name = input_lib::read_user_name();
		password = input_lib::read_password();
	}
	main_screen(user);

}

void login_for_clients()
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                      ATM Login Screen \n";
	cout << "==============================================================\n\n\n";
	client_lib::struct_client client;
	vector<client_lib::struct_client> v_clients = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	string account_number = input_lib::read_client_account_number();
	string pin_code = input_lib::read_client_pin_code();
	while (!file_lib::find_client_by_account_number_and_pincode(account_number, pin_code, v_clients, client))
	{
		cout << "Invalid Account number / Pin code\n";
		account_number = input_lib::read_client_account_number();
		pin_code = input_lib::read_client_pin_code();
	}
	ATM_main_screen(client);

}

void main_entry()
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                      Welcome to Samir's Bank \n";
	cout << "==============================================================\n";
	cout << "                    ||                   ||                   \n";
	cout << "  Account Manager   ||        ATM        ||        Exit       \n";
	cout << "                    ||                   ||                   \n";
	cout << "        ***         ||        ***        ||        ***        \n";
	cout << "        [1]         ||        [2]        ||        [3]        \n";
	cout << "        ***         ||        ***        ||        ***        \n";
	cout << "==============================================================\n\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 3] ", 1, 3);
	if (choice == enum_main_entry::bank_management)
		login_for_users();
	else if (choice == enum_main_entry::ATM)
		login_for_clients();
	else if (choice == enum_main_entry::final_Exit)
		Exit_program();
}

int main()
{
	main_entry();
	return 0;
}