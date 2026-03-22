#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QVector>
#include <QGridLayout>
#include <QIntegerForSize>
#include <vector>
#include <QStackedLayout>
#include <QSpinBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void createMembers();
    void setupLayouts();
    void makeConnections();

    void updateBalance(double newBalance);
    void generateRandomPatternForGrid();
    void updateCoff(double coff);
    void calculatingCoff();

    void setButtonColors();
    void setColorsAfterGame();

signals:
    void boxButtonClickedSignal(int index);

private slots:
    void betCashoutButtonClicked();
    void button05Clicked();
    void button2xClicked();
    void boxClicked(int index);
    void updateTime();

private:
    enum class CurrentAction
    {
        Bet,
        Cashout
    };
    enum class BoxState
    {
        Empty = 0,
        Bomb = 1,
        Star = 2,
        UnclickedBomb = 3,
        UnclickedStar = 4
    };

private:
    const int                  m_countOfBoxes = 25;
    int                        m_countOfBombs = 3;
    int                        m_countOfStars = m_countOfBoxes - m_countOfBombs;
    int                        m_currentBet = 0;
    int                        m_countOfRightClickes = 0;
    double                     m_balance = 100.;
    double                     m_coefficient = .0;
    double                     m_nextCoefficient = .0;
    std::vector<double>        m_coefficients;
    QLabel                    *m_labelOfTime = nullptr;
    QLabel                    *m_labelOfBalance = nullptr;
    QLabel                    *m_labelOfNextCoefficient = nullptr;
    QTimer                    *m_timer;
    QLineEdit                 *m_editBet = nullptr;
    QPushButton               *m_buttonToBetCashout = nullptr;
    QPushButton               *m_buttonTo05 = nullptr;
    QPushButton               *m_buttonTo2x = nullptr;
    QMessageBox               *m_messageOfVictory = nullptr;
    QMessageBox               *m_messageOfLose = nullptr;
    QMessageBox               *m_messageOfLowBalance = nullptr;
    QSpinBox                  *m_spinBoxOfBombs;

    QPalette                   m_defaultButtonColor;
    QPalette                   m_starButtonColor;
    QPalette                   m_bombButtonColor;
    QPalette                   m_unclickedStarButtonColor;
    QPalette                   m_unclickedBombButtonColor;
    QIcon                      m_defaultButtonIcon;
    QIcon                      m_starButtonIcon;
    QIcon                      m_bombButtonIcon;
    QIcon                      m_unclickedStarButtonIcon;
    QIcon                      m_unclickedBombButtonIcon;
    std::vector<QPushButton*>  m_boxes;
    std::vector<BoxState>      m_boxesValues;
    CurrentAction              m_betCashoutButtonState;

};
#endif // WIDGET_H
