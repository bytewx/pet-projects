#include <iostream>

/**
 * Function to calculate and display arithmetic operations on two numbers.
 * 
 * @param int firstNumber First number that is entered by the user
 * @param int secondNumber Second number that is entered by the user
 * @return void
 */
void arithmeticOperations(int firstNumber, int secondNumber)
{
    std::cout << "Addition: " << firstNumber + secondNumber << std::endl;
    std::cout << "Subtraction: " << firstNumber - secondNumber << std::endl;
    std::cout << "Multiplication: " << firstNumber * secondNumber << std::endl;
    
    if (secondNumber == 0) {
        std::cout << "Division: " << 0 << std::endl;
        std::cout << "Modulo: " << 0 << std::endl;
    } else {
        std::cout << "Division: " << firstNumber / secondNumber << std::endl;
        std::cout << "Modulo: " << firstNumber % secondNumber << std::endl;
    }
}

/**
 * Function to perform logical operations on two numbers.
 * 
 * @param int firstNumber First number that is entered by the user
 * @param int secondNumber Second number that is entered by the user
 * @return void
 */
void logicalOperations(int firstNumber, int secondNumber)
{
    if (firstNumber && secondNumber && firstNumber + secondNumber > 10) {
        std::cout << "Numbers are greater than 10." << std::endl;
    }

    if (firstNumber > 10 || secondNumber > 10) {
        std::cout << "One or both of the numbers are greater than 10." << std::endl;
    }

    if (firstNumber != 10) {
        std::cout << "First number is not equal to 10." << std::endl;
    }
}

/**
 * Function to perform bitwise operations on two numbers.
 *
 * @param int firstNumber First number that is entered by the user
 * @param int secondNumber Second number that is entered by the user
 * @return void
 */
void bitwiseOperations(int firstNumber, int secondNumber)
{
    int ANDOperatorResult = firstNumber & secondNumber;
    int OROperatorResult = firstNumber | secondNumber;
    int XOROperatorResult = firstNumber ^ secondNumber;
    int NOTOperatorResultFirstNumber = ~firstNumber;
    int NOTOperatorResultSecondNumber = ~secondNumber;
    int LEFTSHIFTOperatorResult = firstNumber << secondNumber;
    int RIGHTSHIFTOperatorResult = firstNumber >> secondNumber;

    std::cout << "AND operator: " << ANDOperatorResult << std::endl;
    std::cout << "OR operator: " << OROperatorResult << std::endl;
    std::cout << "XOR operator: " << XOROperatorResult << std::endl;
    std::cout << "NOT operator (first number): " << NOTOperatorResultFirstNumber << std::endl;
    std::cout << "NOT operator (second number): " << NOTOperatorResultSecondNumber << std::endl;
    std::cout << "LEFT SHIFT operator: " << LEFTSHIFTOperatorResult << std::endl;
    std::cout << "RIGHT SHIFT operator: " << RIGHTSHIFTOperatorResult << std::endl;
}

/**
 * Function to summarize even numbers from first one to second one.
 *
 * @param int start Number from which to start with
 * @param int end Number from which to end with
 * @return int sum Summation of even numbers
 */
int sumEvenNumbers(int start, int end)
{
    int sum = 0;

    for (int i = start; i <= end; i++) {
        if (i % 2 == 0) {
            sum += i;
        }
    }

    return sum;
}

/**
 * Function to count divisors of the second number.
 *
 * @param int secondNumber Second number that is entered by the user
 * @return int count Count of divisord of the second number
 */
int countDivisorsSecondNumber(int secondNumber)
{
    int count = 1;
    int index = 1;

    while (index <= secondNumber) {
        if (secondNumber % index == 0) {
            count++;
        }

        index++;
    }

    return count;
}

int main()
{
    std::cout << "Practice Project #1: Basic operations" << std::endl;

    int firstNumber, secondNumber = 0;

    std::cout << "Enter first number: ";
    std::cin >> firstNumber;

    std::cout << "Enter second number: ";
    std::cin >> secondNumber;

    std::cout << std::endl;

    arithmeticOperations(firstNumber, secondNumber);
    std::cout << std::endl;

    logicalOperations(firstNumber, secondNumber);
    std::cout << std::endl;

    bitwiseOperations(firstNumber, secondNumber);
    std::cout << std::endl;

    std::cout << "Sum of even numbers is equal to: " << sumEvenNumbers(firstNumber, secondNumber) << std::endl;
    std::cout << "Second number's divisors count is equal to: " << countDivisorsSecondNumber(secondNumber) << std::endl;

    return 0;
}
