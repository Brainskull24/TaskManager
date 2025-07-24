#include<iostream>
using namespace std;

enum class Priority {
    Low,
    Medium,
    High
};

inline string toString(Priority p) {
    switch (p) {
        case Priority::Low: return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High: return "High";
        default: return "Unknown";
    }
}

inline Priority priorityFromString(const std::string& s) {
    if (s == "Low") return Priority::Low;
    if (s == "Medium") return Priority::Medium;
    if (s == "High") return Priority::High;
    throw std::invalid_argument("Invalid Priority: " + s);
}

enum class Category {
    Work,
    Personal,
    Study,
    Other
};

inline string toString(Category c) {
    switch (c) {
        case Category::Work: return "Work";
        case Category::Personal: return "Personal";
        case Category::Study: return "Study";
        case Category::Other: return "Other";
        default: return "Unknown";
    }
}

inline Category categoryFromString(const std::string& s) {
    if (s == "Work") return Category::Work;
    if (s == "Personal") return Category::Personal;
    if (s == "Study") return Category::Study;
    if (s == "Other") return Category::Other;
    throw std::invalid_argument("Invalid Category: " + s);
}

enum class Status {
    Pending,
    Completed,
    Incomplete
};

inline string toString(Status s) {
    switch (s) {
        case Status::Pending: return "Pending";
        case Status::Completed: return "Completed";
        case Status::Incomplete: return "Incomplete";
        default: return "Unknown";
    }
}

inline Status statusFromString(const std::string& s) {
    if (s == "Pending") return Status::Pending;
    if (s == "Completed") return Status::Completed;
    if (s == "Incomplete") return Status::Incomplete;
    throw std::invalid_argument("Invalid Status: " + s);
}
