The Decorator Pattern is a structural design pattern that allows you to add new behavior to an object dynamically, without modifying its existing code.

It works by wrapping an object inside another object (a decorator) that adds extra functionality.

📌 Problem It Solves

Sometimes you want to add features to objects:

❌ Without creating a huge number of subclasses

❌ Without changing existing class code

Example problem:

You have a Coffee class.
Now you want Milk, Sugar, Whipped Cream, etc.
Creating subclasses for every combination quickly becomes messy.

✅ Solution (Decorator Pattern)

Instead of inheritance:

Use composition

Wrap the original object with decorators

Each decorator adds its own behavior

🧠 Key Idea

"Wrap an object to extend its behavior at runtime."