#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>

using namespace std;

enum class EventCategory {
    CONCERT,
    CONFERENCE,
    SPORTS,
    WORKSHOP
};

struct Event {
    string name;
    string date;
    EventCategory category;
    int attendees;
    double ticketPrice;
};

// Returns the display name for a category
string categoryName(EventCategory cat) {

    switch (cat) {

        // BUG: Concert and Workshop labels were swapped
        // FIX: Return the correct category names
        case EventCategory::CONCERT:
            return "Concert";

        case EventCategory::CONFERENCE:
            return "Conference";

        case EventCategory::SPORTS:
            return "Sports";

        // BUG: Workshop incorrectly returned "Concert"
        // FIX: Changed to return "Workshop"
        case EventCategory::WORKSHOP:
            return "Workshop";

        default:
            return "Unknown";
    }
}

// Display a single event
void printEvent(const Event& e) {

    cout << left
         << setw(30) << e.name
         << setw(12) << e.date
         << setw(12) << categoryName(e.category)
         << "Attendees: "
         << setw(5) << e.attendees
         << " Price: $"
         << fixed
         << setprecision(2)
         << e.ticketPrice
         << "\n";
}

// Display all events
void displayAll(const vector<Event>& events) {

    cout << "\n=== All Events ===\n";

    cout << left
         << setw(30) << "Name"
         << setw(12) << "Date"
         << setw(12) << "Category"
         << "\n";

    cout << string(70, '-') << "\n";

    for (const auto& e : events) {
        printEvent(e);
    }
}

// Calculate total revenue across all events
double totalRevenue(const vector<Event>& events) {

    return accumulate(
        events.begin(),
        events.end(),
        0.0,

        [](double sum, const Event& e) {

            // BUG: Only attendees were added
            // FIX: Multiply attendees by ticket price
            return sum + (e.attendees * e.ticketPrice);
        }
    );
}

// Calculate average ticket price across all events
double averageTicketPrice(const vector<Event>& events) {

    // BUG: Used int, causing decimal truncation
    // FIX: Changed total to double
    double total = 0.0;

    for (const auto& e : events) {

        // BUG: Decimal values lost when added to int
        // FIX: Using double preserves decimals
        total += e.ticketPrice;
    }

    // BUG: Integer division truncated result
    // FIX: Use double division
    return total / static_cast<double>(events.size());
}

// Sort events by date, oldest first
void sortByDateAscending(vector<Event>& events) {

    sort(
        events.begin(),
        events.end(),

        [](const Event& a, const Event& b) {

            // BUG: Used > which sorted descending
            // FIX: Changed to < for ascending order
            return a.date < b.date;
        }
    );
}

// Search for events whose name contains the search term
void searchByName(
    const vector<Event>& events,
    const string& term
) {

    cout << "\n=== Search Results for \""
         << term
         << "\" ===\n";

    bool found = false;

    for (const auto& e : events) {

        if (e.name.find(term) != string::npos) {

            // BUG: Only first match was displayed
            // FIX: Loop through all events and print every match
            printEvent(e);

            found = true;
        }
    }

    if (!found) {
        cout << "No events found.\n";
    }
}

// Feature 1
// Sort events by attendee count, highest first
void sortByAttendees(vector<Event>& events) {

    sort(
        events.begin(),
        events.end(),

        [](const Event& a, const Event& b) {
            return a.attendees > b.attendees;
        }
    );

    cout << "\n=== Events by Popularity ===\n";

    for (const auto& e : events) {
        printEvent(e);
    }
}

// Feature 2
// Filter events by category
void filterByCategory(
    const vector<Event>& events,
    EventCategory cat
) {

    vector<Event> filtered;

    copy_if(
        events.begin(),
        events.end(),
        back_inserter(filtered),

        [cat](const Event& e) {
            return e.category == cat;
        }
    );

    cout << "\n=== "
         << categoryName(cat)
         << " Events ===\n";

    if (filtered.empty()) {
        cout << "No matching events found.\n";
        return;
    }

    for (const auto& e : filtered) {
        printEvent(e);
    }
}

// Feature 3
// Export upcoming events to file
void exportUpcomingEvents(
    const vector<Event>& events,
    const string& filename
) {

    ofstream outFile(filename);

    if (!outFile) {

        cout << "Error opening file.\n";

        return;
    }

    for (const auto& e : events) {

        if (e.date >= "2025-06-01") {

            outFile << e.name
                    << " | "
                    << e.date
                    << " | "
                    << categoryName(e.category)
                    << " | "
                    << e.attendees
                    << " | $"
                    << fixed
                    << setprecision(2)
                    << e.ticketPrice
                    << endl;
        }
    }

    outFile.close();

    cout << "\nUpcoming events saved to "
         << filename
         << endl;
}

// Bonus Feature
void filterByMinAttendees(
    const vector<Event>& events,
    int minCount
) {

    vector<Event> filtered;

    copy_if(
        events.begin(),
        events.end(),
        back_inserter(filtered),

        [minCount](const Event& e) {
            return e.attendees > minCount;
        }
    );

    cout << "\n=== Events With More Than "
         << minCount
         << " Attendees ===\n";

    for (const auto& e : filtered) {
        printEvent(e);
    }
}

int main() {

    vector<Event> events = {

        {
            "Spring Music Fest",
            "2025-04-12",
            EventCategory::CONCERT,
            1200,
            45.50
        },

        {
            "Tech Summit 2025",
            "2025-06-20",
            EventCategory::CONFERENCE,
            350,
            129.00
        },

        {
            "City 5K Run",
            "2025-05-03",
            EventCategory::SPORTS,
            800,
            25.25
        },

        {
            "Watercolor Workshop",
            "2025-07-15",
            EventCategory::WORKSHOP,
            40,
            60.00
        },

        {
            "Jazz Under the Stars",
            "2025-08-02",
            EventCategory::CONCERT,
            600,
            35.75
        },

        {
            "Leadership Workshop",
            "2025-06-28",
            EventCategory::WORKSHOP,
            75,
            89.00
        },

        {
            "Regional Soccer Cup",
            "2025-09-14",
            EventCategory::SPORTS,
            2500,
            18.00
        },

        {
            "Dev Conf Northwest",
            "2025-10-05",
            EventCategory::CONFERENCE,
            420,
            199.00
        }
    };

    cout << "=== Community Event Scheduler ===\n";

    displayAll(events);

    cout << "\nTotal revenue (all events): $"
         << fixed
         << setprecision(2)
         << totalRevenue(events)
         << "\n";

    cout << "Average ticket price: $"
         << fixed
         << setprecision(2)
         << averageTicketPrice(events)
         << "\n";

    sortByDateAscending(events);

    cout << "\n=== Events sorted by date (oldest first) ===\n";

    for (const auto& e : events) {
        printEvent(e);
    }

    searchByName(events, "Workshop");

    // Feature calls
    sortByAttendees(events);

    filterByCategory(
        events,
        EventCategory::CONCERT
    );

    exportUpcomingEvents(
        events,
        "upcoming_events.txt"
    );

    // Bonus feature
    filterByMinAttendees(events, 500);

    return 0;
}