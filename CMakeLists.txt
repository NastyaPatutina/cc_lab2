cmake_minimum_required(VERSION 3.13)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp gram/Terminal.cpp gram/Terminal.h gram/NotTerminal.cpp gram/NotTerminal.h gram/GramSymbol.h gram/Equation.cpp gram/Equation.h regexp/RegExpression.cpp regexp/RegExpression.h gram/Gramatic.cpp gram/Gramatic.h elimination/LeftFactoringElimination.cpp elimination/LeftFactoringElimination.h)