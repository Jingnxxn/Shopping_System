# C++ 기반 쇼핑 시스템
## 1. 서론 
---
 * C++ 언어를 사용하여 쇼핑몰 관리 시스템을 개발하고, 상품, 고객, 주문 정보를 효과적으로 관리하는 방법을 제시한다. 이를 통해 쇼핑몰 운영자는 상품, 고객, 주문 관리를 원활하게 수행할 수 있는 시스템을 활용할 수 있고, 클래스와 객체지향 프로그래밍 설계, 표준 라이브러리 사용법 등을 학습할 수 있다.
---
## 2. 팀원 및 역할
---
> + 김진원 : 깃허브, 코드 전체 구조, 파일 입출력 구현, 발표
> + 황찬영 : 유튜브 영상, 프로젝트 계획서, 함수 구현
> + 김지은 : 논문, 오류 수정 및 검출, 함수 구현
---
## 3. 주요 기능
---
+ 상속
> C++에서 상속은 클래스 간의 특성과 동작을 공유하는 메커니즘이다. 상위 클래스의 멤버를 하위 클래스에서 재사용할 수 있어 코드의 재사용성과 유지 보수성을 높여준다. 또한, 객체 지향 원리만의 특성으로 추상화 레벨을 높여주며, 소프트웨어의 재사용성을 지원해준다.
+ 다형성
> 다형성은 객체지향 언어의 중요한 개념으로서 동일한 메시지를 서로 다른 객체에 각기 보냈을 때 각 객체에 맞는 메소드를 부를 수 있는 것, 나의 인터페이스를 통해 다양한 타입의 객체를 사용할 수 있게 하는 기능이다. 이런 기능은 확장성을 제공하고 코드의 재사용성과 유연성을 높일 수 있으며, 상속과 가상 함수를 통해 구현된다.
+ 템플릿
> C++ 템플릿은 제네릭 프로그래밍을 지원하기 위한 핵심 기능이다. 자료형에 대해 재사용 가능한 코드를 생성하는 템플릿 형태를 정의하는 메커니즘이다. 이는 추상화를 통해 타입이나 값에 대한 일반적인 알고리즘 또는 데이터 구조를 작성 가능하게 해주며 이를 통해 코드의 유연성과 재사용성을 증가할 수 있다.
+ STL
> C++의 STL은 템플릿 기반의 라이브러리이다. 이는 다양한 데이터 구조, 알고리즘을 제공한다. STL은 컨테이너, 반복자, 알고리즘, 함수 객체, 어댑터 등의 주요 구성 요소로 이루어진다. 이는 효율성과 유지 보수성을 향상시킨다. 
+ 파일 입출력
> C++의 파일 입출력 기능은 파일에서 데이터를 읽거나 데이터를 파일에 쓰는 기능을 제공한다. 이를 통해 프로그램은 외부 파일과 데이터를 주고받아 정보를 활용하고 저장할 수 있다. 파일 열기와 닫기는 데이터 처리와 관리에 필수적인 단계이다.
---
## 4. 코드 분석
---
```cpp
#include <iostream>
#include <string>
#include <vector> //컨테이너 클래스 정의(추가, 삭제, 검색 등 지원)
#include <algorithm> //STL의 일부분, 수정과 검색 함수에 쓰임
#include <fstream>
#include <locale>

using namespace std;

class Product {
public:
    string name;
    int price;
    string size;

    Product(string name, int price, string size) {
        this->name = name;
        this->price = price;
        this->size = size;
    }

    virtual void printInfo() {
        cout << "상품명: " << name << ", 가격: " << price << "원, 사이즈: " << size  << endl;
    }
     void modifyProduct(string newName, int newPrice, string newSize) {
        name = newName;
        price = newPrice;
        size = newSize;
    } 
};

class Clothing : public Product { //상속 : Clothing 클래스가 Product 클래스에게 상속받음, 옷 상품 외에도 가능
public:
    string size;
    Clothing(string name, int price, string size) : Product(name, price, size) {
        this->size = size;
    }

    void printInfo() {
        cout << "상품명: " << name << ", 가격: " << price << "원, 사이즈: " << size << endl;
    }
};

template <typename T> //장바구니에 담을 수 있도록 일반화된 코드 작성 위해 템플릿 사용
class ShoppingCart {
public:            //ShoppingCart 클래스는 vector<T*> products 멤버 변수를 사용하여 제품들을 저장
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
/*ShoppingCart<Product>로 인스턴스화하면 Product 타입의 제품들을 담는 장바구니가 생성되고,
ShoppingCart<Book>으로 인스턴스화하면 Book 타입의 제품들을 담는 장바구니가 생성*/

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
    
    
    void modifyProduct(int productIndex, string newName, int newPrice, string newSize) {
        if (productIndex < 1 || productIndex > productDatabase.size()) {
            cout << "잘못된 상품 번호입니다. 다시 선택하세요." << endl;
            return;
        }
        Product* product = productDatabase[productIndex - 1];
       cout << "상품을 수정하였습니다." << endl;
    }
    Product* searchProduct(string productName) {
        for (int i = 0; i < productDatabase.size(); i++) {
            if (productDatabase[i]->name == productName) {
                return productDatabase[i];
            }
        }
        return nullptr;
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
    void modifyCustomer(string newName, string newAddress) {
        name = newName;
        address = newAddress;
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
    void modifyCustomer(int customerIndex, string newName, string newAddress) {
        if (customerIndex < 1 || customerIndex > customerDatabase.size()) {
            cout << "잘못된 고객 번호입니다. 다시 선택하세요." << endl;
            return;
        }

        Customer* customer = customerDatabase[customerIndex - 1];
        customer->modifyCustomer(newName, newAddress);
        cout << "고객을 수정하였습니다." << endl;
    }

    Customer* searchCustomer(string customerName) {
        for (int i = 0; i < customerDatabase.size(); i++) {
            if (customerDatabase[i]->name == customerName) {
                return customerDatabase[i];
            }
        }
        return nullptr;
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
        cout << "10. 상품 수정" << endl;
        cout << "11. 상품 검색" << endl;
        cout << "12. 고객 수정" << endl;
        cout << "13. 고객 검색" << endl;
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
        case 10: {
            int productIndex;
            cout << "수정할 상품 번호를 입력하세요: ";
            cin >> productIndex;

            string newName;
            int newPrice;
            string newSize;

            cout << "새로운 상품 이름: ";
            cin.ignore();
            getline(cin, newName);

            cout << "새로운 상품 가격: ";
            cin >> newPrice;
            
            cout << "새로운 상품 사이즈: ";
            cin.ignore();
            getline(cin, newSize);

            productManagement.modifyProduct(productIndex, newName, newPrice, newSize);
            productManagement.saveProductData();
            break;
        }

        case 11: {
            string productName;
            cout << "검색할 상품 이름을 입력하세요: ";
            cin.ignore();
            getline(cin, productName);
            
            Product* product = productManagement.searchProduct(productName);
          if (product == nullptr) {
              cout << "상품을 찾을 수 없습니다." << endl;
          } else {
              cout << "상품을 찾았습니다." << endl;
              product->printInfo();
          }
          break;

        }

        case 12: {
            int customerIndex;
            cout << "수정할 고객 번호를 입력하세요: ";
            cin >> customerIndex;

            string newName;
            string newAddress;

            cout << "새로운 고객 이름: ";
            cin.ignore();
            getline(cin, newName);

            cout << "새로운 고객 주소: ";
            getline(cin, newAddress);

            customerManagement.modifyCustomer(customerIndex, newName, newAddress);
            customerManagement.saveCustomerData();
            break;
        }

        case 13: {
            string customerName;
            cout << "검색할 고객 이름을 입력하세요: ";
            cin.ignore();
            getline(cin, customerName);

            Customer* customer = customerManagement.searchCustomer(customerName);
            if (customer != nullptr) {
                cout << "검색 결과:" << endl;
                customer->printInfo();
            } else {
                cout << "고객을 찾을 수 없습니다." << endl;
            }
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
```
-------
## 5. 실행 영상
-------
> 유튜브링크 : <https://www.youtube.com/watch?v=jZDLbWjEDq4>

-----
## 소감
-----
+ 김진원 : 이전에는 예시 양식이나 코드 같은 것들을 보면서 프로젝트를 진행해왔었는데, 이번 프로젝트에서는 완전한 무에서 유를 창조한 첫 프로젝트가 아닌가 싶었습니다.    많은 요구사항들을 충족시키기위해 많은 시간과 노력이 필요했고 그에 맞춰 팀원들이 모두 함께 과제수행을 해줬기에 좋은 결과가 나오지 않았나 생각이 듭니다.    처음은 막막했으나 역시나 마무리가 되고 나니 뿌듯함만 남는 과제였습니다.
+ 황찬영 : 처음으로 팀프로젝트를 통해 큰 프로그램을 만들어봤던 것 같습니다. 며칠 밤을 새벽까지 공대에서 조원들과 함께 프로젝트를 하면서 힘들기도 하였지만 오류를 검출해나가면서 좋았던 일들과 성취감을 느끼는 일도 많았습니다. 정말 단 기간에 코딩 실력이 많이 늘어난 것 같아 기분이 좋습니다.
+ 김지은 : 수업시간에 다룬 내용을 통해 팀프로젝트를 진행하며 수업시간의 내용을 직접 적용해 볼 수 있어서 유익했습니다.  처음엔 마음대로 잘 되지않았지만 팀원들과 여러번의 회의를 통해 서로 아이디어를 제시하고 수정해주며  모든 기능을 구현할 수 있어서 뿌듯했습니다. 이 과정에서 코딩 능력을 향상할 수 있었습니다. 힘들었지만 얻어간것이 많다고 생각되어 행복했습니다. 
