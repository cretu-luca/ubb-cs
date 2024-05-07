#include "gui.h"
#include "adminGUI.h"

MainWidget::MainWidget(QWidget* parent): QWidget(parent) {
    this->selectUserButton = new QPushButton;
    this->selectAdminButton = new QPushButton;
    this->HTMLButton = new QPushButton;
    this->CSVButton = new QPushButton;

    this->controller = nullptr;
    this->resize(800, 800);

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->setSpacing(10);
    this->mainLayout->setContentsMargins(10, 10, 10, 10);
    this->setLayout(mainLayout);

    this->setUpController();
}

void MainWidget::setUpController() {
    this->setWindowTitle("Select filetype");

    this->HTMLButton = new QPushButton("HTML", this);
    this->HTMLButton->resize(100, 100);
    this->HTMLButton->setGeometry(150, 300, 200, 200);
    this->HTMLButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->HTMLButton->setFixedSize(buttonSize);
    connect(this->HTMLButton, &QPushButton::clicked, this, &MainWidget::setUpHTMLController);

    this->CSVButton = new QPushButton("CSV", this);
    this->CSVButton->resize(100, 100);
    this->CSVButton->setGeometry(450, 300, 200, 200);
    this->CSVButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->CSVButton->setFixedSize(buttonSize);
    connect(this->CSVButton, &QPushButton::clicked, this, &MainWidget::setUpCSVController);

    this->mainLayout->addWidget(this->HTMLButton);
    this->mainLayout->addWidget(this->CSVButton);
}

void MainWidget::selectProfile() {
    this->setWindowTitle("Select profile");

    this->selectUserButton = new QPushButton("User", this);
    this->selectUserButton->resize(100, 100);
    this->selectUserButton->setGeometry(150, 300, 200, 200);
    this->selectUserButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->selectUserButton->setFixedSize(buttonSize);
    connect(this->selectUserButton, &QPushButton::clicked, this, &MainWidget::selectUser);

    this->selectAdminButton = new QPushButton("Admin", this);
    this->selectAdminButton->resize(100, 100);
    this->selectAdminButton->setGeometry(450, 300, 200, 200);
    this->selectAdminButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->selectAdminButton->setFixedSize(buttonSize);
    connect(this->selectAdminButton, &QPushButton::clicked, this, &MainWidget::selectAdmin);

    this->mainLayout->removeWidget(this->HTMLButton);
    this->mainLayout->removeWidget(this->CSVButton);
    this->mainLayout->addWidget(selectUserButton);
    this->mainLayout->addWidget(selectAdminButton);

    this->selectUserButton->show();
    this->selectAdminButton->show();
}

void MainWidget::selectUser() {
    // auto userMenuWidget = new UserMenuWidget;
    // userMenuWidget->show();
}

void MainWidget::selectAdmin() {
    this->close();
    auto adminMenuWidget = new AdminMenuWidget(nullptr, this->controller);
    adminMenuWidget->show();
}

void MainWidget::setUpHTMLController() {
    this->HTMLButton->hide();
    this->CSVButton->hide();
    this->controller = new Controller(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\movies.html)", "HTML");
    this->selectProfile();
}

void MainWidget::setUpCSVController () {
    this->HTMLButton->hide();
    this->CSVButton->hide();
    this->controller = new Controller(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\movies.csv)", "CSV");
    this->selectProfile();
}
