// Workshop - Multi-threading
// TreasureMap.cpp


/*
*****************************************************************************
                  Workshop - #9 (P2)
Full Name   : Yuchi Zheng
Email       : andyzheng.ca@gmail.com
Date        : 25th, November, 2022

* ****************************************************************************
*/

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <string>
#include <vector>
#include <functional>
#include "TreasureMap.h"

namespace sdds{

    size_t digForTreasure(const std::string& str, char mark){
        size_t cnt = 0;
        for (auto& x : str){
            if (x == mark){
                cnt++;
            }
        }
        return cnt;
    }

    TreasureMap::TreasureMap(const char* filename){
        std::fstream fin(filename);
        if (fin){
            fin >> rows;
            fin.ignore();//ignore colSizes
            map = new std::string[rows];
            size_t idx = 0;
            while(fin){
                getline(fin, map[idx]);
                idx++;
            }
            colSize = map[0].length();
        }
        else {
            throw std::string(filename) + " cannot be opened";
        }
    }

    TreasureMap::~TreasureMap(){
        delete [] map;
    }

    std::ostream& TreasureMap::display(std::ostream& os) const{
        if (map){
            for (size_t i = 0; i < rows; ++i){
                os << map[i] << std::endl;
            }
        }
        else 
            os << "The map is empty!" << std::endl;
        return os;
    }

    void TreasureMap::enscribe(const char* filename){
        // Binary write
        if (map){
            // TODO: Open a binary file stream to the filename and
            //       then write the row number to the binary file 
            //       then each of the rows of the map.
            //       If the file cannot be open, raise an exception to
            //       inform the client.
           std::ofstream oFile(filename, std::ios::binary);

           if (oFile) {
              oFile.write((const char*)&rows, sizeof(rows));//sizeof(size_t)
              oFile.write((const char*)&colSize, sizeof(colSize));

              for (size_t i = 0; i < rows; i++) {
                 oFile.write((const char*)(map[i].c_str()), colSize);//sizeof(char) is 1
                 /*method2:
                 oFile.write((const char*)(&(map[i][0])), colSize * sizeof(char));*/
                 
                 /*method3:
                 size_t len = map[i].length();
                 oFile.write((const char*)&len, sizeof(size_t));
                 sizeof(map[i][0]) is a char, 1 byte. Do not use sizeof(std::string), because length is unkow
                 oFile.write((const char*)(&(map[i][0])), map[i].length() * sizeof(map[i][0]));*/
              } 
              oFile.close();
           }
           else {
              throw std::string("File can't be open!");
           }
            // END TODO
        }
        else{
            throw std::string("Treasure map is empty!");
        }
    }

    void TreasureMap::recall(const char* filename){
        // Binary read
        // TODO: Open a binary file stream to the filename
        //       and read from it to populate the current object.
        //       The first 4 bytes of the file will be the number of rows
        //       for the map followed another 4 bytes for the colSize
        //       of each row in the map.
        //       Afterwards is each row of the map itself.
        //       If the file cannot be open, raise an exception to inform
        //       the client.
       std::ifstream iFile(filename, std::ios::binary);

       if (iFile) {
          iFile.read((char*)&rows, sizeof(rows));//size_t = 4, sizeof(size_t), dont use 4 because it could be changed by platform
          iFile.read((char*)&colSize, sizeof(colSize));

          delete[] map;
          map = new std::string[rows];
          for (size_t i = 0; i < rows; i++) {
             map[i].resize(colSize);
             iFile.read((char*)(map[i].c_str()), colSize);//not map[i].length()£¬ because it may not be read   
             //iFile.read((char*)(&(map[i][0])), map[i].length());//map[i].length()  colSize

             /*size_t len = colSize * sizeof(char);
             char* temp = new char[len + 1];

             iFile.read(temp, len);
             temp[len] = '\0';
             map[i] = temp;
             delete[] temp;*/
          }
          iFile.close();
       }
       else {
          throw std::string("File can't be open!");
       }
        // END TODO
    }

    void TreasureMap::clear(){
        delete [] map;
        map = nullptr;
        rows = 0;
        colSize = 0;
    }

    size_t TreasureMap::findTreasure(char mark){
        size_t count = 0;
        // TODO: For part 2, comment this "for" loop and write the multihreaded version.
        /*for (size_t i = 0; i < rows; ++i){
            count += digForTreasure(map[i], mark);
        }*/

        // seperate map data
        std::vector<std::string> strArr;// str1, str2, str3, str4
        size_t numThreads{ 4 }, aveLength{};
        std::string totalStr{};
        
        for (size_t i = 0; i < rows; i++) {
           totalStr += map[i];
        }
        aveLength = totalStr.length() / numThreads;

        for (size_t i = 0; i < numThreads; i++) {
           std::string temp = totalStr.substr(i * aveLength, aveLength);
           strArr.push_back(temp);   
        }
        
        //bind
        auto func = std::bind(digForTreasure, std::placeholders::_1, mark);//std::placeholders::_1, std::placeholders::_2

        //provider:package_task
        std::packaged_task<size_t(std::string)> pt1(func);//return size_t
        std::packaged_task<size_t(std::string)> pt2(func);
        std::packaged_task<size_t(std::string)> pt3(func);
        std::packaged_task<size_t(std::string)> pt4(func);
        //std::packaged_task<size_t(std::string, char)> pt4(func); //or keep char

        //future:
        auto f1 = pt1.get_future();
        auto f2 = pt2.get_future();
        auto f3 = pt3.get_future();
        auto f4 = pt4.get_future();

        //thread
        std::thread t1(std::move(pt1), strArr[0]);
        std::thread t2(std::move(pt2), strArr[1]);
        std::thread t3(std::move(pt3), strArr[2]);
        std::thread t4(std::move(pt4), strArr[3]);
        //std::thread t4(std::move(pt4), strArr[3], mark); //or keep mark

        count = f1.get() + f2.get() + f3.get() + f4.get();

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        return count;
    }
}
