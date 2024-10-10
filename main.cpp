#include <QApplication>
#include <QPushButton>
#include "app/EpiGimp.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    EpiGimp epiGimp;

    epiGimp.run();
    return app.exec();
}
