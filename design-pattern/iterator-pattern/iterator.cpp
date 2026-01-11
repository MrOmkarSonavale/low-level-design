#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

template <typename T>
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

template <typename T>
class Iterable
{
public:
    virtual Iterator<T> *getIterator() = 0;
};

class LinkList : public Iterable<int>
{
public:
    int data;
    LinkList *next;

    LinkList(int val)
    {
        data = val;
        next = nullptr;
    }

    Iterator<int> *getIterator() override;
};

class BinearyTree : public Iterable<int>
{
public:
    int data;
    BinearyTree *left;
    BinearyTree *right;

    BinearyTree(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }

    Iterator<int> *getIterator() override;
};

class Song
{
public:
    string name;
    string artist;

    Song(string n, string a)
    {
        name = n;
        artist = a;
    }
};

class Playlist : public Iterable<Song *>
{
public:
    vector<Song *> items;

    void addSong(Song *s)
    {
        items.push_back(s);
    }

    Iterator<Song *> *getIterator() override;
};

class LinkListIterator : public Iterator<int>
{
private:
    LinkList *curr;

public:
    LinkListIterator(LinkList *head)
    {
        curr = head;
    }

    bool hasNext() override
    {
        return curr != nullptr;
    }

    int next() override
    {
        int val = curr->data;
        curr = curr->next;
        return val;
    }
};

class BinearyTreeIterator : public Iterator<int>
{
private:
    stack<BinearyTree *> st;

    void pushLeft(BinearyTree *node)
    {
        while (node)
        {
            st.push(node);
            node = node->left;
        }
    }

public:
    BinearyTreeIterator(BinearyTree *root)
    {
        pushLeft(root);
    }

    bool hasNext() override
    {
        return !st.empty();
    }

    int next() override
    {
        BinearyTree *node = st.top();
        st.pop();

        int val = node->data;

        if (node->right)
        {
            pushLeft(node->right);
        }

        return val;
    }
};

/* ===================== Playlist Iterator ===================== */
class PlayListIterator : public Iterator<Song *>
{
private:
    vector<Song *> &songs;
    size_t index;

public:
    PlayListIterator(vector<Song *> &s)
        : songs(s), index(0) {}

    bool hasNext() override
    {
        return index < songs.size();
    }

    Song *next() override
    {
        return songs[index++];
    }
};

Iterator<int> *LinkList::getIterator()
{
    return new LinkListIterator(this);
}

Iterator<int> *BinearyTree::getIterator()
{
    return new BinearyTreeIterator(this);
}

Iterator<Song *> *Playlist::getIterator()
{
    return new PlayListIterator(items);
}

int main()
{
    /* Linked List */
    LinkList *l1 = new LinkList(1);
    l1->next = new LinkList(2);
    l1->next->next = new LinkList(3);

    Iterator<int> *listIt = l1->getIterator();
    while (listIt->hasNext())
    {
        cout << listIt->next() << " ";
    }
    cout << endl;

    /* Binary Tree */
    BinearyTree *tree = new BinearyTree(1);
    tree->left = new BinearyTree(2);
    tree->right = new BinearyTree(3);

    Iterator<int> *treeIt = tree->getIterator();
    while (treeIt->hasNext())
    {
        cout << treeIt->next() << " ";
    }
    cout << endl;

    /* Playlist */
    Playlist *pl = new Playlist();
    pl->addSong(new Song("Song1", "Artist1"));
    pl->addSong(new Song("Song2", "Artist2"));

    Iterator<Song *> *playIt = pl->getIterator();
    while (playIt->hasNext())
    {
        Song *s = playIt->next();
        cout << "Title: " << s->name
             << ", Artist: " << s->artist << endl;
    }

    return 0;
}
