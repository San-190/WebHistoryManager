# WebHistoryManager

A comprehensive web browser history management system developed in C++ as part of a Data Structures course. This project implements a complete navigation history manager with support for tabs, bookmarks, searching, and session management.

## 🎓 Educational Purpose

This project was developed for educational purposes as part of the **Data Structures** course at **Universidad Nacional de Costa Rica**. It demonstrates the practical implementation of linear data structures and algorithms in a real-world scenario.

## ✨ Features

### Core Functionality
- **Navigation History**: Navigate backward and forward through visited websites in correct order
- **Tab Management**: Support for multiple tabs with individual navigation histories
- **Bookmark System**: Mark visited pages with tag support for organization
- **Search and Filtering**: Search through history and bookmarks with various filters
- **Private Navigation**: Incognito mode that doesn't record history or bookmarks
- **Import/Export**: Save and restore browsing sessions including all tabs and bookmarks
- **History Policies**: Customizable policies for history management (entry limits, time-based cleanup)

### Technical Features
- **Binary Serialization**: Efficient disk space usage through binary file storage
- **Optimal Complexity**: Algorithms maintain optimal time complexity
- **Memory Management**: Proper memory allocation and deallocation
- **Exception Handling**: Custom exception classes for robust error handling

## 🎯 Project Objectives

- **Research**: Investigate the application of linear data structures
- **Implementation**: Implement linear data structures from scratch
- **Algorithms**: Implement search, sorting, and data serialization mechanisms
- **Optimization**: Maintain optimal algorithmic complexity in all implemented functions

## 🔧 Technical Requirements

- **IDE**: Visual Studio Community 2022
- **Language**: C++
- **Paradigm**: Object-Oriented Programming
- **Storage**: Binary file format for data persistence
- **Testing**: Unit testing implementation

## 🏗️ Architecture

### Core Classes

- **`Controladora`**: Main controller managing user interactions and menu navigation
- **`Historial`**: Manages the complete browsing history and tab collection
- **`Pestana`**: Represents individual browser tabs with their own history
- **`Sitio`**: Represents individual website entries with URL, title, and domain
- **`Bookmark`**: Manages bookmarked sites with tag support
- **`Limitador`**: Implements time-based policies for history management
- **`Configuracion`**: Singleton pattern for global configuration management
- **`Interfaz`**: Handles all user interface interactions

### Exception Handling
- **`ExcCadVacia`**: Handles empty string exceptions
- **`ExcValor`**: Handles invalid value exceptions

## 🚀 Usage

### Main Menu Options

1. **Go to Website**: Navigate to a specific URL
2. **Site Options**: Manage bookmarks and tags for current site
3. **New Tab**: Create a new browsing tab
4. **Search & Filters**: Search through history and bookmarks
5. **Incognito Mode**: Enable private browsing
6. **Import/Export**: Save or load browsing sessions
7. **Configuration**: Adjust history policies and limits
8. **Exit**: Close the application

### Navigation Controls

- Use arrow keys to navigate through history
- Switch between tabs using the interface
- Add/remove bookmarks and tags as needed

## 📊 Key Algorithms

- **Binary Search**: Using `std::lower_bound` for efficient site lookup
- **Sorting**: Custom comparators for site ordering
- **Serialization**: Binary file I/O for data persistence
- **Time-based Cleanup**: Automatic expiration of old entries

---

*This README was created to provide comprehensive documentation for the WebHistoryManager project, showcasing both technical implementation and educational value.*