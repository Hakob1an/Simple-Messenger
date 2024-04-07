#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent)
    , _client(new Client(username, this))
{
    _chatDisplay = new QTextEdit;
    _chatDisplay->setReadOnly(true);
    _chatDisplay->setStyleSheet("QTextEdit {"
                                "background-color: #f7f7f7;"
                                "border: 2px solid #282a36;"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "color: #282a36;"
                                "font-weight: bold;"
                                "}");

    _messageInput = new QLineEdit;
    _messageInput->setStyleSheet("QLineEdit {"
                                 "background-color: #f8f8f2;"
                                 "color: #282a36;"
                                 "font-weight: bold;"
                                 "border: 2px solid #282a36;"
                                 "border-radius: 10px;"
                                 "padding: 5px;"
                                 "}");

    QFont font("Arial", 11, QFont::TypeWriter);
    _chatDisplay->setFont(font);

    _sendButton = new QPushButton(tr("Send"));
    //_sendButton->setIcon(QIcon(":/path/to/send_icon.png")); // If you have an icon
    _sendButton->setStyleSheet("QPushButton {"
                               "background-color: #4f5578;"
                               "border: 2px solid #282a36;"
                               "border-radius: 10px;"
                               "padding: 5px;"
                               "color: white;"
                               "font-weight: bold;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #282a36;"
                               "}");


    connect(_sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);

    auto* layout = new QVBoxLayout;
    layout->addWidget(_chatDisplay);
    layout->addWidget(_messageInput);
    layout->addWidget(_sendButton);

    layout->setSpacing(5); // Reduce spacing if needed
    layout->setMargin(5); // Reduce margin if needed


    this->setStyleSheet("background-color: #ffffff;");

    auto* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(_client, &Client::receivedMessage, this, &MainWindow::onReceivedMessage);

    _client->connectToServer("localhost", 8080);
    _client->sendUsername(username);
}

MainWindow::~MainWindow()
{}

void MainWindow::onReceivedMessage(const QString &sender, const QString &message)
{
    QTextCursor cursor(_chatDisplay->document());
    cursor.movePosition(QTextCursor::End);

    QTextBlockFormat format;
    format.setAlignment(Qt::AlignLeft);
    cursor.insertBlock(format);

    QString formattedMessage = QString("<b>%1:</b> %2<br>").arg(sender.toHtmlEscaped(), message.toHtmlEscaped());
    cursor.insertHtml(formattedMessage);
    _chatDisplay->ensureCursorVisible();
}

void MainWindow::onSendClicked()
{
    QString message = _messageInput->text().toHtmlEscaped();

    if (!message.isEmpty()) {
        QTextCursor cursor(_chatDisplay->document());
        cursor.movePosition(QTextCursor::End);

        QTextBlockFormat format;
        format.setAlignment(Qt::AlignRight);
        cursor.insertBlock(format);

        QString formattedMessage = QString("<b>Me:</b> %1<br>").arg(message);
        cursor.insertHtml(formattedMessage);
        _chatDisplay->ensureCursorVisible();

        _client->sendMessage(message);
        _messageInput->clear();
    }
}

void MainWindow::onLoginSuccess(const User& user)
{
    qDebug() << "Login successful for user:" << user.getUsername();
}

void MainWindow::onLoginFailure(const QString& message)
{
    qDebug() << "Login failed:" << message;
}
