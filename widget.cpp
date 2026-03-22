#include "widget.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QStackedWidget>
#include <random>
#include <QPixmap>
#include <QIcon>
#include <QHoverEvent>
#include <QEvent>
#include <QEnterEvent>
#include <QPalette>
#include <QColor>
#include <QRegularExpressionValidator>
#include <QTimer>
#include <QDateTime>
#include <QSpinBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_betCashoutButtonState(CurrentAction::Bet)
{
    createMembers();
    setupLayouts();
    makeConnections();
}

void Widget::createMembers()
{
    m_defaultButtonColor = QPalette();
    m_starButtonColor = QPalette();
    m_bombButtonColor = QPalette();
    m_unclickedStarButtonColor = QPalette();
    m_unclickedBombButtonColor = QPalette();

    m_defaultButtonColor.setColor(QPalette::Button, QColor(Qt::darkGray));
    m_starButtonColor.setColor(QPalette::Button, QColor(Qt::yellow));
    m_bombButtonColor.setColor(QPalette::Button, QColor(Qt::red));
    m_unclickedStarButtonColor.setColor(QPalette::Button, QColor(200, 200 , 200));
    m_unclickedBombButtonColor.setColor(QPalette::Button, QColor(255, 80, 80));

    this->setStyleSheet("QPushButton { qproperty-iconSize: 32px 32px; }");
    m_defaultButtonIcon = QIcon("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/default.png");
    m_starButtonIcon = QIcon("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/star.png");
    QPixmap starPix("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/star.png");
    m_starButtonIcon.addPixmap(starPix, QIcon::Normal, QIcon::Off);
    m_starButtonIcon.addPixmap(starPix, QIcon::Disabled, QIcon::Off);
    m_bombButtonIcon = QIcon("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/boom.png");
    m_unclickedStarButtonIcon = QIcon("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/unopenedStar.png");
    QPixmap unopenedStarPix("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/unopenedStar.png");
    m_unclickedStarButtonIcon.addPixmap(unopenedStarPix, QIcon::Normal, QIcon::Off);
    m_unclickedStarButtonIcon.addPixmap(unopenedStarPix, QIcon::Disabled, QIcon::Off);
    m_unclickedBombButtonIcon = QIcon("C:/Users/User/OneDrive/Desktop/Programming/CasinoMinesGame/bomb.png");

    m_timer = new QTimer();
    m_labelOfTime = new QLabel();
    m_labelOfBalance = new QLabel();
    m_labelOfNextCoefficient = new QLabel();

    m_editBet = new QLineEdit();
    m_buttonToBetCashout = new QPushButton();
    m_buttonToBetCashout->setFixedSize(120, 24);
    m_buttonTo05 = new QPushButton();
    m_buttonTo05->setFixedSize(58,24);
    m_buttonTo2x = new QPushButton();
    m_buttonTo2x->setFixedSize(58,24);
    m_spinBoxOfBombs = new QSpinBox();

    m_messageOfVictory = new QMessageBox();
    m_messageOfVictory -> setWindowTitle("Victory!");
    m_messageOfVictory -> setText("Congratulations! Let's continue.");
    m_messageOfVictory -> setIcon(QMessageBox::Information);
    m_messageOfVictory -> setStandardButtons(QMessageBox::Ok);

    m_messageOfLose = new QMessageBox();
    m_messageOfLose -> setWindowTitle("Boooom! Game Over!");
    m_messageOfLose -> setText("Don't worry. Let's try again:)");
    m_messageOfLose -> setIcon(QMessageBox::Information);
    m_messageOfLose -> setStandardButtons(QMessageBox::Ok);

    m_messageOfLowBalance = new QMessageBox();
    m_messageOfLowBalance -> setWindowTitle("Warning!");
    m_messageOfLowBalance -> setText("Your balance is low.");
    m_messageOfLowBalance -> setIcon(QMessageBox::Warning);
    m_messageOfLowBalance -> setStandardButtons(QMessageBox::Ok);

    m_boxes.resize(m_countOfBoxes);
    for(int index = 0; index < m_countOfBoxes; index++)
    {
        m_boxes[index] = new QPushButton("");
        m_boxes[index]->setFixedSize(50, 50);
        m_boxes[index]->setDisabled(true);
    }


}

void Widget::updateTime() {
    QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss AP");
    m_labelOfTime->setText(currentTime);
    m_timer->start(1000);
}

void Widget::setupLayouts()
{

    m_spinBoxOfBombs->setRange(3, 24);
    m_countOfBombs = m_spinBoxOfBombs->value();

    calculatingCoff();

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout -> addWidget(m_labelOfTime);
    upperLayout->addWidget(m_spinBoxOfBombs);
    upperLayout -> addWidget(m_labelOfBalance);
    mainLayout -> addLayout(upperLayout);

    QGridLayout *boxesLayout = new QGridLayout();
    boxesLayout -> setSpacing(5*5);

    for(int i = 0; i < m_countOfBoxes; ++i)
    {
        boxesLayout->addWidget(m_boxes[i], i / 5, i % 5);
    }

    boxesLayout -> setSpacing(0);
    mainLayout -> addLayout(boxesLayout);

    m_editBet->setPlaceholderText("Amount Of Bet");

    QHBoxLayout *downLayout = new QHBoxLayout();
    downLayout -> addWidget(m_labelOfNextCoefficient);
    downLayout -> addWidget(m_buttonToBetCashout);
    mainLayout -> addLayout(downLayout);

    QHBoxLayout *downLayout1 = new QHBoxLayout();
    downLayout1 -> addWidget(m_editBet);
    m_editBet->setValidator(new QIntValidator(1, 999));

    downLayout1 -> addWidget(m_buttonTo05);
    downLayout1 -> addWidget(m_buttonTo2x);
    mainLayout -> addLayout(downLayout1);
    m_labelOfBalance -> setText("Balance: $" + QString::number(m_balance));

    m_coefficient = m_coefficients[1];
    m_nextCoefficient = m_coefficients[m_countOfRightClickes + 1] * 0.9;

    m_labelOfNextCoefficient -> setText("Next: " + QString::number(std::ceil(m_nextCoefficient * 100.0) / 100.0) + "x");

    m_buttonToBetCashout -> setText("BET");

    m_buttonTo05 -> setText("1/2");
    m_buttonTo2x -> setText("2X");

    updateTime();
    setButtonColors();
    setLayout(mainLayout);
}

void Widget::updateBalance(double newBalance)
{
    m_balance = newBalance;
    m_labelOfBalance -> setText("Balance: $" + QString::number(m_balance));

}

void Widget::calculatingCoff()
{
    m_coefficients.clear();
    m_countOfBombs = m_spinBoxOfBombs->value();
    m_countOfStars = m_countOfBoxes - m_countOfBombs;

    m_coefficients.push_back(1.);
    m_coefficients.push_back(1. * (m_countOfBoxes * 1.)/(m_countOfStars * 1.));

    for(int i = 2; i < m_countOfStars + 1; i++)
    {
        double c = ((m_countOfBoxes - (i - 1)) * 1.) / ((m_countOfStars - (i - 1))) * 1.;
        m_coefficients.push_back(m_coefficients[i - 1] * c);
    }
    updateCoff(m_coefficients[1]);
}

void Widget::generateRandomPatternForGrid()
{
    m_boxesValues = std::vector<BoxState>(m_countOfBoxes, BoxState::UnclickedStar);
    std::vector<int> v(m_countOfBoxes, 0);
    for(int i = 0; i < m_countOfBoxes; ++i)v[i] = i;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    for(int i = 0; i < m_countOfBombs; ++i)
    {
        m_boxesValues[v[i]] = BoxState::UnclickedBomb;
    }
}

void Widget::updateCoff(double coff)
{
    m_coefficient = coff;
    m_nextCoefficient = m_coefficients[m_countOfRightClickes + 1] * 0.9;
    m_labelOfNextCoefficient -> setText("Next: " + QString::number((std::ceil(m_nextCoefficient * 100.0) / 100.0)) + "x");

    if(m_betCashoutButtonState == CurrentAction::Cashout){
        int bet = m_editBet -> text().toInt();
        m_buttonToBetCashout->setText("Cashout: $" + QString::number(m_coefficient * bet));
    }

}
void Widget::setButtonColors()
{
    for(size_t i = 0; i < m_boxes.size(); ++i)
    {
        if(i >= m_boxesValues.size() || m_boxesValues[i] != BoxState::Star)
        {
            m_boxes[i]->setPalette(m_defaultButtonColor);
            m_boxes[i]->setIcon(QIcon(m_defaultButtonIcon));
        }
        else
        {
            m_boxes[i]->setPalette(m_starButtonColor);
        }
    }
}

void Widget::boxClicked(int index)
{
    if(m_boxesValues[index] == BoxState::UnclickedBomb)
    {
        m_boxesValues[index] = BoxState::Bomb;
        m_boxes[index]->setPalette(m_bombButtonColor);
        m_boxes[index]->setIcon(m_bombButtonIcon);
        m_countOfRightClickes = 0;
        updateCoff(m_coefficients[1]);
        m_betCashoutButtonState = CurrentAction::Bet;
        m_buttonToBetCashout->setText("BET");
        m_buttonToBetCashout->setEnabled(true);
        setColorsAfterGame();
        m_messageOfLose->exec();
        m_editBet->setEnabled(true);
        m_buttonTo05->setEnabled(true);
        m_buttonTo2x->setEnabled(true);
        m_spinBoxOfBombs->setEnabled(true);
        for(int i = 0; i < m_countOfBoxes; i++){
            m_boxes[i]->setDisabled(true);
        }
        return;
    }

    m_boxesValues[index] = BoxState::Star;
    m_boxes[index]->setPalette(m_starButtonColor);
    m_boxes[index]->setIcon(m_starButtonIcon);//////
    m_boxes[index]->setDisabled(true);
    m_countOfRightClickes++;
    m_buttonToBetCashout->setEnabled(true);
    updateCoff(m_coefficients[m_countOfRightClickes] * 0.9);
    if(m_countOfRightClickes == m_countOfStars){
        m_buttonToBetCashout->click();
        m_editBet->setEnabled(true);
        m_buttonTo05->setEnabled(true);
        m_buttonTo2x->setEnabled(true);
        m_spinBoxOfBombs->setEnabled(true);
    }
}

void Widget::makeConnections()
{
    for(int i = 0; i < m_countOfBoxes; ++i)
    {
        QObject::connect(m_boxes[i], &QPushButton::clicked, this, [this, i]
        {
            emit boxButtonClickedSignal(i);
        });
    }
    QObject::connect(m_buttonToBetCashout, &QPushButton::clicked, this, &Widget::betCashoutButtonClicked);
    QObject::connect(m_buttonTo05, &QPushButton::clicked, this, &Widget::button05Clicked);
    QObject::connect(m_buttonTo2x, &QPushButton::clicked, this, &Widget::button2xClicked);
    QObject::connect(this, &Widget::boxButtonClickedSignal, this, &Widget::boxClicked);
    QObject::connect(m_timer, &QTimer::timeout, this, &Widget::updateTime);
    QObject::connect(m_spinBoxOfBombs, &QSpinBox::valueChanged, this, &Widget::calculatingCoff);
}

void Widget::betCashoutButtonClicked()
{
    if(m_betCashoutButtonState == CurrentAction::Bet)
    {
        m_currentBet = m_editBet->text().toInt();
        if(m_currentBet > m_balance)
        {
            m_messageOfLowBalance -> exec();
            return;
        }
        if(m_currentBet == 0)
        {
            return;
        }
        for(int i = 0; i < m_countOfBoxes; i++){
            m_boxes[i]->setEnabled(true);
        }
        m_editBet->setDisabled(true);
        m_buttonTo2x->setDisabled(true);
        m_buttonTo05->setDisabled(true);
        m_spinBoxOfBombs->setDisabled(true);
        updateBalance(m_balance - m_currentBet);
        generateRandomPatternForGrid();

        setButtonColors();

        m_betCashoutButtonState = CurrentAction::Cashout;

        m_buttonToBetCashout->setDisabled(true);
        m_buttonToBetCashout->setText("Cashout: $" + QString::number(0.9 * m_coefficient * m_currentBet));
    }
    else if(m_betCashoutButtonState == CurrentAction::Cashout)
    {
        m_betCashoutButtonState = CurrentAction::Bet;
        m_buttonToBetCashout->setText("BET");
        for(int i = 0; i < m_countOfBoxes; i++){
            m_boxes[i]->setDisabled(true);
        }
        m_editBet->setEnabled(true);
        m_buttonTo05->setEnabled(true);
        m_buttonTo2x->setEnabled(true);
        m_spinBoxOfBombs->setEnabled(true);
        m_boxesValues.clear();
        updateBalance(m_balance + m_coefficient * m_currentBet);
        m_currentBet = 0;
        m_countOfRightClickes = 0;
        updateCoff(m_coefficients[1]);
        setColorsAfterGame();
        m_messageOfVictory->exec();
    }
}

void Widget::button05Clicked()
{
    int bet = m_editBet->text().toInt();
    bet /= 2;
    if(bet < 1)bet = 1;
    m_editBet -> setText(QString::number(bet));
}

void Widget::button2xClicked()
{
    int bet = m_editBet -> text().toInt();
    bet *= 2;
    if(bet > 999)bet = 999;
    m_editBet -> setText(QString::number(bet));
}

void Widget::setColorsAfterGame()
{
    for(int i = 0; i < m_countOfBoxes; i++){
        if(m_boxesValues[i] == BoxState::UnclickedStar){
            m_boxes[i]->setPalette(m_unclickedStarButtonColor);
            m_boxes[i]->setIcon(m_unclickedStarButtonIcon);
        }
        if(m_boxesValues[i] == BoxState::UnclickedBomb){
            m_boxes[i]->setPalette(m_unclickedBombButtonColor);
            m_boxes[i]->setIcon(m_unclickedBombButtonIcon);
        }
    }
}


Widget::~Widget()
{
}

