#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
//#include <unistd.h>
#include <iomanip>
#include <vector> 
#include <thread>
#include <chrono>

/*This is a interactive code using C++ language coded on 04/24/2024 for the Intro to C and C++
course by Dr. Roman V. Yampolskiy by Bethanie Bairen
*/
using namespace std;
using namespace chrono;

int cellLength = 21;
int patientCount = 0;

//Tracking system for number of patients with each illness
double numCovid = 0;
double numCold = 0;
double numFlu = 0;
double numOther = 0;

//Template function for easy table printing
template<typename T> void printCell(T t, const int& width) {
    cout << left << setw(width) << setfill(' ') << t;
}

//Funciton to print symptom table
void printChart(){
    printCell("\nSymptoms", cellLength);
    printCell("COVID-19", cellLength);
    printCell("Cold", cellLength);
    printCell("Flu", cellLength);
    cout << endl;

    printCell("Fever", cellLength);
    printCell("*", cellLength);
    printCell("+", cellLength);
    printCell("*", cellLength);
    cout << endl;

    printCell("Cough", cellLength);
    printCell("*", cellLength);
    printCell("+", cellLength);
    printCell("*", cellLength);
    cout << endl;

    printCell("Shortness of Breath", cellLength);
    printCell("*", cellLength);
    printCell("-", cellLength);
    printCell("-", cellLength);
    cout << endl;

    printCell("Runny Nose", cellLength);
    printCell("+", cellLength);
    printCell("*", cellLength);
    printCell("+", cellLength);
    cout << endl;

    printCell("Headaches", cellLength);
    printCell("+", cellLength);
    printCell("+", cellLength);
    printCell("*", cellLength);
    cout << endl;

    printCell("Sneezing", cellLength);
    printCell("-", cellLength);
    printCell("*", cellLength);
    printCell("-", cellLength);
    cout << endl;

    printCell("Fatigue", cellLength);
    printCell("+", cellLength);
    printCell("+", cellLength);
    printCell("*", cellLength);
    cout << endl;

    printCell("\nGuide:", cellLength);
    printCell("*Common", cellLength);
    printCell("+Sometimes/Rarely", cellLength);
    printCell("-NO", cellLength);
    cout << endl;

    cout << "\n";
}

//Pre-declaration of class
class Disease;

//Patient class declaration
class Patient{
    public:
        Disease* disease;

        int symptoms[7] = {0,0,0,0,0,0,0};
        string patientNumber;
        int breathShortness = 0;
        int sneezing = 0;
        int diagnosis = 0;
        int covidScore;
        int coldScore;
        int fluScore;

        //Function to assign symptoms randomly to each patient
        void symptomGen() {
            int i = 0;

            for (i = 0; i < 7; i++){
                    symptoms[i] = (rand()%3);
            }        
        }

        //Function to print each patient's symptoms once assigned
        void printSymptoms(){
            
            cout << "\n" << patientNumber << " displays the following symptoms:\n";

            if (symptoms[0] == 2){
                cout << "Fever: Present\n";
            } else if (symptoms[0] == 1){
                cout << "Fever: Sometimes\n";
            } else {
                cout << "Fever: Absent\n";
            }
            
            if (symptoms[1] == 2){
                cout << "Cough: Present\n";
            } else if (symptoms[1] == 1){
                cout << "Cough: Sometimes\n";
            } else {
                cout << "Cough: Absent\n";
            }
            
            if (symptoms[2] == 2){
                cout << "Shortness of Breath: Present\n";
            } else if (symptoms[2] == 1){
                cout << "Shortness of Breath: Sometimes\n";
            } else {
                cout << "Shortness of Breath: Absent\n";
            }
            
            if (symptoms[3] == 2){
                cout << "Runny Nose: Present\n";
            } else if (symptoms[3] == 1){
                cout << "Runny Nose: Sometimes\n";
            } else {
                cout << "Runny Nose: Absent\n";
            }
            
            if (symptoms[4] == 2){
                cout << "Headaches: Present\n";
            } else if (symptoms[4] == 1){
                cout << "Headaches: Sometimes\n";
            } else {
                cout << "Headaches: Absent\n";
            }
            
            if (symptoms[5] == 2){
                cout << "Sneezing: Present\n";
            } else if (symptoms[5] == 1){
                cout << "Sneezing: Sometimes\n";
            } else {
                cout << "Sneezing: Absent\n";
            }
            
            if (symptoms[6] == 2){
                cout << "Fatigue: Present\n";
            } else if (symptoms[6] == 1){
                cout << "Fatigue: Sometimes\n";
            } else {
                cout << "Fatigue: Absent\n";
            }

            cout << "\n";
        
    }

        //Funciton to print individual diagnoses for each patient after analysis
        void printDiag(){
            
            cout << "\n";
            if(diagnosis == 1){
                cout << patientNumber << " shows all symptoms of COVID-19  and has been diagnosed with COVID-19.";
            } else if(diagnosis == 2){
                cout << patientNumber << " shows all symptoms of a Cold and has been diagnosed with a Cold.";
            } else if(diagnosis == 3){
                cout << patientNumber << " shows all symptoms of the Flu and has been diagnosed with the Flu.";
            } else if(diagnosis == 4){
                cout << patientNumber << " shows some symptoms of COVID-19, so they may have COVID-19.";
            } else if(diagnosis == 5){
                cout << patientNumber << " shows some symptoms of a Cold, so they may have a Cold.";
            } else if(diagnosis == 6){
                cout << patientNumber << " shows some symptoms of the Flu, so they may have the Flu.";
            } else {
                cout << patientNumber << " likely does not have COVID-19, a Cold, or the Flu. Further testing is recommended.";
            }
            this_thread::sleep_for(2000ms);
            
        }

        //Function to determine the diagnosis of each patient
        void diagFunc(){

                //Check key differences between illnesses: Shortness of Breath and Sneezing
                if (symptoms[2] == 2){
                    breathShortness = 2;
                } else if(symptoms[2] == 1) {
                    breathShortness = 1;
                } else {
                    breathShortness = 0;
                }

                if (symptoms[5] == 2){
                    sneezing = 2;
                } else if(symptoms[5] == 1){
                    sneezing = 1;
                } else {
                    sneezing = 0;
                }

                //Compare symptoms and values for each illness to assign diagnosis

                //Diagnosis 1 = Definite COVID-19; 2 = Definite Cold; 3 = Definite Flu;
                //4 = Maybe COVID-19; 5 = Maybe Cold;6 = Maybe Flu; 7 = Likely Other Illness
                if(breathShortness == 2 && sneezing < 2 && covidScore == 12){
                    diagnosis = 1;
                    numCovid++;
                } else if(sneezing == 2 && breathShortness < 2 && coldScore == 12){
                    diagnosis = 2;
                    numCold++;
                } else if(breathShortness == 0 && sneezing == 0 && fluScore == 10){
                    diagnosis = 3;
                    numFlu++;
                } else if(breathShortness > 0 && sneezing < 2 && covidScore >= 6){
                    diagnosis = 4;
                    numCovid++;
                } else if(sneezing > 0 && breathShortness < 2 && coldScore >= 6){
                    diagnosis = 5;
                    numCold++;
                } else if(breathShortness == 0 && sneezing == 0 && fluScore >= 5){
                    diagnosis = 6;
                    numFlu++;
                } else {
                    diagnosis = 7;
                    numOther++;
                }
            
        }

};
Patient patient;
vector <Patient> patients; //Vector of objects to store patients

//Defining base class we declared earlier
class Disease{
    public:

        //Virtual class to be overridden in derived classes
        virtual void diagnose(vector<Patient>& patients) = 0;
};

//Derived class for COVID-19 diagnosis
class Covid19 : public Disease {
    public:
        //Function to evaluate symptoms and assign values for COVID-19 to determine likelihood of infection
        void diagnose(vector<Patient>& patients) override{
            for(Patient& patient : patients){
                patient.covidScore = 0;
                if(patient.symptoms[0] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[0] == 1){
                    patient.covidScore += 1;
                }
                if(patient.symptoms[1] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[1] == 1){
                    patient.covidScore += 1;
                }
                if(patient.symptoms[2] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[2] == 1){
                    patient.covidScore += 1;
                }
                if(patient.symptoms[3] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[3] == 1){
                    patient.covidScore += 1;
                }
                if(patient.symptoms[4] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[4] == 1){
                    patient.covidScore += 1;
                }
                if(patient.symptoms[6] == 2){
                    patient.covidScore += 2;
                } else if (patient.symptoms[6] == 1){
                    patient.covidScore += 1;
                }
            }
        }
};

//Derived class for Cold diagnosis
class Cold : public Disease {
    public:
        //Function to evaluate symptoms and assign values for Cold to determine likelihood of infection
        void diagnose(vector<Patient>& patients) override{
            for(Patient& patient : patients){
                patient.coldScore = 0;
                if(patient.symptoms[0] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[0] == 1){
                    patient.coldScore += 1;
                }
                if(patient.symptoms[1] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[1] == 1){
                    patient.coldScore += 1;
                }
                if(patient.symptoms[3] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[3] == 1){
                    patient.coldScore += 1;
                }
                if(patient.symptoms[4] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[4] == 1){
                    patient.coldScore += 1;
                }
                if(patient.symptoms[5] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[5] == 1){
                    patient.coldScore += 1;
                }
                if(patient.symptoms[6] == 2){
                    patient.coldScore += 2;
                } else if (patient.symptoms[6] == 1){
                    patient.coldScore += 1;
                }
            }
        }
};

//Derived class for Flu diagnosis
class Flu : public Disease {
    public:
        //Function to evaluate symptoms and assign values for Flu to determine likelihood of infection
        void diagnose(vector<Patient>& patients) override{
            for(Patient& patient : patients){
                patient.fluScore = 0;
                if(patient.symptoms[0] == 2){
                    patient.fluScore += 2;
                } else if (patient.symptoms[0] == 1){
                    patient.fluScore += 1;
                }
                if(patient.symptoms[1] == 2){
                    patient.fluScore += 2;
                } else if (patient.symptoms[1] == 1){
                    patient.fluScore += 1;
                }
                if(patient.symptoms[3] == 2){
                    patient.fluScore += 2;
                } else if (patient.symptoms[3] == 1){
                    patient.fluScore += 1;
                }
                if(patient.symptoms[4] == 2){
                    patient.fluScore += 2;
                } else if (patient.symptoms[4] == 1){
                    patient.fluScore += 1;
                }
                if(patient.symptoms[6] == 2){
                    patient.fluScore += 2;
                } else if (patient.symptoms[6] == 1){
                    patient.fluScore += 1;
                }
            }
        }
};

//Class to handle patient organization and diagnosis functions
class Hospital{
    private:
        vector<Patient> patients;
        Covid19 covid;
        Cold cold;
        Flu flu;
    
    public:
        //Function to add patients to the vector of "patient" objects
        void addPatient(const Patient& patient) {
            patients.push_back(patient);
        }

        //Function to run diagnosis functions and print diagnoses
        void diagnosePatients() {
            cout << "Analyzing symptoms for diagnosis...\n";
            this_thread::sleep_for(2000ms);
            for (Patient& patient : patients){
                covid.diagnose(patients);
                cold.diagnose(patients);
                flu.diagnose(patients);
                patient.diagFunc();
                patient.printDiag();
            }
        }
};

//Function to print final results after diagnoses and calculations
void printResults(){
    
    double covidPerc = numCovid*100/patientCount;
    double coldPerc = numCold*100/patientCount;
    double fluPerc = numFlu*100/patientCount;
    double otherPerc = numOther*100/patientCount;

    cout << "\n\nFinal Results:";
    cout << "\nCOVID-19 Patients: " << numCovid << " - " << fixed << setprecision(2) << covidPerc << "%";
    cout << "\nCold Patients: " << numCold << " - " << fixed << setprecision(2) << coldPerc << "%";
    cout << "\nFlu Patients: " << numFlu << " - " << fixed << setprecision(2) << fluPerc << "%";
    cout << "\nPatients with Other Illnesses: " << numOther << " - " << fixed << setprecision(2) << otherPerc << "%\n";
}

//Main function
int main(){
    srand(time(NULL));
    Hospital hospital;

    printChart();
    //Ask user for number of patients
    cout << "How many patients would you like to check?\n";
    cin >> patientCount;
    
    //Creation and configuration of patients, adding details to Patient and Hospital classes
    for (int i = 0; i < patientCount; i++){
        Patient patient;
        patient.patientNumber = "Patient number " + to_string(i+1);
        patient.symptomGen();
        hospital.addPatient(patient);
        patient.printSymptoms();
    }
    
    //Run diagnosis functions
    hospital.diagnosePatients();

    //Print final report
    printResults();

    return 0;
}