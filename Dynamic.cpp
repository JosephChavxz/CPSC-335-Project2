//Joseph Chavez jchavez0026@csu.fullerton.edu
//CPSC 335 Ornella Dsouza 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int max_stocks(int N, const std::vector<std::pair<int, int>>& Stocks_and_values, int amount) {
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(amount + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= amount; j++) {
            if (Stocks_and_values[i - 1].second <= j) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - Stocks_and_values[i - 1].second] + Stocks_and_values[i - 1].first);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[N][amount];
}

int main() {

    std::ifstream file("test_cases.txt");
    std::string line;
    int N, amount;
    std::vector<std::pair<int, int>> Stocks_and_values;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        int result = max_stocks(N, Stocks_and_values, amount);
        std::cout << "\nThe maximum amount of stocks that can be purchased with the current allowance from the list of stocks is: " << result << "\n";
        std::cout << "\n----------------------------------\n";
    }

    return 0;
}
