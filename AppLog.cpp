#include"AppLog.h"



void showLog(const char* LogText,LogStatus LogSt){
    QString CurrentTime = QTime::currentTime().toString("hh:mm:ss.zzz");
    if (LogSt == LogStatus::ALL){
        cout << RESET << "[" << CurrentTime.toStdString() << "] " << LogText << endl;
    }else if (LogSt == LogStatus::DEBUG){
        cout << RESET << "[" << CurrentTime.toStdString() << "] DEBUG: " << LogText << endl;
    }else if (LogSt == LogStatus::INFO){
        cout << GREEN << "[" << CurrentTime.toStdString() << "] INFO: " << LogText << endl;
    }else if (LogSt == LogStatus::WARN){
        cout << YELLOW << "[" << CurrentTime.toStdString() << "] WARN: " << LogText << endl;
    }else if (LogSt == LogStatus::ERR){
        cout << RED << "[" << CurrentTime.toStdString() << "] ERR: " << LogText << endl;
    }else if (LogSt == LogStatus::EXIT){
        cout << YELLOW << "[" << CurrentTime.toStdString() << "] EXIT: " << LogText << endl;
    }

}
