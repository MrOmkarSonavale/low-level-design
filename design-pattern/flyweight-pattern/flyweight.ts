class AsteriodFlyweight {
    private length: number;
    private width: number;
    private weight: number;
    private color: string;
    private texture: string;
    private material: string;

    constructor(l: number, w: number, wt: number, c: string, t: string, m: string) {
        this.length = l;
        this.width = w;
        this.weight = wt;
        this.color = c;
        this.texture = t;
        this.material = m;
    };

    render(posX: number, posY: number, velocityX: number, velocityY: number): void {
        console.log(
            `Rendering Asteriod at (${posX}, ${posY}) with velocity (${velocityX}, ${velocityY}) 
            Properties -> Length: ${this.length}, Width: ${this.width}, Weight: ${this.weight}, 
            Color: ${this.color}, Texture: ${this.texture}, Material: ${this.material}`
        );
    }


    static getMemoryUsage() {
        return 4 * 3 + 50 * 3;
    }
};

class AsteriodFactory {
    private static asteriods: Map<string, AsteriodFlyweight> = new Map();

    static getAsteriod(
        length: number,
        width: number,
        weight: number,
        color: string,
        texture: string,
        material: string
    ): AsteriodFlyweight {
        const key = `${length}-${width}-${weight}-${color}-${texture}-${material}`;

        if (!this.asteriods.has(key)) {
            this.asteriods.set(key, new AsteriodFlyweight(length, width, weight, color, texture, material));
        };

        return this.asteriods.get(key)!;
    };

    static getFlyweightCount(): number {
        return this.asteriods.size;
    };

    static getTotalMemoryUsage(): number {
        return this.asteriods.size * AsteriodFlyweight.getMemoryUsage();
    };



    static cleanup(): void {
        this.asteriods.clear();
    }
};

class AsteriodContext {
    private posX: number;
    private posY: number;
    private velocityX: number;
    private velocityY: number;
    private flyweight: AsteriodFlyweight;


    constructor(x: number, y: number, vx: number, vy: number, fw: AsteriodFlyweight) {
        this.posX = x;
        this.posY = y;
        this.velocityX = vx;
        this.velocityY = vy;
        this.flyweight = fw;
    };

    render(): void {
        this.flyweight.render(this.posX, this.posY, this.velocityX, this.velocityY)
    };

    static getMemoryUsage(): number {
        return 4 * 4 + 8; // approx
    }
};

class spaceGameWithFlyweight {
    private static asteriods: AsteriodContext[] = [];

    spawnAsteriods(count: number): void {
        const color = ["Red", "Blue", "Gray"];
        const texture = ["Rocky", "Metallic", "Icy"];
        const material = ["Iron", "Silicon", "Carbon"];
        const size = [10, 20, 30];

        for (let i = 0; i < count; i++) {
            const type = i % 3;

            const flyweight = AsteriodFactory.getAsteriod(
                size[type],
                size[type],
                size[type] * 10,
                color[type],
                texture[type],
                material[type]
            );

            spaceGameWithFlyweight.asteriods.push(
                new AsteriodContext(
                    Math.floor(Math.random() * 100),
                    Math.floor(Math.random() * 100),
                    1,
                    2,
                    flyweight
                )
            );
        }
    }

    renderAll(): void {
        for (let i = 0; i < Math.min(5, spaceGameWithFlyweight.asteriods.length); i++) {
            spaceGameWithFlyweight.asteriods[i].render();
        }
    };

    static calculateMemoryUsage(): number {
        const contextMemory =
            spaceGameWithFlyweight.asteriods.length *
            AsteriodContext.getMemoryUsage();

        const flyweightMemory = AsteriodFactory.getTotalMemoryUsage();

        return contextMemory + flyweightMemory;
    }

    getAsteriodCount(): number {
        return spaceGameWithFlyweight.asteriods.length;
    }
}

const ASTEROID_COUNT = 10000;

console.log("Testing with Flyweight");

const game = new spaceGameWithFlyweight();

game.spawnAsteriods(ASTEROID_COUNT);
game.renderAll();

const totalMemoryUsage = spaceGameWithFlyweight.calculateMemoryUsage();

console.log("\n=== Memory Usage ===");
console.log("Total Asteroids:", ASTEROID_COUNT);
console.log("Memory per Asteroid:", AsteriodFlyweight.getMemoryUsage(), "bytes");
console.log("Total Memory Usage:", totalMemoryUsage, "bytes");
console.log("Total Memory Usage:", totalMemoryUsage / 1024, "KB");

AsteriodFactory.cleanup();