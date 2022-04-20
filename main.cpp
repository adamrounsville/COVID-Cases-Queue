#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

void writeFileToQueueCopy(queue<int>& covidCasesCopy);
void writeQueueCopyToQueue(queue<int>& covidCasesCopy, queue<int>& covidCases, int numDays);
void printQueue(queue<int> covidCases);
int computeQueueAverage(queue<int> covidCases, int numDays);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "./covid [.txt file] [number of days]" << endl;
        return 0;
    }

    queue<int> covidCases;
    queue<int> covidCasesCopy;
    string fileName = argv[1];
    int numDays = stoi(argv[2]);

    cout << "Using Data from " << fileName << " with a " << numDays << " day rolling average" << endl;

    writeFileToQueueCopy(covidCasesCopy);

    while (!covidCasesCopy.empty()) {
        writeQueueCopyToQueue(covidCasesCopy, covidCases, numDays);
        printQueue(covidCases);
        cout << "Average " << computeQueueAverage(covidCases, numDays) << endl;
        covidCases.pop();
    }

    return 0;
}

void writeFileToQueueCopy(queue<int>& covidCasesCopy) {
    fstream infile("cases.txt");

    int num;

    while (infile >> num) {
        covidCasesCopy.push(num);
    }

    infile.close();
}

void writeQueueCopyToQueue(queue<int>& covidCasesCopy, queue<int>& covidCases, int numDays) {
    while (covidCases.size() < numDays) {
        int num = covidCasesCopy.front();
        covidCases.push(num);
        covidCasesCopy.pop();
    }
}

void printQueue(queue<int> covidCases) {
    while (!covidCases.empty()) {
        cout << covidCases.front() << ",";
        covidCases.pop();
    }

    cout << endl;
}

int computeQueueAverage(queue<int> covidCases, int numDays) {
    int totalCovidCases = 0;
    int averageCovidCases;

    while (!covidCases.empty()) {
        totalCovidCases += covidCases.front();
        covidCases.pop();
    }

    averageCovidCases = (totalCovidCases / numDays);

    return averageCovidCases;
}
