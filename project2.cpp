#include <iostream>
using std::cout; using std::endl; using std::cin;
#include <fstream>
using std::ifstream; using std::ofstream;
#include <unordered_map>
using std::unordered_map;
#include <unordered_set>
using std::unordered_set;
#include <string>
using std::string; using std::getline;
#include <sstream>
using std::ostringstream;


// YOUR FUNCTIONS HERE
void OpenFile(ifstream &in_file, string &input){
    in_file.open(input);
    
    if (!in_file.is_open()) {
        std::cerr << "Error: Cannot open '" << input << "'." << endl;
        std::exit(1);
    }
}

void ReadEncodingPairs(string &in, unordered_map<char, char> &encript){
    if (in.length() == 2){
        if(encript.insert({in.at(0), in.at(1)}).second == false){
            std::cerr << "Error: The character '" << in.at(0) << "' is encoded as both '" << encript[in.at(0)] << "' and '" << in.at(1) << "'." << endl;
            std::exit(1);
        }
    } else{
        std::cerr << "Error: Unknown encoding '" << in << "'." << endl;
        std::exit(1);
    }
    
}

void ApplyEncoding(string &line,string &encripted, const unordered_map<char, char> &encript){
    for (auto i = line.begin(); i != line.end(); ++i){ 
        if (encript.find(*i) != encript.end()){
            encripted += (encript.find(*i))->second;
        } else {
            encripted += *i;
        }
    }
}

string ProcessFile(ifstream &in_file, const unordered_map<char, char> &encript){
    ostringstream oss;
    string line;
    unordered_set <string> final;
    while (getline(in_file, line)){
        string encripted = "";
        ApplyEncoding(line, encripted, encript);
        int count = final.count(encripted);
        if (count == 0) {
            oss << encripted << endl;
            final.insert(encripted);
        }
    }
    return oss.str();
}

int main() {
    string input;

    cin >> input;
    ifstream in_file;
    OpenFile(in_file, input);
    
    
    unordered_map<char, char> encription;
    while (cin >> input){
        if (input == "q"){
            break;
        }
        ReadEncodingPairs(input, encription);
    }

    cout << ProcessFile(in_file, encription);

    return 0;
}



//echo example.txt aq bw ce dr et fy gu hi io jp ka ls md nf og ph qj rk sl tz ux vc wv xb yn zm | ./proj2.exe
//g++ -Wall -Wextra -Werror -o proj2.exe project2.cpp 