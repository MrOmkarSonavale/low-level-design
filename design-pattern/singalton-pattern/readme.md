Singleton Design Pattern in C++
📌 Overview

This project demonstrates the Singleton Design Pattern implemented in C++.
The Singleton pattern ensures that only one instance of a class exists throughout the lifetime of an application and provides a global access point to that instance.

🧠 Why Singleton?

Use Singleton when:

You need exactly one instance of a class

The object represents a shared resource

Creating multiple instances can cause inconsistent behavior

Common real-world use cases:

Database connection manager

Logger

Configuration manager

Cache

⚙️ Implementation Details
Key Concepts Used

Private constructor → Prevents direct object creation

Static pointer (instance) → Holds the single instance

Static getInstance() method → Controls instance creation

Lazy initialization → Object is created only when needed