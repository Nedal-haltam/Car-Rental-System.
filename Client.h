#pragma once

struct client {
	client() = default;
	client(string name, string phonenumber)
		: name(name), phonenumber(phonenumber) {}

	string name;
	string phonenumber;

	vector<int> carids;




	bool operator==(const client& client)
	{
		return this->name == client.name and this->phonenumber == client.phonenumber;
	}
};

