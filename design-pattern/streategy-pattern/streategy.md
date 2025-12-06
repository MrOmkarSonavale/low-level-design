🤖 Robot Behavior System (Strategy Pattern) – C++

This project demonstrates how to dynamically change a robot’s walk and talk behaviors at runtime using the Strategy Design Pattern in C++.

📌 Problem Statement

Design a robot system where:

Different robots can walk differently (normal walk, no walk).

Different robots can talk differently (normal talk, no talk).

Behaviors should be changeable at runtime without modifying the Robot class.

🎯 Functional Requirements

Robot should be able to walk using selected walking behavior.

Robot should be able to talk using selected talking behavior.

System must support adding new behaviors in the future.

🏛️ Design Used: Strategy Pattern

Behaviors are separated into independent classes:

Walking Strategies

normalwalk

nowalk

Talking Strategies

normalTalk

noTalk

Robot class contains these strategies and calls them when needed.

🚀 Future Enhancements

Add fly behavior

Add dance behavior

Add robot types (Humanoid, Pet Robot, Industrial Robot)