#include <vector>
#include <iostream>
#include <queue>
#include <utility>
#include <unordered_map>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<queue<pair<int, int>>> data(n);
    priority_queue<pair<int, int>> current_queue;
    unordered_map<int, int> visited;
    int first, second, weight;
    for (size_t i = 0; i < m; ++i) {
        cin >> first >> weight >> second;
        data[first-1].push(make_pair(-weight, second-1));
        data[second-1].push(make_pair(-weight, first-1));
    }

    int current_node = 0;
    visited.insert(make_pair(0, 0));
    do {
        while (!data[current_node].empty()) {
            if (visited.find(data[current_node].front().second) == visited.end()) {
                current_queue.push(make_pair(data[current_node].front().first + visited[current_node], data[current_node].front().second));
            }
            data[current_node].pop();
        }
        while (visited.find(current_queue.top().second) != visited.end()) {
            current_queue.pop();
            if (current_queue.empty()) break;
        }
        visited.insert(make_pair(current_queue.top().second, current_queue.top().first));
        current_node = current_queue.top().second;
        current_queue.pop();
    } while (visited.size() != n);
    for (size_t i = 1; i < n; ++i) cout << -visited[i] << " ";
    return 0;
}
