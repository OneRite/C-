
#pragma once
#include <iostream>

class String {
private:
    char* str; // Указатель на строку
    int length; // Длина строки

public:
    // Конструктор по умолчанию
    String();

    // Конструктор копирования
    String(const String& other);

    // Деструктор
    ~String();

    // Метод для установки значения строки
    void setString(const char* s);

    // Метод для получения значения строки
    const char* getString() const;

    // Перегрузка оператора присваивания
    String& operator=(const String& other);
};

