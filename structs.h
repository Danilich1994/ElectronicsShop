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
    Unknown,
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
    Item(){Model[0] = '\0';};
};

Item searchItemByID(const std::vector<Item>& items, uint32_t itemID) {
    for (const auto& item : items) {
        if (item.ID == itemID) {
            return item;
        }
    }
    // If itemID is not found, return a default-constructed Item
    return Item();
}

// Структура Order Item
struct OrderItem {
    uint32_t ItemID;
    uint32_t Amount;
    float TotalPrice;
    OrderItem(uint32_t id, uint32_t amount, float price):
        ItemID(id), Amount(amount), TotalPrice(price){};
    OrderItem(){};
};

// Типы оплаты
enum PaymentType {
    Cash,
    CreditCard,
    PayPal,
};

std::string paymentTypeToString(PaymentType type) {
    switch (type) {
        case PaymentType::Cash:
            return "Cash";
        case PaymentType::CreditCard:
            return "CreditCard";
        case PaymentType::PayPal:
            return "PayPal";
        default:
            return "Unknown";
    }
}

// Структура Order
struct Order {
    uint32_t ID;
    std::string Date;
    uint32_t ClientID;
    float TotalPrice;
    PaymentType PaymentType;
    std::vector<OrderItem> Items;
};

// Уровни пользователей
enum UserRole {
    ClientUser,
    AdminUser,
};

struct MenuScreen {
    std::string Name;
    std::vector<std::string> Actions;
    std::string TableName;
    uint32_t ElementIndex;
};