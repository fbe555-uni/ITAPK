/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

#include <fstream>
#include <iostream>
#include <iterator>

#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <string>


#define PRODUCT_DB_FILE		"product.db"

class Product
{
public:
  Product(const std::string& name, float price, unsigned int sold = 0)
    : name_(name), price_(price), sold_(sold)
  {}
  Product()
    : name_(""), price_(0), sold_(0)
  {}
  
  const std::string& name() const
  {
    return name_;
  }
  
  float price() const
  {
    return price_;
  }

  void setPrice(float newPrice)
  {
    price_ = newPrice;
  }
  
  unsigned int sold() const
  {
    return sold_;
  }
  
  friend std::istream& operator>> ( std::istream& i, Product& p );
  friend std::ostream& operator<< ( std::ostream& o, const Product& p );
  
private:
  std::string   name_;
  float         price_;
  int           sold_;
};
typedef std::vector<Product>  ProductList;


std::ostream& operator<< ( std::ostream& o, const Product& p )
{ 
  return o << p.name_ << " " << p.price_ << " " << p.sold_; 
}

std::istream& operator>> ( std::istream& i, Product& p )
{
    return i >> p.name_ >> p.price_ >> p.sold_;
}



/**
 * Read products from file
 */
void productDBRead(ProductList& pl, const std::string& fileName)
{
  pl.clear();
  std::ifstream pFile( fileName.c_str() );
  while( !pFile.eof() )
  {
    Product p;
    pFile >> p;
    if( pFile ) pl.push_back( p );
  }
}


/**
 * Printout all products
 */
void printAll(const ProductList& pl)
{
  std::cout << "##################################################" << std::endl;
  std::cout << "Printing out all products..." << std::endl;
  std::cout << "----------------------------" << std::endl;
  for(ProductList::const_iterator iter = pl.begin(); iter != pl.end(); ++iter)
  {
    std::cout << *iter << std::endl;
  }  
  std::cout << "##################################################" << std::endl;
}



/**
   Add item
*/
void addItem(ProductList& pl)
{
}


/**
   Write data to db file
*/
void productDBWrite(const ProductList& pl, const std::string& fileName)
{
}


/**
 * Print poorly selling products
 */
void printPoorlySellingProducts(const ProductList& pl)
{
}


/**
 * Set a discount on all products - Using for_each()
 */
void addDiscountUsingForEach(ProductList& pl)
{
}


/**
 * Set a discount on all products - Using transform()
 */
void addDiscountUsingTransform(ProductList& pl)
{
}


/**
 * Calculate the total amount of sold products
 */
void calcTotalSoldProducts(ProductList& pl)
{
}


/**
 * Setting discount using bind2nd - OPTIONAL
 */


