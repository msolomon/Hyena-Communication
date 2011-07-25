#include "pop.h"
#include <QString>

using namespace std;

pop::pop(){
	ENV = new environment();
}

pop::~pop(){
	delete ENV;
}

void pop::add_blank_nodes(){
	for(int i = 0; i < POP_SIZE; i++){
		the_pop[i] = new team();
	}
}

void pop::save_data(int iteration){
	// total ms from start
	data[iteration][0] = QDateTime::currentMSecsSinceEpoch() - trialstarttime;
	// generation's average team fitnesses
	float avg_fit = 0;
	for (int i = 0; i < POP_SIZE; i++) {
		avg_fit += the_pop[i]->get_avg_fit();
	}
    data[iteration][1] = avg_fit / POP_SIZE;

    //// Best team information
	// average distance to zebra (per hyena)
	data[iteration][2] = the_pop[pop_bestteam]->get_avg_dist_to_zebra();
	// average number of lion attacks (for whole team per test, not per hyena)
	data[iteration][3] = the_pop[pop_bestteam]->get_avg_lion_attacks();
    // average penalty from lion attacks (for whole team/test, not per hyena)
    data[iteration][4] = the_pop[pop_bestteam]->get_avg_penalty();
	// average bonus from getting close to zebra (whole team/test, not per hy.)
	data[iteration][5] = the_pop[pop_bestteam]->get_avg_reward();
	// average fitness for best team (for whole team per test, not per hyena)
	data[iteration][6] = the_pop[pop_bestteam]->get_avg_fit();
	// best team average number of hits
	data[iteration][7] = the_pop[pop_bestteam]->get_avg_hits();
	// best team average importance of a given node type
	data[iteration][8] = 0;
	double *imp = the_pop[pop_bestteam]->get_importance();
	for(int i = 0; i < NUM_OPS; i++){
		data[iteration][8] += imp[i] / (NUM_OPS);
	}

	/*
	//// Average hits per hyena on each node type, for entire generation
	float uses[NUM_OPS] = {};
	for(int i = 0; i < POP_SIZE; i++){
		float *h_uses = the_pop[i]->get_uses();
		for(int j = 0; j < NUM_OPS; j++){
			uses[j] += h_uses[j];
		}
	}

	// Write the values
	for(int i = 0; i < NUM_OPS; i++){
		data[iteration][i+NUM_EXTRA] = uses[i] / (float)(POP_SIZE);
	}
	*/
/*
	// Best team hits per hyena on each node type
	float *uses = the_pop[pop_bestteam]->get_uses();
	for(int i = 0; i < NUM_OPS; i++){
		data[iteration][i+NUM_EXTRA] = uses[i];
	}
*/
	// Best team average importance for each node type
	for(int i = 0; i < NUM_OPS; i++){
		data[iteration][i+NUM_EXTRA] = imp[i];
	}

	// Best team individual fitnesses
	for(int i = 0; i < NUM_HYENAS; i++){
		data[iteration][i + (NUM_OPS) + NUM_EXTRA] =
				the_pop[pop_bestteam]->get_hyena_fit(i);
	}
/*
	// Best team individual tree hits
	for(int i = 0; i < NUM_HYENAS; i++){
		data[iteration][i +2*(NUM_OPS)+NUM_EXTRA+NUM_HYENAS] =
				the_pop[pop_bestteam]->hyenas[i].get_hits() /
				(float) (NUM_TESTS * TIME_STEPS);
	}

	// Best team individual named counts
	for(int i = 0; i < NUM_HYENAS; i++){
		data[iteration][i +2*(NUM_OPS)+NUM_EXTRA+2*NUM_HYENAS] =
				the_pop[pop_bestteam]->hyenas[i].get_uses()[TRACKED_OP] /
				(float) (NUM_TESTS * TIME_STEPS);
	}
*/
}

void pop::write_data(int trial){
	QString fname = QString(DATA_TEMPLATE).arg(trial+1);
	ofstream f;
	f.open(fname.toStdString().c_str());

	// provide column labels
	f << "trial gen time avg_fit best_zeb_dist best_num_attacks best_pen "
		 "best_reward best_fit best_hits best_imp "
		 // terminals
		 "zebra nearest_hyena nearest_lion nearest_calling "
		 "north randm last_move constant number_calling mirror_nearest "
		 "last_pen named landmark "
		 // nonterminals
		 "sum subtract compare invert iflteMAG iflteCLOCKWISE ifVectorZero ";
	for(int i = 1; i < NUM_HYENAS; i++){
		f << "h" << i << " ";
	}
	f << "h" << (int)NUM_HYENAS << "\n";

	// iterations
	for(int i = 0; i < GENERATIONS; i++){
		f << trial + 1 << " " << i + 1 << " " ; // trial and generation
		// now write all data fields
		for(int j = 0; j < NUM_EXTRA + (NUM_OPS) + NUM_HYENAS - 1; j++){
			f << data[i][j] << " ";
		}
		f << data[i][NUM_EXTRA + (NUM_OPS) + NUM_HYENAS - 1]
		  << "\n";
	}
	f.close();
}

void pop::generate(void) {
	for (int i = 0; i < POP_SIZE; i++) {
		the_pop[i] = new team();
		the_pop[i]->generate();
	}
}

void pop::evaluate_team(int member){
	ENV->set_up(the_pop[member]);
	the_pop[member]->reset_fitness();
	for (int test = 0; test < NUM_TESTS; test++) {
//		the_pop[member]->reset_team();
		ENV->place_agents(test);
		the_pop[member]->reset_inputs();
		for (int g = 0; g < TIME_STEPS; g++) {
			ENV->update_vectors();
			ENV->move();
			ENV->evaluate();
		}
	}
	the_pop[member]->calc_avg_fit();
}

void pop::draw_best(int member, int iteration){
	team best;
	best.copy(the_pop[member]);
	ENV->set_up(&best);
	//		the_pop[member]->reset_team();
	ENV->place_agents(0); // just use first set of start positions
	best.reset_inputs();
	for (int g = 0; g < TIME_STEPS; g++) {
		ENV->update_vectors();
		ENV->draw(helper, iteration);
		ENV->move();
		ENV->evaluate();
	}
	best.clear();
}

void pop::evolve_repeat(){
	evolve_repeat(1);
}

void pop::evolve_repeat(int trial){
	trial--;
	for(int i = 0; i < TRIALS; i++){
		generate();
		calc_trial(QString::number(trial+i+1));
		calc_trial_total(QString::number(TRIALS+trial));
		trialstarttime = QDateTime::currentMSecsSinceEpoch();
		evolve(trial+i);
//		exit(0);
	}
	for(int i = 0; i < POP_SIZE; i++){
		the_pop[i]->clear();
		delete the_pop[i];
	}
}

void pop::evolve(int trial) {
	ENV->generate_positions();
	for (int i = 0; i < POP_SIZE; i++) {
		evaluate_team(i);
	}
	string fname = QString(VIDEO_TEMPLATE).arg(trial+1).toStdString();
	ofstream f;
	f.open(fname.c_str());
	f.close();
	cout << "Trial " << trial + 1 << endl;
	ENV->fname = fname;

	for (int i = 0; i < GENERATIONS; i++) {
		// update the GUI
		calc_iter(QString::number(i+1));
		calc_iter_total(QString::number(GENERATIONS));
		calc_iter_percent(i);
		calc_iter_percent_total(GENERATIONS - 1);
		calc_trial_percent(trial * GENERATIONS + i);
		calc_trial_percent_total(GENERATIONS * TRIALS - 1);

		// generate a new set of starting positions for all to use
		ENV->generate_positions();

		// only use one method of reproduction
		if(ISLAND_STEADY)
			island_reproduce();
		if(TEAM_GENERATIONAL || ISLAND_GENERATIONAL ||
		   OET_GENERATIONAL)
			all_generational();
		pop_bestteam = select_best_team(1);
		save_data(i);

		// draw the best team
		if(i % DRAW_EVERY == (DRAW_EVERY - 1)){
			f.open(fname.c_str(), ios_base::app);
			f << "generation " << i + 1 << "\n";
			f.close();
            cout << "Generation " << i + 1 << " of " << GENERATIONS <<
					" (" << (i+1)/(float)GENERATIONS * 100 << "% of trial " <<
					trial + 1 << ")" << endl;
			draw_best(pop_bestteam, i);
		}
	}

	write_data(trial); // one file per trial

	// graphviz output of the first hyena in best team of last generation's tree
	fname = QString(GRAPHVIZ_TEMPLATE).arg(trial+1).toStdString();
	f.open(fname.c_str());
    f << the_pop[select_best_team(1)]->hyenas[0].tree->graphviz(NULL, "").toStdString() << endl;
	f.close();

    // retest the best team of the last gen FINAL_TESTS times and save the data
	final_test(trial);

}

void pop::final_test(int trial){
	QString fname = QString(FINAL_TEMPLATE).arg(trial+1);
	ofstream f;
	f.open(fname.toStdString().c_str());
	// provide column labels
	f << "trial id best_zeb_dist best_num_attacks best_pen "
		 "best_reward best_fit best_hits best_imp "
		 // terminals
		 "zebra nearest_hyena nearest_lion nearest_calling "
		 "north randm last_move constant number_calling mirror_nearest "
		 "last_pen named landmark "
		 // nonterminals
		 "sum subtract compare invert iflteMAG iflteCLOCKWISE ifVectorZero ";
	for(int i = 1; i < NUM_HYENAS; i++){
		f << "h" << i << " ";
	}
	f << "h" << (int)NUM_HYENAS << "\n";

	ENV->set_up(the_pop[pop_bestteam]);
	int testnum = 0;
	for (int test = 0; test < FINAL_TESTS; test++) {
		testnum == (NUM_TESTS-1) ? testnum = 0 : testnum++;
		if(testnum == 0) // need to generate more test positions
			ENV->generate_positions();
		the_pop[pop_bestteam]->reset_fitness();
		ENV->place_agents(testnum);
		the_pop[pop_bestteam]->reset_inputs();
		for (int g = 0; g < TIME_STEPS; g++) {
			ENV->update_vectors();
			ENV->move();
			ENV->evaluate();
		}

		the_pop[pop_bestteam]->write_avg_fit_final(f, trial+1, test+1);
	}
	f.close();
}

/*
void pop::OET1_reproduce() {
	int team_replace1, team_replace2;
	int parent_hyena;
	int best = select_best_team(1);
	do {
		team_replace1 = tourn_select(-1);
	} while (team_replace1 == best);
	do {
		team_replace2 = tourn_select(-1);
	} while (team_replace1 == team_replace2 || team_replace2 == best);
	for (int i = 0; i < NUM_HYENAS; i++) {
		// Piecewise construct two new teams to replace the poor teams 
		do { // first parent's hyena
			parent_hyena = member_select(1, i);
		} while (parent_hyena == team_replace1 || parent_hyena == team_replace2);
		the_pop[team_replace1]->copy(the_pop[parent_hyena], i);
		do { // second parent's hyena
			parent_hyena = member_select(1, i);
		} while (parent_hyena == team_replace1 || parent_hyena == team_replace2);
		the_pop[team_replace2]->copy(the_pop[parent_hyena], i);
	}

	the_pop[team_replace1]->calc_size();
	the_pop[team_replace2]->calc_size();
	//         the_pop[r1]->xOver(the_pop[r2]);
	the_pop[team_replace1]->xOver(the_pop[team_replace2]);
	the_pop[team_replace1]->mutate();
	the_pop[team_replace2]->mutate();
	evaluate_team(team_replace1);
	evaluate_team(team_replace2);
}

void pop::island_reproduce(){
    int ps1, rs1;
    int ps2, rs2;
    // select hyenas
    for(int i =0; i < NUM_HYENAS;i++){
		ps1 = member_select(1,i);
        do{
			rs1 = member_select(-1,i);
        }while(ps1 == rs1);
        do{
			ps2 = member_select(1,i);
        }while(ps2 == ps1 || ps2 == rs1);
        do{
			rs2 = member_select(-1,i);
        }while(rs2 == rs1 || rs2 == ps1 || rs2 == ps2);
		the_pop[rs1]->copy(the_pop[ps1],i);  // hyena
		the_pop[rs2]->copy(the_pop[ps2],i);  // hyena
        the_pop[rs1]->calc_size();
        the_pop[rs2]->calc_size();
		the_pop[rs1]->xOver(the_pop[rs2],i);
		the_pop[rs1]->mutate(i);
		evaluate_team(rs1);
    }

}

void pop::member_reproduce() {
        int ps1, pi1, rs1, ri1;
        // select members
        for (int i = 0; i < TEAM_SIZE; i++) {
                ps1 = member_select(1, i, scout); // 0 == scout
                do {
                        rs1 = member_select(-1, i, scout); // 0== scout
                } while (ps1 == rs1);
                pi1 = member_select(1, i, investigator); // -1 == investigator
                do {
                        ri1 = member_select(-1, i, investigator);
                } while (ri1 == pi1);
                the_pop[rs1]->copy(the_pop[ps1], i, scout); // scout
                the_pop[ri1]->copy(the_pop[pi1], i, investigator); // investigator
                the_pop[rs1]->calc_size();
                the_pop[ri1]->calc_size();
                //         the_pop[r1]->xOver(the_pop[r2]);
                the_pop[rs1]->mutate(i, scout);
                the_pop[ri1]->mutate(i, investigator);
                evaluate_team(rs1, 0);
                evaluate_team(ri1, 0);
        }
}
*/

void pop::all_generational(){
	pop *temp = new pop();
	temp->add_blank_nodes();
	delete temp->ENV;
	temp->ENV = ENV;
	int bound; // determines how to split the new population between island and team
	if(TEAM_GENERATIONAL)
		bound = POP_SIZE;       // team approach
	if(ISLAND_GENERATIONAL)
		bound = 0;                      // island approach
	if(OET_GENERATIONAL)
		bound = POP_SIZE/2;   // OET approach,  POP_SIZE should always be even
	for (int i = 0; i < bound; i = i + 2) {
		int p1, p2;
		// select teams
		p1 = tourn_select(1);
		do {
			p2 = tourn_select(1);
		} while (p2 == p1);
		temp->the_pop[i]->copy(the_pop[p1]);
		temp->the_pop[i + 1]->copy(the_pop[p2]);
		temp->the_pop[i]->calc_size();
		temp->the_pop[i + 1]->calc_size();
		temp->the_pop[i]->xOver(temp->the_pop[i + 1]);
		temp->the_pop[i]->mutate();
		temp->the_pop[i + 1]->mutate();
		temp->evaluate_team(i);
		temp->evaluate_team(i + 1);
	}

	for (int i = bound; i < POP_SIZE; i = i + 2) {
		// all-star
		int parent_hyena;
		for (int j = 0; j < NUM_HYENAS; j++) {
			// Piecewise construct new teams, ignoring previous associations – island model
			parent_hyena = member_select(1, j);
			temp->the_pop[i]->copy(the_pop[parent_hyena], j);
			parent_hyena = member_select(1, j);
			temp->the_pop[i + 1]->copy(the_pop[parent_hyena], j);
		}
		temp->the_pop[i]->calc_size();
		temp->the_pop[i + 1]->calc_size();
		temp->the_pop[i]->xOver(temp->the_pop[i + 1]);
		temp->the_pop[i]->mutate();
		temp->the_pop[i + 1]->mutate();
		temp->evaluate_team(i);
		temp->evaluate_team(i + 1);
	}

	temp->ENV = NULL;

	for (int i = 0; i < POP_SIZE; i++) {
		// delete the old team
		the_pop[i]->clear();
		delete the_pop[i];
		// now point to the new team
		the_pop[i] = (temp->the_pop[i]);
	}
	delete temp; // doesn't delete the new teams (this is good)
}

/*
void pop::team_reproduce() {
	int p1, p2, r1, r2;
	// select teams    
	p1 = tourn_select(1);
	do {
		p2 = tourn_select(1);
	} while (p2 == p1);
	do {
		r1 = tourn_select(-1); // -1 for select worst
	} while (r1 == p1 || r1 == p2);
	do {
		r2 = tourn_select(-1);
	} while (r2 == p1 || r2 == p1 || r2 == r1);
	the_pop[r1]->copy(the_pop[p1]);
	the_pop[r2]->copy(the_pop[p2]);
	the_pop[r1]->calc_size();
	the_pop[r2]->calc_size();
	the_pop[r1]->xOver(the_pop[r2]);
	the_pop[r1]->mutate();
	the_pop[r1]->mutate();
	evaluate_team(r1);
	evaluate_team(r2);
}
*/

int pop::member_select(int c, int member) {
	int best = 0, current;
	float current_fit;
	float best_fit;
	best = Random::Global.Integer(POP_SIZE);
	best_fit = the_pop[best]->get_hyena_fit(member);
	for (int i = 1; i < TOURNAMENT_SIZE; i++) {
		current = Random::Global.Integer(POP_SIZE);
		current_fit = the_pop[current]->get_hyena_fit(member);
		if (c == 1) {
			if (current_fit > best_fit) {
				best_fit = current_fit;
				best = current;
			}
		} else if (c == -1) {
			if (current_fit < best_fit) {
				best_fit = current_fit;
				best = current;
			}
		}
	}
	return best;
}

int pop::tourn_select(int c) { // or worst if c = -1
	int best = 0, current;
	float current_fit;
	float best_fit;
	best = Random::Global.Integer(POP_SIZE);

	best_fit = the_pop[best]->get_avg_fit();
	for (int i = 1; i < TOURNAMENT_SIZE; i++) {
		current = Random::Global.Integer(POP_SIZE);
		current_fit = the_pop[current]->get_avg_fit();
		if (c == 1) {
			if (current_fit > best_fit) {
				best_fit = current_fit;
				best = current;
			}
		} else if (c == -1) {
			if (current_fit < best_fit) {
				best_fit = current_fit;
				best = current;
			}
		}
	}
	return best;
}

int pop::select_best_team(int c) { // or worst if c = -1
	int best = 0;
	float current_fit;
	float best_fit = the_pop[0]->get_avg_fit();
	for (int i = 1; i < POP_SIZE; i++) {
		current_fit = the_pop[i]->get_avg_fit();
		if (c == 1) {
			if (current_fit > best_fit) {
				best_fit = current_fit;
				best = i;
			}
		} else if (c == -1) {
			if (current_fit < best_fit) {
				best_fit = current_fit;
				best = i;
			}
		}
	}
	return best;
}
