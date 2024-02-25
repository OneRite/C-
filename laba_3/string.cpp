
#include "string.hpp"
#include <cstring>

// Конструктор по умолчанию
String::String() {
    str = nullptr;
    length = 0;
}

// Конструктор копирования
String::String(const String& other) {
    length = other.length;
    str = new char[length + 1]; // Выделение памяти для строки
    strcpy(str, other.str); // Копирование строки
}

// Деструктор
String::~String() {
    delete[] str; // Освобождение выделенной памяти
}

// Метод для установки значения строки
void String::setString(const char* s) {
    if (str != nullptr) // Освобождение старой памяти, если она была выделена
        delete[] str;
    length = strlen(s);
    str = new char[length + 1]; // Выделение памяти для новой строки
    strcpy(str, s); // Копирование строки
}

// Метод для получения значения строки
const char* String::getString() const {
    return str;
}

// Перегрузка оператора присваивания
String& String::operator=(const String& other) {
    if (this != &other) { // Проверка на самоприсваивание
        delete[] str; // Освобождение текущей памяти
        length = other.length;
        str = new char[length + 1]; // Выделение новой памяти
        strcpy(str, other.str); // Копирование строки
    }
    return *this;
}

