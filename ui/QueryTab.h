#ifndef CONNECTIONTAB_H
#define CONNECTIONTAB_H

#include "../src/ConnectionManager.h"

#include <QPlainTextEdit>
#include <QString>
#include <QWidget>
#include <QWidget>
#include <QSqlDatabase>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSplitter>
#include <QComboBox>

namespace Ui {
class ConnectionTab;
}

class QueryTab : public QWidget
{
	Q_OBJECT

signals:
   void textChanged();

public:
    explicit QueryTab(QString filename, ConnectionManager *connectionManager, QWidget *parent = 0);
    ~QueryTab();
    void executeQueryAtCursor(QSqlDatabase sqlDatabase);
    void executeQuery(QSqlDatabase sqlDatabase, QString query);
    QString filename() const;
    void setFilename(const QString &filename);
    bool modified() const;
    void setModified(const bool &modified);
    void readFile();
    void writeFile();

private:
    Ui::ConnectionTab *ui;
    QSqlQueryModel* m_queryResultsModel;
    QStandardItemModel* m_openConnectionsModel;
    QString m_filename;
    ConnectionManager* m_connectionManager;

public slots:
    void refreshOpenConnections();
private slots:
    void on_button_selectionQuery_released();
};

#endif // CONNECTIONTAB_H