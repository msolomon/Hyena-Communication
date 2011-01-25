#include "environment.h"


void environment::set_up(team *a) {
	agents = a;
}

void environment::evaluate(void) {
	float temp_fit;
	float tempx, tempy;
	float radius;
	int erase_flag = 0;
	for (int i = 0; i < NUM_HYENAS; i++) {
		tempx = agents->scouts[i].getX();
		tempy = agents->scouts[i].getY();
		radius = sqrt(pow((tempx - ZEBRAX), 2) + pow((tempy - ZEBRAY), 2));
		agents->scouts[i].changeFit(1.0 / (1.0 + radius)); // near zebra
		agents->scouts[i].inc_dist_to_zebra(radius);
		for (int j = 0; j < NUM_LIONS; j++) {
			radius = sqrt(pow((tempx - agents->invests[j].getX()), 2) + pow(
					(tempy - agents->invests[j].getY()), 2));
			if (radius < LION_ATTACK_RADIUS) { // not too close to lions/investigators
				//      agents->scouts[i].changeFit(3*(radius-LION_ATTACK_RADIUS)); // near lion
				agents->scouts[i].inc_lion_attacks();
			}
		}
	}

	// if(tempx < 0 || tempx > X || tempy < 0 || tempy > Y){

}

void environment::move(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
		agents->scouts[i].move();
	for (int i = 0; i < NUM_LIONS; i++)
		agents->invests[i].move();
}

void environment::update_vectors(void) {
	float magnitude, min_mag;
	vect temp;
	float direction, agentx, agenty;
	//for each scout
	for (int i = 0; i < NUM_HYENAS; i++) {
		agentx = agents->scouts[i].getX(); //get scout x,y
		agenty = agents->scouts[i].getY();
		//find nearest scout
		min_mag = 4 * (X + Y); // maximize minimum magnitude
		agents->scouts[i].set_num_scouts(0);
		for (int j = 0; j < NUM_HYENAS; j++) {
			magnitude = sqrt(pow((agentx - agents->scouts[j].getX()), 2) + pow(
					(agenty - agents->scouts[j].getY()), 2));
			if (magnitude < min_mag && i != j) {
				min_mag = magnitude;
				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
						- agents->scouts[j].getY()));
				agents->scouts[i].inc_num_scouts();
			}
		}
		temp.magnitude = min_mag;
		temp.direction = direction;
		agents->scouts[i].set_nearest_scout(temp);
		//find nearest calling scout
		min_mag = X + Y; // maximize minimum magnitude
		for (int j = 0; j < NUM_HYENAS; j++) {
			magnitude = sqrt(pow((agentx - agents->scouts[j].getX()), 2) + pow(
					(agenty - agents->scouts[j].getY()), 2));
			if (agents->scouts[j].get_calling() == true && magnitude < min_mag
					&& i != j && magnitude < X) {
				min_mag = magnitude;
				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
						- agents->scouts[j].getY()));
			}
		}
		if (min_mag == X + Y) { // if nearest was too far away
			temp.magnitude = 0;
			temp.direction = 0;
		} else {
			temp.magnitude = min_mag;
			temp.direction = direction;
		}
		agents->scouts[i].set_nearestcalling(temp);

		//find nearest investigator
		min_mag = 5 * (X + Y); // some large value
		for (int j = 0; j < NUM_LIONS; j++) {
			magnitude = sqrt(pow((agentx - agents->invests[j].getX()), 2)
					+ pow((agenty - agents->invests[j].getY()), 2));
			if (magnitude < min_mag && magnitude < X / 4) {
				min_mag = magnitude;
				direction = atan2(agentx - agents->invests[j].getX(), (agenty
						- agents->invests[j].getY()));
			}
		}
		if (min_mag < X + Y) { // nearest investigator was close enough
			temp.magnitude = min_mag;
			temp.direction = direction;
		} else { // else zero
			temp.magnitude = 0;
			temp.direction = 0;
		}
		agents->scouts[i].set_nearest_invest(temp);
		//zebra     
		temp.magnitude = sqrt(pow(double(agentx - ZEBRAX), 2.0) + pow(double(
				agenty - ZEBRAY), 2.0));
		if (temp.magnitude < X / 4) { // min range to zebra
			temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
			agents->scouts[i].set_calling(true);
		} else {
			temp.direction = 0;
			temp.magnitude = 0;
			agents->scouts[i].set_calling(false);
		}
		agents->scouts[i].set_zebra(temp);
	}
	// count investigators (lions)

	//for each investigator (lion)
	for (int i = 0; i < NUM_LIONS; i++) {
		agentx = agents->invests[i].getX(); //get invest x,y
		agenty = agents->invests[i].getY();

		//find nearest scout, count number
		int num_scouts = 0;
		min_mag = X + Y; // maximize minimum magnitude
		for (int j = 0; j < NUM_HYENAS; j++) {
			magnitude = sqrt(pow((agentx - agents->scouts[j].getX()), 2) + pow(
					(agenty - agents->scouts[j].getY()), 2));
			if (magnitude < LION_HYENA_RADIUS)
				num_scouts++;
			if (magnitude < min_mag) {
				min_mag = magnitude;
				direction = atan2(agentx - agents->scouts[j].getX(), (agenty
						- agents->scouts[j].getY()));
			}
		}
		temp.magnitude = min_mag;
		temp.direction = direction;
		agents->invests[i].set_nearest_scout(temp);
		agents->invests[i].set_num_hyenas(num_scouts);
		//find nearest investigator, count investigators/lions close enough
		int num_invests = 0;
		for (int j = 0; j < NUM_LIONS; j++) {
			magnitude = sqrt(pow((agentx - agents->invests[j].getX()), 2)
					+ pow((agenty - agents->invests[j].getY()), 2));
			if (magnitude < LION_LION_RADIUS)
				num_invests++;
			if (magnitude < min_mag && i != j) {
				min_mag = magnitude;
				direction = atan2(agentx - agents->invests[j].getX(), (agenty
						- agents->invests[j].getY()));
			}
		}
		temp.magnitude = min_mag;
		temp.direction = direction;
		agents->invests[i].set_nearest_invest(temp);
		agents->invests[i].set_num_lions(num_invests);

		// zebra
		temp.magnitude = sqrt(pow((agentx - ZEBRAX), 2) + pow(
				(agenty - ZEBRAY), 2));
		temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
		agents->invests[i].set_zebra(temp);
	}
}

environment::environment(void) {
}

void environment::draw(Helper* helper) {
	if (helper) {
	} else
		return;
	//TODO: include moving/multiple zebras
	helper->zebras[0].enqueue(QPoint(ZEBRAX, ZEBRAY));

	for (int i = 0; i < NUM_LIONS; i++) {
		helper->lions[i].enqueue(
								QPoint(agents->invests[i].getX(),
										agents->invests[i].getY())
								);
	}

	for (int i = 0; i < NUM_HYENAS; i++) {
		helper->hyenas[i].enqueue(QPoint(agents->scouts[i].getX(),
										agents->scouts[i].getY()));
	}
}
