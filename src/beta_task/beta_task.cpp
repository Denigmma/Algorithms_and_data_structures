#include <iostream>
#include <bitset>
#include <stdexcept>

template<typename B = int32_t, unsigned FRAC = 16>
class fixed_point {
private:
    // ����� ��� ���������� ����� �����
    static constexpr B INT_MASK = (1 << (sizeof(B) * 8 - FRAC)) - 1;
    // ����� ��� ���������� ������� �����
    static constexpr B FRAC_MASK = (1 << FRAC) - 1;

    B data;

public:
    // �����������
    fixed_point(const B& value = 0) : data(value) {}

    // �������� ��������
    fixed_point operator+(const fixed_point& other) const {
        B sum = data + other.data;
        return fixed_point((sum & INT_MASK) | (sum & FRAC_MASK));
    }

    // �������� ���������
    fixed_point operator-(const fixed_point& other) const {
        B diff = data - other.data;
        return fixed_point((diff & INT_MASK) | (diff & FRAC_MASK));
    }

    // �������� ���������
    fixed_point operator*(const fixed_point& other) const {
        B product = (data * other.data) >> FRAC;
        return fixed_point(product);
    }

    // �������� �������
    fixed_point operator/(const fixed_point& other) const {
        if (other.data == 0) {
            throw std::invalid_argument("������� �� ����!");
        }
        B quotient = (data << FRAC) / other.data;
        return fixed_point(quotient);
    }

    friend std::ostream& operator<<(std::ostream& os, const fixed_point& num) {
        std::string resultStr = std::bitset<sizeof(B) * 8>(num.data).to_string();

        // ������� ������� ����
        resultStr.erase(0, resultStr.find('1'));

        // ��������� ����, ���� ������ �����
        if (resultStr.empty()) {
            resultStr = "0";
        }

        os << resultStr;
        return os;
    }
};

int main() {
    setlocale(LC_ALL,"ru");
    // ������ �������������
    fixed_point<> num1(0b1100110011001100); // ����� �����: 1100, ������� �����: 1100110011001100 (16 ���)
    fixed_point<> num2(0b1111000011110001); // ����� �����: 1111, ������� �����: 0000111100001111 (16 ���)

    // �������� ��������
    fixed_point<> sum = num1 + num2;
    fixed_point<> diff = num1 - num2;
    fixed_point<> product = num1 * num2;
    fixed_point<> quotient = num1 / num2;

    // ������� ����������
    std::cout << "�����: " << sum << std::endl;
    std::cout << "��������: " << diff << std::endl;
    std::cout << "������������: " << product << std::endl;
    std::cout << "�������: " << quotient << std::endl;

    return 0;
}
