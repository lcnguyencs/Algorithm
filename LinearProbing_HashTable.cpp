#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class LinearProbingHashTable {
private:
    vector<string> table; // declare a table of lists
    const int size = 11; // size of the table = 11

    int hash(const string& key) { // hash function
        int sum = 0;
        for (char c : key) { // loop through the string
            sum += static_cast<int>(c); // sum of ASCII values of characters in the string
        }
        return sum % size;
    }

public:
    LinearProbingHashTable() { 
        table.resize(size); // resize the table to size = 11
    }

    void insert(const string& key) {
        int index = hash(key);
        while (!table[index].empty()) { // if the index is not empty
            index = (index + 1) % size; // increment the index
        }
        table[index] = key; // insert the key into the table
    }

    bool isIndexEmpty(const vector<string>& table, int index) { // check if the index is empty
        return table[index].empty();
    }

    bool search(const string& key) {
        int index = hash(key); 
        int startIndex = index;
        int emptyIndexCount = 0;

        for (int i = 0; i < size; ++i) {
            if (isIndexEmpty(table, index)) { // if the index is empty
                ++emptyIndexCount; // increment the empty index count
            } else if (table[index] == key) { // if the index is not empty and the key is found
                return true; 
            }

            if (emptyIndexCount > 1) { // if the empty index count is greater than 1
                break;
            }

            index = (index + 1) % size; // increment the index
        }

        return false;
    }


    void remove(const string& key) {
        int index = hash(key);
        while (!table[index].empty()) { // if the index is not empty
            if (table[index] == key) { // if the key is found
                table[index].clear(); // clear the key
                return;
            }
            index = (index + 1) % size; // increment the index
        }
    }

};

int main() {
    LinearProbingHashTable Table;

    vector<string> listOfName = {
        "A","B","C","D"};

    for (const string& name : listOfName) {
        Table.insert(name);
    }

    string searchName = "B";

    // Search for a name in the chaining hash table
    if (Table.search(searchName)) {
        cout << "Linear Probing: Found " << searchName << endl;
    } else {
        cout << "Linear Probing: Did not find " << searchName << endl;
    }

    string newName = "X";
    string deleteName = "D";

    // Insert a new name and delete an existing name in the chaining hash table
    Table.insert(newName);
    Table.remove(deleteName);

    // Verify the insertion and deletion in the chaining hash table
    if (Table.search(newName)) {
        cout << "Linear Probing: Found " << newName << " after insertion" << endl;
    } else {
        cout << "Linear Probing: Did not find " << newName << " after insertion" << endl;
    }

    if (!Table.search(deleteName)) {
        cout << "Linear Probing: " << deleteName << " removed successfully" << endl;
    } else {
        cout << "Linear Probing: " << deleteName << " not removed" << endl;
    }

    return 0;
}
