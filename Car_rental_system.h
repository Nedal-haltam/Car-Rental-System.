#pragma once
#include<string>
#include<unordered_map>
#include<vector>
#include<chrono>
#include"Car.h"
#include"Client.h"
using namespace std;

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);

		if (hash1 != hash2) {
			return hash1 ^ hash2;
		}

		// If hash1 == hash2, their XOR is zero.
		return hash1;
	}
};



class car_rental_system {

private:

	unordered_map<int, car> cars;
	unordered_map< pair<string, string>, client, hash_pair > clients;

public:

	//adding technique may differ
	car_rental_system()
	{
		cars[++car::ids] = car(car::ids, "carone", 2000, 12);
		cars[++car::ids] = car(car::ids, "cartwo", 2020, 2);
		cars[++car::ids] = car(car::ids, "carthree", 2023, 122);
		cars[++car::ids] = car(car::ids, "carfour", 2021, 162);

	}

	void Register(const pair<string, string>& p)
	{
		cout << "do you want to confirm registering.\n";
		cout << "1-yes\n2-no\n"; int ch; cin >> ch; ch--; cin.ignore();
		if (ch) return;
		cout << "registering..." << endl << "done!" << endl;
		clients[p] = client(p.first, p.second);
		manageclients();
	}


	void manageclients()
	{

		string entryname;
		string entryphonenumber;

		cout << "insert your name : "; getline(cin, entryname);
		cout << "\ninsert your phone number : "; getline(cin, entryphonenumber);

		pair<string, string> p(entryname, entryphonenumber);


		cout << endl << endl;


		int choice;
		if (clients.find(p) != clients.end())
		{
			cout << "you are registered" << endl << endl;
			cout << "do you want to\n1-rent\n2-derent \n"; cin >> choice; choice--;
			if (!choice) rentcar(clients[p]);

			else derentcar(clients[p]);
		}

		else
			Register(p);
	}

	void rentcar(client& c)
	{
		cout << "                 available cars choose the desired car : " << endl;

		print_cars();




		int entryid;
		cin >> entryid;
		cin.ignore();

		if (cars.find(entryid) == cars.end() or !cars[entryid].available) { cout << "invalid id " << endl; rentcar(c); }

		else
		{
			c.carids.push_back(entryid);
			cars[entryid].available = 0;
			cars[entryid].start_timing();
			cout << "      car is rented successfuly!       \n\n";
		}
	}

	void derentcar(client& c)
	{
		cout << "\n\ncars currently renting : \n";

		if (c.carids.empty()) {
			cout << "\n\n no cars to derent\n\n";
			return;
		}

		for (auto& i : c.carids)
		{
			cout << "car id : " << i << "\n";
			cout << "car name : " << cars[i].carname << "\n\n";
		}

		int entryid; cin >> entryid;
		cin.ignore();
		auto it = find(c.carids.begin(), c.carids.end(), entryid);

		if (it == c.carids.end() or cars[entryid].available) { cout << "\n\ninvalid id \n\n"; derentcar(c); }


		else
		{
			cars[entryid].end_timing();
			c.carids.erase(it);
			cars[entryid].available = 1;
			cout << "      car is derented successfuly  \n\n";

		}
	}




	void print_cars()
	{
		for (auto& i : cars)
			if (i.second.available)
			{
				cout << "\ncar id : " << i.second.carid << endl;
				cout << "car name : " << i.second.carname << endl;
				cout << "car model : " << i.second.model << endl;
				cout << "car cost per day : " << i.second.costperday << endl;
			}
	}
};

