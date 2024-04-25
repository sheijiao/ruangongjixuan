#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <sstream>

// 将数字转换为字符串
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

// 生成指定范围内的整数
int generateInteger(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 生成指定范围内的小数（小数点后两位）
float generateFloat(float min, float max) {
    int intMin = static_cast<int>(min * 100);
    int intMax = static_cast<int>(max * 100);
    int randomNum = rand() % (intMax - intMin + 1) + intMin;
    return static_cast<float>(randomNum) / 100;
}

// 生成随机运算符
char generateOperator(bool allowAddition, bool allowSubtraction, bool allowMultiplication, bool allowDivision) {
    std::string validOperators = "";

    if (allowAddition) validOperators += "+";
    if (allowSubtraction) validOperators += "-";
    if (allowMultiplication) validOperators += "*";
    if (allowDivision) validOperators += "/";

    int index = rand() % validOperators.size();
    return validOperators[index];
}

// 生成括号
std::string generateParentheses(bool allowParentheses, bool allowAddition, bool allowSubtraction, bool allowMultiplication, bool allowDivision) {
    if (!allowParentheses) return "";

    std::string parentheses = "";
    int numPairs = generateInteger(1, 3); // 生成 1 到 3 对括号
    for (int i = 0; i < numPairs; ++i) {
        // 添加括号前的运算符
        if (i > 0 || parentheses.empty()) {
            parentheses += generateOperator(allowAddition, allowSubtraction, false, false);
        }
        parentheses += '(';
        // 添加因式
        char factorOperator = generateOperator(allowAddition, allowSubtraction, false, false); // 只允许加减
        int factorNum1 = generateInteger(1, 100); // 生成整数
        int factorNum2 = generateInteger(1, 100); // 生成整数
        // 组装因式
        std::string factorExpression = to_string(factorNum1) + " " + factorOperator + " " + to_string(factorNum2);
        parentheses += factorExpression;
        parentheses += ')';
    }
    return parentheses;
}

int main() {
    srand(time(0)); // 初始化随机数种子

    bool exitProgram = false;

    while (!exitProgram) {
        // 用户选择是否允许加减符号
        bool allowAddition, allowSubtraction, allowMultiplication, allowDivision;
        std::cout << "Do you want to include addition (+)? (0/1): ";
        std::cin >> allowAddition;
        std::cout << "Do you want to include subtraction (-)? (0/1): ";
        std::cin >> allowSubtraction;
        std::cout << "Do you want to include multiplication (*)? (0/1): ";
        std::cin >> allowMultiplication;
        std::cout << "Do you want to include division (/)? (0/1): ";
        std::cin >> allowDivision;

        // 用户选择是否允许括号
        bool allowParentheses;
        std::cout << "Do you want to include parentheses? (0/1): ";
        std::cin >> allowParentheses;

        // 用户指定题目数量
        int numQuestions;
        std::cout << "Enter the number of questions: ";
        std::cin >> numQuestions;

        // 用户指定操作数范围
        int maxOperand;
        std::cout << "Enter the maximum operand: ";
        std::cin >> maxOperand;

        // 用户选择是否允许小数运算
        bool allowDecimal;
        std::cout << "Do you want to include decimal numbers? (0/1): ";
        std::cin >> allowDecimal;

        // 生成指定数量的题目
        for (int i = 0; i < numQuestions; ++i) {
            // 生成题目的操作数和括号
            std::string parentheses = generateParentheses(allowParentheses, allowAddition, allowSubtraction, allowMultiplication, allowDivision);
            float num1, num2;
            if (allowDecimal) {
                num1 = generateFloat(0, maxOperand);
                num2 = generateFloat(0, maxOperand);
            }
            else {
                num1 = generateInteger(0, maxOperand);
                num2 = generateInteger(0, maxOperand);
            }

            // 组装表达式
            std::string expression;
            if (parentheses.empty()) {
                expression = to_string(num1) + " " + generateOperator(allowAddition, allowSubtraction, allowMultiplication, allowDivision) + " " + to_string(num2) + " = ?";
            }
            else {
                expression = to_string(num1) + " " + generateOperator(allowAddition, allowSubtraction, allowMultiplication, allowDivision) + " " + to_string(num2) + " " + parentheses + " = ?";
            }

            // 显示题目
            std::cout << "Question " << i + 1 << ": " << expression << std::endl;
        }

        // 是否继续生成题目
        char choice;
        std::cout << "Do you want to generate more questions? (Y/N): ";
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            exitProgram = true;
        }
    }

    return 0;
}
