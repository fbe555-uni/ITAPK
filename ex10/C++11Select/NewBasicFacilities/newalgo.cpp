#include <fstream>
#include <iostream>
#include <iterator>

#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <string>


#define PRODUCT_DB_FILE        "product.db"

class Product {
public:
    Product(const std::string &name, double price, unsigned int sold = 0)
            : name_(name), price_(price), sold_(sold) {}

    Product()
            : name_(""), price_(0), sold_(0) {}

    const std::string &name() const {
        return name_;
    }

    /**
     * Setting the discount as a percentage
     */
    void setDiscount(double discount) {
        discount = (discount < 0 ? 0 : discount);
        discount = (discount > 100 ? 100 : discount);
        price_ *= (100.0 - discount) / 100.0;
    }

    double price() const {
        return price_;
    }

    void setPrice(double newPrice) {
        price_ = newPrice;
    }

    unsigned int sold() const {
        return sold_;
    }

    friend std::istream &operator>>(std::istream &i, Product &p);

    friend std::ostream &operator<<(std::ostream &o, const Product &p);

private:
    std::string name_;
    double price_;
    int sold_;
};

typedef std::vector<Product> ProductList;


std::ostream &operator<<(std::ostream &o, const Product &p) {
    return o << p.name_ << " " << p.price_ << " " << p.sold_;
}

std::istream &operator>>(std::istream &i, Product &p) {
    return i >> p.name_ >> p.price_ >> p.sold_;
}



/**
 * Read products from file
 */
// void productDBRead(ProductList& pl, const std::string& fileName)
// {
//   pl.clear();
//   std::ifstream pFile( fileName.c_str() );
//   while( !pFile.eof() )
//   {
//     Product p;
//     pFile >> p;
//     if( pFile ) pl.push_back( p );
//   }
// }
void productDBRead(ProductList &pl, const std::string &fileName) {
    pl.clear();
    std::ifstream pFile(fileName.c_str());
    std::copy(std::istream_iterator<Product>(pFile),
              std::istream_iterator<Product>(),
              std::back_inserter(pl));
}



/**
 * Printout all products
 */
// void printAll(const ProductList& pl)
// {
//   std::cout << "##################################################" << std::endl;
//   std::cout << "Printing out all products..." << std::endl;
//   std::cout << "----------------------------" << std::endl;
//   for(ProductList::const_iterator iter = pl.begin(); iter != pl.end(); ++iter)
//   {
//     std::cout << *iter << std::endl;
//   }  
//   std::cout << "##################################################" << std::endl;
// }
void printAll(const ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out all products..." << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::copy(pl.begin(), pl.end(), std::ostream_iterator<Product>(std::cout, "\n"));
    std::cout << "##################################################" << std::endl;
}


/**
   Add item
*/
void addItem(ProductList &pl) {
    std::string name;
    std::cout << "Name of product: ";
    std::cin >> name;

    double price;
    std::cout << "Price: ";
    std::cin >> price;

    unsigned int sold;
    std::cout << "Number of products sold: ";
    std::cin >> sold;

    pl.push_back(Product(name, price, sold));
}


/**
   Write data to db file
*/
void productDBWrite(const ProductList &pl, const std::string &fileName) {
    std::ofstream pFile(fileName.c_str());
    std::copy(pl.begin(), pl.end(), std::ostream_iterator<Product>(pFile, "\n"));
}


/**
 * Print poorly selling products
 */
struct ALot {
    ALot(unsigned int minSold)
            : minSold_(minSold) {}

    bool operator()(const Product &p) {
        return (p.sold() >= minSold_ ? true : false);
    }

private:
    unsigned int minSold_;
};


void printPoorlySellingProducts(const ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out those products that have only been sold a few times..." << std::endl;
    std::cout << "------------------------" << std::endl;
    std::remove_copy_if(pl.begin(), pl.end(), std::ostream_iterator<Product>(std::cout, "\n"), ALot(10));
}


/**
 * Set a discount on all products - Using for_each()
 */
struct DiscountUsingForEach {
    DiscountUsingForEach(double discount)
            : discount_(discount) {}

    void operator()(Product &p) {
        p.setPrice(p.price() * discount_);
    }

private:
    double discount_;
};

void addDiscountUsingForEach(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Giving all products a discount using for_each()..." << std::endl;
    std::for_each(pl.begin(), pl.end(), DiscountUsingForEach(0.9));
    std::cout << "##################################################" << std::endl;
}


/**
 * Set a discount on all products - Using transform()
 */
struct DiscountUsingTransform {
    DiscountUsingTransform(double discount)
            : discount_(discount) {}

    Product operator()(Product p) {
        p.setPrice(p.price() * discount_);
        return p;
    }

private:
    double discount_;
};

void addDiscountUsingTransform(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Giving all products a discount using transform..." << std::endl;
    std::transform(pl.begin(), pl.end(), std::ostream_iterator<Product>(std::cout, "\n"),
                   DiscountUsingTransform(0.9));
    std::cout << "##################################################" << std::endl;
}


/**
 * Calculate the total amount of sold products
 */
void calcTotalSoldProducts(ProductList &pl) {
    std::vector<unsigned int> v;
    std::transform(pl.begin(), pl.end(), std::back_inserter(v), std::mem_fun_ref(&Product::sold));
    unsigned int total = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "##################################################" << std::endl;
    std::cout << "Total products sold: " << total << std::endl;
    std::cout << "##################################################" << std::endl;
}


/**
 * Setting discount using bind2nd - OPTIONAL
 */
void addDiscountOpt(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Giving all products a discount using binders..." << std::endl;
    std::for_each(pl.begin(), pl.end(), std::bind2nd(std::mem_fun_ref(&Product::setDiscount), 10));
    std::cout << "##################################################" << std::endl;
}


int main() {
    auto running = true;
    ProductList pl;

    while (running) {
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
        std::cout << "'9' Set a discount on all products (using binders()) - OPTIONAL" << std::endl;


        std::cout << "'q' Quit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
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
                addDiscountUsingForEach(pl);
                break;

            case '7':
                addDiscountUsingTransform(pl);
                break;

            case '8':
                calcTotalSoldProducts(pl);
                break;

            case '9':
                addDiscountOpt(pl);
                break;


            case 'q':
            case 'Q':
                running = false;
            default:break;
        }


    }
}
