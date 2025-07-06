#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

enum class Type
{
	Income = 1,
	Expense = 2
};

class Transaction
{
public:
	std::string							  name;
	std::string							  category;
	double								  amount;
	std::chrono::system_clock::time_point createdAt;
	std::string							  commentary;
	Type								  type;

	Transaction(const std::string& name,
				const std::string& category,
				double amount,
				std::chrono::system_clock::time_point createdAt,
				const std::string& commentary,
				Type type)
				:
				name(name),
				category(category),
				amount(amount),
				createdAt(createdAt),
				commentary(commentary),
				type(type)
	{}
	
	void print() const
	{
		std::time_t createdTime = std::chrono::system_clock::to_time_t(createdAt);
		std::tm timeStruct{};

		if (localtime_s(&timeStruct, &createdTime) == 0)
		{
			std::cout << "\n\n-----------------------------\n";
			std::cout << "Name      : " << name											   << "\n";
			std::cout << "Category  : " << category										   << "\n";
			std::cout << "Amount    : " << amount										   << "\n";
			std::cout << "Date      : " << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S") << "\n";
			std::cout << "Comment   : " << commentary									   << "\n";
			std::cout << "Type      : " << (type == Type::Income ? "Income" : "Expense")   << "\n";
			std::cout << "-----------------------------\n\n";
		}
		else
		{
			std::cout << "Date      : [invalid time]\n";
		}
	}

};

#endif
