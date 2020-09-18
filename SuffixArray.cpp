//
// Created by LIGHTNING X-TREME on 24.07.2020.
//

#include "Interfaces.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

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

    void LongestCommonSubstring::assignStringCategory() {  // works

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

    void LongestCommonSubstring::printResult(){  // works

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

    void LongestCommonSubstring::calculate_lcs(int k_common) {  // works

        unordered_map<int, int> category_map;
        unordered_set<string> lcs;
        int lcs_length = 0;

        int window_start = 0 , window_end = 0;
        int k_curr = 0;
        int tmp_lcp_length;


        while (window_start < this->lcpArray.size()){



            // adjust window size and update the category-counter-map
            if (k_curr < k_common){
                // increase window size

                if (window_end == this->lcpArray.size()) break; // stopping criteria

                int cat_count_in_window = category_map[this->stringAssignmentArray[window_end]];
                cat_count_in_window++;
                category_map[this->stringAssignmentArray[window_end]] = cat_count_in_window;
                window_end++;
            }

            else{
                // decrease window size
                category_map[this->stringAssignmentArray[window_start]]--;
                window_start++;
            }


            // count current number of different colors
            k_curr = 0;
            for (auto i = category_map.begin(); i != category_map.end(); i++){
                if (i->second > 0) k_curr++;
            }

            // if enough colors are present, get the smallest value of this lcp subarray
            if (k_curr >= k_common){

                tmp_lcp_length = 2147483627;
                for (int i=window_start+1; i<window_end; i++){
                    tmp_lcp_length = min(tmp_lcp_length, this->lcpArray[i]);
                }

                // is tmp result the best one?
                if (tmp_lcp_length > lcs_length){
                    lcs.clear();
                    string tmp =  this->getSuffixFromSuffixArray(this->suffixArray[window_start]);
                    lcs.insert(tmp.substr(0,tmp_lcp_length));
                    lcs_length = tmp_lcp_length;
                }
                // is tmp result as good as the best one?
                else if (tmp_lcp_length == lcs_length){
                    string tmp =  this->getSuffixFromSuffixArray(this->suffixArray[window_start]);
                    lcs.insert(tmp.substr(0,tmp_lcp_length));
                }
                // is tmp result worse than the best one?
                // do nothing
            }
        }

        cout << "\n\nLongest common substring: " << lcs_length << endl;
        for (const string &x : lcs) {
            cout << x << "  ";
        }

    }








    LongestRepeatedSubstring::LongestRepeatedSubstring(std::string str) : LongestCommonPrefix(str){
        this->s = str;
    }

    void LongestRepeatedSubstring::get_LRS() {
        int max_lcp_value = 0;
        unordered_set<string> res;

        for (int i=0; i<this->lcpArray.size(); i++){
            if (this->lcpArray[i] > max_lcp_value){
                res.clear();
                max_lcp_value = this->lcpArray[i];
                string tmp = this->getSuffixFromSuffixArray(this->suffixArray[i]);
                res.insert(tmp.substr(0,max_lcp_value));
            }
            else if (this->lcpArray[i] == max_lcp_value){
                string tmp = this->getSuffixFromSuffixArray(this->suffixArray[i]);
                res.insert(tmp.substr(0,max_lcp_value));
            }
        }

        cout << "\n\nLongest repeated substring: " << max_lcp_value << endl;
        for (const string &x : res) {
            cout << x << "  ";
        }


    }




}




