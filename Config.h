#pragma once
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctime>
#include <iostream>
#include <pqxx/pqxx>
#include <conio.h>
#include <fstream>

std::string dbname = "restaurant_menu";
std::string user = "postgres";
std::string password = "7341";
std::string host = "localhost";
std::string port = "5432";

std::string config = "dbname = " + dbname + " user = " + user + " password = " + password + " host = " + host + " port = " + port;

