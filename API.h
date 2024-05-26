#ifndef API_H
#define API_H
#include<QString>
#include<QStandardPaths>
#include<QDir>
#include<QJsonObject>
#include<QJsonArray>

QString TABLE_JSON = QDir::currentPath() + "/tables.json";
QString CONFIG_JSON = QDir::currentPath() + "/config.json";
QDir TABLE_JSON_QDOBJECT(TABLE_JSON);
QDir CONFIG_JSON_QDOBJECT(CONFIG_JSON);
QString ZUAN_DB = QDir::currentPath() + "/zuan.db";
QDir ZUAN_DB_QDOBJECT(TABLE_JSON);
QJsonObject time_table;
QJsonArray today_table;
#endif // API_H
