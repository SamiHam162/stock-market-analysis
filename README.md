# Stock Market Analysis

This project is a C++ application for analyzing stock market data using historical data fetched from Alpha Vantage. It includes functionalities for fetching, processing, and visualizing stock data, as well as testing various components using Google Test.

## Features

- Fetch historical stock data from Alpha Vantage.
- Process and analyze stock data.
- Visualize data using Python's `matplotlib` library.
- Unit tests for data fetching, processing, and prediction.

## Getting Started

### Prerequisites

- CMake
- vcpkg
- A C++ compiler (e.g., GCC, Clang, MSVC)
- Python with `matplotlib` library for plotting

### Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/stock-market-analysis.git
    cd stock-market-analysis
    ```

2. **Install dependencies using `vcpkg`:**

    ```bash
    ./vcpkg install
    ```

3. **Configure and build the project:**

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

4. **Run the application:**

    ```bash
    ./stock_market_analysis
    ```

### Configuration

Edit the `config.json` file to set your API key and other configuration parameters.

### Running Tests

To build and run tests, use the following commands:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
./tests/stock_market_analysis_tests
```

### Contributing

Contributions are welcome! Please open an issue or submit a pull request.

### License

This project is licensed under the MIT License - see the LICENSE file for details.

## Adding Tests

To add new tests:

1. Create a new test file in the `tests` directory.
2. Write your test cases using Google Test.
3. Update the `CMakeLists.txt` file in the `tests` directory to include your new test file.

For more information on Google Test, visit the [Google Test documentation](https://google.github.io/googletest/).