#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Product
{
private:
    int sku;
    string name;
    double price;

public:
    Product(int id, string str, double pr)
    {
        this->sku = id;
        this->name = str;
        this->price = pr;
    };

    // getters

    int getSku()
    {
        return this->sku;
    };

    string getName()
    {
        return this->name;
    };

    double getPrice()
    {
        return this->price;
    };
};

class ProductFactory
{
public:
    static Product *createProduct(int sku)
    {
        string name;
        double price;

        if (sku == 101)
        {
            name = "Apple";
            price = 20;
        }
        else if (sku == 102)
        {
            name = "Banana";
            price = 10;
        }
        else if (sku == 103)
        {
            name = "Chocolate";
            price = 50;
        }
        else if (sku == 201)
        {
            name = "T-Shirt";
            price = 500;
        }
        else if (sku == 202)
        {
            name = "Jeans";
            price = 1000;
        }
        else
        {
            name = "Item" + to_string(sku);
            price = 100;
        }
        return new Product(sku, name, price);
    };
};

class InventoryStore
{
public:
    virtual ~InventoryStore() {};
    virtual void addProduct(Product *product, int quantity) = 0;
    virtual void removeProduct(Product *product, int quantity) = 0;
    virtual int checkStock(int sku) = 0;
    virtual vector<Product *> listAvailableProducts() = 0;
};

class DBInventoryStore : public InventoryStore
{
private:
    map<int, int> *stock;          // sku - quantity
    map<int, Product *> *products; // sku - product
public:
    DBInventoryStore()
    {
        stock = new map<int, int>();
        products = new map<int, Product *>();
    };

    ~DBInventoryStore()
    {
        for (auto it : *products)
        {
            delete it.second;
        };
        delete stock;
        delete products;
    };

    void addProduct(Product *pro, int quan) override
    {
        int sku = pro->getSku();

        if (products->count(sku) == 0)
        {

            // mepping the sku to new product
            (*products)[sku] = pro;
        };

        (*stock)[sku] += quan;
    };

    void removeProduct(Product *pro, int quant) override
    {
        // get the sku of the product want to delete
        int sku = pro->getSku();

        // check product is exit or not
        if (skock->count(sku) == 0)
        {
            cout << "Product with SKU " << sku << " does not exist in inventory.\n";
            return;
        };

        int currentStock = (*stock)[sku];
        int remainingStock = currentStock - quant;

        if (remainingStock > 0)
        {
            (*stock)[sku] = remainingStock;
        }
        else
        {
            // remove the product from stock and products map
            stock->erase(sku);
            products->erase(sku);
        }
    };

    int checkStock() override
    {
        // check if stock are exit or not
        if (stock->count(sku) == 0)
        {
            return 0;
        }

        return (*stock)[sku];
    };

    vector<Product *> listAvailableProducts() override
    {
        vector<Product *> available;

        for (auto it : *stock)
        {
            int sku = it.first;
            int quantity = it.second;

            if (quantity > 0)
            {
                available.push_back((*products)[sku]);
            }
        };
        return available;
    };
};

class InventoryManager
{
    InventoryStore *store;

public:
    InventoryManager(InventoryStore *store)
    {
        this->store = store;
    };

    void addStock(int sku, int quant)
    {
        Product *prod = ProductFactory::createProduct(sku);
        store->addProduct(prod, quant);

        count << "Added " << quant << " units of " << prod->getName() << " to inventory.\n";
    }

    void removeStock(int sku, int quant)
    {
        store->removeStock(sku, quant);
    };

    void checkStock(int sku)
    {
        return store->checkStock(sku);
    };

    vector<Product *> getAvailableProduct()
    {
        return store->getAvailableProduct();
    };
};

class ReplenishStreategy
{
public:
    virtual void replenish(InventoryManager *manager, map<int, int> iteamToReplenish) = 0;

    virtual ~ReplenishStreategy() {};
};

class ThresholdReplenishStreategy : public ReplenishStreategy
{
private:
    // threashold for quantity stock
    int threshold;

public:
    ThresholdReplenishStreategy(int threshold)
    {
        this->threshold = threshold;
    };

    void replenish(InventoryManager *manager, map<int, int> itemsToReplen) override
    {
        cout << "[Threshold Replenish] Checking threshold... \n";

        for (auto it : itemsToReplen)
        {
            int sku = it.first;
            int quant = it.second;

            int current = manager->checkStock(sku);

            if (current < threshold)
            {
                manager->addStock(sku, quant);
                cout << " -> sku " << sku << " was " << current << ", replenished by " << quant << endl;
            };
        };
    };
};

class WeeklyReplenishStreategy : public ReplenishStreategy
{
public:
    WeeklyReplenishStreategy() {
    };

    void replenish(InventoryManager *manager, map<int, int> itemsToReplenish) override {
        cout << "[WeeklyReplenish] Weekly replenishment triggered for inventory.\n"
    };
};

class DarkStoree
{
private:
    string name;
    double x, y;
    InventoryManager *inventoryManager;
    ReplenishStreategy *replenishStreategy;

public:
    DarkStoree(string n, double x_coord, double y_coord)
    {
        name = n;
        x = x_coord;
        y = y_coord;

        replenishStreategy = nullptr;
        inventoryManager = new InventoryManager(new DBInventoryStore);
    };

    ~DarkStoree()
    {
        delete inventoryManager;
        if (replenishStreategy)
            delete replenishStreategy;
    };

    void distaceTo(double ux, double uy)
    {
        return sqrt((x - ux) * (x - ux) + (y - uy) * (y - uy));
    };

    void runReplenishment(map<int, int> itemsToReplenish)
    {
        if (replenishStreategy)
        {
            replenishStreategy->replenish(inventoryManager, itemsToReplenish);
        }
    };

    vector<Product *> getAllProduct()
    {
        return inventoryManager->getAvailableProduct();
    };

    void removeStock(int sku, int qty)
    {
        inventoryManager->removeStock(sku, qty);
    };

    void addStock(int sku, int qty)
    {
        Product *prod = ProductFactory::createProduct(sku);

        inventoryManager->addStock(sku, qty);
    };

    void setReplenishStrategy(ReplenishStrategy *str)
    {
        this->replenishStreategy = str;
    };

    string getName()
    {
        return this->name;
    };

    double getXcord()
    {
        return this->x;
    };

    double getYcord()
    {
        return this->y;
    };

    InventoryManager *getInventoryManager()
    {
        return this->inventoryManager;
    };
};

class DarkStoreManager
{
private:
    vector<DarkStoree *> *darkStores;
    static DarkStoreManager *instance;

    DarkStoreManager()
    {
        darkStores = new vector<DarkStoree *>();
    };

public:
    static DarkStoreManager *getInstance()
    {
        if (!instance)
        {
            instance = new DarkStoreManager();
        };

        return instance;
    };

    void registerDarkStore(DarkStoree *ds)
    {
        darkStores->push_back(ds);
    };

    vector<DarkStoree *> getAllNearByDarkStores(double ux, double uy, double maxDis)
    {

        vector<pair<double, DarkStoree *>> distList;

        for (auto ds : *darkStores)
        {
            double d = ds->distaceTo(ux, uy);
            if (d <= maxDis)
            {
                distList.push_back(make_pair(d, ds));
            }
        };

        sort(distList.begin(), distList.end(), [](auto &a, auto &b)
             { return a.first < b.first; });

        vector<DarkStoree *> result;

        for (auto d : distList)
        {
            result.push_back(d.second);
        };

        return result;
    };

    ~DarkStoreManager()
    {
        for (auto ds : *darkStores)
        {
            delete ds;
        };

        delete darkStores;
    };
};

DarkStoreManager *DarkStoreManager::instance = nullptr;

class User
{
public:
    string name;
    double x, y;
    Cart *cart;

    User(string n, double x_coord, double y_coord)
    {
        name = n;
        x = x_coord;
        y = y_coord;
        cart = new Cart();
    };

    ~User()
    {
        delete cart;
    };

    Cart *getCart()
    {
        return this->cart;
    };
};

class Cart
{
public:
    vector<pair<Product *, int>> items;

    void addItem(int sku, int qty)
    {
        Product *prd = ProductFactory::createProduct(sku);

        items.push_back(make_pair(prd, qty));
    };

    double getTotalPrice()
    {
        double total = 0;
        for (auto item : items)
        {
            total += item.first->getPrice() * item.second;
        };
        return total;
    };

    vector<pair<Product *, int>> getItems()
    {
        return items;
    }

    ~Cart()
    {
        for (auto &i : items)
        {
            delete i.first;
        }
    }
};

class DeliveryPartner
{
public:
    string name;

    DeliveryPartner(string n)
    {
        name = n;
    };
};

class Order
{
public:
    static int nextId;
    int orderId;
    User *user;
    vector<pair<Product *, int>> items;
    vector<DeliveryPartner *> partner;
    double totalAmt;

    Order(User *u)
    {
        orderId = nextId++;
        user = u;
        totalAmt = 0.0;
    };
};

int Order::nextId = 1;

class OrderManager
{
private:
    vector<Order *> *orders;
    static OrderManager *instance;

    OrderManager()
    {
        orders = new vector<Order *>();
    };

public:
    static OrderManager *getInstance()
    {
        if (!instance)
        {
            instance = new OrderManager();
        };
        return instance;
    };

    void placeOrder(User *user, Cart *cart)
    {
        cout << "\n [OrderManager] Placing order for user: " << user->name << "\n";

        vector<pair<Product *, int>> requestedItems = cart->getItems();

        // 1 find the nearby dark store within 5km
        double maxdis = 5.0;
        vector<DarkStoree *> nearbyDarkStores = DarkStoreManager::getInstance()->getAllNearByDarkStores(user->x, user->y, maxdis);

        if (nearbyDarkStores.empty())
        {
            cout << "No nearby dark store found for user: " << user->name << "\n";
            return;
        };

        // check if the closest dark store has all the items in stock

        bool containsAll = true;

        DarkStoree *firstStore = nearbyDarkStores[0];

        for (pair<Product *, int> &item : requestedItems)
        {
            int sku = item.first->getSku();
            int qty = item.second;

            if (firstStore->getInventoryManager()->checkStock(sku) < qty)
            {
                containsAll = false;
                break;
            };
        };

        Order *order = new Order(user);

        // if the closest dark store has all the items, place the order there
        if (containsAll)
        {
            cout << "All items at : " << firstStore->getName() << "\n";

            for (pair<Product *, int> &item : requestedItems)
            {
                int sku = item.first->getSku();
                int qty = item.second;

                firstStore->removeStock(sku, qty);
                order->items.push_back(make_pair(item.first, qty));
            };

            order->totalAmt = cart->getTotalPrice();
            order->partner.push_back(new DeliveryPartner("Delivery Partner A"));
        }
        else
        {
            cout << "Splitting order across multiple dark stores for user: " << user->name << "\n";

            map<int, int> allItems;

            for (pair<Product *, int> &item : requestedItems)
            {
                allItems[item.first->getSku()] = item.second;
            };

            int partnerId = 1;

            for (DarkStoree *ds : nearbyDarkStores)
            {
                if (allItems.empty())
                {
                    break;
                };

                cout << "Checking dark store: " << ds->getName() << "\n";

                bool assigned = false;

                vector<int> toRemove;

                for (auto &item : allItems)
                {
                    int availableQuant = ds->getInventoryManager()->checkStock(item.first);

                    if (availableQuant <= 0)
                        continue;

                    // take whichever is smaller between available quantity and requested quantity

                    int takenQty = min(availableQuant, item.second);

                    ds->removeStock(item.first, takenQty);

                    order->items.push_back(make_pair({ProductFactory::createProduct(item.first), takenQty}));

                    if (allItems[item.second] > takenQty)
                    {
                        allItems[item.first] -= takenQty;
                    }
                    else
                    {
                        toRemove.push_back(item.first);
                    };

                    assigned = true;
                };

                // after iterating all the sku in all items , we erase
                //  any fully -statisfied sku from the allItems map

                for (int sku : toRemove)
                {
                    allItems.erase(sku);
                };

                if (assigned)
                {
                    string pname = "Delivery Partner " + to_string(partnerId++);

                    order->partner.push_back(new DeliveryPartner(pname));

                    cout << "Assigned " << pname << " to deliver items from " << ds->getName() << "\n";
                }

                if (!allItems.empty())
                {
                    cout << "Could'nt fulfill the entire order for user: " << user->name << endl

                        for (auto &items : allItems)
                    {
                        cout << " -> SKU " << items.first << ", Quantity: " << items.second << "\n";
                    }
                }

                double sum = 0;

                for (auto &iem : order->items)
                {
                    sum += iem.first->getPrice() * iem.second;
                };

                order->totalAmt = sum;
            };
        };

        cout << "\n [orderManager] Order #" << order->orderId << " placed for user: " << user->name << " with total amount: $" << order->totalAmt << "\n";

        for (auto &item : order->items)
        {
            cout << "    SKU " << item.first->getSku()
                 << " (" << item.first->getName() << ") x" << item.second
                 << " @ ₹" << item.first->getPrice() << "\n";
        };

        cout << " Total: $ " << order->totalAmt << "\n Partners: \n";

        for (auto &dp : order->partner)
        {
            cout << "  - " << dp->name << "\n";
        };

        cout << endl;

        orders->push_back(order);

        // cleanup;
        for (auto *dp : order->partner)
        {
            delete dp;
        }

        for (auto &item : order->items)
        {
            delete item.first;
        };
    };

    vector<Order *> getAllOrders()
    {
        return *orders;
    };

    ~OrderManager()
    {
        for (auto order : *orders)
        {
            delete order;
        };
        delete orders;
    };
};

OrderManager *OrderManager::instance = nullptr;

class ZeptoHelper
{
public:
    static void showAllItems(User *user)
    {
        cout << "\n [zepto] all available products within 5 km for" << user->name << ":\n";

        DarkStoreManager *dsManager = DarkStoreManager::getInstance();

        vector<DarkStoree *> nearbyStore = dsManager->getAllNearByDarkStores(user->x, user->y, 5.0);

        // collect each sku ->price (so we only display each product once);

        map<int, double> skuToPrice;
        map<int, string> skuToName;

        for (DarkStoree *ds : nearbyStore)
        {
            vector<Product *> products = ds->getAllProduct();

            for (Product *prod : products)
            {
                int sku = prod->getSku();

                if (skuToPrice.count(sku) == 0)
                {
                    skuToPrice[sku] = prod->getPrice();
                    skuToName[sku] = prod->getName();
                }
            };
        };

        for (auto &entry : skuToPrice)
        {
            int sku = entry.first;
            double price = entry.second;
            string name = skuToName[sku];
            cout << " -> SKU: " << sku << ", Name: " << name << ", Price: $" << price << "\n";
        };
    };

    static void initialize()
    {
        auto dsManager = DarkStoreManager::getInstance();

        // dark store A
        DarkStoree *DarkStoreA = new DarkStoree("DarkStore A", 0, 0);
        DarkStoreA->setReplenishStrategy(new ThresholdReplenishStreategy(10));

        cout << "\n Adding stock in DarkStore A...\n";
        << endl;

        DarkStoreA->addStock(101, 50);
        DarkStoreA->addStock(102, 20);

        DarkStoree *DarkStoreB = new DarkStoree("DarkStore B", 3, 4);

        DarkStoreB->setReplenishStrategy(new ThresholdReplenishStreategy(5));

        cout << "\n Adding stock in DarkStore B...\n"
             << endl;
        DarkStoreB->addStock(102, 15);
        DarkStoreB->addStock(103, 30);

        DarkStoree *DarkStoreC = new DarkStoree("DarkStore C", 6, 8);
        DarkStoreC->setReplenishStrategy(new ThresholdReplenishStreategy(8));

        cout << "\n Adding stock in DarkStore C...\n"
             << endl;

        DarkStoreC->addStock(101, 25);
        DarkStoreC->addStock(103, 10);

        dsManager->registerDarkStore(DarkStoreA);
        dsManager->registerDarkStore(DarkStoreB);
        dsManager->registerDarkStore(DarkStoreC);
    }
};

int main()
{
    // initialize the system with some dark stores and stock
    ZeptoHelper::initialize();

    User *user1 = new User("Alice", 1, 1);

    cout << "\n User with name " << user1->name << " is browsing available products...\n";

    // show all available products within 5 km for user1
    ZeptoHelper::showAllItems(user1);

    // user add itemds to cart
    cout << "\n User " << user1->name << " is adding items to cart...\n";

    Cart *cart = user1->getCart();

    cart->addItem(101, 5);  // Apple x5
    cart->addItem(102, 10); // Banana x10
    cart->addItem(103, 3);  // Chocolate x3

    OrderManager::getInstance()->placeOrder(user1, cart);

    delete user1;
    delete OrderManager::getInstance();
    delete DarkStoreManager::getInstance();

    return 0;
}