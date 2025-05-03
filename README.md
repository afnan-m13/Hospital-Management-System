# 🏥 HealZone Hospital Management System (C++ + HTML + CGI)

This project simulates a fully functional hospital management system using core data structures in C++, a styled HTML interface, and CGI for connecting backend and frontend. Developed for the Spring 2025 *Data Structures & Algorithms* course at Effat University.

## 💡 Features

- ✅ **Linked List** for patient record management  
- 🚑 **Queue** for Emergency Room operations  
- 🩺 **Stack** to undo recent treatment records  
- ⚠️ **Priority Queue** for handling critical patient priority levels  
- 🌐 **HTML Web Interface** with navigation for Patient, Emergency, and Treatment forms  
- 🔁 **CGI Backend Integration** that saves form submissions into output files

## 📁 File Structure

| File/Folder              | Description                                      |
|--------------------------|--------------------------------------------------|
| `hospitalcode.cpp`       | Main logic for the system (C++ with file handling) |
| `hospitalcode.cgi`       | Compiled CGI binary for web submission handling  |
| `hospitalinterface.html` | Web interface with form navigation               |
| `hospitalLogo.png`       | Hospital branding/logo used in header            |
| `patients.txt`           | Stores patient record submissions                |
| `emergency.txt`          | Stores emergency room queue data                 |
| `treatments.txt`         | Stores treatment record submissions              |
| `output/`                | Optional: compiled output (e.g., `.exe`, `.cgi`) |
| `README.md`              | Project overview and usage instructions          |

## ⚙️ How to Run Locally

### 🧠 Prerequisites
- A C++ compiler (e.g. g++)
- [XAMPP](https://www.apachefriends.org/) for running CGI on localhost
- Files placed under: `C:\xampp\htdocs\hospitalsystem`

### 🔧 Compile and Deploy
```bash
g++ hospitalcode.cpp -o hospitalcode.cgi
copy hospitalcode.cgi C:\xampp\cgi-bin\hospitalcode.cgi
