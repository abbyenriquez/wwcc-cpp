#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>

using namespace std;

enum class Department {
    ENGINEERING,
    SALES,
    HR,
    OPERATIONS
};

constexpr double OVERTIME_THRESHOLD = 40.0;
constexpr double OVERTIME_MULTIPLIER = 1.5;
constexpr double MAX_WEEKLY_HOURS = 168.0;

struct Employee {
    string name;
    Department dept;

    // BUG: hourlyRate was int which removed decimal values
    // FIX: Changed hourlyRate to double
    double hourlyRate;

    double hoursWorked;
};

// Returns the display name for a department
string deptName(Department d) {

    switch (d) {

        case Department::ENGINEERING:
            return "Engineering";

        case Department::SALES:
            return "Sales";

        case Department::HR:
            return "HR";

        case Department::OPERATIONS:
            return "Operations";

        // BUG: No default return path
        // FIX: Added default case to avoid undefined behavior
        default:
            return "Unknown";
    }
}

// Validate hours input
bool validHours(double hours) {

    // BUG: Only checked upper limit
    // FIX: Added lower bound validation for negative hours
    if (hours < 0 || hours > MAX_WEEKLY_HOURS) {

        cout << "Error: hours must be between 0 and "
             << MAX_WEEKLY_HOURS
             << "\n";

        return false;
    }

    return true;
}

// Calculate weekly pay
double calculatePay(const Employee& e) {

    if (e.hoursWorked <= OVERTIME_THRESHOLD) {

        return e.hoursWorked * e.hourlyRate;

    } else {

        // BUG: Overtime multiplier applied to ALL hours
        // FIX: Apply overtime only to hours above threshold
        double regularPay =
            OVERTIME_THRESHOLD * e.hourlyRate;

        double overtimeHours =
            e.hoursWorked - OVERTIME_THRESHOLD;

        double overtimePay =
            overtimeHours
            * e.hourlyRate
            * OVERTIME_MULTIPLIER;

        return regularPay + overtimePay;
    }
}

// Display one employee
void printEmployee(const Employee& e) {

    cout << left
         << setw(20) << e.name
         << setw(14) << deptName(e.dept)

         << right
         << setw(8)
         << fixed
         << setprecision(2)
         << e.hoursWorked
         << " hrs"

         << setw(12)
         << ("$" + to_string(e.hourlyRate))

         << setw(14)
         << ("$" + to_string(calculatePay(e)))

         << "\n";
}

// Display all employees
void displayAll(const vector<Employee>& employees) {

    cout << "\n=== Employee Time Report ===\n";

    cout << left
         << setw(20) << "Name"
         << setw(14) << "Department"

         << right
         << setw(8) << "Hours"
         << setw(12) << "Rate"
         << setw(14) << "Pay"
         << "\n";

    cout << string(70, '-') << "\n";

    for (const auto& emp : employees) {
        printEmployee(emp);
    }
}

// Calculate total payroll cost
double totalPayroll(const vector<Employee>& employees) {

    return accumulate(

        employees.begin(),
        employees.end(),

        // BUG: Initial value was int 0
        // FIX: Changed to double 0.0
        0.0,

        [](double sum, const Employee& e) {

            return sum + calculatePay(e);
        }
    );
}

// Feature 1
// Sort employees by hours worked
void sortByHours(vector<Employee>& employees) {

    sort(

        employees.begin(),
        employees.end(),

        [](const Employee& a, const Employee& b) {

            return a.hoursWorked > b.hoursWorked;
        }
    );

    cout << "\n=== Hours Ranking ===\n";

    for (const auto& emp : employees) {
        printEmployee(emp);
    }
}

// Feature 2
// Department statistics
void getDepartmentStats(
    const vector<Employee>& employees,
    Department dept
) {

    vector<Employee> filtered;

    copy_if(

        employees.begin(),
        employees.end(),

        back_inserter(filtered),

        [dept](const Employee& e) {

            return e.dept == dept;
        }
    );

    cout << "\n=== "
         << deptName(dept)
         << " Department Stats ===\n";

    if (filtered.empty()) {

        cout << "No employees found.\n";

        return;
    }

    double totalHours = 0.0;
    double totalPay = 0.0;

    for (const auto& emp : filtered) {

        totalHours += emp.hoursWorked;

        totalPay += calculatePay(emp);
    }

    double avgPay =
        totalPay / filtered.size();

    cout << "Employee count: "
         << filtered.size()
         << endl;

    cout << "Total hours: "
         << totalHours
         << endl;

    cout << "Average pay: $"
         << fixed
         << setprecision(2)
         << avgPay
         << endl;
}

// Feature 3
// Export payroll report
void exportPayrollReport(
    const vector<Employee>& employees,
    const string& filename
) {

    ofstream outFile(filename);

    if (!outFile) {

        cout << "Error opening file.\n";

        return;
    }

    vector<Department> departments = {

        Department::ENGINEERING,
        Department::SALES,
        Department::HR,
        Department::OPERATIONS
    };

    for (const auto& dept : departments) {

        outFile << "\n=== "
                << deptName(dept)
                << " ===\n";

        double subtotal = 0.0;

        for (const auto& emp : employees) {

            if (emp.dept == dept) {

                double pay =
                    calculatePay(emp);

                outFile << emp.name
                        << " - $"
                        << fixed
                        << setprecision(2)
                        << pay
                        << endl;

                subtotal += pay;
            }
        }

        outFile << "Subtotal: $"
                << fixed
                << setprecision(2)
                << subtotal
                << "\n";
    }

    outFile.close();

    cout << "\nPayroll report saved to "
         << filename
         << endl;
}

// Bonus feature
void findHighEarners(
    const vector<Employee>& employees,
    double threshold
) {

    vector<Employee> highEarners;

    copy_if(

        employees.begin(),
        employees.end(),

        back_inserter(highEarners),

        [threshold](const Employee& e) {

            return calculatePay(e) > threshold;
        }
    );

    cout << "\n=== High Earners ===\n";

    for (const auto& emp : highEarners) {

        printEmployee(emp);
    }
}

int main() {

    vector<Employee> employees = {

        {
            "Alice Chen",
            Department::ENGINEERING,
            42.0,
            45.0
        },

        {
            "Bob Martinez",
            Department::SALES,
            28.0,
            38.0
        },

        {
            "Carol Singh",
            Department::HR,
            35.5,
            32.5
        },

        {
            "David Park",
            Department::ENGINEERING,
            38.0,
            50.0
        },

        {
            "Emma Wilson",
            Department::OPERATIONS,
            30.0,
            29.0
        },

        {
            "Frank Torres",
            Department::SALES,
            45.0,
            44.5
        },

        {
            "Grace Kim",
            Department::HR,
            33.5,
            33.5
        },

        {
            "Henry Okafor",
            Department::OPERATIONS,
            29.0,
            55.0
        }
    };

    cout << "=== HR Time Tracker ===\n";

    cout << "\nValidating hours entry -5: "
         << (validHours(-5)
             ? "valid"
             : "invalid")
         << "\n";

    displayAll(employees);

    cout << "\nTotal payroll this week: $"
         << fixed
         << setprecision(2)
         << totalPayroll(employees)
         << "\n";

    // Feature calls
    sortByHours(employees);

    getDepartmentStats(
        employees,
        Department::ENGINEERING
    );

    exportPayrollReport(
        employees,
        "payroll_report.txt"
    );

    // Bonus feature
    findHighEarners(employees, 1800);

    return 0;
}