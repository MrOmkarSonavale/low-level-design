interface Iterator<T> {
    hasNext(): boolean;
    next(): T;
};

interface Iterable<T> {
    getIterator(): Iterator<T>;
};

// ---------------- Linked List ----------------
class LinkList implements Iterable<number> {
    protected next: LinkList | null;
    protected data: number;

    constructor(data: number, next: LinkList | null = null) {
        this.data = data;
        this.next = next;
    };

    getIterator(): Iterator<number> {
        return new LinkListIterator(this);
    }
};

class LinkListIterator implements Iterator<number> {
    private head: LinkList | null;

    constructor(curr: LinkList) {
        this.head = curr;
    };

    hasNext(): boolean {
        return this.head !== null;
    }

    next(): number {
        if (!this.head) throw new Error("No more elements");
        const val = this.head.data;
        this.head = this.head.next;
        return val;
    }
};

// ---------------- Binary Tree ----------------
class BinaryTree implements Iterable<number> {
    protected left: BinaryTree | null;
    protected right: BinaryTree | null;
    protected data: number;

    constructor(data: number) {
        this.data = data;
        this.left = this.right = null;
    };

    getIterator(): Iterator<number> {
        return new BinaryTreeIterator(this);
    };
};

class BinaryTreeIterator implements Iterator<number> {
    private stack: BinaryTree[] = [];

    constructor(btree: BinaryTree) {
        this.pushLeft(btree);
    };

    private pushLeft(btree: BinaryTree | null): void {
        while (btree) {
            this.stack.push(btree);
            btree = btree.left;
        };
    };

    hasNext(): boolean {
        return this.stack.length > 0;
    };

    next(): number {
        if (!this.hasNext()) throw new Error("No more elements");

        const node = this.stack.pop()!;
        if (node.right) {
            this.pushLeft(node.right);
        }
        return node.data;
    }
};

// ---------------- Playlist ----------------
class Song {
    public title: string;
    public artist: string;

    constructor(title: string, artist: string) {
        this.title = title;
        this.artist = artist;
    };
};

class PlayList implements Iterable<Song> {
    private songs: Song[] = [];

    addSong(song: Song) {
        this.songs.push(song);
    };

    getIterator(): Iterator<Song> {
        return new PlayListIterator(this.songs);
    };
};

class PlayListIterator implements Iterator<Song> {
    private listSong: Song[] = [];
    private index: number = 0;

    constructor(song: Song[]) {
        this.listSong = song;
    };

    hasNext(): boolean {
        return this.index < this.listSong.length;
    };

    next(): Song {
        if (!this.hasNext()) throw new Error("No more elements");
        return this.listSong[this.index++];
    }
};

// ---------------- Client Code ----------------
const list = new LinkList(1);
list.next = new LinkList(2);
list.next.next = new LinkList(3);

const listIterator = list.getIterator();
console.log("LinkedList:");
while (listIterator.hasNext()) {
    console.log(listIterator.next());
}

const tree = new BinaryTree(1);
tree.left = new BinaryTree(2);
tree.right = new BinaryTree(3);

const treeIterator = tree.getIterator();
console.log("\nBinaryTree (Inorder):");
while (treeIterator.hasNext()) {
    console.log(treeIterator.next());
}

const playlist = new PlayList();
playlist.addSong(new Song("Song1", "Artist1"));
playlist.addSong(new Song("Song2", "Artist2"));

const playlistIterator = playlist.getIterator();
console.log("\nPlaylist:");
while (playlistIterator.hasNext()) {
    const s = playlistIterator.next();
    console.log(`Title: ${s.title}, Artist: ${s.artist}`);
}
