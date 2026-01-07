
abstract class modelTrainer {

    templateMethod(dataPath: string, modelPath: string): void {
        this.loadData(dataPath);
        this.preprocessData();
        this.trainModel();
        this.evaluateModel();
        this.saveModel(modelPath);
    }

    protected loadData(dataPath: string): void {
        console.log("Loading data...");
    }

    protected preprocessData(): void {
        console.log("Preprocessing data...");
    }

    protected abstract trainModel(): void;
    protected abstract evaluateModel(): void;

    protected saveModel(modelPath: string): void {
        console.log("Saving model...");
    }
}

class decisionTreeTrainer extends modelTrainer {
    trainModel(): void {
        console.log("Training Decision Tree model...");
    }

    evaluateModel(): void {
        console.log("Evaluating Decision Tree model...");
    }
};

class neuralNetworkTrainer extends modelTrainer {
    trainModel(): void {
        console.log("Training Neural Network model...");
    };

    evaluateModel(): void {
        console.log("Evaluating Neural Network model...");
    }
};

const algo = new decisionTreeTrainer();
algo.templateMethod("data/train.csv", "models/decision_tree.model");