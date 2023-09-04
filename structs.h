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
    UnknownItem,
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
    Item(): ID(0), Type(ItemType::UnknownItem), Price(0) {Model[0] = '\0';};
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
    uint32_t ID;
    uint32_t ItemID;
    uint32_t Amount;
    float TotalPrice;
    uint32_t NextOrderItemID;
    OrderItem(uint32_t id, uint32_t itemId, uint32_t amount, float price):
        ID(id), ItemID(itemId), Amount(amount), TotalPrice(price){};
    OrderItem(): ID(0), ItemID(0), Amount(0), TotalPrice(0), NextOrderItemID(0) {};
};

OrderItem searchOrderItemByID(const std::vector<OrderItem>& items, uint32_t itemID) {

    for (const auto& item : items) {
        if (item.ID == itemID) {
            return item;
        }
    }

    // If itemID is not found, return a -1
    return OrderItem();
}

void setNextOrderItemID(std::vector<OrderItem>& items, uint32_t firstItemID, uint32_t nextItemID) {
    
    uint32_t index = 0;
    uint32_t currentID = firstItemID;
    std::cout << "\nDEBUG::First OrderItem ID in chain: " << currentID << std::endl;
    while (index < items.size()) {
        if (items[index].ID == currentID){
            if (items[index].NextOrderItemID != 0){
                currentID = items[index].NextOrderItemID;
                index = 0;
                std::cout << "\nDEBUG::Next OrderItem ID in chain: " << currentID << std::endl;
            } else {
                items[index].NextOrderItemID = nextItemID;
                break;
            }
        } else index ++;
    }

    // If itemID is not found, return a default-constructed Item
    if (index == items.size()) {
        std::cout << "\nDEBUG::Unable to find an OrderItem with ID: " << firstItemID << std::endl;
    }
}

// Типы оплаты
enum PaymentType {
    Cash,
    CreditCard,
    PayPal,
    UnknownPayment,
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
    char Date[11];
    uint32_t ClientID;
    float TotalPrice;
    PaymentType PayType;
    uint32_t FirstOrderItemID;

    Order(): ID(0), ClientID(0), TotalPrice(0), PayType(PaymentType::UnknownPayment), FirstOrderItemID(0) { Date[0] = '\0';};
};

// Уровни пользователей
enum UserRole {
    ClientUser,
    AdminUser
};

struct MenuScreen {
    std::string Name;
    std::vector<std::string> Actions;
    std::string TableName;
    uint32_t ElementIndex;
};