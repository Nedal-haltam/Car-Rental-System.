#pragma once

#include<iostream>

using namespace std;




struct car {
	static int ids;



	car() { carid = 0; model = 0; costperday = 0; available = 1; }
	car(int carid, string carname, int model, int costperday, bool available = 1)
		:carid(carid), carname(carname), model(model), costperday(costperday), available(available) {}

	int carid;
	string carname;
	int model, costperday;
	bool available;

	std::chrono::system_clock::time_point start_day;
	std::chrono::system_clock::time_point start_hour;


	std::chrono::system_clock::time_point end_day;
	std::chrono::system_clock::time_point end_hour;





	void start_timing()
	{
		start_day = std::chrono::system_clock::from_time_t(std::time(nullptr));
		start_hour = std::chrono::system_clock::now();
	}

	void end_timing()
	{

		end_day = std::chrono::system_clock::now();
		end_hour = std::chrono::system_clock::now();

		calculation();

	}



private:
	void calculation()
	{
		auto durationindays = std::chrono::duration_cast<std::chrono::duration<int, std::ratio<86400>>>(end_day - start_day);

		auto durationinhours = std::chrono::duration_cast<std::chrono::hours>(end_hour - start_hour);

		int extra = durationinhours.count() - durationindays.count() * 24;

		cout << "the calculation : \n";
		cout << "duration : " << "(" << durationindays.count() << ")" << "days and " << "(" << extra << ")" << "hours." << "\n";


		cout << "the amount is : " << costperday * durationindays.count() + ((int)(costperday / 24) * extra) << "\n\n";

	}

}; int car::ids = 0;



