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
    setMinimumSize(250,600);
    scheduleselect=new ScheduleSelect(this);
    FIRST_PROCESSES_CREATION=0;
    layout=new QGridLayout(this);
    layout->addWidget(scheduleselect,0,0);
    layout->setHorizontalSpacing(50);
    Answer *answer=new Answer(this);
    answer->set_model();
    QScrollArea *bar2=new QScrollArea(this);
    bar2->setWidget(answer);
    bar2->setFrameShape(QFrame::NoFrame);
    bar2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(bar2,2,0,1,2);
    QFont waiting_time_label("times",20,QFont::Bold,true);
    QPalette waiting_time_palette;
    waiting_time_palette.setColor(QPalette::WindowText,Qt::blue);

    QLabel *avg_waiting_time=new QLabel("Average Waiting Time",this);
    QLabel *avg_waiting_time_answer=new QLabel("20",this);
    avg_waiting_time->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
    avg_waiting_time->setFont(waiting_time_label);
    avg_waiting_time->setPalette(waiting_time_palette);
    avg_waiting_time_answer->setFont(waiting_time_label);
    avg_waiting_time_answer->setPalette(waiting_time_palette);
    QHBoxLayout *avg_waiting_time_layout=new QHBoxLayout;
    avg_waiting_time_layout->addWidget(avg_waiting_time);
    avg_waiting_time_layout->setContentsMargins(30,0,0,0);
    layout->addLayout(avg_waiting_time_layout,1,0);
    layout->addWidget(avg_waiting_time_answer,1,1);



    connect(scheduleselect,SIGNAL(input_finished()),this,SLOT(create_processess()));

}

CenteralWidget::~CenteralWidget()
{

}

void CenteralWidget::create_processess()
{
    setMinimumWidth(1020);
    if(FIRST_PROCESSES_CREATION!=0)
    {
        delete  ps;
        delete bar;
    }
    ps=new ProcessesSelector(this);

    ps->setModel(scheduleselect->getOp(),scheduleselect->getNo_p());




    bar=new QScrollArea(this);
    bar->setWidget(ps);
    layout->addWidget(bar,0,1);
    bar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bar->setFrameShape(QFrame::NoFrame);
    FIRST_PROCESSES_CREATION=1;

}
