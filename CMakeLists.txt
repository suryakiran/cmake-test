cmake_minimum_required(VERSION 3.14)
project(cmake-test LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

# find_package(Boost REQUIRED COMPONENTS chrono filesystem date_time program_options iostreams)
set (Boost_ARCHITECTURE "-x64")
# find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer)
find_package(cppzmq REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(aws-cpp-sdk-core)
find_package(aws-cpp-sdk-s3)
find_package(GDAL REQUIRED)
find_package(msgpack REQUIRED)
find_package(fmt REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation JSON Util XML Zip)
find_package(TBB REQUIRED)
find_package(Angelscript REQUIRED)
find_package(libpqxx REQUIRED)
find_package(easyloggingpp REQUIRED)
find_package(RapidJSON REQUIRED)


add_executable (test main.cc)

add_library(clang_flags INTERFACE IMPORTED)
set_target_properties (clang_flags
  PROPERTIES
  INTERFACE_COMPILE_OPTIONS $<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>
  INTERFACE_LINK_LIBRARIES $<$<CXX_COMPILER_ID:Clang>:c++>
  )

target_link_libraries(test PUBLIC
  # clang_flags
  # Boost::timer
  Poco::Foundation
  # Boost::disable_autolinking
  # Boost::filesystem
  fmt::fmt
  libpqxx::pqxx_shared
  PostgreSQL::PostgreSQL
  angelscript
  TBB::tbb
  easyloggingpp
  rapidjson
  )

