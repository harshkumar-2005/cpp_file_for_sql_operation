#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Record {
    int id;
    std::string name;
    int age;
    std::string city;
};

void writeToFile(const std::string &filename, const std::vector<Record> &data) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    file << "ID,Name,Age,City\n"; // Header row
    for (const auto &record : data) {
        file << record.id << "," << record.name << "," << record.age << "," << record.city << "\n";
    }

    file.close();
}

std::vector<Record> readFromFile(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Record> data;

    if (!file) {
        std::cerr << "Error: Unable to open file for reading.\n";
        return data;
    }

    std::string line;
    getline(file, line); // Skip the header
    while (getline(file, line)) {
        std::stringstream ss(line);
        Record record;
        std::string token;

        getline(ss, token, ',');
        record.id = std::stoi(token);

        getline(ss, token, ',');
        record.name = token;

        getline(ss, token, ',');
        record.age = std::stoi(token);

        getline(ss, token, ',');
        record.city = token;

        data.push_back(record);
    }

    file.close();
    return data;
}

void queryByCity(const std::vector<Record> &data, const std::string &city) {
    std::cout << "Records in city: " << city << "\n";
    for (const auto &record : data) {
        if (record.city == city) {
            std::cout << "ID: " << record.id
                      << ", Name: " << record.name
                      << ", Age: " << record.age
                      << ", City: " << record.city << "\n";
        }
    }
}

void insertRecord(std::vector<Record> &data, const Record &newRecord) {
    data.push_back(newRecord);
    std::cout << "Record inserted successfully.\n";
}

void deleteRecordById(std::vector<Record> &data, int id) {
    auto it = std::remove_if(data.begin(), data.end(), [id](const Record &record) { return record.id == id; });
    if (it != data.end()) {
        data.erase(it, data.end());
        std::cout << "Record with ID " << id << " deleted successfully.\n";
    } else {
        std::cout << "No record found with ID " << id << ".\n";
    }
}

void updateRecordById(std::vector<Record> &data, int id, const Record &updatedRecord) {
    for (auto &record : data) {
        if (record.id == id) {
            record = updatedRecord;
            std::cout << "Record with ID " << id << " updated successfully.\n";
            return;
        }
    }
    std::cout << "No record found with ID " << id << ".\n";
}

int main() {
    std::string filename = "data.csv";

    // Sample data
    std::vector<Record> records = {
        {1, "Alice", 25, "New York"},
        {2, "Bob", 30, "Los Angeles"},
        {3, "Charlie", 22, "New York"},
        {4, "Diana", 27, "Chicago"}
    };

    // Write data to file
    writeToFile(filename, records);

    // Read data from file
    std::vector<Record> loadedData = readFromFile(filename);

    // Query data by city
    std::string city;
    std::cout << "Enter city to query: ";
    std::cin >> city;
    queryByCity(loadedData, city);

    // Perform insert operation
    Record newRecord = {5, "Eve", 35, "Miami"};
    insertRecord(loadedData, newRecord);

    // Perform delete operation
    int deleteId;
    std::cout << "Enter ID to delete: ";
    std::cin >> deleteId;
    deleteRecordById(loadedData, deleteId);

    // Perform update operation
    int updateId;
    Record updatedRecord = {2, "Bob Updated", 32, "San Francisco"};
    std::cout << "Enter ID to update: ";
    std::cin >> updateId;
    updateRecordById(loadedData, updateId, updatedRecord);

    // Write updated data back to file
    writeToFile(filename, loadedData);

    return 0;
}
