#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

string generateHamming(string data) {
    int m = data.length();
    int r = 0;

    while ((1 << r) < (m + r + 1))
        r++;

    int n = m + r;
    vector<int> code(n + 1);

    int j = 0;

    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0)
            code[i] = 0;
        else
            code[i] = data[j++] - '0';
    }

    for (int p = 1; p <= n; p *= 2) {
        int parity = 0;

        for (int i = 1; i <= n; i++) {
            if (i & p)
                parity ^= code[i];
        }

        code[p] = parity;
    }

    string result = "";

    for (int i = n; i >= 1; i--)
        result += char(code[i] + '0');

    return result;
}

int checkHamming(string received) {
    int n = received.length();

    vector<int> code(n + 1);

    int k = 0;
    for (int i = n; i >= 1; i--)
        code[i] = received[k++] - '0';

    int errorPos = 0;

    for (int p = 1; p <= n; p *= 2) {
        int parity = 0;

        for (int i = 1; i <= n; i++) {
            if (i & p)
                parity ^= code[i];
        }

        if (parity)
            errorPos += p;
    }

    return errorPos;
}

//test
int main() {
    string data = "1010101000011010";

    string hammingCode = generateHamming(data);

    cout << "Original Data : " << data << endl;
    cout << "Hamming Code  : " << hammingCode << endl;

    int error = checkHamming(hammingCode);

    if (error == 0)
        cout << "Test Passed: No Error Detected" << endl;
    else
        cout << "Error at bit position: " << error << endl;

    return 0;
}