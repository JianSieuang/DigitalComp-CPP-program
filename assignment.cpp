#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

double LAPTOP_WATT, SMARTPHONE_WATT, GAMING_WATT, TABLET_WATT, DESKTOP_WATT, CO2_FACTOR;

class device
{
private:
    string name;
    double powerConsumption;
    double dailyUsage;
    // energy consumption in kWh using the formula: (Power in Watts * Hours) / 1000
    double energyConsumption;

    double co2Factor;
    // co₂ emission in kg using the formula: Energy Consumption * CO₂ factor
    double co2Emission;

public:
    // constructor: initializes name, power consumption, and CO₂ factor
    device(string name, double powerConsumption, double co2Factor)
        : name(name), powerConsumption(powerConsumption), co2Factor(co2Factor)
    {
        dailyUsage = 0;
        energyConsumption = 0;
        co2Emission = 0;
    }

    // sets daily usage (in hours) and calculates energy consumption and CO₂ emission
    void setDailyUsage(double hours)
    {
        dailyUsage = hours;
        energyConsumption = (powerConsumption * dailyUsage) / 1000;
        co2Emission = energyConsumption * co2Factor;
    }

    // getter methods.
    double getEnergyConsumption() const { return energyConsumption; }
    double getCO2Emission() const { return co2Emission; }
    string getName() const { return name; }
};

void configuration()
{
    // predefined power consumption values (in Watts) for each device type
    LAPTOP_WATT = 50.0;
    SMARTPHONE_WATT = 5.0;
    GAMING_WATT = 150.0;
    TABLET_WATT = 10.0;
    DESKTOP_WATT = 200.0;

    // in Malaysia, the value is about 0.758 kg CO₂/kWh based on the Energy Commission's 2021 Grid Emission Factor (GEF) for Peninsular Malaysia
    CO2_FACTOR = 0.758;
}

void header()
{
    cout << "=======================================================================\n";
    cout << "                     Energy Consumption Tracker\n";
    cout << "=======================================================================\n\n";
    cout << "This tracker calculates your daily energy consumption and carbon footprint\n";
    cout << "for common devices such as laptops, smartphones, gaming consoles, tablets, and desktops.\n\n";
}

void getDevices(vector<device> &devices)
{
    int numDevices;
    cout << "Enter the number of devices you want to track: ";
    cin >> numDevices;
    cin.ignore();

    // loop for each device
    for (int i = 0; i < numDevices; i++)
    {
        int deviceChoice;
        double hours;
        string deviceName;
        double power;

        cout << "\n--- Device " << i + 1 << " ---\n";

        // valid check for device type
        bool validChoice = false;
        while (!validChoice)
        {
            cout << "Select device type:\n";
            cout << "  1. Laptop\n";
            cout << "  2. Smartphone\n";
            cout << "  3. Gaming Console\n";
            cout << "  4. Tablet\n";
            cout << "  5. Desktop\n";
            cout << "Enter your choice (1-5): ";
            cin >> deviceChoice;
            cin.ignore();

            if (deviceChoice >= 1 && deviceChoice <= 5)
            {
                validChoice = true;
            }
            else
            {
                cout << "Invalid choice! Please try again.\n";
            }
        }

        cout << "Enter the device name: ";
        getline(cin, deviceName);


        switch (deviceChoice)
        {
        case 1:
            power = LAPTOP_WATT;
            break;
        case 2:
            power = SMARTPHONE_WATT;
            break;
        case 3:
            power = GAMING_WATT;
            break;
        case 4:
            power = TABLET_WATT;
            break;
        case 5:
            power = DESKTOP_WATT;
            break;
        }

        // valid check for daily usage
        bool validHours = false;
        while (!validHours)
        {
            cout << "Enter daily usage (in hours): ";
            cin >> hours;

            if (hours >= 1 && hours <= 24)
            {
                validHours = true;
            }
            else
            {
                cout << "Invalid input! Please try again.\n";
            }
        }

        // create the device and set its usage
        device d(deviceName, power, CO2_FACTOR);
        d.setDailyUsage(hours);
        devices.push_back(d);
    }
}

void display(vector<device> &devices)
{
    // calculate total energy and CO₂ emissions
    double totalEnergy = 0.0;
    double totalCO2 = 0.0;

    cout << "\n=======================================================================\n";
    cout << "             Daily Energy Consumption & Carbon Footprint\n";
    cout << "=======================================================================\n\n";
    cout << fixed << setprecision(3);

    // display results for each device
    for (size_t i = 0; i < devices.size(); i++)
    {
        cout << "Device " << i + 1 << " (" << devices[i].getName() << ")\n";
        cout << "  Energy Consumption:     \t\t" << devices[i].getEnergyConsumption() << " kWh/day\n";
        cout << "  CO₂ Emissions:          \t\t" << devices[i].getCO2Emission() << " kg CO₂/day\n\n";
        totalEnergy += devices[i].getEnergyConsumption();
        totalCO2 += devices[i].getCO2Emission();
    }

    cout << "-----------------------------------------------------------------------\n";
    cout << "Total Energy Consumption: \t\t" << totalEnergy << " kWh/day\n";
    cout << "Total CO₂ Emissions:      \t\t" << totalCO2 << " kg CO₂/day\n";

    // simulate potential energy savings
    if (!devices.empty())
    {
        double savingRate = 0.10;
        double energySaved = totalEnergy * savingRate;
        double co2Reduction = energySaved * CO2_FACTOR;

        cout << "-----------------------------------------------------------------------\n\n";
        cout << "Energy-Saving Simulation\n";
        cout << "If you enable power-saving mode (assumed 10% saving), you might save:\n";
        cout << "  Energy Saved: " << energySaved << " kWh/day\n";
        cout << "  CO₂ Reduction: " << co2Reduction << " kg CO₂/day\n";
    }
}

void energySavingTips()
{
    cout << "\nGeneral Energy-Saving Tips:\n";
    cout << "1. Use power-saving mode on your devices.\n";
    cout << "2. Reduce screen brightness when possible.\n";
    cout << "3. Turn off devices when not in use.\n";
    cout << "4. Unplug chargers once devices are fully charged.\n";
}

void footer()
{
    cout << "\n=======================================================================\n";
    cout << "       Thank you for using the Energy Consumption Tracker!\n";
    cout << "=======================================================================\n";
}

int main()
{
    vector<device> devices;
    // program configuration
    configuration();
    // program header
    header();

    // get the devices and their usage
    getDevices(devices);

    // display the results.
    display(devices);

    // display general energy-saving tips
    energySavingTips();

    // program footer
    footer();

    return 0;
}
