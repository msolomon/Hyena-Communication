#include <bitset>
#include <QStringList>
#include "environment.h"

using namespace std;

void environment::set_up(team *a) {
	agents = a;
}

void environment::generate_positions(){
	bool one_inside = false;
	for(int i = 0; i < NUM_TESTS; i++){
		for(int j = 0; j < NUM_LIONS; j++){
			// place lions within 1 unit of zebra
			lioncoord[i][j][0] = ZEBRAX + Random::Global.FloatW();
			lioncoord[i][j][1] = ZEBRAY + Random::Global.FloatW();
		}

		for(int j = 0; j < NUM_HYENAS; j++){
			float x, y;
			x = ZEBRAX;
			y = ZEBRAY;
			if(START_OUTSIDE_ZEBRA){
				while(distance_sq(ZEBRAX - x, ZEBRAY - y) < CALLING_RANGE_SQ){
					x = Random::Global() / ((float)Random::max / (float)X);
					y = Random::Global() / ((float)Random::max / (float)Y);
				}
			} else{ // start outside lion radius instead
				float distnce = 0;
				while (distnce <
					   ((LION_ATTACK_RADIUS + 1) * (LION_ATTACK_RADIUS + 1))){
					x = Random::Global() / ((float)Random::max / (float)X);
					y = Random::Global() / ((float)Random::max / (float)Y);
					distnce = distance_sq(ZEBRAX - x, ZEBRAY - y);
				}
				if(distnce < CALLING_RANGE_SQ){
					one_inside = true;
				}
			}

			hyenacoord[i][j][0] = x;
			hyenacoord[i][j][1] = y;
		}
		if(START_ONE_INSIDE && one_inside == false){
			i--; // redo this test's positions until one starts inside
		}
	}
}

void environment::place_agents(int test){
	for(int i = 0; i < NUM_LIONS; i++){
		agents->lions[i].set_position(lioncoord[test][i][0],
									  lioncoord[test][i][1]);
	}
	for(int i = 0; i < NUM_HYENAS; i++){
		agents->hyenas[i].set_position(hyenacoord[test][i][0],
									   hyenacoord[test][i][1]);
	}
}

void environment::evaluate(void) {
	float tempx, tempy;
	float radius;
	for (int i = 0; i < NUM_HYENAS; i++) {
		tempx = agents->hyenas[i].getX();
		tempy = agents->hyenas[i].getY();
		radius = dist((tempx - ZEBRAX), (tempy - ZEBRAY));
		agents->hyenas[i].changeFit(1.0 / (1.0 + radius)); // near zebra
		//		radius = sqrt(radius);
		// bonus for getting close enough to 'eat'
		if(EAT_BONUS_ACTIVE && radius <= EAT_RADIUS){
			agents->hyenas[i].changeFit(EAT_BONUS);
		}

		agents->hyenas[i].reset_attack_input();

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
	for(int i = 0; i < NUM_HYENAS; i++){
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		agents->hyenas[i].set_num_hyenas(num_calling);
		min_mag = HYENA_HYENA_RADIUS_SQ;
		for(int j = 0; j < NUM_HYENAS; j++){
			if(i == j) continue;
			magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
									agenty - agents->hyenas[j].getY());
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		// if out of range, zero vector
		if(min_mag == HYENA_HYENA_RADIUS_SQ){
			temp.direction = 0;
			temp.magnitude = 0;
			agents->hyenas[i].set_nearest_hyena(temp);
			agents->hyenas[i].set_mirrored(temp);
		} else { // set to nearest hyena
			temp.magnitude = sqrt(min_mag);
			temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
								   agenty - agents->hyenas[the_j].getY());
			// set the closest hyena and mirror input
			agents->hyenas[i].set_nearest_hyena(temp);
			agents->hyenas[i].set_mirrored(agents->hyenas[the_j].get_last_move());
		}
	}

	// find nearest lion, leader, and calling scout
	for(int i = 0; i < NUM_HYENAS; i++){
		bool setLeader = false;
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		// find nearest calling scout
		min_mag = FLT_MAX;
		for(int j = 0; j < NUM_HYENAS; j++){
			if(agents->hyenas[j].get_calling() && i != j){
				magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
										agenty - agents->hyenas[j].getY());
				if(magnitude < min_mag){
					min_mag = magnitude;
					the_j = j;
				}
				// set leader vector, if this is the leader
				if(j == 0){
					temp.magnitude = sqrt(magnitude);
					temp.direction = atan2(agentx - agents->hyenas[j].getX(),
										   agenty - agents->hyenas[j].getY());
					agents->hyenas[i].set_leader(temp);
					setLeader = true;
				}
			}
		}

		// zero out leader if not yet set
		if(!setLeader){
			temp.magnitude = 0;
			temp.direction = 0;
			agents->hyenas[i].set_leader(temp);
		}

		if(min_mag == FLT_MAX){ // no hyenas calling
			temp.magnitude = 0;
			temp.direction = 0;
		} else {
			temp.magnitude = sqrt(min_mag);
			temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
								   agenty - agents->hyenas[the_j].getY());
		}
		agents->hyenas[i].set_nearestcalling(temp);

		// find nearest lion
		min_mag = LION_HYENA_RADIUS_SQ;
		for(int j = 0; j < NUM_LIONS; j++){
			magnitude = distance_sq(agentx - agents->lions[j].getX(),
									agenty - agents->lions[j].getY());
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		if(min_mag == LION_HYENA_RADIUS_SQ){
			temp.direction = 0;
			temp.magnitude = 0;
		} else{
			temp.magnitude = sqrt(magnitude);
			temp.direction = atan2(agentx - agents->lions[the_j].getX(),
								   agenty - agents->lions[the_j].getY());
		}
		agents->hyenas[i].set_nearest_lion(temp);
	}

	// lions
	// get closest hyena and vice versa, count nearby lions
	for(int i = 0; i < NUM_LIONS; i++){
		int n_hyenas = 0;
		agentx = agents->lions[i].getX(); //get lion x,y
		agenty = agents->lions[i].getY();
		min_mag = LION_HYENA_RADIUS_SQ;
		for(int j = 0; j < NUM_HYENAS; j++){
			magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
									agenty - agents->hyenas[j].getY());
			if (magnitude < LION_HYENA_RADIUS_SQ)
				n_hyenas++;
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		if(min_mag < LION_HYENA_RADIUS_SQ){ // lion close enough to hyena
			temp.magnitude = sqrt(min_mag);
			temp.direction = atan2(agentx - agents->hyenas[the_j].getX(),
								   agenty - agents->hyenas[the_j].getY());
		}
		else {
			temp.direction = 0;
			temp.magnitude = 0;
		}
		// lion -> hyena
		agents->lions[i].set_nearest_hyena(temp);
		agents->lions[i].set_num_hyenas(n_hyenas);

		//find nearest lion.
		int num_lions = 1; // count self
		for (int j = 0; j < NUM_LIONS; j++) {
			if(i == j) continue;
			magnitude = distance_sq(agentx - agents->lions[j].getX(),
									agenty - agents->lions[j].getY());
			if (magnitude < LION_LION_RADIUS_SQ)
				num_lions++;
		}
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

void environment::draw(DrawHelper* helper, int itera) {
	helper->iter.enqueue(itera);
	QStringList list;
	list.reserve(NUM_LIONS + NUM_HYENAS + 3);

	for (int i = 0; i < NUM_LIONS; i++) {
		QPointF p = QPointF(agents->lions[i].getX(),
							agents->lions[i].getY());
		list.append(QString("%1 %2").arg(p.x()).arg(p.y()));
		helper->lions[i].enqueue(p);
	}
	list.append("\n");

	for (int i = 0; i < NUM_HYENAS; i++) {
		QPointF p = QPointF(agents->hyenas[i].getX(),
							agents->hyenas[i].getY());
        list.append(QString("%1 %2").arg(p.x(), 0, 'g', 4)
                    .arg(p.y(), 0, 'g', 4));
		helper->hyenas[i].enqueue(p);
	}
	list.append("\n");
	ofstream f;
	f.open(fname.c_str(), ios_base::app);
	f << list.join(" ").toStdString();
	f.close();
}
