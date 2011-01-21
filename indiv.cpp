
#include "indiv.h"
//Window *win;


void indiv::xOver(indiv *p2){
	int point1 = rand()%size+1;
	int point2 = rand()%(p2->get_size())+1;
	int temp = 0;
	node *xOver1 = tree->get_point(point1,temp);
	temp = 0;
	node *xOver2 = p2->tree->get_point(point2,temp);
	node *tempP1,*tempP2;
	int c1,c2;
	tempP1 = xOver1->get_parent();
	tempP2 = xOver2->get_parent();
	if(tempP1 != NULL){  // not root
		if(tempP2 != NULL){ // not root         
			c1 = tempP1->find_child(xOver1);
			c2 = tempP2->find_child(xOver2);
			xOver1->set_parent(xOver2->get_parent());
			xOver2->set_parent(tempP1);
			tempP2->set_child(c2,xOver1);
			tempP1->set_child(c1,xOver2);
		}
	}
}         

void indiv::reset_fitness(void){
	fitness = 0;
	lion_attacks = 0;
	avg_dist_to_zebra = 0;
}     

void indiv::reset(void){
	calling = false;
	if(type == investigator){
		x = X/2 + ((rand()%20)/10.0)-1;
		y = Y/2 + ((rand()%20)/10.0)-1;
	}
	else{
		//         float ang = rand()%360;
		//         float rad = X/2 + rand()%X;
		//         x = X/2 + rad*sin(ang);
		//         y = Y/2 + rad*cos(ang);
		x = rand()%X;
		y = rand()%Y;
	}
}

indiv &indiv::operator=(const indiv &source){
	//x=source.x;
	//y=source.y;
	//the_info = source.the_info;
	//fitness = source.fitness;
	//size = source.size;
	//if(tree != NULL)
	//	clear();
	//tree = new node;
	//tree->copy(source.tree,NULL);
	//return *this;
	indiv ans;
	ans.x=source.x;
	ans.y=source.y;
	ans.the_info = source.the_info;
	ans.fitness = source.fitness;
	ans.size = source.size;
	//if(ans.tree != NULL)
	//	clear();
	ans.tree = new node;
	ans.tree->copy(source.tree,NULL);
	return ans;
}

void indiv::grow(void){
	x = X/2;
	y = Y/2;
	fitness = 0.0;
	tree = new node;
	tree->grow(GROW_DEPTH,0,NULL);
}

void indiv::clear(void){
	tree->clear();
	delete tree;
	tree = NULL;
}


void indiv::mutate(void){
	tree->mutate();
}

void indiv::rand_move(){
	//   x+=((rand()%3-1)/50.0);
	//   y+=((rand()%3-1)/50.0);
	;
}

void indiv::lion_move(void){
	if(the_info.num_scouts > (the_info.num_investigators*3)){
		x+=1.0*sin(the_info.nearest_scout.direction);
		y+=1.0*cos(the_info.nearest_scout.direction);
	}
	/*     else if(the_info.zebra.magnitude < LION_SEES_ZEBRA && the_info.zebra.magnitude > LION_NEAR_ZEBRA){
	x-=1.0*sin(the_info.zebra.direction);
	y-=1.0*cos(the_info.zebra.direction);
	}
	*/        
}

void indiv::move(void){
	vect v;
	if(type == investigator){
		lion_move();
		return;
	}
	if(tree != NULL){
		v = tree->evaluate(&the_info);
		if (v.magnitude > 1)  // trying to move too far
			v.magnitude = 1;
		if (type == investigator && v.magnitude >= 0.5)
			v.magnitude = 0.5;
		the_info.last_move.direction = v.direction;
		the_info.last_move.magnitude = v.magnitude;
		x+=v.magnitude*sin(v.direction);
		y+=v.magnitude*cos(v.direction);
	}
}

indiv::indiv(void){
	//  grow();
	//     connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
	//indiv* a = this;
	//connect(a, SIGNAL(draw()), win, SLOT(animate()));
}

//void indiv::draw(int i){
//	int vectorLength = 5;
//	// Draw agent
//	if(type == investigator)
//		glColor3f(1-0.01*i,1-0.01*i,0);
//	else
//		glColor3f(0.4,0.3+0.01*i,0);
//	if(calling == true)
//		glColor3f(1,0.3+0.01*i,0);
//
//	int ix = int(x),iy=int(y);
//	float ix2,iy2;
//	glBegin(GL_TRIANGLE_FAN);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX+SCOUT_SIZE/2)/yscale-yshift,0.05);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX)/yscale-yshift,0);
//	glVertex3f((x*BOX+SCOUT_SIZE)/xscale-xshift, (y*BOX+SCOUT_SIZE/2.0)/yscale-yshift,0);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift, (y*BOX+SCOUT_SIZE)/yscale-yshift,0);
//	glVertex3f((x*BOX)/xscale-xshift, (y*BOX+SCOUT_SIZE/2.0)/yscale-yshift,0);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX)/yscale-yshift,0);
//	glEnd(); 
//	/*
//	//vect to nearest calling 
//	glLineWidth(2.0); 
//	glColor3f(0.5,0.0,0.5);
//	//    glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX)/yscale-yshift,0);
//	ix2 = (x-(the_info.nearest_calling.magnitude*sin(the_info.nearest_calling.direction)));
//	iy2 = (y-(the_info.nearest_calling.magnitude*cos(the_info.nearest_calling.direction)));
//	glBegin(GL_LINES);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX+SCOUT_SIZE/2.0)/yscale-xshift,0);
//	glVertex3f((ix2*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(iy2*BOX+SCOUT_SIZE/2.0)/yscale-yshift,0);    
//	glEnd(); 
//	*/
//	//vect to nearest scout
//	/*
//	glLineWidth(2.0); 
//	glColor3f(1,1.0,1);
//	//    glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX)/yscale-yshift,0);
//	ix2 = (x-(the_info.nearest_scout.magnitude*sin(the_info.nearest_scout.direction)));
//	iy2 = (y-(the_info.nearest_scout.magnitude*cos(the_info.nearest_scout.direction)));
//	glBegin(GL_LINES);
//	glVertex3f((x*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(y*BOX+SCOUT_SIZE/2.0)/yscale-xshift,0);
//	glVertex3f((ix2*BOX+SCOUT_SIZE/2.0)/xscale-xshift,(iy2*BOX+SCOUT_SIZE/2.0)/yscale-yshift,0);      
//	glEnd(); 
//	*/
//
//}
