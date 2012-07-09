#include "indiv_base.h"

void indiv_base::lion_move(void) {
    if (the_info.num_hyenas > (the_info.num_lions * HYENA_LION_FEAR_RATIO)) {
        x += LION_MOVE * sin(the_info.nearest_hyena.direction);
        y += LION_MOVE * cos(the_info.nearest_hyena.direction);
    }
    else if(LIONS_RETURN &&
            the_info.zebra.magnitude < LION_SEES_ZEBRA &&
            the_info.zebra.magnitude > LION_NEAR_ZEBRA){
        x -= LION_MOVE * sin(the_info.zebra.direction);
        y -= LION_MOVE * cos(the_info.zebra.direction);
    }
}

indiv_base::~indiv_base(){
}

void indiv_base::move(void) {
    vect v;
    if (type == lion) {
        lion_move();
        return;
    }

    v = eval_me();

    the_info.last_move.direction = v.direction;
    the_info.last_move.magnitude = v.magnitude;

    if (v.magnitude > MAX_HYENA_MOVE){ // trying to move too far
        v.magnitude = MAX_HYENA_MOVE;
    }

    assert(v.magnitude >= 0 &&
           v.magnitude <= MAX_HYENA_MOVE &&
           "Magnitude outside valid range!");
    assert(v.direction <= PI &&
           v.direction >= -PI &&
           "Direction outside valid range!");

    if(v.magnitude != 0) // if moving
        the_info.moved_yet = true;

    x += v.magnitude * sin(v.direction);
    y += v.magnitude * cos(v.direction);
}

void indiv_base::reset_fitness() {
    for(int i = 0; i < NUM_TESTS; i++){
        fitnesses[i] = 0;
    }
    reward = 0;
    lion_attacks = 0;
    attack_pen = 0;
    avg_dist_to_zebra = 0;
    the_info.hits = 0;
    for(int i = 0; i < NUM_OPS; i++){
        the_info.importance[i] = 0;
    }
}

void indiv_base::reset(void) {
    calling = false;
    if (type == lion) {
        // place lions within 1 unit of zebra
        x = ZEBRAX + Random::Global.FloatW();
        y = ZEBRAY + Random::Global.FloatW();
    } else {
        x = y = 0;
        while (distance_sq(x, y) < (
                   (LION_ATTACK_RADIUS + 1) * (LION_ATTACK_RADIUS + 1)
                   )){
            x = Random::Global.FixedN() * X;
            y = Random::Global.FixedN() * Y;
        }
    }
}
