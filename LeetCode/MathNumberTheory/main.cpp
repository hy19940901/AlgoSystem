#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

// =====================
// Base Conversion & Numeric Simulation
// =====================

/**
 * Problem 1: Integer to Roman (LC 12) - [Greedy / Mapping Construction]
 * Description:
 * Convert an integer (1–3999) to Roman numeral.
 *
 * Approach:
 * - Define a descending list of (value, symbol) pairs for Roman numerals.
 * - Use a greedy approach: subtract the largest value repeatedly while appending its symbol.
 * - Loop through all defined values until the input becomes 0.
 *
 * Example:
 * Input: num = 1994
 * Output: "MCMXCIV"
 */
string intToRoman(int num) {
    vector<pair<int, string>> values = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string res;
    for (auto& [val, sym] : values) {
        while (num >= val) {
            res += sym;  // append Roman symbol
            num -= val;  // subtract value
        }
    }
    return res;
}

/**
 * Problem 2: Roman to Integer (LC 13) - [Greedy / Mapping Construction]
 * Description:
 * Convert a Roman numeral string to an integer.
 *
 * Approach:
 * - Create a map from Roman characters to integer values.
 * - Iterate the string:
 *   - If the current character is less than the next one, subtract it (like IV = 4).
 *   - Otherwise, add it.
 *
 * Example:
 * Input: s = "MCMXCIV"
 * Output: 1994
 */
int romanToInt(string s) {
    unordered_map<char, int> val = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        int curr = val[s[i]];
        int next = (i + 1 < s.length()) ? val[s[i + 1]] : 0;
        if (curr < next) res -= curr;  // subtractive
        else res += curr;              // additive
    }
    return res;
}

/**
 * Problem 3: Excel Column Title (LC 168) - [Base Conversion]
 * Description:
 * Convert a column number to its corresponding Excel title.
 *
 * Approach:
 * - Treat input as base-26, where A=1, B=2, ..., Z=26.
 * - Use (n - 1) for 0-indexing.
 * - Use modulo 26 to extract characters from least significant digit.
 *
 * Example:
 * Input: n = 28
 * Output: "AB"
 */
string convertToTitle(int n) {
    string res;
    while (n > 0) {
        n--;  // shift for 0-based index
        res = char('A' + (n % 26)) + res;
        n /= 26;
    }
    return res;
}

/**
 * Problem 4: Excel Column Number (LC 171) - [Base Conversion]
 * Description:
 * Convert Excel column title (e.g., "AB") into a column number.
 *
 * Approach:
 * - Iterate through the string.
 * - Treat as base-26 number: multiply accumulator and add char value.
 *
 * Example:
 * Input: s = "AB"
 * Output: 28
 */
int titleToNumber(string s) {
    int res = 0;
    for (char c : s) {
        res = res * 26 + (c - 'A' + 1);
    }
    return res;
}

/**
 * Problem 5: Add Binary (LC 67) - [Binary Simulation]
 * Description:
 * Add two binary strings and return the result as a binary string.
 *
 * Approach:
 * - Start from the least significant digits of both strings.
 * - Use a carry to keep track of overflow.
 * - Append each bit result to the front of the result string.
 * - Continue until both strings and carry are consumed.
 *
 * Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 */
string addBinary(string a, string b) {
    int i = a.size() - 1, j = b.size() - 1, carry = 0;
    string res;
    while (i >= 0 || j >= 0 || carry) {
        if (i >= 0) carry += a[i--] - '0';
        if (j >= 0) carry += b[j--] - '0';
        res = char('0' + (carry % 2)) + res;
        carry /= 2;
    }
    return res;
}

/**
 * Problem 6: Multiply Strings (LC 43) - [Simulation / Digit Math]
 * Description:
 * Multiply two non-negative integers represented as strings.
 *
 * Approach:
 * - Use a result vector of size m+n (maximum length).
 * - Multiply each digit and accumulate positionally.
 * - Handle carry by dividing and modulo operations.
 * - Skip leading zeros in the result.
 *
 * Example:
 * Input: "123", "456"
 * Output: "56088"
 */
string multiply(string num1, string num2) {
    int m = num1.size(), n = num2.size();
    vector<int> pos(m + n);
    for (int i = m - 1; i >= 0; --i)
        for (int j = n - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + pos[i + j + 1];
            pos[i + j] += sum / 10;
            pos[i + j + 1] = sum % 10;
        }
    string res;
    for (int p : pos)
        if (!(res.empty() && p == 0)) res += to_string(p);
    return res.empty() ? "0" : res;
}

/**
 * Problem 7: Count Primes (LC 204) - [Sieve of Eratosthenes]
 * Description:
 * Count the number of prime numbers less than a non-negative number, n.
 *
 * Approach:
 * - Use a boolean sieve initialized as true.
 * - Set multiples of each prime to false.
 * - Count the number of true entries.
 *
 * Example:
 * Input: n = 10
 * Output: 4 // primes are 2, 3, 5, 7
 */
int countPrimes(int n) {
    if (n <= 2) return 0;
    vector<bool> prime(n, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i < n; ++i)
        if (prime[i])
            for (int j = i * i; j < n; j += i)
                prime[j] = false;
    return count(prime.begin(), prime.end(), true);
}

/**
 * Problem 8: Trailing Zeroes in Factorial (LC 172) - [Factor Counting]
 * Description:
 * Count trailing zeroes in n! (factorial).
 *
 * Approach:
 * - Count how many times 5 appears as a factor in numbers from 1 to n.
 * - Accumulate n / 5 + n / 25 + ...
 *
 * Example:
 * Input: n = 100
 * Output: 24
 */
int trailingZeroes(int n) {
    int count = 0;
    while (n) {
        n /= 5;
        count += n;
    }
    return count;
}

/**
 * Problem 9: Power of Two (LC 231) - [Bit Manipulation]
 * Description:
 * Check if a given integer is a power of 2.
 *
 * Approach:
 * - Must be > 0 and have only one bit set.
 * - Use n & (n - 1) == 0 trick.
 *
 * Example:
 * Input: n = 16
 * Output: true
 */
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/**
 * Problem 10: Power of Three (LC 326) - [Loop Division]
 * Description:
 * Check if n is a power of 3.
 *
 * Approach:
 * - Repeatedly divide n by 3.
 * - If remainder ever not 0, return false.
 *
 * Example:
 * Input: n = 27
 * Output: true
 */
bool isPowerOfThree(int n) {
    if (n <= 0) return false;
    while (n % 3 == 0) n /= 3;
    return n == 1;
}

/**
 * Problem 11: Add Digits (LC 258) - [Digital Root / Math Trick]
 * Description:
 * Repeatedly add digits until result is a single digit.
 *
 * Approach:
 * - Use the digital root formula: (num - 1) % 9 + 1
 *
 * Example:
 * Input: 38
 * Output: 2
 */
int addDigits(int num) {
    return num == 0 ? 0 : (num - 1) % 9 + 1;
}

/**
 * Problem 12: Reverse Integer (LC 7) - [Math / Integer Overflow]
 * Description:
 * Reverse digits of an integer.
 * Return 0 on overflow.
 *
 * Approach:
 * - Use modulo and division to extract digits.
 * - Check if result would overflow before updating.
 *
 * Example:
 * Input: 123
 * Output: 321
 */
int reverse(int x) {
    int res = 0;
    while (x) {
        int digit = x % 10;
        x /= 10;
        if (res > INT_MAX / 10 || res < INT_MIN / 10) return 0;
        res = res * 10 + digit;
    }
    return res;
}

/**
 * Problem 13: Divide Two Integers (LC 29) - [Bit Shifting / Math]
 * Description:
 * Divide two integers without using multiplication, division or mod.
 *
 * Approach:
 * - Use bit shift doubling to subtract divisor from dividend.
 * - Handle sign separately.
 *
 * Example:
 * Input: 10 / 3
 * Output: 3
 */
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    long a = abs((long)dividend), b = abs((long)divisor), res = 0;
    while (a >= b) {
        long tmp = b, m = 1;
        while (a >= (tmp << 1)) tmp <<= 1, m <<= 1;
        a -= tmp;
        res += m;
    }
    return ((dividend > 0) ^ (divisor > 0)) ? -res : res;
}

/**
 * Problem 14: Pow(x, n) (LC 50) - [Fast Exponentiation]
 * Description:
 * Implement x^n (power function).
 *
 * Approach:
 * - Use binary exponentiation (divide and conquer).
 * - Handle negative exponents.
 *
 * Example:
 * Input: x = 2.0, n = 10
 * Output: 1024.0
 */
double myPow(double x, int n) {
    long long N = n;
    if (N < 0) x = 1 / x, N = -N;
    double res = 1;
    while (N) {
        if (N & 1) res *= x;
        x *= x;
        N >>= 1;
    }
    return res;
}

/**
 * Problem 15: Convert to Base 7 (LC 504) - [Base Conversion]
 * Description:
 * Convert an integer to its base 7 string representation.
 *
 * Approach:
 * - Handle sign and use modulo/division.
 * - Reverse result string at the end.
 *
 * Example:
 * Input: 100
 * Output: "202"
 */
string convertToBase7(int num) {
    if (num == 0) return "0";
    bool neg = num < 0;
    num = abs(num);
    string res;
    while (num) {
        res = to_string(num % 7) + res;
        num /= 7;
    }
    return neg ? "-" + res : res;
}

/**
 * Problem 16: Convert to Hex (LC 405) - [Base Conversion / Bit Manipulation]
 * Description:
 * Convert an integer to a lowercase hexadecimal string.
 *
 * Approach:
 * - Handle negative by unsigned conversion.
 * - Use modulo and lookup table.
 *
 * Example:
 * Input: 26
 * Output: "1a"
 */
string toHex(int num) {
    if (num == 0) return "0";
    unsigned int n = num;
    string res, hex = "0123456789abcdef";
    while (n) {
        res = hex[n % 16] + res;
        n /= 16;
    }
    return res;
}

/**
 * Problem 17: Nim Game (LC 292) - [Math / Game Theory]
 * Description:
 * Determine whether you can win the Nim game.
 *
 * Approach:
 * - You lose only if n is a multiple of 4.
 *
 * Example:
 * Input: n = 4
 * Output: false
 */
bool canWinNim(int n) {
    return n % 4 != 0;
}

/**
 * Problem 18: Divisor Game (LC 1025) - [Math / Game Theory]
 * Description:
 * Return true if Alice wins the divisor game.
 *
 * Approach:
 * - If n is even, Alice wins; odd, she loses.
 *
 * Example:
 * Input: n = 2
 * Output: true
 */
bool divisorGame(int n) {
    return n % 2 == 0;
}

/**
 * Problem 19: Sum of Two Integers (LC 371) - [Bit Manipulation]
 * Description:
 * Calculate sum of two integers without + or - operators.
 *
 * Approach:
 * - Use XOR for partial sum and AND+shift for carry.
 * - Repeat until carry is 0.
 *
 * Example:
 * Input: a = 1, b = 2
 * Output: 3
 */
int getSum(int a, int b) {
    while (b != 0) {
        unsigned carry = (unsigned)(a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

/**
 * Problem 20: Hamming Distance (LC 461) - [Bit Manipulation / XOR]
 * Description:
 * Return number of differing bits between x and y.
 *
 * Approach:
 * - XOR x and y, then count number of 1s in result.
 * - Use Brian Kernighan’s algorithm.
 *
 * Example:
 * Input: x = 1, y = 4
 * Output: 2
 */
int hammingDistance(int x, int y) {
    int xorVal = x ^ y, count = 0;
    while (xorVal) {
        xorVal &= xorVal - 1;
        count++;
    }
    return count;
}

/**
 * Problem 21: Basic Calculator II (LC 227) - [Math / Stack / Operator Precedence]
 * Description:
 * Evaluate a simple arithmetic expression string containing non-negative integers,
 * '+', '-', '*', and '/' operators with no parentheses. Division should truncate toward zero.
 *
 * Approach:
 * - Traverse the string character by character.
 * - When encountering a digit, build the full number.
 * - When encountering an operator or at the end of string:
 *     - If previous operator is '+' or '-', push value (or -value) to the stack.
 *     - If '* or '/', pop the top value, compute with current number, push result.
 * - Finally, sum all values in the stack for result.
 *
 * Time: O(n), Space: O(n)
 *
 * Example:
 * Input: s = "3+2*2"
 * Output: 7
 */
int calculate227(string s) {
    stack<int> stk;
    int num = 0;
    char op = '+';
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
        if ((!isdigit(c) && c != ' ') || i == s.size() - 1) {
            if (op == '+') stk.push(num);
            else if (op == '-') stk.push(-num);
            else if (op == '*') {
                int temp = stk.top(); stk.pop();
                stk.push(temp * num);
            } else if (op == '/') {
                int temp = stk.top(); stk.pop();
                stk.push(temp / num);
            }
            op = c;
            num = 0;
        }
    }
    int result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    return result;
}

/**
 * Problem 22: Basic Calculator I (LC 224) - [Stack / Parentheses / Simulation]
 * Description:
 * Evaluate an arithmetic expression string that contains '+', '-', integers, and parentheses.
 * Whitespace is ignored. Only integer division and no *, / operators.
 *
 * Approach:
 * - Traverse character by character.
 * - Maintain a result and current sign.
 * - Push previous result and sign to the stack when encountering '('.
 * - Pop and restore context when encountering ')'.
 * - On '+', '-', update sign. On number, accumulate result.
 *
 * Time: O(n), Space: O(n) due to parentheses.
 *
 * Example:
 * Input: s = "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 */
int calculate224(string s) {
    stack<int> stk;
    int result = 0, sign = 1, num = 0;
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '+') {
            result += sign * num;
            sign = 1;
            num = 0;
        } else if (c == '-') {
            result += sign * num;
            sign = -1;
            num = 0;
        } else if (c == '(') {
            stk.push(result);
            stk.push(sign);
            result = 0;
            sign = 1;
        } else if (c == ')') {
            result += sign * num;
            num = 0;
            result *= stk.top(); stk.pop();
            result += stk.top(); stk.pop();
        }
    }
    result += sign * num;
    return result;
}

/**
 * Problem 23: Basic Calculator III (LC 772) - [Full Expression Evaluator]
 * Description:
 * Evaluate a complex arithmetic expression string with integers, '+', '-', '*', '/', and parentheses.
 * Assumes valid syntax and integer division truncates toward zero.
 *
 * Approach:
 * - Use two stacks: one for numbers (operands), one for operators.
 * - Precedence function determines operator priority.
 * - When encountering ')', resolve until matching '('.
 * - For each operator, resolve existing operators of higher or equal precedence.
 * - Push final result from value stack.
 *
 * Time: O(n), Space: O(n)
 *
 * Example:
 * Input: s = "2*(5+5*2)/3+(6/2+8)"
 * Output: 21
 */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int apply(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

int calculate772(string s) {
    stack<int> nums;
    stack<char> ops;
    int num = 0;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == ' ') {
            continue;
        } else {
            if (isdigit(s[i - 1])) {
                nums.push(num);
                num = 0;
            }
            if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    int b = nums.top(); nums.pop();
                    int a = nums.top(); nums.pop();
                    char op = ops.top(); ops.pop();
                    nums.push(apply(a, b, op));
                }
                ops.pop();
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                    int b = nums.top(); nums.pop();
                    int a = nums.top(); nums.pop();
                    char op = ops.top(); ops.pop();
                    nums.push(apply(a, b, op));
                }
                ops.push(c);
            }
        }
    }
    if (isdigit(s.back())) nums.push(num);
    while (!ops.empty()) {
        int b = nums.top(); nums.pop();
        int a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        nums.push(apply(a, b, op));
    }
    return nums.top();
}

// =====================
// Extra: Base Conversion Module (Problem 24)
// =====================
/**
 * Problem 24: General Base Conversion - [Base Conversion / Simulation]
 * Description:
 * Implement conversion from any base (2–64) to any other base, supporting digits:
 * 0-9, A-Z, a-z, +, / (for base64).
 * Supports both general conversion (string → string) and bitwise shortcuts for powers of 2.
 *
 * Approach:
 * - Define digit set for base64 encoding.
 * - Step 1: Convert input string from base-X to decimal (base-10).
 *     - For each character, map to numeric value and accumulate into num = num * base + val.
 * - Step 2: Convert decimal number to target base-Y.
 *     - Use modulo operation to extract digits and append to result string.
 *     - Reverse the result string to get the correct order.
 * - Also provide optimized bitwise conversion versions for base 2, 8, 16.
 *
 * Example:
 * Input: fromBase = 10, toBase = 16, input = "2024"
 * Output: "7E8"
 */

 // Digit characters used for base-64 encoding (index 0 to 63)
 string digits64 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

 // Map a single character to its numeric value in base-X
 int charToVal(char c) {
     if ('0' <= c && c <= '9') return c - '0';             // 0–9 → 0–9
     if ('A' <= c && c <= 'Z') return c - 'A' + 10;        // A–Z → 10–35
     if ('a' <= c && c <= 'z') return c - 'a' + 36;        // a–z → 36–61
     if (c == '+') return 62;
     if (c == '/') return 63;
     return -1;  // Invalid character for base system
 }

 // General base conversion function: convert string from base-X to base-Y
 string convertBase(string input, int fromBase, int toBase) {
     // Step 1: Convert input string to decimal value
     long long num = 0;
     for (char c : input) {
         int val = charToVal(c);
         if (val < 0 || val >= fromBase) return "[error]"; // Error if char is invalid in fromBase
         num = num * fromBase + val;  // Multiply then add
     }

     // Step 2: Convert decimal to target base string
     if (num == 0) return "0";
     string res;
     while (num > 0) {
         res += digits64[num % toBase]; // Append lowest digit character
         num /= toBase;                // Divide for next digit
     }
     reverse(res.begin(), res.end()); // Final string is in reverse order
     return res;
 }

 // Bitwise shortcut: convert integer to base-2 string
 string intToBase2(int num) {
     if (num == 0) return "0";
     string res;
     while (num) {
         res += (num & 1) ? '1' : '0';  // Extract lowest bit
         num >>= 1;                     // Shift right by 1 bit
     }
     reverse(res.begin(), res.end());  // Reverse result to correct order
     return res;
 }

 // Bitwise shortcut: convert integer to base-8 (octal) string
 string intToBase8(int num) {
     if (num == 0) return "0";
     string res;
     while (num) {
         res += '0' + (num & 7);  // num % 8 using 0x7 mask
         num >>= 3;               // Shift by 3 bits (one octal digit)
     }
     reverse(res.begin(), res.end());
     return res;
 }

 // Bitwise shortcut: convert integer to base-16 (hexadecimal) string
 string intToBase16(int num) {
     if (num == 0) return "0";
     string res;
     while (num) {
         res += digits64[num & 15]; // num % 16 using 0xF mask
         num >>= 4;                 // Shift by 4 bits (one hex digit)
     }
     reverse(res.begin(), res.end());
     return res;
 }

 // Base conversion test driver
 void testBaseConversions() {
     cout << "Problem 24: Base Conversion Test" << endl;
     cout << "[10 → 2]   2024 → " << intToBase2(2024) << endl;            // 11111101000
     cout << "[10 → 8]   2024 → " << intToBase8(2024) << endl;            // 3740
     cout << "[10 → 16]  2024 → " << intToBase16(2024) << endl;           // 7E8
     cout << "[10 → 64]  2024 → " << convertBase("2024", 10, 64) << endl; // Ve
     cout << "[16 → 64]  7E8 → " << convertBase("7E8", 16, 64) << endl;   // Ve
     cout << "[64 → 16]  Ve → " << convertBase("Ve", 64, 16) << endl;     // 7E8
     cout << "[8  → 2]   3740 → " << convertBase("3740", 8, 2) << endl;   // 11111101000
     cout << "[2  → 16]  11111101000 → " << convertBase("11111101000", 2, 16) << endl; // 7E8
     cout << endl;
 }

 /**
 * Problem 25: Count Prime Factors - [Prime Factorization / Number Theory]
 * Description:
 * Given a positive integer n, count how many total prime factors (with multiplicity) it has.
 * For example, 28 = 2 * 2 * 7 → count = 3
 *
 * Approach:
 * - Iterate from 2 to sqrt(n), and for each i, divide as long as n % i == 0
 * - Each division means one prime factor counted
 * - If n > 1 at the end, it itself is a remaining prime factor
 */
int countPrimeFactors(int n) {
    int count = 0;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            count++;
            n /= i;
        }
    }
    if (n > 1) count++; // n is prime
    return count;
}

/**
 * Problem 26: List All Prime Factors - [Factorization / Divisor Enumeration]
 * Description:
 * Given a positive integer n, return a vector of all its prime factors in order (with duplicates).
 *
 * Input: n = 60
 * Output: [2, 2, 3, 5]
 *
 * Approach:
 * - Use trial division to find all prime factors:
 *     - Start with i = 2, iterate up to sqrt(n).
 *     - For each i, while i divides n, divide n by i and record i into result.
 *     - This collects repeated factors like 2 in 60 = 2*2*3*5.
 * - After the loop, if n > 1, it means n is a prime number larger than sqrt(original n), append it.
 * - This is a brute-force but efficient approach for small/moderate n.
 */
vector<int> getPrimeFactors(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

/**
 * Problem 27: Sum of Numbers With Exactly K Prime Factors (LC 2310)
 * Description:
 * Given integers n and k, return the sum of all numbers in [1, n] that have exactly k prime factors (with multiplicity).
 *
 * Input: n = 10, k = 2
 * Output: 16 // (6 = 2*3, 9 = 3*3, 10 = 2*5) → 6+9+10 = 25
 *
 * Approach:
 * - Iterate from 1 to n
 * - For each number, call countPrimeFactors() and check if it equals k
 * - If yes, add to result sum
 */
int sumOfNumbersWithKPrimeFactors(int n, int k) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (countPrimeFactors(i) == k) sum += i;
    }
    return sum;
}

int main() {
    // Test Problem 1: Integer to Roman
    cout << "Problem 1: intToRoman(1994) = " << intToRoman(1994) << endl;

    // Test Problem 2: Roman to Integer
    cout << "Problem 2: romanToInt(\"MCMXCIV\") = " << romanToInt("MCMXCIV") << endl;

    // Test Problem 3: Excel Sheet Column Title
    cout << "Problem 3: convertToTitle(28) = " << convertToTitle(28) << endl;

    // Test Problem 4: Excel Sheet Column Number
    cout << "Problem 4: titleToNumber(\"AB\") = " << titleToNumber("AB") << endl;

    // Test Problem 5: Add Binary
    cout << "Problem 5: addBinary(\"11\", \"1\") = " << addBinary("11", "1") << endl;

    // Test Problem 6: Multiply Strings
    cout << "Problem 6: multiply(\"123\", \"456\") = " << multiply("123", "456") << endl;

    // Test Problem 7: Count Primes
    cout << "Problem 7: countPrimes(10) = " << countPrimes(10) << endl;

    // Test Problem 8: Trailing Zeroes in Factorial
    cout << "Problem 8: trailingZeroes(100) = " << trailingZeroes(100) << endl;

    // Test Problem 9: Power of Two
    cout << "Problem 9: isPowerOfTwo(16) = " << (isPowerOfTwo(16) ? "true" : "false") << endl;

    // Test Problem 10: Power of Three
    cout << "Problem 10: isPowerOfThree(27) = " << (isPowerOfThree(27) ? "true" : "false") << endl;

    // Test Problem 11: Add Digits
    cout << "Problem 11: addDigits(38) = " << addDigits(38) << endl;

    // Test Problem 12: Reverse Integer
    cout << "Problem 12: reverse(123) = " << reverse(123) << endl;

    // Test Problem 13: Divide Two Integers
    cout << "Problem 13: divide(10, 3) = " << divide(10, 3) << endl;

    // Test Problem 14: Power Function
    cout << "Problem 14: myPow(2.0, 10) = " << myPow(2.0, 10) << endl;

    // Test Problem 15: Convert to Base 7
    cout << "Problem 15: convertToBase7(100) = " << convertToBase7(100) << endl;

    // Test Problem 16: Convert to Hexadecimal
    cout << "Problem 16: toHex(26) = " << toHex(26) << endl;

    // Test Problem 17: Nim Game
    cout << "Problem 17: canWinNim(4) = " << (canWinNim(4) ? "true" : "false") << endl;

    // Test Problem 18: Divisor Game
    cout << "Problem 18: divisorGame(2) = " << (divisorGame(2) ? "true" : "false") << endl;

    // Test Problem 19: Sum of Two Integers
    cout << "Problem 19: getSum(1, 2) = " << getSum(1, 2) << endl;

    // Test Problem 20: Hamming Distance
    cout << "Problem 20: hammingDistance(1, 4) = " << hammingDistance(1, 4) << endl;

    // Test Problem 21: Basic Calculator II (LC 227)
    cout << "Problem 21: calculate227(\"3+2*2-4/2\") = " << calculate227("3+2*2-4/2") << endl;

    // Test Problem 22: Basic Calculator I (LC 224)
    cout << "Problem 22: calculate224(\"(1+(4+5+2)-3)+(6+8)\") = " << calculate224("(1+(4+5+2)-3)+(6+8)") << endl;

    // Test Problem 23: Basic Calculator III (LC 772)
    cout << "Problem 23: calculate772(\"2*(5+5*2)/3+(6/2+8)\") = " << calculate772("2*(5+5*2)/3+(6/2+8)") << endl;

    // Test Problem 24: Base Conversion Module (Problem 24)
    testBaseConversions();

    // Problem 25: Count Prime Factors
    cout << "Problem 25: countPrimeFactors(60) = " << countPrimeFactors(60) << endl; // 4 (2,2,3,5)
    cout << "Problem 25: countPrimeFactors(97) = " << countPrimeFactors(97) << endl; // 1 (97)

    // Problem 26: List Prime Factors
    vector<int> pf = getPrimeFactors(84);
    cout << "Problem 26: getPrimeFactors(84) = ";
    for (int f : pf) cout << f << " "; cout << endl; // 2 2 3 7

    // Problem 27: Sum of Numbers With K Prime Factors
    cout << "Problem 27: sumOfNumbersWithKPrimeFactors(10, 2) = " << sumOfNumbersWithKPrimeFactors(10, 2) << endl; // 6+9+10 = 25

    return 0;
}
