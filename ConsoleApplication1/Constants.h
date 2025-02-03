/**
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Bogomil Pankov
* @idnumber 6MI0600428 @compiler VCC
* <file with the all the constats>
* */

#pragma once

const double MALE_BMR_BASE = 88.362;
const double MALE_BMR_WEIGHT_FACTOR = 13.397;
const double MALE_BMR_HEIGHT_FACTOR = 4.799;
const double MALE_BMR_AGE_FACTOR = 5.677;

const double FEMALE_BMR_BASE = 447.593;
const double FEMALE_BMR_WEIGHT_FACTOR = 9.247;
const double FEMALE_BMR_HEIGHT_FACTOR = 3.098;
const double FEMALE_BMR_AGE_FACTOR = 4.330;

const double SEATED_WORK_MULTIPLIER = 1.2;
const double MILD_ACTIVITY_MULTIPLIER = 1.375;
const double AVERAGE_ACTIVITY_MULTIPLIER = 1.55;
const double ACTIVE_MULTIPLIER = 1.725;
const double VERY_ACTIVE_MULTIPLIER = 1.9;

const double LOSE_WEIGHT_CARBS_RATIO = 0.35;
const double LOSE_WEIGHT_PROTEINS_RATIO = 0.35;
const double LOSE_WEIGHT_FATS_RATIO = 0.30;

const double KEEP_WEIGHT_CARBS_RATIO = 0.45;
const double KEEP_WEIGHT_PROTEINS_RATIO = 0.25;
const double KEEP_WEIGHT_FATS_RATIO = 0.30;

const double GAIN_WEIGHT_CARBS_RATIO = 0.35;
const double GAIN_WEIGHT_PROTEINS_RATIO = 0.40;
const double GAIN_WEIGHT_FATS_RATIO = 0.25;

const int CALORIES_PER_GRAM_CARBS = 4;
const int CALORIES_PER_GRAM_PROTEINS = 4;
const int CALORIES_PER_GRAM_FATS = 9;

const int CALORIE_DIFFERENCE_LOSE_0_25_KG = -275;
const int CALORIE_DIFFERENCE_LOSE_0_50_KG = -550;
const int CALORIE_DIFFERENCE_LOSE_0_75_KG = -825;
const int CALORIE_DIFFERENCE_LOSE_1_00_KG = -1100;

const int CALORIE_DIFFERENCE_GAIN_0_25_KG = 275;
const int CALORIE_DIFFERENCE_GAIN_0_50_KG = 550;
const int CALORIE_DIFFERENCE_GAIN_0_75_KG = 825;
const int CALORIE_DIFFERENCE_GAIN_1_00_KG = 1100;


