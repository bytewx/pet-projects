#ifndef EXPENSE_MANAGER_HPP
#define EXPENSE_MANAGER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "Transaction.hpp"

/**
 * @class ExpenseManager
 * @brief Manages financial transactions: creation, deletion, editing, viewing, and exporting.
 */
class ExpenseManager
{
private:
	std::vector<Transaction> transactions;

public:
	/**
	 * @brief Adds a new transaction.
	 * @param transaction The transaction to add.
	 */
	void addTransaction(const Transaction& transaction)
	{
		transactions.push_back(transaction);
	}

	/**
	 * @brief Displays all transactions to the console.
	 */
	void viewAllTransactions() const
	{
		if (transactions.empty())
		{
			std::cout << "\n\nNo transactions recorded yet.\n";
			return;
		}

		std::cout << "\n\nAll transactions:\n";

		for (size_t i = 0; i < transactions.size(); ++i)
		{
			std::cout << "Transaction ID: " << i << "\n";
			transactions[i].print();
		}
	}

	/**
	 * @brief Returns all transactions.
	 * @return A const reference to the transaction list.
	 */
	const std::vector<Transaction>& getAllTransactions() const
	{
		return transactions;
	}

	/**
	 * @brief Returns a transaction by its ID.
	 * @param transactionID ID of the transaction.
	 * @return Const reference to the transaction.
	 * @throws std::out_of_range if ID is invalid.
	 */
	const Transaction& getTransaction(int transactionID) const
	{
		if (transactionID < 0 || transactionID >= static_cast<int>(transactions.size()))
		{
			throw std::out_of_range("Transaction ID is out of range.");
		}
			
		return transactions[transactionID];
	}

	/**
	 * @brief Displays a specific transaction.
	 * @param transaction The transaction to display.
	 * @param transactionID Its ID for reference.
	 */
	void viewTransaction(const Transaction& transaction, int transactionID) const
	{
		std::cout << "\n--- Transaction #" << transactionID << " ---\n";

		transaction.print();
	}

	/**
	 * @brief Edits an existing transaction.
	 * @param transactionID The ID of the transaction to edit.
	 * @param updatedTransaction The new transaction data.
	 * @return True if successful, false if ID is invalid.
	 */
	bool editTransaction(int transactionID, const Transaction& updatedTransaction)
	{
		if (transactionID < 0 || transactionID >= static_cast<int>(transactions.size()))
		{
			return false;
		}

		transactions[transactionID] = updatedTransaction;

		return true;
	}

	/**
	 * @brief Deletes a transaction by ID.
	 * @param transactionID The ID of the transaction.
	 * @return True if successful, false if ID is invalid.
	 */
	bool deleteTransaction(int transactionID)
	{
		if (transactionID < 0 || transactionID >= static_cast<int>(transactions.size()))
		{
			std::cout << "Invalid transaction ID. Please try again.\n";

			return false;
		}

		transactions.erase(transactions.begin() + transactionID);

		return true;
	}

	/**
	 * @brief Exports transactions to a CSV file.
	 * @param filename Name of the output file.
	 * @throws std::runtime_error if file can't be opened.
	 */
	void exportToCSV(const std::string& filename) const
	{
		std::ofstream outFile(filename);

		if (!outFile)
		{
			throw std::runtime_error("Failed to open file for writing.");
		}

		outFile << "Name,Category,Amount,Date,Commentary,Type\n";

		for (const auto& transaction : transactions)
		{
			std::time_t t = std::chrono::system_clock::to_time_t(transaction.createdAt);
			std::tm tm{};
			localtime_s(&tm, &t);

			char buffer[100];
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);

			outFile << '\"' << transaction.name << "\","
				<< '\"' << transaction.category << "\","
				<< transaction.amount << ","
				<< '\"' << buffer << "\","
				<< '\"' << transaction.commentary << "\","
				<< (transaction.type == Type::Income ? "\"Income\"" : "\"Expense\"")
				<< "\n";
		}

		outFile.close();
		std::cout << "Transactions successfully exported to " << filename << "\n";
	}
};

#endif
