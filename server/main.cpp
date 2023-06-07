#include <QCoreApplication>
#include <QApplication>
#include "bisa.h"
#include <grpcpp/grpcpp.h>
#include <string>
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"
#include <QDebug>
#include <iostream>
#include <memory>
#include <string>

#include "tampilserver.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#define FFT_LINES_DISABLE   0
#define FFT_LINES_50        1
#define FFT_LINES_100       2
#define FFT_LINES_200       3
#define FFT_LINES_400       4
#define FFT_LINES_800       5
#define FFT_LINES_1600      6
#define FFT_LINES_3200      7
#define FFT_LINES_6400      8
#define FFT_LINES_12800     9

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Status;
using helloworld::Greeter2;
using helloworld::HelloReply;
using helloworld::HelloRequest;

ABSL_FLAG(uint16_t, port, 5000, "Server port for the service");

QVector<int> validasi[3];

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int decode_fft_lines(int setting_lines )
{
    if ( setting_lines == FFT_LINES_DISABLE)
        return 0;
    else if (setting_lines == FFT_LINES_50)
        return 50;
    else if (setting_lines == FFT_LINES_100)
        return 100;
    else if (setting_lines == FFT_LINES_200)
        return 200;
    else if (setting_lines == FFT_LINES_400)
        return 400;
    else if (setting_lines == FFT_LINES_800)
        return 800;
    else if (setting_lines == FFT_LINES_1600)
        return 1600;
    else if (setting_lines == FFT_LINES_3200)
        return 3200;
    else if (setting_lines == FFT_LINES_6400)
        return 6400;
    else if (setting_lines == FFT_LINES_12800)
        return 12800;
    else
        return 0;
}

class GreeterServiceImpl final : public Greeter2::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {


    ////////////////////////////////////////////////////////////
    /// \brief mulai terima apa saja perintahnya:
    ///
    ///
    ///

    if(request->name()=="info UPLOAD"){
        std::cout << "Req " << request->name() << std::endl;
        std::string prefix("UPLOAD");
        //reply->set_name(prefix + request->name());
        reply->set_name(prefix);

        std::cout << "size all: " << request->size_all() << std::endl;
        if(request->size_arr_size() == request->timeepoch_size()){
            for(int i=0; i<request->size_arr_size(); i++){
                std::cout << "size " << i <<":"<< request->size_arr(i) << std::endl;
                std::cout << "time " << i <<":"<< request->timeepoch(i) << std::endl;
                std::cout << "tipe " << i <<":"<< request->tipe_data(i) << std::endl;
                validasi[0].push_back(request->tipe_data(i)); //info array tipe data
                validasi[1].push_back(request->timeepoch(i)); //info array time epoch
                validasi[2].push_back(request->size_arr(i)); //info array size
            }
        }else{
            qDebug()<<"kiriman data rusak";
        }
    }else if(request->name()=="UPLOAD"){
        std::cout << "UPLOAD Req " << request->name() << std::endl;
        QByteArray byteArray(request->datablob().c_str(), request->datablob().length());
        qDebug()<<"bytea: "<<byteArray.size();
        std::cout << "data ke =" << request->size_all() << std::endl;
        qDebug()<< "tipe data: "<<validasi[0][0];
        //qDebug()<< "tipe data: "<<validasi[0][0];
        //int datake = request->size_all();
        if((validasi[0][request->size_all()]==41)||
           (validasi[0][request->size_all()]==42)||
           (validasi[0][request->size_all()]==43)&&
           (request->flagparam()==1)){
            //qDebug()<<" masuk data 41 bro";
            struct t_kom_dat *_tKomDat;
            struct t_dd_rotat *_tDataRotat;
            int pjgtRute = sizeof(t_rute);
            int pjgtSetPar = sizeof(t_setting_param);
            int pjgKomDat = sizeof (_tKomDat->data);
            int pjgtDdRot = sizeof(t_dd_rotat);
            int pjgData;
            int sizeTotal;

            struct t_setting_param *_tSetParamData;
            QByteArray dSetPAram = byteArray.mid(pjgtRute,pjgtSetPar);
            _tSetParamData = (struct t_setting_param *) dSetPAram.data();
            pjgData = (decode_fft_lines(_tSetParamData->fft_lines)) *4 + (decode_fft_lines(_tSetParamData->fft_lines) *4 *2.56) ; // point *4 + point*4*2.56
            sizeTotal = pjgtRute + pjgKomDat + pjgData + pjgtDdRot;

            QByteArray dDatRot = byteArray.mid((pjgtRute+pjgKomDat+pjgData),pjgtDdRot);
            _tDataRotat =(struct t_dd_rotat *) dDatRot.data();
            qDebug()<<"test setting data: " <<"||fft lines: " << decode_fft_lines(_tSetParamData->fft_lines)<<
                      "||ovrlp: "<<_tSetParamData->fft_overlap <<
                      "||fstart: "<<_tSetParamData->freq_start<<
                      "||fstop: " << _tSetParamData->freq_stop;

            //ini tanpa flag setting param
            // struct t_dd_rotat *_tDataRotat;
//            struct t_info_rotat *_inforot;
//            int pjgtInforotat = sizeof(_inforot);
//            QByteArray dinforot = byteArray.mid(pjgtRute,pjgtInforotat);
//            _inforot = (struct t_info_rotat *) dinforot.data();
//            qDebug()<<"test setting data: " <<"||fft lines: " << _inforot->fft_point<<
//                      "||ovrlp: "<<_inforot->overlap <<
//                      "||fstart: "<<_inforot->high_pass<<
//                      "||fstop: " << _inforot->f_maks;
        }
        else{
            qDebug()<<"bukan rotating";
        }
        reply->set_done_send(1);
        std::string prefix("Cek");
        reply->set_name(prefix);
            //mulai masukin ke database/buffer
    }
    else if(request->name()=="Cek"){
        std::cout << "Cek Req " << request->name() << std::endl;
        if(request->size_all()==validasi[0].size()){
            qDebug()<<"sudah selesai";
            std::string prefix("Selesai");
            reply->set_name(prefix);
            validasi->clear();
        }
        else{
            std::string prefix("Cek");
            reply->set_name(prefix);
        }
            //mulai masukin ke database/buffer
        }
    else if(request->name()=="Selesai"){
        std::cout << "Selesai Req " << request->name() << std::endl;
        std::string prefix("Selesai");
        reply->set_name(prefix);
        validasi->clear();
            //mulai masukin ke database/buffer
        }
    return Status::OK;
  }
};

void RunServer(uint16_t port) {

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.

    builder.SetMaxSendMessageSize(1024 * 1024 * 1024);
    builder.SetMaxMessageSize(1024 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    GreeterServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
   // grpc::ServerAsyncResponseWriter<EchoResponse> response_writer()
    server->Wait();

}

int main(int argc, char** argv) {
 // QApplication a(argc, argv);
  //TampilServer as;
  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
