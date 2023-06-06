#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coba_lagi.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "coba_lagi.h"
#include <iostream>
#include <memory>
#include <string>
#include "grpcpp/support/channel_arguments.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"

#define gagal 100
#define OK_Cek 11
#define upload 1
#define download 3
#define info_upload 10
#define info_download 30


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ChannelArguments;
using grpc::experimental::Interceptor;
using helloworld::Greeter2;
using helloworld::HelloReply;
using helloworld::HelloRequest;

coba_lagi coba;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GRPC Client");
    //cek_data(0, 0, 0, 0);
    this->setMinimumSize(350,350);
    this->setMaximumSize(350,350);
}

MainWindow::~MainWindow()
{
    delete ui;
}


class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter2::NewStub(channel)) {}
   std::string SayHello(const std::string& user) {
    // Data we are sending to the server.

   coba.flag_disconnect = 0;
   coba.flag_db = 1;
   HelloRequest request;
   request.set_name(user);
   HelloReply reply;
   ClientContext context;
   QSqlDatabase db;
   ////////////////////////////////////////////////////////////
   /// \brief mulai kasi data apa saja urutannya:
   ///
   ///
   ///
    //*info upload yang dikirim array nya tipe data dan arraynya epoch
      //byte nya bisa dimasukkan info asetnya, sekalian bikin param
   //*upload yang dikirim array satuan, tanpa array dan ngecek sizenya per buah
   //*sisa yang dikirim dicek last kirim/ yang berhasil terkirim,
     //last array upload untuk bandingin sama array sisa, lalu sisa yang dikirim
   //*ganti mode upload
   //kelar;
    //if(coba.flag_db==1){
    QString filename = "tes_viro.dbb";
    QString con_name;
    con_name = QString("LOC_DB%1").arg(1);
    db =QSqlDatabase::addDatabase("QSQLITE",con_name);
    db.setDatabaseName(filename);
    coba.flag_db=0;
    //}
    QByteArray buffer_data;
    QByteArray hard;
    QString nama_aset;
    std::vector<int32_t> array_size_data;
    std::vector<int32_t> array_epoc;
    std::vector<int32_t> array_tipe;
    int siap =info_upload;
    if(!db.open())
    {
      qDebug()<<"db gak kebukak";
      //return;
    }
    else
    {
        QSqlQuery buka(db);
        QVector<int> data = {1,2,3,4};
        int jumlah = 4;
        //if(siap==OK_Cek || siap==gagal);

        for(int i=0; i<jumlah; i++){//loop jumlah data
        buka.prepare("select * from data_41_tipe where id=:id");
        buka.bindValue(":id", data[i]);
        if(!buka.exec()){qDebug()<<"gak buka";}
        else{while(buka.next()){
          QByteArray data1 = buka.value("data").toByteArray();
          array_size_data.push_back(data1.size());
          buffer_data.push_back(data1);
          //array_epoc.push_back(buka.value("data_timestamp").toInt());
          //array_tipe.push_back(410);
          if(user=="info UPLOAD"){
              request.add_tipe_data(41);
              request.add_timeepoch(buka.value("data_timestamp").toInt());
              request.add_size_arr(data1.size());
          }
          else if(user=="UPLOAD"){
              std::string stdString(data1.constData(), data1.length());
              request.set_datablob(stdString);
              qDebug()<<"data size:"<<data1.size();
              //qDebug()<<"---------------------------------->";
          }
        }}
        }//diluar loop

        if(user=="info UPLOAD"){
            request.set_size_all(buffer_data.size());
            std::cout << user << std::endl;
            qDebug()<<"size all data:" <<buffer_data.size();
        }
        else if(user=="UPLOAD")
            std::cout << user << std::endl;
        else if(user=="Cek")
            std::cout << user << std::endl;
        else if(user=="Selesai")
            std::cout << user << std::endl;

    }//loop dumlah data
   Status status = stub_->SayHello(&context,request ,&reply);

    if (status.ok()) {
       //std::cout << user << std::endl;
       qDebug()<<"ok";
       qDebug()<<"---------------------------------->";
       coba.flag_disconnect = 0;
      return reply.name();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      coba.flag_disconnect = 1;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter2::Stub> stub_;
};
ABSL_FLAG(std::string, target, "192.168.20.62:5000", "Server address");

void MainWindow::cek_data(int koneksi, int tipe_data, int time_epoch, int size){

    std::string target_str = absl::GetFlag(FLAGS_target);
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (target_str, grpc::InsecureChannelCredentials(), ch_args));
    std::string user("info UPLOAD");
    greeter.SayHello(user);
//    qDebug()<<"cek koneksi:"<<coba.flag_disconnect;
//    std::string user1("UPLOAD");
//    greeter.SayHello(user1);
//    qDebug()<<"cek koneksi:"<<coba.flag_disconnect;
//    std::string user2("Cek");
//    greeter.SayHello(user2);
//    qDebug()<<"cek koneksi:"<<coba.flag_disconnect;
//    std::string user3("Selesai");
//    greeter.SayHello(user3);
//    qDebug()<<"cek koneksi:"<<coba.flag_disconnect;
}


void MainWindow::on_pushButton_clicked()
{
    cek_data(0,0,0,0);
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string target_str = absl::GetFlag(FLAGS_target);
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (target_str, grpc::InsecureChannelCredentials(), ch_args));
    std::string user1("UPLOAD");
    greeter.SayHello(user1);
}


void MainWindow::on_pushButton_3_clicked()
{
    std::string target_str = absl::GetFlag(FLAGS_target);
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (target_str, grpc::InsecureChannelCredentials(), ch_args));
    std::string user2("Cek");
    greeter.SayHello(user2);
}


void MainWindow::on_pushButton_4_clicked()
{
    std::string target_str = absl::GetFlag(FLAGS_target);
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (target_str, grpc::InsecureChannelCredentials(), ch_args));
    std::string user3("Selesai");
    greeter.SayHello(user3);
}

