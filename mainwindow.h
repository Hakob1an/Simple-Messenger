#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include "loginmanager.h"
#include "messagebubble.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDir>
#include <QLabel>
#include <QDateTime>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString username, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onLoginSuccess(const User& user);
    void onLoginFailure(const QString& message);

private slots:
    void onSendClicked();
    void onReceivedMessage(const QString &sender, const QString &message);

private:
    Client *_client;
    QTextEdit *_chatDisplay;
    QLineEdit *_messageInput;
    QPushButton *_sendButton;
    QVBoxLayout *_chatLayout;  // Holds message bubbles
    QWidget *_chatContainer;   // Container for the layout
    QScrollArea *_chatScrollArea;  // Allows scrolling through messages
};
#endif // MAINWINDOW_H
