#include <iostream>
#include <string>
#include <limits>

const int DEFAULT = 0;

void resetStream();
bool intInRange(int num, int lower, int upper);
bool intGT(int num, int lower = 0, int = 0);
bool intLT(int num, int upper = 0, int = 0);
bool intGTEQ(int num, int lower = 0, int = 0);
bool intLTEQ(int num, int upper = 0, int = 0);
int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower = 0, int upper = 0);
int factorial(int n);
long fibNum(long f[], long n);
int iterativeFibonacci(int n);          
int recursiveFibonacci(int n);          
void moveDisks(int, char source, char destination, char spare);

int main()
{
    std::string prompt = "Enter a number between 1 and 50: ";
    std::string err = "You did not enter a number between 1 and 50.";
    int num = inputInt(prompt, err, intInRange, 1, 50);
    std::cout << "Factorial of " << num << " is " << factorial(num) << std::endl;

    prompt = "Enter the first Fibonacci Number: ";
    err = "The number entered must be greater than 0.";
    long fibNum1 = inputInt(prompt, err, intGTEQ);

    prompt = "Enter the second Fibonacci Number: ";
    err = "The number entered must be greater than or equal to " + std::to_string(fibNum1);
    long fibNum2 = inputInt(prompt, err, intGTEQ, fibNum1);

    prompt = "Enter the position of the desired Fibonacci number (at least 2): ";
    err = "The number must be greater than or equal to 2.";
    long nthFibonacci = inputInt(prompt, err, intGTEQ, 2);

    // Recursive Fibonacci with memoization
    long* fibseq = new long[nthFibonacci];
    for (int i = 0; i < nthFibonacci; i++) {
        fibseq[i] = -1;
    }
    fibseq[0] = fibNum1;
    fibseq[1] = fibNum2;

    std::cout << "\n--- Recursive Fibonacci with Memoization ---\n";
    std::cout << "The " << nthFibonacci << "th Fibonacci number is " << fibNum(fibseq, nthFibonacci) << std::endl;

    delete[] fibseq;  // to prevent memory leak

    // User can chooses between recursive or iterative for built-in Fibonacci
    prompt = "\nEnter a number n to get the nth Fibonacci number (built-in): ";
    err = "The number entered must be greater than or equal to 0.";
    int n = inputInt(prompt, err, intGTEQ);

    std::cout << "\nUsing iterative method: ";
    std::cout << "Fibonacci(" << n << ") = " << iterativeFibonacci(n) << std::endl;

    std::cout << "Using recursive method: ";
    std::cout << "Fibonacci(" << n << ") = " << recursiveFibonacci(n) << std::endl;

    std::cout << "\n--- Tower of Hanoi (Move 5 disks) ---\n";
    moveDisks(5, 'A', 'C', 'B');

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;
    std::cout << std::endl;
    if (std::cin && valid(theNum, lower, upper))
    {
        return theNum;
    }
    if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        resetStream();
    }
    std::cout << err << std::endl;
    return inputInt(prompt, err, valid, lower, upper);
}

bool intInRange(int num, int lower, int upper)
{
    return num >= lower && num <= upper;
}
bool intGT(int num, int lower, int)
{
    return num > lower;
}
bool intLT(int num, int upper, int)
{
    return num < upper;
}
bool intGTEQ(int num, int lower, int)
{
    return num >= lower;
}
bool intLTEQ(int num, int upper, int)
{
    return num <= upper;
}

int factorial(int n)
{
    if (n < 0) return 0;
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

// Recursive Fibonacci that has memoization
long fibNum(long f[], long n)
{
    if (n < 0) return 0;
    if (f[n - 1] != -1) return f[n - 1];
    f[n - 1] = fibNum(f, n - 1) + fibNum(f, n - 2);
    return f[n - 1];
}

int iterativeFibonacci(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    int prev1 = 0, prev2 = 1, current = 0;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return current;
}

// Added Basic Recursive Fibonacci here.
int recursiveFibonacci(int n)
{
    if (n <= 1) return n;
    return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
}

void moveDisks(int count, char source, char destination, char spare)
{
    if (count > 0)
    {
        moveDisks(count - 1, source, spare, destination);
        std::cout << "Move disk " << count << " from " << source << " to " << destination << std::endl;
        moveDisks(count - 1, spare, destination, source);
    }
}
