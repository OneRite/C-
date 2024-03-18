
//Задача №2
//“Первый класс”
//Создайте класс, описывающий указанный в вашем варианте реальный объект.
//Не забывайте про принципы абстракции и инкапсуляции.
//Продемонстрируйте использование вашего класса.
//Треугольник, расчет площади, периметра.
#include <iostream>
#include <cmath>

class Triangle 
{
    float side1;
    float side2;
    float side3;
public:
    // Конструктор по умолчанию с параметрами по умолчанию
    Triangle(float a = 1, float b = 1, float c = 1) : side1(a), side2(b), side3(c) {}

    float calculateP() 
    {
        return side1 + side2 + side3;
    }

    float calculateS() 
    {
        // Полупериметр
        float s = calculateP() / 2;
        // Площадь по формуле Герона
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    // Создаем объект треугольника с конструктором по умолчанию
    Triangle t;

    // Рассчитываем P и S треугольника
    float P = t.calculateP();
    float S = t.calculateS();

    // Вывод результата
    std::cout << "Периметр треугольника: " << P << std::endl;
    std::cout << "Площадь треугольника: " << S << std::endl;

    return 0;
}

