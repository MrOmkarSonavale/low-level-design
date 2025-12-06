📝 Document Editor – Low Level Design (C++)

This project is a simple Document Editor designed using Object-Oriented Principles and Polymorphism.
It demonstrates how different document elements (like text and images) can be added and rendered using a clean, extensible design.

📌 Problem Statement

Design a simple Document Editing System that allows users to:

Add text elements

Add image elements

Render the entire document as a combined output

The system must be extensible, meaning new types of document elements can be added in the future without modifying existing code.

🎯 Functional Requirements
1. Add Text

User should be able to insert text into the document.

2. Add Images

User should be able to insert images into the document using a file path.

3. Render Document

System should combine all elements and produce a final rendered output.

Render should be generated only once and then cached for reuse.

4. Extensibility

New document elements (tables, videos, headings, etc.) should be easy to add using inheritance.

🏛️ Design Approach (OOP + Polymorphism)

The system uses:

Abstract Base Class (DocumentElement)
Defines a render() method for polymorphic rendering.

Derived Classes (textElement, imageElement)
Each implements its own rendering logic.

Document Class
Stores all elements and generates the final output.

DocumentEditor Class
Provides a user-friendly interface to add elements and render the final document.

This follows Open/Closed Principle (OCP) — meaning the system is open for extension but closed for modification.

🧱 Class Responsibilities
1. DocumentElement (Abstract Class)

Defines the interface for all document elements.

Contains pure virtual function render().

2. textElement

Stores text

Returns text as-is during rendering

3. imageElement

Stores image path

Renders image as HTML-like tag:

<img src="path">

4. Document

Stores a list of DocumentElement*

Combines all rendered outputs into a single string

5. DocumentEditor

Acts as a façade for clients

Adds text or images into the document

Caches the rendered output for performance




