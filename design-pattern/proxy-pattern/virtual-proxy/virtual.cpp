#include <iostream>

using namespace std;

class Idisplay
{
    virtual void display() = 0;
};

class ImageDisplay : public Idisplay
{
private:
    string path;

public:
    ImageDisplay(string p) : path(p) {};

    void display() override
    {
        cout << "Displaying image from path: " << path << endl;
    }
};

class virtualProxy : public Idisplay
{
private:
    string path;
    ImageDisplay *imageDisplay = nullptr;

public:
    virtualProxy(string p) : path(p) {}

    void display() override
    {
        if (imageDisplay == nullptr)
        {
            cout << "Loading image from path: " << path << endl;
            imageDisplay = new ImageDisplay(path);
        }

        imageDisplay->display();
    }
};

int main(void)
{
    virtualProxy *proxy = new virtualProxy("path/to/image.jpg");
    proxy->display(); // Image is loaded and displayed
    proxy->display(); // Image is displayed without loading again
    return 0;
}