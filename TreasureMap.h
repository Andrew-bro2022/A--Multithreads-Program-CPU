// Workshop  - Multi-threading
// TreasureMap.h

/*
*****************************************************************************
                  Workshop  (P2)
Full Name   : Yuchi Zheng
Email       : andyzheng.ca@gmail.com
Date        : 25th, November, 2022

* ****************************************************************************
*/


#ifndef SDDS_TREASUREMAP_H
#define SDDS_TREASUREMAP_H

#include <cstddef>
#include <iostream>
#include <string>

namespace sdds{

    size_t digForTreasure(const std::string& str, char mark);

    class TreasureMap{
        size_t rows = 0;
        size_t colSize = 0;
        std::string* map = nullptr;
    public:
        TreasureMap(const char* filename);
        ~TreasureMap();

        std::string operator[](int i) const{
            return map[i % rows];
        }

        size_t size() const{
            return rows;
        }

        std::ostream& display(std::ostream& os) const;
        void enscribe(const char* filename); 
        void recall(const char* filename);
        void clear();

        size_t findTreasure(char mark);
    };

}

#endif
