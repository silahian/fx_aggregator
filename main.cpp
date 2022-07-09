/******************************************************************************

                              C++ Compiler. C++ 14
                              Ariel Silahian
    How technology and automation can help to improve Execution Quality in FX
                
                    Creating a simple FX Aggregator
*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class price_level{
public:
    double price;
    double size;
};

class lob{
public:
    double get_best_offer(){
        return 0;
    }
    double get_best_bid(){
        return 0;
    }

    void AddNewLevel(price_level& pl, bool is_bid){
        if (is_bid){
            bids.push_back(pl);
            std::sort(bids.begin(), bids.end(), [](auto const& l, auto const& r)
            { return l.price > r.price; } ); //DESCENDING
        }
        else{
            offers.push_back(pl);
            std::sort(offers.begin(), offers.end(), [](auto const& l, auto const& r)
            { return l.price < r.price; } ); //ASCENDING
        }
    }
    void DeleteLevel(double price, bool is_bid){
        if (is_bid){
            bids.erase(
                std::remove_if(bids.begin(), bids.end(), [&](auto const & l) {
                    return l.price == price;
                }),
            bids.end());
        }
        else{
            offers.erase(
                std::remove_if(offers.begin(), offers.end(), [&](auto const & l) {
                    return l.price == price;
                }),
            offers.end());
        }
    }
    void UpdateLevel(price_level& pl, bool is_bid){
        vector<price_level>::iterator it;
        if (is_bid){
            it = std::find_if(bids.begin(), bids.end(),
                    [&](auto const &l) {return l.price == pl.price;});
        }
        else{
            it = std::find_if(offers.begin(), offers.end(),
                    [&](auto const &l) {return l.price == pl.price;});
        }
        if (it != bids.end())
        {
            it->price = pl.price;
            it->size = pl.size;
        }
    }
private:
    vector<price_level> bids;
    vector<price_level> offers;
};


class aggregated_lob{
public:
    //METHODS TO HANDLE INDIVIDUAL BOOK METHODS
    void AddNewLevel(int venue_id, price_level& pl, bool is_bid){
        all_books[venue_id].AddNewLevel(pl, is_bid);
    }
    void DeleteLevel(int venue_id, double price, bool is_bid){
        all_books[venue_id].DeleteLevel(price, is_bid);
    }
    void UpdateLevel(int venue_id, price_level& pl, bool is_bid){
        all_books[venue_id].UpdateLevel(pl, is_bid);
    }
    
    
    double get_best_offer(){
        double best_offer;
        for (const lob& b: all_books){
            if (best_offer == 0)
                best_offer = b.get_best_offer();
            else
                best_offer = min(best_offer, b.get_best_offer());
        }
        return best_offer;
    }
    double get_best_bid(){
        double best_bid;
        for (const lob& b: all_books){
            if (best_bid == 0)
                best_bid = b.get_best_bid();
            else
                best_bid = max(best_bid, b.get_best_bid());
        }
        return best_bid;
    }
    
private:
    vector<lob> all_books;
};




int main()
{
    cout<<"Hello World";

    return 0;
}
