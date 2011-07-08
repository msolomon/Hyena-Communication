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

void team::reset_calling(){
	for(int i = 0; i < NUM_HYENAS; i++){
		hyenas[i].set_calling(false);
	}
}

void team::reset_fitness(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
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

float team::calc_avg_fit(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
    avg_penalty = 0;
	avg_dist_to_zebra = 0;
	avg_hits = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = hyenas[i].get_fitness() / NUM_TESTS;
		avg_fit += hyena_fits[i];
		avg_dist_to_zebra += hyenas[i].get_avg_dist_to_zebra();
		avg_lion_attacks += hyenas[i].get_lion_attacks();
        avg_penalty += hyenas[i].get_penalty();
		avg_hits += hyenas[i].get_hits();
	}
	for(int i = 0; i < NUM_TERMS+NUM_NON_TERMS; i++){
		uses[i] = 0;
		importance[i] = 0;
	}
//	// sum up usages
//	for(int i = 0; i < NUM_HYENAS; i++){
//		int *h_uses = hyenas[i].get_uses();
//		for(int j = 0; j < NUM_TERMS+NUM_NON_TERMS; j++){
//			uses[j] += h_uses[j];
//		}
//	}
	// sum up importance
	for(int i = 0; i < NUM_HYENAS; i++){
		double *h_imp = hyenas[i].get_importance();
		for(int j = 0; j < NUM_TERMS+NUM_NON_TERMS; j++){
			importance[j] += h_imp[j];
		}
	}
//	// divide out each usage
//	for(int i = 0; i < NUM_TERMS+NUM_NON_TERMS; i++){
//		uses[i] /= NUM_HYENAS * NUM_TESTS * TIME_STEPS;
//	}
	// divide out each importance
	for(int i = 0; i < NUM_TERMS+NUM_NON_TERMS; i++){
		importance[i] /= NUM_HYENAS * NUM_TESTS * TIME_STEPS;
	}
	avg_hits /= NUM_HYENAS * NUM_TESTS;
	avg_lion_attacks /= NUM_TESTS;
    avg_penalty /= NUM_TESTS;
	avg_dist_to_zebra /= NUM_HYENAS * NUM_TESTS;
	return avg_fit;
}
