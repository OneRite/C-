
// func.cpp

#include <iostream>
#include "func.hpp"
#include <fstream>
#include <chrono>
#include <ctime>

namespace rs 
{
    void TimeFile(const std::string& filename) 
    {
        std::ofstream file(filename, std::ios::app); // Открываем файл для добавления информации в конец
        if (!file.is_open()) 
        {
            std::cout << "Error.Not file" << std::endl; // Обработка ошибки открытия файла
            return;
        }
        
        // Получаем текущее системное время
        auto now = std::chrono::system_clock::now(); 
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        // Преобразуем время в строку в нужном формате
        std::tm* ptm = std::localtime(&now_c);
        char buffer[32]; // мы создаем массив символов(строку) с размером 32 символа, который будет 
                         // использоваться для сохранения преобразованной строки времени.
        std::strftime(buffer, 32, "%Y-%m-%d-%H-%M-%S", ptm);

        // Получаем порядковый номер запуска программы
        int number = 0;
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line))
            ++number;

        // Добавляем информацию в файл
        file << number << "-" << buffer << std::endl;

        // Закрываем файл
        file.close();
    }
}
