#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QWidget>
#include <QMap>

class Utils : public QObject
{
    Q_OBJECT

public:
static QKeySequence readJson(QWidget *widget, const QString &jsonFileName, const QString &key);
    static void loadStyleSheet(const QString &qssName, QWidget *widget);

private:
};

#endif // UTILS_H
