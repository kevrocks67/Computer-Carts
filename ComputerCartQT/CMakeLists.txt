cmake_minimum_required(VERSION 3.1.0)

project(ComputerCartQT)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
    Widgets REQUIRED
    Sql REQUIRED
    Gui REQUIRED
)

include_directories(phantom)

add_executable(ComputerCartQT
    AddCart.cpp
    AddLaptop.cpp
    Application.cpp
    CartModel.cpp
    CartView.cpp
    DeleteCart.cpp
    DeleteLaptop.cpp
    DetailView.cpp
    EditCart.cpp
    EditLaptop.cpp
    LaptopModel.cpp
    Laptops.cpp
    LaptopView.cpp
    MainWindow.cpp
    ResModel.cpp
    Settings.cpp
)

target_link_libraries(ComputerCartQT
    Qt5::Widgets
    Qt5::Sql
    Qt5::Gui
)
