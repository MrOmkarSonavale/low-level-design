#include <iostream>
#include <string>
#include <vector>

using namespace std;

// abstract class

class DocumentElement
{
public:
    virtual string render() const = 0; // Pure virtual function for rendering
};

class textElement : public DocumentElement
{
private:
    string text;

public:
    textElement(const string &text) : text(text) {};

    string render() const override
    {
        return text;
    };
};

class imageElement : public DocumentElement
{
private:
    string imagePath;

public:
    imageElement(const string &path) : imagePath(path) {};

    string render() const override
    {
        return "<img src=\"" + imagePath + "\">";
    }
};

class Document
{
private:
    vector<DocumentElement *> elements;

public:
    void addElement(DocumentElement *element)
    {
        elements.push_back(element);
    };

    string render()
    {
        string result;

        for (const auto &element : elements)
        {
            result += element->render() + "\n";
        }

        return result;
    }
};

class DocumentEditor
{
private:
    Document *document;
    string renderedDocument;

public:
    DocumentEditor(Document *doc) : document(doc) {};

    void addText(const string &text)
    {
        document->addElement(new textElement(text));
    }

    void addImage(const string &imagePath)
    {
        document->addElement(new imageElement(imagePath));
    }

    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            renderedDocument = document->render();
        }

        return renderedDocument;
    }
};

int main(void)
{
    Document *doc = new Document();
    DocumentEditor *editor = new DocumentEditor(doc);
    editor->addText("This is a sample document.");
    editor->addImage("image1.jpg");
    editor->addText("This document contains an image.");
    cout << editor->renderDocument() << endl;
    return 0;
}