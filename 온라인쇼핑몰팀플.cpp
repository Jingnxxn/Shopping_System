#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <locale>

using namespace std;

class Product {
public:
    string name;
    int price;

    Product(string name, int price) {
        this->name = name;
        this->price = price;
    }

    virtual void printInfo() {
        cout << "상품명: " << name << ", 가격: " << price << "원" << endl;
    }
};

class Clothing : public Product {
public:
    string size;
    Clothing(string name, int price, string size) : Product(name, price) {
        this->size = size;
    }

    void printInfo() {
        cout << "상품명: " << name << ", 가격: " << price << "원, 사이즈: " << size << endl;
    }
};

template <typename T>
class ShoppingCart {
public:
    vector<T*> products;

    void addProduct(T* product) {
        products.push_back(product);
    }

    int calculateTotalPrice() {
        int totalPrice = 0;
        for (int i = 0; i < products.size(); i++) {
            totalPrice += products[i]->price;
        }
        return totalPrice;
    }
};

class ProductManagement {
public:
    vector<Product*> productDatabase;
    void loadProductData() {
        ifstream file("product_data.txt");
        if (!file) {
            cout << "상품 데이터 파일을 찾을 수 없습니다." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            string name;
            int price;
            string size;

            size_t commaPos1 = line.find(',');
            if (commaPos1 != string::npos) {
                name = line.substr(0, commaPos1);

                size_t commaPos2 = line.find(',', commaPos1 + 1);
                if (commaPos2 != string::npos) {
                    string priceStr = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
                    price = stoi(priceStr);
                    size = line.substr(commaPos2 + 1);
                }
            }

            Clothing* clothing = new Clothing(name, price, size);
            productDatabase.push_back(clothing);
        }

        file.close();
    }

    void saveProductData() {
        ofstream file("product_data.txt");
        if (!file) {
            cout << "상품 데이터 파일을 생성할 수 없습니다." << endl;
            return;
        }

        for (int i = 0; i < productDatabase.size(); i++) {
            Clothing* clothing = dynamic_cast<Clothing*>(productDatabase[i]);
            if (clothing) {
                file << clothing->name << "," << clothing->price << "," << clothing->size << endl;
            }
        }

        file.close();
    }

    void addProduct(Product* product) {
        productDatabase.push_back(product);
    }

    void removeProduct(int productIndex) {
        if (productIndex < 1 || productIndex > productDatabase.size()) {
            cout << "잘못된 상품 번호입니다. 다시 선택하세요." << endl;
            return;
        }

        productDatabase.erase(productDatabase.begin() + productIndex - 1);
        cout << "상품을 삭제하였습니다." << endl;
    }

    Product* searchProduct(string productName) {
        for (int i = 0; i < productDatabase.size(); i++) {
            if (productDatabase[i]->name == productName) {
                return productDatabase[i];
            }
        }
        return nullptr;
    }

    void printProductList() {
        cout << "상품 목록:" << endl;
        for (int i = 0; i < productDatabase.size(); i++) {
            cout << i + 1 << ". ";
            productDatabase[i]->printInfo();
        }
    }
};

class Customer {
public:
    string name;
    string address;

    Customer(string name, string address) {
        this->name = name;
        this->address = address;
    }

    void printInfo() {
        cout << "이름: " << name << ", 주소: " << address << endl;
    }
};

class CustomerManagement {
private:
    vector<Customer*> customerDatabase;

public:
    void loadCustomerData() {
        ifstream file("customer_data.txt");
        if (!file) {
            cout << "고객 데이터 파일을 찾을 수 없습니다." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            string name;
            string address;

            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                name = line.substr(0, commaPos);
                address = line.substr(commaPos + 1);
            }

            Customer* customer = new Customer(name, address);
            customerDatabase.push_back(customer);
        }

        file.close();
    }

    void saveCustomerData() {
        ofstream file("customer_data.txt");
        if (!file) {
            cout << "고객 데이터 파일을 생성할 수 없습니다." << endl;
            return;
        }

        for (int i = 0; i < customerDatabase.size(); i++) {
            file << customerDatabase[i]->name << "," << customerDatabase[i]->address << endl;
        }

        file.close();
    }

    void addCustomer(Customer* customer) {
        customerDatabase.push_back(customer);
    }

    void removeCustomer(int customerIndex) {
        if (customerIndex < 1 || customerIndex > customerDatabase.size()) {
            cout << "잘못된 고객 번호입니다. 다시 선택하세요." << endl;
            return;
        }

        customerDatabase.erase(customerDatabase.begin() + customerIndex - 1);
        cout << "고객을 삭제하였습니다." << endl;
    }

    Customer* searchCustomer(string customerName) {
        for (int i = 0; i < customerDatabase.size(); i++) {
            if (customerDatabase[i]->name == customerName) {
                return customerDatabase[i];
            }
        }
        return nullptr;
    }

    void printCustomerList() {
        cout << "고객 목록:" << endl;
        for (int i = 0; i < customerDatabase.size(); i++) {
            cout << i + 1 << ". ";
            customerDatabase[i]->printInfo();
        }
    }
};

class Order {
public:
    string orderNumber;
    Customer* customer;
    vector<Product*> products;

    Order(string orderNumber, Customer* customer) {
        this->orderNumber = orderNumber;
        this->customer = customer;
    }

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void removeProduct(int productIndex) {
        if (productIndex < 1 || productIndex > products.size()) {
            cout << "잘못된 상품 번호입니다. 다시 선택하세요." << endl;
            return;
        }

        products.erase(products.begin() + productIndex - 1);
        cout << "상품을 삭제하였습니다." << endl;
    }

    void printOrderInfo() {
        cout << "주문번호: " << orderNumber << endl;
        cout << "고객 정보: ";
        customer->printInfo();
        cout << "주문 상품 목록:" << endl;
        for (int i = 0; i < products.size(); i++) {
            cout << i + 1 << ". ";
            products[i]->printInfo();
        }
        cout << "총 주문 가격: " << calculateTotalPrice() << "원" << endl;
    }

    int calculateTotalPrice() {
        int totalPrice = 0;
        for (int i = 0; i < products.size(); i++) {
            totalPrice += products[i]->price;
        }
        return totalPrice;
    }
};

class OrderManagement {
private:
    vector<Order*> orderDatabase;

public:
    void addOrder(Order* order) {
        orderDatabase.push_back(order);
    }

    void removeOrder(int orderIndex) {
        if (orderIndex < 1 || orderIndex > orderDatabase.size()) {
            cout << "잘못된 주문 번호입니다. 다시 선택하세요." << endl;
            return;
        }

        orderDatabase.erase(orderDatabase.begin() + orderIndex - 1);
        cout << "주문을 삭제하였습니다." << endl;
    }

    Order* searchOrder(string orderNumber) {
        for (int i = 0; i < orderDatabase.size(); i++) {
            if (orderDatabase[i]->orderNumber == orderNumber) {
                return orderDatabase[i];
            }
        }
        return nullptr;
    }

    void printOrderList() {
        cout << "주문 목록:" << endl;
        for (int i = 0; i < orderDatabase.size(); i++) {
            cout << i + 1 << ". ";
            orderDatabase[i]->printOrderInfo();
        }
    }
};

int main() {
    ProductManagement productManagement;
    CustomerManagement customerManagement;
    OrderManagement orderManagement;

    productManagement.loadProductData();
    customerManagement.loadCustomerData();

    int choice;
    while (true) {
        cout << "=== 메뉴 ===" << endl;
        cout << "1. 상품 등록" << endl;
        cout << "2. 상품 삭제" << endl;
        cout << "3. 상품 목록 출력" << endl;
        cout << "4. 고객 등록" << endl;
        cout << "5. 고객 삭제" << endl;
        cout << "6. 고객 목록 출력" << endl;
        cout << "7. 주문 생성" << endl;
        cout << "8. 주문 삭제" << endl;
        cout << "9. 주문 목록 출력" << endl;
        cout << "0. 종료" << endl;
        cout << "메뉴를 선택하세요: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int price;
            string size;

            cout << "상품 이름: ";
            cin.ignore();
            getline(cin, name);

            cout << "상품 가격: ";
            cin >> price;

            cout << "옷 사이즈: ";
            cin.ignore();
            getline(cin, size);

            Clothing* clothing = new Clothing(name, price, size);
            productManagement.addProduct(clothing);
            productManagement.saveProductData();

            cout << "상품이 등록되었습니다." << endl;
            break;
        }
        case 2: {
            int productIndex;
            cout << "삭제할 상품 번호를 입력하세요: ";
            cin >> productIndex;
            productManagement.removeProduct(productIndex);
            productManagement.saveProductData();
            break;
        }
        case 3: {
            productManagement.printProductList();
            break;
        }
        case 4: {
            string name;
            string address;

            cout << "고객 이름: ";
            cin.ignore();
            getline(cin, name);

            cout << "고객 주소: ";
            getline(cin, address);

            Customer* customer = new Customer(name, address);
            customerManagement.addCustomer(customer);
            customerManagement.saveCustomerData();

            cout << "고객이 등록되었습니다." << endl;
            break;
        }
        case 5: {
            int customerIndex;
            cout << "삭제할 고객 번호를 입력하세요: ";
            cin >> customerIndex;
            customerManagement.removeCustomer(customerIndex);
            customerManagement.saveCustomerData();
            break;
        }
        case 6: {
            customerManagement.printCustomerList();
            break;
        }
        case 7: {
            string orderNumber;
            string customerName;

            cout << "주문 번호: ";
            cin.ignore();
            getline(cin, orderNumber);

            cout << "주문 고객 이름: ";
            getline(cin, customerName);

            Customer* customer = customerManagement.searchCustomer(customerName);
            if (customer == nullptr) {
                cout << "고객을 찾을 수 없습니다. 주문을 생성할 수 없습니다." << endl;
                break;
            }

            Order* order = new Order(orderNumber, customer);

            while (true) {
                cout << "주문할 상품 번호를 선택하세요 (0: 주문 완료): ";
                int productChoice;
                cin >> productChoice;

                if (productChoice == 0) {
                    break;
                }

                productManagement.printProductList();

                if (productChoice < 1 || productChoice > productManagement.productDatabase.size()) {
                    cout << "잘못된 상품 번호입니다. 다시 선택하세요." << endl;
                    continue;
                }

                Product* product = productManagement.productDatabase[productChoice - 1];
                order->addProduct(product);
            }

            orderManagement.addOrder(order);

            cout << "주문이 생성되었습니다." << endl;
            break;
        }

        case 8: {
            int orderIndex;
            cout << "삭제할 주문 번호를 입력하세요: ";
            cin >> orderIndex;
            orderManagement.removeOrder(orderIndex);
            break;
        }
        case 9: {
            orderManagement.printOrderList();
            break;
        }
        case 0: {
            productManagement.saveProductData();
            customerManagement.saveCustomerData();
            cout << "프로그램을 종료합니다." << endl;
            return 0;
        }
        default:
            cout << "잘못된 메뉴 번호입니다. 다시 선택하세요." << endl;
        }
    }
}

