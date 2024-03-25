#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <iomanip>
#include <istream>
#include <string>
#include <sstream>

using namespace std;

struct Task {
    string name;
    string description;
    chrono::system_clock::time_point due_time;
};

void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task name: ";
    getline(cin, newTask.name);
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    cout << "Enter due date and time (format as such mm-dd-yy hh:mm): ";
    string dueTimeString;
    getline(cin, dueTimeString);
    istringstream iss(dueTimeString);
    int year, month, day, hour, minute;
    char dash, colon;
    iss >> month >> dash >> day >> dash >> year >> hour >> colon >> minute;
    struct tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    time_t dueTime = mktime(&tm);
    newTask.due_time = chrono::system_clock::from_time_t(dueTime);
    tasks.push_back(newTask);
    cout << "Task added successfully!\n";
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "Tasks:\n";
    for (const auto& task : tasks) {
        time_t dueTime = chrono::system_clock::to_time_t(task.due_time);
        cout << "Name: " << task.name << endl;
        cout << "Description: " << task.description << endl;
        cout << "Due Time: " << put_time(localtime(&dueTime), "%D %R") << endl;
        cout << "------------------------------\n" << endl;
    }
}

void checkReminders(const vector<Task>& tasks) {
    auto currentTime = chrono::system_clock::now();
    for (const auto& task : tasks) {
        if (task.due_time <= currentTime) {
            time_t dueTime = chrono::system_clock::to_time_t(task.due_time);
            cout << "Reminder: Task '" << task.name << "' is due now!\n";
        }
    }
}

int main() {
    vector<Task> tasks;

    while (true) {
        cout << "\nTask Scheduler\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Check Reminders\n";
        cout << "4. Exit\n";
        cout << "Enter Your Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                checkReminders(tasks);
                break;
            case 4:
                cout << "Exiting Program.\n";
                return 0;
            default:
                cout << "Invalid Choice. Please pick a number between 1-4.\n";
        }
    }
    return 0;
}
