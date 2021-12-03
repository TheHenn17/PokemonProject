//Fix the FIXME's (looping if non-integer input)

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

double TYPECHART[18][18] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0,
                            1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0,
                            1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0,
                            1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0,
                            1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0,
                            1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0,
                            2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5,
                            1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0,
                            1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0,
                            1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0,
                            1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0,
                            1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5,
                            1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0,
                            0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0,
                            1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0,
                            1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5,
                            1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0,
                            1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0};

int numTypes = 18;

struct pokemon { //pokemon struct
        string name;
        pokemon* next = 0;
        int type1;
        int type2;
};

struct typeCombo { //type combination struct
	int type1;
        int type2;
	typeCombo* next = 0;
	int ind; //index for unique typecombo table
};

pokemon* getPokemon(char*, int);
void removePokemon(pokemon*&);
typeCombo* getTypeCombos(pokemon*, int&);
double** getTables(typeCombo*, int);
typeCombo* doCalculations(double**, int, pokemon*, typeCombo*, int&);
int enterStatic(typeCombo**&, pokemon*, typeCombo*);
int calcTeamPower(typeCombo*, typeCombo*, typeCombo*, typeCombo*, typeCombo*, typeCombo*, double**);
void calcCharts(typeCombo*, double**, int*&, int*&, int*&);
void outputTeams(typeCombo*, char*, pokemon*, int);
unsigned long long choose(int, int);
int IND(string type);
string TYPE(int ind);
void deleteList(typeCombo*);
void deleteList(pokemon*);

int main(int argc, char** argv) {
        int inp;
        int gen;
	
	if(argc != 3) { //exit if user did not enter input and output file
		cout << "type \"./FindTeams.exe <inputFileName> <outputFileName>\" into the command line" << endl;
		exit(1);
	}

        cout << "Which Generation are you playing?" << endl;
        cout << "\t1. Generation 2-5\n\t2. Generation 6+" << endl;
        cin >> inp;
        while(inp != 1 && inp != 2) { //loops when string entered FIXME
                cout << "Please Enter 1 or 2: " << endl;
                cin >> inp;
        }
        if(inp == 1) {
                TYPECHART[13][16] = 0.5; //steel resists dark and ghost in this generation
                TYPECHART[15][16] = 0.5;
                numTypes = 17; //fairy type is not in this generation
        }
	
	pokemon* P_head = getPokemon(argv[1], gen); //get pokemon from input file

        cout << "Would you like to remove any pokemon from consideration?" << endl;
        cout << "\t1. Yes\n\t2. No" << endl;
        cin >> inp;
        while(inp != 1 && inp != 2) { //loops when string entered FIXME
                cout << "Please Enter 1 or 2: " << endl;
                cin >> inp;
        }
        if(inp == 1) {
                removePokemon(P_head); //remove pokemon from list
        }

        int totalCombos = 0;
        typeCombo* T_head = getTypeCombos(P_head, totalCombos); //get all type combinations
	
	if(totalCombos < 6) { //check if there is enough typecombos for a team of 6
		deleteList(P_head);
        	deleteList(T_head);
		cout << "Not enough type combinations to calculate (less than 6)" << endl;
		exit(1);
	}

        double** tables = getTables(T_head, totalCombos); //create unique typeCombo tables accessed by typeCombos ind field
	
	int best = -1000;
	typeCombo* teams = doCalculations(tables, totalCombos, P_head, T_head, best); //calculate best teams
	cout << endl;
	if(teams == 0) {
		cout << "Calculations Failed" << endl;
	}
	else { 
		outputTeams(teams, argv[2], P_head, best); //output best teams to output file
		cout << "Results written to: " << argv[2] << endl;
	}

	deleteList(teams); //Cleanup
	deleteList(P_head);
	deleteList(T_head);
	for(int i = 0; i < totalCombos; i++) {
                delete[] tables[i];
        }
	delete[] tables;

        return 0;
}

pokemon* getPokemon(char* filename, int gen) {
	ifstream file;
        file.open(filename);
        if(!file.is_open()) { //Error opening file
                cout << "Error: input file could not be opened" << endl;
                exit(1);
        }
        string input;
        pokemon* pok = 0;
        pokemon* prevPok = 0;
        pokemon* head;
        int temp;
        int lineno = 1;
        if(!(file >> input)) { //return null if file is empty
                cout << "Error: input file is empty" << endl;
                exit(1);
        }
        while(!file.eof()) {
                pok = new pokemon;
                pok->name = input;
                file >> input;
                if(IND(input) >= 0 && IND(input) < numTypes) { //get pokemons first type
                        pok->type1 = IND(input);
                }
                else {
                        cout << "Error: pokemon type on line " << 0 << " is invalid"; //Fix later
                        deleteList(head);
                        exit(1);
                }
                if(file >> input) {
                        if(IND(input) >= 0 && IND(input) < numTypes) {
                                pok->type2 = IND(input);
				if(pok->type2 > pok->type1) { //swap typing to avoid duplicate type combos
					temp = pok->type1;
					pok->type1 = pok->type2;
					pok->type2 = temp;
				}
                                file >> input; //does nothing if last pokemon in file
                        }
                        else if (IND(input) >= 0 && IND(input) >= numTypes){
                                cout << "Error: pokemon type on line " << lineno << " is invalid";
                                deleteList(head);
                                exit(1);
                        }
                        else { pok->type2 = -1; }
                }
                else { pok->type2 = -1; } //last pokemon in file, single typing
                if(prevPok != 0) { //generate linked list
                        prevPok->next = pok;
                        prevPok = pok;
                        lineno++;
                }
                else { prevPok = pok; head = pok; lineno++; }
        }
        file.close();
        return head;
}

void removePokemon(pokemon*& head) {
        string name;
        pokemon* p = 0;
        pokemon* i = 0;
        bool removed = false;
        cout << "List the names of pokemon you want to remove (type \"q\" to finish):" << endl;
        cin >> name;
        while(name != "q") {
                p = 0;
                removed = false;
                for(i = head; i != 0; i = i->next) { //iterate through list
                        if(name == i->name) {
                                if(i == head) { //special case head removal
                                        p = head;
                                        head = head->next;
                                        delete p;
                                        removed = true;
                                        break;
                                }
                                else { //common case removal
                                        p->next = i->next;
                                        delete i;
                                        removed = true;
                                        break;
                                }
                        }
                        p = i;
                }
                if(!removed) {
                        //end reached with no removal; must be invalid name
                        cout << "Pokemon name is invalid. Please enter a pokmeon from the file (Case sensitive)" << endl;
                }
                else {
                        cout << name << " removed" << endl;
                }
                cin >> name;
        }
}

typeCombo* getTypeCombos(pokemon* head, int& totalCombos) {
	pokemon* p = 0;
	typeCombo* tc = 0;
	typeCombo* ptc = 0;
	typeCombo* itr = 0;
	typeCombo* T_head = 0;
	bool inList = false;
	for(p = head; p != 0; p = p->next) { //interate through pokemon
		inList = false;
		tc = new typeCombo;
		tc->type1 = p->type1;
		tc->type2 = p->type2;
		if(T_head == 0) { //first type combo (first pokemon)
                        T_head = tc;
                        ptc = T_head;
                        tc->ind = totalCombos++;
                }
		else {
			for(itr = T_head; itr != 0; itr = itr->next) { //iterate through existing combos
				if(itr->type1 == tc->type1 && itr->type2 == tc->type2) { //delete if existing
					delete tc;
                                        tc = 0;
					inList = true;
					break;
				}
			}
			if(!inList) { //add to list
				ptc->next = tc;
				ptc = tc;
                                tc->ind = totalCombos++;
			}
		}
	}
	return T_head;
}

double** getTables(typeCombo* T_head, int totalCombos) { //get unique typecharts for all typecombos
	typeCombo* tc;
        double** tables = new double*[totalCombos];
        for(int i = 0; i < totalCombos; i++) {
                tables[i] = new double[numTypes];
        }
        for(tc = T_head; tc != 0; tc = tc->next) {
                if(tc->type2 < 0) {
                        for(int i = 0; i < numTypes; i++) {
                                tables[tc->ind][i] = TYPECHART[i][tc->type1];
                        }
                }
                else {
                        for(int i = 0; i < numTypes; i++) {
                                tables[tc->ind][i] = TYPECHART[i][tc->type1]*TYPECHART[i][tc->type2];
                        }
                }
        }
        return tables;
}

typeCombo* doCalculations(double** tables, int totalCombos, pokemon* P_head, typeCombo* T_head, int& best) {
	typeCombo** startArr = new typeCombo*[6];
        for(int i = 0; i < 6; i++) {
                startArr[i] = 0;
        }

        int inp;
        int stat = 0;
	cout << "Would you like to enter pokemon you want on the team no matter what? (up to 6)" << endl;
        cout << "\t1. Yes\n\t2. No" << endl;
        cin >> inp;
        while(inp != 1 && inp != 2) { //loops when string entered FIXME
                cout << "Please Enter 1 or 2: " << endl;
                cin >> inp;
        }
        if(inp == 1) {
                stat = enterStatic(startArr, P_head, T_head); //enter static pokemon
        }

        int curBest = -1000;
        int prevBest = -1000;
        bool headPlaced = false;
        typeCombo* temp = 0;
        typeCombo* cur = 0;
        typeCombo* team = 0;
        typeCombo* tc1 = startArr[0];
        typeCombo* tc2 = startArr[1];
        typeCombo* tc3 = startArr[2];
        typeCombo* tc4 = startArr[3];
        typeCombo* tc5 = startArr[4];
        typeCombo* tc6 = startArr[5];

        if (stat == 6) { //user typed in 6, so output power and exit (no file write)
                curBest = calcTeamPower(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                cout << "This team has a Power level of " << curBest << " (Capped at " << numTypes+12 << ")" << endl;
                exit(0);
        }

        unsigned long long total = choose(totalCombos, (6-stat));
	double tally = 0;
        int percent = 0;
        int prevPercent = 0;
        int minutes = 0;
        int hours = 0;

        auto start = std::chrono::steady_clock::now();
        if(startArr[0] != 0) { tc1 = startArr[0]; }
        else { tc1 = T_head; headPlaced = true; }
        while(tc1 != 0) {
                if(startArr[1] != 0) { tc2 = startArr[1]; }
                else if(!headPlaced) { tc2 = T_head; headPlaced = true; }
                else { tc2 = tc1->next; }
                while(tc2 != 0) {
                        if(startArr[2] != 0) { tc3 = startArr[2]; }
                        else if(!headPlaced) { tc3 = T_head; headPlaced = true; }
                        else { tc3 = tc2->next; }
                        while(tc3 != 0) {
                                if(startArr[3] != 0) { tc4 = startArr[3]; }
                                else if(!headPlaced) { tc4 = T_head; headPlaced = true; }
                                else { tc4 = tc3->next; }
                                while(tc4 != 0) {
                                        if(startArr[4] != 0) { tc5 = startArr[4]; }
                                        else if(!headPlaced) { tc5 = T_head; headPlaced = true; }
                                        else { tc5 = tc4->next; }
                                        while(tc5 != 0) {
                                                if(startArr[5] != 0) { tc6 = startArr[5]; }
                                                else if(!headPlaced) { tc6 = T_head; headPlaced = true; }
                                                else { tc6 = tc5->next; }
                                                while(tc6 != 0) {
                                                        curBest = calcTeamPower(tc1, tc2, tc3, tc4, tc5, tc6, tables); //calc power
                                                        tally++;
                                                        percent = (tally/total)*100;
                                                        if(prevPercent < percent) {
                                                                if(percent == 1) {
                                                                        auto stop = std::chrono::steady_clock::now();
                                                                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                                                                        double calcTime = ((double)duration.count()) / 1000000;
                                                                        double time = calcTime*100;
                                                                        while(time >= 60) {
                                                                                minutes++;
                                                                                time-=60;
                                                                        }
                                                                        while(minutes >= 60) {
                                                                                hours++;
                                                                                minutes-=60;
                                                                        }
                                                                        int seconds = time;
                                                                        cout << "Estimated Calculation Time - " << hours << ":" << minutes << ":" << seconds << endl;
                                                                }
                                                                cout << "\r" << flush << "Calculating [" << percent << "%]";
                                                                prevPercent = percent;
                                                        }
                                                        if(curBest >= prevBest) {
								if(curBest > prevBest) { //if new best, create a new team list
									deleteList(team);
									team = 0;
									prevBest = curBest;
								}
                                                		temp = new typeCombo; //add team to team list at current power
                                                		temp->type1 = tc1->type1;
                                                		temp->type2 = tc1->type2;
								temp->ind = tc1->ind;
                                                        	temp->next = 0;
                                                		if(team == 0) { team = temp; cur = team; }
                                                		else { cur->next = temp; cur = temp; }
                                                        	temp = new typeCombo;
                                                        	temp->type1 = tc2->type1;                                                        		temp->type2 = tc2->type2;
								temp->ind = tc2->ind;
                                                        	temp->next = 0;
                                                        	cur->next = temp;
                                                		cur = temp;
                                                		temp = new typeCombo;
                                                		temp->type1 = tc3->type1;
                                                		temp->type2 = tc3->type2;
                                                                temp->ind = tc3->ind;
                                                        	temp->next = 0;
                                                		cur->next = temp;
                                                        	cur = temp;
                                                        	temp = new typeCombo;
                                                		temp->type1 = tc4->type1;
                                                		temp->type2 = tc4->type2;
                                                                temp->ind = tc4->ind;
                                                		temp->next = 0;
                                                        	cur->next = temp;
                                                        	cur = temp;
                                                		temp = new typeCombo;
                                                        	temp->type1 = tc5->type1;
                                                        	temp->type2 = tc5->type2;
                                                                temp->ind = tc5->ind;
                                                		temp->next = 0;
                                                		cur->next = temp;
                                                		cur = temp;
                                                        	temp = new typeCombo;
								temp->type1 = tc6->type1;
                                                                temp->type2 = tc6->type2;
                                                                temp->ind = tc6->ind;
                                                                temp->next = 0;
                                                                cur->next = temp;
                                                                cur = temp;
                                        		}
                                                        tc6 = tc6->next;
                                                }
                                                if(stat >= 5) { break; }
                                                tc5 = tc5->next;
                                        }
                                        if(stat >= 4) { break; }
                                        tc4 = tc4->next;
                                }
                                if(stat >= 3) { break; }
                                tc3 = tc3->next;
                        }
                        if(stat >= 2) { break; }
                        tc2 = tc2->next;
                }
                if(stat >= 1) { break; }
                tc1 = tc1->next;
        }
        delete startArr;
        best = prevBest;
        return team;
}

int enterStatic(typeCombo**& arr, pokemon* P_head, typeCombo* T_head) {
        string name;
        typeCombo* tc = 0;
        pokemon* p = 0;
        int ind = 0;
        cout << "List the names of pokemon you want to be on the team (type \"q\" to finish):" << endl;
        cin >> name;
        while(name != "q" && ind < 6) {
                tc = 0;
		for(p = P_head; p != 0; p = p->next) { //iterate through pokemon
			if(p->name == name) { //match name
                                for(tc = T_head; tc != 0; tc = tc->next) {
                                        if(tc->type1 == p->type1 && tc->type2 == p->type2) { //find typecombo
                                                break;
                                        }
                	        }
                                break;
			}
		}
                if(tc == 0) { //name invalid
                        cout << "Pokemon name is invalid. Please enter a pokmeon from the file (Case sensitive)" << endl;
                }
                else {
                        arr[ind] = tc;
                        ind++;
                        cout << name << " added" << endl;
                }
                if(ind < 6) { cin >> name; }
	}
        return ind;
}

int calcTeamPower(typeCombo* tc1, typeCombo* tc2, typeCombo* tc3, typeCombo* tc4, typeCombo* tc5, typeCombo* tc6, double** tables) {
	int* resistChart = new int[numTypes];
        int* weaknessChart = new int[numTypes];
	int* coverageChart = new int[numTypes];
        for(int i = 0; i < numTypes; i++) {
                resistChart[i] = 0;
                weaknessChart[i] = 0;
                coverageChart[i] = 0;
        }

        calcCharts(tc1, tables, resistChart, weaknessChart, coverageChart); //calc charts for all 6 pokemon
        calcCharts(tc2, tables, resistChart, weaknessChart, coverageChart);
        calcCharts(tc3, tables, resistChart, weaknessChart, coverageChart);
        calcCharts(tc4, tables, resistChart, weaknessChart, coverageChart);
        calcCharts(tc5, tables, resistChart, weaknessChart, coverageChart);
        calcCharts(tc6, tables, resistChart, weaknessChart, coverageChart);

        int total = 0;
        double value = 0;
	for(int i = 0; i < numTypes; i++) {
                value = (resistChart[i]-weaknessChart[i]);
		if(value >= 0) {  //add to power level (numTypes+12)
                        total += (coverageChart[i]+1); 
                }
		else { total += coverageChart[i]+value; }
	}
        delete resistChart;
        delete weaknessChart;
        delete coverageChart;
	return total;
}

void calcCharts(typeCombo* tc, double** tables, int*& resistChart, int*& weaknessChart, int*& coverageChart) {
        double* curTable = tables[tc->ind]; //get unique typechart
        coverageChart[tc->type1] = 1;
        if(tc->type2 > 0) { coverageChart[tc->type2] = 1; }
        for(int i = 0; i < numTypes; i++) { //calc tables
                if(curTable[i] < 1) { resistChart[i] += 1; }
                if(curTable[i] >= 2) { weaknessChart[i] += 1; }
        }
}

unsigned long long choose(int left, int right) {
	unsigned long long ret = 1;
	int i;
	for(i = 0; i < right; i++) {
		ret*=(left-i);
	}
	for(i = right; i >= 2; i--) {
		ret = ret / i;
	}
	return ret;
}

int IND(string type) { //return types index in the TYPECHART given its name
	if(type == "normal") { return 0; }
	if(type == "fire") { return 1; }
	if(type == "water") { return 2; }
	if(type == "electric") { return 3; }
	if(type == "grass") { return 4; }
	if(type == "ice") { return 5; }
	if(type == "fighting") { return 6; }
	if(type == "poison") { return 7; }
	if(type == "ground") { return 8; }
	if(type == "flying") { return 9; }
	if(type == "psychic") { return 10; }
	if(type == "bug") { return 11; }
	if(type == "rock") { return 12; }
	if(type == "ghost") { return 13; }
	if(type == "dragon") { return 14; }
	if(type == "dark") { return 15; }
	if(type == "steel") { return 16; }
        if(type == "fairy") { return 17; }
	return -1;
}

string TYPE(int ind) { //return type give the types index in the TYPECHART
	if(ind == 0) { return "normal"; }
	if(ind == 1) { return "fire"; }
	if(ind == 2) { return "water"; }
	if(ind == 3) { return "electric"; }
	if(ind == 4) { return "grass"; }
	if(ind == 5) { return "ice"; }
	if(ind == 6) { return "fighting"; }
	if(ind == 7) { return "poison"; }
	if(ind == 8) { return "ground"; }
	if(ind == 9) { return "flying"; }
	if(ind == 10) { return "psychic"; }
	if(ind == 11) { return "bug"; }
	if(ind == 12) { return "rock"; }
	if(ind == 13) { return "ghost"; }
	if(ind == 14) { return "dragon"; }
	if(ind == 15) { return "dark"; }
	if(ind == 16) { return "steel"; }
        if(ind == 17) { return "fairy"; }
	return "NULL";
}

void deleteList(typeCombo* head) { //delete linked list
	if(head == 0) { return; }
	typeCombo* temp = head;
	typeCombo* temp2;
	for(temp2 = head->next; temp2 != 0; temp2 = temp2->next) {
		delete temp;
		temp = temp2;
	}
	delete temp;
}

void deleteList(pokemon* head) { //delete linked list
	if(head == 0) { return; }
	pokemon* temp = head;
        pokemon* temp2;
        for(temp2 = head->next; temp2 != 0; temp2 = temp2->next) {
                delete temp;
                temp = temp2;
        }
        delete temp;
}

void outputTeams(typeCombo* teams, char* filename, pokemon* P_head, int best) { //output teams to file
	ofstream file;
        file.open(filename);
        if(!file.is_open()) {
                cout << "Output file could not be opened" << endl;
                return;
        }
        int count = 0;
        bool first;
	pokemon* p;
	int i;
        typeCombo* cur = teams;
	file << "Power levels cap at " << numTypes+12 << endl << "The teams listed below have a Power level of: " << best << endl << endl;
        while(cur != 0) {
                file << "Team Option " << ++count << ":" << endl;
                for(i = 0; i < 6; i++) {
                        first = true;
                        for(p = P_head; p != 0; p=p->next) {
                                if(p->type1 == cur->type1 && p->type2 == cur->type2) {
                                        if(first) { file << p->name; first = false; }
                                        else { file << " / " << p->name; }
                                }
                        }
                        file << endl;
                        cur = cur->next;
                }
                if(cur != 0) { file << endl;}
        }
        file.close();
}