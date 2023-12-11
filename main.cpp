#include <iostream>
#include <string>

using namespace std;

// Salvador Mendoza 
// This funciton will add a new Description and a new ID.
void addTask(std::string* description, int* ID, int& taskDescription_Size, int& ID_Size) 
{
    // Check if description size or ID size is greater than 100
    if (taskDescription_Size >= 100 || ID_Size >= 100)
    {
        std::cout << "\nSize reached limit. Please delete at least 1 task.\n" << std::endl;
        return;
    }

    std::string inputDescription;
    int inputID;

    // Enter task description
    cout << "\nEnter new task description: ";
    cin >> inputDescription;

    bool ExistingID;
    // Enter ID input and check if ID exist
    do
    {
        ExistingID = false;     // False by default whenever this while loop is called
        
        // Enter task ID number
        cout << "Enter task ID: ";
        cin >> inputID;
        
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input\n" << endl;;
            ExistingID = true;     // Set to true in order to reset while loop
        }
        else if (inputID < 1)
        {
            cout << "\nInput must be greater than zero\n" << endl;
            ExistingID = true;     // Set to true in order to reset while loop
        }
        else
        {
            // Search for ID in system
            for (int i = 0; i < ID_Size; ++i)
            {
                int ID_from_list = ID[i];   // Get current ID from list

                // Check if current ID matches the ID input
                if (ID_from_list == inputID)
                {
                    ExistingID = true;
                    break;
                }
            }

            // If existing ID is found, while loop will reset and user will be prompted to enter ID again
            if (ExistingID)
            {
                cout << "\nID already exist\n" << endl;
            }
        }
    }
    while (ExistingID);

    // Add description and ID in their arrays
    description[taskDescription_Size] = inputDescription;
    ID[ID_Size] = inputID;

    // Increment description size and ID size after new description and ID is added to their arrays
    taskDescription_Size++;
    ID_Size++;
    
    cout << "\nTask description " << inputDescription << " and ID number " << inputID << " added\n" << endl;
}

// Delete task description and task ID with matched ID input
// Marquise Williams
void deleteTask(std::string* description, int* ID, int& taskDescription_Size, int& ID_Size)
{
    // Checks if task description or ID is empty
    // If either size is empty, exit out of function
    if (taskDescription_Size <= 0 || ID_Size <= 0)
    {
        std::cout << "\nTask description or ID is empty\n\n";
        return;
    }

    int findID;
    int userAttempts = 3;   // Number of attempts
    bool HasFoundID = false;

    // User is prompt to enter ID that will be searched in system
    while (!HasFoundID)
    {
        // Enter user ID
        std::cout << "\nAttempts: " << userAttempts << std::endl;
        std::cout << "Enter ID number: ";
        cin >> findID;

        // Check if input failed 
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            std::cout << "\nInvalid input" << std::endl;
        }
        else if (findID < 1)    // Print if ID input is less than 1
        {
            std::cout << "\nInput must be greater than zero" << std::endl;
        }
        else
        {
            // Search for the ID
            // If task ID matches ID input, remove matched description and ID from arrays at their positions
            for (int i = 0; i < ID_Size; i++)
            {
                if (findID == ID[i])
                {
                    std::cout << "\nTask description " << description[i] << " and ID number " << ID[i] << " removed\n" << std::endl;
                    for (int j = i; j < ID_Size; j++)
                    {
                        // Remove description and ID in their arrays
                        description[j] = description[j + 1];
                        ID[j] = ID[j + 1];
                    }

                    // Decrease description and ID size by 1 after removal
                    taskDescription_Size--; 
                    ID_Size--;
                    HasFoundID = true;
                    break;
                }
            }

            // Check if ID input wasn't found in ID array
            if (!HasFoundID)
            {
                std::cout << "\nID not found" << std::endl;

                // Decrease attempts by 1
                userAttempts--;

                // Checks if user has no more attempts. 
                // If true, exit out of function. 
                if (userAttempts <= 0)
                {
                    std::cout << "\nOut of attempts. Please try again\n" << std::endl;
                    return;
                }
            }
        }
    }
}

// Print each task description and ID number
// Joseph Green
void listTasks(std::string* description, int* ID, int& taskDescription_Size, int& ID_Size)
{
    // Chek if task description size or ID size is empty
    if (taskDescription_Size <= 0 || ID_Size <= 0)
    {
        cout << "\nTask descripiton or task ID is empty\n" << endl;
        return;
    }

    // Print out each description and ID number
    cout << endl;
    for (int i = 0; i < taskDescription_Size; i++)
    {
        std::cout << "Task " << i + 1 << " - Description: " << description[i] << " | ID: " << ID[i] << std::endl;
    }
    cout << endl;
}

int main()
{
    const int MAX = 100;    // Max number of elements allowed in array
    std::string* taskDescription = new std::string[MAX];    // Task description array that holds up to 100 descriptions
    int* taskID = new int[MAX]; // Task ID array that holds up to 100 IDs
    int DescriptionSize = 0;    // Description size for description array 
    int ID_Size = 0;    // ID size for ID array

    bool Running = true;    // Program is running until changed to false

    cout << endl;
    while (Running)
    {
        char selection;

        // User is prompted to choose an option by entering a letter
        std::cout << "Choose an option" << endl;
        std::cout << "A. Add task\n";   // Add task to system
        std::cout << "B. Delete task\n";    // Delete a task from system
        std::cout << "C. Print task\n"; // Print all task descriptions with ID
        std::cout << "D. Exit\n\n";     // Exit program
        std::cout << "Selection: ";

        cin >> selection;

        switch (selection)
        {
            case 'a':
            case 'A':
                // Call add task function
                addTask(taskDescription, taskID, DescriptionSize, ID_Size);
                break;

            case 'b':
            case 'B':
                // Call delete task function
                deleteTask(taskDescription, taskID, DescriptionSize, ID_Size);
                break;

            case 'c':
            case 'C':
                // Call list tasks function
                listTasks(taskDescription, taskID, DescriptionSize, ID_Size);
                break;

            case 'd':
            case 'D':
                // Delete both array pointers and exit program
                Running = false;
                delete[] taskDescription;
                delete[] taskID;
                break;

            default:
                // Print if input is not a character 
                std::cout << "\nInvalid input or selection\n\n";
                break;
        }
    }

    return 0;
}