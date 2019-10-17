//
// Created by zygisau on 2019-09-23.
//

#ifndef HASH_ZA256_H
#define HASH_ZA256_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>
#include <numeric>
using std::cin; using std::cout; using std::string; using std::endl;
using std::ifstream; using std::ofstream; using std::stringstream; using std::hex;
using std::ceil; using std::vector;

namespace zygisau {
	class ZA256 {
	private:
		static string DEFAULT_HASH() { return "C0794730544D2337ED9D5FC52E9A17243AE5237C9347CCF7A246210EBE4AEDAC"; };
		explicit ZA256() = default;

		static unsigned long convertAndShift(char &character, unsigned long ind, unsigned long mixer) {
			return (unsigned int) character ^ mixer;
		}

		/* Populates string by inserting 64 symbols form the ASCII table.
		 * Takes first and last letters as offsets */
		static void populateString(string &str) {
			string leftPart;
			string rightPart;

			/* Variable which is either the first symbol
			 * or 32 symbols behind the first letter in the ASCII table */
			unsigned char leftBound;

            /* Variable which is either the 32nd symbol (in the ASCII table)
             * or 32nd + what's left from the leftPart */
            unsigned long rightBound;

            if ((int)str.front() < 32) {
                leftBound = '\0';
                rightBound = 32 + (32 - (int)str.front());
			} else {
			    leftBound = str.front() - 32;
			    rightBound = 32;
			}

			// Through every letter from the leftBound to the the first letter from the string
			for (unsigned char i = leftBound; i < str[0]; i++) {
                leftPart += i;
			}
			// Through every letter from the last letter of the string to the the rightBound
			int i = 1;
            while (rightBound > i) {
            	rightPart += (char)(127 - i);
            	i++;
            }

			str.insert(0, leftPart);
            str += rightPart;
		}

		static void stringToIntArray(string &str, vector<unsigned long> &array) {
			populateString(str);
			mixUp(str, 0, (int)(str.front() + str.back()));

			array.reserve((unsigned long) ceil((double) str.length() / 2));
			// Variable that helps to make every letter dependent on other letters
			unsigned long mixer = (unsigned long)str[0] ^ str.length();

			// Iterates through the beginning and ending of a string, converts it, shifts both results and pushes everything to the vector *
			for (unsigned long i = 0; i < str.length() / 2; ++i) {
				array.push_back(
						convertAndShift(str[i], i, mixer) + convertAndShift(str[str.length() - 1 - i], i, mixer));
				mixer = array.back();
			}
			// Hashes middle letter if the length of a string is odd number
			if (str.length() % 2 != 0) {
				array.push_back(convertAndShift(str[str.length() / 2 + 1], str.length() / 2 + 1, mixer));
			}

			array.shrink_to_fit();
		}

		static string convertAndResize(vector<unsigned long> &array) {
			string hash;
			std::stringstream stream;
			for (auto &integer: array) {
				stream << hex << integer;
			}
			hash = stream.str();

			string payload = hash.substr(0, 64);
			string surplus = hash.substr(64);

			int i = 0;
			vector<unsigned long> newArray;
			for (char& character : surplus) {
				std::for_each(payload.begin(), payload.end(), [character, &newArray] (char &c) {
					newArray.push_back((unsigned)c ^ (unsigned)character);
					c = newArray.back();
				});
			}

			stream.str(std::string());
			for (auto &integer: newArray) {
				stream << hex << integer;
			}
			hash = stream.str();
			return hash.substr(0, 64);
		}

		/* Makes the hash more dependant from every letter of the string */
		static void mixUp (string& str, unsigned long index, unsigned long sauce) {
			str[index] = (unsigned)str[index] ^ sauce;
			str[str.length() - 1 - index] = (unsigned)str[str.length() - 1 - index] ^ sauce;
			sauce += (unsigned)str[index] ^ (unsigned)str[str.length() - 1 - index];

			if (++index < str.length()) {
				mixUp(str, index, sauce);
			}
		}
		static void mixUp (vector<unsigned long>& array, unsigned long index, unsigned long sauce) {
			auto front = &array[index];
			auto back = array.end() - 1 - index;

			*front ^= sauce;
			*back ^= sauce;
			sauce += *front ^ *back;

			if (++index < array.size()) {
				mixUp(array, index, sauce);
			}
		}

	public:

		static string hash(string str) {
			if (str.empty())
				return DEFAULT_HASH();

			vector<unsigned long> array;
			stringToIntArray(str, array);
			mixUp(array, 0, array.front() + array.back());

			return convertAndResize(array);
		}
	};
}


#endif //HASH_ZA256_H
