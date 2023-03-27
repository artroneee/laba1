//#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <iostream>
#include "windows.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include "thread"
#include <regex>
#include <locale>
#include <codecvt>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;
wstring_convert<std::codecvt_utf8<wchar_t>> converter;
void end() {
    cout << "До свидания!";
    exit(0);
}
void search();
void check_path();
void managment();
void show_files();
void add_folder();
void remove_folder();
void remove_folder();
void percent();

string phone, mail;
wstring login;
double total_file_count, temp_percent, percentt;
string login_str;
bool isNameValid(const std::wstring& name) {
    for (wchar_t c : name) {
        if (!iswalpha(c) && c != ' ') {
            return false;
        }
    }
    std::wistringstream iss(name);
    std::wstring word;
    while (iss >> word) {
        if (!iswupper(word[0])) {
            return false;
        }
        for (size_t i = 1; i < word.size(); ++i) {
            if (!iswlower(word[i])) {
                return false;
            }
        }
    }
    return true;
}
void count_files() {
    double total_file_count1=0;
    std::ifstream file("C:\\Users\\Artem\\db\\db_\\folders.txt");//поменять на вашу
    std::string folder_path;
    while (std::getline(file, folder_path)) {
        int file_count = 0;

        for (auto& file : fs::directory_iterator(folder_path)) {
            if (file.is_regular_file()) {
                file_count++;
            }
        }

        std::cout << "Папка " << folder_path << " содержит " << file_count << " файлов." << std::endl;
        total_file_count1 += file_count;
    }

    std::cout << "Всего просматриваемых файлов: " << total_file_count1 << std::endl;
    file.close();
}
void percent() {

    std::ifstream file("C:\\Users\\Artem\\db\\db_\\folders.txt");//поменять на вашу
    std::string folder_path;
    while (std::getline(file, folder_path)) {
        int file_count = 0;

        for (auto& file : fs::directory_iterator(folder_path)) {
            if (file.is_regular_file()) {
                file_count++;
            }
        }
        total_file_count += file_count;
    }temp_percent = 100 / total_file_count;
    while (percentt < 99) {
        cout << "Прочитано " << percentt << " %\n";
        percentt += temp_percent;
    }cout << "Прочитано 100 %\n";
    percentt = 0, temp_percent = 0, total_file_count = 0;
    file.close();
}
void search_login(const std::string& login_temp, const std::string& mail_temp, const std::string& phone_temp, const fs::path& folder_paths) {


    if (login_str == "" && mail == "" && phone == "") {
        cout << "Вы ничего не ввели!\n";

        search();

    }
    else {

        for (const auto &file: fs::directory_iterator(folder_paths)) {
            if (file.is_regular_file() && file.path().extension() == ".csv") {
                std::ifstream input(file.path());
                std::string line;
                int line_number = 1;

                input.clear();
                input.seekg(0);


                while (std::getline(input, line)) {
                    //cout <<"строка файла"<< line << endl;
                    //cout <<"переменная"<< login_temp << endl;
                    //cout << (line.find(login_temp) != std::string::npos);
                    //cout << (line.find(mail_temp) != std::string::npos);
                    //cout << (line.find(phone_temp) != std::string::npos);
                    if (line.find(login_temp) != std::string::npos && line.find(mail_temp) != std::string::npos &&
                        line.find(phone_temp) != std::string::npos) {
                        std::cout << "Данные найдены в файле " << file.path() << ", строка " << line_number << ": "
                                  << line << std::endl;

                    }
                    line_number++;
                }
                input.close();
            }
        }
    }
}
void remove_folder() {
    string path_folder_for_txt = "C:\\Users\\Artem\\db\\db_"; //поменять на вашу
    string new_file_full_path = path_folder_for_txt + "\\" + "folders.txt";//это тоже
    string file_name = "folders.txt";//и это
    string full_path = path_folder_for_txt + "\\" + file_name;
    string tmp_path = path_folder_for_txt + "\\temporary.tmp";//и это

    std::ifstream input_file(full_path);

    if (!input_file.is_open()) {
        std::cerr << "Не удалось открыть файл!\n" << full_path << std::endl;
        managment();
    }

    std::string search_string;
    std::cout << "Введите путь до папки в формате path/to/folder для удаления: \n";
    cin >> search_string;

    std::string line;
    std::ofstream output_file(tmp_path);

    while (std::getline(input_file, line)) {
        if (line != search_string) {
            output_file << line << std::endl;
        }
    }
    input_file.close();
    output_file.close();
    if (std::remove(full_path.c_str()) != 0) {
        cout << "Не удалось удалить файл!\n" << full_path;
        managment();
    }
    if (std::rename(tmp_path.c_str(), full_path.c_str()) != 0) {
        cout << "Не удалось переименовать файл!\n";
        managment();
    }
    std::cout << "Путь успешно удален!\n";

    managment();
}
void add_folder(string folder_path) {
    string path_folder_for_txt = "C:\\Users\\Artem\\db\\db_"; // поменять на вашу
    string file_name = "folders.txt"; //и это тоже
    string full_path = path_folder_for_txt + "\\" + file_name;
    ofstream outfile(full_path, ios::app);
    if (!outfile) {
        cout << "Ошибка добавления! Попробуйте снова.\n";
        managment();
    }
    outfile << folder_path << endl;
    outfile.close();
}
void show_files(string folder_path) {

    for (const auto& entry : fs::directory_iterator(folder_path))
        cout << entry.path() << endl;
}
void check_path(string folder_path) {
    while (true) {
        if (!filesystem::exists(folder_path)) {
            cout << "Папка не найдена! Повторите попытку.\n" << endl;
            cin >> folder_path;
            continue;

        }
        else {
            cout << "Папка найдена и успешно добавлена!\nСодержимое папки:\n";
            show_files(folder_path); //содержимое папки
            add_folder(folder_path);// добавить в файл путь
            managment();
            cout << "\n";
            break;
        }
    }
}
void vibor(string choose) {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Управление данными [1] \nРабота с поиском [2]\nВыход [3]\n";
    cin >> choose;
    while (true) {
        if (choose == "1") {
            managment();
            break;
        }
        else if (choose == "2") {
            search();
            break;
        }
        else if (choose == "3") {
            end();
            break;
        }
        else {
            cout << "Введите корректное значение!\n";
            cin >> choose;
            continue;
        }
    }

};
void managment() {
    string folder_path;
    cout << "Добавить информацию о папке данных [1]\nУдалить информацию о папке [2]\nПросмотреть сохраненные пути [3]\nНазад [4]\n";
    string choose;
    cin >> choose;
    while (true) {
        if (choose == "1") {
            cout << "Введите путь вашей папки в формате path/to/folder\n";
            cin >> folder_path;
            check_path(folder_path);
            break;
        }
        else if (choose == "2") {
            remove_folder();
            break;
        }
        else if (choose == "3") {
            cout << "Ваши пути:\n";
            std::ifstream f("C:\\Users\\Artem\\db\\db_\\folders.txt"); //поменять на вашу

            if (f.is_open()) {
                if (f.peek() != std::ifstream::traits_type::eof()) {
                    // файл не пустой
                    std::cout << f.rdbuf();
                }
                else {
                    // файл пустой
                    std::cout << "Пути не добавлены!" << std::endl;
                }
                f.close();
            }
            else {
                // не удалось открыть файл
                std::cout << "Не удалось открыть файл." << std::endl;
            }
            cout << "\n";
            managment();

            f.close();
            break;
        }
        else if (choose == "4") {
            vibor(choose);
        }
        else {
            cout << "Введите корректное значение!\n";
            cin >> choose;
            continue;
        }
    }


}
void search() {

    const fs::path file_path = "C:\\Users\\Artem\\db\\db_\\folders.txt"; //поменять на вашу
    ifstream input(file_path);
    string folder_path_str;

    cout << "Указать искомый логин[1]\nУказать искомую почту[2]\nУказать искомый номер телефона[3]\nОсуществить поиск по всей базе[4]\n"
            "Очистить введенные данные[5]\nНазад[6]\n";
    string choose;
    cin >> choose;
    while (true) {
        if (choose == "1") {
            cout << "Введите ФИО для поиска в формате ИвановИванИванович:\n";
            cin.ignore();
            //wcin >> login;
            while (true) {
                std::getline(std::wcin, login);
                if (isNameValid(login)) {
                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    login_str = converter.to_bytes(login);
                    break;
                }
                cout << "Некорректный ввод! Попробуйте еще раз.\n";
            }

            wcout << "Логин успешно введен!\n";
            input.close();
            search();
            break;
        }
        else if (choose == "2") {
            regex pattern("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
            cout << "Введите почту для поиска в формате example@test.ru:\n";
            while (true) {
                cin >> mail;
                if (std::regex_match(mail, pattern)) {
                    std::cout << "Почта успешно введена!\n";
                    break;
                }
                else {
                    std::cout << "Некорректная почта!\n";
                }
            }
            input.close();
            search();
            break;
        }
        else if (choose == "3") {
            regex pattern("7[0-9]{10}");
            cout << "Введите номер телефона для поиска в формате 71234567890:\n";
            while (true) {
                cin >> phone;
                if (std::regex_match(phone, pattern)) {
                    std::cout << "Номер телефона успешно введен!\n";
                    break;
                }
                else {
                    std::cout << "Некорректный номер!\n";
                }
            }
            input.close();
            search();
            break;
        }
        else if (choose == "4") {
            count_files();
            percent();

            while (std::getline(input, folder_path_str)) { // читаем файл построчно
                const fs::path folder_paths(folder_path_str);

                search_login(login_str, mail, phone, folder_paths);// передаем логин и путь к папке в функцию поиска
            }
            input.close();
            search();
            break;
        }
        else if (choose == "5") {
            login_str = "", mail = "", phone = "";
            cout << "Данные очищены!\n";
            input.close();
            search();
            break;
        }
        else if (choose == "6") {
            input.close();
            vibor(choose);
            break;
        }
        else {
            cout << "Введите корректное значение!\n";
            cin >> choose;
            continue;
        }
    }input.close();
}
int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string choose;
    vibor(choose);

    return 0;
}
