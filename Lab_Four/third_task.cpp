#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <windows.h>
using namespace std;

int readInt(const string& prompt, int minimum, int maximum) {
    string line;
    int value;
    char extra;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) throw runtime_error("Ввод завершён.");
        istringstream input(line);
        if (input >> value && value >= minimum && value <= maximum && !(input >> extra))
            return value;
        cout << "Введите целое число от " << minimum << " до " << maximum << ".\n";
    }
}

string readFilename() {
    string filename;
    cout << "Имя бинарного файла (с расширением .txt по методичке): ";
    if (!getline(cin, filename)) throw runtime_error("Ввод завершён.");
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt")
        throw runtime_error("Файл должен иметь расширение .txt.");
    return filename;
}

struct Student {
    char surname[100];
    int group;
    int grades[3]; 
};

class Session {
    vector<Student> students;

    bool isValid(const Student& student) const {
        if (!memchr(student.surname, '\0', sizeof(student.surname))
            || student.surname[0] == '\0' || student.group <= 0) return false;
        for (int grade : student.grades)
            if (grade < 2 || grade > 5) return false;
        return true;
    }

    void printStudent(const Student& student, size_t number) const {
        cout << number << ". " << student.surname << ", группа " << student.group
             << ", оценки: " << student.grades[0] << ' ' << student.grades[1]
             << ' ' << student.grades[2] << '\n';
    }

public:
    void add() {
        Student student = {};
        string surname;
        while (true) {
            cout << "Фамилия: ";
            if (!getline(cin, surname)) throw runtime_error("Ввод завершён.");
            if (!surname.empty() && surname.size() < sizeof(student.surname)) break;
            cout << "Введите непустую фамилию короче 100 байт.\n";
        }
        strcpy(student.surname, surname.c_str());
        student.group = readInt("Номер группы: ", 1, 1000000);
        student.grades[0] = readInt("Геометрия (2..5): ", 2, 5);
        student.grades[1] = readInt("Алгебра (2..5): ", 2, 5);
        student.grades[2] = readInt("Информатика (2..5): ", 2, 5);
        students.push_back(student);
        cout << "Студент добавлен.\n";
    }

    void remove(int number) {
        if (number < 1 || static_cast<size_t>(number) > students.size())
            throw runtime_error("Студента с таким номером нет.");
        students.erase(students.begin() + number - 1);
        cout << "Студент удалён.\n";
    }

    void print() const {
        if (students.empty()) cout << "Список пуст.\n";
        for (size_t i = 0; i < students.size(); ++i) printStudent(students[i], i + 1);
    }

    void save(const string& filename) const {
        ofstream output;
        output.exceptions(ios::failbit | ios::badbit);
        output.open(filename, ios::binary);
        for (const Student& student : students)
            output.write(reinterpret_cast<const char*>(&student), sizeof(student));
        output.close();
        cout << "Данные сохранены.\n";
    }

    void load(const string& filename) {
        ifstream input(filename, ios::binary);
        if (!input) throw runtime_error("Файл не существует или недоступен для чтения.");
        input.exceptions(ios::badbit);
        vector<Student> loaded;
        Student student;
        while (input.read(reinterpret_cast<char*>(&student), sizeof(student))) {
            if (!isValid(student)) throw runtime_error("В файле некорректная запись.");
            loaded.push_back(student);
        }
        if (!input.eof() || input.gcount() != 0)
            throw runtime_error("Файл повреждён: неполная запись.");
        students = loaded;
        cout << "Загружено студентов: " << students.size() << '\n';
    }

    void readRecord(const string& filename, int number) const {
        ifstream input(filename, ios::binary);
        if (!input) throw runtime_error("Файл не существует или недоступен для чтения.");
        input.exceptions(ios::badbit);
        input.seekg(static_cast<streamoff>(number - 1) * sizeof(Student));
        Student student;
        if (!input.read(reinterpret_cast<char*>(&student), sizeof(student)))
            throw runtime_error("Запись с таким номером отсутствует или файл повреждён.");
        if (!isValid(student)) throw runtime_error("В файле некорректная запись.");
        printStudent(student, number);
    }

    void report() const {
        if (students.empty()) {
            cout << "Список пуст.\n";
            return;
        }

        int qualityCount = 0;
        int subjectSums[3] = {};
        bool hasDebts = false;
        cout << "Студенты с задолженностями (оценка 2):\n";
        for (const Student& student : students) {
            bool debt = false, quality = true;
            for (int j = 0; j < 3; ++j) {
                subjectSums[j] += student.grades[j];
                if (student.grades[j] == 2) debt = true;
                if (student.grades[j] < 4) quality = false;
            }
            if (debt) {
                cout << student.surname << '\n';
                hasDebts = true;
            }
            if (quality) ++qualityCount;
        }
        if (!hasDebts) cout << "Нет.\n";
        cout << fixed << setprecision(2);
        cout << "Качество успеваемости (все оценки 4 и 5): "
             << 100.0 * qualityCount / students.size() << "%\n";

        int best = subjectSums[0];
        for (int j = 1; j < 3; ++j)
            if (subjectSums[j] > best) best = subjectSums[j];
        const char* subjects[3] = {"Геометрия", "Алгебра", "Информатика"};
        cout << "Лучше всего сданы (по средней оценке):\n";
        for (int j = 0; j < 3; ++j)
            if (subjectSums[j] == best)
                cout << subjects[j] << ": " << 1.0 * best / students.size() << '\n';

        struct Group {
            int number;
            double sum;
            int count;
        };
        vector<Group> groups;
        for (const Student& student : students) {
            size_t i = 0;
            while (i < groups.size() && groups[i].number != student.group) ++i;
            if (i == groups.size()) groups.push_back({student.group, 0, 0});
            for (int grade : student.grades) groups[i].sum += grade;
            groups[i].count += 3;
        }
        for (size_t i = 0; i < groups.size(); ++i) {
            for (size_t j = i + 1; j < groups.size(); ++j) {
                if (groups[j].sum / groups[j].count > groups[i].sum / groups[i].count) {
                    Group temp = groups[i];
                    groups[i] = groups[j];
                    groups[j] = temp;
                }
            }
        }
        cout << "Группы по убыванию средней успеваемости:\n";
        for (const Group& group : groups)
            cout << group.number << ": " << group.sum / group.count << '\n';
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Session session;
    try {
        while (true) {
            cout << "\n1 - добавить, 2 - удалить, 3 - показать список,\n"
                 << "4 - сохранить, 5 - загрузить (заменить список),\n"
                 << "6 - прочитать запись из файла по номеру, 7 - результаты сессии, 0 - выход.\n";
            int choice = readInt("Выбор: ", 0, 7);
            if (choice == 0) break;
            if (choice == 1) session.add();
            if (choice == 2) session.remove(readInt("Номер студента: ", 1, 1000000));
            if (choice == 3) session.print();
            if (choice == 4) session.save(readFilename());
            if (choice == 5) session.load(readFilename());
            if (choice == 6) {
                string filename = readFilename();
                int number = readInt("Номер записи: ", 1, 1000000);
                session.readRecord(filename, number);
            }
            if (choice == 7) session.report();
        }
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
