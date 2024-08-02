#include <iostream>
#include <cstdlib>
#include <string>
#include <locale>
#include <cmath>
#include <vector>

using namespace std;
void rewrite(int&, int&, int&, string*&, int*&, double*&);
void rewrite1(int, string&);
void check_symbol1(int, string&, string, int&);
void check_if_del_or_umn(int, string&, vector <int>&, int&);
void check_if_minus_or_plus(int, string&, int&);
void check_errors(int&, string&, int&, vector <int>&);
string check_errors_player(string);
string check_tochek(string, int&, string&);
void delenie_deistv_ot_chisel(string&, string&, double*&, string*&, int*&, int&, int&);
void schet_viragenia(int&, string&, double*&, string*&, int*&);
void privedenie(string&);
double calculate(string&, int&);


static void rewrite(int& max_index, int& kolvo_deistv, int& i, string*& deistv, int*& deistv_weight, double*& numbers) // ���������� �������� ���������� ������ � �������� ������ �����������. ��� �������������� ������ �� 1 ������
{
	for (int j = max_index; j < kolvo_deistv - i; j++) // ��������� ������ ���������� �� ����� ����������, ��-�� ���� ����� ������ ������ � �������� max_index ��������
	{
		if (j != kolvo_deistv - 1)  // ���� �������� �� ���������, ���������� ����������
		{
			deistv[j] = deistv[j + 1];
			deistv_weight[j] = deistv_weight[j + 1];
			numbers[j + 1] = numbers[j + 2];
		}
		else // ���� �������� ���������, ������ �� ��������, ����� ���� - ��� ���������� �� �������������
		{
			deistv_weight[j] = -1;
		}
	}
}
void rewrite1(int h, string& input) //�������������� ������, ������ ��� ������� input ������ �� 1 ������
{
	for (int j = h; j < input.length(); j++) // ��������� ������ ���������� �� ����� ����������, ��-�� ���� ����� ������ ������ � �������� h ��������
	{
		input[j] = input[j + 1];
	}
}
void check_symbol1(int i, string& input, string str, int& check) // �������� �� ��������� ������. ���� ��������� �����-���� ��������, ������. �������� ������ � �������� 
{
	if ((input[i] == '.') || (input[i] == ',') || (input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^')) // ��� ������ ����� ������, ���� ������ � �������� i - ��������. ������ check, ������� �������� �� �����������������
	{
		check = 0;
	}
}
void check_if_del_or_umn(int i, string& input, vector <int>& buf_minus, int& check) //�������� ������ � ��������� � �������. ���� ��������� �����, ��������. ����� - ���
{
	if (input[i + 1] == '-') // ���� ������ ������ �����, ��������� �����, � ������� ����� ������������ ������� �����, ������� ���������� ����� ��������������
	{
		int buf = 0;
		for (int j = 0; j < i + 1; j++) // ���� ������� �������� �� ��������, ����� ������ ����� 
		{
			if ((input[j] == '+') || (input[j] == '-') || (input[j] == '*') || (input[j] == '/') || (input[j] == '^'))
			{
				buf += 1;
			}
		}
		buf_minus.push_back(buf); //� ������ �������� ����� �����, ������� ����� ����������������. ��� ����� �������� � ������ 
		buf = 0;
		rewrite1(i + 1, input); //���������� ������� �����, ��� ���� � ���������������� �����
	}
	else // ���� ������ ������ �� ����� � �� �����, ������
	{
		check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������", check);
	}
}
void check_if_minus_or_plus(int i, string& input, int& check) // �������� ������ � ����� ��� ������. ���� ��������� �����, ��������, ����� - ���
{
	if (input[i + 1] == '-') // ���� ������ ������ �����, 2 ������ ���������� ������. ���� ������ ������ ����, ������ ����������
	{
		if (input[i] == '-')
		{
			input[i + 1] = '+'; // �������� ������ ������ �������� ���������� ������, � ��� �� ���������� �� ����� �������, ��������� ������������
		}
		rewrite1(i, input); // ���������� ����� �� ������� ������ �� 1 ������
	}
	else //�� � ���� ������ ������ �� ����� ��� �����, ������
	{
		check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������", check);
	}
}
void check_errors(int& check, string& input, int& check_minus, vector <int>& buf_minus)
{
	if (check == 1) //���� �� ��� ��� ������ ���, ���������� ����� ������
	{
		for (int i = 0; i < input.length(); i++) // ���� �������� �� ������ ������������
		{
			if (input[0] == '-')// ���� ������ ������ �������� � �� �����, �������� check_minus ������ 1 � ���������� ���������� ������, ������ ������ �����. � ���������� ������ ����� ����� ���������������
			{
				check_minus = 1;
				rewrite1(0, input);
				check_symbol1(0, input, "������.�������� �� ����� ���� ������ ��������", check); // �������� �� ������� ������ �������� �� �����. ����� - ������
			}
			if (i == (input.length() - 1)) //�������� ���������� �������. ����� - ������
			{
				check_symbol1((input.length() - 1 - check_minus), input, "������.�������� �� ����� ���� ��������� ��������", check);
			}
			else // �������� �� ������� ��������
			{
				if (input[i] == '+') //��� ������ ����� ����� ���� ������ ����� - ������ 7 + +8 ���������. ���� ������ �����, �� ���� �������� �������� ������ ����� � ����������������
				{
					check_if_minus_or_plus(i, input, check); // ���� ������ �� �����, ������
				}
				else if (input[i] == '-') // ��� ������ ������ ����� ���� ������ ����� - ������ 7 - + 8 ���������. ���� ������ �����, �� ���� �������� �������� ������ ���� � ����������������. ���� ������ �� �����, ������
				{
					check_if_minus_or_plus(i, input, check);// ���� ������ �� �����, ������
				}
				else if (input[i] == '*') // ��� ������ ��������� ����� ���� ������ �����. ���� �� �� - ������, ���� �����, ������ ����� ������������ � �����, ������ �� ���� ��� �������������
				{
					check_if_del_or_umn(i, input, buf_minus, check); // ���� ������ �� �����, ������
				}
				else if (input[i] == '/') // ��� ������ ������� ����� ���� ������ �����. ���� �� �� - ������, ���� �����, ������ ����� ������������ � �����, ������ �� ���� ��� �������������
				{
					check_if_del_or_umn(i, input, buf_minus, check); // ���� ������ �� �����, ������
				}
				else if (input[i] == '^') // �����  ������� ����� ���� ������� �����
				{
					check_if_del_or_umn(i, input, buf_minus, check); //���� ������ �� �����, ������
				}
			}
		}
	}
}
string check_errors_player(string input)
{
	int check = 1;
	for (int i = 0; i < input.length(); i++) // ���� �������� �� ������ ������������
	{
		if (input[0] != '-')// ���� ������ ������ �������� � �� �����, ���������� ���������� ������, ������ ������ �����. � ���������� ������ ����� ����� ���������������
		{
			check_symbol1(0, input, "������.�������� �� ����� ���� ������ �������� \n", check); // �������� �� ������� ������ �������� �� �����. ����� - ������
			if (check == 0)
			{
				return "�������� �� ����� ���� ������ ��������";
			}
		}
		else
		{
			check_symbol1(1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
			if (check == 0)
			{
				return "�� ����� ���� 2 �������� ������";
			}
		}
		if (i == (input.length() - 1)) //�������� ���������� �������. ����� - ������
		{
			check_symbol1((input.length() - 1), input, "������.�������� �� ����� ���� ��������� �������� \n", check);
			if (check == 0)
			{
				return "�������� �� ����� ���� ��������� ��������";
			}
			else
			{
				return "";
			}
		}
		else // �������� �� ������� ��������
		{
			if (input[i] == '+') //��� ������ ����� ����� ���� ������ ����� - ������ 7 + +8 ���������. ���� ������ �����, �� ���� �������� �������� ������ ����� � ����������������
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
				}
				if (check == 0)
				{
					return "�� ����� ���� 2 �������� ������";
				}
			}
			else if (input[i] == '-') // ��� ������ ������ ����� ���� ������ ����� - ������ 7 - + 8 ���������. ���� ������ �����, �� ���� �������� �������� ������ ���� � ����������������. ���� ������ �� �����, ������
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
				}
				if (check == 0)
				{
					return "�� ����� ���� 2 �������� ������";
				}
			}
			else if (input[i] == '*') // ��� ������ ��������� ����� ���� ������ �����. ���� �� �� - ������, ���� �����, ������ ����� ������������ � �����, ������ �� ���� ��� �������������
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
				}
				if (check == 0)
				{
					return "�� ����� ���� 2 �������� ������";
				}
			}
			else if (input[i] == '/') // ��� ������ ������� ����� ���� ������ �����. ���� �� �� - ������, ���� �����, ������ ����� ������������ � �����, ������ �� ���� ��� �������������
			{
				if (input[i + 1] == '-')
				{
				}
				else
				{
					check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
				}
				if (check == 0)
				{
					return "�� ����� ���� 2 �������� ������";
				}
			}
			else if (input[i] == '^') // �����  ������� � �������� �� ����� ������ ���� ���� ���. ��� ��������� ������ ����� ������ ��� �� ������ � ������������� �������
			{
				check_symbol1(i + 1, input, "������.�� ����� ���� 2 �������� ������ \n", check);
				if (check == 0)
				{
					return "�� ����� ���� 2 �������� ������";
				}
			}
		}
	}
}
string check_tochek(string input, int& check_tochki, string& errors)
{
	string buf = "";
	for (int i = 0; i < input.length(); i++) // ������� �������� �� �����. � ����� ������������� ����� �� ��� ���, ���� �� ���������� ��������. deistv_weight - ��� ��������, ������������ ������� ��, ������� ��������
	{
		if ((input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/') && (input[i] != '^')) //���� ������ �� ��������, ����������� �����
		{
			buf += input[i];
		}
		else // ��� ������� �������� ����� ����������� � ����� � ������������ � ������ �����. 
		{
			int schet_toch = 0;
			for (int j = 0; j < buf.length(); j++)
			{
				if (buf[j] == '.' || buf[j] == ',')
				{
					schet_toch += 1;
				}
			}
			if (schet_toch > 1)
			{
				return "� ������������ ����� ������ 1 �����";
			}
		}
		if (i == input.length() - 1)
		{
			if (input[i] == ',' || input[i] == '.')
			{
				return "����� �� ����� ���� ��������� ��������";
			}
			else
			{
				return errors;
			}
		}
	}
	buf = "";
}
void delenie_deistv_ot_chisel(string& input, string& buf, double*& numbers, string*& deistv, int*& deistv_weight, int& kolvo_numbers, int& check_tochki)
{
	for (int i = 0; i < input.length(); i++) // ������� �������� �� �����. � ����� ������������� ����� �� ��� ���, ���� �� ���������� ��������. deistv_weight - ��� ��������, ������������ ������� ��, ������� ��������
	{
		if ((input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/') && (input[i] != '^')) //���� ������ �� ��������, ����������� �����
		{
			buf += input[i];
		}
		else // ��� ������� �������� ����� ����������� � ����� � ������������ � ������ �����. 
		{
			int schet_toch = 0;
			for (int j = 0; j < buf.length(); j++)
			{
				if (buf[j] == '.' || buf[j] == ',')
				{
					schet_toch += 1;
				}
			}
			if (schet_toch > 1)
			{
				check_tochki = 0;
			}
			else if (schet_toch == 1)
			{
				string ah = "";
				string al = "";
				int trig = 0;
				for (int j = 0; j < buf.length(); j++)
				{
					if (trig == 0)
					{
						if (buf[j] != '.' && buf[j] != ',')
						{
							ah += buf[j];
						}
						else
						{
							trig = 1;
						}
					}
					else
					{
						al += buf[j];
					}
				}
				numbers[kolvo_numbers] = stod(ah) + (stod(al) / pow(10, al.length()));
			}
			else if (schet_toch == 0)
			{
				numbers[kolvo_numbers] = stod(buf);
			}
			if (check_tochki == 1)
			{
				deistv[kolvo_numbers] = input[i];
				// ������ � ������ ���� �������. �������>���������>��������. ����������, ����� �������� �������� � ���������� �������������� ������� 
				// -->>
				if ((input[i] == '+') || (input[i] == '-'))
				{
					deistv_weight[kolvo_numbers] = 1; // ������ � ������ ����� ��������
				}
				else if ((input[i] == '*') || (input[i] == '/'))
				{
					deistv_weight[kolvo_numbers] = 2; // ������ � ������ ����� ��������
				}
				else if (input[i] == '^')
				{
					deistv_weight[kolvo_numbers] = 3; // ������ � ������ ����� ��������
				}
				// <<--
				kolvo_numbers++;
				buf = "";
				schet_toch = 0;
			}
		}
		if (i == input.length() - 1) //��������� ����� �� ��������� � ����� ��� �����������
		{
			int schet_toch = 0;
			for (int j = 0; j < buf.length(); j++)
			{
				if (buf[j] == '.' || buf[j] == ',')
				{
					schet_toch += 1;
				}
			}
			if (schet_toch > 1)
			{
				check_tochki = 0;
			}
			else if (schet_toch == 1)
			{
				string ah = "";
				string al = "";
				int trig = 0;
				for (int j = 0; j < buf.length(); j++)
				{
					if (trig == 0)
					{
						if (buf[j] != '.' && buf[j] != ',')
						{
							ah += buf[j];
						}
						else
						{
							trig = 1;
						}
					}
					else
					{
						al += buf[j];
					}
				}
				numbers[kolvo_numbers] = stod(ah) + (stod(al) / pow(10, al.length()));
			}
			else if (schet_toch == 0)
			{
				numbers[kolvo_numbers] = stod(buf);
			}
		}
	}
}
void schet_viragenia(int& kolvo_deistv, string& input, double*& numbers, string*& deistv, int*& deistv_weight)
{
	for (int i = 0; i < kolvo_deistv; i++) // ����������� ���������� ��������
	{
		int max_weidth = 0; // ������������ ��� � ������. �� ���� ������ ������, ������� ������������ ��� ������ �������������� ��������
		int max_index = 0;
		for (int j = 0; j < kolvo_deistv; j++)
		{
			if (deistv_weight[j] > max_weidth) // ���� ��� �� ������� j ������, ��� �������� ���, ������ j ���������� ������������ �������� � ��� ������� j ���������� ������������ �����
			{
				max_weidth = deistv_weight[j];
				max_index = j;
			}
		}
		// ���������� �������� �������� �� ����������� ���������� ����. �.�. ������� ���������� ������ �������� ��� ���������. 
		// ����� �������� � ���, � ������ ���������, ��-�� ���� ��������� �������� �� �����
		if (deistv[max_index] == "+") // ��������, ����������� ���������� �������� -->> **
		{
			numbers[max_index] = numbers[max_index] + numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "-") // ���������, ����������� ���������� �������� -->> **
		{
			numbers[max_index] = numbers[max_index] - numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "*") // ���������, ����������� ���������� �������� -->> **
		{
			numbers[max_index] = numbers[max_index] * numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "/") //�������, ����������� ���������� �������� -->> **
		{
			numbers[max_index] = numbers[max_index] / numbers[max_index + 1];
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
		else if (deistv[max_index] == "^") // ���������� � �������, ����������� ���������� �������� --> **
		{
			numbers[max_index] = pow(numbers[max_index], numbers[max_index + 1]);
			rewrite(max_index, kolvo_deistv, i, deistv, deistv_weight, numbers);// ** <<--
		}
	}
}
void privedenie(string& input)
{
	int check = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '.' || input[i] == ',')
		{
			check = 1;
		}
	}
	for (int i = input.length() - 1; check == 1; i--)
	{
		if (input[i] == '0')
		{
			input[i] = ' ';
		}
		else if (input[i] == ',' || input[i] == '.')
		{
			input[i] = ' ';
			check = 0;
		}
	}
}
double calculate(string& input, int& check_tochki) {
	string buf;
	int kolvo_minus = 0; // ����� ������ ��� ����� �������� ��������
	int kolvo_numbers = 0;
	int kolvo_deistv = 0;
	int check = 1;
	int check_minus = 0;
	vector <int> buf_minus;
	for (int i = 0; i < input.length(); i++) // ����������� ���� ��������
	{
		if ((input[i] == ' ') && (i != input.length() - 1)) //��� ������� ������� ���������� ����������, ��� ������ i, ���������� ��������, ����� ������
		{
			rewrite1(i, input);
			kolvo_minus++; // � ����� �������� �� ����� ��� ����� �������� �� ����� ������, ����� ������� � ����� ������ �� �����������
		}
	}
	check_errors(check, input, check_minus, buf_minus); // ����� ���� �������� �� ������������ �������� ��������, ��������, ++ - ������
	if (check == 1) //���� ������ ���, ����� ��-�� ������
	{
		for (int i = 0; i < input.length(); i++) // ������� ���������� ��������
		{
			if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^'))
			{
				kolvo_deistv++; // ������ � ���� ���������� ��������
			}
		}
		double* numbers = new double[kolvo_deistv + 1]; // �������� �������� �����, �������� � ����� ���� ��������
		string* deistv = new string[kolvo_deistv];
		int* deistv_weight = new int[kolvo_deistv];
		// ������ ����:
		// ������ ������� �� ����� � �������� ��������� ������
		// ������ ����� - ��������, �������� - ���������
		// ����� � ��������� ������ ������������ ��� ��������, ������ - ��������
		// ��������� ������ � ������ ���������� ������������ ��� ������� � ��� ������
		// �� ����� ������� ��������� ������ ����� � �� �������+1 ���������. � ����� ����� ������� ������ �� ���� ����� � 1 �������� ����� ����
		// ����������� ��������, ��������� ������������ � ������ �����, � ���, �������� � ����� �� �������+1 ��������� � ������� ����������
		// �������� ����� ���� ������� ���, ������� ���� ��������, ��������� 1 �����, �������, ��������, �������� ������� �� ���� ������

		//���������� �� ������ �������� ����� � ��������
		delenie_deistv_ot_chisel(input, buf, numbers, deistv, deistv_weight, kolvo_numbers, check_tochki);
		//����������� ������� �����, ���� ����� �����
		if (check_tochki == 1)
		{
			if (check_minus == 1)
			{
				numbers[0] = numbers[0] * -1;
			}
			// ����������� �����, ��� ����� ��������� ��� �����
			for (size_t i = 0; i < buf_minus.size(); i++)
			{
				numbers[buf_minus[i]] = numbers[buf_minus[i]] * -1;
			}
			// ���������������� ���������� ��������
			schet_viragenia(kolvo_deistv, input, numbers, deistv, deistv_weight);
			return numbers[0]; // ����� ������������� �����, ����������� �������
		}
	}
}