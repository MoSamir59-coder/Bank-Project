#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Client process.h"
#include "User process.h"

using namespace std;

namespace file_lib
{
	const string users_file_name = "users.txt";
	const string clients_file_name = "clients.txt";

//====================================================================================================================

	void add_data_line_to_file(string file_name, string data_line)
	{
		fstream my_file;
		my_file.open(file_name, ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << data_line << endl;
			my_file.close();
		}
	}

//====================================================================================================================


	vector <client_lib::struct_client> load_clients_data_from_file(string file_name)
	{
		vector <client_lib::struct_client> v_clients;
		fstream my_file;
		my_file.open(file_name, ios::in);//read Mode
		if (my_file.is_open())
		{
			string line;
			client_lib::struct_client client;
			while (getline(my_file, line))
			{
				if (line == "")
				{
					continue;
				}
				client = client_lib::convert_line_to_record(line);
				v_clients.push_back(client);
			}
			my_file.close();
		}
		return v_clients;
	}

//====================================================================================================================

	bool find_client_by_account_number(string account_number, vector<client_lib::struct_client> v_clients, client_lib::struct_client& client)
	{
		for (client_lib::struct_client C : v_clients)
		{
			if (C.account_number == account_number)
			{
				client = C;
				return true;
			}
		}
		return false;
	}

//====================================================================================================================

	bool find_client_by_account_number_and_pincode(string account_number, string pin_code, vector<client_lib::struct_client> v_clients, client_lib::struct_client& client)
	{
		for (client_lib::struct_client C : v_clients)
		{
			if ((C.account_number == account_number) && (C.pin_code == pin_code))
			{
				client = C;
				return true;
			}
		}
		return false;
	}

//====================================================================================================================

	vector <client_lib::struct_client> save_clients_data_to_file(string file_name, vector<client_lib::struct_client> v_clients)
	{
		fstream my_file;
		my_file.open(file_name, ios::out);//overwrite
		string data_line;
		if (my_file.is_open())
		{
			for (client_lib::struct_client C : v_clients)
			{
				if (C.mark_for_delete == false)
				{
					//we only write records that are not marked for delete.
					data_line = client_lib::convert_record_to_line(C);
					my_file << data_line << endl;
				}
			}
			my_file.close();
		}
		return v_clients;
	}

//====================================================================================================================

	bool delete_client_by_account_number(string account_number, vector<client_lib::struct_client>& v_clients)
	{
		char delete_more = 'Y';
		client_lib::struct_client client;
		char answer = 'n';
		if (find_client_by_account_number(account_number, v_clients,client))
		{
			client_lib::print_client_card(client);
			cout << "\n\nAre you sure you want delete this client? y/n ? ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				client_lib::mark_client_for_delete_by_account_number(account_number,v_clients);
				save_clients_data_to_file(clients_file_name, v_clients);
				//Refresh Clients
				v_clients = load_clients_data_from_file(clients_file_name);
				cout << "\n\nClient Deleted Successfully, do you want to delete more clients ? Y / N ?  . \n";
				cin >> delete_more;
				while (toupper(delete_more) == 'Y')
					delete_client_by_account_number(account_number, v_clients);
				return true;
			}
		}
		else
		{
			cout << "\nClient with Account Number (" << account_number << ") is Not Found!";
			return false;
		}
	}

//====================================================================================================================

	bool update_client_by_account_number(string account_number, vector<client_lib::struct_client>& v_clients)
	{
		char update_more = 'Y';
		client_lib::struct_client client;
		char answer = 'n';
		if (find_client_by_account_number(account_number, v_clients,client))
		{
			client_lib::print_client_card(client);
			cout << "\n\nAre you sure you want update this client? y/n? ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				for (client_lib::struct_client& C : v_clients)
				{
					if (C.account_number == account_number)
					{
						C = client_lib::change_client_record(account_number);
						break;
					}
				}
				save_clients_data_to_file(clients_file_name, v_clients);
				cout << "\n\nClient Updated Successfully, do you want to update more clients ? Y / N ?  . \n";
				cin >> update_more;
				while (toupper(update_more) == 'Y')
					update_client_by_account_number(account_number, v_clients);
				return true;
			}
		}
		else
		{
			cout << "\nClient with Account Number (" << account_number << ") is Not Found!";
			return false;
		}
	}

//====================================================================================================================

	vector <user_lib::struct_user> load_users_data_from_file(string file_name)
	{
		vector <user_lib::struct_user> v_users;
		fstream my_file;
		my_file.open(file_name, ios::in);//read Mode
		if (my_file.is_open())
		{
			string line;
			user_lib::struct_user user;
			while (getline(my_file, line))
			{
				if (line == "")
				{
					continue;
				}
				user = user_lib::convert_line_to_record(line);
				v_users.push_back(user);
			}
			my_file.close();
		}
		return v_users;
	}

//====================================================================================================================

	bool find_user_by_name(string user_name, vector<user_lib::struct_user> v_users, user_lib::struct_user& user)
	{
		for (user_lib::struct_user C : v_users)
		{
			if (C.user_name == user_name)
			{
				user = C;
				return true;
			}
		}
		return false;
	}


//====================================================================================================================

	bool find_user_by_name_and_password(string user_name, string password, vector<user_lib::struct_user> v_users, user_lib::struct_user& user)
	{
		for (user_lib::struct_user C : v_users)
		{
			if ((C.user_name == user_name) && (C.password == password))
			{
				user = C;
				return true;
			}
		}
		return false;
	}
	
//====================================================================================================================

	vector <user_lib::struct_user> save_users_data_to_file(string file_name, vector<user_lib::struct_user> v_users)
	{
		fstream my_file;
		my_file.open(file_name, ios::out);//overwrite
		string data_line;
		if (my_file.is_open())
		{
			for (user_lib::struct_user C : v_users)
			{
				if (C.mark_for_delete == false)
				{
					//we only write records that are not marked for delete.
					data_line = user_lib::convert_record_to_line(C);
					my_file << data_line << endl;
				}
			}
			my_file.close();
		}
		return v_users;
	}

//====================================================================================================================

	bool delete_user_by_name(string user_name, vector<user_lib::struct_user>& v_users)
	{
		if (user_name == "admin")
		{
			cout << "You can't dalete this user!!\n\n";
			return false;
		}
		char delete_more = 'Y';
		user_lib::struct_user user;
		char answer = 'n';
		if (find_user_by_name(user_name, v_users, user))
		{
			cout << "\n\nAre you sure you want delete this user? y/n ? ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				user_lib::mark_user_for_delete_by_name(user_name, v_users);
				save_users_data_to_file(users_file_name, v_users);
				//Refresh Clients
				v_users = load_users_data_from_file(users_file_name);
				cout << "\n\nUser Deleted Successfully, do you want to delete more users ? Y / N ?  . \n";
				cin >> delete_more;
				while (toupper(delete_more) == 'Y')
					delete_user_by_name(user_name, v_users);
				return true;
			}
		}
		else
		{
			cout << "\nUser (" << user_name << ") is Not Found!";
			return false;
		}
	}

//====================================================================================================================

	bool update_user_by_name(string user_name, vector<user_lib::struct_user>& v_users)
	{
		if (user_name == "admin")
		{
			cout << "You can't apdate this user!!\n\n";
			return false;
		}
		char update_more = 'Y';
		user_lib::struct_user user;
		char answer = 'n';
		if (find_user_by_name(user_name, v_users, user))
		{
			user_lib::print_user_card(user);
			cout << "\n\nAre you sure you want update this user? y/n? ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				for (user_lib::struct_user& C : v_users)
				{
					if (C.user_name == user_name)
					{
						C = user_lib::change_user_record(user_name);
						break;
					}
				}
				save_users_data_to_file(users_file_name, v_users);
				cout << "\n\nUser Updated Successfully, do you want to update more users ? Y / N ?  . \n";
				cin >> update_more;
				while (toupper(update_more) == 'Y')
					update_user_by_name(user_name, v_users);
				return true;
			}
		}
		else
		{
			cout << "\nUser (" << user_name << ") is Not Found!";
			return false;
		}
	}
}