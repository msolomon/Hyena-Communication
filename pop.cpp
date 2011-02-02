#include "pop.h"

using namespace std;

pop::pop(){
    for(int i = 0; i < POP_SIZE; i++){
        the_pop[i] = NULL;
    }
}

void pop::save_data(int g, int trial) {
	float avg_fit = 0;
	for (int i = 0; i < POP_SIZE; i++) {
		avg_fit += the_pop[i]->get_avg_fit();
	}
	data[0 + trial * (TEAM_SIZE * 2 + 2)][g] = avg_fit / POP_SIZE;
	int best = select_best_team(1);
	data[1 + trial * (TEAM_SIZE * 2 + 2)][g] = the_pop[best]->get_avg_fit();
	data[2 + trial * (TEAM_SIZE * 2 + 2)][g]
			= the_pop[best]->get_avg_dist_to_zebra();
	data[3 + trial * (TEAM_SIZE * 2 + 2)][g]
			= the_pop[best]->get_avg_lion_attacks();
	for (int t = 0; t < TEAM_SIZE; t++) {
		data[4 + t + trial * (TEAM_SIZE * 2 + 2)][g]
				= the_pop[best]->get_scout_fit(t);
		data[4 + t + TEAM_SIZE + trial * (TEAM_SIZE * 2 + 2)][g]
				= the_pop[best]->get_invest_fit(t);
	}
	pop_bestteam = best;
	data[4][g] = the_pop[pop_bestteam]->get_avg_fit();
}

void pop::write_fitnesses(void) {
	cout << "writing fitnesses" << endl;
	ofstream fit;
//	float avg_fit = 0;
	fit.open("fit.txt", ios_base::app);
	for (int i = 0; i < ITERATIONS; i++) {
		fit << i << " ";
		for (int j = 0; j < (TEAM_SIZE * 2 + 4) * TRIALS; j++) {
			if (j % (TEAM_SIZE * 2 + 2) == 0)
				fit << "  :  ";
			fit << data[j][i] << " ";
		}
		fit << endl;
	}
}

void pop::generate(Helper *h) {
	helper = h;
	pop::generate();
}

void pop::generate(void) {
	for (int i = 0; i < POP_SIZE; i++) {
		if(the_pop[i] != NULL)
			delete the_pop[i];
		the_pop[i] = new team;
		//TODO:here
		the_pop[i]->generate();
	}
}

void pop::evaluate_team(int member, int flag){
	evaluate_team(member, flag, -1);
}

void pop::evaluate_team(int member, int flag, int iteration) {
	ENV.set_up(the_pop[member]);
	the_pop[member]->reset_fitness();
	for (int tests = 0; tests < NUM_TESTS; tests++) {
		the_pop[member]->reset_team();
		for (int g = 0; g < TIME_STEPS; g++) {
			if(flag) ENV.draw(helper, iteration);
			ENV.update_vectors();
			if (flag) {
				ENV.draw(helper, iteration);
				//update();
			}
			ENV.move();
			ENV.evaluate();
		}
	}
	the_pop[member]->calc_avg_fit();
}

void pop::evolve_repeat(){
	for(int i = 0; i < TRIALS; i++){
		calc_trial(QString::number(i+1));
		calc_trial_total(QString::number(TRIALS));
		evolve(i);
	}
}

void pop::evolve(int t) {
	for (int i = 0; i < POP_SIZE; i++) {
		evaluate_team(i, 0);
	}
	for (int i = 0; i < ITERATIONS; i++) {
		// update the GUI
		calc_iter(QString::number(i+1));
		calc_iter_total(QString::number(ITERATIONS));
		calc_iter_percent(i+1);
		calc_iter_percent_total(ITERATIONS);
		calc_trial_percent(t*ITERATIONS + i);
		calc_trial_percent(ITERATIONS*TRIALS);

//		team_reproduce();
//		member_reproduce();
//		OET1_reproduce();
		oet_generational();
		save_data(i, t);
		if (i % EVALUATE_EVERY == 0) {
			int bestTeam;
			bestTeam = select_best_team(1);
			evaluate_team(bestTeam, 1, i);
		}
	}
	if (t + 1 == TRIALS)
		write_fitnesses();
}

void pop::OET1_reproduce() {
	int team_replace1, team_replace2;
	int parent_scout, parent_investigator;
	int best = select_best_team(1);
	do {
		team_replace1 = tourn_select(-1);
	} while (team_replace1 == best);
	do {
		team_replace2 = tourn_select(-1);
	} while (team_replace1 == team_replace2 || team_replace2 == best);
	for (int i = 0; i < NUM_HYENAS; i++) {
		// Piecewise construct two new teams to replace the poor teams 
		do { // first parent's scout
			parent_scout = member_select(1, i, scout);
		} while (parent_scout == team_replace1 || parent_scout == team_replace2);
		the_pop[team_replace1]->copy(the_pop[parent_scout], i, scout);
		do { // second parent's scout
			parent_scout = member_select(1, i, scout);
		} while (parent_scout == team_replace1 || parent_scout == team_replace2);
		the_pop[team_replace2]->copy(the_pop[parent_scout], i, scout);
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		do { // first parent's investigator
			parent_investigator = member_select(1, i, investigator);
		} while (parent_investigator == team_replace1 || parent_investigator
				== team_replace2);
		the_pop[team_replace1]->copy(the_pop[parent_investigator], i,
				investigator);
		do { // second parent's investigator
			parent_investigator = member_select(1, i, investigator);
		} while (parent_investigator == team_replace1 || parent_investigator
				== team_replace2);
		the_pop[team_replace2]->copy(the_pop[parent_investigator], i,
				investigator);
	}
	the_pop[team_replace1]->calc_size();
	the_pop[team_replace2]->calc_size();
	//         the_pop[r1]->xOver(the_pop[r2]);
	the_pop[team_replace1]->xOver(the_pop[team_replace2]);
	the_pop[team_replace1]->mutate();
	the_pop[team_replace2]->mutate();
	evaluate_team(team_replace1, 0);
	evaluate_team(team_replace2, 0);
}

void pop::island_reproduce() {
	int ps1, pi1, rs1, ri1;
	int ps2, pi2, rs2, ri2;
	// select scouts   
	for (int i = 0; i < TEAM_SIZE; i++) {
		ps1 = member_select(1, i, scout); //
		do {
			rs1 = member_select(-1, i, scout);
		} while (ps1 == rs1);
		do {
			ps2 = member_select(1, i, scout);
		} while (ps2 == ps1 || ps2 == rs1);
		do {
			rs2 = member_select(-1, i, scout);
		} while (rs2 == rs1 || rs2 == ps1 || rs2 == ps2);
		//select investigators
		pi1 = member_select(1, i, investigator);
		do {
			ri1 = member_select(-1, i, investigator);
		} while (ri1 == pi1);
		do {
			pi2 = member_select(1, i, investigator);
		} while (pi2 == pi1 || pi2 == ri1);
		do {
			ri2 = member_select(-1, i, investigator);
		} while (ri2 == ri1 || ri2 == pi1 || ri2 == pi2);
		the_pop[rs1]->copy(the_pop[ps1], i, scout); // scout
		the_pop[rs2]->copy(the_pop[ps2], i, scout); // scout
		the_pop[ri1]->copy(the_pop[pi1], i, investigator); // investigator
		the_pop[ri2]->copy(the_pop[pi2], i, investigator); // investigator
		the_pop[rs1]->calc_size();
		the_pop[ri1]->calc_size();
		the_pop[rs2]->calc_size();
		the_pop[ri2]->calc_size();
		the_pop[rs1]->xOver(the_pop[rs2], i, scout);
		the_pop[ri1]->xOver(the_pop[ri2], i, investigator);
		the_pop[rs1]->mutate(i, scout);
		the_pop[ri1]->mutate(i, investigator);
		evaluate_team(rs1, 0);
		evaluate_team(ri1, 0);
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

void pop::oet_generational() {
	pop temp;
	temp.generate();
	for (int i = 0; i < POP_SIZE; i = i + 2) {
		int p1, p2;
		// select teams    
		p1 = tourn_select(1);
		do {
			p2 = tourn_select(1);
		} while (p2 == p1);
		temp.the_pop[i]->copy(the_pop[p1]);
		temp.the_pop[i + 1]->copy(the_pop[p2]);
		temp.the_pop[i]->calc_size();
		temp.the_pop[i + 1]->calc_size();
		temp.the_pop[i]->xOver(temp.the_pop[i + 1]);
		temp.the_pop[i]->mutate();
		temp.the_pop[i + 1]->mutate();
		temp.evaluate_team(i, 0);
		temp.evaluate_team(i + 1, 0);
	}

	for (int i = POP_SIZE / 2; i < POP_SIZE; i = i + 2) {
		// all-star
		int parent_scout, parent_investigator;
		for (int j = 0; j < NUM_HYENAS; j++) {
			// Piecewise construct two new teams to replace the poor teams 
			parent_scout = member_select(1, j, scout);
			temp.the_pop[i]->copy(the_pop[parent_scout], j, scout);
			parent_scout = member_select(1, j, scout);
			temp.the_pop[i + 1]->copy(the_pop[parent_scout], j, scout);
		}
		for (int j = 0; j < NUM_LIONS; j++) {
			parent_investigator = member_select(1, j, investigator);
			temp.the_pop[i]->copy(the_pop[parent_investigator], j, investigator);
			parent_investigator = member_select(1, j, investigator);
			temp.the_pop[i + 1]->copy(the_pop[parent_investigator], j,
					investigator);
		}
		temp.the_pop[i]->calc_size();
		temp.the_pop[i + 1]->calc_size();
		temp.the_pop[i]->xOver(temp.the_pop[i + 1]);
		temp.the_pop[i]->mutate();
		temp.the_pop[i + 1]->mutate();
		temp.evaluate_team(i, 0);
		temp.evaluate_team(i + 1, 0);
	}

	for (int i = 0; i < POP_SIZE; i++) {
		// copy back to pop
		the_pop[i]->clear();
		the_pop[i]->copy(temp.the_pop[i]);
		temp.the_pop[i]->clear();
		delete temp.the_pop[i];
	}

}

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
	evaluate_team(r1, 0);
	evaluate_team(r2, 0);
}

int pop::member_select(int c, int member, agent_type t) {
	int best = 0, current;
	float current_fit;
	float best_fit;
	best = rand() % POP_SIZE;
	if (t == scout) // scout
		best_fit = the_pop[best]->get_scout_fit(member);
	if (t == investigator) // investigator
		best_fit = the_pop[best]->get_invest_fit(member);
	for (int i = 1; i < TOURNAMENT_SIZE; i++) {
		current = rand() % POP_SIZE;
		if (t == scout) // scout
			current_fit = the_pop[current]->get_scout_fit(member);
		if (t == investigator) // scout
			current_fit = the_pop[current]->get_invest_fit(member);
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
	best = rand() % POP_SIZE;
	best_fit = the_pop[best]->get_avg_fit();
	for (int i = 1; i < TOURNAMENT_SIZE; i++) {
		current = rand() % POP_SIZE;
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
