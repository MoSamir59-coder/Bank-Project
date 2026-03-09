#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "String funcs.h"
#include "File process.h"
#include "Client process.h"
#include "Reading input.h"

using namespace std;


enum enum_chioce { client_list = 1, new_client = 2, delete_client = 3, update_client = 4, find_client = 5,transactions = 6, Exit = 7 };

void main_screen();

void return_to_main_screen()
{
	cout << "\n\n\n\nPress any key to return to main screen ... \n";
	system("pause>0");
	system("cls");
	main_screen();
}

void show_client_list()
{
	system("cls");
	client_lib::print_all_clients_data(file_lib::load_clients_data_from_file(file_lib::clients_file_name));

	return_to_main_screen();
}

void add_new_client()
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
		add_new_client();
	return_to_main_screen();
}

void delete_client_from_list()
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Delete Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	file_lib::delete_client_by_account_number(account_number, data);
	return_to_main_screen();
}

void update_client_in_list()
{
	system("cls");
	cout << "---------------------------------------------------------\n\n";
	cout << "                    Update Clients Screen\n\n";
	cout << "---------------------------------------------------------\n\n";
	string account_number = input_lib::read_client_account_number();
	vector <client_lib::struct_client> data = file_lib::load_clients_data_from_file(file_lib::clients_file_name);
	file_lib::update_client_by_account_number(account_number, data);
	return_to_main_screen();
}

void find_client_in_list()
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
		find_client_in_list();
	return_to_main_screen();
}

void deposit()
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
			deposit();
		return_to_main_screen();
		return;
	}
	else
	{
		cout << "\nClient with account number (" << account_number << ") is Not Found!";
		cout << "\n\nDo you want to try again ?  Y / N ?    ";
		cin >> deposit_more;
		while (toupper(deposit_more) == 'Y')
			deposit();
		return_to_main_screen();
	}
}

void withdraw()
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
			withdraw();
		return_to_main_screen();
		return;
	}
	else
	{
		cout << "\nClient with account number (" << account_number << ") is Not Found!";
		cout << "\n\nDo you want to try again ?  Y / N ?    ";
		cin >> withdraw_more;
		while (toupper(withdraw_more) == 'Y')
			withdraw();
	}
}

void total_balances()
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
	return_to_main_screen();
}

void transactions_screen()
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
		deposit();
	else if (choice == 2)
		withdraw();
	else if (choice == 3)
		total_balances();
	else if (choice == 4)
		main_screen();
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

void main_screen()
{
	system("cls");
	cout << "==============================================================\n";
	cout << "                       Main Screen \n";
	cout << "===========================================================\n";
	cout << "            [1] Show Client List  \n";
	cout << "            [2] Add New Client  \n";
	cout << "            [3] Delete Client  \n";
	cout << "            [4] Update Client Info  \n";
	cout << "            [5] Find Client \n";
	cout << "            [6] Transactions  \n";
	cout << "            [7] Exit  \n";
	cout << "===========================================================\n";
	short choice = input_lib::read_positive_number_in_range("Choose What do you want to do [1 : 7] ", 1, 7);
	if (choice == enum_chioce::client_list)
		show_client_list();
	else if (choice == enum_chioce::new_client)
		add_new_client();
	else if (choice == enum_chioce::delete_client)
		delete_client_from_list();
	else if (choice == enum_chioce::update_client)
		update_client_in_list();
	else if (choice == enum_chioce::find_client)
		find_client_in_list();
	else if (choice == enum_chioce::transactions)
		transactions_screen();
	else if (choice == enum_chioce::Exit)
		Exit_program();
}


int main()
{
	main_screen();
	return 0;
}