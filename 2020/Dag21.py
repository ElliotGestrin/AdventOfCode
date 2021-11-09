import elliot_standard_library as es
import math

file = open("Filer\Dag21.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    allergens = {}
    ingredients = []
    for line in lines:
        foodIngredientNames = line.split(" (")[0].split(" ")
        foodAllergens = line.split("(contains ")[1][:-1].split(", ")
        ingredients += foodIngredientNames.copy()
        for allergen in foodAllergens:
            try:
                allergens[allergen].append(foodIngredientNames.copy())
            except KeyError:
                allergens[allergen] = [foodIngredientNames.copy()]
    for allergen, foodOptions in allergens.items():
        toRemove = []
        for food in foodOptions[0]:
            for subFoodOption in foodOptions:
                #print(f"  {allergen}:{food} vs {subFoodOption} ({food in subFoodOption})")
                if food not in subFoodOption:
                    toRemove.append(food)
                    break
        for food in toRemove:
            foodOptions[0].remove(food)
    for allergen, foods in allergens.items():
        allergens[allergen] = foods[0]
    possibly_allergenic_food = []
    for allergen_foods in allergens.values():
        possibly_allergenic_food += allergen_foods
    non_allergenic_ingredients = 0
    for ingredient in ingredients:
        if not ingredient in possibly_allergenic_food:
            non_allergenic_ingredients += 1
    for allergen, foods in allergens.items():
        print(f"1:    {allergen}: {foods}")
    while max([len(foods) for allergen, foods in allergens.items()]) > 1:
        for mainAllergen, mainFoods in allergens.items():
            if len(mainFoods) == 1:
                for subAllergen, subFoods in allergens.items():
                    if mainAllergen == subAllergen:
                        continue
                    if mainFoods[0] in subFoods:
                        subFoods.remove(mainFoods[0])
    for allergen, foods in allergens.items():
        print(f"2:    {allergen}: {foods}")
    sortedAllergenList = [allergen for allergen in allergens.keys()]
    sortedAllergenList.sort()
    canDanList = ""
    for allergen in sortedAllergenList:
        canDanList += allergens[allergen][0] + ","
    print(f"The number of nonallergic ingredients: {non_allergenic_ingredients}")
    print(f"The canonical danger list is:\n   {canDanList}")

main()
