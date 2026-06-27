interface Iterator<T> {
    hasNext(): boolean;
    next(): T;
}

interface Iterable<T> {
    getIterator(): Iterator<T>;
}

// ---------------- Linked List ----------------
class LinkList implements Iterable<number> {
    public next: LinkList | null;
    public data: number;

    constructor(data: number, next: LinkList | null = null) {
        this.data = data;
        this.next = next;
    }

    getIterator(): Iterator<number> {
        return new LinkListIterator(this);
    }
}

class LinkListIterator implements Iterator<number> {
    private head: LinkList | null;

    constructor(curr: LinkList) {
        this.head = curr;
    }

    hasNext(): boolean {
        return this.head !== null;
    }

    next(): number {
        if (!this.head) {
            throw new Error("No more elements");
        }

        const val = this.head.data;
        this.head = this.head.next;

        return val;
    }
}

// ---------------- Binary Tree ----------------
class BinaryTree implements Iterable<number> {
    public left: BinaryTree | null;
    public right: BinaryTree | null;
    public data: number;

    constructor(data: number) {
        this.data = data;
        this.left = null;
        this.right = null;
    }

    getIterator(): Iterator<number> {
        return new BinaryTreeIterator(this);
    }
}

class BinaryTreeIterator implements Iterator<number> {
    private stack: BinaryTree[] = [];

    constructor(root: BinaryTree) {
        this.pushLeft(root);
    }

    private pushLeft(node: BinaryTree | null): void {
        while (node) {
            this.stack.push(node);
            node = node.left;
        }
    }

    hasNext(): boolean {
        return this.stack.length > 0;
    }

    next(): number {
        if (!this.hasNext()) {
            throw new Error("No more elements");
        }

        const node = this.stack.pop()!;

        if (node.right) {
            this.pushLeft(node.right);
        }

        return node.data;
    }
}

// ---------------- Playlist ----------------
class Song {
    constructor(
        public title: string,
        public artist: string
    ) { }
}

class PlayList implements Iterable<Song> {
    private songs: Song[] = [];

    addSong(song: Song): void {
        this.songs.push(song);
    }

    getIterator(): Iterator<Song> {
        return new PlayListIterator(this.songs);
    }
}

class PlayListIterator implements Iterator<Song> {
    private index: number = 0;

    constructor(private songs: Song[]) { }

    hasNext(): boolean {
        return this.index < this.songs.length;
    }

    next(): Song {
        if (!this.hasNext()) {
            throw new Error("No more elements");
        }

        return this.songs[this.index++];
    }
}

// ---------------- Client Code ----------------
const list = new LinkList(1);
list.next = new LinkList(2);
list.next.next = new LinkList(3);

console.log("Linked List:");
const listIterator = list.getIterator();

while (listIterator.hasNext()) {
    console.log(listIterator.next());
}

const tree = new BinaryTree(1);
tree.left = new BinaryTree(2);
tree.right = new BinaryTree(3);

console.log("\nBinary Tree:");
const treeIterator = tree.getIterator();

while (treeIterator.hasNext()) {
    console.log(treeIterator.next());
}

const playlist = new PlayList();

playlist.addSong(new Song("Song1", "Artist1"));
playlist.addSong(new Song("Song2", "Artist2"));

console.log("\nPlaylist:");
const playlistIterator = playlist.getIterator();

while (playlistIterator.hasNext()) {
    const song = playlistIterator.next();
    console.log(`${song.title} - ${song.artist}`);
}