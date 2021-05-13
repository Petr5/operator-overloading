#include "BigNumber.h"




int main() {
	peregruz::BigNumber k1("-640000"), k2("640001");
	
	std::cout << "First number: " << k1 << std::endl;
	std::cout << "Second number: " << k2 << std::endl;
	std::cout << "More: " << (k1 > k2) << std::endl;

	std::cout << "Fewer: " << (k1 < k2) << std::endl;
	std::cout << "More or =: " << (k1 >= k2) << std::endl;
	std::cout << "Fewer or =: " << (k1 <= k2) << std::endl;
	std::cout << "Sum: " << k1 + k2 << std::endl;

	
	std::cout << "Sub: " << k1 - k2 << std::endl;


	std::cout << "Multiply: " << k1 * k2 << std::endl;
	
	std::cout << "Division: " << k1 / k2 << std::endl;
	std::cout << "Modulo: " << k1 % k2 << std::endl;



}
