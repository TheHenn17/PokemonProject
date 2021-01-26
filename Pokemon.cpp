#include<iostream>
#include<fstream>

using namespace std;

const double TYPECHART[17][17] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5,
                                  1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0,
                                  1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0,
                                  1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0,
                                  1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5,
                                  1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5,
                                  2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0,
                                  1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0,
                                  1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0,
                                  1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5,
                                  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5,
                                  1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5,
                                  1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5,
                                  0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5,
                                  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5,
                                  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5,
                                  1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5};

const double calcTime = 0.000002858;

struct pokemon {
        string name;
        pokemon* next;
        string type1;
        string type2;
};

struct typeCombo {
	string type1;
        string type2;
	typeCombo* next;
	int ind;
};

int IND(string type);
string TYPE(int ind);
int getMax(int, int);
unsigned long long choose(int, int);
pokemon* getPokemon(char*);
typeCombo* getTypeCombos(pokemon*);
double** getTable(pokemon*, double**);
typeCombo* doCalculations(double**, int, pokemon*, typeCombo*, int&);
int calc(typeCombo*, typeCombo*, typeCombo*, typeCombo*, typeCombo*, typeCombo*, double**);
void outputTeams(typeCombo*, char*, pokemon*, int);
void deleteList(typeCombo*);
void deleteList(pokemon*);

int main(int argc, char** argv) {
	//check if user provided an input and output file; exit if not
	if(argc != 3) {
		cout << "Wrong number of arguments." << endl;
		return 0;
	}
	
	//get pokemon from input file and list of all type combos
	pokemon* P_head = getPokemon(argv[1]);
        typeCombo* T_head = getTypeCombos(P_head);
	
	//get total number of type combos and create dual type tables needed
	int i, type1, type2;
	int totalCombos = 0;
	typeCombo* tc;
	for(tc = T_head; tc != 0; tc = tc->next) {
                tc->ind = totalCombos++;
        }
	if(totalCombos < 6) {
		deleteList(P_head);
        	deleteList(T_head);
		cout << "Not enough data to calculate" << endl;
		return 0;
	}
        double** tables = new double*[totalCombos];
        for(i = 0; i < totalCombos; i++) {
                tables[i] = new double[17];
        }
        for(tc = T_head; tc != 0; tc = tc->next) {
                type1 = IND(tc->type1);
                type2 = IND(tc->type2);
                if(type2 < 0) {
                        for(i = 0; i < 17; i++) {
                                tables[tc->ind][i] = TYPECHART[i][type1];
                        }
                }
                else {
                        for(i = 0; i < 17; i++) {
                                tables[tc->ind][i] = TYPECHART[i][type1]*TYPECHART[i][type2];
                        }
                }
        }
	
	//Calculate teams and output to file
	int best = -1000;
	typeCombo* teams = doCalculations(tables, totalCombos, P_head, T_head, best);
	cout << endl;
	if(teams == 0) {
		cout << "Calculations Failed" << endl;
	}
	else { 
		outputTeams(teams, argv[2], P_head, best);
		cout << "Results written to: " << argv[2] << endl;
	}

	//Cleanup
	deleteList(teams);
	deleteList(P_head);
	deleteList(T_head);
	for(i = 0; i < totalCombos; i++) {
                delete[] tables[i];
        }
	delete[] tables;

	return 0;
}

pokemon* getPokemon(char* filename) {
	ifstream file;
        file.open(filename);
        if(!file.is_open()) {
                cout << "input file could not be opened" << endl;
                return 0;
        }
        string input;
        pokemon* pok = 0;
        pokemon* prevPok = 0;
        pokemon* head;
        if(!(file >> input)) { return 0; }
        while(!file.eof()) {
                pok = new pokemon;
		pok->next = 0;
                pok->name = input;
                file >> input;
                pok->type1 = input;
                if(file >> input) {
                        if(IND(input) >= 0) {
                                pok->type2 = input;
				if(pok->type2 < pok->type1) {
					input = pok->type1;
					pok->type1 = pok->type2;
					pok->type2 = input;
				}
                                file >> input;
                        }
                        else { pok->type2 = "NULL"; }
                }
                else { pok->type2 = "NULL"; }
                if(prevPok != 0) {
                        prevPok->next = pok;
                        prevPok = pok;
                }
                else { prevPok = pok; head = pok; }
        }
        file.close();
	int remove;
        cout << "How many pokemon to remove? ";
        cin >> remove;
        if(remove > 0) { cout << "Which pokemon?" << endl; }
        for(int i = 0; i < remove; i++) {
                cin >> input;
                if(input == head->name) {
                        prevPok = head;
                        head = head->next;
                        delete prevPok;
                }
		else {
			prevPok = head;
			for(pok = head->next; pok != 0; pok = pok->next) {
				if(input == pok->name) {
					if(pok->next == 0) {
						prevPok->next = pok->next;
                                        	delete pok;
						pok = prevPok;
					}
					else {
						prevPok->next = pok->next;
						delete pok;
						pok = prevPok->next;
					}
				}
				else { prevPok = pok; }
			}
		}
        }
	return head;
}

void outputTeams(typeCombo* teams, char* filename, pokemon* P_head, int best) {
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
	file << "Power levels cap at 17" << endl << "The teams listed below have a Power level of: " << best << endl << endl;
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

typeCombo* getTypeCombos(pokemon* head) {
	pokemon* temp;
	typeCombo* node = 0;
	typeCombo* prevNode = 0;
	typeCombo* it;
	typeCombo* T_head = 0;
	bool notInList;
	for(temp = head; temp!=0; temp=temp->next) {
		notInList = true;
		node = new typeCombo;
		node->type1 = temp->type1;
		node->type2 = temp->type2;
		node->next = 0;
		if(T_head == 0) { T_head = node; prevNode = node; }
		else {
			for(it = T_head; it != 0; it=it->next) {
				if(it->type1 == node->type1 && it->type2 == node->type2) {
					delete node;
					notInList = false;
					break;
				}
			}
			if(notInList) {
				prevNode->next = node;
				prevNode = node;
			}
		}
	}
	return T_head;
}

typeCombo* doCalculations(double** tables, int totalCombos, pokemon* P_head, typeCombo* T_head, int& best) {
	typeCombo* arr[6] = {0, 0, 0, 0, 0, 0};
	int i, stat;
	string pokName;
	pokemon* p;
	typeCombo* tc;
	typeCombo* temp;
	cout << "How many static pokemon? ";
	cin >> stat;
	if(stat >= 6 || stat < 0) {
		cout << "Invalid amount of static pokemon" << endl;
		return 0;
	}
	if(stat > 0) { cout << "Which pokemon?" << endl; }
	for(i = 0; i < stat; i++) {
		tc = new typeCombo;
		tc->type1 = "NULL";
		cin >> pokName;
		for(p = P_head; p != 0; p = p->next) {
			if(p->name == pokName) {
				tc->type1 = p->type1;
				tc->type2 = p->type2;
				tc->next = 0;
				break;
			}
		}
		if(tc->type1 == "NULL") { 
			cout << "No such pokemon in the list.";
			for(int j = 0; j < stat; j++) {
				if(arr[i] != 0) { delete arr[i]; }
			}
			delete tc;
			return 0;
		}
		else {
			for(temp = T_head; temp != 0; temp = temp->next) {
                        	if(temp->type1 == tc->type1 && temp->type2 == tc->type2) {
					tc->ind = temp->ind;
                                	break;
                        	}
                	}
		}
		arr[i] = tc;
	}
        int curBest = -1000;
	int prevBest = -1000;
        typeCombo* tc1;
        typeCombo* tc2;
        typeCombo* tc3;
        typeCombo* tc4;
        typeCombo* tc5;
        typeCombo* tc6;
        typeCombo* team = 0;
	temp = 0;
	typeCombo* cur = 0;
	unsigned long long total = choose(totalCombos, (6-stat));
	double tally = 0;
        int percent = 0;
        int prevPercent = -1;
        int minutes = 0;
        double time = calcTime*total;
        while(time >= 60) {
                minutes++;
                time-=60;
        }
        cout << "Estimated Calculation Time - " << minutes << ":" << time << endl;
	switch(stat) {
		case 0: 
      			for(tc1 = T_head; tc1 != 0; tc1 = tc1->next) {
                		for(tc2 = tc1->next; tc2 != 0; tc2 = tc2->next) {
                        		for(tc3 = tc2->next; tc3 != 0; tc3 = tc3->next) {
                                		for(tc4 = tc3->next; tc4 != 0; tc4 = tc4->next) {
                                        		for(tc5 = tc4->next; tc5 != 0; tc5 = tc5->next) {
                                                		for(tc6 = tc5->next; tc6 != 0; tc6 = tc6->next) {
                                                        		curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                        		tally++;
                                                        		percent = (tally/total)*100;
                                                        		if(prevPercent < percent) {
                                                                		cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                		prevPercent = percent;
                                                        		}
									if(curBest >= prevBest) {
										if(curBest > prevBest) {
											deleteList(team);
											team = 0;
											prevBest = curBest;
										}
                                                                		temp = new typeCombo;
                                                                		temp->type1 = tc1->type1;
                                                                		temp->type2 = tc1->type2;
										temp->ind = tc1->ind;
                                                                		temp->next = 0;
                                                                		if(team == 0) { team = temp; cur = team; }
                                                                		else { cur->next = temp; cur = temp; }
                                                                		temp = new typeCombo;
                                                                		temp->type1 = tc2->type1;
                                                                		temp->type2 = tc2->type2;
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
                                                		}
                                        		}
                                		}
                        		}
                		}
        		}
			break;
		case 1:
			for(tc1 = arr[0]; tc1 != 0; tc1 = tc1->next) {
                                for(tc2 = T_head; tc2 != 0; tc2 = tc2->next) {
                                        for(tc3 = tc2->next; tc3 != 0; tc3 = tc3->next) {
                                                for(tc4 = tc3->next; tc4 != 0; tc4 = tc4->next) {
                                                        for(tc5 = tc4->next; tc5 != 0; tc5 = tc5->next) {
                                                                for(tc6 = tc5->next; tc6 != 0; tc6 = tc6->next) {
                                                                        curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                                        tally++;
                                                                        percent = (tally/total)*100;
                                                                        if(prevPercent < percent) {
                                                                                cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                                prevPercent = percent;
                                                                        }
                                                                        if(curBest >= prevBest) {
                                                                                if(curBest > prevBest) {
                                                                                        deleteList(team);
											team = 0;
                                                                                        prevBest = curBest;
                                                                                }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc1->type1;
                                                                                temp->type2 = tc1->type2;
                                                                                temp->ind = tc1->ind;
                                                                                temp->next = 0;
                                                                                if(team == 0) { team = temp; cur = team; }
                                                                                else { cur->next = temp; cur = temp; }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc2->type1;
                                                                                temp->type2 = tc2->type2;
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
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        break;
		case 2:
			for(tc1 = arr[0]; tc1 != 0; tc1 = tc1->next) {
                                for(tc2 = arr[1]; tc2 != 0; tc2 = tc2->next) {
                                        for(tc3 = T_head; tc3 != 0; tc3 = tc3->next) {
                                                for(tc4 = tc3->next; tc4 != 0; tc4 = tc4->next) {
                                                        for(tc5 = tc4->next; tc5 != 0; tc5 = tc5->next) {
                                                                for(tc6 = tc5->next; tc6 != 0; tc6 = tc6->next) {
                                                                        curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                                        tally++;
                                                                        percent = (tally/total)*100;
                                                                        if(prevPercent < percent) {
                                                                                cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                                prevPercent = percent;
                                                                        }
                                                                        if(curBest >= prevBest) {
                                                                                if(curBest > prevBest) {
                                                                                        deleteList(team);
											team = 0;
                                                                                        prevBest = curBest;
                                                                                }
										temp = new typeCombo;
                                                                                temp->type1 = tc1->type1;
                                                                                temp->type2 = tc1->type2;
                                                                                temp->ind = tc1->ind;
                                                                                temp->next = 0;
                                                                                if(team == 0) { team = temp; cur = team; }
                                                                                else { cur->next = temp; cur = temp; }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc2->type1;
                                                                                temp->type2 = tc2->type2;
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
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        break;
		case 3:
			for(tc1 = arr[0]; tc1 != 0; tc1 = tc1->next) {
                                for(tc2 = arr[1]; tc2 != 0; tc2 = tc2->next) {
                                        for(tc3 = arr[2]; tc3 != 0; tc3 = tc3->next) {
                                                for(tc4 = T_head; tc4 != 0; tc4 = tc4->next) {
                                                        for(tc5 = tc4->next; tc5 != 0; tc5 = tc5->next) {
                                                                for(tc6 = tc5->next; tc6 != 0; tc6 = tc6->next) {
                                                                        curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                                        tally++;
                                                                        percent = (tally/total)*100;
                                                                        if(prevPercent < percent) {
                                                                                cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                                prevPercent = percent;
                                                                        }
                                                                        if(curBest >= prevBest) {
                                                                                if(curBest > prevBest) {
                                                                                        deleteList(team);
											team = 0;
                                                                                        prevBest = curBest;
                                                                                }
										temp = new typeCombo;
                                                                                temp->type1 = tc1->type1;
                                                                                temp->type2 = tc1->type2;
                                                                                temp->ind = tc1->ind;
                                                                                temp->next = 0;
                                                                                if(team == 0) { team = temp; cur = team; }
                                                                                else { cur->next = temp; cur = temp; }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc2->type1;
                                                                                temp->type2 = tc2->type2;
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
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        break;
		case 4:
			for(tc1 = arr[0]; tc1 != 0; tc1 = tc1->next) {
                                for(tc2 = arr[1]; tc2 != 0; tc2 = tc2->next) {
                                        for(tc3 = arr[2]; tc3 != 0; tc3 = tc3->next) {
                                                for(tc4 = arr[3]; tc4 != 0; tc4 = tc4->next) {
                                                        for(tc5 = T_head; tc5 != 0; tc5 = tc5->next) {
                                                                for(tc6 = tc5->next; tc6 != 0; tc6 = tc6->next) {
                                                                        curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                                        tally++;
                                                                        percent = (tally/total)*100;
                                                                        if(prevPercent < percent) {
                                                                                cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                                prevPercent = percent;
                                                                        }
                                                                        if(curBest >= prevBest) {
                                                                                if(curBest > prevBest) {
                                                                                        deleteList(team);
											team = 0;
                                                                                        prevBest = curBest;
                                                                                }
										temp = new typeCombo;
                                                                                temp->type1 = tc1->type1;
                                                                                temp->type2 = tc1->type2;
                                                                                temp->ind = tc1->ind;
                                                                                temp->next = 0;
                                                                                if(team == 0) { team = temp; cur = team; }
                                                                                else { cur->next = temp; cur = temp; }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc2->type1;
                                                                                temp->type2 = tc2->type2;
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
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        break;
		case 5:
			for(tc1 = arr[0]; tc1 != 0; tc1 = tc1->next) {
                                for(tc2 = arr[1]; tc2 != 0; tc2 = tc2->next) {
                                        for(tc3 = arr[2]; tc3 != 0; tc3 = tc3->next) {
                                                for(tc4 = arr[3]; tc4 != 0; tc4 = tc4->next) {
                                                        for(tc5 = arr[4]; tc5 != 0; tc5 = tc5->next) {
                                                                for(tc6 = T_head; tc6 != 0; tc6 = tc6->next) {
                                                                        curBest = calc(tc1, tc2, tc3, tc4, tc5, tc6, tables);
                                                                        tally++;
                                                                        percent = (tally/total)*100;
                                                                        if(prevPercent < percent) {
                                                                                cout << "\r" << flush << "Calculating[" << percent << "%]";
                                                                                prevPercent = percent;
                                                                        }
                                                                        if(curBest >= prevBest) {
                                                                                if(curBest > prevBest) {
                                                                                        deleteList(team);
											team = 0;
                                                                                        prevBest = curBest;
                                                                                }
										temp = new typeCombo;
                                                                                temp->type1 = tc1->type1;
                                                                                temp->type2 = tc1->type2;
                                                                                temp->ind = tc1->ind;
                                                                                temp->next = 0;
                                                                                if(team == 0) { team = temp; cur = team; }
                                                                                else { cur->next = temp; cur = temp; }
                                                                                temp = new typeCombo;
                                                                                temp->type1 = tc2->type1;
                                                                                temp->type2 = tc2->type2;
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
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        break;
		default:
			cout << "Unexpected Error" << endl;
			break;
	}
	for(int j = 0; j < stat; j++) {
        	if(arr[i] != 0) { delete arr[i]; }
        }
	best = prevBest;
        return team;
}

int calc(typeCombo* tc1, typeCombo* tc2, typeCombo* tc3, typeCombo* tc4, typeCombo* tc5, typeCombo* tc6, double** tables) {
	double* curTable = 0;
	int total = 0;
	int type1, type2, i, num1;
	double value;
	int resistChart[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int weaknessChart[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int coverageChart[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	curTable = tables[tc1->ind];
	type1 = IND(tc1->type1);
	type2 = IND(tc1->type2);
	for(i = 0; i < 17; i++) {
		value = curTable[i];
		if(value == 0.0) { resistChart[i] += 1; }
		if(value == 0.5) { resistChart[i] += 1; }
		if(value == 0.25) { resistChart[i] += 1; }
		if(value == 2.0) { weaknessChart[i] += 1; }
		if(value == 4.0) { weaknessChart[i] += 1; }
		if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
		if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
	}
	curTable = tables[tc2->ind];
        type1 = IND(tc2->type1);
        type2 = IND(tc2->type2);
        for(i = 0; i < 17; i++) {
                value = curTable[i];
                if(value == 0.0) { resistChart[i] += 1; }
                if(value == 0.5) { resistChart[i] += 1; }
                if(value == 0.25) { resistChart[i] += 1; }
                if(value == 2.0) { weaknessChart[i] += 1; }
                if(value == 4.0) { weaknessChart[i] += 1; }
                if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
                if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
        }
	curTable = tables[tc3->ind];
        type1 = IND(tc3->type1);
        type2 = IND(tc3->type2);
        for(i = 0; i < 17; i++) {
                value = curTable[i];
                if(value == 0.0) { resistChart[i] += 1; }
                if(value == 0.5) { resistChart[i] += 1; }
                if(value == 0.25) { resistChart[i] += 1; }
                if(value == 2.0) { weaknessChart[i] += 1; }
                if(value == 4.0) { weaknessChart[i] += 1; }
                if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
                if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
        }
	curTable = tables[tc4->ind];
        type1 = IND(tc4->type1);
        type2 = IND(tc4->type2);
        for(i = 0; i < 17; i++) {
                value = curTable[i];
                if(value == 0.0) { resistChart[i] += 1; }
                if(value == 0.5) { resistChart[i] += 1; }
                if(value == 0.25) { resistChart[i] += 1; }
                if(value == 2.0) { weaknessChart[i] += 1; }
                if(value == 4.0) { weaknessChart[i] += 1; }
                if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
                if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
        }
	curTable = tables[tc5->ind];
        type1 = IND(tc5->type1);
        type2 = IND(tc5->type2);
        for(i = 0; i < 17; i++) {
                value = curTable[i];
                if(value == 0.0) { resistChart[i] += 1; }
                if(value == 0.5) { resistChart[i] += 1; }
                if(value == 0.25) { resistChart[i] += 1; }
                if(value == 2.0) { weaknessChart[i] += 1; }
                if(value == 4.0) { weaknessChart[i] += 1; }
                if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
                if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
        }
	curTable = tables[tc6->ind];
        type1 = IND(tc6->type1);
        type2 = IND(tc6->type2);
        for(i = 0; i < 17; i++) {
                value = curTable[i];
                if(value == 0.0) { resistChart[i] += 1; }
                if(value == 0.5) { resistChart[i] += 1; }
                if(value == 0.25) { resistChart[i] += 1; }
                if(value == 2.0) { weaknessChart[i] += 1; }
                if(value == 4.0) { weaknessChart[i] += 1; }
                if(TYPECHART[type1][i] == 2.0) { coverageChart[i] = 1; }
                if(type2 < 0 && TYPECHART[type2][i] == 2.0) { coverageChart[i] = 1; }
        }
	for(i = 0; i < 17; i++) {
		num1 = (resistChart[i]-weaknessChart[i]);
		if(num1 < 0) { total += (coverageChart[i]+num1); }
		else { total += coverageChart[i]; }
	}
	return total;
}

int IND(string type) {
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
	return -1;
}

string TYPE(int ind) {
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
	return "NULL";
}

int getMax(int a, int b) {
	if(a >= b) { return a; }
	return b;
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

void deleteList(typeCombo* head) {
	if(head == 0) { return; }
	typeCombo* temp = head;
	typeCombo* temp2;
	for(temp2 = head->next; temp2 != 0; temp2 = temp2->next) {
		delete temp;
		temp = temp2;
	}
	delete temp;
}
void deleteList(pokemon* head) {
	if(head == 0) { return; }
	pokemon* temp = head;
        pokemon* temp2;
        for(temp2 = head->next; temp2 != 0; temp2 = temp2->next) {
                delete temp;
                temp = temp2;
        }
        delete temp;
}
