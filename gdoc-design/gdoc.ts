abstract class documentElement {
    abstract render(): string;
};

class textElement extends documentElement {
    private text: string;
    constructor(text: string) {
        super();
        this.text = text;
    }

    render(): string {
        return this.text;
    }
};


class imageElement extends documentElement {
    private path: string;

    constructor(path: string) {
        super();
        this.path = path;
    };

    render(): string {
        return this.path;
    }
};

class gdocument {
    private element: documentElement[]
        = [];

    addElement(element: documentElement): void {
        this.element.push(element);
    };

    render(): string {
        let result = "";

        for (const ele of this.element) {
            result += ele.render() + '\n';
        }

        return result;
    };
}

class googleDoc {
    private gdoc: gdocument;

    constructor(doc: gdocument) {
        this.gdoc = doc;
    };


    addText(text: string): void {
        this.gdoc.addElement(new textElement(text));
    };


    addImage(url: string): void {
        this.gdoc.addElement(new imageElement(url));
    };

    render(): string {
        return this.gdoc.render();
    };

};

const myDoc = new gdocument();
const googleDocument = new googleDoc(myDoc);

googleDocument.addText("Hello, this is a sample text. ");
googleDocument.addImage("https://example.com/image.png");
googleDocument.addText("This is another text after the image.");
console.log(googleDocument.render())