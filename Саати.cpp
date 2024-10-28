#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

void create_mas(int kolvo, const vector<int>& spis) {
    cout << "Элементы списка: " << endl;
    for (int i = 0; i<size(spis); ++i) {
        cout << spis[i] << endl;

    }

}

void vivod_ocenk(vector<vector<float>>& a) 
{
    for (float i = 0; i < a.size(); i++) 
    {
        for (float j = 0; j < a[0].size(); j++) 
        {
            cout << fixed << setprecision(2) << a[i][j] << "\t\t";
        }
        cout << endl << endl;
    }
}

void vivod_kri(vector<string>& a)
{
    for (int i = 0; i < a.size(); i++) 
    {
        cout << "Критерий колонны номер " << i + 1 << ": " << a[i] << endl;
    }
    cout << endl;
}

void create_kri(vector<string>& a, const int k) 
{
    string RUS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    string rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    for (int i = 0; i < k; i++) 
    {
        while (true) 
        {
            cout << "Введите критерий номер " << i + 1 << " Пример - 'Стиль'" << endl;
            cin >> a[i];

            if (a[i].empty())
            {
                cout << "Введите данные!" << endl << endl;
                continue;
            }

           
            bool correct = RUS.find(a[i][0]) != string::npos;  //Проверка на первую заглавную букву

            
            for (int j = 1; j < a[i].size(); j++) 
            {
                if (rus.find(a[i][j]) == string::npos)  //Проверка на прописные буквы
                {
                    correct = false;
                    break;
                }
            }

            if (correct) 
            {
                break;
            }
            else 
            {
                cout << "Проверьте корректность вводимых данных!" << endl << endl;
            }
        }

        cout << endl;
    }
    
    a.push_back("Построчная сумма");
    a.push_back("Весовые коэфиценты");
}

float parse_fraction(const string& input) //Функция нужна, если пользователь введёт число через дробь - 1/6
{
    size_t pos = input.find('/');
    if (pos != string::npos) 
    {
        float numerator = stof(input.substr(0, pos));
        float denominator = stof(input.substr(pos + 1));
        if (denominator != 0) 
        {
            return numerator / denominator;
        }
        else 
        {
            throw invalid_argument("Знаменатель не может быть равен нулю.");
        }
    }
    else 
    {
        return stof(input); // Если нет '/', просто преобразуем в float
    }
}

void ocenki_vvod(vector<vector<float>>& oc, const vector<string>& kr) 
{
    string input;
    for (size_t i = 0; i < oc.size() - 1; i++)
    {
        for (size_t j = i + 1; j < oc.size() - 1; j++)
        {
            cout << "Как вы оцениваете отношение " << kr[i] << "/" << kr[j] << " ?" << endl;

            while (true) { // Цикл для повторного ввода в случае ошибки
                cin >> input;

                try {
                    float k = parse_fraction(input);
                    if (k <= 0) 
                    {
                        cout << "Оценка должна быть положительным числом!" << endl;
                    }
                    else 
                    {
                        oc[i][j] = k;
                        oc[j][i] = 1 / k; 
                        break; 
                    }
                }
                catch (const invalid_argument& e) 
                {
                    cout << "Ошибка: " << e.what() << " Введите число в формате 'числитель/знаменатель' или просто число!" << endl;
                }
                catch (...) 
                {
                    cout << "Введен неверный символ! Введите число!" << endl;
                }
            }

            cout << endl;
        }
    }

    // Обозначение отношений для самих на себя
    for (size_t i = 0; i < oc.size() - 1; i++) {
        oc[i][i] = 1;
    }

    // Присвоение суммы строки
    for (size_t i = 0; i < oc.size() - 1; i++) {
        for (size_t j = 0; j < oc.size() - 1; j++) {
            oc[i][oc[0].size() - 2] += oc[i][j];
        }
    }

    // Присвоение суммы столбца
    for (size_t j = 0; j < oc.size() - 1; j++) {
        oc[oc.size() - 1][oc[0].size() - 2] += oc[j][oc[0].size() - 2];
    }

    // Расчет весовых коэффициентов
    for (size_t i = 0; i < oc.size(); i++) {
        oc[i][oc[0].size() - 1] = oc[i][oc[0].size() - 2] / oc[oc.size() - 1][oc[0].size() - 2];
    }
}

int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");

    
    
    while (true)
    {
        int n;

        cout << "Сколько критериев вы хотите добавить?: " << endl;
        cin >> n;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(); // Игнорируем некорректный ввод
            cout << "Вы ввели некорректное число! Попробуйте снова." << endl;

            continue;
        }
        cout << endl;

        vector<vector<float>> matrica(n + 1, vector<float>(n + 2));
                
        vector<string> kriter(n);
                
        create_kri(kriter, n);
                
        ocenki_vvod(matrica, kriter);

        system("cls");

        vivod_kri(kriter);
        
        vivod_ocenk(matrica);

        return 0;
    }
   
}