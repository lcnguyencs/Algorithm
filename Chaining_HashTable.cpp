#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class ChainingHashTable {
    private:
        vector<list<string>> table; // declare a table of lists
        const int size = 11; // size of the table

        int hash(string& key) { // hash function
            int sum = 0;   
            for (int i = 0; i < key.length(); i++) { // loop through the string
                sum += static_cast<int>(key[i]);   // sum of ASCII values of characters in the string
            }  
            return sum % size; 
        }

    public:
        ChainingHashTable() {
            table.resize(size);  // resize the table to size = 11
        }

        void insert(string& key) {
            int index = hash(key); // get the index of the table
            table[index].push_back(key);  // insert the key into the table
        }

        bool search(string& key) {
            int index = hash(key); // get the index of the table
            for (string& item : table[index]) { // loop through the list at the index
                if (item == key) {
                    return true;
                }
            }
            return false;
        }

        void remove(string& key) {
            int index = hash(key); // get the index of the table
            table[index].remove(key); // remove the key from the list at the index
        }
};

int main() {
    ChainingHashTable Table;
    

    vector<string> listOfName = { 
        "A","B","C","D"};

    for (string& name : listOfName) { // insert the names into the chaining hash table
        Table.insert(name); 
    }

    string searchName = "B";

    // Search for a name in the chaining hash table
    if (Table.search(searchName)) {
        cout << "Chaining: Found " << searchName << endl;
    } else {
        cout << "Chaining: Did not find " << searchName<< endl;
    }


    string newName = "X";
    string deleteName = "D";

    // Insert a new name and delete an existing name in the chaining hash table
    Table.insert(newName);
    Table.remove(deleteName);


    // Verify the insertion and deletion in the chaining hash table
    if (Table.search(newName)) {
        cout << "Chaining: Found " << newName << " after insertion" << endl;
    } else {
        cout << "Chaining: Did not find " << newName << " after insertion" << endl;
    }

    if (!Table.search(deleteName)) {
        cout << "Chaining: " << deleteName << " removed successfully" << endl;
    } else {
        cout << "Chaining: " << deleteName << " not removed" << endl;
    }

    return 0;
}