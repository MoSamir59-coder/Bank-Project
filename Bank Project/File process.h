#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Client process.h"

using namespace std;

namespace file_lib
{
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
}