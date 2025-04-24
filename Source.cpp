#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "Header.h"
using namespace std;

enum class AnomalyType : int
{
    Wormhole = 1,
    DarkNebula = 2,
    EnergyPulse = 3,

    Undefined = 0
};

class SpaceAnomaly
{
public:
    string name;
    double distance;

    SpaceAnomaly(string name, double distance) : name(name), distance(distance) {};

    virtual ~SpaceAnomaly() {};

    virtual void Analyze() const {
        cout << "Anomaly info:\nName - " << name << "\nDistance - " << distance;
    }

    virtual int PredictDanger() const {
        return (10000000 - distance) * 0.000001;
    }

    virtual int SimulateInteraction() const {
        return (100 + distance) * 0.01;
    }

    virtual AnomalyType GetType() const {
        return AnomalyType::Undefined;
    }
};

class Wormhole : public SpaceAnomaly
{
public:
    int stability;

    Wormhole(string name, double distance, int stability) : SpaceAnomaly(name, distance), stability(stability) {};
    ~Wormhole() {};

    void Analyze() const override {
        SpaceAnomaly::Analyze();
        cout << "\nStability - " << stability << endl;

    }

    int PredictDanger() const override {
        int danger = SpaceAnomaly::PredictDanger() * stability;
        return danger;
    }

    int SimulateInteraction() const override {
        int interaction = SpaceAnomaly::SimulateInteraction() * stability;
        return interaction;
    }

    AnomalyType GetType() const override {
        return AnomalyType::Wormhole;
    }
};

class DarkNebula : public SpaceAnomaly
{
public:
    int opacity;

    DarkNebula(string name, double distance, int opacity) : SpaceAnomaly(name, distance), opacity(opacity) {};
    ~DarkNebula() {};

    void Analyze() const override {
        SpaceAnomaly::Analyze();
        cout << "\nOpacity - " << opacity << endl;
    }

    int PredictDanger() const override {
        int danger = SpaceAnomaly::PredictDanger() * opacity;
        return danger;
    }

    int SimulateInteraction() const override {
        int interaction = SpaceAnomaly::SimulateInteraction() * opacity;
        return interaction;
    }

    AnomalyType GetType() const override {
        return AnomalyType::DarkNebula;
    }
};

class EnergyPulse : public SpaceAnomaly
{
public:
    int intensity;

    EnergyPulse(string name, double distance, int intensity) : SpaceAnomaly(name, distance), intensity(intensity) {};
    ~EnergyPulse() {};

    void Analyze() const override {
        SpaceAnomaly::Analyze();
        cout << "\nIntensity - " << intensity << endl;
    }

    int PredictDanger() const override {
        int danger = SpaceAnomaly::PredictDanger() * intensity;
        return danger;
    }

    int SimulateInteraction() const override {
        int interaction = SpaceAnomaly::SimulateInteraction() * intensity;
        return interaction;
    }

    AnomalyType GetType() const override {
        return AnomalyType::EnergyPulse;
    }

};

SpaceAnomaly* CreateAnomaly(AnomalyType type)
{
    SpaceAnomaly* newAnomaly = nullptr;

    if (type == AnomalyType::Wormhole) { newAnomaly = new Wormhole("WormWorm", rand() % (10001), rand() % 11); }
    else if (type == AnomalyType::DarkNebula) { newAnomaly = new DarkNebula("Nebula_1231", rand() % (10001), rand() % 11); }
    else if (type == AnomalyType::EnergyPulse) { newAnomaly = new EnergyPulse("Death", rand() % (10001), rand() % 11); }

    return newAnomaly;
}

class AnomalyTypeFilterDecorator : public IteratorDecorator<class SpaceAnomaly*>
{
private:
    AnomalyType TargetType;
public:
    AnomalyTypeFilterDecorator(Iterator<SpaceAnomaly*>* it, AnomalyType type) : IteratorDecorator<SpaceAnomaly*>(it), TargetType(type) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetType() != TargetType) { It->Next(); }
    }

    void Next()
    {
        do { It->Next(); } while (!It->IsDone() && It->GetCurrent()->GetType() != TargetType);
    }
};

class MostDangerDecorator : public IteratorDecorator<class SpaceAnomaly*>
{
private:
    SpaceAnomaly* MostDanger{};
public:
    MostDangerDecorator(Iterator<SpaceAnomaly*>* it) : IteratorDecorator<SpaceAnomaly*>(it) {}

    void First()
    {
        It->First();
        MostDanger = It->GetCurrent();
        while (!It->IsDone()) {
            if (It->GetCurrent()->PredictDanger() > MostDanger->PredictDanger()) { MostDanger = It->GetCurrent(); }
            It->Next();
        }
    }

    SpaceAnomaly* GetCurrent() const override {
        return MostDanger;
    }
};

class AnomalyIntecartionDecorator : public IteratorDecorator<class SpaceAnomaly*>
{
private:
    SpaceAnomaly* CurrentAnomaly{};
public:
    AnomalyIntecartionDecorator(Iterator<SpaceAnomaly*>* it) : IteratorDecorator<SpaceAnomaly*>(it) {}
    void First()
    {
        It->First();
        while (!It->IsDone())
        {
            CurrentAnomaly = It->GetCurrent();
            cout << CurrentAnomaly->SimulateInteraction() << endl;
            It->Next();
        }
    }
};

void AnalyzeAll(Iterator<SpaceAnomaly*>* it)
{
    for (it->First(); !it->IsDone(); it->Next())
    {
        SpaceAnomaly* currentAnomaly = it->GetCurrent();
        currentAnomaly->Analyze();
        cout << "---------------------" << endl;
    }
}

int main()
{
    srand(time(0));
    size_t Num = 5;
    StackClass<SpaceAnomaly*> anomalyStack;
    for (size_t i = 0; i < Num; i++)
    {
        int anomaly_num = rand() % 3 + 1;
        AnomalyType anomaly_type = static_cast<AnomalyType>(anomaly_num);
        SpaceAnomaly* newAnomaly = CreateAnomaly(anomaly_type);
        anomalyStack.Push(newAnomaly);
    }
    cout << "Stack class: " << endl << endl;
    Iterator<SpaceAnomaly*>* allStackIt = anomalyStack.GetIterator();
    AnalyzeAll(allStackIt);
    delete allStackIt;

    ArrayClass<SpaceAnomaly*> anomalyArray;
    for (size_t i = 0; i < Num; i++)
    {
        int anomaly_num = rand() % 3 + 1;
        AnomalyType anomaly_type = static_cast<AnomalyType>(anomaly_num);
        SpaceAnomaly* newAnomaly = CreateAnomaly(anomaly_type);
        anomalyArray.Add(newAnomaly);
    }
    cout << "Array class: " << endl << endl;
    Iterator<SpaceAnomaly*>* allArrIt = anomalyArray.GetIterator();
    AnalyzeAll(allArrIt);
    delete allArrIt;

    Iterator<SpaceAnomaly*>* TypeAnomalyFitler = new AnomalyTypeFilterDecorator(anomalyStack.GetIterator(), AnomalyType::Wormhole);
    cout << "Only wormholes: " << endl << endl;
    AnalyzeAll(TypeAnomalyFitler);
    delete TypeAnomalyFitler;

    Iterator<SpaceAnomaly*>* MostDangerIt = new MostDangerDecorator(anomalyArray.GetIterator());
    MostDangerIt->First();
    SpaceAnomaly* MostDangerAnomaly = MostDangerIt->GetCurrent();
    cout << "Most danger anomaly with danger " << MostDangerAnomaly->PredictDanger() << " is: " << endl << endl;
    MostDangerAnomaly->Analyze();
    delete MostDangerIt;

    Iterator<SpaceAnomaly*>* AnomalyInteraction = new AnomalyIntecartionDecorator(anomalyStack.GetIterator());
    cout << "Interactions: " << endl << endl;
    AnomalyInteraction->First();
    delete AnomalyInteraction;

    vector<SpaceAnomaly*> anomalyVector;

    for (size_t i = 0; i < Num; i++)
    {
        int object_num = rand() % 3 + 1;
        AnomalyType object_type = static_cast<AnomalyType>(object_num);
        SpaceAnomaly* newObject = CreateAnomaly(object_type);
        anomalyVector.push_back(newObject);
    }
    Iterator<SpaceAnomaly*>* afterAdaptIt = new ConstIteratorAdapter<vector<SpaceAnomaly*>, SpaceAnomaly*>(&anomalyVector);
    cout << "After adaptation: " << endl << endl;
    AnalyzeAll(afterAdaptIt);
    delete afterAdaptIt;
    return 0;
}