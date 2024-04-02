/*
    Exercise 7.20: When are friends useful? Discuss the pros and cons of using friends.
*/

#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <ostream>
using std::cout, std::cin, std::endl, std::string,  std::vector, std::begin, std::end, std::runtime_error, std::istream, std::ostream;

class Sales_data
{   
    //Friendships
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend istream &read(istream&, Sales_data&); //Read I made changes based on the combine function to get it to compile earlier
    friend ostream &print(ostream&, const Sales_data&); //I made public facing functions to return values, but this is easier

    public:
    Sales_data() = default; //I did this already in a previous exercise
    Sales_data(const string &s): bookNum(s) {}
    Sales_data(const string &s, unsigned n, double p): bookNum(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &is);

    //public facing function to perform a task
    Sales_data& combine(const Sales_data&);

    private:
    double avg_price() const { return units_sold ? revenue/units_sold : 0; };
    string bookNum = "0-000-00000-X";    
    unsigned units_sold = 0;
    double revenue = 0.0;

    
};

Sales_data::Sales_data(std::istream &is) 
{
    read(is, *this);
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream& read(istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNum >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

double Sales_data::avg_price() const 
{
    if (units_sold)
    {
        return revenue/units_sold;
    }
    else
    {
        return 0;
    }
}

Sales_data add(const Sales_data &item1, const Sales_data &item2)
{
    Sales_data added = item1;
    added.combine(item2);
    return added;
}

ostream &print(ostream &os, const Sales_data &item)
{
    //I originally added functions to return values within the public facing portion of the object
    //os << item.isbn() << " " << item.sales() << " " << item.income();
    
    //But you can make the function a friend, which will allow the use of private properties
    os << item.bookNum << " " << item.units_sold << " " << item.revenue;

    //This is useful for keeping code more streamline
    //However, since friendships are not ordinary declarations, you may need to add code to call them
    //This is still advantageous compared to making a new function/functions that require public properties
    //The biggest drawback of using friendships is compilers may treat them differently

    return os;
}