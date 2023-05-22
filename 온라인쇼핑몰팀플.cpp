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
        cout << "��ǰ��: " << name << ", ����: " << price << "��" << endl;
    }
};

class Clothing : public Product {
public:
    string size;
    Clothing(string name, int price, string size) : Product(name, price) {
        this->size = size;
    }

    void printInfo() {
        cout << "��ǰ��: " << name << ", ����: " << price << "��, ������: " << size << endl;
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
            cout << "��ǰ ������ ������ ã�� �� �����ϴ�." << endl;
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
            cout << "��ǰ ������ ������ ������ �� �����ϴ�." << endl;
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
            cout << "�߸��� ��ǰ ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
            return;
        }

        productDatabase.erase(productDatabase.begin() + productIndex - 1);
        cout << "��ǰ�� �����Ͽ����ϴ�." << endl;
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
        cout << "��ǰ ���:" << endl;
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
        cout << "�̸�: " << name << ", �ּ�: " << address << endl;
    }
};

class CustomerManagement {
private:
    vector<Customer*> customerDatabase;

public:
    void loadCustomerData() {
        ifstream file("customer_data.txt");
        if (!file) {
            cout << "�� ������ ������ ã�� �� �����ϴ�." << endl;
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
            cout << "�� ������ ������ ������ �� �����ϴ�." << endl;
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
            cout << "�߸��� �� ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
            return;
        }

        customerDatabase.erase(customerDatabase.begin() + customerIndex - 1);
        cout << "���� �����Ͽ����ϴ�." << endl;
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
        cout << "�� ���:" << endl;
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
            cout << "�߸��� ��ǰ ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
            return;
        }

        products.erase(products.begin() + productIndex - 1);
        cout << "��ǰ�� �����Ͽ����ϴ�." << endl;
    }

    void printOrderInfo() {
        cout << "�ֹ���ȣ: " << orderNumber << endl;
        cout << "�� ����: ";
        customer->printInfo();
        cout << "�ֹ� ��ǰ ���:" << endl;
        for (int i = 0; i < products.size(); i++) {
            cout << i + 1 << ". ";
            products[i]->printInfo();
        }
        cout << "�� �ֹ� ����: " << calculateTotalPrice() << "��" << endl;
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
            cout << "�߸��� �ֹ� ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
            return;
        }

        orderDatabase.erase(orderDatabase.begin() + orderIndex - 1);
        cout << "�ֹ��� �����Ͽ����ϴ�." << endl;
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
        cout << "�ֹ� ���:" << endl;
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
        cout << "=== �޴� ===" << endl;
        cout << "1. ��ǰ ���" << endl;
        cout << "2. ��ǰ ����" << endl;
        cout << "3. ��ǰ ��� ���" << endl;
        cout << "4. �� ���" << endl;
        cout << "5. �� ����" << endl;
        cout << "6. �� ��� ���" << endl;
        cout << "7. �ֹ� ����" << endl;
        cout << "8. �ֹ� ����" << endl;
        cout << "9. �ֹ� ��� ���" << endl;
        cout << "0. ����" << endl;
        cout << "�޴��� �����ϼ���: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int price;
            string size;

            cout << "��ǰ �̸�: ";
            cin.ignore();
            getline(cin, name);

            cout << "��ǰ ����: ";
            cin >> price;

            cout << "�� ������: ";
            cin.ignore();
            getline(cin, size);

            Clothing* clothing = new Clothing(name, price, size);
            productManagement.addProduct(clothing);
            productManagement.saveProductData();

            cout << "��ǰ�� ��ϵǾ����ϴ�." << endl;
            break;
        }
        case 2: {
            int productIndex;
            cout << "������ ��ǰ ��ȣ�� �Է��ϼ���: ";
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

            cout << "�� �̸�: ";
            cin.ignore();
            getline(cin, name);

            cout << "�� �ּ�: ";
            getline(cin, address);

            Customer* customer = new Customer(name, address);
            customerManagement.addCustomer(customer);
            customerManagement.saveCustomerData();

            cout << "���� ��ϵǾ����ϴ�." << endl;
            break;
        }
        case 5: {
            int customerIndex;
            cout << "������ �� ��ȣ�� �Է��ϼ���: ";
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

            cout << "�ֹ� ��ȣ: ";
            cin.ignore();
            getline(cin, orderNumber);

            cout << "�ֹ� �� �̸�: ";
            getline(cin, customerName);

            Customer* customer = customerManagement.searchCustomer(customerName);
            if (customer == nullptr) {
                cout << "���� ã�� �� �����ϴ�. �ֹ��� ������ �� �����ϴ�." << endl;
                break;
            }

            Order* order = new Order(orderNumber, customer);

            while (true) {
                cout << "�ֹ��� ��ǰ ��ȣ�� �����ϼ��� (0: �ֹ� �Ϸ�): ";
                int productChoice;
                cin >> productChoice;

                if (productChoice == 0) {
                    break;
                }

                productManagement.printProductList();

                if (productChoice < 1 || productChoice > productManagement.productDatabase.size()) {
                    cout << "�߸��� ��ǰ ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
                    continue;
                }

                Product* product = productManagement.productDatabase[productChoice - 1];
                order->addProduct(product);
            }

            orderManagement.addOrder(order);

            cout << "�ֹ��� �����Ǿ����ϴ�." << endl;
            break;
        }

        case 8: {
            int orderIndex;
            cout << "������ �ֹ� ��ȣ�� �Է��ϼ���: ";
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
            cout << "���α׷��� �����մϴ�." << endl;
            return 0;
        }
        default:
            cout << "�߸��� �޴� ��ȣ�Դϴ�. �ٽ� �����ϼ���." << endl;
        }
    }
}

