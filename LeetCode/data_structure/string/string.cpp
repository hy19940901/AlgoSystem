#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * Problem 1: Reverse a String (LC 344)
 * Description:
 * Given a string s, return its reversed version without using built-in reverse functions.
 * Example:
 * Input: s = "hello"
 * Output: "olleh"
 */
string ReverseString(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++, right--;
    }
    return s;
}

/**
 * Problem 2: Check if a String is a Palindrome (LC 125)
 * Description:
 * Given a string s, determine if it is a palindrome, ignoring non-alphanumeric characters and case.
 * Example:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 */
bool IsPalindrome(string s) {
    string cleaned;
    for (char c : s) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            cleaned += (c >= 'A' && c <= 'Z') ? c + 32 : c; // Convert uppercase to lowercase
    }
    int left = 0, right = cleaned.size() - 1;
    while (left < right) {
        if (cleaned[left] != cleaned[right]) return false;
        left++, right--;
    }
    return true;
}

/**
 * Problem 3: Convert String to Lowercase (LC 709)
 * Description:
 * Given a string s, convert all uppercase characters to lowercase.
 * Example:
 * Input: s = "Hello World"
 * Output: "hello world"
 */
string ToLowerCase(string s) {
    for (size_t i = 0; i < s.size(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
    return s;
}

/**
 * Problem 4: Remove Vowels from a String (LC 1119)
 * Description:
 * Given a string s, remove all vowels ('a', 'e', 'i', 'o', 'u') from the string.
 * Example:
 * Input: s = "leetcodeisacommunityforcoders"
 * Output: "ltcdscmmntyfrcdrs"
 */
string RemoveVowels(string s) {
    string result;
    for (char c : s)
        if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
              c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'))
            result += c;
    return result;
}

/**
 * Problem 5: Reverse Words in a String (LC 151)
 * Description:
 * Given a string s, reverse the order of words.
 * Example:
 * Input: s = "the sky is blue"
 * Output: "blue is sky the"
 */
string ReverseWords(string s) {
    vector<string> words;
    string word, result;
    int i = 0;
    while (static_cast<size_t>(i) < s.size()) {
        while (static_cast<size_t>(i) < s.size() && s[i] == ' ') i++; // Skip spaces
        while (static_cast<size_t>(i) < s.size() && s[i] != ' ') word += s[i++];
        if (!word.empty()) words.push_back(word);
        word = "";
    }
    for (int j = words.size() - 1; j >= 0; j--) {
        result += words[j];
        if (j != 0) result += " ";
    }
    return result;
}

/**
 * Problem 6: Find the First Non-Repeating Character (LC 387)
 * Description:
 * Given a string s, return the first non-repeating character in it. 
 * If no unique character exists, return an empty character (' ').
 * Example:
 * Input: s = "leetcode"
 * Output: 'l'
 * Input: s = "aabb"
 * Output: ' '
 */
char FirstUniqChar(string s) {
    int freq[26] = {0};
    for (char c : s) freq[c - 'a']++;
    for (char c : s)
        if (freq[c - 'a'] == 1) return c;
    return ' ';
}

/**
 * Problem 7: Check if Two Strings Are Anagrams (LC 242)
 * Description:
 * Given two strings s and t, return true if t is an anagram of s.
 * Example:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * Input: s = "rat", t = "car"
 * Output: false
 */
bool IsAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int count[26] = {0};
    for (size_t i = 0; i < s.size(); i++) {
        count[s[i] - 'a']++;
        count[t[i] - 'a']--;
    }
    for (size_t i = 0; i < 26; i++)
        if (count[i] != 0) return false;
    return true;
}

/**
 * Problem 8: Longest Common Prefix (LC 14)
 * Description:
 * Given a list of strings, find the longest common prefix shared among them.
 * Example:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 */
string LongestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    for (size_t i = 0; i < strs[0].size(); i++)
        for (size_t j = 1; j < strs.size(); j++)
            if (strs[j][i] != strs[0][i]) return strs[0].substr(0, i);
    return strs[0];
}

/**
 * Problem 9: Count and Say (LC 38)
 * Description:
 * The "Count and Say" sequence is a series where each term describes the previous term.
 * Example:
 * Input: n = 4
 * Output: "1211"
 * Explanation:
 * - n = 1 -> "1"
 * - n = 2 -> "11"
 * - n = 3 -> "21"
 * - n = 4 -> "1211"
 */
string CountAndSay(int n) {
    if (n == 1) return "1";
    string prev = CountAndSay(n - 1), result = "";
    for (size_t i = 0; i < prev.size(); i++) {
        int count = 1;
        while (static_cast<size_t>(i) + 1 < prev.size() && prev[i] == prev[i + 1]) {
            count++;
            i++;
        }
        result += to_string(count) + prev[i];
    }
    return result;
}

/**
 * Problem 10: Isomorphic Strings (LC 205)
 * Description:
 * Given two strings s and t, determine if they are isomorphic (i.e., can be transformed into each other).
 * Example:
 * Input: s = "egg", t = "add"
 * Output: true
 * Input: s = "foo", t = "bar"
 * Output: false
 */
bool IsIsomorphic(string s, string t) {
    unordered_map<char, int> map_s, map_t;
    for (size_t i = 0; i < s.size(); i++) {
        if (map_s[s[i]] != map_t[t[i]]) return false;
        map_s[s[i]] = map_t[t[i]] = i + 1;
    }
    return true;
}

/**
 * Problem 11: Valid Parentheses (LC 20)
 * Description:
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * Example:
 * Input: s = "()[]{}"
 * Output: true
 * Input: s = "(]"
 * Output: false
 */
bool IsValid(string s) {
    vector<char> stack;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push_back(c);
        } else {
            if (stack.empty()) return false;
            char top = stack.back();
            stack.pop_back();
            if ((c == ')' && top != '(') || 
                (c == '}' && top != '{') || 
                (c == ']' && top != '[')) return false;
        }
    }
    return stack.empty();
}

/**
 * Problem 12: Implement strStr() (LC 28)
 * Description:
 * Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 * Example:
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 */
int StrStr(string haystack, string needle) {
    for (size_t i = 0; i <= haystack.size() - needle.size(); i++) {
        int j = 0;
        while (static_cast<size_t>(j) < needle.size() && haystack[i + j] == needle[j]) j++;
        if (static_cast<size_t>(j) == needle.size()) return i;
    }
    return -1;
}

/**
 * Problem 13: Length of Last Word (LC 58)
 * Description:
 * Given a string s consisting of words and spaces, return the length of the last word in the string.
 * Example:
 * Input: s = "Hello World"
 * Output: 5
 */
int LengthOfLastWord(string s) {
    int length = 0, i = s.size() - 1;
    while (i >= 0 && s[i] == ' ') i--; // Trim trailing spaces
    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }
    return length;
}

/**
 * Problem 14: Add Binary (LC 67)
 * Description:
 * Given two binary strings a and b, return their sum as a binary string.
 * Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 */
string AddBinary(string a, string b) {
    string result = "";
    int carry = 0, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 2;
        result = char(sum % 2 + '0') + result;
    }
    return result;
}

/**
 * Problem 15: Multiply Strings (LC 43)
 * Description:
 * Given two non-negative integers num1 and num2 represented as strings, return the product as a string.
 * Example:
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 */
string MultiplyStrings(string num1, string num2) {
    int n = num1.size(), m = num2.size();
    vector<int> result(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = result[i + j + 1] + mul;
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    string res;
    for (int num : result) {
        if (!(res.empty() && num == 0)) res += to_string(num);
    }
    return res.empty() ? "0" : res;
}

/**
 * Problem 16: Longest Substring Without Repeating Characters (LC 3)
 * Description:
 * Given a string s, find the length of the longest substring without repeating characters.
 * Example:
 * Input: s = "abcabcbb"
 * Output: 3
 */
int LengthOfLongestSubstring(string s) {
    unordered_map<char, int> last_index_map;
    int max_length = 0, start = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (last_index_map.count(s[i])) start = max(start, last_index_map[s[i]] + 1);
        last_index_map[s[i]] = i;
        max_length = max(max_length, static_cast<int>(i) - start + 1);
    }
    return max_length;
}

/**
 * Problem 17: Valid Palindrome II (LC 680)
 * Description:
 * Given a string s, return true if it can be a palindrome after deleting at most one character.
 * Example:
 * Input: s = "abca"
 * Output: true
 */
bool IsValidPalindrome(string s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++, right--;
    }
    return true;
}

bool ValidPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right])
            return IsValidPalindrome(s, left + 1, right) || IsValidPalindrome(s, left, right - 1);
        left++, right--;
    }
    return true;
}

/**
 * Problem 18: Reverse Only Letters (LC 917)
 * Description:
 * Given a string s, return the string after reversing only the letters.
 * Example:
 * Input: s = "a-bC-dEf-ghIj"
 * Output: "j-Ih-gfE-dCba"
 */
string ReverseOnlyLetters(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        while (left < right && !isalpha(s[left])) left++;
        while (left < right && !isalpha(s[right])) right--;
        swap(s[left++], s[right--]);
    }
    return s;
}

/**
 * Problem 19: Check If a String Is a Subsequence (LC 392)
 * Description:
 * Given two strings s and t, return true if s is a subsequence of t.
 * Example:
 * Input: s = "abc", t = "ahbgdc"
 * Output: true
 */
bool IsSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (static_cast<size_t>(i) < s.size() && static_cast<size_t>(j) < t.size()) {
        if (s[i] == t[j]) i++;
        j++;
    }
    return static_cast<size_t>(i) == s.size();
}

/**
 * Problem 20: Count Binary Substrings (LC 696)
 * Description:
 * Given a binary string s, count the number of substrings with equal 0s and 1s.
 * Example:
 * Input: s = "00110011"
 * Output: 6
 */
int CountBinarySubstrings(string s) {
    int prev_group = 0, cur_group = 1, count = 0;
    for (size_t i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            cur_group++;
        } else {
            count += min(prev_group, cur_group);
            prev_group = cur_group;
            cur_group = 1;
        }
    }
    return count + min(prev_group, cur_group);
}

/**
 * Main Function: Test all string manipulation functions
 */
int main() {
    // Test Problem 1: Reverse a String
    cout << "Test Problem 1: Reverse a String (LC 344) \n";
    cout << ReverseString("hello") << " (Expected: olleh)" << endl;
    cout << ReverseString("world") << " (Expected: dlrow)" << endl;

    // Test Problem 2: Check if a String is a Palindrome
    cout << "\nTest Problem 2: Check if a String is a Palindrome (LC 125) \n";
    cout << (IsPalindrome("A man, a plan, a canal: Panama") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (IsPalindrome("race a car") ? "true" : "false") << " (Expected: false)" << endl;

    // Test Problem 3: Convert String to Lowercase
    cout << "\nTest Problem 3: Convert String to Lowercase (LC 709) \n";
    cout << ToLowerCase("Hello World") << " (Expected: hello world)" << endl;
    cout << ToLowerCase("LeetCode") << " (Expected: leetcode)" << endl;

    // Test Problem 4: Remove Vowels from a String
    cout << "\nTest Problem 4: Remove Vowels from a String (LC 1119) \n";
    cout << RemoveVowels("leetcodeisacommunityforcoders") << " (Expected: ltcdscmmntyfrcdrs)" << endl;
    cout << RemoveVowels("hello") << " (Expected: hll)" << endl;

    // Test Problem 5: Reverse Words in a String
    cout << "\nTest Problem 5: Reverse Words in a String (LC 151) \n";
    cout << ReverseWords("the sky is blue") << " (Expected: blue is sky the)" << endl;
    cout << ReverseWords("  hello world  ") << " (Expected: world hello)" << endl;

    // Test Problem 6: Find the First Non-Repeating Character
    cout << "Test Problem 6: Find the First Non-Repeating Character (LC 387) \n";
    cout << FirstUniqChar("leetcode") << " (Expected: l)" << endl;
    cout << FirstUniqChar("aabb") << " (Expected: ' ')" << endl;

    // Test Problem 7: Check if Two Strings Are Anagrams
    cout << "\nTest Problem 7: Check if Two Strings Are Anagrams (LC 242) \n";
    cout << (IsAnagram("anagram", "nagaram") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (IsAnagram("rat", "car") ? "true" : "false") << " (Expected: false)" << endl;

    // Test Problem 8: Longest Common Prefix
    cout << "\nTest Problem 8: Longest Common Prefix (LC 14) \n";
    vector<string> strs1 = {"flower", "flow", "flight"};
    vector<string> strs2 = {"dog", "racecar", "car"};
    cout << LongestCommonPrefix(strs1) << " (Expected: fl)" << endl;
    cout << LongestCommonPrefix(strs2) << " (Expected: '')" << endl;

    // Test Problem 9: Count and Say
    cout << "\nTest Problem 9: Count and Say (LC 38) \n";
    cout << CountAndSay(4) << " (Expected: 1211)" << endl;
    cout << CountAndSay(5) << " (Expected: 111221)" << endl;

    // Test Problem 10: Isomorphic Strings
    cout << "\nTest Problem 10: Isomorphic Strings (LC 205) \n";
    cout << (IsIsomorphic("egg", "add") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (IsIsomorphic("foo", "bar") ? "true" : "false") << " (Expected: false)" << endl;

    // Test Problem 11: Valid Parentheses
    cout << "Test Problem 11: Valid Parentheses (LC 20) \n";
    cout << (IsValid("()[]{}") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (IsValid("(]") ? "true" : "false") << " (Expected: false)" << endl;

    // Test Problem 12: Implement strStr()
    cout << "\nTest Problem 12: Implement strStr() (LC 28) \n";
    cout << StrStr("hello", "ll") << " (Expected: 2)" << endl;
    cout << StrStr("aaaaa", "bba") << " (Expected: -1)" << endl;

    // Test Problem 13: Length of Last Word
    cout << "\nTest Problem 13: Length of Last Word (LC 58) \n";
    cout << LengthOfLastWord("Hello World") << " (Expected: 5)" << endl;
    cout << LengthOfLastWord("   fly me   to   the moon  ") << " (Expected: 4)" << endl;

    // Test Problem 14: Add Binary
    cout << "\nTest Problem 14: Add Binary (LC 67) \n";
    cout << AddBinary("11", "1") << " (Expected: 100)" << endl;
    cout << AddBinary("1010", "1011") << " (Expected: 10101)" << endl;

    // Test Problem 15: Multiply Strings
    cout << "\nTest Problem 15: Multiply Strings (LC 43) \n";
    cout << MultiplyStrings("2", "3") << " (Expected: 6)" << endl;
    cout << MultiplyStrings("123", "456") << " (Expected: 56088)" << endl;

    // Test Problem 16: Longest Substring Without Repeating Characters
    cout << "\nTest Problem 16: Longest Substring Without Repeating Characters (LC 3) \n";
    cout << LengthOfLongestSubstring("abcabcbb") << " (Expected: 3)" << endl;
    cout << LengthOfLongestSubstring("bbbbb") << " (Expected: 1)" << endl;

    // Test Problem 17: Valid Palindrome II
    cout << "\nTest Problem 17: Valid Palindrome II (LC 680) \n";
    cout << (ValidPalindrome("abca") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (ValidPalindrome("racecar") ? "true" : "false") << " (Expected: true)" << endl;

    // Test Problem 18: Reverse Only Letters
    cout << "\nTest Problem 18: Reverse Only Letters (LC 917) \n";
    cout << ReverseOnlyLetters("a-bC-dEf-ghIj") << " (Expected: j-Ih-gfE-dCba)" << endl;
    cout << ReverseOnlyLetters("Test1ng-Leet=code-Q!") << " (Expected: Qedo1ct-eeLg=ntse-T!)" << endl;

    // Test Problem 19: Check If a String Is a Subsequence
    cout << "\nTest Problem 19: Check If a String Is a Subsequence (LC 392) \n";
    cout << (IsSubsequence("abc", "ahbgdc") ? "true" : "false") << " (Expected: true)" << endl;
    cout << (IsSubsequence("axc", "ahbgdc") ? "true" : "false") << " (Expected: false)" << endl;

    // Test Problem 20: Count Binary Substrings
    cout << "\nTest Problem 20: Count Binary Substrings (LC 696) \n";
    cout << CountBinarySubstrings("00110011") << " (Expected: 6)" << endl;
    cout << CountBinarySubstrings("10101") << " (Expected: 4)" << endl;

    return 0;
}
