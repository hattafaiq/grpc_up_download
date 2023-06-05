#include <QCoreApplication>
#include "bisa.h"
#include <grpcpp/grpcpp.h>
#include <string>
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"
#include <QDebug>
#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Status;
using helloworld::Greeter2;
using helloworld::HelloReply;
using helloworld::HelloRequest;

ABSL_FLAG(uint16_t, port, 5000, "Server port for the service");

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

class GreeterServiceImpl final : public Greeter2::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {


    ////////////////////////////////////////////////////////////
    /// \brief mulai terima apa saja perintahnya:
    ///
    ///
    ///
    QVector<int> validasi[3];
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
                validasi[0].push_back(request->tipe_data(i));
                validasi[1].push_back(request->timeepoch(i));
                validasi[2].push_back(request->size_arr(i));
            }
        }else{
            qDebug()<<"kiriman data rusak";
        }
    }else if(request->name()=="UPLOAD"){
        std::cout << "UPLOAD Req " << request->name() << std::endl;
        std::string prefix("Cek");
        reply->set_name(prefix);
            //mulai masukin ke database/buffer
    }
    else if(request->name()=="Cek"){
        std::cout << "Cek Req " << request->name() << std::endl;
        std::string prefix("Selesai");
        reply->set_name(prefix);
            //mulai masukin ke database/buffer
        }
    else if(request->name()=="Selesai"){
        std::cout << "Selesai Req " << request->name() << std::endl;
        std::string prefix("Selesai");
        reply->set_name(prefix);
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
  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
