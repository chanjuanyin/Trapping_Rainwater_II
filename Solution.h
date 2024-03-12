#include "HeapSort.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int> >& heightMap);
    int calculate_trapped_water_at_level(vector<vector<int> >& heightMap, vector<vector<int> >& grid_of_records, 
                                         int num_rows, int num_columns, int level_current, int level_previous);
};
