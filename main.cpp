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
        void reduceQuantity() { if (quantity > 0) quantity--; }
};

class BookShop {
    private:
        Book shopInventory[100];
        int bookIDs[100];
        int totalBooks;
        double totalIncome;

    public:

        BookShop() {
            totalBooks = 0;
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

        void purchaseBook(int bookID, double money) {
            for (int i = 0; i < totalBooks; i++) {
                if (bookIDs[i] == bookID) {
                    if (shopInventory[i].getQuantity() > 0) {
                        if (money >= shopInventory[i].getPrice()) {
                            shopInventory[i].reduceQuantity();
                            totalIncome += shopInventory[i].getPrice();
                            cout << "Purchase Successful!";
                            if (money > shopInventory[i].getPrice()) {
                                cout << " Return Change: " << (money - shopInventory[i].getPrice());
                            }
                            cout << endl;
                        } else {
                            cout << "Not enough money to buy the book.\n";
                        }
                    } else {
                        cout << "Book is out of stock.\n";
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
};

void displayMenu() {
    cout << "\n--- BookShop Menu ---\n";
    cout << "1. Add Book\n";
    cout << "2. Purchase Book\n";
    cout << "3. Show Book Lists\n";
    cout << "4. Show Total Income\n";
    cout << "5. Exit\n";
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
            int bookID;
            double money;

            cout << "Enter Book ID: ";
            cin >> bookID;
            cout << "Enter Payment Amount: ";
            cin >> money;

            shop.purchaseBook(bookID, money);
        } else if (choice == 3) {
            shop.showBookDetails();
        } else if (choice == 4) {
            shop.showIncome();
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
