#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>   // for getenv and strtol
#include <stack>
#include <fstream>  


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
int main() {
    cout << "Content-type: text/html\n\n";

    string input;
    getline(cin, input);

    auto decode = [](const string& str) {
        string result;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '+') result += ' ';
            else if (str[i] == '%' && i + 2 < str.length()) {
                string hex = str.substr(i + 1, 2);
                result += static_cast<char>(strtol(hex.c_str(), nullptr, 16));
                i += 2;
            } else result += str[i];
        }
        return result;
    };

    auto getValue = [&](const string& key) -> string {
        size_t pos = input.find(key + "=");
        if (pos == string::npos) return "";
        size_t start = pos + key.length() + 1;
        size_t end = input.find("&", start);
        return decode(input.substr(start, end - start));
    };

    string id = getValue("id");
    string name = getValue("name");
    string diagnosis = getValue("diagnosis");
    string critical = getValue("critical");
    string emergency = getValue("emergency");
    string time = getValue("time");
    string treatment = getValue("treatment");
    string doctor = getValue("doctor");

    cout << "<html><body style='font-family:sans-serif'>";

    if (!name.empty() && !diagnosis.empty()) {
        // Patient record
        ofstream out("C:\\xampp\\htdocs\\hospitalsystem\\patients.txt", ios::app);
        out << "ID: " << id << ", Name: " << name << ", Diagnosis: " << diagnosis
            << ", Critical: " << critical << endl;
        out.close();
        cout << "<h2>Patient Info Saved</h2>";
    }
    else if (!emergency.empty() && !time.empty()) {
        // Emergency record
        ofstream out("C:\\xampp\\htdocs\\hospitalsystem\\emergency.txt", ios::app);
        out << "ID: " << id << ", Emergency: " << emergency << ", Time: " << time << endl;
        out.close();
        cout << "<h2>🚑 Emergency Info Saved</h2>";
    }
    else if (!treatment.empty() && !doctor.empty()) {
        // Treatment record
        ofstream out("C:\\xampp\\htdocs\\hospitalsystem\\treatments.txt", ios::app);
        out << "ID: " << id << ", Treatment: " << treatment << ", Doctor: " << doctor << endl;
        out.close();
        cout << "<h2>Treatment Info Saved</h2>";
    }
    else {
        cout << "<p style='color:red'>Invalid submission or missing fields.</p>";
    }

    cout << "</body></html>";
    return 0;
}
