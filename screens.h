#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdint>
#include <cctype>
#include <ctime>

template<typename T>
bool ascendingPrices(const T& a, const T& b) {
    return a.Price < b.Price;
}

template<typename T>
bool descendingPrices(const T& a, const T& b) {
    return a.Price > b.Price;
}

void stringToLower(std::string& input){
    for (char& c : input) {
        c = std::tolower(c);
    }
}

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

float getOrderTotalPrice(const Order& order){
    float totalPrice = 0;
    OrderItem temp;
    uint32_t it = order.FirstOrderItemID;
    while (it != 0){
        temp = searchOrderItemByID(order_item_db, it);
        totalPrice = totalPrice + temp.TotalPrice;
        it = temp.NextOrderItemID;
    }
    return totalPrice;
}

template<typename T>
unsigned int getNextAvailableID(const std::vector<T>& data) {
  unsigned int smallest = 1;
  if (data.size() == 0) return smallest;

  std::vector<unsigned int> ids;
  ids.reserve(data.size());
  
  for (const auto& next : data) {
    ids.push_back(next.ID);
  }
  
  std::sort(ids.begin(), ids.end());
  
  for (unsigned int id : ids) {
    if (id == smallest) {
      smallest++;
    } else if (id > smallest) {
      return smallest;
    }
  }
  
  return smallest;
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

void displayOrderItemTable(const Order& order, int startIndex = 0) {
    std::vector<OrderItem> tempOrderItems;
    uint32_t nextOrderItemId = order.FirstOrderItemID;
    while (nextOrderItemId != 0){
        tempOrderItems.push_back(searchOrderItemByID(order_item_db, nextOrderItemId));
        nextOrderItemId = tempOrderItems.back().NextOrderItemID;
    }

    int endIndex = std::min(startIndex + TABLE_PAGE_AMOUNT, static_cast<int>(tempOrderItems.size()));
    std::cout << std::left << std::setw(10) << "Item ID"
                << std::setw(30) << "Model"
                << std::setw(10) << "Amount"
                << std::setw(15) << "Total Price" << std::endl;
    std::cout << std::setfill('=') << std::setw(65) << "" << std::setfill(' ') << std::endl;
    for (int i = startIndex; i < endIndex; i++) {
        std::cout << std::left << std::setw(10) << tempOrderItems[i].ItemID
                    << std::setw(30) << searchItemByID(items_db, tempOrderItems[i].ItemID).Model
                    << std::setw(10) << tempOrderItems[i].Amount
                    << std::setw(15) << std::fixed << std::setprecision(2) << tempOrderItems[i].TotalPrice << std::endl;
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
            std::cout << "\nProvide a type of Item you are interested in: ";
            std::string input;
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
            stringToLower(input);
            tempItems.clear();
            for (const auto& item : items_db) {
                std::string typeString = itemTypeToString(item.Type);
                stringToLower(typeString);
                int result = input.compare(typeString);
                if (result == 0) {
                    tempItems.push_back(item);
                }
            }
        }
        else if (actionNumber == 3) {
            std::cout << "\nProvide a Model name of part of it: ";
            std::string input;
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
            stringToLower(input);
            tempItems.clear();
            for (const auto& item : items_db) {
                std::string modelString(item.Model);
                stringToLower(modelString);
                int result = modelString.find(input);
                if (result != -1) {
                    tempItems.push_back(item);
                }
            }
        }
        else if (actionNumber == 4) {
            std::cout << "\nPress 1 for 'Lower to Higher', or 2 for 'Higher to Lower' price: ";
            int choise;
            std::cin >> choise;
            if (choise == 1){
                std::sort(tempItems.begin(), tempItems.end(),ascendingPrices<Item>);
            }
            else if (choise == 2){
                std::sort(tempItems.begin(), tempItems.end(), descendingPrices<Item>);
            }
            else std::cout << "\nInvalid sorting option" << std::endl;
        }
        else if (actionNumber == 5) {
            tempItems.clear();
            std::copy(items_db.begin(), items_db.end(), std::back_inserter(tempItems));
            std::cout << "\nFilters cleared" << std::endl;
        }
        else if (actionNumber == 6) {
            nextPage(tempPage);
        }
        else if (actionNumber == 7) {
            previousPage(tempPage);
        }
        else if (actionNumber == 8) {
            std::cout << "\nOrder creation cancelled.\n";
            return Item();
        }
        else {
            std::cout << "\nInvalid action number. Please choose a number between 1 and " << Screen.Actions.size() << ".\n";
        }
    }
}

uint32_t addItemToOrder(const MenuScreen& Screen) {
    Item tempItem;
    OrderItem tempOrderItem;
    uint32_t selectedAmount = 0;
    std::string tempAmount;

    while (true) {
        printActions(Screen);

        std::cout << "\nSelected Item:\n";
        displayItem(tempItem);
        std::cout << "\nSelected Amount: " << selectedAmount << "\n";

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
            tempOrderItem.ID = getNextAvailableID<OrderItem>(order_item_db);
            tempOrderItem.ItemID = tempItem.ID;
            tempOrderItem.Amount = selectedAmount;
            tempOrderItem.TotalPrice = selectedAmount * tempItem.Price;
            order_item_db.push_back(tempOrderItem);
            return tempOrderItem.ID;
        }
        else if (actionNumber == 3) {
            std::cout << "\nSet new Amount: ";
            std::cin >> tempAmount;
            if (isNumber(tempAmount)) selectedAmount = std::stoul(tempAmount);
        }
        else if (actionNumber == 4) {
            std::cout << "\nItem addition cancelled.\n";
            return 0;
        }
        else {
            std::cout << "\nInvalid action number. Please choose a number between 1 and " << Screen.Actions.size() << ".\n";
        }
    }
}

Order createOrder(const MenuScreen& Screen) {
    // initialize an empty vector of OrderItems
    Order tempOrder;
    Item tempItem;
    uint32_t tempOrderItemID;
    int32_t tempPage = 0;

    while (true) {
        // print the header and actions list
        printActions(Screen);

        // print the ordered items table
        std::cout << "\n" << Screen.TableName << ":\n\n";
        displayOrderItemTable(tempOrder, tempPage);

        // prompt the user to choose an action
        std::cout << "\nWhat would you like to do now? Choose an action number: ";

        int actionNumber;
        std::cin >> actionNumber;

        // perform the selected action
        std::cout << "\nYou chose action number " << actionNumber << ".\n";

        if (actionNumber == 1) {
            tempOrderItemID = addItemToOrder(AddItemToOrderScreen);
            std::cout << "\nDEBUG::Temp OrderItem ID: " << tempOrderItemID << std::endl;
            if (tempOrderItemID != 0){
                if (tempOrder.FirstOrderItemID == 0) tempOrder.FirstOrderItemID = tempOrderItemID;
                else {
                    uint32_t firstID = tempOrder.FirstOrderItemID;
                    setNextOrderItemID(order_item_db, firstID, tempOrderItemID);
                }
            }
        }
        else if (actionNumber == 2) {
            // delete OrderItem
        }
        else if (actionNumber == 3) {
            tempOrder.ClientID = 12;
            std::time_t now = std::time(nullptr);
            std::strftime(tempOrder.Date, sizeof(tempOrder.Date), "%Y-%m-%d", std::localtime(&now));
            tempOrder.PayType = PaymentType::Cash;
            tempOrder.TotalPrice = getOrderTotalPrice(tempOrder);
            return tempOrder;
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
