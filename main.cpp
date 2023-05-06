#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>


#include "structs.h"


// Структура MenuScreen
struct MenuScreen {
    std::vector<std::string> ActionOptions;
    uint32_t ElementIndex;

    MenuScreen(std::vector<std::string> actionOptions, uint32_t elementIndex)
        : ActionOptions(std::move(actionOptions)), ElementIndex(elementIndex) {}
};
void displayItems(const std::vector<Item> &items, uint32_t startIndex, uint32_t itemsPerPage) {
    uint32_t endIndex = std::min(startIndex + itemsPerPage, static_cast<uint32_t>(items.size()));

    for (uint32_t i = startIndex; i < endIndex; i++) {
        const Item &item = items[i];
        std::cout << "Item ID: " << item.ID << ", Model: " << item.Model << ", Price: $" << item.Price << std::endl;
    }
}

MenuScreen navigateMenu(const MenuScreen &currentMenu, UserRole userRole, uint32_t &elementIndex) {
    for (size_t i = 0; i < currentMenu.ActionOptions.size(); i++) {
        std::cout << (i + 1) << ". " << currentMenu.ActionOptions[i] << std::endl;
    }

    uint32_t userChoice;
    std::cin >> userChoice;

    if (userChoice > 0 && userChoice <= currentMenu.ActionOptions.size()) {
        const std::string &action = currentMenu.ActionOptions[userChoice - 1];

        if (action == "Next Page") {
            elementIndex += 10;
        } else if (action == "Previous Page") {
            if (elementIndex >= 10) {
                elementIndex -= 10;
            }
        } else {
            // Здесь можно добавить обработку других действий
        }
    }

    // Возвращаем обновленную копию текущего меню
    return MenuScreen(currentMenu.ActionOptions, elementIndex);
}


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

void displayItemsTable(const std::vector<Item> &items, uint32_t startIndex = 0) {
    const uint32_t itemsPerPage = 5;
    uint32_t endIndex = std::min(startIndex + itemsPerPage, static_cast<uint32_t>(items.size()));

    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(15) << "Type"
              << std::setw(25) << "Model"
              << std::setw(10) << "Price" << std::endl;
    std::cout << std::setfill('=') << std::setw(55) << "" << std::setfill(' ') << std::endl;

    for (uint32_t i = startIndex; i < endIndex; i++) {
        const Item &item = items[i];
        std::cout << std::left << std::setw(5) << item.ID
                  << std::setw(15) << itemTypeToString(item.Type)
                  << std::setw(25) << item.Model
                  << std::setw(10) << item.Price << std::endl;
    }
}

void linkOrdersWithOrderItems(std::vector<Order> &orders, const std::vector<OrderItem> &orderItems) {
    for (auto &order : orders) {
        uint32_t currentOrderItemID = order.FirstOrderItemID;
        while (currentOrderItemID != 0) {
            // Найти элемент OrderItem с текущим ID
            auto orderItemIt = std::find_if(orderItems.begin(), orderItems.end(),
                                            [currentOrderItemID](const OrderItem &item) {
                                                return item.ItemID == currentOrderItemID;
                                            });

            if (orderItemIt != orderItems.end()) {
                // Обработка OrderItem (если нужно)
                // ...
                
                // Переход к следующему элементу
                currentOrderItemID = orderItemIt->NextID;
            } else {
                std::cerr << "Error: OrderItem with ID " << currentOrderItem
                currentOrderItemID = 0;
            }
        }
    }
}


int main() {
    
    std::vector<Order> orders = {
        // ... примеры заказов ...
    };

    std::vector<OrderItem> orderItems = {
        // ... примеры элементов заказа ...
    };

    // Сохранение заказов и элементов заказа в файлы
    saveToFile<Order>(orders, "orders.bin");
    saveToFile<OrderItem>(orderItems, "order_items.bin");

    // Загрузка заказов и элементов заказа из файлов
    std::vector<Order> loadedOrders = loadFromFile<Order>("orders.bin");
    std::vector<OrderItem> loadedOrderItems = loadFromFile<OrderItem>("order_items.bin");

    // Восстановление взаимосвязей между заказами и элементами заказа
    linkOrdersWithOrderItems(loadedOrders, loadedOrderItems);

    // ... остальной код программы ...

    std::vector<Item> readed_items = loadFromFile<Item>( "items.bin" );

    displayItemsTable( readed_items );
    std::cin.get();
    displayItemsTable( readed_items, 5 );
    return 0;
}