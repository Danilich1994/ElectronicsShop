#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#define TABLE_PAGE_AMOUNT 5

#include "structs.h"

std::vector<Item> items_db;
std::vector<Order> order_db;
std::vector<OrderItem> order_item_db;

MenuScreen CreateOrderScreen;
MenuScreen AddItemToOrderScreen;
MenuScreen SearchItemScreen;

#include "screens.h"


// MenuScreen navigateMenu(const MenuScreen &currentMenu, UserRole userRole, uint32_t &elementIndex) {
//     for (size_t i = 0; i < currentMenu.ActionOptions.size(); i++) {
//         std::cout << (i + 1) << ". " << currentMenu.ActionOptions[i] << std::endl;
//     }

//     uint32_t userChoice;
//     std::cin >> userChoice;

//     if (userChoice > 0 && userChoice <= currentMenu.ActionOptions.size()) {
//         const std::string &action = currentMenu.ActionOptions[userChoice - 1];

//         if (action == "Next Page") {
//             elementIndex += 10;
//         } else if (action == "Previous Page") {
//             if (elementIndex >= 10) {
//                 elementIndex -= 10;
//             }
//         } else {
//             // Здесь можно добавить обработку других действий
//         }
//     }

//     // Возвращаем обновленную копию текущего меню
//     return MenuScreen(currentMenu.ActionOptions, elementIndex);
// }


// Функция сохранения вектора структур Item в бинарный файл
template<typename T>
void saveToFile(const std::vector<T> &items, const std::string &filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        for (const T &item : items) {
            outFile.write(reinterpret_cast<const char *>(&item), sizeof(T));
        }
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

template<typename T>
std::vector<T> loadFromFile(const std::string &filename) {
    std::vector<T> items;
    std::ifstream inFile(filename, std::ios::binary);
    if (inFile.is_open()) {
        T item;
        while (inFile.read(reinterpret_cast<char *>(&item), sizeof(T))) {
            items.push_back(item);
        }
        inFile.close();
    } else {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
    }
    return items;
}


int main() {
    
    // Сохранение заказов и элементов заказа в файлы
    //saveToFile<Order>(orders, "orders.bin");

    // Загрузка заказов и элементов заказа из файлов
    //std::vector<Order> loadedOrders = loadFromFile<Order>("orders.bin");

    // ... остальной код программы ...

    CreateOrderScreen.Name = "Create New Order";
    CreateOrderScreen.Actions = {"Add Item", "Delete Item", "Confirm Order", "Next Page", "Previous Page", "Cancel Order"};
    CreateOrderScreen.TableName = "Ordered Items";
    CreateOrderScreen.ElementIndex = 0;

    AddItemToOrderScreen.Name = "Add Item To Order";
    AddItemToOrderScreen.Actions = {"Search for Item", "Add Item", "Change Amount", "Cancel"};
    AddItemToOrderScreen.TableName = "";
    AddItemToOrderScreen.ElementIndex = 0;

    SearchItemScreen.Name = "Item Search";
    SearchItemScreen.Actions = {"Choose Item", "Search by Type", "Search by Model", "Filter by Price", "Next Page", "Previous Page", "Cancel"};
    SearchItemScreen.TableName = "Found Items";
    SearchItemScreen.ElementIndex = 0;


    items_db = loadFromFile<Item>( "items.bin" );
    order_db = loadFromFile<Order>( "orders.bin" );
    order_item_db = loadFromFile<OrderItem>( "item_orders.bin" );

    displayOrderTable(order_db);

    if (order_db.size() != 0) {
        std::cout << "There are " << order_db.size() << " orders in DB" << std::endl;
        displayOrderItemTable(order_db[0]);
    }

    Order newOrder = createOrder(CreateOrderScreen);
    if (newOrder.FirstOrderItemID == 0) {
        std::cout << "Order creation was cancelled." << std::endl;
    } else {
        order_db.push_back(newOrder);
        std::cout << "New order created successfully!" << std::endl;
    }

    if (order_db.size() != 0) {
        std::cout << "There are " << order_db.size() << " orders in DB" << std::endl;
        std::cout << "First order 'FirstItemId' = " << order_db[0].FirstOrderItemID << std::endl;
    }
    saveToFile<Order>(order_db, "orders.bin");
    saveToFile<OrderItem>(order_item_db, "item_orders.bin");
    return 0;
}