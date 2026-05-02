#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_SONGS = 5;

struct Artist {
    string name;
    string hometown;
};

struct Song {
    string title;
    Artist artist;
    string genre;
    int durationSeconds;
};

// Convert seconds → M:SS
string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int sec = seconds % 60;

    string result = to_string(minutes) + ":";
    if (sec < 10) result += "0";
    result += to_string(sec);

    return result;
}

// Convert string to lowercase
string toLower(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

// Display one song
void displaySong(const Song& s, int index) {
    cout << index + 1 << ". " << s.title << endl;
    cout << "   Artist: " << s.artist.name << " (" << s.artist.hometown << ")\n";
    cout << "   Genre: " << s.genre << endl;
    cout << "   Duration: " << formatDuration(s.durationSeconds) << "\n\n";
}

int main() {
    Song playlist[NUM_SONGS];

    cout << "PERSONAL PLAYLIST MANAGER\n";
    cout << "--------------------------\n";

    // INPUT (FIXED LOOP)
    for (int i = 0; i < NUM_SONGS; i++) {
        cout << "Enter information for Song " << i + 1 << ":\n";

        cout << "  Title: ";
        getline(cin, playlist[i].title);

        cout << "  Artist name: ";
        getline(cin, playlist[i].artist.name);

        cout << "  Artist hometown: ";
        getline(cin, playlist[i].artist.hometown);

        cout << "  Genre: ";
        getline(cin, playlist[i].genre);

        cout << "  Duration (seconds): ";
        cin >> playlist[i].durationSeconds;

        // CRITICAL FIX
        cin.ignore(1000, '\n');

        cout << endl;
    }

    // DISPLAY PLAYLIST
    cout << "YOUR PLAYLIST:\n";
    cout << "--------------\n";
    for (int i = 0; i < NUM_SONGS; i++) {
        displaySong(playlist[i], i);
    }

    // STATS
    int totalSeconds = 0;
    int longestIndex = 0;

    for (int i = 0; i < NUM_SONGS; i++) {
        totalSeconds += playlist[i].durationSeconds;

        if (playlist[i].durationSeconds > playlist[longestIndex].durationSeconds) {
            longestIndex = i;
        }
    }

    cout << "Playlist Stats:\n";
    cout << "  Total runtime: " << formatDuration(totalSeconds) << endl;
    cout << "  Longest song:  " << playlist[longestIndex].title
         << " (" << formatDuration(playlist[longestIndex].durationSeconds) << ")\n\n";

    // SEARCH BY ARTIST
    string searchArtist;
    cout << "Search by artist: ";
    getline(cin, searchArtist);

    bool found = false;
    string searchArtistLower = toLower(searchArtist);

    cout << "Songs by " << searchArtist << ":\n";
    for (int i = 0; i < NUM_SONGS; i++) {
        if (toLower(playlist[i].artist.name) == searchArtistLower) {
            cout << "  - " << playlist[i].title
                 << " (" << formatDuration(playlist[i].durationSeconds) << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "  No songs found for that artist.\n";
    }

    cout << endl;

    // SEARCH BY GENRE
    string searchGenre;
    cout << "Search by genre: ";
    getline(cin, searchGenre);

    found = false;
    string searchGenreLower = toLower(searchGenre);

    cout << "Songs in genre \"" << searchGenre << "\":\n";
    for (int i = 0; i < NUM_SONGS; i++) {
        if (toLower(playlist[i].genre) == searchGenreLower) {
            cout << "  - " << playlist[i].title
                 << " (" << formatDuration(playlist[i].durationSeconds) << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "  No songs found for that genre.\n";
    }

    cout << endl;

    // BONUS: SHUFFLE
    srand(time(0));

    Song shuffled[NUM_SONGS];
    for (int i = 0; i < NUM_SONGS; i++) {
        shuffled[i] = playlist[i];
    }

    for (int i = NUM_SONGS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(shuffled[i], shuffled[j]);
    }

    cout << "Shuffled Playlist:\n";
    for (int i = 0; i < NUM_SONGS; i++) {
        cout << "  " << i + 1 << ". " << shuffled[i].title << endl;
    }

    return 0;
}