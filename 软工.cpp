#include <iostream>
#include <fstream>
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

    // ����Ƿ�������һ�������
    if (validOperators.empty()) {
        std::cerr << "Error: No valid operators selected." << std::endl;
        exit(1);
    }

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

// ����Ŀд���ļ�
void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Questions have been written to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

// ����Ŀ�������ӡ��
void printToPrinter(const std::string& content) {
    // �˴���ӽ���Ŀ�������ӡ���Ĵ���
    std::cout << "Questions have been sent to printer for printing." << std::endl;
}

// ����Ŀ���������̨
void printToConsole(const std::string& content) {
    std::cout << content << std::endl;
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

        // �û�ѡ�������ʽ
        int outputChoice;
        std::cout << "Select output method:" << std::endl;
        std::cout << "1. File" << std::endl;
        std::cout << "2. Printer" << std::endl;
        std::cout << "3. Console" << std::endl;
        std::cin >> outputChoice;

        std::string questions; // ����������Ŀ���ַ���

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

            // ��ӵ���Ŀ�ַ�����
            questions += "Question " + to_string(i + 1) + ": " + expression + "\n";
        }

        // �����û�ѡ��������ʽ�������
        if (outputChoice == 1) {
            // ������ļ�
            std::string filename;
            std::cout << "Enter output filename: ";
            std::cin >> filename;
            writeToFile(filename, questions);
        }
        else if (outputChoice == 2) {
            // �������ӡ��
            printToPrinter(questions);
        }
        else if (outputChoice == 3) {
            // ���������̨
            printToConsole(questions);
        }
        else {
            std::cerr << "Invalid output choice. Please select either 1, 2, or 3." << std::endl;
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
