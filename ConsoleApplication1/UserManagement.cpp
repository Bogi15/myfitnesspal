/**
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Bogomil Pankov
* @idnumber 6MI0600428 @compiler VCC
* <file with the functions and their code>
* */

#include "UserManagement.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void userMenu(User& user);
void closeApp();


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



void userMenu(User& user) {
    int choice;
    do {
        cout << "1. Add Meal\n";
        cout << "2. Add Workout\n";
        cout << "3. Update Meal\n";
        cout << "4. Update Workout\n";
        cout << "5. Update User Info\n";
        cout << "6. Display Daily Intake\n";
        cout << "7. View Daily Log\n";
        cout << "8. View Log for Specific Date\n";
        cout << "9. Delete Old Data\n";
        cout << "10. Log Out\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 10) {
            cout << "Invalid choice. Select a number between 1 and 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            addMeal(user);
            break;
        case 2:
            addWorkout(user);
            break;
        case 3:
            updateMeal(user);
            break;
        case 4:
            updateWorkout(user);
            break;
        case 5:
            updateUserInfo(user);
            break;
        case 6:
            displayDailyIntake(user);
            break;
        case 7:
            dateLog(user, getCurrentDate());
            break;
        case 8:
            loadDateLog(user);
            break;
        case 9:
            deleteOldDataMessage(user);
            break;
        case 10:
            saveDailyData(user);
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);
}


void closeApp() {
    cout << "Closing the application. Goodbye!\n";
}

void signUp(vector<User>& users) {
    User newUser;
    cout << "\n=== Sign Up ===\n";


    cout << "Enter username: ";
    cin >> newUser.username;

    if (checkUsernameInFile(newUser.username)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> newUser.password;


    cout << "Enter age: ";
    while (!(cin >> newUser.age) || newUser.age <= 0) {
        cout << "Invalid input. Enter a valid age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter gender (M/F): ";
    cin >> newUser.gender;

    while (!(newUser.gender == 'M' || newUser.gender == 'F')) {
        cout << "Invalid input. Enter a gender with the specific letter: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> newUser.gender;
    }

    cout << "Enter height (in cm): ";

    while (!(cin >> newUser.height) || (newUser.height <= 0)) {
        cout << "Invalid input. Enter a valid height: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter weight (in kg): ";

    while (!(cin >> newUser.weight) || (newUser.weight <= 0)) {
        cout << "Invalid input. Enter a valid weight: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Activity Level
    cout << "Select your activity level:\n";
    cout << "1. Seated work\n";
    cout << "2. Mild activity\n";
    cout << "3. Average activity\n";
    cout << "4. Active\n";
    cout << "5. Very active\n";
    cout << "Enter your choice: ";
    int activityChoice;
    while (!(cin >> activityChoice) || activityChoice < 1 || activityChoice > 5) {
        cout << "Invalid choice. Select a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (activityChoice) {
    case 1: newUser.activityLevel = "Seated work"; break;
    case 2: newUser.activityLevel = "Mild activity"; break;
    case 3: newUser.activityLevel = "Average activity"; break;
    case 4: newUser.activityLevel = "Active"; break;
    case 5: newUser.activityLevel = "Very active"; break;
    }

    // Goal
    cout << "Select your goal:\n";
    cout << "1. Lose weight\n";
    cout << "2. Keep weight\n";
    cout << "3. Gain weight\n";
    cout << "Enter your choice: ";
    int goalChoice;

    while (!(cin >> goalChoice) || goalChoice < 1 || goalChoice > 3) {
        cout << "Invalid choice. Select a number between 1 and 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    switch (goalChoice) {
    case 1:
        newUser.goal = "Lose weight";
        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceLose;

        while (!(cin >> amountPerWeekChoiceLose) || amountPerWeekChoiceLose < 1 || amountPerWeekChoiceLose > 4) {
            cout << "Invalid choice. Select a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (amountPerWeekChoiceLose) {
        case 1: newUser.calorieDifferenceFromMaintenance = -275; break;
        case 2: newUser.calorieDifferenceFromMaintenance = -550; break;
        case 3: newUser.calorieDifferenceFromMaintenance = -825; break;
        case 4: newUser.calorieDifferenceFromMaintenance = -1100; break;
        }
        break;
    case 2: newUser.goal = "Keep weight"; break;
    case 3:
        newUser.goal = "Gain weight";

        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceGain;

        while (!(cin >> amountPerWeekChoiceGain) || amountPerWeekChoiceGain < 1 || amountPerWeekChoiceGain > 4) {
            cout << "Invalid choice. Select a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (amountPerWeekChoiceGain) {
        case 1: newUser.calorieDifferenceFromMaintenance = 275; break;
        case 2: newUser.calorieDifferenceFromMaintenance = 550; break;
        case 3: newUser.calorieDifferenceFromMaintenance = 825; break;
        case 4: newUser.calorieDifferenceFromMaintenance = 1100; break;
        }
        break;
    }


    cout << "Select account type:\n";
    cout << "1. Standard\n";
    cout << "2. Premium\n";
    cout << "Enter your choice: ";
    int accountChoice;

    while (!(cin >> accountChoice) || accountChoice < 1 || accountChoice > 2) {
        cout << "Invalid choice. Select a number between 1 and 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (accountChoice) {
    case 1:
        newUser.accountType = "Standard";
        break;
    case 2:
        newUser.accountType = "Premium";
        break;
    }

    newUser.BMR = calculatingBMR(newUser);
    newUser.dailyCalorieGoal = calculateCalorieGoal(newUser);


    users.push_back(newUser);
    cout << "Sign up successful! You can now log in.\n";
    saveUsernameToFile(newUser.username);
    createUserFile(newUser);
}

void logIn(const vector<User>& users) {
    string enteredUsername, enteredPassword;
    cout << "\n=== Log In ===\n";
    cout << "Enter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    string filename = "users\\" + enteredUsername + ".txt";
    string storedUsername, storedPassword;

    if (readUsernameAndPassword(filename, storedUsername, storedPassword)) {
        if (enteredPassword == storedPassword) {
            User user;
            if (readFullUserFromFile(filename, user)) {
                loadDailyData(user);
                cout << "Login successful! Welcome, " << user.username << ".\n";
                userMenu(user);
            }
            else {
                cout << "Failed to load user data. Please try again.\n";
            }
        }
        else {
            cout << "Invalid password. Try again.\n";
        }
    }
    else {
        cout << "User does not exist. Try again.\n";
    }
}

void createUserFile(const User& newUser) {
    string filename = "users\\" + newUser.username + ".txt";
    ofstream userFile(filename);
    if (userFile.is_open()) {
        userFile << newUser.username << endl;
        userFile << newUser.password << endl;
        userFile << newUser.age << endl;
        userFile << newUser.gender << endl;
        userFile << newUser.height << endl;
        userFile << newUser.weight << endl;
        userFile << newUser.activityLevel << endl;
        userFile << newUser.goal << endl;
        userFile << newUser.calorieDifferenceFromMaintenance << endl;
        userFile << newUser.accountType << endl;
        userFile << newUser.BMR << endl;
        userFile << newUser.dailyCalorieGoal << endl;

        userFile.close();
        
    }
    else {
        cout << "Unable to create file!" << endl;
    }
}

bool readUsernameAndPassword(const string& filename, string& username, string& password) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        return false;
    }

    userFile >> username;
    userFile >> password;

    userFile.close();
    return true;
}

bool readFullUserFromFile(const string& filename, User& user) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        return false;
    }

    getline(userFile, user.username);
    getline(userFile, user.password);
    userFile >> user.age;
    userFile.ignore();
    userFile >> user.gender;
    userFile >> user.height;
    userFile >> user.weight;
    userFile.ignore();
    getline(userFile, user.activityLevel);
    getline(userFile, user.goal);
    userFile >> user.calorieDifferenceFromMaintenance;
    userFile.ignore();
    getline(userFile, user.accountType);
    userFile >> user.BMR;
    userFile >> user.dailyCalorieGoal;

    userFile.close();
    return true;
}

void saveUsernameToFile(const string& username) {
    ofstream outFile("usernames.txt");
    if (outFile.is_open()) {
        outFile << username << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file to save username!" << endl;
    }
}

bool checkUsernameInFile(const string& username) {
    ifstream inFile("usernames.txt");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == username) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
    }
    return false;
}

int calculateCalorieGoal(const User& user) {
    return user.BMR + user.calorieDifferenceFromMaintenance;
}

double calculatingBMR(const User& user) {
    if (user.gender == 'M') {
        return 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    if (user.gender == 'F') {
        return 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
}

void calculatingBMRWithActivityLevels(User& user) {
    if (user.activityLevel == "Seated work") user.BMR = user.BMR * 1.2;
    if (user.activityLevel == "Mild activity") user.BMR = user.BMR * 1.375;
    if (user.activityLevel == "Average activity") user.BMR = user.BMR * 1.55;
    if (user.activityLevel == "Active") user.BMR = user.BMR * 1.725;
    if (user.activityLevel == "Very active") user.BMR = user.BMR * 1.9;
}

void calculatingMacronutrients(User& user) {
    int dailyCaloriesGoal = user.dailyCalorieGoal;
    string goal = user.goal;
    if (goal == "Lose weight") {
        user.carbsGoal = (0.35 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.35 * dailyCaloriesGoal) / 4;
        user.fatsGoal = (0.30 * dailyCaloriesGoal) / 9;
    }
    else if (goal == "Keep weight") {
        user.carbsGoal = (0.45 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.25 * dailyCaloriesGoal) / 4;
        user.fatsGoal = (0.30 * dailyCaloriesGoal) / 9;
    }
    else {
        user.carbsGoal = (0.35 * dailyCaloriesGoal) / 4;
        user.proteinsGoal = (0.40 * dailyCaloriesGoal) / 4;
        user.fatsGoal = (0.25 * dailyCaloriesGoal) / 9;
    }
}

void addMeal(User& user) {
    Meal meal;
    meal.id = loadIdForMeals(user) + 1;
    cout << "Enter meal name: ";
    cin.ignore();
    getline(cin, meal.name);

    cout << "Enter calories: ";
    cin >> meal.calories;
    user.caloriesEaten += meal.calories;

    if (user.accountType == "Premium") {
        cout << "Enter protein (g): ";
        cin >> meal.proteins;
        user.proteinsEaten += meal.proteins;

        cout << "Enter fats (g): ";
        cin >> meal.fats;
        user.fatsEaten += meal.fats;

        cout << "Enter carbs (g): ";
        cin >> meal.carbs;
        user.carbsEaten += meal.carbs;
    }

    user.meals.push_back(meal);
    cout << "Meal added successfully!\n";


    string filename = "users/" + user.username + "_meals_" + getCurrentDate() + ".txt";
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << meal.id << endl;
        outFile << meal.name << endl;
        outFile << meal.calories << endl;

        if (user.accountType == "Premium") {
            outFile << meal.proteins << endl;
            outFile << meal.fats << endl;
            outFile << meal.carbs << endl;
        }

        outFile.close();
    }
    else {
        cout << "Unable to open file to append meal data!" << endl;
    }
}

void updateMeal(User& user) {

    string currentDate = getCurrentDate();

    string mealsFilename = "users/" + user.username + "_meals_" + currentDate + ".txt";
    ifstream mealsFile(mealsFilename);
    vector<Meal> meals;

    if (mealsFile.is_open()) {
        while (!mealsFile.eof()) {
            Meal meal;
            string line;
            getline(mealsFile, line);
            if (line.empty()) break;
            meal.id = convertIdToNumber(line);
            getline(mealsFile, meal.name);
            mealsFile >> meal.calories;
            if (user.accountType == "Premium") {
                mealsFile >> meal.proteins;
                mealsFile >> meal.fats;
                mealsFile >> meal.carbs;
            }
            mealsFile.ignore(numeric_limits<streamsize>::max(), '\n');
            meals.push_back(meal);
        }
        mealsFile.close();
    }
    else {
        cout << "No meals data found for " << currentDate << endl;
        return;
    }


    cout << "\nSelect a meal to update:\n";
    for (const Meal& meal : meals) {
        cout << meal.id << ". " << meal.name << " - " << meal.calories << " kcal";
        if (user.accountType == "Premium") {
            cout << ", " << meal.proteins << " protein, " << meal.fats << "g fats, " << meal.carbs << "g carbs";
        }
        cout << endl;
    }

    int mealId;
    cout << "Enter the meal ID: ";
    cin >> mealId;

    for (Meal& meal : meals) {
        if (meal.id == mealId) {
            cout << "Enter new meal name (or press enter to keep the current name): ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                meal.name = newName;
            }

            cout << "Enter new calories (or press enter to keep the current value): ";
            string newCalories;
            getline(cin, newCalories);
            if (!newCalories.empty()) {
                meal.calories = convertIdToNumber(newCalories);
            }

            if (user.accountType == "Premium") {
                cout << "Enter new protein (or press enter to keep the current value): ";
                string newProtein;
                getline(cin, newProtein);
                if (!newProtein.empty()) {
                    meal.proteins = convertIdToNumber(newProtein);
                }

                cout << "Enter new fats (or press enter to keep the current value): ";
                string newFats;
                getline(cin, newFats);
                if (!newFats.empty()) {
                    meal.fats = convertIdToNumber(newFats);
                }

                cout << "Enter new carbs (or press enter to keep the current value): ";
                string newCarbs;
                getline(cin, newCarbs);
                if (!newCarbs.empty()) {
                    meal.carbs = convertIdToNumber(newCarbs);
                }
            }
            break;
        }
    }

    ofstream outFile(mealsFilename);
    if (outFile.is_open()) {
        for (const Meal& meal : meals) {
            outFile << meal.id << endl;
            outFile << meal.name << endl;
            outFile << meal.calories << endl;
            if (user.accountType == "Premium") {
                outFile << meal.proteins << endl;
                outFile << meal.fats << endl;
                outFile << meal.carbs << endl;
            }
        }
        outFile.close();
        cout << "Meal updated successfully!\n";
    }
    else {
        cout << "Unable to open file to save meal data!" << endl;
    }
}

void addWorkout(User& user) {
    Workout workout;
    workout.id = loadIdForWorkouts(user) + 1;
    cout << "Enter workout name: ";
    cin.ignore();
    getline(cin, workout.name);

    cout << "Enter calories burned: ";
    cin >> workout.caloriesBurned;
    user.dailyCalorieGoal += workout.caloriesBurned;

    user.workouts.push_back(workout);
    cout << "Workout added successfully!\n";

    string filename = "users/" + user.username + "_workouts_" + getCurrentDate() + ".txt";
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << workout.id << endl;
        outFile << workout.name << endl;
        outFile << workout.caloriesBurned << endl;
        outFile.close();
    }
    else {
        cout << "Unable to open file to append workout data!" << endl;
    }
}

void updateWorkout(User& user) {

    string currentDate = getCurrentDate();


    string workoutsFilename = "users/" + user.username + "_workouts_" + currentDate + ".txt";
    ifstream workoutsFile(workoutsFilename);
    vector<Workout> workouts;

    if (workoutsFile.is_open()) {
        while (!workoutsFile.eof()) {
            Workout workout;
            string line;
            getline(workoutsFile, line);
            if (line.empty()) break;
            workout.id = convertIdToNumber(line);
            getline(workoutsFile, workout.name);
            workoutsFile >> workout.caloriesBurned;
            workoutsFile.ignore(numeric_limits<streamsize>::max(), '\n');
            workouts.push_back(workout);
        }
        workoutsFile.close();
    }
    else {
        cout << "No workouts data found for " << currentDate << endl;
        return;
    }


    cout << "\nSelect a workout to update:\n";
    for (const Workout& workout : workouts) {
        cout << workout.id << ". " << workout.name << " - " << workout.caloriesBurned << " kcal burned" << endl;
    }

    int workoutId;
    cout << "Enter the workout ID: ";
    cin >> workoutId;

    for (Workout& workout : workouts) {
        if (workout.id == workoutId) {
            cout << "Enter new workout name (or press enter to keep the current name): ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                workout.name = newName;
            }

            cout << "Enter new calories burned (or press enter to keep the current value): ";
            string newCaloriesBurned;
            getline(cin, newCaloriesBurned);
            if (!newCaloriesBurned.empty()) {
                workout.caloriesBurned = convertIdToNumber(newCaloriesBurned);
            }
            break;
        }
    }


    ofstream outFile(workoutsFilename);
    if (outFile.is_open()) {
        for (const Workout& workout : workouts) {
            outFile << workout.id << endl;
            outFile << workout.name << endl;
            outFile << workout.caloriesBurned << endl;
        }
        outFile.close();
        cout << "Workout updated successfully!\n";
    }
    else {
        cout << "Unable to open file to save workout data!" << endl;
    }
}

int loadIdForMeals(User& user) {
    string filename = "users/" + user.username + "_meals_" + getCurrentDate() + ".txt";
    ifstream mealsFile(filename);

    bool isPremium = (user.accountType == "Premium");
    int numberOfMeal = 0;
    string line;

    if (mealsFile.is_open()) {
        while (getline(mealsFile, line)) {
            numberOfMeal = convertIdToNumber(line);
            if (isPremium) {
                for (int i = 0; i < 5; i++) {
                    getline(mealsFile, line);
                }
            }
            else {
                for (int i = 0; i < 2; i++) {
                    getline(mealsFile, line);
                }
            }
        }

        mealsFile.close();
    }

    return numberOfMeal;
}

int loadIdForWorkouts(User& user) {
    string filename = "users/" + user.username + "_workouts_" + getCurrentDate() + ".txt";
    ifstream workoutsFile(filename);

    int numberOfWorkout = 0;
    string line;

    if (workoutsFile.is_open()) {
        while (getline(workoutsFile, line)) {
            numberOfWorkout = convertIdToNumber(line);
            for (int i = 0; i < 2; i++) {
                getline(workoutsFile, line);
            }
        }

        workoutsFile.close();
    }

    return numberOfWorkout;
}

void saveDailyData(const User& user) {
    string filename = "users/" + user.username + "_daily_" + getCurrentDate() + ".txt";
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << user.dailyCalorieGoal << endl;
        outFile << user.caloriesEaten << endl;
        if (user.accountType == "Premium") {
            outFile << user.proteinsEaten << endl;
            outFile << user.fatsEaten << endl;
            outFile << user.carbsEaten << endl;
        }
        outFile.close();
    }
}

void loadDailyData(User& user) {
    string filename = "users/" + user.username + "_daily_" + getCurrentDate() + ".txt";
    ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> user.dailyCalorieGoal;
        inFile >> user.caloriesEaten;
        if (user.accountType == "Premium") {
            inFile >> user.proteinsEaten;
            inFile >> user.fatsEaten;
            inFile >> user.carbsEaten;
        }
        inFile.close();
    }
    else {
        cout << "Unable to open file to load daily data!" << endl;
    }
}

void dateLog(User& user, const string& date) {
    cout << "\n=== Daily Log for " << date << " ===\n";

    int totalCaloriesEaten = 0;
    int totalCaloriesBurned = 0;
    int totalCarbs = 0;
    int totalProtein = 0;
    int totalFats = 0;

    string mealsFilename = "users/" + user.username + "_meals_" + date + ".txt";
    ifstream mealsFile(mealsFilename);
    string line;

    if (mealsFile.is_open()) {
        cout << "\nMeals Consumed:\n";
        while (true) {
            string line;
            int id, calories, protein = 0, fats = 0, carbs = 0;
            string name;

            if (!getline(mealsFile, line))  break;

            id = convertIdToNumber(line);
            getline(mealsFile, name);
            mealsFile >> calories;

            if (user.accountType == "Premium") {
                mealsFile >> protein;
                mealsFile >> fats;
                mealsFile >> carbs;
            }
            mealsFile.ignore(numeric_limits<streamsize>::max(), '\n');

            totalCaloriesEaten += calories;
            totalCarbs += carbs;
            totalProtein += protein;
            totalFats += fats;

            cout << id << ". " << name << " - " << calories << " kcal";
            if (user.accountType == "Premium") {
                cout << ", " << protein << "g protein, " << fats << "g fats, " << carbs << "g carbs";
            }
            cout << "\n";
        }
        mealsFile.close();
    }
    else {
        cout << "No meals data found for " << date << endl << endl;
    }

    string workoutsFilename = "users/" + user.username + "_workouts_" + date + ".txt";
    ifstream workoutsFile(workoutsFilename);

    if (workoutsFile.is_open()) {
        cout << "\nWorkouts Performed:\n";
        while (true) {
            string line;
            int id, caloriesBurned;
            string name;


            if (!getline(workoutsFile, line)) break;

            id = convertIdToNumber(line);
            getline(workoutsFile, name);
            workoutsFile >> caloriesBurned;
            workoutsFile.ignore(numeric_limits<streamsize>::max(), '\n');

            totalCaloriesBurned += caloriesBurned;
            cout << id << ". " << name << " - " << caloriesBurned << " kcal burned\n";
        }
        workoutsFile.close();
    }
    else {
        cout << "No workouts data found for " << date << endl;
    }


    cout << "\nSummary:\n";
    cout << "Total Calories Consumed: " << totalCaloriesEaten << " kcal\n";
    cout << "Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    cout << "Net Calories: " << (totalCaloriesEaten - totalCaloriesBurned) << " kcal\n";
    if (user.accountType == "Premium") {
        cout << "Total Carbs Consumed: " << totalCarbs << " grams\n";
        cout << "Total Protein Consumed: " << totalProtein << " grams\n";
        cout << "Total Fats Consumed: " << totalFats << " grams\n";
    }
    cout << endl;
}

void viewDailyLog(User& user) {
    string choice;
    do {
        if (user.accountType == "Premium") calculatingMacronutrients(user);
        displayDailyIntake(user);

        cout << "\nWrite back to go back to the User Menu: ";
        cin >> choice;
    } while (choice != "back");
}

void displayDailyIntake(const User& user) {
    cout << "\n=== Display Daily Intake ===\n";
    cout << "Daily Calorie Goal: " << user.caloriesEaten << "/" << user.dailyCalorieGoal << " kcal" << endl;
    if (user.accountType == "Premium") {
        cout << "Daily Carbs Goal: " << user.carbsEaten << "/" << user.carbsGoal << " grams" << endl;
        cout << "Daily Protein Goal: " << user.proteinsEaten << "/" << user.proteinsGoal << " grams" << endl;
        cout << "Daily Fats Goal: " << user.fatsEaten << "/" << user.fatsGoal << " grams" << endl;
    }
}

void loadDateLog(User& user) {
    string date;
    cout << "Enter the date (YYYY-MM-DD) for the log you want to view: ";
    cin >> date;
    dateLog(user, date);
}

string getCurrentDate() {

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm,&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", &ltm);
    return string(date);
}

string generateDailyFilename(const string& username) {
    return "users/" + username + "_" + getCurrentDate() + ".txt";
}


int convertIdToNumber(const string& str) {
    int result = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] < '0' || str[i] > '9') {
            throw invalid_argument("Invalid input string");
        }
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

bool deleteOldData(string& username, string& date) {
    string mealsFilename = "users/" + username + "_meals_" + date + ".txt";
    string workoutsFilename = "users/" + username + "_workouts_" + date + ".txt";
    bool mealsDeleted = false, workoutsDeleted = false;

    if (!remove(mealsFilename.c_str())) {
        cout << "Deleted meal file: " << mealsFilename << endl;
        mealsDeleted = true;
    }
    else {
        cout << "Could not delete meal file: " << mealsFilename << endl;
    }

    if (!remove(workoutsFilename.c_str())) {
        cout << "Deleted workout file: " << workoutsFilename << endl;
        workoutsDeleted = true;
    }
    else {
        cout << "Could not delete workout file: " << workoutsFilename << endl;
    }

    return mealsDeleted || workoutsDeleted;
}

void deleteOldDataMessage(User& user) {
    string date;
    cout << "Enter the date (YYYY-MM-DD) for the data you want to delete: ";
    cin >> date;
    if (deleteOldData(user.username, date)) {
        cout << "Old data deleted successfully.\n";
    }
    else {
        cout << "Failed to delete old data. Please check the date and try again.\n";
    }
}

void updateActivityLevel(User& user) {
    cout << "Select your activity level:\n";
    cout << "1. Seated work\n";
    cout << "2. Mild activity\n";
    cout << "3. Average activity\n";
    cout << "4. Active\n";
    cout << "5. Very active\n";
    cout << "Enter your choice: ";
    int activityChoice;
    while (!(cin >> activityChoice) || activityChoice < 1 || activityChoice > 5) {
        cout << "Invalid choice. Select a number between 1 and 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (activityChoice) {
    case 1: user.activityLevel = "Seated work"; break;
    case 2: user.activityLevel = "Mild activity"; break;
    case 3: user.activityLevel = "Average activity"; break;
    case 4: user.activityLevel = "Active"; break;
    case 5: user.activityLevel = "Very active"; break;
    }
}

void updateCalorieDifference(User& user) {
    cout << "Select your goal:\n";
    cout << "1. Lose weight\n";
    cout << "2. Keep weight\n";
    cout << "3. Gain weight\n";
    cout << "Enter your choice: ";
    int goalChoice;
    
    while (!(cin >> goalChoice) || goalChoice < 1 || goalChoice > 3) {
        cout << "Invalid choice. Select a number between 1 and 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (goalChoice) {
    case 1:
        user.goal = "Lose weight";
        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceLose;

        while (!(cin >> amountPerWeekChoiceLose) || amountPerWeekChoiceLose < 1 || amountPerWeekChoiceLose > 4) {
            cout << "Invalid choice. Select a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (amountPerWeekChoiceLose) {
        case 1: user.calorieDifferenceFromMaintenance = -275; break;
        case 2: user.calorieDifferenceFromMaintenance = -550; break;
        case 3: user.calorieDifferenceFromMaintenance = -825; break;
        case 4: user.calorieDifferenceFromMaintenance = -1100; break;
        }
        break;
    case 2: user.goal = "Keep weight"; user.calorieDifferenceFromMaintenance = 0; break;
    case 3:
        user.goal = "Gain weight";

        cout << "Select your weekly goal:\n";
        cout << "1. 0.25 kg per week\n";
        cout << "2. 0.50 kg per week\n";
        cout << "3. 0.75 kg per week\n";
        cout << "4. 1.00 kg per week\n";
        cout << "Enter your choice: ";
        int amountPerWeekChoiceGain;
            
        while (!(cin >> amountPerWeekChoiceGain) || amountPerWeekChoiceGain < 1 || amountPerWeekChoiceGain > 4) {
            cout << "Invalid choice. Select a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (amountPerWeekChoiceGain) {
        case 1: user.calorieDifferenceFromMaintenance = 275; break;
        case 2: user.calorieDifferenceFromMaintenance = 550; break;
        case 3: user.calorieDifferenceFromMaintenance = 825; break;
        case 4: user.calorieDifferenceFromMaintenance = 1100; break;
        }
        break;
    }
}

void updateUserInfo(User& user) {
    cout << "\n=== Update User Info ===\n";
    cout << "1. Update Weight\n";
    cout << "2. Update Goal\n";
    cout << "3. Update Activity Level\n";
    cout << "4. Cancel\n";
    cout << "Enter your choice: ";
    int choice;
    
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Invalid choice. Select a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice) {
    case 1:
        cout << "Enter new weight (kg): ";
        cin >> user.weight;
        break;
    case 2:
        updateCalorieDifference(user);
        break;
    case 3:
        updateActivityLevel(user);
        break;
    case 4:
        cout << "Update canceled.\n";
        return;
    }


    user.BMR = calculatingBMR(user);
    calculatingBMRWithActivityLevels(user);
    user.dailyCalorieGoal = calculateCalorieGoal(user);
    calculatingMacronutrients(user);


    cout << "User info updated successfully!\n";
    cout << "New Daily Calorie Goal: " << user.dailyCalorieGoal << " kcal\n";

    if (user.accountType == "Premium") {

        cout << "New Macronutrient Goals:\n";
        cout << "Protein: " << user.proteinsGoal << " grams\n";
        cout << "Fats: " << user.fatsGoal << " grams\n";
        cout << "Carbs: " << user.carbsGoal << " grams\n";
    }

    createUserFile(user);
}
