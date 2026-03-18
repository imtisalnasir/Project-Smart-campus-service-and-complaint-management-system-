#include <iostream>
#include <string>
using namespace std;
struct Complaint
{
    int id;
    string studentName;
    string serviceName;
    string complaintText;
    Complaint* next;
};

class CampusComplaintList
{
private:
    Complaint* head;

public:
    CampusComplaintList()
    {
        head = NULL;
    }

    Complaint* addNewComplaint(int id, string name, string service, string text)
    {
        Complaint* n = new Complaint();
        n->id = id;
        n->studentName = name;
        n->serviceName = service;
        n->complaintText = text;
        n->next = NULL;

        if (head == NULL)
            head = n;
        else
        {
            Complaint* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = n;
        }

        return n;
    }

    void showAllComplaints()
    {
        if (head == NULL)
        {
            cout << "No complaints found.\n";
            return;
        }

        Complaint* temp = head;
        while (temp != NULL)
        {
            cout << "\nID: " << temp->id;
            cout << "\nStudent: " << temp->studentName;
            cout << "\nService: " << temp->serviceName;
            cout << "\nComplaint: " << temp->complaintText << endl;
            temp = temp->next;
        }
    }
};
struct QNode
{
    Complaint* data;
    QNode* next;
};

class PendingQueue
{
private:
    QNode* front;
    QNode* rear;

public:
    PendingQueue()
    {
        front = rear = NULL;
    }

    void enqueue(Complaint* c)
    {
        QNode* n = new QNode();
        n->data = c;
        n->next = NULL;

        if (rear == NULL)
        {
            front = rear = n;
            return;
        }

        rear->next = n;
        rear = n;
    }

    Complaint* dequeue()
    {
        if (front == NULL)
            return NULL;

        QNode* temp = front;
        Complaint* c = temp->data;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
        return c;
    }

    bool isEmpty()
    {
        return front == NULL;
    }
};
struct SNode
{
    Complaint* data;
    SNode* next;
};

class SolvedStack
{
private:
    SNode* top;

public:
    SolvedStack()
    {
        top = NULL;
    }

    void push(Complaint* c)
    {
        SNode* n = new SNode();
        n->data = c;
        n->next = top;
        top = n;
    }

    void displaySolved()
    {
        if (top == NULL)
        {
            cout << "No resolved complaints.\n";
            return;
        }

        SNode* temp = top;
        while (temp != NULL)
        {
            cout << "ID: " << temp->data->id
                 << " | Student: " << temp->data->studentName
                 << " | Service: " << temp->data->serviceName << endl;
            temp = temp->next;
        }
    }
};
struct TreeNode
{
    string name;
    TreeNode* left;
    TreeNode* right;
};

class ServiceCategoryTree
{
public:
    TreeNode* root;

    ServiceCategoryTree()
    {
        root = new TreeNode();
        root->name = "Campus Services";
        root->left = NULL;
        root->right = NULL;

        root->left = new TreeNode();
        root->left->name = "Academic Services";
        root->left->left = NULL;
        root->left->right = NULL;

        root->right = new TreeNode();
        root->right->name = "Administration Services";
        root->right->left = NULL;
        root->right->right = NULL;

        root->left->left = new TreeNode();
        root->left->left->name = "Library";
        root->left->left->left = NULL;
        root->left->left->right = NULL;

        root->left->right = new TreeNode();
        root->left->right->name = "LMS / Portal";
        root->left->right->left = NULL;
        root->left->right->right = NULL;

        root->right->left = new TreeNode();
        root->right->left->name = "Accounts Office";
        root->right->left->left = NULL;
        root->right->left->right = NULL;

        root->right->right = new TreeNode();
        root->right->right->name = "Classroom / Furniture";
        root->right->right->left = NULL;
        root->right->right->right = NULL;
    }

    void display(TreeNode* node, int level = 0)
    {
        if (node == NULL)
            return;

        for (int i = 0; i < level; i++)
            cout << "   ";

        cout << "- " << node->name << endl;

        display(node->left, level + 1);
        display(node->right, level + 1);
    }
};

int main()
{
    CampusComplaintList complaintList;
    PendingQueue pendingQueue;
    SolvedStack solvedStack;
    ServiceCategoryTree categoryTree;

    int choice;
    int idCounter = 1;

    do
    {
        cout << "\n------ Smart Campus Service & Complaint Management System ------\n";
        cout << "1. Register new complaint\n";
        cout << "2. Show all complaints\n";
        cout << "3. Process next complaint\n";
        cout << "4. Show resolved complaints\n";
        cout << "5. Show service category tree\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string name, service, text;

            cout << "Student name: ";
            getline(cin, name);

            cout << "Service name: ";
            getline(cin, service);

            cout << "Complaint text: ";
            getline(cin, text);

            Complaint* c = complaintList.addNewComplaint(idCounter, name, service, text);
            pendingQueue.enqueue(c);

            cout << "Complaint registered with ID: " << idCounter << endl;
            idCounter++;
        }

        else if (choice == 2)
        {
            complaintList.showAllComplaints();
        }

        else if (choice == 3)
        {
            if (pendingQueue.isEmpty())
            {
                cout << "No pending complaints.\n";
            }
            else
            {
                Complaint* c = pendingQueue.dequeue();
                cout << "Processing complaint ID: " << c->id << endl;
                solvedStack.push(c);
                cout << "Complaint marked as resolved.\n";
            }
        }

        else if (choice == 4)
        {
            solvedStack.displaySolved();
        }
        else if (choice == 5)
        {
            categoryTree.display(categoryTree.root);
        }

    } while (choice != 0);

    return 0;
}