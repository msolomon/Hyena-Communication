#include "team.h"

void team::reset_team(void) {

	for (int i = 0; i < NUM_HYENAS; i++) {
		scouts[i].reset();
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		invests[i].reset();
	}
}

void team::reset_fitness(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		scout_fits[i] = 0;
		scouts[i].reset_fitness();
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		invest_fits[i] = 0;
		invests[i].reset_fitness();
	}
}

void team::clear(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		scouts[i].clear();
	for (int i = 0; i < NUM_LIONS; i++)
		invests[i].clear();
}

void team::generate(void) {
	for (int i = 0; i < NUM_HYENAS; i++) {
		scouts[i].grow();
		scouts[i].set_type(scout);
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		invests[i].grow();
		invests[i].set_type(investigator);
	}
}

void team::copy(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++) {
		scouts[i].clear();
//		delete &scouts[i];
		scouts[i] = (p2->scouts[i]);
		scouts[i].set_type(scout);
		scout_fits[i] = p2->scout_fits[i];
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		invests[i].clear();
//		delete &invests[i];
		invest_fits[i] = p2->invest_fits[i];
		invests[i] = (p2->invests[i]);
		invests[i].set_type(investigator);
	}
	avg_fit = p2->avg_fit;
}

void team::copy(team *p2, int i, agent_type t) {
	if (t == scout) {
		scouts[i] = (p2->scouts[i]);
		scout_fits[i] = p2->scout_fits[i];
	}
	if (t == investigator) {
		invests[i] = (p2->invests[i]);
		invest_fits[i] = p2->invest_fits[i];
	}
}

void team::xOver(team *p2, int i, agent_type t) {
	if (t == scout)
		scouts[i].xOver(&(p2->scouts[i]));
	if (t == investigator)
		invests[i].xOver(&(p2->invests[i]));
}

void team::xOver(team *p2) {
	for (int i = 0; i < NUM_HYENAS; i++)
		scouts[i].xOver(&(p2->scouts[i]));
	for (int i = 0; i < NUM_LIONS; i++)
		invests[i].xOver(&(p2->invests[i]));
}

void team::calc_size(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		scouts[i].calc_size();
	for (int i = 0; i < NUM_LIONS; i++)
		invests[i].calc_size();
}

void team::mutate(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		scouts[i].mutate();
	for (int i = 0; i < NUM_LIONS; i++)
		invests[i].mutate();
}

void team::mutate(int member, agent_type t) {
	if (t == scout)
		scouts[member].mutate();
	if (t == investigator)
		invests[member].mutate();
}

float team::calc_avg_fit(void) {
	avg_fit = 0;
	avg_lion_attacks = 0;
	avg_dist_to_zebra = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		scout_fits[i] = scouts[i].get_fitness();
		avg_fit += scout_fits[i];
		avg_dist_to_zebra += scouts[i].get_avg_dist_to_zebra();
		avg_lion_attacks += scouts[i].get_lion_attacks();
	}
	for (int i = 0; i < NUM_LIONS; i++) {
		invest_fits[i] = invests[i].get_fitness();
		avg_fit += invest_fits[i];
		;
	}
	avg_lion_attacks /= NUM_HYENAS;
	avg_dist_to_zebra /= NUM_HYENAS;
	return avg_fit;
}
