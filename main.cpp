/**
 * Pranav Srinivasan
 * Quantlab Take Home Assignment
 * 
 * This code takes in an input file in the form of a csv called input.csv. This input
 * represents stock trades and is of the form (time, symbol, quantity price). Using this data
 * the code returns an output csv file of the form symbol, <symbol>,<MaxTimeGap>,<Volume>,
 * <WeightedAveragePrice>,<MaxPrice>.
 * 
 * Code parses using a stringstream and converts into a vector of strings. Then interate through the 
 * vector and map a vector of ints to the symbol as a key. THen calculate values by iterating through the 
 * vector of ints. Finally use an ofstream to output to csv file.
 * 
 * Time Taken 1 hr 30 mins
 * 
 * */



#include <iostream>     
#include <tuple>   
#include <vector>
#include<iterator>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include "parser.h"

using namespace std;

int main(int argc, const char * argv[]) {
	//Inital format spacing
	// cout << "" << endl;
	// cout << "" << endl;
	// cout << "" << endl;

    vector< vector<string> > data_vector = file_to_data("input.csv"); //convert csv to vector

    //Code to print vector
    // for(auto list: data_vector) {
    //     for(auto word: list) {
    //         cout << word << " ";
    //     }

    //     cout << " " << endl;
    // }


    // stock_map = (number of trades, total trade price, max trade price, current time, current max gap)
    //desired output = symbol, max gap, total quantity, max price, weighted average price
    //data_vector = (time, symbol, quantity, price)
    map< string, vector<int> > stockMap;


    //iterate throught data vector 
    for (int i = 0; i < (int)data_vector.size(); i++) {
        //cout << stockMap.count(data_vector[i][1]) << endl;
        if (stockMap.count(data_vector[i][1]) == 0) { //check if first occurences
            vector<int> listStock;
            listStock.push_back(stoi(data_vector[i][2]));
            listStock.push_back(stoi(data_vector[i][3])*stoi(data_vector[i][2]));
            listStock.push_back(stoi(data_vector[i][3]));
            listStock.push_back(stol(data_vector[i][0]));
            //listStock.push_back(stoi(data_vector[i][2]));
            listStock.push_back(0);

            stockMap[data_vector[i][1]] = listStock;
        } else {

            //cout << "here" << endl;
            // if (data_vector[i][1] == "aaa") {
            //     cout << stockMap[data_vector[i][1]][4] << endl;
            // }
            stockMap[data_vector[i][1]][0] += stoi(data_vector[i][2]); // number of trades 
            stockMap[data_vector[i][1]][1] += stoi(data_vector[i][3])*stoi(data_vector[i][2]); // value of trades

            if (stoi(data_vector[i][3]) > stockMap[data_vector[i][1]][2]) { // max trade price
                stockMap[data_vector[i][1]][2] = stoi(data_vector[i][3]);
            }

            if ((stol(data_vector[i][0]) - stockMap[data_vector[i][1]][3]) > stockMap[data_vector[i][1]][4]) { //difference in time 
                stockMap[data_vector[i][1]][4] = (stol(data_vector[i][0]) - stockMap[data_vector[i][1]][3]);
            }

            stockMap[data_vector[i][1]][3] = stol(data_vector[i][0]); // current time


        }
    }

    std::vector<string> keys;
    for(std::map< string, vector<int> >::iterator it = stockMap.begin(); it != stockMap.end(); ++it) {
        keys.push_back(it->first);
        //cout << "Key: " << it->first << endl;
    }

    map< string, vector<int> > output;

    std::ofstream myfile;
    myfile.open("output.csv");

    for (string key: keys) {
        vector<int> oList;
        vector<int> mapList = stockMap[key];
        oList.push_back(mapList[4]);
        oList.push_back(mapList[0]);
        oList.push_back(mapList[2]);
        oList.push_back(mapList[1]/mapList[0]);
        output[key] = oList;
        myfile << key << ",";
        // cout << mapList[1] << ", ";
        // cout << " " << endl;
        int count = 0;
        for (int x: oList) {
            myfile << x;
            if (count < 3) {
                myfile << ",";
            }
            count++;
        }

        myfile << "\n";
    }

    myfile.close();

}