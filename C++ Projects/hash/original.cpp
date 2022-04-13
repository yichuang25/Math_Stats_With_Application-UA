#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
    }
    void print() {
        cout << id << "\t"<< first << "\t" << last << "\t"  << email << "\t"  << phone << "\t"  << city << "\t"  << state << "\t"  << postalCode << endl;
    }

    

};

//create hash table
class HashTable {
private:
    int tableSize;
    vector<Person> *table;
public:
    HashTable(int size) {
        tableSize = size;
        table = new vector<Person>[tableSize];
    }

    int hash(string key) {
        return djb2(key) % tableSize;
    }

    void add(Person person, string key) {
        if(key == "Id") {
            table[hash(person.id)].push_back(person);
        }
        else if(key == "First") {
            table[hash(person.first)].push_back(person);
        }
        else if(key == "Last") {
            table[hash(person.last)].push_back(person);
        }
        else if(key == "Email") {
            table[hash(person.email)].push_back(person);
        }
        else if(key == "Phone") {
            table[hash(person.phone)].push_back(person);
        }
        else if(key == "City") {
            table[hash(person.city)].push_back(person);
        }
        else if(key == "State") {
            table[hash(person.state)].push_back(person);
        }
        else if(key == "PostalCode") {
            table[hash(person.postalCode)].push_back(person);
        }
        
    }

    void print(string key) {
        for (int i = 0; i < tableSize; i++) {
            if(table[i].size() >0) {
                cout << i << ": ";
                if(key=="Id") {
                    vector<string> ids;
                    for (int j = 0; j < table[i].size(); j++) {
                        ids.push_back(table[i][j].id);
                    }
                    vector<string> uniqueIds;
                    for(int k=0;k<ids.size();k++) {
                        if(find(uniqueIds.begin(), uniqueIds.end(), ids[k]) == uniqueIds.end()) {
                            uniqueIds.push_back(ids[k]);
                        }
                    }

                    if(uniqueIds.size() == 1) {
                        cout << uniqueIds[0] << " (1)" << endl;

                    }
                    else {
                        for (int j = 0; j < uniqueIds.size(); j++) {
                            if(j==0) {
                                cout << uniqueIds[j] << " (" << count(ids.begin(), ids.end(), uniqueIds[j]) << ")";
                            }
                            else {
                                cout << ", " << uniqueIds[j] << " (" << count(ids.begin(), ids.end(), uniqueIds[j]) << ")";
                            }
                
                        }
                    }

                }
                

                
                cout << endl;
            }
        }
    }

    void search(string key) {
        int index = hash(key);
        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].id == key) {
                cout << table[index][i].id << " " << table[index][i].first << " " << table[index][i].last << " " << table[index][i].email << " " << table[index][i].phone << " " << table[index][i].city << " " << table[index][i].state << " " << table[index][i].postalCode << endl;
            }
        }
    }

};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    //check for correct number of arguments
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);

    //check if file is open
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    //check validity of key
    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    //create hash table
    HashTable hashTable(tableSize);

    //read file
    int count = 0;
    string line, token;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        string first;
        string last;
        string email;
        string phone;
        string city;
        string state;
        string postalCode;
    
        while (getline(iss, token, '\t')) {
            if (count == 0) {
                id = token;
            }
            else if (count == 1) {
                first = token;
            }
            else if (count == 2) {
                last = token;
            }
            else if (count == 3) {
                email = token;
            }
            else if (count == 4) {
                phone = token;
            }
            else if (count == 5) {
                city = token;
            }
            else if (count == 6) {
                state = token;
            }
            else if (count == 7) {
                postalCode = token;
            }
            count++;
        }
        Person person(id, first, last, email, phone, city, state, postalCode);
        //person.print();
        hashTable.add(person,key);
        count = 0;
    }

    
    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            // print code here
            hashTable.print(key);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }
    
    return 0;
}
