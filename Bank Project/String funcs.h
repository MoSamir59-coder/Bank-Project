#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace string_lib
{
	string read_string()
	{
		string s;
		cout << "Please enter your string \n";
		getline(cin, s);
		return s;
	}

//====================================================================================================================

	vector<string> split_string(string s, string delim)
	{
		vector<string> v_string;
		short pos = 0;
		string s_word; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = s.find(delim)) != std::string::npos)
		{
			s_word = s.substr(0, pos); // store the word
			if (s_word != "")
			{
				v_string.push_back(s_word);
			}
			s.erase(0, pos + delim.length()); /* erase() until
			position and move to next word. */
		}
		if (s != "")
		{
			v_string.push_back(s); // it adds last word of the string.
		}
		return v_string;
	}

//====================================================================================================================

}