#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "String funcs.h"

using namespace std;

namespace user_lib
{

	struct struct_permission
	{
		int client_list;
		int new_client;
		int delete_client;
		int update_client;
		int find_client;
		int transactions;
		int manage_users;
	};

//====================================================================================================================

	struct struct_user
	{
		string user_name;
		string password;
		int permissions;
		bool mark_for_delete = false;
		struct_permission permissions_details;

	};

//====================================================================================================================

	struct_user convert_line_to_record(string line, string separator = "#//#")
	{
		struct_user user;
		vector<string> user_data;
		user_data = string_lib::split_string(line, separator);
		if (user_data.size() > 0)
		{
		    user.user_name = user_data[0];
			user.password = user_data[1];
			user.permissions = stoi(user_data[2]); //cast string to int
			int num = user.permissions;
			if (num == -1)
			{
				user.permissions_details.client_list = 1;
				user.permissions_details.new_client = 2;
				user.permissions_details.delete_client = 4;
				user.permissions_details.update_client = 8;
				user.permissions_details.find_client = 16;
				user.permissions_details.transactions = 32;
				user.permissions_details.manage_users = 64;
			}
			else
			{
				if (num % 2 == 1)
					user.permissions_details.client_list = 1;
				else
					user.permissions_details.client_list = 0;
				num /= 2;
				if (num % 2 == 1)
					user.permissions_details.new_client = 2;
				else
					user.permissions_details.new_client = 0;
				num /= 2;
				if (num % 2 == 1)
					user.permissions_details.delete_client = 4;
				else
					user.permissions_details.delete_client = 0;
				num /= 2;

				if (num % 2 == 1)
					user.permissions_details.update_client = 8;
				else
					user.permissions_details.update_client = 0;
				num /= 2;

				if (num % 2 == 1)
					user.permissions_details.find_client = 16;
				else
					user.permissions_details.find_client = 0;
				num /= 2;

				if (num % 2 == 1)
					user.permissions_details.transactions = 32;
				else
					user.permissions_details.transactions = 0;
				num /= 2;

				if (num % 2 == 1)
					user.permissions_details.manage_users = 64;
				else
					user.permissions_details.manage_users = 0;
				num /= 2;

			}
		}
		return user;
	}

//====================================================================================================================

	string convert_record_to_line(struct_user user, string separator = "#//#")
	{
		int num = (user.permissions_details.client_list | user.permissions_details.delete_client | user.permissions_details.find_client | user.permissions_details.manage_users | user.permissions_details.new_client | user.permissions_details.transactions | user.permissions_details.update_client);
		if (num == 127)
			user.permissions = -1;
		else
			user.permissions = num;
		string user_record = "";
		user_record += user.user_name + separator;
		user_record += user.password + separator;
		user_record += to_string(user.permissions);
		return user_record;
	}
	
//====================================================================================================================

	bool mark_user_for_delete_by_name(string user_name, vector <struct_user>& v_users)
	{
		for (struct_user& C : v_users)
		{
			if (C.user_name == user_name)
			{
				C.mark_for_delete = true;
				return true;
			}
		}
		return false;
	}

//====================================================================================================================

	struct_permission read_permissions()
	{
		user_lib::struct_permission permissions;
		char answer;
		cout << "Do you want to give access to : \n\n";
		cout << "Show client list? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.client_list = 1;
		}
		else
			permissions.client_list = 0;
		cout << "\n\nAdd new client? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.new_client = 2;
		}
		else
			permissions.new_client = 0;
		cout << "\n\nDelete client? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.delete_client = 4;
		}
		else
			permissions.delete_client = 0;
		cout << "\n\nUpdate client? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.update_client = 8;
		}
		else
			permissions.update_client = 0;
		cout << "\n\nFind client? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.find_client = 16;
		}
		else
			permissions.find_client = 0;
		cout << "\n\nTransactions? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.transactions = 32;
		}
		else
			permissions.transactions = 0;
		cout << "\n\nManage users? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions.manage_users = 64;
		}
		else
			permissions.manage_users = 0;

		return permissions;

	}

//====================================================================================================================

	struct_user change_user_record(string user_name)
	{
		struct_user user;
		user.user_name = user_name;
		cout << "Enter Password? ";
		getline(cin >> ws, user.password);
		user.permissions_details = read_permissions();
		return user;
	}

//====================================================================================================================

	void print_user_card(struct_user user)
	{
		cout << "\n\nThe following is the extracted user record:\n";
		cout << "\nUser name: " << user.user_name;
		cout << "\nPassword : " << user.password;
		cout << "\nPermissions : " << user.permissions;
	}

//====================================================================================================================

	void print_user_record(struct_user user)
	{
		cout << "| " << setw(30) << left << user.user_name;
		cout << "| " << setw(30) << left << user.password;
		cout << "| " << setw(30) << left << user.permissions;
	}

//====================================================================================================================

	void print_all_users_data(vector <struct_user> v_users)
	{
		cout << "\n\t\t\t\t\tUser List (" << v_users.size() << ") User(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(30) << "User name";
		cout << "| " << left << setw(30) << "Password";
		cout << "| " << left << setw(30) << "Permissions";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		for (struct_user user : v_users)
		{
			print_user_record(user);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

//====================================================================================================================



}

