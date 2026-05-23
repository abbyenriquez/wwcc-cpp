#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Struct to store recipe information
struct Recipe {
    string name;
    vector<string> ingredients;
    vector<string> steps;
};

// Function to add a recipe
void addRecipe(vector<Recipe>& recipes) {
    Recipe r;

    cout << "\nEnter recipe name: ";
    getline(cin, r.name);

    int ingredientCount;

    cout << "How many ingredients? ";
    cin >> ingredientCount;
    cin.ignore();

    for (int i = 0; i < ingredientCount; i++) {
        string ingredient;

        cout << "Enter ingredient " << i + 1 << ": ";
        getline(cin, ingredient);

        r.ingredients.push_back(ingredient);
    }

    int stepCount;

    cout << "\nHow many steps? ";
    cin >> stepCount;
    cin.ignore();

    for (int i = 0; i < stepCount; i++) {
        string step;

        cout << "Enter step " << i + 1 << ": ";
        getline(cin, step);

        r.steps.push_back(step);
    }

    recipes.push_back(r);

    cout << "\nRecipe added successfully!\n";
}

// Function to display all recipes
void displayRecipes(const vector<Recipe>& recipes) {
    if (recipes.size() == 0) {
        cout << "\nNo recipes available.\n";
        return;
    }

    cout << "\nALL RECIPES\n";
    cout << "-----------\n";

    for (int i = 0; i < recipes.size(); i++) {
        cout << "\nRecipe " << i + 1 << ": "
             << recipes.at(i).name << endl;

        cout << "\nIngredients:\n";

        for (int j = 0; j < recipes.at(i).ingredients.size(); j++) {
            cout << "  - "
                 << recipes.at(i).ingredients.at(j)
                 << endl;
        }

        cout << "\nSteps:\n";

        for (int j = 0; j < recipes.at(i).steps.size(); j++) {
            cout << "  "
                 << j + 1
                 << ". "
                 << recipes.at(i).steps.at(j)
                 << endl;
        }

        cout << endl;
    }
}

// Convert string to lowercase
string toLower(string text) {
    for (char &c : text) {
        c = tolower(c);
    }

    return text;
}

// Search recipes
void searchRecipes(const vector<Recipe>& recipes) {
    if (recipes.size() == 0) {
        cout << "\nNo recipes available.\n";
        return;
    }

    string keyword;

    cout << "\nEnter recipe name or ingredient to search: ";
    getline(cin, keyword);

    keyword = toLower(keyword);

    bool found = false;

    cout << "\nSEARCH RESULTS\n";
    cout << "--------------\n";

    for (int i = 0; i < recipes.size(); i++) {

        string recipeName =
            toLower(recipes.at(i).name);

        // Partial recipe name match
        if (recipeName.find(keyword) != string::npos) {

            cout << "- "
                 << recipes.at(i).name
                 << endl;

            found = true;
        }

        // Ingredient match
        for (int j = 0;
             j < recipes.at(i).ingredients.size();
             j++) {

            string ingredient =
                toLower(recipes.at(i).ingredients.at(j));

            if (ingredient.find(keyword) != string::npos) {

                cout << "- "
                     << recipes.at(i).name
                     << endl;

                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "No matching recipes found.\n";
    }
}

// Remove recipe
void removeRecipe(vector<Recipe>& recipes) {
    if (recipes.size() == 0) {
        cout << "\nNo recipes to remove.\n";
        return;
    }

    cout << "\nRecipes:\n";

    for (int i = 0; i < recipes.size(); i++) {
        cout << i + 1
             << ". "
             << recipes.at(i).name
             << endl;
    }

    int choice;

    cout << "\nEnter recipe number to remove: ";
    cin >> choice;
    cin.ignore();

    // Input validation
    if (choice < 1 || choice > recipes.size()) {
        cout << "Invalid recipe number.\n";
        return;
    }

    recipes.erase(recipes.begin() + (choice - 1));

    cout << "Recipe removed successfully!\n";
}

// Show statistics
void showStatistics(const vector<Recipe>& recipes) {

    cout << "\nCOLLECTION STATISTICS\n";
    cout << "--------------------\n";

    cout << "Total recipes: "
         << recipes.size()
         << endl;

    if (recipes.size() == 0) {
        cout << "Average ingredients per recipe: 0\n";
        cout << "Average steps per recipe: 0\n";
        return;
    }

    int totalIngredients = 0;
    int totalSteps = 0;

    for (int i = 0; i < recipes.size(); i++) {
        totalIngredients +=
            recipes.at(i).ingredients.size();

        totalSteps +=
            recipes.at(i).steps.size();
    }

    double avgIngredients =
        (double) totalIngredients / recipes.size();

    double avgSteps =
        (double) totalSteps / recipes.size();

    cout << fixed << setprecision(1);

    cout << "Average ingredients per recipe: "
         << avgIngredients
         << endl;

    cout << "Average steps per recipe: "
         << avgSteps
         << endl;
}

// Main program
int main() {

    vector<Recipe> recipes;

    int choice;

    do {
        cout << "\nDYNAMIC RECIPE MANAGER\n";
        cout << "---------------------\n";

        cout << "1. Add Recipe\n";
        cout << "2. Display All Recipes\n";
        cout << "3. Search Recipes\n";
        cout << "4. Remove Recipe\n";
        cout << "5. Show Statistics\n";
        cout << "6. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            addRecipe(recipes);
            break;

        case 2:
            displayRecipes(recipes);
            break;

        case 3:
            searchRecipes(recipes);
            break;

        case 4:
            removeRecipe(recipes);
            break;

        case 5:
            showStatistics(recipes);
            break;

        case 6:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}