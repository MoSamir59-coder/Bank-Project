#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "String funcs.h"

using namespace std;

namespace client_lib
{
	struct struct_client
	{
		string account_number;
		string pin_code;
		string name;
		string phone;
		double account_balance;
		bool mark_for_delete = false;
	};

//====================================================================================================================

	struct_client convert_line_to_record(string line, string separator = "#//#")
	{
		struct_client client;
		vector<string> client_data;
		client_data = string_lib::split_string (line, separator);
		if (client_data.size() > 0)
		{
			client.account_number = client_data[0];
			client.pin_code = client_data[1];
			client.name = client_data[2];
			client.phone = client_data[3];
			client.account_balance = stod(client_data[4]); //cast string to double
		}
		return client;
	}

//====================================================================================================================

	string convert_record_to_line(struct_client client, string separator = "#//#")
	{
		string client_record = "";
		client_record += client.account_number + separator;
		client_record += client.pin_code + separator;
		client_record += client.name + separator;
		client_record += client.phone + separator;
		client_record += to_string(client.account_balance);
		return client_record;
	}

//====================================================================================================================

	void print_client_card(struct_client client)
	{
		cout << "\n\nThe following is the extracted client record:\n";
		cout << "\nAccount Number: " << client.account_number;
		cout << "\nPin Code : " << client.pin_code;
		cout << "\nName : " << client.name;
		cout << "\nPhone : " << client.phone;
		cout << "\nAccount Balance: " << client.account_balance;
	}

//====================================================================================================================

	void print_client_record(struct_client client)
	{
		cout << "| " << setw(15) << left << client.account_number;
		cout << "| " << setw(10) << left << client.pin_code;
		cout << "| " << setw(40) << left << client.name;
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(12) << left << client.account_balance;
	}

//====================================================================================================================

	void print_all_clients_data(vector <struct_client> v_clients)
	{
		cout << "\n\t\t\t\t\tClient List (" <<v_clients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		for (struct_client client : v_clients)
		{
			print_client_record(client);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

//====================================================================================================================

	bool mark_client_for_delete_by_account_number(string account_number, vector <struct_client>& vClients)
	{
		for (struct_client& C : vClients)
		{
			if (C.account_number == account_number)
			{
				C.mark_for_delete = true;
				return true;
			}
		}
		return false;
	}

//====================================================================================================================

	struct_client change_client_record(string account_number)
	{
		struct_client client;
		client.account_number = account_number;
		cout << "\n\nEnter PinCode? ";
		getline(cin >> ws, client.pin_code);
		cout << "Enter Name? ";
		getline(cin, client.name);
		cout << "Enter Phone? ";
		getline(cin, client.phone);
		cout << "Enter AccountBalance? ";
		cin >> client.account_balance;
		return client;
	}

	
}
