#include "add.h"
#include "ui_add.h"


Add::Add(QWidget *parent,QList<mv>*movie,class home *hm,QString *c) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    this->movies=movie;
    this->home=hm;
    this-> combo_g=c;
    timer_1s = new QTimer(this);
    connect(timer_1s, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    timer_1s->start(100);

}

Add::~Add()
{
    delete ui;
}



void Add::on_cancel_clicked()
{
    this->ui->ldirector->clear();
    this->ui->limdb->clear();
    this->ui->llanguage->clear();
   this->ui->lname->clear();
    this->ui->lstars->clear();
    this->ui->lreleas->clear();
}

void Add::on_close_clicked()
{
    this->close();
}

void Add::on_add_clicked()
{
    mv tmp;
    tmp.name=this->ui->lname->text();
    tmp.director=this->ui->ldirector->text();
   tmp.stars=this->ui->lstars->text();
    tmp.release_year=this->ui->lreleas->text();
    tmp.language=this->ui->llanguage->text();
    tmp.imdb=this->ui->limdb->text();
    tmp.valence="30";
    QString genre;
    QObjectList boxes=this->ui->qMain->children();
    foreach(QObject* obj,boxes)
    {
        if(obj->inherits("QCheckBox"))
        {
            QCheckBox* box=qobject_cast<QCheckBox*>(obj);
            if(box && box->isChecked())
                genre+=box->text()+"\r\n";

        }
    }
    tmp.genre=genre;
   movies->append(tmp);
   QMessageBox::information(this,"Add","Successfully added");
    home->comb_g(*combo_g);
    this->hide();
    home->show();


}
void Add::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Add::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}



void Add::on_ret_clicked()
{
    this->hide();
    parentWidget()->show();
}

void Add::UpdateTime()
{
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}
