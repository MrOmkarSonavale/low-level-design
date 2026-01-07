#include <iostream>
#include <string>

using namespace std;

class modelTrainer
{
public:
    void executeTrainingPipeline(string &data)
    {
        collectData(data);
        preprocessData();
        trainModel();
        evaluateModel();
        saveModel();
    }

protected:
    void collectData(string &data)
    {
        cout << "Collecting data for Model Training" << endl;
    };

    void preprocessData()
    {
        cout << "Preprocessing data for Model Training" << endl;
    };

    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;

    void saveModel()
    {
        cout << "Saving Model after Training" << endl;
    };
};

class LinearRegressionTrainer : public modelTrainer
{
public:
    void trainModel() override
    {
        cout << "Training Linear Regression Model with data: " << endl;
    };

    void evaluateModel() override
    {
        cout << "Evaluating Linear Regression Model" << endl;
    };
};

class NLPTrainer : public modelTrainer
{
public:
    void trainModel() override
    {
        cout << "Training NLP Model with data: " << endl;
    };

    void evaluateModel() override
    {
        cout << "Evaluating NLP Model" << endl;
    };
};

class SVMTrainer : public modelTrainer
{
public:
    void trainModel() override
    {
        cout << "Training SVM Model with data: " << endl;
    };

    void evaluateModel() override
    {
        cout << "Evaluating SVM Model" << endl;
    };
};

int main(void)
{
    string data = "Sample Training Data";

    modelTrainer *trainer = new NLPTrainer();
    trainer->executeTrainingPipeline(data);
    delete trainer;

    trainer = new SVMTrainer();
    trainer->executeTrainingPipeline(data);
    delete trainer;
};