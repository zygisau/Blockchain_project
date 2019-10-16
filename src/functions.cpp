//
// Created by zygisau on 2019-10-11.
//

#include "functions.h"

string generateRandomString(size_t len) {
	char *s = new char[len];
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<> random(1, 10);

	for (size_t i = 0; i < len; ++i) {
		int randomChar = random(rng) % (26 + 26 + 10);
		if (randomChar < 26)
			s[i] = (char) ('a' + randomChar);
		else if (randomChar < 26 + 26)
			s[i] = (char) ('A' + randomChar - 26);
		else
			s[i] = (char) ('0' + randomChar - 26 - 26);
	}
	s[len] = 0;
	return string(s);
}

double generateRandomNumber(const int& from, const int& to) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<> random(from, to);
	return random(rng);
}

void generateUsers(vector<User>& users) {
	cout << "Generating users..." << endl;
	ifstream nameStream("../assets/names.json");

	bool streamConnected = nameStream.is_open();
	string name;
	if (streamConnected) {
		nameStream >> name;
	}

	for (int i = 1; i <= 10000; i++) {
		if (streamConnected) {
			nameStream >> name;
			name = name.substr(1, name.length() - 3);
		} else {
			name = generateRandomString(8);
		}

		User user(std::to_string(i), name, generateRandomNumber(1, 1000));
//		User user(std::to_string(i), generateRandomString(5), generateRandomNumber(1, 1000)); // Or just use this
		users.push_back(user);

		if(i % 2500 == 0) {
			cout << i / 100 << "% users created" << endl;
		}
	}

	nameStream.close();
	cout << "All users have been generated succesfully" <<  endl;
}

void generateTransactions(vector<Transaction>& transactions) {
	cout << "Generating transactions..." << endl;
	
}