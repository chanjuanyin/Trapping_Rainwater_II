#include "Solution.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int> > readHeightMap(const std::string& filename) {
    vector<vector<int> > heightMap;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return heightMap;
    }

    if (getline(file, line)) {
        // Remove the first and last double square brackets
        line = line.substr(2, line.size() - 4);

        stringstream ss(line);
        string row_data;

        // Split rows
        while (getline(ss, row_data, ']')) {
            // Remove leading '[' and ','
            if (row_data.front() == '[') {
                row_data = row_data.substr(1);
            } else if (row_data.front() == ',') {
                row_data = row_data.substr(2);
            }

            stringstream row_stream(row_data);
            string value;
            vector<int> row;

            // Split values within a row
            while (getline(row_stream, value, ',')) {
                row.push_back(std::stoi(value));
            }

            heightMap.push_back(row);
        }
    }

    file.close();
    return heightMap;
}

int main() {
    vector<vector<int> > heightMap1 = readHeightMap("TestCases/Case1.in");
    vector<vector<int> > heightMap2 = readHeightMap("TestCases/Case2.in");
    vector<vector<int> > heightMap37 = readHeightMap("TestCases/Test37.in");
    Solution s;
    int rainwater1, rainwater2, rainwater37;
    rainwater1 = s.trapRainWater(heightMap1);
    rainwater2 = s.trapRainWater(heightMap2);
    rainwater37 = s.trapRainWater(heightMap37);
    cout << "Total rainwater trapped for Case 1 is: " << rainwater1 << endl;
    cout << "Total rainwater trapped for Case 2 is: " << rainwater2 << endl;
    cout << "Total rainwater trapped for Test Case 37 is: " << rainwater37 << endl;
    return 0;
}
