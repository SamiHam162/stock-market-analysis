cmake_minimum_required(VERSION 3.25)
project(stock_market_analysis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Find required packages
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(gtest REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
# Include the include directory
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find Python3 and NumPy
# Specify Python version and paths manually
set(PYTHON_VERSION 311)  # Adjust according to your Python version
set(PYTHON_INCLUDE_DIR "C:/Users/SamiH/AppData/Local/Programs/Python/Python${PYTHON_VERSION}/include")
set(PYTHON_LIBRARY "C:/Users/SamiH/AppData/Local/Programs/Python/Python${PYTHON_VERSION}/libs/python${PYTHON_VERSION}.lib")

# Include Python headers
include_directories(${PYTHON_INCLUDE_DIR})

# Include directories

include_directories("C:\\Users\\SamiH\\AppData\\Local\\Programs\\Python\\Python311\\Lib\\site-packages\\numpy\\core\\include")

add_executable(stock_market_analysis src/utils/HttpClient.cpp src/utils/JSONParser.cpp src/utils/ThreadPool.cpp
        src/DataFetcher.cpp
        src/main.cpp
        src/DataProcessor.cpp
        src/Predictor.cpp
        src/Visualizer.cpp
        src/AlertManager.cpp)

#add_executable(test_plot src/testplot.cpp)
#target_link_libraries(test_plot ${PYTHON_LIBRARY})

## Link libraries
target_link_libraries(stock_market_analysis
        ${CURL_LIBRARIES}
        nlohmann_json::nlohmann_json
        ${PYTHON_LIBRARY}
)