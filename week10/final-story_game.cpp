#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Player
{
    string name;
    bool map1 = false;
    bool map2 = false;
    bool hasShovel = false;
    bool solvedPuzzle = false;
    vector<string> inventory;
};

enum class Location
{
    CABIN,
    FOREST,
    RIVER,
    CLEARING,
    TREASURE,
    WIN,
    LOSE
};

void describeLocation(Location loc)
{
    if (loc == Location::CABIN)
        cout << "\nYou stand inside an old abandoned cabin...\n";
    else if (loc == Location::FOREST)
        cout << "\nYou step into a dark, quiet forest...\n";
    else if (loc == Location::RIVER)
        cout << "\nYou arrive at a fast-moving river...\n";
    else if (loc == Location::CLEARING)
        cout << "\nYou enter a mysterious ancient clearing...\n";
    else if (loc == Location::TREASURE)
        cout << "\nYou reach what seems to be the treasure site...\n";
}

void printInventory(const Player& p)
{
    cout << "\n=== INVENTORY ===\n";

    if (p.inventory.empty())
        cout << "Empty\n";
    else
    {
        for (const auto& item : p.inventory)
            cout << "- " << item << "\n";
    }

    cout << "\n";
}

int getChoice(int max)
{
    int c;

    while (true)
    {
        cout << "Choose: ";
        cin >> c;

        if (!cin.fail() && c >= 1 && c <= max)
            return c;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice.\n";
    }
}

bool puzzle()
{
    cout << "\n=== ANCIENT STONE DOOR ===\n\n";

    cout << "A faded inscription is carved into the stone:\n\n";

    cout << "\"Three brothers left their village in search of a lost treasure.\n";
    cout << "Each carried two torches to light the path ahead.\n";
    cout << "After a week of travel, they reached an ancient ruin.\n";
    cout << "There they found a stone altar supported by four pillars.\n";
    cout << "The door will open only for those who remember the tale.\"\n\n";

    cout << "Below the inscription are the words:\n";
    cout << "\"Enter the code using:\n";
    cout << "1. The number of brothers.\n";
    cout << "2. The total number of torches.\n";
    cout << "3. The number of pillars.\"\n\n";

    string code;
    cout << "Enter the code: ";
    cin >> code;

    if (code == "364")
    {
        cout << "\nThe stone door rumbles open...\n";
        return true;
    }

    cout << "\nThe door remains sealed.\n";
    return false;
}

void intro()
{
    ifstream f("story.txt");

    if (!f)
    {
        cout << "(Story file not found)\n";
        return;
    }

    string line;

    while (getline(f, line))
        cout << line << '\n';

    cout << '\n';
}

void save(const Player& p, const string& result)
{
    ofstream out("game_summary.txt");

    out << "Name: " << p.name << "\n";
    out << "Map1: " << p.map1 << "\n";
    out << "Map2: " << p.map2 << "\n";
    out << "Shovel: " << p.hasShovel << "\n";
    out << "Puzzle Solved: " << p.solvedPuzzle << "\n";
    out << "Result: " << result << "\n\n";

    out << "Inventory:\n";

    for (const auto& item : p.inventory)
        out << "- " << item << "\n";
}

int main()
{
    Player p;

    Location loc = Location::CABIN;
    Location prevLoc = Location::WIN;

    cout << "Enter name: ";
    getline(cin, p.name);

    cout << "\n=== LOST TREASURE ===\n";
    intro();

    while (loc != Location::WIN && loc != Location::LOSE)
    {
        if (loc != prevLoc)
        {
            describeLocation(loc);
            prevLoc = loc;
        }

        if (loc == Location::CABIN)
        {
            cout << "\n1.Search room  2.Go forest  3.Inventory  4.Quit\n";

            int c = getChoice(4);

            if (c == 1)
            {
                cout << "\n1.Bookshelf  2.Chest  3.Fireplace\n";

                int s = getChoice(3);

                if (s == 2 && !p.map1)
                {
                    cout << "You found Map Piece 1!\n";
                    p.map1 = true;
                    p.inventory.push_back("Map Piece 1");
                }
                else
                {
                    cout << "Nothing useful found.\n";
                }
            }
            else if (c == 2)
            {
                loc = Location::FOREST;
            }
            else if (c == 3)
            {
                printInventory(p);
            }
            else
            {
                save(p, "QUIT");
                cout << "You quit the game.\n";
                return 0;
            }
        }

        else if (loc == Location::FOREST)
        {
            cout << "\n1.Search  2.River  3.Cabin  4.Inventory  5.Quit\n";

            int c = getChoice(5);

            if (c == 1)
            {
                cout << "\n1.Hollow tree  2.Bushes  3.Log\n";

                int s = getChoice(3);

                if (s == 1 && !p.hasShovel)
                {
                    cout << "You found a shovel!\n";
                    p.hasShovel = true;
                    p.inventory.push_back("Shovel");
                }
                else
                {
                    cout << "Nothing useful found.\n";
                }
            }
            else if (c == 2)
            {
                loc = Location::RIVER;
            }
            else if (c == 3)
            {
                loc = Location::CABIN;
            }
            else if (c == 4)
            {
                printInventory(p);
            }
            else
            {
                save(p, "QUIT");
                cout << "You quit the game.\n";
                return 0;
            }
        }

        else if (loc == Location::RIVER)
        {
            cout << "\n1.Search rocks  2.Forest";

            if (p.map1 && p.map2)
                cout << "  3.Follow map";

            cout << "  4.Quit\n";

            int maxChoice = (p.map1 && p.map2) ? 4 : 3;
            int c = getChoice(maxChoice);

            if (c == 1)
            {
                if (!p.map2)
                {
                    cout << "You found Map Piece 2!\n";
                    p.map2 = true;
                    p.inventory.push_back("Map Piece 2");

                    if (p.map1)
                    {
                        cout << "\nThe two map pieces fit together.\n";
                        cout << "A hidden route appears on the map.\n";
                    }
                }
                else
                {
                    cout << "You already searched these rocks.\n";
                }
            }
            else if (c == 2)
            {
                loc = Location::FOREST;
            }
            else if (p.map1 && p.map2 && c == 3)
            {
                cout << "\nYou follow the completed map.\n";
                loc = Location::CLEARING;
            }
            else
            {
                save(p, "QUIT");
                cout << "You quit the game.\n";
                return 0;
            }
        }

        else if (loc == Location::CLEARING)
        {
            cout << "\n1.Solve puzzle  2.Back  3.Quit\n";

            int c = getChoice(3);

            if (c == 1)
            {
                if (puzzle())
                {
                    cout << "\nThe path opens...\n";
                    p.solvedPuzzle = true;
                    loc = Location::TREASURE;
                }
                else
                {
                    loc = Location::LOSE;
                }
            }
            else if (c == 2)
            {
                loc = Location::RIVER;
            }
            else
            {
                save(p, "QUIT");
                cout << "You quit the game.\n";
                return 0;
            }
        }

        else if (loc == Location::TREASURE)
        {
            if (!p.hasShovel)
            {
                cout << "You need a shovel before you can dig.\n";
                loc = Location::FOREST;
            }
            else
            {
                cout << "\n1.Dig  2.Leave  3.Quit\n";

                int c = getChoice(3);

                if (c == 1)
                {
                    loc = Location::WIN;
                }
                else if (c == 2)
                {
                    loc = Location::FOREST;
                }
                else
                {
                    save(p, "QUIT");
                    cout << "You quit the game.\n";
                    return 0;
                }
            }
        }
    }

    if (loc == Location::WIN)
    {
        cout << "\nYOU FOUND THE TREASURE!\n";
        save(p, "WIN");
    }
    else
    {
        cout << "\nGAME OVER\n";
        save(p, "LOSE");
    }

    return 0;
}