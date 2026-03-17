#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include <string>
#include <chrono>

using namespace std;

class AsteriodFlyweight
{
private:
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;

public:
    AsteriodFlyweight(int l, int w, int wt, string c, string t, string m)
        : length(l), width(w), weight(wt), color(c), texture(t), material(m) {}

    void render(int posX, int posY, int velocityX, int velocityY) const
    {
        cout << "Rendering Asteriod at (" << posX << ", " << posY << ") with velocity ("
             << velocityX << ", " << velocityY << ") and properties: "
             << "Length: " << length << ", Width: " << width
             << ", Weight: " << weight << ", Color: " << color
             << ", Texture: " << texture << ", Material: " << material
             << endl;
    }

    static size_t getMemoryUsage()
    {
        return sizeof(int) * 3 + sizeof(string) * 3 + 32 * 3;
    }
};

class AsteriodFactory
{
private:
    static unordered_map<string, AsteriodFlyweight *> asteriods;

public:
    static AsteriodFlyweight *getAsteriod(int length, int width, int weight, string color, string texture, string material)
    {
        string key = to_string(length) + "-" + to_string(width) + "-" + to_string(weight) + "-" + color + "-" + texture + "-" + material;

        if (asteriods.find(key) == asteriods.end())
        {
            asteriods[key] = new AsteriodFlyweight(length, width, weight, color, texture, material);
        }

        return asteriods[key];
    }

    static int getFlyweightCount()
    {
        return asteriods.size();
    };

    static size_t getTotalMemoryUsage()
    {
        return asteriods.size() * AsteriodFlyweight::getMemoryUsage();
    };

    static void cleanup()
    {
        asteriods.clear();
    }
};

unordered_map<string, AsteriodFlyweight *> AsteriodFactory::asteriods;

class AsteriodContext
{
private:
    int posX, posY;
    int velocityX, velocityY;
    AsteriodFlyweight *flyweight;

public:
    AsteriodContext(int x, int y, int vx, int vy, AsteriodFlyweight *fw)
        : posX(x), posY(y), velocityX(vx), velocityY(vy), flyweight(fw) {};

    void render()
    {
        flyweight->render(posX, posY, velocityX, velocityY);
    };

    static size_t getMemoryUsage()
    {
        return sizeof(int) * 4 + sizeof(AsteriodFlyweight *);
    };
};

class spaceGamewithFlyweight
{
private:
    static vector<AsteriodContext *> asteriods;

public:
    void spawnAsteriods(int count)
    {
        vector<string> color = {"Red", "Blue", "Gray"};
        vector<string> texture = {"Rocky", "Metallic", "Icy"};
        vector<string> material = {"Iron", "Silicon", "Carbon"};
        int size[] = {10, 20, 30};
        for (int i = 0; i < count; i++)
        {
            int type = i % 3;
            AsteriodFlyweight *flyweight = AsteriodFactory::getAsteriod(
                size[type], size[type], size[type] * 10,
                color[type], texture[type], material[type]);

            asteriods.push_back(new AsteriodContext(
                rand() % 100, rand() % 100, 1, 2, flyweight));
        }
    };

    void renderALL()
    {
        for (int i = 0; i < min(5, (int)asteriods.size()); i++)
        {
            asteriods[i]->render();
        }
    };

    static size_t calculateMemoryUsage()
    {
        size_t contextMemory = asteriods.size() * AsteriodContext::getMemoryUsage();
        size_t flyweightMemory = AsteriodFactory::getTotalMemoryUsage();
        return contextMemory + flyweightMemory;
    };

    int getAsteriodCount()
    {
        return asteriods.size();
    };
};

vector<AsteriodContext *> spaceGamewithFlyweight::asteriods;

int main(void)
{
    const int ASTRIOD_COUNT = 10000;

    cout << "Testing with Flyweight" << endl;
    spaceGamewithFlyweight *game = new spaceGamewithFlyweight();

    game->spawnAsteriods(ASTRIOD_COUNT);
    game->renderALL();

    size_t totalMemoryUsage = game->calculateMemoryUsage();

    cout << "\n === Memory Usage ===" << endl;
    cout << "Total Asteriods: " << ASTRIOD_COUNT << endl;

    cout << "Memory per Asteriod: " << AsteriodFlyweight::getMemoryUsage() << " bytes" << endl;

    cout << "Total Memory Usage: " << totalMemoryUsage << " bytes" << endl;
    cout << "Total Memory Usage: " << totalMemoryUsage / (1024) << "KM" << endl;

    AsteriodFactory::cleanup();
    return 0;
}