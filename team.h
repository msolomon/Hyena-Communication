#ifndef TEAM_H
#define TEAM_H

#include "globals.h"
#include "indiv.h"

class team{
      public:
        float calc_avg_fit();
        float get_avg_fit(){return this->avg_fit;}
        void calc_size();
        void mutate();
        void mutate(int,agent_type);
        void xOver(team *);
        void xOver(team *, int,agent_type);
        void copy(team *);
        void copy(team *, int, agent_type);
        void generate(void);
        void clear(void);
        void reset_team(void);
        float get_scout_fit(int i){return scout_fits[i];}
        float get_invest_fit(int i){return invest_fits[i];}
        float get_avg_dist_to_zebra(void){return avg_dist_to_zebra;}
        float get_avg_lion_attacks(void){return avg_lion_attacks;}
        void reset_fitness(void);
        
        indiv scouts[NUM_HYENAS];
        indiv invests[NUM_LIONS];
        float scout_fits[NUM_HYENAS];
        float invest_fits[NUM_LIONS];
        float avg_fit;
        float avg_lion_attacks;
        float avg_dist_to_zebra;
};    



#endif