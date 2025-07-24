#pragma once
#include <string>
#include <iostream>
#include "Enums.h"  
using namespace std;

class Task {
private:
    int id;
    string description;
    Category category;
    Priority priority;
    Status status;
    std::string dueDate; 

public:
    Task(int id, const std::string& desc, Category cat, Priority prio, const std::string& due = "");

    int getId() const;
    std::string getDescription() const;
    Category getCategory() const;
    Priority getPriority() const;
    Status getStatus() const;
    std::string getDueDate() const;

    void setDescription(const std::string& desc);
    void setCategory(Category cat);
    void setPriority(Priority prio);
    void setStatus(Status s);
    void setDueDate(const std::string& due);

    void markComplete();
    void display() const;
};
