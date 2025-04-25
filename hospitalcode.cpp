#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// ---------------------
// Linked List-based Patient Record
// ---------------------
class LinkedListPatientRecords
{
    struct PatientNode
    {
        int id;
        string name;
        string diagnosis;
        PatientNode *next;
    } *patientListHead = nullptr;
public:
    void addPatientToLinkedList(int id, const string &name, const string &diagnosis)
    {
        PatientNode *newNode = new PatientNode{id, name, diagnosis, nullptr};
        if (!patientListHead)
        {
            patientListHead = newNode;
        }
        else
        {
            PatientNode *current = patientListHead;
            while (current->next)
                current = current->next;
            current->next = newNode;
        }
        cout << "Patient " << name << " added." << endl;
    }

    void displayPatientLinkedList()
    {
        cout << "\n--- Patient Records  ---" << endl;
        if (!patientListHead)
        {
            cout << "No patients." << endl;
            return;
        }
        PatientNode *current = patientListHead;
        while (current)
        {
            cout << "ID: " << current->id << ", Name: " << current->name
                 << ", Diagnosis: " << current->diagnosis << endl;
            current = current->next;
        }
    }

    bool getPatientById(int id, string &name, string &diagnosis)
    {
        PatientNode *current = patientListHead;
        while (current)
        {
            if (current->id == id)
            {
                name = current->name;
                diagnosis = current->diagnosis;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// ---------------------
// Emergency Room Queue
// ---------------------
class EmergencyRoomQueue
{
public:
    struct ERPatient
    {
        int id;
        string name;
        string diagnosis;
    };

    queue<ERPatient> emergencyRoomQueue;
    int nextID = 1;

    void admitToER(const string &name, const string &diagnosis)
    {
        ERPatient patient = {nextID++, name, diagnosis};
        emergencyRoomQueue.push(patient);
        cout << "Patient added to Emergency Room: " << name << " (" << diagnosis << ")" << endl;
    }

    void treatNextInER()
    {
        if (!emergencyRoomQueue.empty())
        {
            ERPatient patient = emergencyRoomQueue.front();
            cout << "Treating Patient ID " << patient.id << ": " << patient.name
                 << " (" << patient.diagnosis << ")" << endl;
            emergencyRoomQueue.pop();
        }
        else
        {
            cout << "Emergency Room is empty." << endl;
        }
    }

    void displayERQueue()
    {
        cout << "\n--- Emergency Room Queue ---" << endl;
        if (emergencyRoomQueue.empty())
        {
            cout << "No patients in queue." << endl;
            return;
        }
        queue<ERPatient> tempQueue = emergencyRoomQueue;
        while (!tempQueue.empty())
        {
            ERPatient patient = tempQueue.front();
            cout << "ID: " << patient.id << " | Name: " << patient.name
                 << " | Diagnosis: " << patient.diagnosis << endl;
            tempQueue.pop();
        }
    }
};

// ---------------------
// Stack-based Treatment Log
// ---------------------
class TreatmentStack
{
    static const int MAX_TREATMENTS = 10000;
    int top;

public:
    string treatmentLog[MAX_TREATMENTS];
    TreatmentStack() : top(-1) {}

    bool logTreatment(const string &treatmentName)
    {
        if (top >= MAX_TREATMENTS - 1)
        {
            cout << "Treatment log overflow!" << endl;
            return false;
        }
        treatmentLog[++top] = treatmentName;
        cout << "Logged: \"" << treatmentName << "\"" << endl;
        return true;
    }

    string undoLastTreatment()
    {
        if (top >= 0)
        {
            string undone = treatmentLog[top--];
            cout << "Undone: \"" << undone << "\"" << endl;
            return undone;
        }
        cout << "No treatments to undo." << endl;
        return "";
    }
};

// ---------------------
// Priority Queue for Critical Patients
// ---------------------
class CriticalPatientPriorityQueue
{
    struct CriticalPatient
    {
        string name;
        int critical;
        CriticalPatient *next;
        CriticalPatient(string n, int c)
        {
            name = n;
            critical = c;
            next = nullptr;
        }
    } *front = nullptr, *rear = nullptr;

public:
    void insertPatient(string name, int critical)
    {
        CriticalPatient *newPatient = new CriticalPatient(name, critical);
        if (!front || front->critical > critical)
        {
            newPatient->next = front;
            front = newPatient;
            if (!rear)
                rear = newPatient;
            return;
        }
        CriticalPatient *current = front;
        while (current->next && current->next->critical <= critical)
            current = current->next;
        newPatient->next = current->next;
        current->next = newPatient;
        if (!newPatient->next)
            rear = newPatient;
    }

    void displayCriticalPatients()
    {
        cout << "\n--- Critical Patients (Priority) ---" << endl;
        if (!front)
        {
            cout << "No critical patients in the list." << endl;
            return;
        }
        CriticalPatient *current = front;
        while (current)
        {
            cout << "Patient: " << current->name << " | Critical Level: " << current->critical << endl;
            current = current->next;
        }
    }
};

// ---------------------
// Main
// ---------------------
int main()
{
    LinkedListPatientRecords listSystem;
    EmergencyRoomQueue erQueue;
    TreatmentStack treatmentLog;
    CriticalPatientPriorityQueue priorityQueue;

    int choice;
    do
    {
        cout << "\n==== Connected Hospital System Menu ====\n"
             << "1. Add Patient \n"
             << "2. Display Patients List\n"
             << "3. Admit Linked List Patient to ER\n"
             << "4. Display ER Queue\n"
             << "5. Treat Next Patient in ER\n"
             << "6. Log Treatment for ER Front\n"
             << "7. Move ER Front to Critical Queue\n"
             << "8. Display Critical Patients\n"
             << "9. Undo Last Treatment\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 9)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter number 0-9: ";
            cin >> choice;
        }
        cin.ignore();

        string name, diagnosis, doctor;
        int id, critical;

        switch (choice)
        {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Diagnosis: ";
            getline(cin, diagnosis);
            listSystem.addPatientToLinkedList(id, name, diagnosis);
            break;
        case 2:
            listSystem.displayPatientLinkedList();
            break;
        case 3:
            listSystem.displayPatientLinkedList();
            cout << "Enter ID to admit to ER: ";
            cin >> id;
            cin.ignore();
            if (listSystem.getPatientById(id, name, diagnosis))
            {
                erQueue.admitToER(name, diagnosis);
            }
            else
            {
                cout << "Patient ID not found in Linked List." << endl;
            }
            break;
        case 4:
            erQueue.displayERQueue();
            break;
        case 5:
            erQueue.treatNextInER();
            break;
        case 6:
            if (!erQueue.emergencyRoomQueue.empty())
            {
                auto p = erQueue.emergencyRoomQueue.front();
                treatmentLog.logTreatment("Treated: " + p.name);
            }
            else
            {
                cout << "ER is empty." << endl;
            }
            break;
        case 7:
            if (!erQueue.emergencyRoomQueue.empty())
            {
                auto p = erQueue.emergencyRoomQueue.front();
                cout << "Enter critical level for " << p.name << ": ";
                cin >> critical;
                cin.ignore();
                priorityQueue.insertPatient(p.name, critical);
            }
            else
            {
                cout << "ER is empty." << endl;
            }
            break;
        case 8:
            priorityQueue.displayCriticalPatients();
            break;
        case 9:
            treatmentLog.undoLastTreatment();
            break;
        case 0:
            cout << "Exiting system. Goodbye!" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
