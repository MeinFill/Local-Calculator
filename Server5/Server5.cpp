#include "httplib.h"
#include "Calculator.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <locale>
#include <cmath>
#include <vector>

using namespace std;
using namespace httplib;
string errors = "";
int main() {
    setlocale(LC_ALL, "Russian");
    Server svr;
    svr.Post("/", [](const Request& req, Response& res) {
        bool check = true;
        string output = req.get_param_value("a");
        if (output.length() > 0) { // проверка на наличие ввода
            if (output.length() < 20000)
            {
                for (int i = 0; i < output.length(); i++) { // проверка на отсутствие буковок
                    if (output[i] != '^' && output[i] != '*' && output[i] != '/' && output[i] != '+' && output[i] != '-' && output[i] != ' ' && output[i] != '0' && output[i] != '1' && output[i] != '2' && output[i] != '3' && output[i] != '4' && output[i] != '5' && output[i] != '6' && output[i] != '7' && output[i] != '8' && output[i] != '9' && output[i] != '.' && output[i] != ',') {
                        check = false;
                    }
                }
                errors = check_errors_player(output); // метод проверяет на наличие повторяющихся действий. НИЧЕГО НЕ МЕНЯЕТ
                if (check && errors.length() == 0) {
                    // если все в порядке, и у переменной число, то вывожу число
                    if (calculate(output) > -2000000000 && calculate(output) < 2000000000) {
                        res.set_content(to_string(calculate(output)), "enctype ");// метод считает все сам, вводимое число изменилось
                    }
                    else {
                        res.set_content("Ну просили же результат меньше 2 млрд", "enctype ");
                    }

                }
                else { // если есть буквы ИЛИ ошибки в вводе
                    if (errors.length() > 0) { // если ошибки в вводе, выводится ошибка
                        res.set_content(errors, "enctype ");
                    }
                    // если была встречена хотя бы одна буква check это увидит и выведет ошибку 
                    else {
                        res.set_content("А можно вводить числа?", "enctype ");
                        cout << "\n" << "Ввод буковок" << "\n";
                    }
                }
            }
            else {
                res.set_content("А можно вводить меньше символов", "enctype");
            }
        }
        else {
            // если все пусто или же у переменной нет числа, где запрос???
            res.set_content("Где запрос?", "enctype");
            cout << "\n" << "Где запрос?" << "\n";
        }
        });

    // Это просто если перейти по ссылке, а не по форме
    svr.Get("/", [](const Request& req, Response& res) {
        res.set_content("Hello!", "text/plain");
        });
    std::cout << "Сервер находится по ссылке http://localhost:5000\n";
    svr.listen("0.0.0.0", 5000);

    return 0;
}