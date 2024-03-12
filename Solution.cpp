#include "Solution.h"

using namespace std;

int Solution::trapRainWater(vector<vector<int> >& heightMap) {
    int num_rows = heightMap.size();
    int num_columns = heightMap[0].size();
    HeapSort heapSort;

    // Creating color cells
    vector<vector<int> > grid_of_records(num_rows, vector<int>(num_columns, 0));
    // 0 means white cells
    // 1 means green cells (current boundaries)
    // 2 means red cells (popped cells)
    
    // Setting initial green cells
    for (int i=0; i<num_rows; i++) {
        if (grid_of_records[i][0]==0) {
            grid_of_records[i][0] = 1;
            heapSort.Add(heightMap[i][0], i, 0);
        }
        if (grid_of_records[i][num_columns - 1]==0) {
            grid_of_records[i][num_columns - 1] = 1;
            heapSort.Add(heightMap[i][num_columns - 1], i, num_columns - 1);
        }
    }
    for (int i=0; i<num_columns; i++) {
        if (grid_of_records[0][i]==0) {
            grid_of_records[0][i] = 1;
            heapSort.Add(heightMap[0][i], 0, i);
        }
        if (grid_of_records[num_rows - 1][i]==0) {
            grid_of_records[num_rows - 1][i] = 1;
            heapSort.Add(heightMap[num_rows - 1][i], num_rows - 1, i);
        }
    }

    int total = 0;
    int level_previous = 0;
    int level_current = 0;

    while (heapSort.get_number_of_nodes() > 0) {
        // cout << heapSort.Peep()[0] << " " << heapSort.Peep()[1] << " " << heapSort.Peep()[2] << endl;
        if (heapSort.Peep()[0] > level_current) {
            level_previous = level_current;
            level_current = heapSort.Peep()[0];
            total += calculate_trapped_water_at_level(heightMap, grid_of_records, num_rows, num_columns, level_current, level_previous);
        }
        queue<vector<int> > q;
        vector<int> v = heapSort.Pop();
        grid_of_records[v[1]][v[2]] = 2; // set it to a red cell
        q.push(v);
        while (!q.empty()) {
            v = q.front();
            q.pop();
            if (v[1]-1>=0 && grid_of_records[v[1]-1][v[2]]==0) { // if the adjacent is a white cell
                if (heightMap[v[1]-1][v[2]] <= level_current) { // if the adjacent cannot be a new boundary
                    grid_of_records[v[1]-1][v[2]] = 2; // set it to a red cell
                    vector<int> vvv;
                    vvv.push_back(heightMap[v[1]-1][v[2]]);
                    vvv.push_back(v[1]-1);
                    vvv.push_back(v[2]);
                    q.push(vvv);
                }
                else { // heightMap[v[1]-1][v[2]] > level_current // the adjacent can be a new boundary
                    grid_of_records[v[1]-1][v[2]] = 1; // set it to a green cell
                    heapSort.Add(heightMap[v[1]-1][v[2]], v[1]-1, v[2]);
                }
            }
            if (v[1]+1 < num_rows && grid_of_records[v[1]+1][v[2]]==0) { // if the adjacent is a white cell
                if (heightMap[v[1]+1][v[2]] <= level_current) { // if the adjacent cannot be a new boundary
                    grid_of_records[v[1]+1][v[2]] = 2; // set it to a red cell
                    vector<int> vvv;
                    vvv.push_back(heightMap[v[1]+1][v[2]]);
                    vvv.push_back(v[1]+1);
                    vvv.push_back(v[2]);
                    q.push(vvv);
                }
                else { // heightMap[v[1]+1][v[2]] > level_current // the adjacent can be a new boundary
                    grid_of_records[v[1]+1][v[2]] = 1; // set it to a green cell
                    heapSort.Add(heightMap[v[1]+1][v[2]], v[1]+1, v[2]);
                }
            }
            if (v[2]-1>=0 && grid_of_records[v[1]][v[2]-1]==0) { // if the adjacent is a white cell
                if (heightMap[v[1]][v[2]-1] <= level_current) { // if the adjacent cannot be a new boundary
                    grid_of_records[v[1]][v[2]-1] = 2; // set it to a red cell
                    vector<int> vvv;
                    vvv.push_back(heightMap[v[1]][v[2]-1]);
                    vvv.push_back(v[1]);
                    vvv.push_back(v[2]-1);
                    q.push(vvv);
                }
                else { // heightMap[v[1]][v[2]-1] > level_current // the adjacent can be a new boundary
                    grid_of_records[v[1]][v[2]-1] = 1; // set it to a green cell
                    heapSort.Add(heightMap[v[1]][v[2]-1], v[1], v[2]-1);
                }
            }
            if (v[2]+1 < num_columns && grid_of_records[v[1]][v[2]+1]==0) { // if the adjacent is a white cell
                if (heightMap[v[1]][v[2]+1] <= level_current) { // if the adjacent cannot be a new boundary
                    grid_of_records[v[1]][v[2]+1] = 2; // set it to a red cell
                    vector<int> vvv;
                    vvv.push_back(heightMap[v[1]][v[2]+1]);
                    vvv.push_back(v[1]);
                    vvv.push_back(v[2]+1);
                    q.push(vvv);
                }
                else { // heightMap[v[1]][v[2]+1] > level_current // the adjacent can be a new boundary
                    grid_of_records[v[1]][v[2]+1] = 1; // set it to a green cell
                    heapSort.Add(heightMap[v[1]][v[2]+1], v[1], v[2]+1);
                }
            }
        }
    }

    return total;
}

int Solution::calculate_trapped_water_at_level(vector<vector<int> >& heightMap, vector<vector<int> >& grid_of_records, 
                                         int num_rows, int num_columns, int level_current, int level_previous) {
    int total = 0;
    for (int i=0; i<num_rows; i++) {
        for (int j=0; j<num_columns; j++) {
            if (grid_of_records[i][j]==0) { // if white cell
                total += max(min(level_current - heightMap[i][j], level_current - level_previous), 0);
            }
        }
    }
    // cout << total << endl;
    return total;
}
