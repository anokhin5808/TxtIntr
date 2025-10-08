#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class Calculator {
private:
    enum class Operation {
        SUMMA,
        SUBTRACT,
        UNKNOWN
    };

    Operation parseOperation(const std::string& opStr) {
        if (opStr == "summa" || opStr == "add") {
            return Operation::SUMMA;
        } else if (opStr == "subtract" || opStr == "sub") {
            return Operation::SUBTRACT;
        } else {
            return Operation::UNKNOWN;
        }
    }

    int convertToInt(const std::string& str) {
        try {
            return std::stoi(str);
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("Ошибка: '" + str + "' не является числом");
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("Ошибка: число '" + str + "' выходит за пределы диапазона");
        }
    }

    void printHelp() {
        std::cout << "Аддитивный калькулятор\n";
        std::cout << "Использование:\n";
        std::cout << "  calculator -o <операция> <операнд1> <операнд2> ... <операндN>\n";
        std::cout << "  calculator --operation <операция> <операнд1> <операнд2> ... <операндN>\n";
        std::cout << "\nПоддерживаемые операции:\n";
        std::cout << "  summa    - сложение всех операндов\n";
        std::cout << "  subtract - вычитание из первого операнда всех остальных\n";
        std::cout << "\nПараметры:\n";
        std::cout << "  -o, --operation  задает операцию (обязательный параметр)\n";
        std::cout << "  операнды         целые числа (3-5 штук, обязательные)\n";
        std::cout << "\nПримеры:\n";
        std::cout << "  calculator -o summa 5 10 15\n";
        std::cout << "  calculator --operation subtract 100 20 30 10\n";
        std::cout << "  calculator -o summa 1 2 3 4 5\n";
    }

public:
    int run(int argc, char* argv[]) {
        // Проверка на отсутствие параметров
        if (argc == 1) {
            printHelp();
            return 0;
        }

        std::string operationStr;
        std::vector<int> operands;

        // Парсинг аргументов командной строки
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            
            if (arg == "-o" || arg == "--operation") {
                if (i + 1 < argc) {
                    operationStr = argv[++i];
                } else {
                    std::cerr << "Ошибка: отсутствует значение для параметра " << arg << "\n";
                    return 1;
                }
            } else if (arg == "-h" || arg == "--help") {
                printHelp();
                return 0;
            } else {
                // Пытаемся интерпретировать как число
                try {
                    operands.push_back(convertToInt(arg));
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << "\n";
                    return 1;
                }
            }
        }

        // Проверка обязательных параметров
        if (operationStr.empty()) {
            std::cerr << "Ошибка: не указана операция\n";
            std::cerr << "Используйте -o или --operation для указания операции\n\n";
            printHelp();
            return 1;
        }

        // Проверка количества операндов
        if (operands.size() < 3 || operands.size() > 5) {
            std::cerr << "Ошибка: количество операндов должно быть от 3 до 5\n";
            std::cerr << "Получено: " << operands.size() << " операнд(ов)\n\n";
            printHelp();
            return 1;
        }

        // Выполнение операции
        Operation operation = parseOperation(operationStr);
        
        try {
            int result;
            switch (operation) {
                case Operation::SUMMA:
                    result = 0;
                    for (int num : operands) {
                        result += num;
                    }
                    std::cout << "Результат сложения: ";
                    for (size_t i = 0; i < operands.size(); ++i) {
                        std::cout << operands[i];
                        if (i < operands.size() - 1) {
                            std::cout << " + ";
                        }
                    }
                    std::cout << " = " << result << "\n";
                    break;

                case Operation::SUBTRACT:
                    result = operands[0];
                    std::cout << "Результат вычитания: " << operands[0];
                    for (size_t i = 1; i < operands.size(); ++i) {
                        result -= operands[i];
                        std::cout << " - " << operands[i];
                    }
                    std::cout << " = " << result << "\n";
                    break;

                case Operation::UNKNOWN:
                    std::cerr << "Ошибка: неизвестная операция '" << operationStr << "'\n";
                    std::cerr << "Доступные операции: summa, subtract\n\n";
                    printHelp();
                    return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при выполнении операции: " << e.what() << "\n";
            return 1;
        }

        return 0;
    }
};

int main(int argc, char* argv[]) {
    Calculator calculator;
    return calculator.run(argc, argv);
}