//Joseph Chavez jchavez0026@csu.fullerton.edu
//CPSC 335 Ornella Dsouza 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

void verify_combinations(int M, const std::vector<int>& candidate_items, const std::vector<int>& values, const std::vector<int>& stock, 
                         std::vector<int>& working_stock, std::vector<std::vector<int>>& working_combos, std::vector<int>& working_values) {
    int total_price = 0;
    int total_stock = 0;

    for (int item : candidate_items) {
        auto it = std::find(stock.begin(), stock.end(), item);
        if (it != stock.end()) {
            int location = std::distance(stock.begin(), it);
            total_price += values[location];
            total_stock += item;
        } else {
            return; 
        }
    }

    if (total_price <= M) {
        working_combos.push_back(candidate_items);
        working_stock.push_back(total_stock);
        working_values.push_back(total_price);
    }
}

void generate_combinations(const std::vector<int>& stock, std::vector<int>& temp, int start, int end, 
                           int index, int r, std::vector<std::vector<int>>& combinations) {
    if (index == r) {
        combinations.push_back(temp);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        temp[index] = stock[i];
        generate_combinations(stock, temp, i + 1, end, index + 1, r, combinations);
    }
}

int stock_maximization(int M, const std::vector<int>& values, const std::vector<int>& stock) {
    std::vector<int> working_stock;
    std::vector<std::vector<int>> working_combos;
    std::vector<int> working_values;
    int best = -1;

    std::vector<std::vector<int>> possible_combos;

    for (int r = 1; r <= stock.size(); r++) {
        std::vector<int> temp(r);
        generate_combinations(stock, temp, 0, stock.size() - 1, 0, r, possible_combos);
    }

    for (auto& candidate : possible_combos) {
        verify_combinations(M, candidate, values, stock, working_stock, working_combos, working_values);
    }

    for (int i = 0; i < working_combos.size(); i++) {
        if (best == -1 || working_values[i] < working_values[best] || working_stock[i] > working_stock[best]) {
            best = i;
        }
    }

    return best != -1 ? working_stock[best] : 0;
}

int main() {
    std::ifstream file("test_cases.txt");
    std::string line;
    int N, Amount;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> N;

        std::vector<int> stock(N), values(N);
        for (int i = 0; i < N; ++i) {
            ss.clear();
            std::getline(file, line);
            ss.str(line);
            ss >> stock[i] >> values[i];
        }

        ss.clear();
        std::getline(file, line);
        ss.str(line);
        ss >> Amount;

        int max_stock = stock_maximization(Amount, values, stock);
        std::cout << "The maximum amount of stocks that can be purchased with the current allowance from the list of stocks is: " << max_stock << std::endl;
    }

    return 0;
}