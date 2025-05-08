#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------------- 通用版本 ----------------

/*
 * 将字符映射为对应的整数值（用于 base64 范围内的 0-63）
 * 用于从字符串形式的任意进制数字中解析出每一位的实际数值
 */
int charToValue(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    if ('a' <= c && c <= 'z') return c - 'a' + 36;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

/*
 * 通用进制转换函数
 * 输入为字符串 input，及其原始进制 fromBase 和目标进制 toBase
 * 先将 input 转为十进制整数，然后再转为目标进制字符串
 */
char *convertBase(const char *input, int fromBase, int toBase) {
    const char *digits64 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    long long num = 0;
    int i = 0;

    // 字符串 → 十进制整数
    while (input[i]) {
        int val = charToValue(input[i]);
        if (val < 0 || val >= fromBase) {
            char *error = (char *)malloc(128);
            snprintf(error, 128, "[error: invalid digit '%c' for base %d]", input[i], fromBase);
            return error;
        }
        num = num * fromBase + val;
        i++;
    }

    // 十进制整数 → 目标进制字符串（倒序拼接再反转）
    char *result = (char *)malloc(128);
    char buffer[128];
    int j = 0;
    if (num == 0) {
        result[0] = '0'; result[1] = '\0'; return result;
    }
    while (num > 0) {
        buffer[j++] = digits64[num % toBase];
        num /= toBase;
    }
    for (int k = 0; k < j; ++k)
        result[k] = buffer[j - 1 - k];
    result[j] = '\0';
    return result;
}

// 将整数转换为字符串（供 convertBase 使用）
char *intToString(int num) {
    char *buffer = (char *)malloc(32);
    snprintf(buffer, 32, "%d", num);
    return buffer;
}

// ---------------- 位运算版本 ----------------

/* 使用位运算将整数转为 base64 字符串 */
char *intToBase64Bitwise(int num) {
    const char *digits64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *result = (char *)malloc(8);
    result[0] = digits64[(num >> 6) & 0x3F];
    result[1] = digits64[num & 0x3F];
    result[2] = '\0';
    if (num < 64) {
        result[0] = digits64[num];
        result[1] = '\0';
    }
    return result;
}

/* 使用位运算将整数转为二进制字符串 */
char *intToBase2Bitwise(int num) {
    char *result = (char *)malloc(128);
    int i = 0;
    if (num == 0) {
        result[i++] = '0';
    } else {
        for (int bit = sizeof(int) * 8 - 1; bit >= 0; bit--) {
            if (num & (1 << bit)) {
                result[i++] = '1';
                for (bit--; bit >= 0; bit--) {
                    result[i++] = (num & (1 << bit)) ? '1' : '0';
                }
                break;
            }
        }
    }
    result[i] = '\0';
    return result;
}

/* 使用位运算将整数转为 base8 字符串 */
char *intToBase8Bitwise(int num) {
    char *result = (char *)malloc(32);
    int i = 0;
    if (num == 0) {
        result[i++] = '0';
    } else {
        int digits[32];
        int j = 0;
        while (num > 0) {
            digits[j++] = num & 0x7;  // 每 3 位一组，相当于 num % 8，用位运算代替除法：0x7 = 二进制 111
            num >>= 3;
        }
        while (j--) result[i++] = '0' + digits[j];
    }
    result[i] = '\0';
    return result;
}

/* 使用位运算将整数转为 base16（十六进制）字符串 */
char *intToBase16Bitwise(int num) {
    const char *digits = "0123456789ABCDEF";
    char *result = (char *)malloc(32);
    int i = 0;
    if (num == 0) {
        result[i++] = '0';
    } else {
        int digitsArr[32];
        int j = 0;
        while (num > 0) {
            digitsArr[j++] = num & 0xF; // 每 4 位一组，相当于 num % 16，用位运算代替除法：0xF = 二进制 1111
            num >>= 4;
        }
        while (j--) result[i++] = digits[digitsArr[j]];
    }
    result[i] = '\0';
    return result;
}

// ---------------- 封装接口 ----------------

// 通用接口：从任意 baseX 字符串转换为 baseY 字符串（供 main 扩展调用）
char *fromBase2ToBase16(const char *s) { return convertBase(s, 2, 16); }
char *fromBase8ToBase2(const char *s) { return convertBase(s, 8, 2); }
char *fromBase16ToBase64(const char *s) { return convertBase(s, 16, 64); }
char *fromBase64ToBase16(const char *s) { return convertBase(s, 64, 16); }
char *fromBase12ToBase10(const char *s) { return convertBase(s, 12, 10); }
char *fromBase62ToBase10(const char *s) { return convertBase(s, 62, 10); }

// 这些函数将十进制整数转换为对应进制字符串，并返回动态分配内存（使用者需 free）
char *fromBase10IntToBase2(int num) { return intToBase2Bitwise(num); }
char *fromBase10IntToBase4(int num) {
    char *s = intToString(num); char *res = convertBase(s, 10, 4); free(s); return res;
}
char *fromBase10IntToBase8(int num) { return intToBase8Bitwise(num); }
char *fromBase10IntToBase10(int num) {
    char *s = intToString(num); return s;
}
char *fromBase10IntToBase12(int num) {
    char *s = intToString(num); char *res = convertBase(s, 10, 12); free(s); return res;
}
char *fromBase10IntToBase16(int num) { return intToBase16Bitwise(num); }
char *fromBase10IntToBase32(int num) {
    char *s = intToString(num); char *res = convertBase(s, 10, 32); free(s); return res;
}
char *fromBase10IntToBase36(int num) {
    char *s = intToString(num); char *res = convertBase(s, 10, 36); free(s); return res;
}
char *fromBase10IntToBase62(int num) {
    char *s = intToString(num); char *res = convertBase(s, 10, 62); free(s); return res;
}
char *fromBase10IntToBase64(int num) { return intToBase64Bitwise(num); }

// ---------------- 测试入口 ----------------

/*
 * 主函数测试入口：调用所有封装函数并打印输出结果
 */
int main() {
    char *output;

    output = fromBase10IntToBase2(2024);
    printf("[Base10 → Base2] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase4(2024);
    printf("[Base10 → Base4] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase8(2024);
    printf("[Base10 → Base8] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase10(2024);
    printf("[Base10 → Base10] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase12(2024);
    printf("[Base10 → Base12] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase16(2024);
    printf("[Base10 → Base16] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase32(2024);
    printf("[Base10 → Base32] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase36(2024);
    printf("[Base10 → Base36] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase62(2024);
    printf("[Base10 → Base62] 2024 → %s\n", output); free(output);

    output = fromBase10IntToBase64(2024);
    printf("[Base10 → Base64] 2024 → %s\n", output); free(output);

    output = fromBase2ToBase16("11111101000");
    printf("[Base2 → Base16] 11111101000 → %s\n", output); free(output);

    output = fromBase8ToBase2("3740");
    printf("[Base8 → Base2] 3740 → %s\n", output); free(output);

    output = fromBase16ToBase64("7E8");
    printf("[Base16 → Base64] 7E8 → %s\n", output); free(output);

    output = fromBase64ToBase16("Ve");
    printf("[Base64 → Base16] Ve → %s\n", output); free(output);

    output = fromBase12ToBase10("1204");
    printf("[Base12 → Base10] 1204 → %s\n", output); free(output);

    output = fromBase62ToBase10("ZZ");
    printf("[Base62 → Base10] ZZ → %s\n", output); free(output);

    return 0;
}
