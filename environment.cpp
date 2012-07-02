#include "environment.h"

using namespace std;

environment::environment(){
	fname = NULL;
    deployed_lions = 0;
}

void environment::set_up(team *a) {
	agents = a;
	agents->leadership = (int*) leadership;
	if(is_disabled(landmark)){
		landmarkx = -100;
		landmarky = -100;
	}
	for(int i = 0; i < NUM_HYENAS; i++){
		leadership[i] = 0;
	}
}

void environment::generate_positions(){
	for(int i = 0; i < NUM_TESTS; i++){
		double dir, mag;
        for(int j = 0; j < deployed_lions; j++){
			// place lions within 1 unit of zebra
            dir = Random::Global.FixedW() * PI;
			mag = Random::Global.Fixed();
			lioncoord[i][j][0] = ZEBRAX + sin(dir) * mag;
			lioncoord[i][j][1] = ZEBRAY + cos(dir) * mag;
		}

		if(RADIUS_START > 0){ // place within given distance of zebra
			// pick a random non-named hyena
			int inside = Random::Global.IntegerC(1, NUM_HYENAS - 1);
            dir = Random::Global.FixedW() * PI;
			mag = Random::Global.Fixed() * CALLING_RANGE;
			hyenacoord[i][inside][0] = ZEBRAX + sin(dir) * mag;
			hyenacoord[i][inside][1] = ZEBRAY + cos(dir) * mag;

			// place the rest outside CALLING_RANGE and inside RADIUS_START
			for(int j = 0; j < NUM_HYENAS; j++){
				if(j == inside) continue;
                dir = Random::Global.FixedW() * PI;
				mag = Random::Global.Fixed() *
						(RADIUS_START - CALLING_RANGE) + CALLING_RANGE;
				hyenacoord[i][j][0] = ZEBRAX + sin(dir) * mag;
				hyenacoord[i][j][1] = ZEBRAY + cos(dir) * mag;
			}
		} else{ // randomize x,y seperately (non-uniform w.r.t. radius)
			bool one_inside = false;
			for(int j = 0; j < NUM_HYENAS; j++){
				double x, y;
				x = ZEBRAX;
				y = ZEBRAY;
				if(START_OUTSIDE_ZEBRA){
					while(distance_sq(ZEBRAX - x, ZEBRAY - y) < CALLING_RANGE_SQ){
						x = Random::Global.Fixed() * X;
						y = Random::Global.Fixed() * Y;
					}
				} else{ // start outside lion radius instead
					double distnce = 0;
					while (distnce <
						   ((LION_ATTACK_RADIUS + 1) * (LION_ATTACK_RADIUS + 1))){
						x = Random::Global.Fixed() * X;
						y = Random::Global.Fixed() * Y;
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
		}

		// place the landmark inside the calling radius
		if(!is_disabled(landmark)){
            dir = Random::Global.FixedW()* PI;
			mag = Random::Global.Fixed() * CALLING_RANGE;
			landmarkcoord[i][0] = ZEBRAX + sin(dir) * mag;
			landmarkcoord[i][1] = ZEBRAY + cos(dir) * mag;
		}
	}
}

void environment::place_agents(int test){
    for(int i = 0; i < deployed_lions; i++){
		agents->lions[i].set_position(lioncoord[test][i][0],
									  lioncoord[test][i][1]);
	}
	for(int i = 0; i < NUM_HYENAS; i++){
        agents->hyenas[i]->set_position(hyenacoord[test][i][0],
                                        hyenacoord[test][i][1]);
		unmoved.insert(i); // reset set of unmoved hyenas
		uncalled.insert(i); // reset set of hyenas that haven't called
	}
	just_moved.clear(); // these should both also be cleared after each timestep
	just_called.clear();

	if(!is_disabled(landmark)){
		landmarkx = landmarkcoord[test][0];
		landmarky = landmarkcoord[test][1];
	}
}

void environment::evaluate(int test) {
	double tempx, tempy;
	double radius;
	for (int i = 0; i < NUM_HYENAS; i++) {
        tempx = agents->hyenas[i]->getX();
        tempy = agents->hyenas[i]->getY();
		radius = dist((tempx - ZEBRAX), (tempy - ZEBRAY));
        agents->hyenas[i]->changeFit(1.0/(1.0 + radius), test); // near zebra
		//		radius = sqrt(radius);

        agents->hyenas[i]->inc_dist_to_zebra(radius);
        for (int j = 0; j < deployed_lions; j++) {
			radius = distance_sq(tempx - agents->lions[j].getX(),
								 tempy - agents->lions[j].getY());
			if (radius < LION_ATTACK_RADIUS_SQ) { // too close to lions
                double penalty = LION_ATTACK_PENALTY *
                        (sqrt(radius) - LION_ATTACK_RADIUS);
                agents->hyenas[i]->changeFit(penalty, test); // near lion
                agents->hyenas[i]->inc_lion_attacks(penalty);
			}
		}
	}

}

void environment::move(void) {
	for (int i = 0; i < NUM_HYENAS; i++)
        agents->hyenas[i]->move();
    for (int i = 0; i < deployed_lions; i++)
		agents->lions[i].move();
}

double invert_direction(double d){
    if(d < 0) return d + PI;
	else return d - PI;
}

void environment::clear_last_moves(){
	foreach(int mover, unmoved){
        if(agents->hyenas[mover]->get_moved())
			unmoved.remove(mover);
	}
	just_moved.clear();
    just_called.clear();
}

void environment::deploy_lions(int num_lions){
    deployed_lions = num_lions;
}

void environment::update_leadership(){
	foreach(int mover, unmoved){
        if(agents->hyenas[mover]->get_moved()){
			unmoved.remove(mover); // this does remove from original unmoved set
			just_moved.insert(mover);
		}
	}
	foreach(int caller, just_called){
		leadership[caller] += just_moved.size();
	}
	// clear set of those that just moved
	just_moved.clear();
	// clear set of those that just called
	just_called.clear();
}

void environment::update_vectors(void){
	int the_j = 0;
	int calling_j = 0;
	double magnitude, min_mag, nearest_calling;
	vect temp;
	double agentx, agenty;
	int num_calling = 0;

	// set calling hyenas and if they call, set vectors toward zebra
	// and set landmark vector
	for(int i = 0; i < NUM_HYENAS; i++){
        agentx = agents->hyenas[i]->getX(); //get hyena x,y
        agenty = agents->hyenas[i]->getY();

		// set the landmark, if enabled
		if(!is_disabled(landmark)){
			temp.magnitude = dist(agentx - landmarkx, agenty - landmarky);
			temp.direction = atan2(agentx - landmarkx, agenty - landmarky);
            agents->hyenas[i]->set_landmark(temp);
		}

        // set first callers, only if calling isn't a fixed behavior
        if(LEARN_CALLING){
            if(agents->hyenas[i]->get_calling()){ // calling
                num_calling++;
                if(uncalled.contains(i)){ // first time calling
                    just_called.insert(i);
                    uncalled.remove(i);
                }
            }
        }

        temp.magnitude = distance_sq(agentx - ZEBRAX, agenty - ZEBRAY);
        if (temp.magnitude < CALLING_RANGE_SQ) { // min range to zebra
            temp.magnitude = sqrt(temp.magnitude); // now calculate sqrt
            temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
            if(CALLING_ENABLED && !LEARN_CALLING){ // fixed calling only
                if(uncalled.contains(i)){ // first time calling
                    just_called.insert(i);
                    uncalled.remove(i);
                }
                agents->hyenas[i]->set_calling(true);
                num_calling++;
            }
        } else {
            temp.reset();
            if(!LEARN_CALLING){
                agents->hyenas[i]->set_calling(false);
            }
        }
        agents->hyenas[i]->set_zebra(temp);
    }

	// set hyena vect's as well as nearest, nearest calling, named, nearest lion
	for(int i = 0; i < NUM_HYENAS; i++){
        agentx = agents->hyenas[i]->getX(); //get hyena x,y
        agenty = agents->hyenas[i]->getY();
        agents->hyenas[i]->set_num_hyenas(num_calling);
		min_mag = HYENA_HYENA_RADIUS_SQ;
		nearest_calling = DBL_MAX;

		// don't recalculate already-calculated vectors
		for(int j = 0; j < i; j++){
            temp = agents->hyenas[j]->get_hyena_vect(i);
			temp.invert();
            agents->hyenas[i]->set_hyena_vect(j, temp);
			// check if closest hyena yet
			magnitude = temp.magnitude;
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
			// check if closest calling hyena yet
            if(agents->hyenas[i]->get_calling() && magnitude < nearest_calling){
				nearest_calling = magnitude;
				calling_j = j;
			}
		}

		// vector to self should always be zero, so don't update

		// calculate vectors that haven't yet been calculated
		for(int j = i + 1; j < NUM_HYENAS; j++){
                magnitude = dist(agentx - agents->hyenas[j]->getX(),
                                 agenty - agents->hyenas[j]->getY());
				temp.magnitude = magnitude;
                temp.direction = atan2(agentx - agents->hyenas[j]->getX(),
                                       agenty - agents->hyenas[j]->getY());
                agents->hyenas[i]->set_hyena_vect(j, temp);
				// check if closest hyena yet
				if(magnitude < min_mag){
					min_mag = magnitude;
					the_j = j;
				}
				// check if closest calling hyena yet
                if(agents->hyenas[j]->get_calling() && magnitude < nearest_calling){
					nearest_calling = magnitude;
					calling_j = j;
				}
		}

		//// Set the nearest hyena

		// if nearest out of range, zero vector
		if(min_mag == HYENA_HYENA_RADIUS_SQ){
			temp.reset();
            agents->hyenas[i]->set_nearest_hyena(temp);
            agents->hyenas[i]->set_mirrored(temp);
		} else { // set to nearest hyena
			// set the closest hyena
            agents->hyenas[i]->set_nearest_hyena(
                        agents->hyenas[i]->get_hyena_vect(the_j));
			// set the mirrored input
            agents->hyenas[i]->set_mirrored(
                        agents->hyenas[the_j]->get_last_move());
		}

		//// Set the named and nearest calling hyena
		// set the named hyena (always in array position 0)
		if(!is_disabled(named)) // skip if disabled
            agents->hyenas[i]->set_named(agents->hyenas[i]->get_hyena_vect(0));

		// if nobody is calling, zero vector; else set nearest calling
		if(nearest_calling == DBL_MAX){
			temp.reset();
            agents->hyenas[i]->set_nearestcalling(temp);
		} else { // set to nearest calling hyena
            agents->hyenas[i]->set_nearestcalling(
                        agents->hyenas[i]->get_hyena_vect(calling_j));
		}

		//// Find nearest lion
		min_mag = LION_HYENA_RADIUS_SQ;
        for(int j = 0; j < deployed_lions; j++){
			magnitude = distance_sq(agentx - agents->lions[j].getX(),
									agenty - agents->lions[j].getY());
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		if(min_mag == LION_HYENA_RADIUS_SQ){
			temp.reset();
		} else{
			temp.magnitude = sqrt(magnitude);
			temp.direction = atan2(agentx - agents->lions[the_j].getX(),
								   agenty - agents->lions[the_j].getY());
		}
        agents->hyenas[i]->set_nearest_lion(temp);
	}

	/* If we should only get vectors to hyenas that are calling,
	 * zero out those that aren't. This is not optimized for
	 * efficiency, or most of them wouldn't be calculated first.
	*/
	if(VEC_CALLING_ONLY){
		temp.reset(); // the zero vector
		for(int i = 0; i < NUM_HYENAS; i++){
			// if a hyena isn't calling then zero out vectors to it
            if(!agents->hyenas[i]->get_calling()){
				for(int j = 0; j < NUM_HYENAS; j++){
                    agents->hyenas[j]->set_hyena_vect(i, temp);
				}
			}
		}
	}

	// lions
	// get closest hyena, count nearby lions, get vector to zebra
    for(int i = 0; i < deployed_lions; i++){
		int n_hyenas = 0;
		agentx = agents->lions[i].getX(); //get lion x,y
		agenty = agents->lions[i].getY();
		min_mag = LION_HYENA_RADIUS_SQ;
		for(int j = 0; j < NUM_HYENAS; j++){
            magnitude = distance_sq(agentx - agents->hyenas[j]->getX(),
                                    agenty - agents->hyenas[j]->getY());
			if (magnitude < LION_HYENA_RADIUS_SQ)
				n_hyenas++;
			if(magnitude < min_mag){
				min_mag = magnitude;
				the_j = j;
			}
		}
		if(min_mag < LION_HYENA_RADIUS_SQ){ // lion close enough to hyena
			temp.magnitude = sqrt(min_mag);
            temp.direction = atan2(agentx - agents->hyenas[the_j]->getX(),
                                   agenty - agents->hyenas[the_j]->getY());
		}
		else {
			temp.reset();
		}
		// lion -> hyena
		agents->lions[i].set_nearest_hyena(temp);
		agents->lions[i].set_num_hyenas(n_hyenas);

		// find nearest lion.
		int num_lions = 1; // count self
        for (int j = 0; j < deployed_lions; j++) {
			if(i == j) continue;
			magnitude = distance_sq(agentx - agents->lions[j].getX(),
									agenty - agents->lions[j].getY());
			if (magnitude < LION_LION_RADIUS_SQ)
				num_lions++;
		}
		agents->lions[i].set_num_lions(num_lions);

		// lion -> zebra
		temp.magnitude = dist(agentx - ZEBRAX, agenty - ZEBRAY);
		temp.direction = atan2(agentx - ZEBRAX, agenty - ZEBRAY);
		agents->lions[i].set_zebra(temp);
	}
}

void environment::draw(DrawHelper* helper, int itera, int timestep) {
	if(GUI){
		helper->iter.enqueue(itera);
		helper->landmarks.enqueue(QPointF(landmarkx, landmarky));
		helper->step.enqueue(timestep); // track current timestep
	}

	QStringList list;

	list.append(QString("l %1 %2\n").arg(landmarkx).arg(landmarky));

    for (int i = 0; i < deployed_lions; i++) {
		QPointF p = QPointF(agents->lions[i].getX(),
							agents->lions[i].getY());
		list.append(QString("%1 %2").arg(p.x()).arg(p.y()));
		if(GUI)
			helper->lions[i].append(p);
	}

    // fill in off-screen lions for undeployed lions
    for (int i = deployed_lions; i < NUM_LIONS; i++) {
        QPointF p = QPointF(-1000,
                            -1000);
        list.append(QString("%1 %2").arg(p.x()).arg(p.y()));
        if(GUI)
            helper->lions[i].append(p);
    }
    list.append("\n ");

    for (int i = 0; i < NUM_HYENAS; i++) {
        QPointF p = QPointF(agents->hyenas[i]->getX(),
                            agents->hyenas[i]->getY());
		list.append(QString("%1 %2").arg(p.x(), 0, 'g', 4)
                    .arg(p.y(), 0, 'g', 4));
		if(GUI)
			helper->hyenas[i].append(p);
	}
	list.append("\n");

    list.append("c"); // mark the calling section
    for (int i = 0; i < NUM_HYENAS; i++) {
        bool is_calling = agents->hyenas[i]->get_calling();
        if(is_calling){
            list.append(QString("t"));
        } else {
            list.append(QString("f"));
        }
        if(GUI)
            helper->calling[i].append(is_calling);
    }
    list.append("\n");

	ofstream f;
	f.open(fname, ios_base::app);
    f << list.join(" ").toStdString();
	f.close();
}

void environment::knockout_genes(const ops disabled[], int disabled_len){
    vect zero;
    zero.reset();
    // knockout genes as appropriate
	for(int i = 0; i < (disabled_len); i++){
        for(int j = 0; j < NUM_HYENAS; j++){
            switch(disabled[i]){
            // terminals
            case zebra:
                agents->hyenas[j]->set_zebra(zero);
                break;
            case nearest_hyena:
                agents->hyenas[j]->set_nearest_hyena(zero);
                break;
            case nearest_lion:
                agents->hyenas[j]->set_nearest_lion(zero);
                break;
            case nearest_calling:
                agents->hyenas[j]->set_nearestcalling(zero);
                break;
            case north:
                agents->hyenas[j]->set_north_enabled(false);
                break;
            case randm:
                agents->hyenas[j]->set_randm_enabled(false);
                break;
            case last_move:
                agents->hyenas[j]->set_last_move(zero);
                break;
            case constant:
                agents->hyenas[j]->set_constant_enabled(false);
                break;
            case number_calling:
                agents->hyenas[j]->set_num_hyenas(0);
                break;
            case mirror_nearest:
                agents->hyenas[j]->set_mirrored(zero);
                break;
            case last_pen:
                agents->hyenas[j]->reset_pen_input();
                break;
            case named:
                agents->hyenas[j]->set_named(zero);
                break;
            case landmark:
                agents->hyenas[j]->set_landmark(zero);
                break;
                // non-terminals
            case sum:
            case subtract:
            case compare:
            case invert:
            case iflteMAG:
            case iflteCLOCKWISE:
            case ifVectorZero:{
                ofstream error;
                error.open("error.txt", ios_base::app);
                error << "nonterminal in knockout: " << disabled[i] << endl;
                error.close();
                break;
            }
            default:{
				if(disabled[i] < NUM_OPS){
					int hyena_num = (disabled[i] - NUM_UNIQUE_OPS);
                    agents->hyenas[j]->set_hyena_vect(hyena_num, zero);
					break;
				}
                ofstream error;
                error.open("error.txt", ios_base::app);
                error << "error in knockout: " << disabled[i] << endl;
                error.close();
                break;
            }
            }
        }
    }
}
