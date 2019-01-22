#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define p 31
typedef long long int buse;
const buse asal = 1000000007;
using namespace std;
int length;
vector<buse> dicHash;
vector<buse> func;
vector<vector<buse>> hashTable(1001,vector<buse>(1001,-1));
vector<string> dictionary;
string inputString;

buse hashle(string s,int index){
    buse hash = 0;
    if(s.length() > 0 && hashTable[index][s.length() - 1] != -1)
        hashTable[index][s.length()] =(p * hashTable[index][s.length() - 1] + (buse) (inputString.substr(index, s.length())[s.length() - 1] - 97)) % asal;
    else {
        for (int i = 0; i < s.length(); i++) {
            hash = (p * hash + (s[i] - 'a')) % asal;
        }
    }
    return hash;
}

buse hashle2(string s){
    buse hash = 0;
        for (int i = 0; i < s.length(); i++) {
            hash = (p * hash + (s[i] - 'a')) % asal;
        }
    return hash;
}

buse function(int index){
    if(index == length){
        return 1;
    }
    if(func[index]!=-1){
        return func[index];//return func index yaziyordu
    }
    int count = 0;
    for (int i = 0; i <dicHash.size() ; ++i) {

        string word = dictionary[i];
        if(word.length()+index <= inputString.size()+1) {
            string word2 = inputString.substr(index, word.length());
            if (hashTable[index][word.length()] == -1) {
                if(word.length() > 0 && hashTable[index][word.length() - 1] != -1)
                    hashTable[index][word.length()] =(p * hashTable[index][word.length() - 1] + (long long int) (inputString.substr(index, word.length())[word.length() - 1] - 97)) % asal;
                else
                hashTable[index][word.length()] = hashle(word2,index);

            }
            if (dicHash[i] == hashTable[index][word.length()] && word==word2) {
                count = (count + function(index + word.length()))%asal;
            }
        }
    }
    func[index] = count;
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
   //     cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    //cout << "input file: " << argv[1] << endl;
    //cout << "output file: " << argv[2] << endl;
    ifstream inputFile(argv[1]);
    int numOfWords;
    string nextWord;

    inputFile>>inputString;
    inputFile>>numOfWords;
    length = inputString.length();
    func = vector<buse>(length+1,-1);
    dicHash = vector<buse>(numOfWords);
    dictionary = vector<string>(numOfWords);

    for(int i = 0 ; i<numOfWords ;i++){
        inputFile>>nextWord;
        dicHash[i] = (hashle2(nextWord));
        dictionary[i] = nextWord;
    }
    buse result = function(0);
    ofstream myfile;
    myfile.open(argv[2]);
    myfile << result << endl;
    myfile.close();


    return 0;
}
