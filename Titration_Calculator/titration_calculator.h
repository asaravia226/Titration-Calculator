#include<vector> 
#include<string> 
#include<iostream>
#include <math.h> 
#include <sstream>
#include <fstream>
#ifndef TITRATION_CALCULATOR_H
#define TITRATION_CALCULATOR_H

class Calculator
{
// Each buffer will have its designated pKa and target pH.
// This is an early prototype. Only buffers with HEPES will work, for now. 

    public:
        struct buffer {
            std::string name;
            std::string reagent;
            // Buffer Final Volume
            float volume;    
            float pH;    
            float pKa;  
        }; 
        std::vector<buffer> buffers;
        std::ifstream fileStream; 

// Helpful Functions
        // reads a list of buffers stored in a text file
        void push_file(); 

        //Requests and parses user input. 
        void prompt(); 

        // Sorts the data structure
        std::vector<buffer> setBuffer(std::vector<buffer> v,std::string a, std::string b, float c, float d); 
        
        // Helper function returning a buffer's index. 
        unsigned int getBuffer(std::string name);

        // Helps validate user input
        bool validate(std::string name, std::string vol); 

        // The titrant volume calculation as derived from the Henderson Hasselbalch Equation
        float formula(std::string name, float volume); 
        
        // Prints the list of all successfully uploaded buffers. 
        void print(); 
}; 

void Calculator::push_file() {
    fileStream.open("buffer_names_revised.txt", std::ifstream::in); 
    std::string line; 
    std::string s; 
    std::string r;
    std::string temp_y;
    std::string temp_z; 
    float y = 0; 
    float z = 0; 

    while (std::getline(fileStream, line)) {
        std::stringstream ss(line); 
        std::getline(ss, s, ',');
        std::getline(ss, r, ','); 
        std::getline(ss, temp_y, ',');
        std::getline(ss, temp_z, '\n');

        try {
            std::stof(temp_y);
            std::stof(temp_z); 
        }
        catch (std::exception& e) {
            y = 0;
            z = 0;  
            continue;
        }
        y = std::stof(temp_y); 
        z = std::stof(temp_z);
        buffers = setBuffer(buffers, s, r, y, z); 
        } 
    fileStream.close(); 
}

void Calculator::prompt()
{
    bool flag = true;
    float vol = 0;  

    // User Input
    std::string input;
    std::string buffer;
    std::string temp_vol;

    while (flag == true) {
        std::cout << "Enter Buffer Name and a Final Volume separated by a column: " << "\n"; 
        std::cout << "End program, Enter[0] " << "\n";
        std::cout << "Continue, Enter[1] " << "\n";
        std::cout << "--------------------------------------------------------------" << "\n";  
        
        std::getline(std::cin, input, '\n');
        std::istringstream sst(input);
        sst >> std::ws; 
        std::getline(sst, buffer, ',');
        sst >> std::ws; 
        std::getline(sst, temp_vol, '\n'); 


        if (input == "0") {
            std::cout << "Goodbye" << "\n";
            flag = false;
        }
        // else if ( buffer.empty()) 
        //     std::cout << "Wrong input, Try Again!" << "\n"; 
        
        else if(input == "1") 
            flag = true;   
        
        else if (input != "0" or input != "1") {
            if (validate(buffer, temp_vol) == false) {
                std::cout << "Wrong input, Try Again!" << "\n";
                std::cout << "Make sure to type buffer name as it appears and to only type in a number for volume. " << "\n\n"; 
            }
            else if (validate(buffer, temp_vol) == true) {
                    vol = std::stof(temp_vol);
                    formula(buffer, vol); 
            }   
        }
        else
            std::cout << "Wrong input, Try Again!"; 
    }
} 
 
// std::cout << "--------------------------------------------------------------" << "\n";  
std::vector<Calculator::buffer> Calculator::setBuffer(std::vector<buffer> v, std::string a, std::string b, float c, float d) {
    buffer myBuffer;
    myBuffer.name = a; 
    myBuffer.reagent = b;
    myBuffer.pH = c; 
    myBuffer.pKa = d; 
    v.push_back(myBuffer);
    return v;  
}

unsigned int Calculator::getBuffer(std::string name) {
    unsigned int index; 
    // unsigned int index = validate(name); 
    for (unsigned int i = 0; i < buffers.size(); i++) {
        if (buffers[i].name == name) 
            index = i;
    }   
    return index;   
}

bool Calculator::validate(std::string name, std::string vol) {
    int verified_vol; 

    for (unsigned int i = 0; i < buffers.size(); i++) {
        if (buffers[i].name == name) {
            try {
                std::stof(vol);
            }
            catch (std::exception& e) {
                verified_vol = 0; 
                continue;
            }
            return true; 
        } 
        else{continue;}
    }
    return false; 
}

void Calculator::print() {
    for (unsigned int i = 0; i < buffers.size(); i++) {
        std::cout << buffers[i].name << "\n";
    }
    std::cout << "--------------------------------------------------------------" << "\n";  
}

float Calculator::formula(std::string name, float volume) {
    // for now we will just assume the acid and conjugate base are HEPES- HEPES
    unsigned int index = getBuffer(name); 
    // Calculated volume of Base we will need to titrate with 
    float answer = 0; 
    
    // This is derived from the Henderson Hasselbalch Equation  
    float ratio = pow(10,(buffers[index].pH - buffers[index].pKa)); 
    std::cout << "RATIO: " << ratio << "\n"; 

    // [A-]/[HA] 
    // Let our weak acid == an unknown volume, giving us our ratio in this form: 
    // = L_A-/L_HA 
    // answer = ratio * (volume - answer) == 
    answer = (ratio * volume) / (1 + ratio); 
    std::cout << "Titrant Volume required to reach a pH of " << buffers[index].pH << " is: "<< answer << "mL of 10M " << buffers[index].reagent << "\n";
    return answer; 
}
 #endif
