#include <bitset>
#include <QStringList>
#include "environment.h"

using namespace std;

void environment::set_up(team *a) {
	agents = a;
	if(is_disabled(landmark)){
		landmarkx = -100;
		landmarky = -100;
	}
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
			continue;
		}

		// place the landmark inside the calling radius
		if(!is_disabled(landmark)){
			float x, y;
			do{
				x = (Random::Global() / ((float)Random::max / (2*(float)CALLING_RANGE)))
						+ (ZEBRAX - CALLING_RANGE);
				y = (Random::Global() / ((float)Random::max / (2*(float)CALLING_RANGE)))
						+ (ZEBRAY - CALLING_RANGE);
			} while (distance_sq(ZEBRAX - x, ZEBRAY - y) >= CALLING_RANGE_SQ);
			landmarkcoord[i][0] = x;
			landmarkcoord[i][1] = y;
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

	if(!is_disabled(landmark)){
		landmarkx = landmarkcoord[test][0];
		landmarky = landmarkcoord[test][1];
	}
}

void environment::evaluate(int timestep) {
	float tempx, tempy;
	float radius;
	for (int i = 0; i < NUM_HYENAS; i++) {
		tempx = agents->hyenas[i].getX();
		tempy = agents->hyenas[i].getY();
		radius = dist((tempx - ZEBRAX), (tempy - ZEBRAY));
		agents->hyenas[i].changeFit(1.0/(1.0 + radius)); // near zebra
		//		radius = sqrt(radius);

		agents->hyenas[i].inc_dist_to_zebra(radius);
		for (int j = 0; j < NUM_LIONS; j++) {
			radius = distance_sq(tempx - agents->lions[j].getX(),
								 tempy - agents->lions[j].getY());
            if (radius < LION_ATTACK_RADIUS_SQ) { // not too close to lions
                float penalty = LION_ATTACK_PENALTY *
                        (sqrt(radius) - LION_ATTACK_RADIUS);
                agents->hyenas[i].changeFit(penalty); // near lion
                agents->hyenas[i].inc_lion_attacks(penalty);
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
	int num_calling = 0;

	// set calling hyenas and if they call, set vectors toward zebra
	// and set landmark vector
	for(int i = 0; i < NUM_HYENAS; i++){
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();

		if(!is_disabled(landmark)){
			temp.magnitude = dist(agentx - landmarkx, agenty - landmarky);
			temp.direction = atan2(agentx - landmarkx, agenty - landmarky);
			agents->hyenas[i].set_landmark(temp);
		}

		temp.magnitude = distance_sq(agentx - ZEBRAX, agenty - ZEBRAY);
		if (temp.magnitude < CALLING_RANGE_SQ) { // min range to zebra
			temp.magnitude = sqrt(temp.magnitude); // now calculate sqrt
			temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
			if(CALLING_ENABLED){
				agents->hyenas[i].set_calling(true);
				num_calling++;
			} else {
				agents->hyenas[i].set_calling(false);
			}
		} else {
			temp.direction = 0;
			temp.magnitude = 0;
			agents->hyenas[i].set_calling(false);
		}
		agents->hyenas[i].set_zebra(temp);
	}

	// set nearest hyena vectors (and # calling hyenas)
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

	// find nearest lion, named hyena, and calling hyena
	for(int i = 0; i < NUM_HYENAS; i++){
		bool setNamed = false;
		agentx = agents->hyenas[i].getX(); //get hyena x,y
		agenty = agents->hyenas[i].getY();
		// find nearest calling hyena
		min_mag = FLT_MAX;
		for(int j = 0; j < NUM_HYENAS; j++){
			if(i != j && agents->hyenas[j].get_calling()){
				magnitude = distance_sq(agentx - agents->hyenas[j].getX(),
										agenty - agents->hyenas[j].getY());
				if(magnitude < min_mag){
					min_mag = magnitude;
					the_j = j;
				}
				// set named vector, if we are on the named hyena
				if(j == 0){
					temp.magnitude = sqrt(magnitude);
					temp.direction = atan2(agentx - agents->hyenas[j].getX(),
										   agenty - agents->hyenas[j].getY());
					agents->hyenas[i].set_named(temp);
					setNamed = true;
				}
			}
		}

		// zero out named if not yet set
		if(!setNamed){
			temp.magnitude = 0;
			temp.direction = 0;
			agents->hyenas[i].set_named(temp);
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

void environment::draw(DrawHelper* helper, int itera) {
	helper->iter.enqueue(itera);
	helper->landmarks.enqueue(QPointF(landmarkx, landmarky));

	QStringList list;
	list.reserve(NUM_LIONS + NUM_HYENAS + 3);

	list.append(QString("l %1 %2\n").arg(landmarkx).arg(landmarky));

	for (int i = 0; i < NUM_LIONS; i++) {
		QPointF p = QPointF(agents->lions[i].getX(),
							agents->lions[i].getY());
		list.append(QString("%1 %2").arg(p.x()).arg(p.y()));
		if(GUI)
			helper->lions[i].enqueue(p);
	}
	list.append("\n ");

	for (int i = 0; i < NUM_HYENAS; i++) {
		QPointF p = QPointF(agents->hyenas[i].getX(),
							agents->hyenas[i].getY());
		list.append(QString("%1 %2").arg(p.x(), 0, 'g', 4)
                    .arg(p.y(), 0, 'g', 4));
		if(GUI)
			helper->hyenas[i].enqueue(p);
	}
	list.append("\n");
	ofstream f;
	f.open(fname.c_str(), ios_base::app);
	f << list.join(" ").toStdString();
	f.close();
}
