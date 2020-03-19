#include "centeralwidget.h"
#include "scheduleselect.h"
#include "processesselector.h"
#include <QGridLayout>
#include "answer.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>


CenteralWidget::CenteralWidget(QWidget *parent) :
    QWidget(parent)

{
    scheduleselect=new ScheduleSelect(this);
    FIRST_PROCESSES_CREATION=0;
    layout=new QGridLayout(this);


    layout->addWidget(scheduleselect,0,0);
    layout->setSpacing(50);


    connect(scheduleselect,SIGNAL(input_finished()),this,SLOT(create_processess()));
}

CenteralWidget::~CenteralWidget()
{

}

void CenteralWidget::create_processess()
{
    if(FIRST_PROCESSES_CREATION!=0)
    {
        delete  ps;
        delete bar;
    }
    ps=new ProcessesSelector(this);

    ps->setModel(scheduleselect->getOp(),scheduleselect->getNo_p());



    layout->addWidget(ps,0,1);
    bar=new QScrollArea(this);
    bar->setWidget(ps);
    layout->addWidget(bar,0,1);
    FIRST_PROCESSES_CREATION=1;

}
