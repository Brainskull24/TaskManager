#include "TaskManager.h"
#include <iostream>
#include <fstream> // For file I/O
#include <sstream> // for std::getline, std::stringstream

TaskManager::TaskManager() : nextId(1)
{
    // Optional: loadFromFile("tasks.txt");
}

void TaskManager::addTask(const std::string &desc, Category cat, Priority prio, const std::string &due)
{
    Task newTask(nextId, desc, cat, prio, due);
    tasks.push_back(newTask);
    std::cout << "✅ Task added with ID: " << nextId << "\n";
    nextId++;
}

void TaskManager::listAllTasks() const
{
    if (tasks.empty())
    {
        std::cout << "No tasks to display.\n";
        return;
    }

    std::cout << "\n==== All Tasks ====\n";
    for (const Task &task : tasks)
    {
        task.display();
    }
}

Task *TaskManager::findTaskById(int id)
{
    for (Task &task : tasks)
    {
        if (task.getId() == id)
        {
            return &task;
        }
    }
    return nullptr;
}

void TaskManager::deleteTask(int id)
{
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task &t)
                             { return t.getId() == id; });

    if (it != tasks.end())
    {
        tasks.erase(it, tasks.end());
        std::cout << "🗑️ Task with ID " << id << " deleted.\n";
    }
    else
    {
        std::cout << "❌ Task with ID " << id << " not found.\n";
    }
}

void TaskManager::completeTask(int id)
{
    Task *task = findTaskById(id);
    if (task)
    {
        task->markComplete();
        std::cout << "✅ Task marked as completed.\n";
    }
    else
    {
        std::cout << "❌ Task with ID " << id << " not found.\n";
    }
}

void TaskManager::editTask(int id)
{
    Task *task = findTaskById(id);
    if (!task)
    {
        std::cout << "❌ Task with ID " << id << " not found.\n";
        return;
    }

    std::string newDesc, due;
    int catChoice, prioChoice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush leftover newline
    std::cout << "Enter new description (or press Enter to keep): ";
    std::getline(std::cin, newDesc); // read full line

    if (!newDesc.empty())
        task->setDescription(newDesc);

    std::cout << "Choose new category (0: Work, 1: Personal, 2: Study, 3: Other, -1 to skip): ";
    std::cin >> catChoice;
    if (catChoice >= 0 && catChoice <= 3)
    {
        task->setCategory(static_cast<Category>(catChoice));
    }

    std::cout << "Choose new priority (0: Low, 1: Medium, 2: High, -1 to skip): ";
    std::cin >> prioChoice;
    if (prioChoice >= 0 && prioChoice <= 2)
    {
        task->setPriority(static_cast<Priority>(prioChoice));
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush again
    std::cout << "Enter new due date (YYYY-MM-DD) or press Enter to keep: ";
    std::getline(std::cin, due);

    if (!due.empty())
        task->setDueDate(due);

    std::cout << "✏️ Task updated.\n";
}

void TaskManager::listByCategory(Category cat) const
{
    bool found = false;
    std::cout << "\n==== Tasks in category: " << toString(cat) << " ====\n";
    for (const Task &task : tasks)
    {
        if (task.getCategory() == cat)
        {
            task.display();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No tasks found in this category.\n";
    }
}

void TaskManager::listByPriority(Priority pr) const
{
    bool found = false;
    std::cout << "\n==== Tasks in priority: " << toString(pr) << " ====\n";
    for (const Task &task : tasks)
    {
        if (task.getPriority() == pr)
        {
            task.display();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No tasks found in this priority.\n";
    }
}

void TaskManager::listByStatus(Status s) const
{
    bool found = false;
    std::cout << "\n==== Tasks by status: " << toString(s) << " ====\n";
    for (const Task &task : tasks)
    {
        if (task.getStatus() == s)
        {
            task.display();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No tasks found for this status.\n";
    }
}

void TaskManager::saveToFile(const std::string &filename) const
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cout << "❌ Could not open file for saving.\n";
        return;
    }

    for (const Task &task : tasks)
    {
        outFile << task.getId() << ","
                << task.getDescription() << ","
                << toString(task.getCategory()) << ","
                << toString(task.getPriority()) << ","
                << toString(task.getStatus()) << ","
                << task.getDueDate() << "\n";
    }

    outFile.close();
    std::cout << "💾 Tasks saved to " << filename << "\n";
}

void TaskManager::loadFromFile(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cout << "⚠️ No existing task file found.\n";
        return;
    }

    tasks.clear();
    std::string line;
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string idStr, desc, catStr, prioStr, statusStr, due;

        std::getline(ss, idStr, ',');
        std::getline(ss, desc, ',');
        std::getline(ss, catStr, ',');
        std::getline(ss, prioStr, ',');
        std::getline(ss, statusStr, ',');
        std::getline(ss, due);

        try
        {
            int id = std::stoi(idStr);
            Category cat = categoryFromString(catStr);
            Priority prio = priorityFromString(prioStr);
            Status stat = statusFromString(statusStr);

            Task task(id, desc, cat, prio, due);
            task.setStatus(stat);
            tasks.push_back(task);
            nextId = std::max(nextId, id + 1);
        }
        catch (...)
        {
            std::cout << "⚠️ Skipping malformed line: " << line << "\n";
        }
    }

    inFile.close();
    std::cout << "📂 Loaded tasks from " << filename << "\n";
}