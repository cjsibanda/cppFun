//Encapsulation in action
//Clean main()
//Full mini-project complete

#include <iostream>
#include <cmath>
using namespace std;

class SensorData {
private:
    int* readings;
    int size;

public:
    SensorData(const int data[], int count) {
        size = count;
        readings = new int[size];
        for (int i = 0; i < size; i++) readings[i] = data[i];
    }

    ~SensorData() {
        delete[] readings;
    }

    double average() const {
        int sum = 0;
        for (int i = 0; i < size; i++) sum += readings[i];
        return (double)sum / size;
    }

    int maxDrop() const {
        int maxDrop = 0;
        for (int i = 1; i < size; i++) {
            int drop = readings[i - 1] - readings[i];
            if (drop > maxDrop) maxDrop = drop;
        }
        return maxDrop;
    }

    int countSpikes(int threshold = 100) const {
        int spikes = 0;
        for (int i = 1; i < size - 1; i++) {
            if (abs(readings[i] - readings[i - 1]) > threshold &&
                abs(readings[i] - readings[i + 1]) > threshold) {
                spikes++;
            }
        }
        return spikes;
    }

    int countInRange(int low, int high) const {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (readings[i] >= low && readings[i] <= high) count++;
        }
        return count;
    }

    void printReport() const {
        cout << "--- Sensor Analysis Report ---\n";
        cout << "Number of Readings: " << size << endl;
        cout << "Average Temperature: " << average() << " C\n";
        cout << "Spikes Detected: " << countSpikes() << endl;
        cout << "Maximum Drop Between Readings: " << maxDrop() << " C\n";

        int inRange = countInRange(90, 110);
        double percent = (double)inRange / size * 100;

        cout << "Readings in Optimal Range (90-110C): "
             << inRange << " (" << percent << "%)\n";
        cout << "--------------------------------\n";
    }
};

int main() {
    int data[] = {88, 78, 62, 93, 130, 134, 97, 102, 89, 108};
    SensorData sensor(data, 10);
    sensor.printReport();
    return 0;
}
