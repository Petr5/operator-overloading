#include "BigNumber.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <algorithm>


namespace peregruz {

	BigNumber BigNumber::sumDigits(BigNumber other) {
		other.sign_ = 0;
		BigNumber copy = *this;
		copy.sign_ = 0;
		BigNumber ans;
		int64_t len = std::max(this->digits.size(), other.digits.size());
		int s_i = 0;
		int sum_i, sum_i_a, sum_i_b;
		for (int64_t i = 0; i < len; i++) {
			if (i >= this->digits.size()) {
				sum_i_a = 0;
			}
			else {
				sum_i_a = this->digits[i];
			}
			if (i >= other.digits.size()) {
				sum_i_b = 0;
			}
			else {
				sum_i_b = other.digits[i];
			}
			sum_i = (sum_i_a + sum_i_b + s_i) % 10;
			s_i = (sum_i_a + sum_i_b + s_i) / 10;
			ans.digits.push_back(sum_i);
		}
		if (s_i != 0) {
			ans.digits.push_back(s_i);
		}

		return ans;
	}


	BigNumber::BigNumber(int64_t num) {
		if (num < 0) {
			sign_ = 1;
			num *= -1;
		}
		while (num != 0) {
			digits.push_back(num % 10);
			num = num / 10;
		}
	}

	BigNumber::BigNumber(const char s[]) {
		if (s[0] == '-') {
			sign_ = 1;

		}
		for (int i = strlen(s) - 1; i >= 0; i--) {
			if (s[i] != '-') {
				int k = s[i] - '0';
				digits.push_back(k);
			}
		}
	}



	BigNumber BigNumber::subDigits(BigNumber other) {
		BigNumber ans;
		BigNumber res;
		other.sign_ = 0;
		res = *this;
		res.sign_ = 0;
		int64_t len = std::max(this->digits.size(), other.digits.size());
		int s_i = 0;
		int sub_i, sub_i_a, sub_i_b;
		ans.sign_ = 0;
		for (int64_t i = 0; i < len; i++) {
			if (i >= this->digits.size()) {
				sub_i_a = 0;
			}
			else {
				sub_i_a = this->digits[i];
			}
			if (i >= other.digits.size()) {
				sub_i_b = 0;
			}
			else {
				sub_i_b = other.digits[i];
			}
			if (res >= other) {

				sub_i = sub_i_a - sub_i_b - s_i;
				if (sub_i < 0) {
					sub_i += 10;
					s_i = 1;
				}
				else {
					s_i = 0;
				}
				ans.digits.push_back(sub_i);
			}
			else {

				sub_i = sub_i_b - sub_i_a - s_i;
				if (sub_i < 0) {
					sub_i += 10;
					s_i = 1;
				}
				else {
					s_i = 0;
				}
				ans.digits.push_back(sub_i);
			}
		}
		ans.digits.push_back(0);
		while (ans.digits[ans.digits.size() - 1] == 0 && ans.digits.size() > 1) {
			ans.digits.pop_back();
		}
		
		return ans;
		
	}
	std::pair<BigNumber, BigNumber> BigNumber::division(BigNumber other) {
		std::pair<BigNumber, BigNumber> div_and_mod = {};
		BigNumber res;
		res.sign_ = 0;
		BigNumber subtrahend;
		int k;
		int i = this->digits.size() - 1;

		if (*this < other) {
			std::cout << "stupid";
			return { BigNumber("0"),*this };
		}
		while (i >= 0) {
			subtrahend.digits.insert(subtrahend.digits.begin(), digits[i]);
			k = 0;

			while (subtrahend > other) {
				subtrahend = subtrahend - other;
				k++;
				
			}

			if (k != 0) { res.digits.insert(res.digits.begin(), k); }
			i--;
			
		}

		res.sign_ = sign_ != other.sign_;
		div_and_mod.first = res;
		subtrahend.sign_ = sign_ != other.sign_;
		subtrahend.trim();
		div_and_mod.second = subtrahend;
		return div_and_mod;
	}
	//BigNumber multiply(int a) {
	//	BigNumber res;
	//	if (a == 0) {
	//		return static_cast<int64_t>(0);
	//	}
	//	int m_i = 0;
	//	int multiply_i, multiply_i_b;
	//	for (int64_t i = 0; i <= this->digits.size(); ++i) {
	//		if (i >= this->digits.size()) {
	//			multiply_i_b = 0;
	//		}
	//		else {
	//			multiply_i_b = this->digits[i];
	//		}
	//		multiply_i = (multiply_i_b * a + m_i) % 10;
	//		m_i = (multiply_i_b * a + m_i) / 10;
	//		res.digits.push_back(multiply_i);
	//	}
	//	/*if (res.digits.size() >= 100) {
	//		std::cout << "too big";
	//		exit(0);
	//	}*/
	//	/*int64_t zero = 0;
	//	res = zero;*/
	//	res.trim();
	//	return res;
	//}

	

	void BigNumber::trim() {
		while (digits.size() > 1 && !digits.back()) digits.pop_back();
	}
	std::ostream& operator<<(std::ostream& out, const BigNumber& bn) {
		if (bn.sign_) out << '-';
		/*while (bn.digits[bn.digits.size() - 1] == 0 && bn.digits.size() > 1) {
			bn.digits.pop_back();
		}
		*/
		for (int i = bn.digits.size() - 1; i >= 0; i--) {
			out << bn.digits[i];
		}
		return out;
	}
	bool BigNumber::operator>(BigNumber other) {
		int first;
		int second;
		int flag = -1;
		int64_t len = std::max(this->digits.size(), other.digits.size());
		if ((other.sign_) && (this->sign_ == 0)) {
			return true;
		}
		if ((this->sign_) && (other.sign_ == 0)) {
			return false;
		}
		for (int i = len - 1; i >= 0; i--) {
			if (i >= this->digits.size()) {
				first = 0;
			}
			else {
				first = this->digits[i];
			}
			if (i >= other.digits.size()) {
				second = 0;
			}
			else {
				second = other.digits[i];

			}
			if (first > second) {
				flag = 1;
				break;
			}
			else if (first < second) {
				flag = 0;
				break;
			}
		}
		if (flag == -1) {
			return false;

		}
		else if (flag == 0) {
			if ((this->sign_) && (other.sign_)) {
				return true;
			}
			else return false;
		}
		else {
			if ((this->sign_) && (other.sign_)) {
				return false;
			}
			else return true;
		}
	}
	
	bool BigNumber::operator< (BigNumber other) {
		int first;
		int second;
		int flag = -1;
		int64_t len = std::max(this->digits.size(), other.digits.size());
		if ((other.sign_) && (this->sign_ == 0)) {
			return false;
		}
		if ((this->sign_) && (other.sign_ == 0)) {
			return true;
		}
		for (int i = len - 1; i >= 0; i--) {
			if (i >= this->digits.size()) {
				first = 0;
			}
			else {
				first = this->digits[i];
			}
			if (i >= other.digits.size()) {
				second = 0;
			}
			else {
				second = other.digits[i];

			}
			if (first > second) {
				flag = 1;
				break;
			}
			else if (first < second) {
				flag = 0;
				break;
			}
		}
		if (flag == -1) {
			return false;

		}
		else if (flag == 0) {
			if ((this->sign_) && (other.sign_)) {
				return false;
			}
			else return true;
		}
		else {
			if ((this->sign_) && (other.sign_)) {
				return true;
			}
			else return false;
		}
	}
	bool BigNumber::operator>= (BigNumber other) {
		return !(*this < other);
	}
	bool BigNumber::operator<= (BigNumber other) {
		return !(*this > other);
	}
	BigNumber BigNumber::operator-(BigNumber other) {
		BigNumber ans_minus;
		if (sign_) {
			if (other.sign_) {
				ans_minus = this->subDigits(other);
				other.sign_ = 0;
				this->sign_ = 0;
				if (other > * this) {
					this->sign_ = 1;
					return ans_minus;
				}
				else {
					ans_minus.sign_ = 1;
					this->sign_ = 1;
					if (ans_minus.digits.size() == 1 && ans_minus.digits[0] == 0) ans_minus.sign_ = 0;
					return ans_minus;
				}
			}
			else {
				ans_minus = this->sumDigits(other);
				ans_minus.sign_ = 1;
				return ans_minus;
			}
		}
		else {
			if (other.sign_) {
				ans_minus = this->sumDigits(other);
				return ans_minus;
			}
			else {
				ans_minus = this->subDigits(other);
				other.sign_ = 0;
				this->sign_ = 0;
				if (*this > other) {
					return ans_minus;
				}
				else {
					ans_minus.sign_ = 1;
					if (ans_minus.digits.size() == 1 && ans_minus.digits[0] == 0) ans_minus.sign_ = 0;
					return ans_minus;
				}


			}
		}

		return this->subDigits(other);
	}
	BigNumber& BigNumber::operator=(const BigNumber& other) {
		digits = other.digits;
		sign_ = other.sign_;
		return *this;
	}
	BigNumber BigNumber::operator+(BigNumber other) {
		/*
		BigNumber rs = this->subDigits(other);
		rs.sign_ = !rs.sign_;
		*/
		BigNumber ans_plus;
		if (sign_) {
			if (other.sign_) {
				ans_plus = this->sumDigits(other);
				ans_plus.sign_ = !ans_plus.sign_;
				ans_plus.trim();
				return ans_plus;
			}
			else {
				ans_plus = this->subDigits(other);
				this->sign_ = 0;
				if (*this > other) {
					ans_plus.sign_ = 1;
					this->sign_ = 1;
					return ans_plus;
				}
				else {
					this->sign_ = 1;
					return ans_plus;
				}
			}
		}
		else {
			if (other.sign_) {
				ans_plus = this->subDigits(other);
				other.sign_ = 0;
				if (other > * this) {
					ans_plus.sign_ = 1;
					return ans_plus;
				}
				else {
					return ans_plus;
				}
			}
			else {
				ans_plus = this->sumDigits(other);
				ans_plus.trim();
				return ans_plus;
			}
		}
	}
	BigNumber BigNumber::operator*(BigNumber other) {
		BigNumber res = static_cast<int64_t>(0);
		res.sign_ = 0;
		if ((this->digits[0] == 0 && this->digits.size() == 1) || (other.digits[0] == 0 && other.digits.size() == 1)) {
			return "0";
		}
		for (int i = 0; i < digits.size(); ++i) {
			for (int j = 0; j < other.digits.size(); ++j) {
				res = res + digits[i] * other.digits[j] * std::pow(10, i) * std::pow(10, j);
			}
		}
		res.sign_ = sign_ != other.sign_;
		return res;
	}
	BigNumber BigNumber::operator/(BigNumber other) {
		return this->division(other).first;
	}
	BigNumber BigNumber::operator%(BigNumber other) {
		return this->division(other).second;
	}
	/*if (!other.digits.size()) {
		return static_cast<int64_t>(0);
	}
	if (other.digits.size() == 1) {
		return  this->multiply(other.digits[0]);
	}
	BigNumber ans_multiply;
	ans_multiply.sign_ = this->sign_ != other.sign_;
	int multi_i_a, multi_i;
	for (int64_t i = 0; i < this->digits.size(); i++) {
		if (i >= this->digits.size()) {
			multi_i_a = 0;
			break;
		}
		else {
			multi_i_a = this->digits[i];
		}
		ans_multiply = ans_multiply + this->multiply(multi_i_a) * power(10, i);
	}
	ans_multiply.trim();
	return ans_multiply;
}*/
};




