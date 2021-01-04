/* @JUDGE_ID: ******* 10191 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

//using namespace std;

struct timeZ {
    timeZ(){};
    timeZ(std::string timeS){
        this->hours = stoi(timeS.substr(0,2));
        this->minutes = stoi(timeS.substr(3,2));
    };
    timeZ (int hours, int minutes){
        this->hours = hours;
        this->minutes = minutes;
    };
    
    int getTotalMinutes(){
        return (hours*60)+minutes;
    };
    std::string getTime(){
        if (minutes < 10){
            return std::to_string(hours) + ":0" + std::to_string(minutes); 
        } else {
            return std::to_string(hours) + ":" + std::to_string(minutes);
        }
    };
    std::string getLength(){
        if (hours > 0){
            std::string tmp = (std::to_string(hours) + " hours and ");
            tmp += (std::to_string(minutes) + " minutes");
            return tmp;
        } else {
            return (std::to_string(minutes) + " minutes");
        }
    };

    int hours;
    int minutes;
};

struct appointment {
    appointment(){};
    appointment(timeZ start, timeZ end, std::string name){
        this->start = start;
        this->end = end;
        this->name = name;
    };
    timeZ start;
    timeZ end;
    std::string name;
};

//Times must be between 10:00 and 18:00
int main(int argc, char** argv){
    std::vector<timeZ> answerStart;
    std::vector<timeZ> answerLength;

    std::string input;
    while (!std::getline(std::cin, input).eof()){
        if (!std::cin || input.size() == 0)
            break;
        int numAppointments = std::stoi(input);
        if (numAppointments > 0){
            std::vector<appointment> apps; 
            for (int x = 0; x < numAppointments; x++){
                std::string tmpLine;
                std::getline(std::cin, tmpLine);
                if (!std::cin)
                    break;
                timeZ first = timeZ(tmpLine.substr(0,5));
                timeZ second = timeZ(tmpLine.substr(6,5));
                std::string name = "";
                if (tmpLine.size() > 11)
                    name = tmpLine.substr(12);
                appointment tmpAppointment(first,second,name);
                apps.push_back(tmpAppointment);
            }

            //cout << "apps size = " << apps.size() << endl;
            //for (int x = 0; x < numAppointments; x++){
            //    cout << "app #" << x << " start = " << apps[x].start.getTime() << " end = " << apps[x].end.getTime() << " name = " << apps[x].name << endl;
            //}

            //Sort the appointments by start time
            for (int x = 0; x < numAppointments-1; x++){
                for (int y = x+1; y < numAppointments; y++){
                    if (apps[x].start.getTotalMinutes() > apps[y].start.getTotalMinutes()){
                        std::swap(apps[x], apps[y]);
                    }
                }
            }

            //Remove encapsulated times
            for (int x = 0; x < numAppointments; x++){
                for (int y = 0; y < numAppointments; y++){
                    if (x != y){
                        if (apps[y].start.getTotalMinutes() <= apps[x].start.getTotalMinutes() &&
                        apps[y].end.getTotalMinutes() >= apps[x].start.getTotalMinutes() &&
                        apps[y].start.getTotalMinutes() <= apps[x].end.getTotalMinutes() &&
                        apps[y].end.getTotalMinutes() >= apps[x].end.getTotalMinutes()){
                            apps.erase(apps.begin()+x);
                            x -= 1;
                            numAppointments -= 1;
                            break;
                        }
                    }
                }
            }

            int maxTime = 0;
            timeZ startTime;
            //Find the biggest gap in time
            for (int x = 0; x < numAppointments; x++){
                if (x == 0){    //the first schedule might be able to sleep from 10:00 till then
                    int diff = apps[x].start.getTotalMinutes() - 600;
                    //cout << "diff = " << diff << endl;
                    if (diff > maxTime){
                        //check if intersects with any other appointments
                        maxTime = diff;
                        startTime = timeZ(10, 0);
                    }
                }
                //Normal checking ends relative to the next schedule
                if (x < numAppointments-1){
                    int diff = apps[x+1].start.getTotalMinutes() - apps[x].end.getTotalMinutes();
                    //cout << "diff = " << diff << endl;
                    if (diff > maxTime){
                        bool overlap = false;
                        for (int y = 0; y < numAppointments; y++){
                            if (y != x){
                                if (apps[y].start.getTotalMinutes() < apps[x].end.getTotalMinutes() && apps[y].end.getTotalMinutes() > apps[x].end.getTotalMinutes()){
                                    overlap = true;
                                    break;
                                }
                            }
                        }
                        if (!overlap){
                            maxTime = diff;
                            startTime = apps[x].end;
                        }
                    }
                } else {
                    int diff = 1080 - apps[x].end.getTotalMinutes();
                    //cout << "diff = " << diff << endl;
                    if (diff > maxTime){
                        maxTime = diff;
                        startTime = apps[x].end;
                    }
                }
            }

            int maxTimeHours;
            if (maxTime >= 60)
                maxTimeHours = maxTime / 60;
            else
                maxTimeHours = 0;
            int maxTimeMins = maxTime % 60;

            //Store the answer
            answerLength.push_back(timeZ(maxTimeHours, maxTimeMins));
            answerStart.push_back(startTime);
        } else {
            answerLength.push_back(timeZ(8, 0));
            answerStart.push_back(timeZ(10, 0));
        }
    }

    //Print the answers
    int aSize = answerStart.size();
    for (int x = 0; x < aSize; x++){
        std::cout << "Day #" << std::to_string(x+1) << ": the longest nap starts at " << answerStart[x].getTime() << " and will last for " << answerLength[x].getLength() << ".\n";
    }

    return 0;
}


/* @END_OF_SOURCE_CODE */