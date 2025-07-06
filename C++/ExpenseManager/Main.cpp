#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

#include "Transaction.hpp"
#include "ExpenseManager.hpp"

ExpenseManager expenseManager;
bool menuFlag = true;

void displayUI();
void handleCreateTransaction();
void handleViewTransaction();
void handleDeleteTransaction();
void handleExportTransaction();
void handleViewHistoryTransaction();
void handleViewAllTransactions();
void handleEditTransaction();
void saveTransactionsToFile();
void loadTransactionsFromFile();

const std::string SAVE_FILE = "transactions.csv";

int main()
{
    loadTransactionsFromFile();
    displayUI();
    saveTransactionsToFile();
    return 0;
}

void displayUI()
{
    while (menuFlag)
    {
        int userChoice{};

        std::cout << "\n\n --- Welcome to Expense Manager! --- \n\n"
            "Choose what you want to do:\n"
            "1) Create a transaction\n"
            "2) View a transaction\n"
            "3) Delete a transaction\n"
            "4) Export all transactions\n"
            "5) View transaction's history\n"
            "6) View all transactions\n"
            "7) Edit a transaction\n"
            "0) Exit\n"
            "Your choice: ";

        std::cin >> userChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (userChoice)
        {
        case 1:
            handleCreateTransaction();
            break;
        case 2:
            handleViewTransaction();
            break;
        case 3:
            handleDeleteTransaction();
            break;
        case 4:
            handleExportTransaction();
            break;
        case 5:
            handleViewHistoryTransaction();
            break;
        case 6:
            handleViewAllTransactions();
            break;
        case 7:
            handleEditTransaction();
            break;
        case 0:
            menuFlag = false;
            break;
        default:
            std::cout << "There is no functionality for this choice.\n";
            break;
        }
    }
}

void handleCreateTransaction()
{
    std::string transactionName;
    std::string transactionCategory;
    double transactionAmount{};
    std::string transactionCommentary;
    Type transactionType;
    int typeChoice{};

    std::cout << "\n\n --- Create a transaction --- \n\n"
        "Transaction's name: ";
    std::cin >> transactionName;

    std::cout << "Transaction's category: ";
    std::cin >> transactionCategory;

    std::cout << "Transaction's amount: ";
    std::cin >> transactionAmount;

    std::cin.ignore();
    std::cout << "Transaction's commentary (optional): ";
    std::getline(std::cin, transactionCommentary);

    std::cout << "Transaction's type:\n"
        "1) Income\n"
        "2) Expense\n\n"
        "Your choice: ";

    std::cin >> typeChoice;

    if (typeChoice == 1)
        transactionType = Type::Income;
    else if (typeChoice == 2)
        transactionType = Type::Expense;
    else {
        std::cout << "Undefined transaction type. Transaction not created.\n";
        return;
    }

    Transaction transaction(
        transactionName,
        transactionCategory,
        transactionAmount,
        std::chrono::system_clock::now(),
        transactionCommentary,
        transactionType
    );

    expenseManager.addTransaction(transaction);

    std::cout << "Transaction created successfully!\n";
}

void handleViewAllTransactions()
{
    expenseManager.viewAllTransactions();
}

void handleViewTransaction()
{
    int transactionID{};

    std::cout << "\n\n --- View a specific transaction --- \n\n"
        "Enter transaction's ID (starting from 0): ";

    std::cin >> transactionID;

    try {
        const auto& transaction = expenseManager.getTransaction(transactionID);
        expenseManager.viewTransaction(transaction, transactionID);
    }
    catch (const std::out_of_range&) {
        std::cout << "Invalid transaction ID. Please try again.\n";
    }
}

void handleDeleteTransaction()
{
    int transactionID{};

    std::cout << "\n\n --- Delete a specific transaction --- \n\n"
        "Enter transaction's ID (starting from 0): ";

    std::cin >> transactionID;

    if (expenseManager.deleteTransaction(transactionID)) {
        std::cout << "Transaction deleted successfully.\n";
    }
    else {
        std::cout << "Failed to delete transaction.\n";
    }
}

void handleEditTransaction()
{
    int transactionID{};
    std::cout << "\n\n --- Edit a transaction --- \n\n"
        "Enter transaction's ID (starting from 0): ";
    std::cin >> transactionID;

    try {
        const auto& original = expenseManager.getTransaction(transactionID);

        std::string transactionName = original.name;
        std::string transactionCategory = original.category;
        double transactionAmount = original.amount;
        std::string transactionCommentary = original.commentary;
        Type transactionType = original.type;
        int typeChoice{};

        std::cout << "Current name [" << transactionName << "]: ";
        std::cin >> transactionName;

        std::cout << "Current category [" << transactionCategory << "]: ";
        std::cin >> transactionCategory;

        std::cout << "Current amount [" << transactionAmount << "]: ";
        std::cin >> transactionAmount;

        std::cin.ignore();
        std::cout << "Current comment [" << transactionCommentary << "]: ";
        std::getline(std::cin, transactionCommentary);

        std::cout << "Current type: " << (transactionType == Type::Income ? "Income" : "Expense") << "\n"
            "1) Income\n"
            "2) Expense\n"
            "Your choice: ";
        std::cin >> typeChoice;

        if (typeChoice == 1)
            transactionType = Type::Income;
        else if (typeChoice == 2)
            transactionType = Type::Expense;

        Transaction updated(transactionName, transactionCategory, transactionAmount,
            std::chrono::system_clock::now(), transactionCommentary, transactionType);

        if (expenseManager.editTransaction(transactionID, updated))
            std::cout << "Transaction updated successfully!\n";
        else
            std::cout << "Failed to update transaction.\n";

    }
    catch (const std::exception&) {
        std::cout << "Invalid ID.\n";
    }
}

void handleExportTransaction()
{
    std::string filename;
    std::cout << "\n\n --- Export Transactions to CSV --- \n\n"
        "Enter filename (e.g., transactions.csv): ";
    std::cin >> filename;

    try {
        expenseManager.exportToCSV(filename);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void handleViewHistoryTransaction()
{
    std::cout << "\nFeature not implemented yet.\n";
}

void saveTransactionsToFile()
{
    try {
        expenseManager.exportToCSV(SAVE_FILE);
    }
    catch (...) {
        std::cout << "Warning: Failed to auto-save transactions.\n";
    }
}

void loadTransactionsFromFile()
{
    std::ifstream inFile(SAVE_FILE);
    if (!inFile.is_open()) return;

    std::string line;
    std::getline(inFile, line); // skip header

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, category, amountStr, timeStr, commentary, typeStr;

        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, timeStr, ',');
        std::getline(ss, commentary, ',');
        std::getline(ss, typeStr);

        double amount = std::stod(amountStr);

        std::tm tm{};
        std::istringstream timeStream(timeStr);
        timeStream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        Type type = (typeStr == "Income") ? Type::Income : Type::Expense;

        Transaction t(name, category, amount, tp, commentary, type);
        expenseManager.addTransaction(t);
    }
}
