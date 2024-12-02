#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string name;
    int quantity;
    int pages;
    double price;

public:
    Book(string n = "", int q = 0, int pg = 0, double p = 0.0) {
        name = n;
        quantity = q;
        pages = pg;
        price = p;
    }

    string getName() { return name; }
    int getQuantity() { return quantity; }
    int getPages() { return pages; }
    double getPrice() { return price; }

    void setQuantity(int q) { quantity = q; }
    void reduceQuantity(int q) { if (quantity >= q) quantity -= q; }
};

class Transaction {
public:
    int bookID;
    string bookName;
    int quantityPurchased;
    double totalCost;

    Transaction(int id = 0, string name = "", int qty = 0, double cost = 0.0)
        : bookID(id), bookName(name), quantityPurchased(qty), totalCost(cost) {}
};

class BookShop {
private:
    Book shopInventory[100];
    int bookIDs[100];
    Transaction transactionHistory[100];
    int totalBooks;
    int totalTransactions;
    double totalIncome;

public:
    BookShop() {
        totalBooks = 0;
        totalTransactions = 0;
        totalIncome = 0.0;
    }

    void addBook(string name, int quantity, int pages, double price) {
        if (totalBooks < 100) {
            shopInventory[totalBooks] = Book(name, quantity, pages, price);
            bookIDs[totalBooks] = 100 + totalBooks;
            cout << "Book Added! ID: " << bookIDs[totalBooks] << ", Name: " << name << endl;
            totalBooks++;
        } else {
            cout << "Shop is full! Cannot add more books.\n";
        }
    }

    void purchaseBook(int bookID, int purchaseQuantity, double money) {
        for (int i = 0; i < totalBooks; i++) {
            if (bookIDs[i] == bookID) {
                if (shopInventory[i].getQuantity() >= purchaseQuantity) {
                    double totalCost = shopInventory[i].getPrice() * purchaseQuantity;
                    if (money >= totalCost) {
                        shopInventory[i].reduceQuantity(purchaseQuantity);
                        totalIncome += totalCost;

                        // Log the transaction
                        if (totalTransactions < 100) {
                            transactionHistory[totalTransactions++] = Transaction(bookID, shopInventory[i].getName(), purchaseQuantity, totalCost);
                        } else {
                            cout << "Transaction log is full! Cannot record more transactions.\n";
                        }

                        cout << "Purchase Successful! Total Cost: " << totalCost;
                        if (money > totalCost) {
                            cout << ". Return Change: " << (money - totalCost);
                        }
                        cout << endl;
                    } else {
                        cout << "Not enough money to buy the requested quantity.\n";
                    }
                } else {
                    cout << "Not enough stock available. Current stock: " << shopInventory[i].getQuantity() << endl;
                }
                return;
            }
        }
        cout << "Book ID not found.\n";
    }

    void showBookDetails() {
        if (totalBooks == 0) {
            cout << "No books in the shop.\n";
            return;
        }

        for (int i = 0; i < totalBooks; i++) {
            cout << "ID: " << bookIDs[i]
                 << ", Name: " << shopInventory[i].getName()
                 << ", Price: " << shopInventory[i].getPrice()
                 << ", Quantity: " << shopInventory[i].getQuantity()
                 << ", Pages: " << shopInventory[i].getPages() << endl;
        }
    }

    void showIncome() {
        cout << "Total Income: " << totalIncome << endl;
    }

    void showTransactionHistory() {
        if (totalTransactions == 0) {
            cout << "No transactions have been made.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";
        for (int i = 0; i < totalTransactions; i++) {
            cout << "Book ID: " << transactionHistory[i].bookID
                 << ", Book Name: " << transactionHistory[i].bookName
                 << ", Quantity Purchased: " << transactionHistory[i].quantityPurchased
                 << ", Total Cost: " << transactionHistory[i].totalCost << endl;
        }
    }
};

void displayMenu() {
    cout << "\n--- BookShop Menu ---\n";
    cout << "1. Add Book\n";
    cout << "2. Purchase Book\n";
    cout << "3. Show Book Lists\n";
    cout << "4. Show Total Income\n";
    cout << "5. Show Transaction History\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BookShop shop;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            string name;
            int quantity, pages;
            double price;

            cin.ignore();
            cout << "Enter Book Name: ";
            getline(cin, name);
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Pages: ";
            cin >> pages;
            cout << "Enter Price: ";
            cin >> price;

            shop.addBook(name, quantity, pages, price);
        } else if (choice == 2) {
            int bookID, purchaseQuantity;
            double money;

            cout << "Enter Book ID: ";
            cin >> bookID;
            cout << "Enter Quantity to Purchase: ";
            cin >> purchaseQuantity;
            cout << "Enter Payment Amount: ";
            cin >> money;

            shop.purchaseBook(bookID, purchaseQuantity, money);
        } else if (choice == 3) {
            shop.showBookDetails();
        } else if (choice == 4) {
            shop.showIncome();
        } else if (choice == 5) {
            shop.showTransactionHistory();
        } else if (choice == 6) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
