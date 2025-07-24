#pragma once
#include <vector>
#include <string>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;  // Auto-increment ID for each task

public:
    TaskManager();

    // Core operations
    void addTask(const std::string& desc, Category cat, Priority prio, const std::string& due = "");
    void deleteTask(int id);
    void editTask(int id);
    void completeTask(int id);

    // List/Display
    void listAllTasks() const;
    void listByCategory(Category cat) const;
    void listByPriority(Priority prio) const;
    void listByStatus(Status s) const;

    // Persistence
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Helper
    Task* findTaskById(int id);
};
