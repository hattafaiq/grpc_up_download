#ifndef COBA_LAGI_H
#define COBA_LAGI_H
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class coba_lagi : public QObject
{
    Q_OBJECT
public:
    explicit coba_lagi(QObject *parent = nullptr);
    ~coba_lagi();
    void Test();
    int flag_disconnect;
    int flag_db;

public slots:

private:

};
#include <grpcpp/grpcpp.h>
#include <string>
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"


struct t_data{
    char dataku[100];
};

#define BESAR_PAKET 400

struct t_rute {
    unsigned short 	flag;				 	// 2  sudah di trap atau belum
    unsigned short	point_ke;         		// 2  baru ditambahkan
    char 			inisial[10];     	  	// 10
    short  			sudut_fasa;     	  	// 2
    unsigned char	kanal;					// 1  20 Jan 2011, sofhaliza sudah sejak 11 Okt 2010
    unsigned char 	mask;					// 1  20 jan 2011
    short			id_tipe_param;    	    // 2  (di haliza ==> tipe_data)
    unsigned short	id_param;         		// 2  (2014, ini menjadi id_n_param), id_aset
    unsigned short	id_rute;				// 2  total = 38 bytes	--> id_rute (yg bener id_rute)
    unsigned short 	id_dikirim;				// 2  ditambahkan 17 juli, supaya satu rute bisa dipakai beberapa kali
};

struct t_kom_dat {						     // struk paket komunikasi
    char 		kpl[10];
    char 		iden[6];
    struct t_rute rute;                 //yg dipake inisial aja
    unsigned short 	data[ BESAR_PAKET ];
    unsigned short	cek[10];
};

#endif // COBA_LAGI_H
