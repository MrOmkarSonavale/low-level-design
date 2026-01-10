#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileSystem
{
public:
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual string getName() = 0;
    virtual int getSize() = 0;
    virtual bool isFolder() = 0;
    virtual FileSystem *changeFolder(const string &name) = 0;
    virtual ~FileSystem() {}
};

class File : public FileSystem
{
private:
    string name;
    int size;

public:
    File(string name, int size) : name(name), size(size) {}

    void ls(int indent) override
    {
        cout << string(indent, ' ') << "File: " << name
             << " (" << size << " bytes)" << endl;
    }

    void openAll(int indent) override
    {
        cout << string(indent, ' ') << "Opening file: " << name << endl;
    }

    string getName() override
    {
        return name;
    }

    int getSize() override
    {
        return size;
    }

    bool isFolder() override
    {
        return false;
    }

    FileSystem *changeFolder(const string &) override
    {
        return nullptr;
    }
};

class Folder : public FileSystem
{
private:
    string name;
    vector<FileSystem *> fs;

public:
    Folder(string name) : name(name) {}

    void addItem(FileSystem *f)
    {
        fs.push_back(f);
    }

    void ls(int indent) override
    {
        cout << string(indent, ' ') << "Folder: " << name << endl;
        for (auto f : fs)
        {
            f->ls(indent + 4);
        }
    }

    void openAll(int indent) override
    {
        cout << string(indent, ' ') << "Opening folder: " << name << endl;
        for (auto f : fs)
        {
            f->openAll(indent + 4);
        }
    }

    int getSize() override
    {
        int size = 0;
        for (auto f : fs)
        {
            size += f->getSize();
        }
        return size;
    }

    string getName() override
    {
        return name;
    }

    bool isFolder() override
    {
        return true;
    }

    FileSystem *changeFolder(const string &name) override
    {
        for (auto f : fs)
        {
            if (f->isFolder() && f->getName() == name)
            {
                return f;
            }
        }
        return nullptr;
    }

    ~Folder()
    {
        for (auto f : fs)
            delete f;
    }
};

int main()
{
    Folder *root = new Folder("open-contribution");

    root->addItem(new File("javascript.js", 1));
    root->addItem(new File("typescript.js", 1));

    Folder *project = new Folder("project");
    project->addItem(new File("index.java", 1));
    project->addItem(new File("main.java", 1));

    root->addItem(project);

    cout << "Total size: " << root->getSize() << endl;
    root->ls(0);
    root->openAll(0);

    FileSystem *cmd = root->changeFolder("project");
    if (cmd)
    {
        cout << "\nChanged directory to: " << cmd->getName() << endl;
        cmd->ls();
    }

    delete root;
    return 0;
}
