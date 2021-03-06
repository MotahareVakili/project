#include "edit.h"
#include "ui_edit.h"
#include <QDebug>

edit::edit(QWidget *parent,QList<mv>*movie,class home*hm,QString*nm,int ix,QString* comb) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
    this->home=hm;
    this->movies=movie;
    this->name=nm;
    this->index=ix;
    this-> comb_g=comb;
    timer_1s = new QTimer(this);
    connect(timer_1s, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    timer_1s->start(100);
    load();


}

edit::~edit()
{
    delete ui;
}

void edit::on_close_clicked()
{
    this->close();
}

void edit::load()
{
           ui->lname->setText(movies->at(index).name);
           ui->ldirector->setText(movies->at(index).director);
           ui->lstars->setText(movies->at(index).stars);
           ui->limdb->setText(movies->at(index).imdb);
           ui->llanguage->setText(movies->at(index).language);
           ui->lreleas->setText(movies->at(index).release_year);
           QObjectList boxes=this->ui->qMain->children();
           for(QObject* obj:boxes)
           {
               if(obj->inherits("QCheckBox"))
               {
                   QCheckBox* box=qobject_cast<QCheckBox*>(obj);
                   if( box && movies->at(index).genre.contains(box->text(),Qt::CaseInsensitive))
                     {

                       box->setChecked(true);
                   }

               }

        }
}



void edit::on_edit_2_clicked()
{

    (*movies)[index].director=ui->ldirector->text();
    (*movies)[index].imdb=ui->limdb->text();
     (*movies)[index].name=ui->lname->text();
     (*movies)[index].stars=ui->lstars->text();
    (*movies)[index].language=ui->llanguage->text();
    (*movies)[index].release_year=ui->lreleas->text();
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
   (*movies)[index].genre=genre;
    home->comb_g(*comb_g);
    QMessageBox::information(this,"Edit","Successfully edited");
    this->hide();
    home->show();
}

void edit::on_cancel_clicked()
{
    load();

}

void edit::on_back_clicked()
{
    this->hide();
    home->show();
}
void edit::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void edit::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void edit::UpdateTime()
{
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

