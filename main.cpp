#include <iostream>
#include "TaskManager.h"

int main() {
    TaskManager manager;
    const std::string filename = "tasks.csv";

    manager.loadFromFile(filename);

    int choice;
    do {
        std::cout << "\n📋 Task Manager CLI\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Edit Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Mark Task as Completed\n";
        std::cout << "6. Filter Tasks by Category\n";
        std::cout << "7. Save & Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();  // Clear newline
                std::string desc, due;
                int catInt, prioInt;

                std::cout << "Enter description: ";
                std::getline(std::cin, desc);

                std::cout << "Select category (0=Work, 1=Personal, 2=Study, 3=Other): ";
                std::cin >> catInt;

                std::cout << "Select priority (0=Low, 1=Medium, 2=High): ";
                std::cin >> prioInt;

                std::cin.ignore();  // Clear newline
                std::cout << "Enter due date (optional, format YYYY-MM-DD): ";
                std::getline(std::cin, due);

                manager.addTask(desc, static_cast<Category>(catInt), static_cast<Priority>(prioInt), due);
                break;
            }
            case 2:
                manager.listAllTasks();
                break;
            case 3: {
                int id;
                std::cin.ignore();
                std::cout << "Enter task ID to edit: ";
                std::cin >> id;
                manager.editTask(id);
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter task ID to delete: ";
                std::cin >> id;
                manager.deleteTask(id);
                break;
            }
            case 5: {
                int id;
                std::cout << "Enter task ID to mark as completed: ";
                std::cin >> id;
                manager.completeTask(id);
                break;
            }
            case 6: {
                int catInt;
                std::cout << "Enter category to filter (0=Work, 1=Personal, 2=Study, 3=Other): ";
                std::cin >> catInt;
                manager.listByCategory(static_cast<Category>(catInt));
                break;
            }
            case 7:
                manager.saveToFile(filename);
                std::cout << "👋 Exiting. Tasks saved.\n";
                break;
            default:
                std::cout << "❌ Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
