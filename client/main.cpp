#include <QCoreApplication>
#include <QApplication>
#include <mainwindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // absl::ParseCommandLine(argc, argv);
    MainWindow w;
    //w.cek_data(0,0,0,0);
    w.show();
    return a.exec();
}
