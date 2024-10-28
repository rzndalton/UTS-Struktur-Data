#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>
using namespace std;

// Function to check if the character is an operator
bool isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

// Function to perform the calculation based on the operator
float calculate(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Function to evaluate postfix expression
float evaluatePostfix(const string& expression) {
    stack<float> st;
    istringstream tokens(expression);
    string token;

    cout << "Langkah-langkah evaluasi:" << endl;

    while (tokens >> token) {
        if (isdigit(token[0])) {  // Check if token is a number
            float num = stof(token);
            st.push(num);
            cout << "Push " << num << " ke stack." << endl;
        } else if (isOperator(token[0])) {  // Check if token is an operator
            float b = st.top(); st.pop();
            float a = st.top(); st.pop();
            float result = calculate(a, b, token[0]);
            st.push(result);
            cout << "Pop " << b << " dan " << a << ", hitung " << a << " " << token[0] << " " << b 
                 << " = " << result << ". Push hasil ke stack." << endl;
        }
    }
    float finalResult = st.top();
    cout << "Hasil akhir: " << finalResult << endl;
    return finalResult;
}

int main() {
    string expression;
    cout << "Masukkan ekspresi postfix (pisahkan dengan spasi): ";
    getline(cin, expression);

    float result = evaluatePostfix(expression);
    cout << "Hasil evaluasi postfix: " << result << endl;

    return 0;
}
