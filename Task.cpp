#include "Task.h"

// Constructor
Task::Task(int id, const std::string& desc, Category cat, Priority prio, const std::string& due)
    : id(id), description(desc), category(cat), priority(prio), status(Status::Pending), dueDate(due) {}

// Getters
int Task::getId() const { return id; }
std::string Task::getDescription() const { return description; }
Category Task::getCategory() const { return category; }
Priority Task::getPriority() const { return priority; }
Status Task::getStatus() const { return status; }
std::string Task::getDueDate() const { return dueDate; }

// Setters
void Task::setDescription(const std::string& desc) { description = desc; }
void Task::setCategory(Category cat) { category = cat; }
void Task::setPriority(Priority prio) { priority = prio; }
void Task::setStatus(Status s) { status = s; }
void Task::setDueDate(const std::string& due) { dueDate = due; }

// Mark complete
void Task::markComplete() { status = Status::Completed; }

// Display Task Info
void Task::display() const {
    std::cout << "ID: " << id << "\n"
              << "Description: " << description << "\n"
              << "Category: " << toString(category) << "\n"
              << "Priority: " << toString(priority) << "\n"
              << "Status: " << toString(status) << "\n";
    if (!dueDate.empty())
        std::cout << "Due Date: " << dueDate << "\n";
    std::cout << "--------------------------\n";
}