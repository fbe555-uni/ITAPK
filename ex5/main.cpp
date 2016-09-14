#include <iostream>
#include "ProductSystem/algo.cpp"

//#define PRODUCT_DB_FILE		"/home/felix/winlinShare/apk/ex5/ProductSystem/product.db"
#define PRODUCT_DB_FILE     "/home/huxx/Documents/apk/ex5/ProductSystem/product.db"

int main()
{
    bool        running = true;
    ProductList pl;

    while(running)
    {
        char choice;

        std::cout << "********************" << std::endl;
        std::cout << "Help menu: " << std::endl;
        std::cout << "'1' Read product database" << std::endl;
        std::cout << "'2' Print all items" << std::endl;
        std::cout << "'3' Add item" << std::endl;
        std::cout << "'4' Write product database" << std::endl;
        std::cout << "'5' Print poorly selling products" << std::endl;
        std::cout << "'6' Set a discount on all products (using for_each() )" << std::endl;
        std::cout << "'7' Set a discount on all products (using transform() )" << std::endl;
        std::cout << "'8' Calculate the total amount of sold products" << std::endl;


        std::cout << "'q' Quit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;
        float discount = 0;
        switch(choice)
        {
            case '1':
                productDBRead(pl, PRODUCT_DB_FILE);
                break;

            case '2':
                printAll(pl);
                break;

            case '3':
                addItem(pl);
                break;

            case '4':
                productDBWrite(pl, PRODUCT_DB_FILE);
                break;

            case '5':
                printPoorlySellingProducts(pl);
                break;

            case '6':
                std::cout << "Please specify the discount in percent: ";
                std::cin >> discount;
                addDiscountUsingForEach(pl, discount);
                break;

            case '7':
                std::cout << "Please specify the discount in percent: ";
                std::cin >> discount;
                addDiscountUsingTransform(pl, discount);
                break;

            case '8':
                calcTotalSoldProducts(pl);
                break;

            case 'q':
            case 'Q':
                running = false;
                break;
            default:
            std::cout << "Invalid choice! Try again." << std::endl;
        }


    }
}
