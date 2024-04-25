#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <sstream>

// ������ת��Ϊ�ַ���
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

// ����ָ����Χ�ڵ�����
int generateInteger(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// ����ָ����Χ�ڵ�С����С�������λ��
float generateFloat(float min, float max) {
    int intMin = static_cast<int>(min * 100);
    int intMax = static_cast<int>(max * 100);
    int randomNum = rand() % (intMax - intMin + 1) + intMin;
    return static_cast<float>(randomNum) / 100;
}

// ������������
char generateOperator(bool allowAddition, bool allowSubtraction, bool allowMultiplication, bool allowDivision) {
    std::string validOperators = "";

    if (allowAddition) validOperators += "+";
    if (allowSubtraction) validOperators += "-";
    if (allowMultiplication) validOperators += "*";
    if (allowDivision) validOperators += "/";

    int index = rand() % validOperators.size();
    return validOperators[index];
}

// ��������
std::string generateParentheses(bool allowParentheses, bool allowAddition, bool allowSubtraction, bool allowMultiplication, bool allowDivision) {
    if (!allowParentheses) return "";

    std::string parentheses = "";
    int numPairs = generateInteger(1, 3); // ���� 1 �� 3 ������
    for (int i = 0; i < numPairs; ++i) {
        // �������ǰ�������
        if (i > 0 || parentheses.empty()) {
            parentheses += generateOperator(allowAddition, allowSubtraction, false, false);
        }
        parentheses += '(';
        // �����ʽ
        char factorOperator = generateOperator(allowAddition, allowSubtraction, false, false); // ֻ����Ӽ�
        int factorNum1 = generateInteger(1, 100); // ��������
        int factorNum2 = generateInteger(1, 100); // ��������
        // ��װ��ʽ
        std::string factorExpression = to_string(factorNum1) + " " + factorOperator + " " + to_string(factorNum2);
        parentheses += factorExpression;
        parentheses += ')';
    }
    return parentheses;
}

int main() {
    srand(time(0)); // ��ʼ�����������

    bool exitProgram = false;

    while (!exitProgram) {
        // �û�ѡ���Ƿ�����Ӽ�����
        bool allowAddition, allowSubtraction, allowMultiplication, allowDivision;
        std::cout << "Do you want to include addition (+)? (0/1): ";
        std::cin >> allowAddition;
        std::cout << "Do you want to include subtraction (-)? (0/1): ";
        std::cin >> allowSubtraction;
        std::cout << "Do you want to include multiplication (*)? (0/1): ";
        std::cin >> allowMultiplication;
        std::cout << "Do you want to include division (/)? (0/1): ";
        std::cin >> allowDivision;

        // �û�ѡ���Ƿ���������
        bool allowParentheses;
        std::cout << "Do you want to include parentheses? (0/1): ";
        std::cin >> allowParentheses;

        // �û�ָ����Ŀ����
        int numQuestions;
        std::cout << "Enter the number of questions: ";
        std::cin >> numQuestions;

        // �û�ָ����������Χ
        int maxOperand;
        std::cout << "Enter the maximum operand: ";
        std::cin >> maxOperand;

        // �û�ѡ���Ƿ�����С������
        bool allowDecimal;
        std::cout << "Do you want to include decimal numbers? (0/1): ";
        std::cin >> allowDecimal;

        // ����ָ����������Ŀ
        for (int i = 0; i < numQuestions; ++i) {
            // ������Ŀ�Ĳ�����������
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

            // ��װ���ʽ
            std::string expression;
            if (parentheses.empty()) {
                expression = to_string(num1) + " " + generateOperator(allowAddition, allowSubtraction, allowMultiplication, allowDivision) + " " + to_string(num2) + " = ?";
            }
            else {
                expression = to_string(num1) + " " + generateOperator(allowAddition, allowSubtraction, allowMultiplication, allowDivision) + " " + to_string(num2) + " " + parentheses + " = ?";
            }

            // ��ʾ��Ŀ
            std::cout << "Question " << i + 1 << ": " << expression << std::endl;
        }

        // �Ƿ����������Ŀ
        char choice;
        std::cout << "Do you want to generate more questions? (Y/N): ";
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            exitProgram = true;
        }
    }

    return 0;
}
