#include <cstdint>
#include <string>
#include <string.h>
// Структура Client
struct Client {
    uint32_t ID;
    char Name[256];
    char Surname[256];
    char DeliveryAddress[256];
    char Password[256];
};

// Типы товаров (предположим, что это электроника)
enum ItemType {
    Smartphone,
    Laptop,
    Television,
    Tablet,
};

// Функция для получения имени элемента перечисления ItemType в виде строки
std::string itemTypeToString(ItemType type) {
    switch (type) {
        case ItemType::Smartphone:
            return "Smartphone";
        case ItemType::Laptop:
            return "Laptop";
        case ItemType::Television:
            return "Television";
        case ItemType::Tablet:
            return "Tablet";
        default:
            return "Unknown";
    }
}

// Структура Item
struct Item {
    uint32_t ID;
    ItemType Type;
    float Price;
    char Model[256];
    Item(uint32_t id, ItemType type, float price, const char *model):
        ID(id), Type(type), Price(price) {
        strncpy(Model, model, sizeof(Model) - 1);
        Model[sizeof(Model) - 1] = '\0';
    }
    Item(){};
};

// Структура Order Item
struct OrderItem {
    uint32_t ItemID;
    uint32_t Amount;
    float TotalPrice;
    uint32_t NextID; // ID следующего элемента OrderItem
};

// Типы оплаты
enum PaymentType {
    Cash,
    CreditCard,
    PayPal,
};

// Структура Order
struct Order {
    uint32_t ID;
    char Date[20];
    uint32_t ClientID;
    float TotalPrice;
    PaymentType PaymentType;
    uint32_t FirstOrderItemID; // ID первого элемента OrderItem
};
// Уровни пользователей
enum class UserRole {
    Client,
    Admin,
};