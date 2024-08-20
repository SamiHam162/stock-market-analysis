//
// Created by SamiH on 20/08/2024.
//

#include <gtest/gtest.h>
#include "../include/DataFetcher.h"  // Include your DataFetcher header file

class DataFetcherTests : public ::testing::Test {
protected:
    DataFetcher dataFetcher;
};

TEST_F(DataFetcherTests, FetchDataSuccess) {
std::string apiKey = "7YWXXHB280VU6DKX";
std::string symbol = "AAPL";
std::string startDate = "2023-01-01";
std::string endDate = "2023-01-31";

EXPECT_NO_THROW(dataFetcher.fetchHistoricalData(symbol, startDate, endDate));
// Add more assertions based on your fetchData method's expected behavior
}

TEST_F(DataFetcherTests, FetchDataFailure) {
std::string apiKey = "invalid_key";
std::string symbol = "AAPL";
std::string startDate = "2023-01-01";
std::string endDate = "2023-01-31";

EXPECT_THROW(dataFetcher.fetchHistoricalData(symbol, startDate, endDate), std::runtime_error);
// Add more assertions based on expected failure behavior
}