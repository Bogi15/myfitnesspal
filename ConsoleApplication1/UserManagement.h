/**
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Bogomil Pankov
* @idnumber 6MI0600428 @compiler VCC
* <file with the initialization of the structs and some functions>
* */

#pragma once
#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <vector>
#include <string>

using namespace std;

struct Meal {
    int id = 0;
    string name;
    int calories;
    int carbs;
    int proteins;
    int fats;
};

struct Workout {
    int id = 0;
    string name;
    int caloriesBurned;
};

struct User {
    string username;
    string password;
    int age;
    char gender;
    double height; 
    double weight; 
    double BMR;
    string activityLevel;
    string goal;
    string accountType;
    int calorieDifferenceFromMaintenance = 0;
    int dailyCalorieGoal;
    int carbsGoal;
    int proteinsGoal;
    int fatsGoal;
    int carbsEaten = 0;
    int proteinsEaten = 0;
    int fatsEaten = 0;
    int caloriesEaten = 0;
    vector<Meal> meals;
    vector<Workout> workouts;
};

void userMenu(User& user);
void closeApp();
void updateUserInfo(User& user);

void signUp(vector<User>& users);
void logIn(const vector<User>& users);
void createUserFile(const User& newUser);
bool readUsernameAndPassword(const string& filename, string& username, string& password);
bool readFullUserFromFile(const string& filename, User& user);
void saveUsernameToFile(const string& username);
bool checkUsernameInFile(const string& username);
int calculateCalorieGoal(const User& user);
double calculatingBMR(const User& user);
void calculatingBMRWithActivityLevels(User& user);
void calculatingMacronutrients(User& user);

void addMeal(User& user);
void updateMeal(User& user);
void addWorkout(User& user);
void updateWorkout(User& user);
int loadIdForMeals(User& user);
int loadIdForWorkouts(User& user);
void saveDailyData(const User& user);
void loadDailyData(User& user);
void dateLog(User& user, const string& date);
void viewDailyLog(User& user);
void displayDailyIntake(const User& user);
void loadDateLog(User& user);


string getCurrentDate();
string generateDailyFilename(const string& username);
int convertIdToNumber(const string& str);
bool deleteOldData(string& username, string& date);
void deleteOldDataMessage(User& user);

#endif 
