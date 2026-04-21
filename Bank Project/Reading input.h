#pragma once

#include <iostream>
#include "Client process.h"
#include "User process.h"

using namespace std;

namespace input_lib
{
	int read_positive_number_in_range(string message, int from, int to)
	{
		int n;
		do
		{
			cout << message << endl;
			cin >> n;
		} while (n < from || n > to);
		return n;
	}

//====================================================================================================================

	int random_number(int From, int To)
	{
		int rand_num = rand() % (To - From + 1) + From;
		return rand_num;
	}

//====================================================================================================================

	int read_positive_number(string message)
	{
		int n;
		do
		{
			cout << message << endl;
			cin >> n;
		} while (n <= 0);
		return n;
	}

//====================================================================================================================

	int read_positive_number_multiplier_of(int num)
	{
		int n;
		do
		{
			cout << "Enter a number multiple of (" << num << ") " << endl;
			cin >> n;
		} while (n % num != 0);
		return n;
	}

//====================================================================================================================

	int read_number()
	{
		int Number;
		cout << "Please enter a number?" << endl;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number, Enter a valid one:" << endl;
			cin >> Number;
		}
		return Number;
	}

//====================================================================================================================

	string read_client_account_number()
	{
		string account_number = "";
		cout << "\nPlease enter account number ---> ";
		cin >> account_number;
		return account_number;
	}

//====================================================================================================================

	string read_client_pin_code()
	{
		string pin_code = "";
		cout << "\nPlease enter pincode ---> ";
		cin >> pin_code;
		return pin_code;
	}

//====================================================================================================================

	client_lib::struct_client read_new_client()
	{
		client_lib::struct_client client;
		cout << "Enter Account Number? ";
		cin.ignore(1, '\n');
		getline(cin, client.account_number);
		cout << "Enter PinCode? ";
		getline(cin, client.pin_code);
		cout << "Enter Name? ";
		getline(cin, client.name);
		cout << "Enter Phone? ";
		getline(cin, client.phone);
		cout << "Enter AccountBalance? ";
		cin >> client.account_balance;
		return client;
	}

//====================================================================================================================

	string read_user_name()
	{
		string user_name = "";
		cout << "\nPlease enter user name ---> ";
		cin >> user_name;
		return user_name;
	}

//====================================================================================================================

	string read_password()
	{
		string password = "";
		cout << "\nPlease enter password ---> ";
		cin >> password;
		return password;
	}

//====================================================================================================================

	user_lib::struct_user read_new_user()
	{
		user_lib::struct_user user;
		char answer;
		cout << "Enter User name? ";
		cin.ignore(1, '\n');
		getline(cin, user.user_name);
		cout << "Enter Password? ";
		getline(cin, user.password);
		cout << "Do you want to give full access? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			user.permissions = -1;
			return user;
		}
		else
		{
			user.permissions_details = user_lib::read_permissions();
		}
		return user;
	}

}


