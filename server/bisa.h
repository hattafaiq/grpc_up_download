#ifndef BISA_H
#define BISA_H

#include <QObject>
#include <iostream>
#include <grpcpp/grpcpp.h>
#include <string>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"

class bisa: public QObject
{
    Q_OBJECT
public:
   explicit bisa(QObject *parent=nullptr);
   virtual ~bisa();
   void mulai();
   void check_db_exist(QString filename, int count_db, QByteArray data);
   void load_database(QString filename, int count_db, QByteArray data);
   //void proses_q( QSqlQuery *q, const char *s, ...);
private:

public slots:
};

struct t_setting_param {
    int     id_tipe_param;
#if _TTY_POSIX_
    u_char  tipe_tipikal;
    u_char  sumber_data;
    u_char  power_icp;
    u_char  coupling;
    u_char  window_filter;
    u_char  enable_hf_envelope;
    u_char  enable_trigger;
    u_char  integrasi;
    u_char  save_time_domain;
    u_char  save_freq_domain;
    u_char  data_output;
    u_char  amplitude_info;
    u_char  set_gain;

    u_char  fft_overlap;            /* dalam %, misalnya 50 berarti 50 % */
    u_char  skala_y;
    u_char  skala_x;
    u_char  unit_x;
    u_char  tipe_display;
#else //_TTY_WIN_
    unsigned char  tipe_tipikal;
    unsigned char  sumber_data;
    unsigned char  power_icp;
    unsigned char  coupling;
    unsigned char  window_filter;
    unsigned char  enable_hf_envelope;
    unsigned char  enable_trigger;
    unsigned char  integrasi;
    unsigned char  save_time_domain;
    unsigned char  save_freq_domain;
    unsigned char  data_output;
    unsigned char  amplitude_info;
    unsigned char  set_gain;

    unsigned char  fft_overlap;            /* dalam %, misalnya 50 berarti 50 % */
    unsigned char  skala_y;
    unsigned char  skala_x;
    unsigned char  unit_x;
    unsigned char  tipe_display;
#endif

    int     kanal;
    int     sampling_rate;
    int     num_siklus_simpan;      /* jumlah period disimpan */
    int     num_average;
    int     fft_lines;
    int     unit;                   /*Satuan*/
    int     multipeaks;
    int     sideband;

    double  freq_start;
    double  freq_stop;
    double  freq_envelope;
    double  sensitivity;        /* dalam satuan mV/unit*/
};

struct t_data{
    char dataku[100];
};

struct t_plot_aux{
        //int  tipe_data;     /* untuk menentukan struct yang dipakai, diganti dengan id_tipe_param */
        int  num_sample;    /* jumlah sample, terutama untuk recip */
        //char *title;
        //char *nama_point;
        char deskripsi[64];
        char date[32];      /* rute send */
        char nama_sub_unit[128]; // rotating
        char nama_unit[128];     // mesin, equipment
        char nama_lokasi[128];   // nama lokasi/group
        char nama_dept[128];
        //char nama_pt[128];       // nama perusahaan
        char info_unit[1024];       // nama perusahaan dll
        char plot_info[128];     // yang diplot di kanvas grafik
        char satuan_bawah[32];
        char satuan_kiri[32];
        char judul_plot[64];

        /* info2 sebelah kanan grafik */
        char info_judul[32];         // judul info sebelah kanan
        char info_overall[32];         // overal value
        char info_peak[32];    // peak
        char info_rpm[32];
        char info_load[32];
        char info_rute[32];
        char info_tgl[32];
        char info_jam[32];

        /* baru Agt 2015 */
        int id_data;        /* dari tabel data sesuai nama tabel */
        int id_aset;
        int id_param;
        int id_tipe_param;
        int id_date;
        char db_con_name[128];
        int flag_4_tak;
        int fft_point;
        int kind;

        char title[256];
        char nama_point[32];
        char paramnya[33];
        int flag_urutan_parade;    /* 0 biasa (parade ditumpuk), 1 parade sesuai firing order */

        /* dibutuhkan guna menyimpan sudut fasa untuk parade */
        double phase_angle;

        int id_siklus[128];
        int num_siklus;
        int index_siklus;

        /* flag apakah plot waveform */
        int flag_wf;

        int flag_pv;
};

#define SIZE_UMUM   128
#define SIZE_DETIL  4096    /* cukup besar untuk future use */

#define BESAR_PAKET 400
struct t_statistik_rotat{
    int reff_rpm;       //reff rpm
    int dec_f;	        // volt
    int point;		// volt
    float vel_ampl;		// mm/s - Peak freq dominan
    float vel_frekDom;		// mm/s - RMS freq dominan
    float vel_overall_peak;     // mm/s overal dari spektrum dlm peak
    float vel_overall_rms;      // mm/s overal dari spektrum dlm rms
//    float rpm;                  // vel freq dominan(hz)*60
    float env_wf_peak;          // g's
    float env_wf_rms;           // g's
    float env_wf_cf;		// ratio (env_peak dibagi env_rms)
    float temp;                 // temp from dual sensor accelerometer-temp
    int unit_temp; 		// UNIT_CELCIUS or UNIT_FAHRENHEIT (1000 , 1100)
    unsigned long long timestamp;   //in epoch time second
};


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

struct t_setting
{
    /* port komunikasi */
    int  use;               /*17 jan 2018 diganti menjadi (0 serial, 1 bluetooth )//  <> 1 serial, 2 bluetooth, 3 usb, serial */
    char port_name[64];
    char port_speed[32];
    int use_temp;

    /* unutk kumonikasi TCP */
    QString address_Tcp;
    int port_tcp;

    QString con_name;

    /* 17 Jan 2018*/
    int protokol;   /* 0 untuk sofhaliza 8, 1 unutk sofhaliza 10 */

    /* 16 maret 2020 ,  point ke index combobox */
    char vibro_com[64];
    char vibro_speed[32];
    char vibro_protokol_ver[32];
    int mode_komu_device=0;

    /*  database terakhir dibuka
        supaya saat dijalanin lagi langsung buka database terakhir ini */
    char last_open[1024];

    /* satuan */
    int unit_acc;       /* 1 m/s², 2 G */
    int unit_velo;      /* 1 mm/s, 2 IPS */
    int unit_disp;      /* 1 mm, 2 micron, 3 mills, */
    int unit_pcomb;     /* 1 bar, 2 psi */
    int unit_temp;      /* 1 Celecius, 2 Fahrenheit */
    int unit_ihp;       /* 1 kW, 2 horse power */
    int unit_flow_komp; /* 1 MMSCFD, 2 M3/h */
    int unit_frek;      /* 1 Hz, 2 rpm, 3 order */
    int unit_time;      /* 1 milisecond, 2 second, 3 Cycle*/
    int unit_rod_load;   /* 1 newton, 2 LBS */
    int unit_length; /* 1 mm, 2 inch  */

    /* warna grafik qwtplot */
    /* Warna */
    QString curve_color[25];    // warna curve_plot
    QString background_color;   // warna background_plot
    QString grid_color;         // warna grid_plot
    QString body_color;         // warna body_plot
    int     curve_size_index;   // index ukuran curve
    float   curve_size;         // ukuran curve
    bool    check_legend;       // Checkbox Legend
    bool    check_info;         // Checkbox Info curve
    /* Skala */
    QString model_font_scale;   // model huruf_skala
    int size_font_scale;        // ukuran huruf_skala
    /* Judul */
    QString model_font_title;   // model huruf_judul
    int size_font_title;        // ukuran huruf_judul
    QString font_title_color;   // warna huruf_judul

    /* Judul Plot*/
    QString model_font_plot_title;  //model plot_judul
    int size_font_plot_title;       //ukuran plot_judul
    QString font_plot_title_color;  //warna plot_judul

    /* default rotating */
    int high_pass;
    int low_pass;
    int fft_point;
    int averages;
    int window;
    int PP;
    int keluaran;
    int multipeak;
    int sideband;
    /* belum digunakan di form spektrum, sepertinya  t_setting digunakan pada
     * struct pengaturan bukan pada tiap siklus spektrum rotating
    */
    bool set_rpm;
    int new_rpm;

    /* nilai filter */
    int high_filter_val;
    int low_filter_val;

    /* setting buat filter nilai dpdt */
    bool fil_dpdt_use;
    double fil_dpdt_val;
    bool flag_dpdt;

    /* default recip engine */
    int sample;
    int s_rate;
    int kanal_enable;
    int source_kanal_1;
    int source_kanal_2;
    int trigger_fasa;
    /* pilihan sudut 2-tak */
    double sudut_a_2;
    double sudut_b_2;
    double sudut_c_2;
    double sudut_d_2;
    double sudut_e_2;
    /* pilihan sudut 4-tak */
    double sudut_a_4;
    double sudut_b_4;
    double sudut_c_4;
    double sudut_d_4;
    double sudut_e_4;
    /* nilai sudut */
    int rata_rata;
    /* f_cut-off */
    float fc;
    int terfilter;

    /* default recip compressor */
    int sample_comp;
    int s_rate_comp;
    int kanal_enable_comp;
    int source_kanal_1_comp;
    int source_kanal_2_comp;
    int trigger_fasa_comp;

    /* setting skala recip */
    bool skala_recip;
    double max_amp_recip;
    double min_amp_recip;
    bool skala_pressure;
    double max_pres_val;
    double min_pres_val;

    /* set size untuk print pdf */
    bool print_size;
    bool print_conf;

    /* network database */
    char net_hostname[1024];
    char net_db_name[1024];
    char net_user[256];
    char net_passwd[256];
    //char db_file_name[64];
    int  sql_driver;    // 1 SQLITE, 2 MYSQL, 3 POSTGRE
    QString ip_server;
    int port_server;
    int data_push_server;   // 1 gk dipake, 2 dipake


    /* kirim route */
    QString last_name_data_kirim;
    int last_row_data_kirim;
    int last_column_data_kirim;

    /* untuk flag off route global, keperluan copy data */
    bool copy_off_route;

    /* flag data doesn't exist */
    int dat_avb;

    /* flag copy data form_spektrum */
    bool flag_copy;
    bool flag_copy_pv;

    /* 27 Okt 2014 */
    unsigned short index_rotat;

    unsigned short fft_point_vel;
    unsigned short low_cut_vel;
    unsigned short high_pass_vel;
    unsigned short averages_vel;
    unsigned short window_vel;
    unsigned short PP_vel;

    unsigned short fft_point_acc;
    unsigned short low_cut_acc;
    unsigned short high_pass_acc;
    unsigned short averages_acc;
    unsigned short window_acc;
    unsigned short PP_acc;

    unsigned short fft_point_disp;
    unsigned short low_cut_disp;
    unsigned short high_pass_disp;
    unsigned short averages_disp;
    unsigned short window_disp;
    unsigned short PP_disp;

    unsigned short fft_point_vol;
    unsigned short low_cut_vol;
    unsigned short high_pass_vol;
    unsigned short averages_vol;
    unsigned short window_vol;
    unsigned short PP_vol;

    /* Setting Bahasa */
    int bahasa;

    /* setting show timestamp collect data*/
    int show_timestmap_collect_data=0;

    /*21 Jan 2022 tambah info VID serial USB*/
    int vid=0;

    /*default untuk rotating*/
       int minAmpWaveRot;
       int maxAmpWaveRot;
       int minTimeWaveRot;
       int maxTimeWaveRot;
       int minAmpSpecRot;
       int maxAmpSpecRot;
       int minHzSpecRot;
       int maxHzSpecRot;

};

struct t_kom_dat {						     // struk paket komunikasi
    char 		kpl[10];
    char 		iden[6];
    struct t_rute rute;                 //yg dipake inisial aja
    unsigned short 	data[ BESAR_PAKET ];
    unsigned short	cek[10];
};

struct t_detil_rotate_v
{
    int     tipe;               /* pompa, turbin, blower dst */
    int     std_alarm;          /* user defined,ISO10816-1   {0,1} */
    int     cat_alarm;          /* Class I, Class II, Class III, Class IV*/
    float   alarm_lvl[4];       /* good, satisfied, alert, danger */

    char    bearing_brand[ SIZE_UMUM ];
    char    bearing_number[ SIZE_UMUM ];
    float   fault_frek[4];         /* BPFI, BPFO, BSF, FTF */

    float   bp_count;           /*jumlah alarm band pass*/
    float   bp_fmin[6];
    float   bp_fmax[6];
    float   bp_good[6];
    float   bp_satisfied[6];
    float   bp_alert[6];
    float   bp_danger[6];
};

struct t_detil_utama {
    char no_seri[ SIZE_UMUM ];
    double rated_speed;
    double rated_power;
};


//struct dijadiin char terus jadi string?

#endif // BISA_H
