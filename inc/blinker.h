#ifndef BLINKER_H
#define BLINKER_H

#include <QObject>
#include <QTimer>

/**
 * @brief Klasa odpowiedzialna za miganie/stan kierunkowskazów
 * 
 * Klasa powiazania z QML przez Q_PROPERTY
 * Sygnaly:
 * 
 * -bool stateChanged - mowi o zalaczeniu/wylaczeniu kierunkowskazu
 * -double blinkChanged - uzywane z timerem, mruganie kierunkowskazu gdy jest zalaczony
 */
class Blinker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool state READ state WRITE newState NOTIFY stateChanged)
    Q_PROPERTY(double blinkState READ blinkState NOTIFY blinkChanged)

public:
    /**
     * @brief Konstruktor domyslny klasy, nie przyjmuje zadnych argumentow.
     * W momencie powstania obiektu, tworzy tez timer z interwalem 500ms.
     * @param parent Wskaznik na obiekt rodzica (domyslnie nullptr)
     */
    explicit Blinker(QObject* parent = nullptr);

    /**
     * @brief Zwraca wartosc boolean ktora okresla czy kierunkowskaz jest wlaczony.
     * @return true jezeli kierunkowskaz jest wlaczony, false jezeli wylaczony.
     */
    bool state() const {return currentState_; }

    /**
     * @brief Ustawia stan kierunkowskazu (czyta z CANa).
     * @param updated Nowy stan kierunkowskazu (true - wlaczony, false - wylaczony).
     */
    void newState(bool updated);

    /**
     * @brief Zwraca stan migania kierunkowskazu (gdy wlaczony).
     * @return Wartosc double ktora w frontendzie jest opacity kierunowskazow 0.0 - 1.0.
     */
    double blinkState() const { return blinkState_ ? 1.0 : 0.0; }

signals:
    /**
     * @brief (Sygnal) Emitowany, gdy zmienia się stan kierunkowskazu.
     *
     * Emitowany wewnątrz metody newState(), po ustawieniu currentState_.
     */
    void stateChanged();    
    /**
     * @brief (Sygnal) Emitowany co 500 ms podczas migania.
     *
     * Wywoływany w blinkEdit(), aby frontend (np. QML) mógł
     * odświeżyć opacity kierunkowskazów.
     */
    void blinkChanged(); 
private slots:
     /**
     * @brief Slot wywoływany przez QTimer co 500 ms.
     *
     * Zmienia wartość blinkState_ na przeciwną i emituje sygnał blinkChanged().
     */
    void blinkEdit(); 

private:
    bool currentState_; /// Aktualny stan zalaczenia kierunkowskazu
    bool blinkState_; /// Stan migania, wartosc ktora przez blinkState, przekazywana do QML jako opacity kierunkowskazow gdy sa wlaczone
    QTimer timer_; /// Timer odpowiedzialny za miganie kierunkowskazow z interwalem 500ms.
};

#endif // BLINKER_H
