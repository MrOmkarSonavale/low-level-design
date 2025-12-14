Factory Design Patterns 🍔🍕

A practical guide with Simple Factory, Factory Method, and Abstract Factory

📌 Overview

Factory Design Patterns are creational patterns that help create objects without tightly coupling client code to concrete classes.

This repository demonstrates three types of factory patterns using a Food Ordering System (Burger & Pizza) implemented in TypeScript.

🏗️ Types of Factory Patterns Covered

Simple Factory

Factory Method

Abstract Factory

1️⃣ Simple Factory Pattern
🔹 What it is

A single factory class that creates objects based on input conditions.

❗ Not an official GoF pattern, but widely used in practice.

🔹 Structure
Client → SimpleFactory → Product

🔹 Example Idea
BurgerFactory.createBurger("basic");

🔹 When to Use

Object creation logic is simple

Few product types

No need for extensibility