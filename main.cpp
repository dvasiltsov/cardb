#include <iostream>
#include <unordered_map>
using namespace std;

class Car
{
    public:
    int id;
    int year;
    std::string name;
    double price;
    Car(){}

    Car(int id, const std::string& name, int year, double price) 
        : id(id), name(name), year(year), price(price) {}

    void print() const
    {
        std::cout<<id<<" "<<name<<" "<<year<<" "<<price<<std::endl; 
    }
};

class CarDatabase {
private:
    std::unordered_map<int, Car> idIndex;
    std::unordered_multimap<std::string, int> nameIndex;  
    std::unordered_map<int, int> yearIndex;  

public:
    void addCar(int id, const std::string& name, int year, double price) {
        idIndex.emplace(id, Car(id, name, year, price));
        nameIndex.emplace(name, id);
        yearIndex.emplace(year, id);
    }

   
    void searchByName(const std::string& name) {
        auto range = nameIndex.equal_range(name);
        if (range.first == range.second) {
            std::cout << "No cars found with the name: " << name << std::endl;
        } else {
            std::cout << "Cars found with the name " << name << ":\n";
            for (auto it = range.first; it != range.second; ++it) {
                const Car& car = idIndex[it->second];
                car.print();
            }
        }
    }

   
    void searchByYear(int year) {
        
        auto it = yearIndex.find(year);
        if (it == yearIndex.end()) {
            std::cout << "No cars found from the year: " << year << std::endl;
        } else {
            const Car& car = idIndex[it->second];
            std::cout << "Car found from the year " << year << ":\n";
            car.print();
        }
    }
};

int main() {
    CarDatabase db;

    // Додаємо кілька машин
    db.addCar(1, "Toyota", 2020, 30000);
    db.addCar(2, "Honda", 2021, 25000);
    db.addCar(3, "Ford", 2019, 27000);
    db.addCar(4, "Toyota", 2024, 37000);
    // Пошук за назвою
    db.searchByName("Toyota");

    std::cout << std::endl;

    // Пошук за роком
    db.searchByYear(2021);

    return 0;
}