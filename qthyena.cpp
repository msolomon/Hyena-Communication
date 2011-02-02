#include "qthyena.h"

qthyena::qthyena(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);
	connectAll();
}

qthyena::~qthyena(){

}

void qthyena::connectAll(){
	connect(&ui.widget->helper, SIGNAL(disp_iteration(QString)),
			ui.disp_iteration_curr, SLOT(setText(QString)));
	connect(&ui.widget->helper, SIGNAL(disp_iteration_total(QString)),
			ui.disp_iteration_total, SLOT(setText(QString)));

	connect(&ui.widget->p, SIGNAL(calc_iter(QString)),
			ui.calc_iterations_curr, SLOT(setText(QString)));
	connect(&ui.widget->p, SIGNAL(calc_iter_total(QString)),
			ui.calc_iterations_total, SLOT(setText(QString)));

	connect(&ui.widget->p, SIGNAL(calc_trial(QString)),
			ui.calc_trials_curr, SLOT(setText(QString)));
	connect(&ui.widget->p, SIGNAL(calc_trial_total(QString)),
			ui.calc_trials_total, SLOT(setText(QString)));

	connect(&ui.widget->helper, SIGNAL(disp_trial(QString)),
			ui.disp_trial_curr, SLOT(setText(QString)));
	connect(&ui.widget->helper, SIGNAL(disp_trial_total(QString)),
			ui.disp_trial_total, SLOT(setText(QString)));

	connect(&ui.widget->helper, SIGNAL(disp_iter_percent(int)),
			ui.disp_iter_percent, SLOT(setValue(int)));
	connect(&ui.widget->helper, SIGNAL(disp_iter_percent_total(int)),
			ui.disp_iter_percent, SLOT(setMaximum(int)));

	connect(&ui.widget->helper, SIGNAL(disp_trial_percent(int)),
			ui.disp_total_percent, SLOT(setValue(int)));
	connect(&ui.widget->helper, SIGNAL(disp_trial_percent_total(int)),
			ui.disp_total_percent, SLOT(setMaximum(int)));

	connect(&ui.widget->p, SIGNAL(calc_trial_percent(int)),
			ui.calc_trial_percent, SLOT(setValue(int)));
	connect(&ui.widget->p, SIGNAL(calc_trial_percent_total(int)),
			ui.calc_trial_percent, SLOT(setMaximum(int)));

	connect(&ui.widget->p, SIGNAL(calc_iter_percent(int)),
			ui.calc_iter_percent, SLOT(setValue(int)));
	connect(&ui.widget->p, SIGNAL(calc_iter_percent_total(int)),
			ui.calc_iter_percent, SLOT(setMaximum(int)));
}

