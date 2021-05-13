#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>   

#include <algorithm>
namespace peregruz {
	class BigNumber {
	private:
		int sign_;
		std::vector<int> digits;
		void trim();
	public:
		BigNumber() {}
		BigNumber(int64_t num);
		BigNumber(const char s[]);

		std::pair<BigNumber, BigNumber> division(BigNumber other);
		BigNumber sumDigits(BigNumber other);
		BigNumber subDigits(BigNumber other);
		bool operator>(BigNumber other);
		bool operator< (BigNumber other);
		bool operator>= (BigNumber other);
		bool operator<= (BigNumber other);
		BigNumber operator-(BigNumber other);
		BigNumber& operator=(const BigNumber& other);
		BigNumber operator+(BigNumber other);
		BigNumber operator *(BigNumber other);
		BigNumber operator/(BigNumber other);
		BigNumber operator%(BigNumber other);

		friend std::ostream& operator<<(std::ostream& out, const BigNumber& bn);
	protected:

	};

};



