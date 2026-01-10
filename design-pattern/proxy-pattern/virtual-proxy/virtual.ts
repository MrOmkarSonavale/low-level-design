abstract class Idisplay {
    abstract display(): void;
};

class RealImage extends Idisplay {
    private filename: string;

    constructor(path: string) {
        super();
        this.filename = path;
    };

    display(): void {
        console.log("image is displaying");
    };
};

class ProxyImage extends Idisplay {
    private realImage: RealImage | null;
    private path: string;

    constructor(path: string) {
        super();
        this.path = path;
        this.realImage = null
    }

    display(): void {
        if (this.realImage == null) {
            console.log("first time iamge is load to display");
            this.realImage = new RealImage(this.path);
        }

        this.realImage.display();
    }
};


const newImage = new ProxyImage('c:/photo/img1');
newImage.display();
newImage.display();
