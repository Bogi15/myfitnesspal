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

void signUp(vector<User>& users);
void logIn(const vector<User>& users);
void closeApp();
void addMeal(const User& user);
void addWorkout(User& user);
void viewDailyLog(const User& user);
void updateUserInfo(User& user);
int  calculateCalorieGoal(const User& user);

#endif 
