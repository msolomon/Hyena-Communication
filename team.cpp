#include "team.h"

team::team(){
	reset_fitness();
	for (int i = 0; i < NUM_HYENAS; i++) {
//		hyenas[i].grow();
		hyenas[i].set_type(hyena);
		hyenas[i].tree = NULL;
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		lions[i].set_type(lion);
	}
}

void team::reset_team(void) {

	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i].reset();
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		lions[i].reset();
	}
}

void team::reset_inputs(){
	for(int i = 0; i < NUM_HYENAS; i++){
		hyenas[i].reset_inputs();
	}
}

void team::reset_fitness(void) {
	team_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	avg_penalty = 0;
	avg_reward = 0;
	avg_size = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = 0;
		hyenas[i].reset_fitness();
	}
}

void team::clear(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		hyenas[i].clear();
}

void team::generate(void) {
	reset_fitness();
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i].grow();
	}
}

void team::copy(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i] = (p2->hyenas[i]);
		hyena_fits[i] = p2->hyena_fits[i];
	}
	team_fit = p2->team_fit;
}

void team::copy(team *p2, int i) {
	hyenas[i] = (p2->hyenas[i]);
	hyena_fits[i] = p2->hyena_fits[i];
}

void team::xOver(team *p2, int i) {
	hyenas[i].xOver(&(p2->hyenas[i]));
}

void team::xOver(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++)
		hyenas[i].xOver(&(p2->hyenas[i]));
}

int team::get_size(void) {
    int total = 0;
	for (int i = 0; i < NUM_HYENAS; i++)
        total += hyenas[i].get_size();
    return total;
}

void team::apply_parsimony(){
    avg_parsimony = 0;
    for(int i = 0; i < NUM_HYENAS; i++){
        float penalty = hyenas[i].get_size() * -PARSIMONY_COEFF;
        for(int j = 0; j < NUM_TESTS; j++) // must do for each test
            hyenas[i].changeFit(penalty, j);
        avg_parsimony += penalty;
    }
    avg_parsimony /= NUM_HYENAS;
}

void team::mutate(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		hyenas[i].mutate();
}

void team::mutate(int member) {
	hyenas[member].mutate();
}

float team::write_team_fit_final(std::ofstream &f, int trial, int test, int testnum, int size) {
	team_fit = 0;
	avg_lion_attacks = 0;
	avg_penalty = 0;
	avg_reward = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = hyenas[i].get_fitness(testnum);
		team_fit += hyena_fits[i];
		avg_dist_to_zebra += hyenas[i].get_avg_dist_to_zebra();
		avg_lion_attacks += hyenas[i].get_lion_attacks();
		avg_penalty += hyenas[i].get_penalty();
		avg_hits += hyenas[i].get_hits();
		avg_reward += hyenas[i].get_reward();
	}

	for(int i = 0; i < NUM_OPS; i++){
		uses[i] = 0;
		importance[i] = 0;
	}

	float total_leadership = 0;
	for(int i = 0; i < NUM_HYENAS; i++){
		total_leadership += float(leadership[i]);
	}
	int leader_idx, leader_score_int, leader2_idx, leader2_score_int;
	get_leaders(leader_idx, leader_score_int, leader2_idx, leader2_score_int);
	float leader_score, leader2_score;
	leader_score = leader_score_int / (total_leadership);
	leader2_score = leader2_score_int / (total_leadership);

	// sum up importance
	for(int i = 0; i < NUM_HYENAS; i++){
		double *h_imp = hyenas[i].get_importance();
		for(int j = 0; j < NUM_OPS; j++){
			importance[j] += h_imp[j];
		}
	}

	// divide out each importance
	float avg_imp = 0;
	for(int i = 0; i < NUM_OPS; i++){
		importance[i] /= NUM_HYENAS * TIME_STEPS;
		avg_imp += importance[i];
	}
	avg_imp /= NUM_OPS;

	avg_hits /= NUM_HYENAS;
	avg_dist_to_zebra /= NUM_HYENAS;

	//// Now write it all
	f << trial + 1 << " "
	  << test + 1 << " "
	  << avg_dist_to_zebra << " "
	  << avg_lion_attacks << " "
	  << avg_penalty << " "
	  << (size * -PARSIMONY_COEFF) << " " // parsimony
	  << avg_reward << " "
	  << team_fit << " "
	  << size << " "
	  << avg_hits << " "
	  << avg_imp << " "
	  << leader_idx << " "
	  << leader_score << " "
	  << leader2_idx << " "
	  << leader2_score << " ";
	for(int i = 0; i < NUM_OPS; i++)
		f << importance[i] << " ";
	for(int i = 0; i < NUM_HYENAS - 1; i++)
		f << hyena_fits[i] << " ";
	f << hyena_fits[NUM_HYENAS - 1] << "\n";

	return team_fit;
}

void team::get_leaders(int &leader_idx, int &leader_score,
							  int &leader2_idx, int &leader2_score){
	leader_idx = 0;
	leader_score = leadership[0];
	for(int i = 1; i < NUM_HYENAS; i++){
		if(leadership[i] > leader_score){
			leader_score = leadership[i];
			leader_idx = i;
		}
	}
	leader2_idx = -1;
	leader2_score = -100; // minimum score is actually 0
	for(int i = 0; i < NUM_HYENAS; i++){
		if(i != leader_idx && leadership[i] > leader2_score){
			leader2_score = leadership[i];
			leader2_idx = i;
		}
	}
}

float team::recalc_team_avg_fit(){
    team_fit = 0;
    for(int i = 0; i < NUM_HYENAS; i++){
        for(int j = 0; j < NUM_TESTS; j++)
            team_fit += hyenas[i].get_fitness(j) / NUM_TESTS;
    }
	return team_fit;
}

float team::calc_team_fit(void) {
	float run_fits[NUM_TESTS] = {0};
	avg_lion_attacks = 0;
    avg_penalty = 0;
	avg_reward = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		for(int j = 0; j < NUM_TESTS; j++)
			run_fits[j] += hyenas[i].get_fitness(j);
		hyena_fits[i] = hyenas[i].get_fitness(); // destroys order of fitnesses
		avg_dist_to_zebra += hyenas[i].get_avg_dist_to_zebra();
		avg_lion_attacks += hyenas[i].get_lion_attacks();
        avg_penalty += hyenas[i].get_penalty();
		avg_hits += hyenas[i].get_hits();
		avg_reward += hyenas[i].get_reward();
	}
	team_fit = select_from_numtests(run_fits);

	for(int i = 0; i < NUM_OPS; i++){
		uses[i] = 0;
		importance[i] = 0;
	}

	// sum up importance
	for(int i = 0; i < NUM_HYENAS; i++){
		double *h_imp = hyenas[i].get_importance();
		for(int j = 0; j < NUM_OPS; j++){
			importance[j] += h_imp[j];
		}
	}

	// divide out each importance
	for(int i = 0; i < NUM_OPS; i++){
		importance[i] /= NUM_HYENAS * NUM_TESTS * TIME_STEPS;
	}
	avg_hits /= NUM_HYENAS * NUM_TESTS;
	avg_lion_attacks /= NUM_TESTS;
    avg_penalty /= NUM_TESTS;
	avg_dist_to_zebra /= NUM_HYENAS * NUM_TESTS;
	avg_reward /= NUM_TESTS;
	return team_fit;
}

QStringList team::serialize(){
	QStringList output;
	for(int i = 0; i < NUM_HYENAS; i++){
//		output += QString("%1 ").arg(get_hyena_fit(i));
		output += hyenas[i].serialize();
		output += "\n";
	}
	return output;
}

void team::deserialize(QStringList input){
	/* input should be a list of lines, one per hyena */
	if(input.length() != NUM_HYENAS){
		std::ofstream error;
		error.open("error.txt");
		error << "error in team::deserialize: given " << input.length() <<
				 " hyenas but was expecting " << NUM_HYENAS << std::endl;
		error.close();
	}

	// deserialize each hyena in the team
	for(int i = 0; i < NUM_HYENAS; i++){
		hyenas[i].deserialize(input.takeFirst().split(' ',
													  QString::SkipEmptyParts));
	}
}

void team::load_team(QString filename){
	QFile f(filename);
	QStringList list;

	if(f.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&f);
		QString line = in.readLine();
		while(!line.isNull()){
			list.append(line);
			line = in.readLine();
		}
		f.close();
	} else {
		std::ofstream error;
		error.open("error.txt");
		error << "error in load_team" << std::endl;
		error.close();
		return;
	}

	QString names = list.takeFirst();
	if(names.split(' ', QString::SkipEmptyParts).length() !=
			(sizeof(ops_names) / sizeof(ops))){
		std::ofstream error;
		error.open("error.txt");
		error << "error in load_team: wrong number of operations" << std::endl;
		error.close();
		return;
	} else {
		deserialize(list);
	}
}
