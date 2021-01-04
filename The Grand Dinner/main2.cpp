/* @JUDGE_ID: ******* 10249 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Goal:
        Find a way to arrange teams into tables such that no two members of the same team are sitting together

    Notes:
        Solution doesn't exist if a teamSize > numTables
*/

struct team {
    team(int no, int num){teamNo=no;numMembers=num;numMembersUnseated=num;};
    int teamNo;
    int numMembers;
    int numMembersUnseated;
    vector<int> tablesAt;
};

struct table {
    table(int no, int num){tableNo=no; totalSeats=num; openSeats=num;};
    int tableNo;
    int totalSeats;
    int openSeats;
    vector<int> teamsSeated;
};

bool compareTeam(team t1, team t2){
    return (t1.numMembers > t2.numMembers);
}

bool compareTeamNo(team t1, team t2){
    return (t1.teamNo < t2.teamNo);
}

bool compareTable(table t1, table t2){
    return (t1.totalSeats > t2.totalSeats);
}

int main(int argc, char** argv){
    vector<bool> isPossible;
    vector<vector<team>> teamAnswers;
    int numTables;
    int numTeams;
    while(cin >> numTeams >> numTables){
        if (numTeams == 0 && numTables == 0){
            break;
        }

        vector<team> teams;
        vector<table> tables;

        int maxTeamSize = 0;

        int totalNumPeople = 0;
        int totalRemainingSeats = 0;

        bool possible = true;

        //populate teams
        for (int x = 0; x < numTeams; x++){
            int teamSize;
            cin >> teamSize;
            if (teamSize > maxTeamSize)
                maxTeamSize = teamSize;
            totalNumPeople += teamSize;
            if (teamSize > numTables){
                //cout << "false 1" << endl;
                possible = false;
            }
            teams.push_back(team(x,teamSize));
        }

        //populate tables
        for (int x = 0; x < numTables; x++){
            int tableSize;
            cin >> tableSize;
            totalRemainingSeats += tableSize;
            tables.push_back(table(x,tableSize));
        }

        //If there are more people than seats this is impossible (duh)
        if (totalNumPeople > totalRemainingSeats){
            //cout << "false 2 " << totalNumPeople << " " << totalRemainingSeats << endl;
            possible = false;
        }

        //sort by desc for tableSize and teamSize
        //sort teams
        sort(teams.begin(), teams.end(), compareTeam);

        //sort tables
        sort(tables.begin(), tables.end(), compareTable);

        /*
        for (int x = 0; x < teams.size(); x++){
            cout << "TeamSize[" << x << "] = " << teams[x].numMembers << endl;
        }
        for (int x = 0; x < tables.size(); x++){
            cout << "TableSize[" << x << "] = " << tables[x].totalSeats << endl;
        }
        */
        
        //cout << possible << endl;
        //If largest team size > # of tables --> automatically not possible
        if (possible){
            for (int x = 0; x < teams.size(); x++){
                for (int y = 0; y < tables.size(); y++){
                    if (teams[x].numMembersUnseated < 1)
                        break;
                    
                    if (tables[y].openSeats > 0){
                        teams[x].numMembersUnseated -= 1;
                        tables[y].openSeats -= 1;
                        tables[y].teamsSeated.push_back(teams[x].teamNo);
                        teams[x].tablesAt.push_back(tables[y].tableNo);
                    }
                }
                if (teams[x].numMembersUnseated > 0){
                    //cout << "This is impossible, still some members unseated!" << endl;
                    possible = false;
                    break;
                }
            }
                //take largest team
                //iterate through tables from largest to smallest
                    //place team member at table
        }
        isPossible.push_back(possible);

        //sort teams back into their team No
        sort(teams.begin(), teams.end(), compareTeamNo);

        teamAnswers.push_back(teams);
    }
    
    //print out answers
    for (int x = 0; x < isPossible.size(); x++){
        cout << isPossible[x] << endl;
        if (isPossible[x]){
            for (int tIdx = 0; tIdx < teamAnswers[x].size(); tIdx++){
                vector<int> tablesAt = teamAnswers[x][tIdx].tablesAt;
                sort(tablesAt.begin(), tablesAt.end());
                for (int y = 0; y < tablesAt.size(); y++){
                    cout << (tablesAt[y] + 1);
                    if (y + 1 < tablesAt.size())
                        cout << " ";
                }
                cout << endl;
            }
        }
    }

    return 0;
}
/* @END_OF_SOURCE_CODE */