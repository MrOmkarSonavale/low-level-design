class PowerSupply {
    on(): void {
        console.log("Power Supply is ON");
    }
};


class Memory {
    checkMemory(): void {
        console.log("Memory is available");
    }
};

class CPU {
    cpuFan(): void {
        console.log("CPU fan is running");
    }
};

class HardDisk {
    loadOS(): void {
        console.log("Loading Operating System from Hard Disk");
    }
};

class BIOS {
    initailze(cpu: CPU, memory: Memory): void {
        cpu.cpuFan();
        memory.checkMemory();
    }
};

class Facade {
    private cpu: CPU;
    private memory: Memory;
    private os: HardDisk;
    private bios: BIOS;
    private ps: PowerSupply;

    constructor() {
        this.ps = new PowerSupply();
        this.cpu = new CPU();
        this.memory = new Memory();
        this.os = new HardDisk();
        this.bios = new BIOS();
    };

    startComputer(): void {
        this.ps.on();
        this.bios.initailze(this.cpu, this.memory);
        this.os.loadOS();
    }
};

const facade = new Facade();
facade.startComputer();