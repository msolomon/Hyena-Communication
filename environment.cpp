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
	helper->zebras[0].enqueue(QPoint(ZEBRAX * BOX, ZEBRAY * BOX));

	for (int i = 0; i < NUM_LIONS; i++) {
		helper->lions[i].enqueue(
								QPoint(agents->invests[i].getX()*BOX,
										agents->invests[i].getY()*BOX)
								);
	}

	for (int i = 0; i < NUM_HYENAS; i++) {
		helper->hyenas[i].enqueue(QPoint(agents->scouts[i].getX() * BOX,
										agents->scouts[i].getY() * BOX));
	}
}

//void environment::draw(GLWidget*){
//	
//	static float angle = 0;
//	glClearColor(0.0, 0.7, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glColor3f(0.0, 0.0, 0.0);
//	glBegin(GL_POLYGON);
//	glVertex3f(-0.01,-0.01,0);
//	glVertex3f(-0.01,0.01 ,0);
//	glVertex3f(0.01,0.01,0);
//	glVertex3f(0.01,-0.01,0);
//	glEnd();
//	//   xshift = yshift = 0;
//	/*
//	for(int x = 0 ; x < X ; x++){
//	for(int y = 0; y < Y; y++){
//	if(map[x][y].get_interest() == 0)
//	glColor3f(0.0, 1.0, 0.0);
//	else if(map[x][y].get_interest() == 1)
//	glColor3f(1.0, 0.0, 0.0);
//	else  if (map[x][y].get_interest() == 2)
//	glColor3f(0.0, 0.5, 0.0);
//
//	glBegin(GL_POLYGON);
//	glVertex3f((x*BOX+1)/xscale-xshift, (y*BOX+1)/yscale-yshift,0);
//	glVertex3f((x*BOX+1)/xscale-xshift, (y*BOX+BOX-1)/yscale-yshift ,0);
//	glVertex3f((x*BOX+BOX-1)/xscale-xshift, (y*BOX+BOX-1)/yscale-yshift,0);
//	glVertex3f((x*BOX+BOX-1)/xscale-xshift, (y*BOX+1)/yscale-yshift,0);
//	glEnd();
//
//	*/            
//	//          map[x][y].draw(hwnd,x,y);
//	//      }
//	//  }
//
//
//
//	/*
//	for(int i =0; i < beacons.size();i++)
//	beacons[i].draw();
//
//	for(int i =0; i < NUM_HYENAS;i++)
//	agents->scouts[i].draw(i);
//	for(int i =0; i < NUM_LIONS;i++)
//	agents->invests[i].draw(i);
//
//	
//
//	SwapBuffers (hDc);
//	sleep(0);
//	*/
//
//
//	/*
//	if(angle < 65){
//	glRotatef(-1,1,0,0);
//	angle+=1;
//	}
//	*/
//}
