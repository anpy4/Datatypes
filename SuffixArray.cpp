//
// Created by LIGHTNING X-TREME on 24.07.2020.
//

#include "Interfaces.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace SuffixArrays{



    LongestCommonPrefix::LongestCommonPrefix(string str){
        this->s = str;
    }

    string LongestCommonPrefix::getString() {
        return this->s;
    }

    vector<int> LongestCommonPrefix::getSuffixArray() {
        return this->suffixArray;
    }

    string LongestCommonPrefix::getSuffixFromSuffixArray(int idx) {  // works
        int from = idx;
        int range = this->getString().size()-idx;

        return this->getString().substr(from , range);
    }


    struct myComparator{
        bool operator()(const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) {
            // required to sort vector of tuples
            return a.second < b.second;
        }
    };


    void LongestCommonPrefix::buildSuffixArray() {  // works

        vector<pair<int, string>> suffixes;

        int size = this->s.size();

        for (int i=0; i<size; i++){
            suffixes.push_back(make_pair(i, this->s.substr(i, size-i)));
        }

        sort(suffixes.begin(), suffixes.end(), myComparator());

        for (auto a: suffixes){
            this->suffixArray.push_back(a.first);
        }

    }

    vector<int> LongestCommonPrefix::getLcpArray() {
        return this->lcpArray;
    }

    void LongestCommonPrefix::buildLcpArray(){

        if (this->suffixArray.size() == 0) {
            cout << "Build the suffix array before the LCP array can be built!" << endl;
        }
        else{
            this->lcpArray.push_back(0);
            for (int i=1; i<this->suffixArray.size(); i++){
                string prev = this->getSuffixFromSuffixArray(this->suffixArray[i-1]);
                string curr = this->getSuffixFromSuffixArray(this->suffixArray[i]);

                int size = min(prev.size(), curr.size());

                int lcp_val = 0;
                for (int i=0; i<size; i++){
                    if (prev[i] == curr[i]) lcp_val++;
                    else break;
                }

                this->lcpArray.push_back(lcp_val);
            }

        }



    }


    void LongestCommonPrefix::printResult() {  // works

        cout << "Sorted Index        "<<"LCP Value           "<<"Suffix" << "\n\n";

        for (int i=0; i<this->suffixArray.size(); i++){

            string sa = to_string(this->suffixArray[i]);
            for (int j=sa.size(); j<20; j++){
                sa += " ";
            }

            string lcp = to_string(this->lcpArray[i]);
            for (int j=lcp.size(); j<20; j++){
                lcp += " ";
            }

            string suffix = this->getSuffixFromSuffixArray(this->suffixArray[i]);

            cout << sa << lcp << suffix << endl;

        }

    }







    LongestCommonSubstring::LongestCommonSubstring(std::string str, vector<string> stringArray)
            : LongestCommonPrefix(str) {

        for (int i=0; i<stringArray.size(); i++){
            this->s = this->s + stringArray[i] + char(i+33) ;
        }
    }

    vector<int> LongestCommonSubstring::getStringAssignmentArray(){
        return this->stringAssignmentArray;
    }

    void LongestCommonSubstring::assignStringCategory() {

        for (int suffixIndex: this->getSuffixArray()){
            string suffixString = this->getSuffixFromSuffixArray(suffixIndex);

            // count number of chars to assign a string category
            int charSum = 0;
            for (char c: suffixString){
                if (c < 'A') charSum++;
            }

            this->stringAssignmentArray.push_back(charSum);
        }

    }

    void LongestCommonSubstring::printResult(){

        cout << "Sorted Index        "<<"LCP Value           "<<"String              " << "Suffix" <<"\n\n";

        for (int i=0; i<this->suffixArray.size(); i++) {

            string sa = to_string(this->suffixArray[i]);
            for (int j = sa.size(); j < 20; j++) {
                sa += " ";
            }

            string lcp = to_string(this->lcpArray[i]);
            for (int j = lcp.size(); j < 20; j++) {
                lcp += " ";
            }

            string stringAssignment = to_string(this->stringAssignmentArray[i]);
            for (int j = stringAssignment.size(); j < 20; j++) {
                stringAssignment += " ";
            }

            string suffix = this->getSuffixFromSuffixArray(this->suffixArray[i]);


            cout << sa << lcp << stringAssignment << suffix << endl;
        }
    }






}




