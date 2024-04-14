#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

template<typename B>
class ones_compl_int {
private:
    B value;  // ����� �������� � ���� ������ � �������� �������������

public:
    // �����������
    ones_compl_int(const B& val = "0") : value(val) {}

    // �������� ��������
    ones_compl_int operator+(const ones_compl_int& other) const {
        return ones_compl_int(addBinary(value, other.value));
    }

    // �������� ���������
    ones_compl_int operator-(const ones_compl_int& other) const {
        return ones_compl_int(subtractBinary(value, other.value));
    }

    // �������� ���������
    ones_compl_int operator*(const ones_compl_int& other) const {
        // ������� ��������� �������� �����
        return ones_compl_int(multiplyBinary(value, other.value));
    }

    // �������� �������
    ones_compl_int operator/(const ones_compl_int& other) const {
        // ������� ������� �������� �����
        return ones_compl_int(divideBinary(value, other.value));
    }

    // �������� ��������� �� ���������
    bool operator==(const ones_compl_int& other) const {
        return value == other.value;
    }

    // �������� ������ � �����
    friend std::ostream& operator<<(std::ostream& os, const ones_compl_int& num) {
        os << num.value;
        return os;
    }

    // �������� ����� �� ������
    friend std::istream& operator>>(std::istream& is, ones_compl_int& num) {
        B input;
        is >> input;
        num.value = input;  // ������ ��������� ������
        return is;
    }

private:
    // ��������������� ������� ��� ���������� �������� �������� �����
    B addBinary(const B& a, const B& b) const {
        B result;
        int carry = 0;
        for (int i = a.size() - 1; i >= 0; i--) {
            int sum = (a[i] - '0') + (b[i] - '0') + carry;
            result.push_back(sum % 2 + '0');
            carry = sum / 2;
        }
        if (carry) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    // ��������������� ������� ��� ���������� ��������� �������� �����
    B multiplyBinary(const B& a, const B& b) const {
        // ����������� ������ � ����� ����� � �������� �������
        std::bitset<sizeof(B)> num1(a);
        std::bitset<sizeof(B)> num2(b);

        // ��������� ���������
        std::bitset<sizeof(B) * 8> result = num1.to_ulong() * num2.to_ulong();

        // ����������� ��������� ������� � ������ � �������� �������������
        std::string resultStr = result.to_string();

        // ������� ������� ����
        resultStr.erase(0, resultStr.find('1'));

        return resultStr;
    }

    // ��������������� ������� ��� ���������� ������� �������� �����
    B divideBinary(const B& a, const B& b) const {
        // ����������� ������ � ����� ����� � �������� �������
        std::bitset<sizeof(B) * 8> num1(a);
        std::bitset<sizeof(B) * 8> num2(b);

        // ��������� ������� �� ����
        if (num2.to_ulong() == 0) {
            throw std::invalid_argument("������� �� ����!");
        }

        // ��������� �������
        std::bitset<sizeof(B) * 8> result = num1.to_ulong() / num2.to_ulong();

        // ����������� ��������� ������� � ������ � �������� �������������
        std::string resultStr = result.to_string();

        // ������� ������� ����
        resultStr.erase(0, resultStr.find('1'));

        return resultStr;
    }


    // ��������������� ������� ��� ���������� ��������� �������� �����
    B subtractBinary(const B& a, const B& b) const {
        // ����������� ��� ���� ����� B (�������� ���)
        B negB = b;
        for (char& bit : negB) {
            bit = (bit == '0') ? '1' : '0';
        }

        // ��������� ������� � ��������� ���� ��� ���������� �������� ��������
        int carry = 1;
        for (int i = negB.size() - 1; i >= 0; i--) {
            int sum = (negB[i] - '0') + carry;
            negB[i] = sum % 2 + '0';
            carry = sum / 2;
        }

        // ��������� �������� �������� A + (-B)
        B result = addBinary(a, negB);

        // ���� ��������� ��������� ������ ������, ������� ������� ������
        if (result.size() > a.size()) {
            result.erase(0, 1);
        }

        return result;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    ones_compl_int<std::string> num1, num2;
    std::cout << "������� ������ ����� � �������� ����: ";
    std::cin >> num1;

    std::cout << "������� ������ ����� � �������� ����: ";
    std::cin >> num2;

    ones_compl_int<std::string> sum = num1 + num2;
    ones_compl_int<std::string> diff = num1 - num2;
    ones_compl_int<std::string> product = num1 * num2;
    ones_compl_int<std::string> quotient = num1 / num2;

    std::cout << "�����: " << sum << std::endl;
    std::cout << "��������: " << diff << std::endl;
    std::cout << "������������: " << product << std::endl;
    std::cout << "�������: " << quotient << std::endl;

    return 0;
}