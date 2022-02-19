// HolyRotation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Paladin.h"
#include "TargetDummy.h"
#include "CGenAlg.h"
#include "CNeuralNet.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    
    CNeuralNet* neuralNetwork = new CNeuralNet(21, 11, 1, 10);
    CGenAlg* geneticAlgorithm = new CGenAlg(50, .05, .7, neuralNetwork->GetNumberOfWeights(), neuralNetwork->CalculateSplitPoints());
    TargetDummy* dummy = new TargetDummy();
    Paladin* paladin = new Paladin(dummy);

    // go for 2500 generations
    for (int i = 0; i < 2500; i++)
    {
        cout << "generation: " << i << endl;
        // switch weights for each generation
        for (int j = 0; j < 50; j++)
        {
            paladin->reset();
            dummy->reset();
            neuralNetwork->PutWeights(geneticAlgorithm->GetChromos()[j].vecWeights);

            for (int k = 0; k < 300; k++)
            {
                paladin->cycle();
                
                paladin->outputs = neuralNetwork->Update(paladin->getInputs());

                paladin->handleOutputs();
            }

            geneticAlgorithm->GetChromos()[j].dFitness = dummy->totalDamageDone / 30;
        }
        

        geneticAlgorithm->Epoch(geneticAlgorithm->GetChromos());

        cout << "Best performer: " << geneticAlgorithm->m_dBestFitness << endl;
        cout << "Average population performance: " << geneticAlgorithm->m_dAverageFitness << endl;
    }

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
