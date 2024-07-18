#include <iostream>
#include <cstdlib>
#include <string>
#include <locale>
#include <cmath>
#include <vector>

using namespace std;

void rewrite(int&, int&, int&, string*&, int*&, int*&);
void rewrite1(int, string&);
void check_symbol1(int, string&, string, int&);
void check_if_del_or_umn(int, string&, vector <int>&, int&);
void check_if_minus_or_plus(int, string&, int&);
void check_errors(int&, string&, int&, vector <int>&);
string check_errors_player(string);
void delenie_deistv_ot_chisel(string&, string&, int*&, string*&, int*&, int&);
void schet_viragenia(int&, string&, int*&, string*&, int*&);
auto calculate(string&);

static void rewrite(int& max_index, int& kolvo_deistv, int& i, string*& deistv, int*& deistv_weight, int*& numbers) // перезапись большого количества данных в процессе работы калькулятор. Все перезаписывает налево на 1 символ
{
	for (int j = max_index; j < kolvo_deistv - i; j++) // следующий символ становится на место настоящего, из-за чего после метода символ с индексом max_index пропадет
	{
		if (j != kolvo_deistv - 1)  // если действие не последнее, происходит перезапись
		{
			deistv[j] = deistv[j + 1];
			deistv_weight[j] = deistv_weight[j + 1];
			numbers[j + 1] = numbers[j + 2];
		}
		else // если действие последнее, ничего не меняется, кроме веса - оно заменяется на отрицательное
		{
			deistv_weight[j] = -1;
		}
	}
}
void rewrite1(int h, string& input) //перезаписывает строку, смещая все символы input налево на 1 символ
{
	for (int j = h; j < input.length(); j++) // следующий символ становится на место настоящего, из-за чего после метода символ с индексом h пропадет
	{
		input[j] = input[j + 1];
	}
}
void check_symbol1(int i, string& input, string str, int& check) // проверка на следующий символ. Если следующее какое-либо действие, ошибка. Ставится только в условиях 
{
	if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^')) // Это просто вывод строки, если символ с индексом i - действие. Меняет check, которые отвечает за работоспособность
	{
		cout << "\n" << str;
		check = 0;
	}
}
void check_if_del_or_umn(int i, string& input, vector <int>& buf_minus, int& check) //работает только в умножении и делении. Если следующий минус, работает. Иначе - нет
{
	if (input[i + 1] == '-') // Если второй символ минус, создается буфер, в который будут записываться индексы чисел, которые необходимо будет конвертировать
	{
		int buf = 0;
		for (int j = 0; j < i + 1; j++) // идет подсчет действий до двойного, чтобы понять номер 
		{
			if ((input[j] == '+') || (input[j] == '-') || (input[j] == '*') || (input[j] == '/') || (input[j] == '^'))
			{
				buf += 1;
			}
		}
		buf_minus.push_back(buf); //в буфере хранится номер числа, которое будет конвертироваться. Оно будет записано в массив 
		buf = 0;
		rewrite1(i + 1, input); //необходимо удалить минус, для чего и перезаписывается число
	}
	else // Если второй символ не ичсло и не минус, ошибка
	{
		check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд", check);
	}
}
void check_if_minus_or_plus(int i, string& input, int& check) // работает только в плюсе или минусе. Если следующий минус, работает, иначе - нет
{
	if (input[i + 1] == '-') // Если первый символ минус, 2 минуса становятся плюсом. Если первый символ плюс, просто перезапись
	{
		if (input[i] == '-')
		{
			input[i + 1] = '+'; // согласно логике второе действие становится плюсом, и оно же становится на место первого, оставаясь единственным
		}
		rewrite1(i, input); // перезапись числа со сдвигом налево на 1 символ
	}
	else //ну и если второй символ не число или минус, ошибка
	{
		check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд", check);
	}
}
void check_errors(int& check, string& input, int& check_minus, vector <int>& buf_minus)
{
	if (check == 1) //если до сих пор ошибки нет, проводится поиск дальше
	{
		for (int i = 0; i < input.length(); i++) // цикл проверок на ошибки пользователя
		{
			if (input[0] == '-')// если первый символ действие и он минус, значение check_minus примет 1 и произойдет перезапись строки, удалив первый минус. В дальнейшем первое число будет конвертированно
			{
				check_minus = 1;
				rewrite1(0, input);
				check_symbol1(0, input, "Ошибка.Действие не может быть первым символом", check); // проверка на наличие первым символом не числа. Любое - ошибка
			}
			if (i == (input.length() - 1)) //проверка последнего символа. Любой - ошибка
			{
				check_symbol1((input.length() - 1 - check_minus), input, "Ошибка.Действие не может быть последним символом", check);
			}
			else // проверка на двойные действия
			{
				if (input[i] == '+') //при первом плюсе может быть только минус - писать 7 + +8 бредятина. Если второй минус, из двух символов делается просто минус и перезаписывается
				{
					check_if_minus_or_plus(i, input, check); // Если второй НЕ минус, ошибка
				}
				else if (input[i] == '-') // при первом минусе может быть только минус - писать 7 - + 8 бредятина. Если второй минус, из двух символов делается просто плюс и перезаписывается. Если второй НЕ минус, ошибка
				{
					check_if_minus_or_plus(i, input, check);// Если второй НЕ минус, ошибка
				}
				else if (input[i] == '*') // при первом умножении может быть только минус. Если не он - ошибка, если минус, индекс числа записывается в буфер, дальше по коду оно инвертируется
				{
					check_if_del_or_umn(i, input, buf_minus, check); // Если второй НЕ минус, ошибка
				}
				else if (input[i] == '/') // при первом делении может быть только минус. Если не он - ошибка, если минус, индекс числа записывается в буфер, дальше по коду оно инвертируется
				{
					check_if_del_or_umn(i, input, buf_minus, check); // Если второй НЕ минус, ошибка
				}
				else if (input[i] == '^') // после  степени в принципе не может ничего быть пока что. Для обработки минуса нужно менять код на работу с вещественными числами
				{
					check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд", check);
				}
			}
		}
	}
}
string check_errors_player(string input)
{
	int check = 1;
	for (int i = 0; i < input.length(); i++) // цикл проверок на ошибки пользователя
	{
		if (input[0] != '-')// если первый символ действие и он минус, произойдет перезапись строки, удалив первый минус. В дальнейшем первое число будет конвертированно
		{
			check_symbol1(0, input, "Ошибка.Действие не может быть первым символом \n", check); // проверка на наличие первым символом не числа. Любое - ошибка
			if (check == 0)
			{
				return "Действие не может быть первым символом";
			}
		}
		else
		{
			check_symbol1(1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
			if (check == 0)
			{
				return "Не может быть 2 действия подряд";
			}
		}
		if (i == (input.length() - 1)) //проверка последнего символа. Любой - ошибка
		{
			check_symbol1((input.length() - 1), input, "Ошибка.Действие не может быть последним символом \n", check);
			if (check == 0)
			{
				return "Действие не может быть последним символом";
			}
			else
			{
				return "";
			}
		}
		else // проверка на двойные действия
		{
			if (input[i] == '+') //при первом плюсе может быть только минус - писать 7 + +8 бредятина. Если второй минус, из двух символов делается просто минус и перезаписывается
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
				}
				if (check == 0)
				{
					return "Не может быть 2 действия подряд";
				}
			}
			else if (input[i] == '-') // при первом минусе может быть только минус - писать 7 - + 8 бредятина. Если второй минус, из двух символов делается просто плюс и перезаписывается. Если второй НЕ минус, ошибка
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
				}
				if (check == 0)
				{
					return "Не может быть 2 действия подряд";
				}
			}
			else if (input[i] == '*') // при первом умножении может быть только минус. Если не он - ошибка, если минус, индекс числа записывается в буфер, дальше по коду оно инвертируется
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
				}
				if (check == 0)
				{
					return "Не может быть 2 действия подряд";
				}
			}
			else if (input[i] == '/') // при первом делении может быть только минус. Если не он - ошибка, если минус, индекс числа записывается в буфер, дальше по коду оно инвертируется
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
				}
				if (check == 0)
				{
					return "Не может быть 2 действия подряд";
				}
			}
			else if (input[i] == '^') // после  степени в принципе не может ничего быть пока что. Для обработки минуса нужно менять код на работу с вещественными числами
			{
				check_symbol1(i + 1, input, "Ошибка.Не может быть 2 действия подряд \n", check);
				if (check == 0)
				{
					return "Не может быть 2 действия подряд";
				}
			}
		}
	}
}
void delenie_deistv_ot_chisel(string& input, string& buf, int*& numbers, string*& deistv, int*& deistv_weight, int& kolvo_numbers)
{
	for (int i = 0; i < input.length(); i++) // деление действий от чисел. В буфер зщаписывается число до тех пор, пока не встретится действие. deistv_weight - вес действия, записывается столько же, сколько действий
	{
		if ((input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/') && (input[i] != '^')) //если символ НЕ действие, заполняется буфер
		{
			buf += input[i];
		}
		else // При встрече действия буфер переводится в число и записывается в массив чисел. 
		{
			numbers[kolvo_numbers] = stoi(buf);
			deistv[kolvo_numbers] = input[i];
			// Запись в массив веса символа. Степень>умножение>сложение. Необходимо, чтобы действия делались в правильном математическом порядке 
			// -->>
			if ((input[i] == '+') || (input[i] == '-'))
			{
				deistv_weight[kolvo_numbers] = 1; // запись в массив весов действий
			}
			else if ((input[i] == '*') || (input[i] == '/'))
			{
				deistv_weight[kolvo_numbers] = 2; // запись в массив весов действий
			}
			else if (input[i] == '^')
			{
				deistv_weight[kolvo_numbers] = 3; // запись в массив весов действий
			}
			// <<--
			kolvo_numbers++;
			buf = "";
		}
		if (i == input.length() - 1) //последнее число не запишется в буфер без принуждения
		{
			numbers[kolvo_numbers] = stoi(buf);
		}
	}
}
void schet_viragenia(int& kolvo_deistv, string& input, int*& numbers, string*& deistv, int*& deistv_weight)
{
	for (int i = 0; i < kolvo_deistv; i++) // поочередное выполнение действий
	{
		int max_weidth = 0; // максимальные вес и индекс. По весу ищется индекс, который используется как индекс выполняющегося действия
		int max_index = 0;
		for (int j = 0; j < kolvo_deistv; j++)
		{
			if (deistv_weight[j] > max_weidth) // если вес по индексу j больше, чем нынешний вес, индекс j становится максимальным индексом и вес индекса j становится максимальным весом
			{
				max_weidth = deistv_weight[j];
				max_index = j;
			}
		}
		// следующите действия проходят по максимально найденному весу. Т.е. степень выполнится первее сложения или умножения. 
		// После действия и вес, и индекс стираются, из-за чего повторной сработки не будет
		if (deistv[max_index] == "+") // сложение, последующая перезапись массивов -->> **
		{
			numbers[max_index] = numbers[max_index] + numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "-") // вычитание, последующая перезапись массивов -->> **
		{
			numbers[max_index] = numbers[max_index] - numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "*") // умножение, последующая перезапись массивов -->> **
		{
			numbers[max_index] = numbers[max_index] * numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "/") //деление, последующая перезапись массивов -->> **
		{
			numbers[max_index] = numbers[max_index] / numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "^") // возведение в степень, последующая перезапись массивов --> **
		{
			numbers[max_index] = pow(numbers[max_index], numbers[max_index + 1]);
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
	}
}
auto calculate(string& input) {
	string buf;
	int kolvo_minus = 0; // нужно только для счета удаления пробелов
	int kolvo_numbers = 0;
	int kolvo_deistv = 0;
	int check = 1;
	int check_minus = 0;
	vector <int> buf_minus;
	for (int i = 0; i < input.length(); i++) // уничтожение всех пробелов
	{
		if ((input[i] == ' ') && (i != input.length() - 1)) //при встрече пробела происходит перезапись, где индекс i, являющийся пробелом, будет удален
		{
			rewrite1(i, input);
			kolvo_minus++; // в цикле проверки на буквы это число вычтется из длины строки, чтобы пробелы в конце строки не считывались
		}
	}
	check_errors(check, input, check_minus, buf_minus); // здесь идет проверка на правильность введения действий, например, ++ - ошибка
	if (check == 1) //если ошибок нет, можно че-то делать
	{
		for (int i = 0; i < input.length(); i++) // подсчет количества действий
		{
			if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^'))
			{
				kolvo_deistv++; // хранит в себе количество действий
			}
		}
		int* numbers = new int[kolvo_deistv + 1]; // создание массивов чисел, действий и весов этих действий
		string* deistv = new string[kolvo_deistv];
		int* deistv_weight = new int[kolvo_deistv];
		// работа кода:
		// строка делится на числа и действия следующим циклом
		// массив чисел - числовой, действий - строковый
		// также в отдельный массив записывается вес действия, массив - числовой
		// последним циклом в работе выбирается максимальный вес символа и его индекс
		// по этому индексу находится первое число и по индексу+1 следующее. В итоге имеем обычный пример из двух чисел и 1 действия между ними
		// выполняется действие, результат записывается в первое число, а вес, действие и число по индексу+1 удаляются с помощью перезаписи
		// Проделав такой цикл столько раз, сколько есть действий, останется 1 число, которое, очевидно, является ответом на весь пример

		//разделение по разным массивам чисел и действий
		delenie_deistv_ot_chisel(input, buf, numbers, deistv, deistv_weight, kolvo_numbers);
		//конвертация первого числа, если стоит минус
		if (check_minus == 1)
		{
			numbers[0] = numbers[0] * -1;
		}
		// конвертация чисел, где после умножения шел минус
		for (size_t i = 0; i < buf_minus.size(); i++)
		{
			numbers[buf_minus[i]] = numbers[buf_minus[i]] * -1;
		}
		// непосредственное выполнения действия
		schet_viragenia(kolvo_deistv, input, numbers, deistv, deistv_weight);
		return numbers[0]; // Вывод единственного числа, являющегося ответом
	}
}
