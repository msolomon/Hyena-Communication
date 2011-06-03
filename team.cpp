#include "team.h"

team::team(){
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i].grow();
		hyenas[i].set_type(hyena);
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

void team::reset_fitness(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
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
		hyenas[i].clear();
		hyenas[i].grow();
		hyenas[i].set_type(hyena);
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		lions[i].set_type(lion);
	}
}

void team::copy(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyenas[i].clear();
		hyenas[i] = (p2->hyenas[i]);
		hyenas[i].set_type(hyena);
		hyena_fits[i] = p2->hyena_fits[i];
	}
//	for (int i = 0; i < NUM_LIONS; i++) {
//		lions[i].clear();
////		invest_fits[i] = p2->invest_fits[i];
//		lions[i] = (p2->lions[i]);
//		lions[i].set_type(lion);
//	}
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
	avg_dist_to_zebra = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		hyena_fits[i] = hyenas[i].get_fitness();
		avg_fit += hyena_fits[i];
		avg_dist_to_zebra += hyenas[i].get_avg_dist_to_zebra();
		avg_lion_attacks += hyenas[i].get_lion_attacks();
	}
	avg_lion_attacks /= NUM_HYENAS;
	avg_dist_to_zebra /= NUM_HYENAS;
	return avg_fit;
}
