
#include <iostream>
#include <string>
using namespace std;

// Node of the Binary Search Tree
class Component
{
public:
    int id;
    string name;
    string category;
    int quantity;

    Component *left;
    Component *right;

    // Constructor
    Component(int i, string n, string c, int q)
    {
        id = i;
        name = n;
        category = c;
        quantity = q;
        left = nullptr;
        right = nullptr;
    }
};

// Class to manage the inventory using BST
class Inventory
{
private:
    Component *root;

    // Insert a component into the BST
    Component* insertNode(Component *node, int id,
                          string name, string category, int quantity)
    {
        if (node == nullptr)
        {
            return new Component(id, name, category, quantity);
        }

        if (id < node->id)
        {
            node->left = insertNode(node->left, id, name,
                                    category, quantity);
        }
        else if (id > node->id)
        {
            node->right = insertNode(node->right, id, name,
                                     category, quantity);
        }

        return node;
    }

    // Search for a component by ID
    Component* searchNode(Component *node, int id)
    {
        if (node == nullptr || node->id == id)
            return node;

        if (id < node->id)
            return searchNode(node->left, id);

        return searchNode(node->right, id);
    }

    // Find the smallest ID in a subtree
    Component* findMin(Component *node)
    {
        while (node != nullptr && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Delete a component from the BST
    Component* deleteNode(Component *node, int id)
    {
        if (node == nullptr)
            return nullptr;

        if (id < node->id)
        {
            node->left = deleteNode(node->left, id);
        }
        else if (id > node->id)
        {
            node->right = deleteNode(node->right, id);
        }
        else
        {
            // Case 1: No left child
            if (node->left == nullptr)
            {
                Component *temp = node->right;
                delete node;
                return temp;
            }

            // Case 2: No right child
            if (node->right == nullptr)
            {
                Component *temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Component *temp = findMin(node->right);

            node->id = temp->id;
            node->name = temp->name;
            node->category = temp->category;
            node->quantity = temp->quantity;

            node->right = deleteNode(node->right, temp->id);
        }

        return node;
    }

    // Display components in ascending order of ID
    void inorder(Component *node)
    {
        if (node == nullptr)
            return;

        inorder(node->left);

        cout << node->id << "\t"
             << node->name << "\t"
             << node->category << "\t"
             << node->quantity << endl;

        inorder(node->right);
    }

    // Count the number of component records
    int countNodes(Component *node)
    {
        if (node == nullptr)
            return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    // Release dynamically allocated memory
    void clearTree(Component *node)
    {
        if (node == nullptr)
            return;

        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    // Constructor
    Inventory()
    {
        root = nullptr;
    }

    // Add a new component
    void addComponent()
    {
        int id, quantity;
        string name, category;

        cout << "Enter Component ID: ";
        cin >> id;

        if (searchNode(root, id) != nullptr)
        {
            cout << "Component ID already exists!\n";
            return;
        }

        cout << "Enter Component Name (one word): ";
        cin >> name;

        cout << "Enter Category (one word): ";
        cin >> category;

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity < 0)
        {
            cout << "Quantity cannot be negative!\n";
            return;
        }

        root = insertNode(root, id, name, category, quantity);
        cout << "Component added successfully!\n";
    }

    // Search for a component
    void searchComponent()
    {
        int id;

        cout << "Enter Component ID to search: ";
        cin >> id;

        Component *result = searchNode(root, id);

        if (result == nullptr)
        {
            cout << "Component not found!\n";
        }
        else
        {
            cout << "\nComponent Found!\n";
            cout << "ID: " << result->id << endl;
            cout << "Name: " << result->name << endl;
            cout << "Category: " << result->category << endl;
            cout << "Quantity: " << result->quantity << endl;
        }
    }

    // Update the stock quantity
    void updateQuantity()
    {
        int id, quantity;

        cout << "Enter Component ID: ";
        cin >> id;

        Component *result = searchNode(root, id);

        if (result == nullptr)
        {
            cout << "Component not found!\n";
            return;
        }

        cout << "Current Quantity: " << result->quantity << endl;
        cout << "Enter New Quantity: ";
        cin >> quantity;

        if (quantity < 0)
        {
            cout << "Quantity cannot be negative!\n";
            return;
        }

        result->quantity = quantity;
        cout << "Quantity updated successfully!\n";
    }

    // Display all components
    void displayComponents()
    {
        if (root == nullptr)
        {
            cout << "Inventory is empty!\n";
            return;
        }

        cout << "\nID\tName\tCategory\tQuantity\n";
        cout << "----------------------------------------\n";

        inorder(root);
    }

    // Delete a component
    void removeComponent()
    {
        int id;

        cout << "Enter Component ID to delete: ";
        cin >> id;

        if (searchNode(root, id) == nullptr)
        {
            cout << "Component not found!\n";
            return;
        }

        root = deleteNode(root, id);
        cout << "Component deleted successfully!\n";
    }

    // Display total number of component records
    void totalComponents()
    {
        cout << "Total component records: "
             << countNodes(root) << endl;
    }

    // Display component with the smallest ID
    void smallestID()
    {
        Component *temp = findMin(root);

        if (temp == nullptr)
        {
            cout << "Inventory is empty!\n";
            return;
        }

        cout << "Component with smallest ID:\n";
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Category: " << temp->category << endl;
        cout << "Quantity: " << temp->quantity << endl;
    }

    // Destructor
    ~Inventory()
    {
        clearTree(root);
    }
};

// Main function
int main()
{
    Inventory inv;
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << " ELECTRONIC COMPONENTS INVENTORY\n";
        cout << "====================================\n";
        cout << "1. Add Component\n";
        cout << "2. Search Component\n";
        cout << "3. Display All Components\n";
        cout << "4. Update Quantity\n";
        cout << "5. Delete Component\n";
        cout << "6. Count Component Records\n";
        cout << "7. Find Smallest Component ID\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            break;
        }

        switch (choice)
        {
            case 1:
                inv.addComponent();
                break;

            case 2:
                inv.searchComponent();
                break;

            case 3:
                inv.displayComponents();
                break;

            case 4:
                inv.updateQuantity();
                break;

            case 5:
                inv.removeComponent();
                break;

            case 6:
                inv.totalComponents();
                break;

            case 7:
                inv.smallestID();
                break;

            case 8:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
/*PS C:\MinGW\bin> & C:\Users\Asus\Electronics_components_inventory.exe

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 50
Enter Component Name (one word): Resistor1K
Enter Category (one word): 1K
Enter Quantity: 10
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 2
Enter Component ID to search: 50

Component Found!
ID: 50
Name: Resistor1K
Category: 1K
Quantity: 10

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: & C:\Users\Asus\Electronics_components_inventory.exe
Invalid input. Please enter a number.
PS C:\MinGW\bin> 1
1
PS C:\MinGW\bin> & C:\Users\Asus\Electronics_components_inventory.exe

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 105
Enter Component Name (one word): Resistor        
Enter Category (one word): Passive
Enter Quantity: 100
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 80
Enter Component Name (one word): capacitor
Enter Category (one word): passive
Enter Quantity: 50
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 130
Enter Component Name (one word): LED
Enter Category (one word): Optoelectronic
Enter Quantity: 100
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 60
Enter Component Name (one word): Diode
Enter Category (one word): Semiconductor
Enter Quantity: 45
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 90
Enter Component Name (one word): Transistor
Enter Category (one word): Semiconductor
Enter Quantity: 50
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 1
Enter Component ID: 120
Enter Component Name (one word): BreaadBoard
Enter Category (one word): Prototyping_equipment
Enter Quantity: 15
Component added successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 2
Enter Component ID to search: 150
Component not found!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 2
Enter Component ID to search: 80

Component Found!
ID: 80
Name: capacitor
Category: passive
Quantity: 50

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 3

ID      Name    Category        Quantity
----------------------------------------
60      Diode   Semiconductor   45
80      capacitor       passive 50
90      Transistor      Semiconductor   50
105     Resistor        Passive 100
120     BreaadBoard     Prototyping_equipment   15
130     LED     Optoelectronic  100

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 4
Enter Component ID: 80
Current Quantity: 50
Enter New Quantity: 350
Quantity updated successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 6
Total component records: 6

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 7
Component with smallest ID:
ID: 60
Name: Diode
Category: Semiconductor
Quantity: 45

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 5
Enter Component ID to delete: 60
Component deleted successfully!

====================================
 ELECTRONIC COMPONENTS INVENTORY
====================================
1. Add Component
2. Search Component
3. Display All Components
4. Update Quantity
5. Delete Component
6. Count Component Records
7. Find Smallest Component ID
8. Exit
Enter your choice: 8
Thank you for using the system!
PS C:\MinGW\bin> */
