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
	std::uniform_real_distribution<> random(from, to);
	return random(rng);
}

void notifyAboutProgress(int& size, unsigned int progress, string&& message) {
	if(progress % (size/4) == 0) {
		cout << progress * 100 / size << "% " << message << " created" << endl;
	}
}

void generateUsers(vector<User>& users) {
	cout << "Generating users..." << endl;
	ifstream nameStream("../assets/names.json");

	bool streamConnected = nameStream.is_open();
	string name;
	if (streamConnected) {
		nameStream >> name;
	}
	int size = 1000;
	for (int i = 1; i <= size; i++) {
		if (streamConnected) {
			nameStream >> name;
			name = name.substr(1, name.length() - 3);
		} else {
			name = generateRandomString(8);
		}

		User user(std::to_string(i), name, generateRandomNumber(1, 1000));
//		User user(std::to_string(i), generateRandomString(5), generateRandomNumber(1, 1000)); // Or just use this
		users.push_back(user);

		notifyAboutProgress(size, i, "users");
	}

	nameStream.close();
	cout << "All users have been generated succesfully" <<  endl;
}

int iterateUserIndex(int& i, unsigned int size) {
	return ++i >= size ? 0 : i;
}

void generateTransactions(vector<Transaction>& transactions, vector<User>& users) {
	cout << "Generating transactions..." << endl;
	int size = 10000;
	User* user1;
	User* user2;

	double amount;
	bool repeat = true;
	int times = 0;
	int i = 0;
	while (transactions.size() != size) {
		user1 = &users[i];
		i = iterateUserIndex(i, users.size());
		user2 = &users[i];
		amount = generateRandomNumber(10, 50);
		do {
			if (user1->getDebit() >= amount) {
				transactions.emplace_back(user1, user2, amount);
				repeat = false;
			} else if (user2->getDebit() >= amount) {
				transactions.emplace_back(user2, user1, amount);
				repeat = false;
			} else {
				amount = generateRandomNumber((int)amount, 50);
				times++;
			}
		} while(repeat && times < 3);

		if(times >= 3) {
			i++;
		}

		notifyAboutProgress(size, transactions.size(), "transactions");
	}
	cout << "All transactions have been generated succesfully" << endl;
}