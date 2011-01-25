#include "qthyena.h"

qthyena::qthyena(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);
	connect(&ui.widget->helper, SIGNAL(disp_timestep(QString)),
			ui.disp_time_curr, SLOT(setText(QString)));
	connect(&ui.widget->helper, SIGNAL(disp_timestep_total(QString)),
			ui.disp_time_total, SLOT(setText(QString)));

	connect(&ui.widget->helper, SIGNAL(disp_iteration(QString)),
			ui.disp_iteration_curr, SLOT(setText(QString)));
	connect(&ui.widget->helper, SIGNAL(disp_iteration_total(QString)),
			ui.disp_iteration_total, SLOT(setText(QString)));

	connect(&ui.widget->p, SIGNAL(next_calc_iteration(QString)),
				ui.calc_iterations_curr, SLOT(setText(QString)));
	connect(&ui.widget->p, SIGNAL(calc_iteration_total(QString)),
				ui.calc_iterations_total, SLOT(setText(QString)));

	connect(&ui.widget->helper, SIGNAL(disp_percent(int)),
			ui.disp_percent, SLOT(setValue(int)));
	connect(&ui.widget->helper, SIGNAL(disp_percent_total(int)),
			ui.disp_percent, SLOT(setMaximum(int)));

	connect(&ui.widget->p, SIGNAL(calc_percent(int)),
			ui.calc_percent, SLOT(setValue(int)));
	connect(&ui.widget->p, SIGNAL(calc_percent_total(int)),
			ui.calc_percent, SLOT(setMaximum(int)));
}

qthyena::~qthyena(){

}
