
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    
    // Read the compressed image
    vector<vector<int>> compressed(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> compressed[i][j];
        }
    }
    
    // Create the expanded image (3m x 3n)
    vector<vector<int>> expanded(3 * m, vector<int>(3 * n));
    
    // Fill in the center pixels (positions 1,1 in each 3x3 block)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            expanded[3 * i + 1][3 * j + 1] = compressed[i][j];
        }
    }
    
    // Process each pixel in the expanded image
    for (int i = 0; i < 3 * m; i++) {
        for (int j = 0; j < 3 * n; j++) {
            // Skip center pixels (already filled)
            if (i % 3 == 1 && j % 3 == 1) {
                continue;
            }
            
            // Find A-class and B-class center pixels
            vector<int> a_class; // Manhattan distance = 1
            vector<int> b_class; // Manhattan distance = 2
            
            // Check all center pixels (positions where row%3==1 and col%3==1)
            for (int ci = 0; ci < m; ci++) {
                for (int cj = 0; cj < n; cj++) {
                    int center_i = 3 * ci + 1;
                    int center_j = 3 * cj + 1;
                    
                    // Calculate Manhattan distance
                    int dist = abs(i - center_i) + abs(j - center_j);
                    
                    if (dist == 1) {
                        a_class.push_back(compressed[ci][cj]);
                    } else if (dist == 2) {
                        b_class.push_back(compressed[ci][cj]);
                    }
                }
            }
            
            // Calculate the pixel value based on the rules
            int value;
            if (a_class.empty()) {
                // No A-class: use B-class average
                int sum = 0;
                for (int v : b_class) sum += v;
                value = sum / b_class.size();
            } else if (b_class.empty()) {
                // No B-class: use A-class average
                int sum = 0;
                for (int v : a_class) sum += v;
                value = sum / a_class.size();
            } else {
                // Both exist: A-class average * 0.8 + B-class average * 0.2
                int sum_a = 0, sum_b = 0;
                for (int v : a_class) sum_a += v;
                for (int v : b_class) sum_b += v;
                double avg_a = (double)sum_a / a_class.size();
                double avg_b = (double)sum_b / b_class.size();
                value = (int)(avg_a * 0.8 + avg_b * 0.2);
            }
            
            // Clamp to [0, 100] and assign
            expanded[i][j] = max(0, min(100, value));
        }
    }
    
    // Output the expanded image
    for (int i = 0; i < 3 * m; i++) {
        for (int j = 0; j < 3 * n; j++) {
            cout << expanded[i][j];
            if (j < 3 * n - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
