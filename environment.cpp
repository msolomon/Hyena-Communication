#include <bitset>

#include "environment.h"

using namespace std;

void environment::set_up(team *a) {
	agents = a;
}

void environment::evaluate(void) {
	float tempx, tempy;
	float radius;
	for (int i = 0; i < NUM_HYENAS; i++) {
		tempx = agents->hyenas[i].getX();
		tempy = agents->hyenas[i].getY();
		radius = distance_sq(tempx - ZEBRAX, tempy - ZEBRAY); // distance squared
		agents->hyenas[i].changeFit(1.0 / (1.0 + radius)); // near zebra
		radius = sqrt(radius);
		 // bonus for getting close enough to 'eat'
		if(EAT_BONUS_ACTIVE && radius <= EAT_RADIUS){
			agents->hyenas[i].changeFit(EAT_BONUS);
		}

		agents->hyenas[i].inc_dist_to_zebra(radius);
		for (int j = 0; j < NUM_LIONS; j++) {
			radius = distance_sq(tempx - agents->lions[j].getX(),
							  tempy - agents->lions[j].getY());
			if (radius < LION_ATTACK_RADIUS_SQ) { // not too close to lions
					  agents->hyenas[i].changeFit(3*(sqrt(radius)-LION_ATTACK_RADIUS)); // near lion
				agents->hyenas[i].inc_lion_attacks();
			}
		}
	}

}

void environment::move(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		agents->hyenas[i].move();
	for (int i = 0; i < NUM_LIONS; i++)
		agents->lions[i].move();
}

float invert_direction(float d){
	if(d < 0) return d + PI;
	else return d - PI;
}

void environment::update_vectors(void){
	int the_j;
	float magnitude, min_mag;
	vect temp;
	float agentx, agenty;
	char num_calling = 0;

	// set calling hyenas and if they call, set vectors toward zebra
	for(int i = 0; i < NUM_HYENAS; i++){
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		temp.magnitude = distance_sq(agentx - ZEBRAX, agenty - ZEBRAY);
		if (temp.magnitude < CALLING_RANGE_SQ) { // min range to zebra
			temp.magnitude = sqrt(temp.magnitude); // now calculate sqrt
			temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
			agents->hyenas[i].set_calling(true);
			num_calling++;
		} else {
			temp.direction = 0;
			temp.magnitude = 0;
			agents->hyenas[i].set_calling(false);
		}
		agents->hyenas[i].set_zebra(temp);
	}

	// set nearest hyena vectors (and # calling scouts)
	bitset<NUM_HYENAS> already_set;
	for(int i = 0; i < NUM_HYENAS; i++){
		if(already_set[i]) continue;
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		min_mag = (4*(X+Y)) * (4*(X+Y));
		agents->hyenas[i].set_num_hyenas(num_calling);
		for(int j = i+1; j < NUM_HYENAS; j++){
			magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
									agenty - agents->hyenas[j].getY());
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		// set the closest hyena
		temp.magnitude = sqrt(min_mag);
		temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
							   agenty - agents->hyenas[the_j].getY());
		agents->hyenas[i].set_nearest_hyena(temp);
		agents->hyenas[i].set_mirrored(agents->hyenas[the_j].get_last_move());
		// now set the other direction (j closest to i)
		temp.direction = invert_direction(temp.direction);
		agents->hyenas[the_j].set_nearest_hyena(temp);
		agents->hyenas[the_j].set_mirrored(agents->hyenas[i].get_last_move());
		already_set[the_j] = true;
	}

	// find nearest calling scout
	for(int i = 0; i < NUM_HYENAS; i++){
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		min_mag = HEAR_CALLING_RADIUS_SQ;
		for(int j = 0; j < NUM_HYENAS; j++){
			if(agents->hyenas[j].get_calling() && i != j){
				magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
										agenty - agents->hyenas[j].getY());
				if(magnitude < min_mag){
					min_mag = magnitude;
					the_j = j;
				}
			}
		}
		if (min_mag == HEAR_CALLING_RADIUS_SQ) { // if nearest was too far away
			temp.magnitude = 0;
			temp.direction = 0;
		} else {
			temp.magnitude = sqrt(min_mag);
			temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
								   agenty - agents->hyenas[the_j].getY());
		}
		agents->hyenas[i].set_nearestcalling(temp);
	}

	// lions
	// get closest hyena and vice versa, count nearby lions
	for(int i = 0; i < NUM_LIONS; i++){
		int num_hyenas = 0;
		agentx = agents->lions[i].getX(); //get hyena x,y
		agenty = agents->lions[i].getY();
		min_mag = CALLING_RANGE_SQ; // TODO: maximum radius?
		for(int j = 0; j < NUM_HYENAS; j++){
			magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
									agenty - agents->hyenas[j].getY());
			if (magnitude < LION_HYENA_RADIUS_SQ)
				num_hyenas++;
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		if(min_mag < CALLING_RANGE_SQ){ // lion close enough to hyena
			temp.magnitude = sqrt(min_mag);
			temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
								   agenty - agents->hyenas[the_j].getY());
		}
		else {
			temp.magnitude = 0;
			temp.direction = 0;
		}
		// lion -> hyena
		agents->lions[i].set_nearest_hyena(temp);
		agents->lions[i].set_num_hyenas(num_hyenas);
		// hyena -> lion
		temp.direction = invert_direction(temp.direction);
		agents->hyenas[the_j].set_nearest_lion(temp);


		//find nearest lion. commented out: count lions close enough
		int num_lions = 1; // count self
//		min_mag = LION_LION_RADIUS_SQ;
		for (int j = 0; j < NUM_LIONS; j++) {
			if(i == j) continue;
			magnitude = distance_sq(agentx - agents->lions[j].getX(),
									agenty - agents->lions[j].getY());
			if (magnitude < LION_LION_RADIUS_SQ)
				num_lions++;
//			if (magnitude < min_mag) {
//				min_mag = magnitude;
//				the_j = j;
//			}
		}
//		temp.magnitude = sqrt(min_mag); // now take sqrt
//		temp.direction = direction;
		//agents->invests[i].set_nearest_invest(temp);
		agents->lions[i].set_num_lions(num_lions);

		// lion -> zebra
		temp.magnitude = sqrt(distance_sq(agentx - ZEBRAX, agenty - ZEBRAY));
		temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
		agents->lions[i].set_zebra(temp);
	}



}

//void environment::update_vectors(void) {
//	float magnitude, min_mag;
//	vect temp;
//	float direction, agentx, agenty;
//	//for each scout
//	for (int i = 0; i < NUM_HYENAS; i++) {
//		agentx = agents->scouts[i].getX(); //get scout x,y
//		agenty = agents->scouts[i].getY();
//		//find nearest scout
//		min_mag = 4 * (X + Y); // maximize minimum magnitude
//		agents->scouts[i].set_num_scouts(0);
//		for (int j = 0; j < NUM_HYENAS; j++) {
//			magnitude = distance(agentx - agents->scouts[j].getX(),
//								 agenty - agents->scouts[j].getY());
//			if (magnitude < min_mag && i != j) {
//				min_mag = magnitude;
//				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
//						- agents->scouts[j].getY()));
//				// TODO: what does this measure? number of scouts that could possibly be less?
//				agents->scouts[i].inc_num_scouts();
//			}
//		}
//		temp.magnitude = min_mag;
//		temp.direction = direction;
//		agents->scouts[i].set_nearest_scout(temp);

//		//find nearest calling scout
//		min_mag = X + Y; // maximize minimum magnitude
//		for (int j = 0; j < NUM_HYENAS; j++) {
//			magnitude = distance(agentx - agents->scouts[j].getX(),
//								 agenty - agents->scouts[j].getY());
//			if (agents->scouts[j].get_calling() == true && magnitude < min_mag
//					&& i != j && magnitude < X) {
//				min_mag = magnitude;
//				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
//						- agents->scouts[j].getY()));
//			}
//		}
//		if (min_mag == X + Y) { // if nearest was too far away
//			temp.magnitude = 0;
//			temp.direction = 0;
//		} else {
//			temp.magnitude = min_mag;
//			temp.direction = direction;
//		}
//		agents->scouts[i].set_nearestcalling(temp);

//		//find nearest investigator
//		min_mag = 5 * (X + Y); // some large value
//		for (int j = 0; j < NUM_LIONS; j++) {
//			magnitude = distance(agentx - agents->invests[j].getX(),
//								 agenty - agents->invests[j].getY());
//			if (magnitude < min_mag && magnitude < X / 4) { // TODO: magic value
//				min_mag = magnitude;
//				direction = atan2(agentx - agents->invests[j].getX(), (agenty
//						- agents->invests[j].getY()));
//			}
//		}
//		if (min_mag < X + Y) { // nearest investigator was close enough
//			temp.magnitude = min_mag;
//			temp.direction = direction;
//		} else { // else zero
//			temp.magnitude = 0;
//			temp.direction = 0;
//		}
//		agents->scouts[i].set_nearest_invest(temp);
//		//zebra
//		temp.magnitude = distance(agentx - ZEBRAX, agenty - ZEBRAY);
//		if (temp.magnitude < CALLING_RANGE) { // min range to zebra
//			temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
//			agents->scouts[i].set_calling(true);
//		} else {
//			temp.direction = 0;
//			temp.magnitude = 0;
//			agents->scouts[i].set_calling(false);
//		}
//		agents->scouts[i].set_zebra(temp);
//	}
//	// count investigators (lions)

//	//for each investigator (lion)
//	for (int i = 0; i < NUM_LIONS; i++) {
//		agentx = agents->invests[i].getX(); //get invest x,y
//		agenty = agents->invests[i].getY();

//		//find nearest scout, count number
//		int num_scouts = 0;
//		min_mag = X + Y; // maximize minimum magnitude
//		for (int j = 0; j < NUM_HYENAS; j++) {
//			magnitude = distance(agentx - agents->scouts[j].getX(),
//								 agenty - agents->scouts[j].getY());
//			if (magnitude < LION_HYENA_RADIUS)
//				num_scouts++;
//			if (magnitude < min_mag) {
//				min_mag = magnitude;
//				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
//						- agents->scouts[j].getY()));
//			}
//		}
//		temp.magnitude = min_mag;
//		temp.direction = direction;
//		agents->invests[i].set_nearest_scout(temp);
//		agents->invests[i].set_num_hyenas(num_scouts);
//		//find nearest investigator, count investigators/lions close enough
//		int num_invests = 0;
//		for (int j = 0; j < NUM_LIONS; j++) {
//			magnitude = distance_sq(agentx - agents->invests[j].getX(),
//								 agenty - agents->invests[j].getY());
//			if (magnitude < LION_LION_RADIUS_SQ)
//				num_invests++;
//			if (magnitude < min_mag && i != j) {
//				min_mag = magnitude;
//				direction = atan2(agentx - agents->invests[j].getX(), (agenty
//						- agents->invests[j].getY()));
//			}
//		}
//		temp.magnitude = sqrt(min_mag); // now take sqrt
//		temp.direction = direction;
//		//agents->invests[i].set_nearest_invest(temp);
//		agents->invests[i].set_num_lions(num_invests);

//		// zebra
//		temp.magnitude = distance(agentx - ZEBRAX, agenty - ZEBRAY);
//		temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
//		agents->invests[i].set_zebra(temp);
//	}
//}

environment::environment(void) {
}

void environment::draw(DrawHelper* helper, int itera) {
	helper->iter.enqueue(itera);

	for (int i = 0; i < NUM_LIONS; i++) {
		helper->lions[i].enqueue(
					QPointF(agents->lions[i].getX(),
							agents->lions[i].getY())
					);
	}

	for (int i = 0; i < NUM_HYENAS; i++) {
		helper->hyenas[i].enqueue(QPointF(agents->hyenas[i].getX(),
										  agents->hyenas[i].getY()));
	}
}
