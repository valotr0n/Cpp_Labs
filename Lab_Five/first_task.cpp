#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <windows.h>
using namespace std;

string readText(const string& prompt, bool allowEmpty = false) {
    string value;
    while (true) {
        cout << prompt;
        if (!getline(cin, value)) throw runtime_error("Ввод завершён.");
        if (allowEmpty || value.find_first_not_of(" \t\r") != string::npos) return value;
        cout << "Строка не должна быть пустой.\n";
    }
}

int readInt(const string& prompt, int minimum, int maximum) {
    while (true) {
        istringstream input(readText(prompt));
        int value;
        char extra;
        if (input >> value && value >= minimum && value <= maximum && !(input >> extra))
            return value;
        cout << "Введите целое число от " << minimum << " до " << maximum << ".\n";
    }
}

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[2] != '.' || date[5] != '.') return false;
    for (size_t i = 0; i < date.size(); ++i) {
        if (i != 2 && i != 5 && (date[i] < '0' || date[i] > '9')) return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (year == 0 || month < 1 || month > 12) return false;
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) days[1] = 29;
    return day >= 1 && day <= days[month - 1];
}

string readDate(const string& prompt) {
    while (true) {
        string date = readText(prompt);
        if (isValidDate(date)) return date;
        cout << "Введите существующую дату в формате ДД.ММ.ГГГГ.\n";
    }
}

class Patient {
private:
    string date;
    string fullName;
    string group;
    string reason;
    bool referred;
    string note;

public:
    Patient() : referred(false) {}

    Patient(const string& date, const string& fullName, const string& group,
            const string& reason, bool referred, const string& note)
        : date(date), fullName(fullName), group(group), reason(reason),
          referred(referred), note(note) {}

    Patient(const Patient& other)
        : date(other.date), fullName(other.fullName), group(other.group),
          reason(other.reason), referred(other.referred), note(other.note) {}

    string getDate() const { return date; }
    string getFullName() const { return fullName; }
    string getGroup() const { return group; }
    string getReason() const { return reason; }
    bool getReferred() const { return referred; }
    string getNote() const { return note; }

    void setDate(const string& value) { date = value; }
    void setFullName(const string& value) { fullName = value; }
    void setGroup(const string& value) { group = value; }
    void setReason(const string& value) { reason = value; }
    void setReferred(bool value) { referred = value; }
    void setNote(const string& value) { note = value; }

    void input() {
        setDate(readDate("Дата обращения (ДД.ММ.ГГГГ): "));
        setFullName(readText("Ф.И.О. пациента: "));
        setGroup(readText("Группа (кафедра, отдел): "));
        setReason(readText("Причина обращения: "));
        setReferred(readInt("Результат (0 - оказана помощь, 1 - направлен в другое учреждение): ", 0, 1) == 1);
        setNote(readText("Примечание (можно оставить пустым): ", true));
    }

    void print() const {
        cout << "Дата: " << date << "\nФ.И.О.: " << fullName
             << "\nГруппа (кафедра, отдел): " << group
             << "\nПричина обращения: " << reason
             << "\nРезультат: " << (referred ? "направлен в другое лечебное учреждение" : "оказана помощь")
             << "\nПримечание: " << (note.empty() ? "нет" : note) << "\n\n";
    }
};

void fillPatients(vector<Patient>& patients, int count) {
    patients.clear();
    for (int i = 0; i < count; ++i) {
        cout << "\nПациент №" << i + 1 << '\n';
        Patient patient;
        patient.input();
        patients.push_back(patient); 
    }
}

void printPatients(const vector<Patient>& patients) {
    cout << "\nВсе записи о пациентах:\n";
    if (patients.empty()) cout << "Список пуст.\n";
    for (const Patient& patient : patients) patient.print();
}

void printByDate(const vector<Patient>& patients, const string& date) {
    cout << "\nПациенты, обратившиеся " << date << ":\n";
    bool found = false;
    for (const Patient& patient : patients) {
        if (patient.getDate() == date) {
            patient.print();
            found = true;
        }
    }
    if (!found) cout << "Пациентов на эту дату нет.\n";
}

void printReferred(const vector<Patient>& patients) {
    cout << "\nПациенты, направленные в другое лечебное учреждение:\n";
    bool found = false;
    for (const Patient& patient : patients) {
        if (patient.getReferred()) {
            patient.print();
            found = true;
        }
    }
    if (!found) cout << "Таких пациентов нет.\n";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        int count = readInt("Количество записей о пациентах: ", 0, 100000);
        vector<Patient> patients;
        fillPatients(patients, count);
        printPatients(patients);

        string date = readDate("\nВведите дату для поиска (ДД.ММ.ГГГГ): ");
        printByDate(patients, date);
        printReferred(patients);
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
