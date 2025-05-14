//
//  main.cpp
//  Assignment 6
//
//  Created by Kevin Chavez on 5/13/25.
//

#include <iostream>
#include <vector>

#define TABLE_SIZE 907

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> isOccupied;
    std::vector<bool> isDeleted;

public:
    HashTable() : table(TABLE_SIZE, -1),
                 isOccupied(TABLE_SIZE, false),
                 isDeleted(TABLE_SIZE, false) {}

    // Hash function: key mod table size
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    // Insert a key into the hash table
    int HashInsertion(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (isOccupied[index]) {
            if (table[index] == key && !isDeleted[index]) {
                std::cout << "Key " << key << " already exists in the table." << std::endl;
                return -1; // Key already exists
            }
            
            // Linear probing: hash(K) + i
            i++;
            index = (originalIndex + i) % TABLE_SIZE;

            if (index == originalIndex) {
                std::cout << "Hash table is full!" << std::endl;
                return -1; // Table is full
            }
        }

        // Insert the key
        table[index] = key;
        isOccupied[index] = true;
        isDeleted[index] = false;
        return index;
    }

    // Delete a key from the hash table
    int HashDeletion(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (isOccupied[index] || isDeleted[index]) {
            if (table[index] == key && !isDeleted[index]) {
                isDeleted[index] = true;
                isOccupied[index] = false;
                std::cout << "Key " << key << " deleted from index " << index << std::endl;
                return index;
            }

            // Linear probing: hash(K) + i
            i++;
            index = (originalIndex + i) % TABLE_SIZE;

            if (index == originalIndex) {
                break; // Wrapped around to starting index
            }
        }

        std::cout << "Key " << key << " not found in the table." << std::endl;
        return -1; // Key not found
    }

    // Search for a key in the hash table
    int HashSearch(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        while (isOccupied[index] || isDeleted[index]) {
            if (table[index] == key && !isDeleted[index]) {
                return index;
            }

            // Linear probing: hash(K) + i
            i++;
            index = (originalIndex + i) % TABLE_SIZE;

            if (index == originalIndex) {
                break; // Wrapped around to starting index
            }
        }

        return -1; // Key not found
    }

    // Display the hash table
    void display() {
        std::cout << "Hash Table Contents:" << std::endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (isOccupied[i] && !isDeleted[i]) {
                std::cout << "Index " << i << ": " << table[i] << std::endl;
            }
        }
    }
};

int main() {
    HashTable ht;

    // Test insertion
    std::cout << "Inserting keys..." << std::endl;
    ht.HashInsertion(1000);  // 1000 % 907 = 93
    ht.HashInsertion(1907);  // 1907 % 907 = 93 (collision)
    ht.HashInsertion(2814);  // 2814 % 907 = 93 (collision)
    ht.HashInsertion(500);
    ht.HashInsertion(500);   // Duplicate insertion

    // Test search
    std::cout << "\nSearching for keys..." << std::endl;
    int searchKey = 1907;
    int foundIndex = ht.HashSearch(searchKey);
    if (foundIndex != -1) {
        std::cout << "Key " << searchKey << " found at index " << foundIndex << std::endl;
    } else {
        std::cout << "Key " << searchKey << " not found." << std::endl;
    }

    // Test deletion
    std::cout << "\nDeleting keys..." << std::endl;
    ht.HashDeletion(1907);
    ht.HashDeletion(9999);  // Non-existent key

    // Verify deletion by searching again
    std::cout << "\nSearching after deletion..." << std::endl;
    foundIndex = ht.HashSearch(1907);
    if (foundIndex != -1) {
        std::cout << "Key " << searchKey << " found at index " << foundIndex << std::endl;
    } else {
        std::cout << "Key " << searchKey << " not found." << std::endl;
    }

    // Display the hash table
    std::cout << "\nFinal hash table contents:" << std::endl;
    ht.display();

    return 0;
}
