#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdint>

//#include "structs.h"

bool isNumber(std::string input){
    bool isNumber = true;
    for (char c : input) {
        if (!std::isdigit(c)) {
            isNumber = false;
            break;
        }
    }
    return isNumber;
}

void nextPage(int32_t& index){
    index = index + TABLE_PAGE_AMOUNT;
}

void previousPage(int32_t& index){
    index = index - TABLE_PAGE_AMOUNT;
    if (index < 0) index = 0;
}

float getOrderTotalPrice(const std::vector<OrderItem>& orderItems){
    float totalPrice = 0;
    for (const auto& item : orderItems) {
        totalPrice = totalPrice + item.TotalPrice;
    }
    return totalPrice;
}

void printActions(const MenuScreen& screen) {
    std::cout << "\n" << screen.Name << "\n\n";
    std::cout << "Select an action:\n";
    for (size_t i = 0; i < screen.Actions.size(); i++) {
        std::cout << "[" << i + 1 << "] " << screen.Actions[i] << "\n";
    }
}

void displayClientTable(const std::vector<Client>& clients, int startIndex = 0) {
    int endIndex = std::min(startIndex + TABLE_PAGE_AMOUNT, static_cast<int>(clients.size()));
    std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(20) << "Name"
                  << std::setw(30) << "Surname" << std::endl;
    std::cout << std::setfill('=') << std::setw(60) << "" << std::setfill(' ') << std::endl;
    for (int i = startIndex; i < endIndex; i++) {
        std::cout << std::left << std::setw(10) << clients[i].ID
                    << std::setw(20) << clients[i].Name
                    << std::setw(30) << clients[i].Surname << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(60) << "" << std::setfill(' ') << std::endl;
}

void displayItemTable(const std::vector<Item>& items, int startIndex = 0) {
    int endIndex = std::min(startIndex + TABLE_PAGE_AMOUNT, static_cast<int>(items.size()));
    std::cout << std::left << std::setw(10) << "ID"
                << std::setw(30) << "Type"
                << std::setw(30) << "Model"
                << std::setw(10) << "Price" << std::endl;
    std::cout << std::setfill('=') << std::setw(80) << "" << std::setfill(' ') << std::endl;
    for (int i = startIndex; i < endIndex; i++) {
        std::cout << std::left << std::setw(10) << items[i].ID
                    << std::setw(30) << itemTypeToString(items[i].Type)
                    << std::setw(30) << items[i].Model
                    << std::setw(10) << std::fixed << std::setprecision(2) << items[i].Price << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(80) << "" << std::setfill(' ') << std::endl;
}

void displayOrderItemTable(const std::vector<OrderItem>& orderItems, int startIndex = 0) {
    int endIndex = std::min(startIndex + TABLE_PAGE_AMOUNT, static_cast<int>(orderItems.size()));
    std::cout << std::left << std::setw(10) << "Item ID"
                << std::setw(30) << "Model"
                << std::setw(10) << "Amount"
                << std::setw(15) << "Total Price" << std::endl;
    std::cout << std::setfill('=') << std::setw(65) << "" << std::setfill(' ') << std::endl;
    for (int i = startIndex; i < endIndex; i++) {
        std::cout << std::left << std::setw(10) << orderItems[i].ItemID
                    << std::setw(30) << searchItemByID(items_db, orderItems[i].ItemID).Model
                    << std::setw(10) << orderItems[i].Amount
                    << std::setw(15) << std::fixed << std::setprecision(2) << orderItems[i].TotalPrice << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(65) << "" << std::setfill(' ') << std::endl;
}

void displayOrderTable(const std::vector<Order>& orders, int startIndex = 0) {
    int endIndex = std::min(startIndex + TABLE_PAGE_AMOUNT, static_cast<int>(orders.size()));
    std::cout << std::left << std::setw(10) << "ID"
                << std::setw(20) << "Order Date"
                << std::setw(10) << "Client ID"
                << std::setw(15) << "Total Price" << std::endl;
    std::cout << std::setfill('=') << std::setw(55) << "" << std::setfill(' ') << std::endl;
    for (int i = startIndex; i < endIndex; i++) {
        std::cout << std::left << std::setw(10) << orders[i].ID
                    << std::setw(20) << orders[i].Date
                    << std::setw(10) << orders[i].ClientID 
                    << std::setw(15) << orders[i].TotalPrice << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(55) << "" << std::setfill(' ') << std::endl;
}

void displayItem(const Item& item) {
    if (item.Model[0] == '\0') {
        std::cout << "No Items selected" << std::endl;
    } else {
        std::cout << "Item ID: " << item.ID << ", Model: " << item.Model << ", Price: " << item.Price << std::endl;
    }
}

Item searchForItem(const MenuScreen& Screen) {
    Item tempItem;
    int32_t tempPage = 0;
    std::vector<Item> tempItems;

    std::copy(items_db.begin(), items_db.end(), std::back_inserter(tempItems));

    while (true) {
        printActions(Screen);

        // print the ordered items table
        std::cout << "\n" << Screen.TableName << ":\n\n";
        displayItemTable(tempItems, tempPage);

        // prompt the user to choose an action
        std::cout << "\nWhat would you like to do now? Choose an action number: ";

        int actionNumber;
        std::cin >> actionNumber;

        // perform the selected action
        std::cout << "\nYou chose action number " << actionNumber << ".\n";

        if (actionNumber == 1) {
            std::cout << "\nProvide an ID number of Item: ";
            uint32_t tempID;
            std::cin >> tempID;
            tempItem = searchItemByID(items_db, tempID);
            if (tempItem.Model[0] != '\0'){
                return tempItem;
            }
        }
        else if (actionNumber == 2) {
            // TODO: Search by type
        }
        else if (actionNumber == 3) {
            // TODO: search by model
        }
        else if (actionNumber == 4) {
            // TODO: Filter by price
        }
        else if (actionNumber == 5) {
            nextPage(tempPage);
        }
        else if (actionNumber == 6) {
            previousPage(tempPage);
        }
        else if (actionNumber == 7) {
            std::cout << "\nOrder creation cancelled.\n";
            return Item();
        }
        else {
            std::cout << "\nInvalid action number. Please choose a number between 1 and " << Screen.Actions.size() << ".\n";
        }
    }
}

OrderItem addItemToOrder(const MenuScreen& Screen) {
    Item tempItem;
    OrderItem tempOrderItem;
    uint32_t selectedAmount = 1;
    std::string tempAmount;

    while (true) {
        printActions(Screen);

        std::cout << "\nSelected Item:\n";
        displayItem(tempItem);
        std::cout << "\nSelected Amount: " << selectedAmount << " " << tempAmount << "\n";

        // prompt the user to choose an action
        std::cout << "\nWhat would you like to do now? Choose an action number: ";

        int actionNumber;
        std::cin >> actionNumber;

        // perform the selected action
        std::cout << "\nYou chose action number " << actionNumber << ".\n";

        if (actionNumber == 1) {
            tempItem = searchForItem(SearchItemScreen);
        }
        else if (actionNumber == 2) {
            tempOrderItem.ItemID = tempItem.ID;
            tempOrderItem.Amount = selectedAmount;
            tempOrderItem.TotalPrice = selectedAmount * tempItem.Price;
            return tempOrderItem;
        }
        else if (actionNumber == 3) {
            std::cout << "\nSet new Amount: ";
            std::cin >> tempAmount;
            if (isNumber(tempAmount)) selectedAmount = std::stoul(tempAmount);
        }
        else if (actionNumber == 4) {
            std::cout << "\nItem addition cancelled.\n";
            return OrderItem(0,0,0);
        }
        else {
            std::cout << "\nInvalid action number. Please choose a number between 1 and " << Screen.Actions.size() << ".\n";
        }
    }
}

Order createOrder(const MenuScreen& Screen) {
    // initialize an empty vector of OrderItems
    std::vector<OrderItem> tempOrderItems;
    Item tempItem;
    OrderItem tempOrderItem;
    int32_t tempPage = 0;

    while (true) {
        // print the header and actions list
        printActions(Screen);

        // print the ordered items table
        std::cout << "\n" << Screen.TableName << ":\n\n";
        displayOrderItemTable(tempOrderItems, tempPage);

        // prompt the user to choose an action
        std::cout << "\nWhat would you like to do now? Choose an action number: ";

        int actionNumber;
        std::cin >> actionNumber;

        // perform the selected action
        std::cout << "\nYou chose action number " << actionNumber << ".\n";

        if (actionNumber == 1) {
            tempOrderItem = addItemToOrder(AddItemToOrderScreen);
            if (tempOrderItem.Amount != 0) tempOrderItems.push_back(tempOrderItem);
        }
        else if (actionNumber == 2) {
            // delete OrderItem
        }
        else if (actionNumber == 3) {
            Order newOrder;
            newOrder.ClientID = 12;
            newOrder.Date = "202305072052";
            newOrder.PaymentType = PaymentType::Cash;
            newOrder.TotalPrice = getOrderTotalPrice(tempOrderItems);
            std::copy(tempOrderItems.begin(), tempOrderItems.end(), std::back_inserter(newOrder.Items));
            return newOrder;
        }
        else if (actionNumber == 4) {
            nextPage(tempPage);
        }
        else if (actionNumber == 5) {
            previousPage(tempPage);
        }
        else if (actionNumber == 6) {
            std::cout << "\nOrder creation cancelled.\n";
            return Order();
        }
        else {
            std::cout << "\nInvalid action number. Please choose a number between 1 and " << Screen.Actions.size() << ".\n";
        }
    }
}
