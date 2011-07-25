#include "team.h"

team::team(){
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
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	avg_penalty = 0;
	avg_reward = 0;
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
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i].grow();
		hyenas[i].set_type(hyena);
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		lions[i].set_type(lion);
	}
}

void team::copy(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i] = (p2->hyenas[i]);
		hyena_fits[i] = p2->hyena_fits[i];
	}
	avg_fit = p2->avg_fit;
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

void team::calc_size(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		hyenas[i].calc_size();
}

void team::mutate(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		hyenas[i].mutate();
}

void team::mutate(int member) {
	hyenas[member].mutate();
}

float team::write_avg_fit_final(std::ofstream &f, int trial, int test) {
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_penalty = 0;
	avg_reward = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = hyenas[i].get_fitness();
		avg_fit += hyena_fits[i];
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
	f << trial << " "
	  << test << " "
	  << avg_dist_to_zebra << " "
	  << avg_lion_attacks << " "
	  << avg_penalty << " "
	  << avg_reward << " "
	  << avg_fit << " "
	  << avg_hits << " "
	  << avg_imp << " ";
	for(int i = 0; i < NUM_OPS; i++)
		f << importance[i] << " ";
	for(int i = 0; i < NUM_HYENAS - 1; i++)
		f << hyena_fits[i] << " ";
	f << hyena_fits[NUM_HYENAS - 1] << "\n";

	return avg_fit;
}

float team::calc_avg_fit(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
    avg_penalty = 0;
	avg_reward = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = hyenas[i].get_fitness() / NUM_TESTS;
		avg_fit += hyena_fits[i];
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
	return avg_fit;
}
