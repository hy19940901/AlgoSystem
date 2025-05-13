#include <iostream>
#include <vector>
#include <unordered_set>
#include <bitset>
#include <cstdint>
using namespace std;

/**
 * Problem 1: Single Number (LC 136)
 * Description:
 * Given a non-empty array of integers, every element appears twice except for one. Find that single one.
 * Approach:
 * Use XOR operation: a ^ a = 0, a ^ 0 = a. So all duplicates cancel out, and the remaining number is the answer.
 * Example:
 * Input: [4,1,2,1,2]
 * Output: 4
 */
int SingleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) result ^= num;
    return result;
}

/**
 * Problem 2: Number of 1 Bits (LC 191)
 * Description:
 * Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as Hamming weight).
 * Approach:
 * Use n & (n - 1) trick to remove the lowest set bit each time, counting how many steps it takes to reach zero.
 * Example:
 * Input: n = 11 (00000000000000000000000000001011)
 * Output: 3
 */
int HammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Remove the lowest set bit
        count++;
    }
    return count;
}

/**
 * Problem 3: Reverse Bits (LC 190)
 * Description:
 * Reverse bits of a given 32-bit unsigned integer.
 * Approach:
 * Shift result left and add current lowest bit of n. Then shift n right. Repeat 32 times.
 * Example:
 * Input: 00000010100101000001111010011100 (43261596)
 * Output: 00111001011110000010100101000000 (964176192)
 */
uint32_t ReverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

/**
 * Problem 4: Majority Element (LC 169)
 * Description:
 * Given an array of size n, return the majority element (appears more than ⌊n / 2⌋ times).
 * Approach:
 * Use Boyer-Moore Voting Algorithm with a counter and candidate.
 * Example:
 * Input: [3,2,3]
 * Output: 3
 */
int MajorityElement(vector<int>& nums) {
    int count = 0, candidate = 0;
    for (int num : nums) {
        if (count == 0) candidate = num;
        count += (num == candidate) ? 1 : -1;
    }
    return candidate;
}

/**
 * Problem 5: Power of Two (LC 231)
 * Description:
 * Given an integer, return true if it is a power of two.
 * Approach:
 * A number is a power of two if it has exactly one bit set. Check using (n & (n - 1)) == 0.
 * Example:
 * Input: 16
 * Output: true
 */
bool IsPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/**
 * Problem 6: Power of Four (LC 342)
 * Description:
 * Given an integer, return true if it is a power of four.
 * Approach:
 * Must be power of two and the only set bit must be in the odd position. Use 0x55555555 mask.
 * Example:
 * Input: 64
 * Output: true
 */
bool IsPowerOfFour(int n) {
    return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555);
}

/**
 * Problem 7: Single Number II (LC 137)
 * Description:
 * Given an integer array where every element appears three times except for one, which appears exactly once. Find that one.
 * Approach:
 * Use two-bit counters (ones, twos) to simulate base-3 digit counting.
 * Example:
 * Input: [2,2,3,2]
 * Output: 3
 */
int SingleNumberII(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}

/**
 * Problem 8: Single Number III (LC 260)
 * Description:
 * Given an array of numbers where exactly two elements appear only once and all the other elements appear exactly twice.
 * Find the two elements that appear only once.
 * Approach:
 * XOR all elements, then use a differentiating bit to split into two groups and XOR again.
 * Example:
 * Input: [1,2,1,3,2,5]
 * Output: [3,5]
 */
vector<int> SingleNumberIII(vector<int>& nums) {
    int xor_all = 0;
    for (int num : nums) xor_all ^= num;
    int diff = xor_all & -xor_all;
    int a = 0, b = 0;
    for (int num : nums) {
        if (num & diff) a ^= num;
        else b ^= num;
    }
    return {a, b};
}

/**
 * Problem 9: Bitwise AND of Numbers Range (LC 201)
 * Description:
 * Given a range [left, right], return the bitwise AND of all numbers in this range.
 * Approach:
 * Shift both numbers right until equal, then shift result left back.
 * Example:
 * Input: left = 5, right = 7
 * Output: 4
 */
int RangeBitwiseAnd(int left, int right) {
    int shift = 0;
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }
    return left << shift;
}

/**
 * Problem 10: Maximum XOR of Two Numbers in an Array (LC 421)
 * Description:
 * Given an array of integers, return the maximum result of a XOR of two numbers.
 * Approach:
 * Build prefix set while iterating from high to low bits, trying to extend current XOR by 1 bit.
 * Example:
 * Input: [3,10,5,25,2,8]
 * Output: 28
 */
int FindMaximumXOR(vector<int>& nums) {
    int max_xor = 0, mask = 0;
    for (int i = 31; i >= 0; --i) {
        mask |= (1 << i);
        unordered_set<int> prefixes;
        for (int num : nums) prefixes.insert(num & mask);
        int candidate = max_xor | (1 << i);
        for (int p : prefixes) {
            if (prefixes.count(candidate ^ p)) {
                max_xor = candidate;
                break;
            }
        }
    }
    return max_xor;
}

int main() {
    cout << "===== Bit Manipulation Problems =====\n\n";

    // Problem 1
    vector<int> p1 = {4, 1, 2, 1, 2};
    cout << "Problem 1 Output: " << SingleNumber(p1) << "\n\n";

    // Problem 2
    uint32_t p2 = 11;
    cout << "Problem 2 Input: " << bitset<32>(p2) << "\n";
    cout << "Problem 2 Output: " << HammingWeight(p2) << "\n\n";

    // Problem 3
    uint32_t p3 = 43261596;
    cout << "Problem 3 Input: " << bitset<32>(p3) << "\n";
    cout << "Problem 3 Output: " << bitset<32>(ReverseBits(p3)) << "\n\n";

    // Problem 4
    vector<int> p4 = {3, 2, 3};
    cout << "Problem 4 Output: " << MajorityElement(p4) << "\n\n";

    // Problem 5
    int p5 = 16;
    cout << "Problem 5 Output: " << (IsPowerOfTwo(p5) ? "true" : "false") << "\n\n";

    // Problem 6
    int p6 = 64;
    cout << "Problem 6 Output: " << (IsPowerOfFour(p6) ? "true" : "false") << "\n\n";

    // Problem 7
    vector<int> p7 = {2, 2, 3, 2};
    cout << "Problem 7 Output: " << SingleNumberII(p7) << "\n\n";

    // Problem 8
    vector<int> p8 = {1, 2, 1, 3, 2, 5};
    vector<int> r8 = SingleNumberIII(p8);
    cout << "Problem 8 Output: " << r8[0] << ", " << r8[1] << "\n\n";

    // Problem 9
    int left = 5, right = 7;
    cout << "Problem 9 Output: " << RangeBitwiseAnd(left, right) << "\n\n";

    // Problem 10
    vector<int> p10 = {3, 10, 5, 25, 2, 8};
    cout << "Problem 10 Output: " << FindMaximumXOR(p10) << "\n\n";

    return 0;
}
