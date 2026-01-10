abstract class FileSystem {
    abstract getName(): string;
    abstract getSize(): number;
    abstract openAll(indent: number): void;
    abstract ls(indent: number): void;
    abstract changeFolder(file: string): FileSystem | null;
    abstract isFolder(): boolean;
};

class File extends FileSystem {
    private name: string;
    private size: number;

    constructor(name: string, size: number) {
        super();
        this.name = name;
        this.size = size;
    };

    getName(): string {
        return this.name;
    };

    getSize(): number {
        return this.size;
    };

    ls(indent: number = 1): void {
        console.log(`${" ".repeat(indent)}File: ${this.name} (${this.size})`);
    };

    openAll(indent: number = 1): void {
        console.log(`${" ".repeat(indent)}Opening file: ${this.name}`);
    };

    changeFolder(f: string): FileSystem | null {
        return null;
    };

    isFolder(): boolean {
        return false;
    };
};

class Folder extends FileSystem {
    private name: string;
    private items: FileSystem[] = [];

    constructor(name: string) {
        super();
        this.name = name;
    };

    addItem(fileSystem: FileSystem): void {
        this.items.push(fileSystem);
    };

    getName(): string {
        return this.name;
    };

    getSize(): number {
        let size: number = 0;

        for (let item of this.items) {
            size += item.getSize();
        };
        return size;
    };

    ls(indent: number = 1): void {
        console.log(`${" ".repeat(indent)}Folder: ${this.name}`);
        for (let item of this.items) {
            item.ls(indent + 2);
        };
    };

    openAll(indent: number = 1): void {
        console.log(`${" ".repeat(indent)}Opening folder: ${this.name}`);
        for (let item of this.items) {
            item.openAll(indent + 2);
        };
    };

    changeFolder(f: string): FileSystem | null {
        for (let item of this.items) {
            if (item.isFolder() && item.getName() === f) {
                return item;
            }
        };
        return null;
    };

    isFolder(): boolean {
        return true;
    };
};


// usage (your style)

let file1 = new Folder("dsa");

file1.addItem(new File("binarySearch.cpp", 1));
file1.addItem(new File("trie.cpp", 1));
file1.addItem(new File("binaryTree.cpp", 1));

let file2 = new Folder("practice");

file2.addItem(new File("sql_practice", 1));
file2.addItem(new File("mongodb_practice", 1));

file1.addItem(file2);

// test
file1.ls(0);
console.log("Total size:", file1.getSize());

let cmd = file1.changeFolder("practice");
cmd?.ls(2);
