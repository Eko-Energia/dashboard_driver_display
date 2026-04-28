#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QJsonObject>
#include <QString>

class CANsignal{
    public:
        explicit CANsignal(QString name, QString value="0"): name_(name), value_(value){}
        CANsignal() : name_(""), value_("0"){}

        QString getName() const{return name_;}
        QString getValue() const{return value_;}

        void updateValue(const QString& newValue){value_ = newValue;}

        friend QDebug operator<<(QDebug dbg, const CANsignal &signal){
            dbg.nospace() << "CANsignal(Name:" << signal.name_ << ", Value:" << signal.value_ << ")";
            return dbg;
        }

        friend bool operator==(QString string, const CANsignal &signal){return string == signal.name_;}

    private:
        QString name_;
        QString value_;

};

class CANframe{
    public:
        explicit CANframe(QString name): name_(name){}
        CANframe() : name_(""),signals_(QHash<QString,CANsignal>()){}
        QString getName() const{return name_;}

        // Potrzebna jedynie metoda dodajaca bo ramki dodawane sa raz na sztywno w trakcie pracy nie bedziemy ich zmieniac, w razie czego przekompilowac
        void updateSignal(const QString& signalName, const QString& value){
            if(signals_.contains(signalName)){
                signals_[signalName].updateValue(value);
            }
            else{
                qDebug() << "Ramka" << name_ << "nie zawiera sygnalu o nazwie:" << signalName;
            }
        }

        bool containsSignal(const QString& signalName) const{return signals_.contains(signalName);}

        QString getSigVal(const QString& signalName) const{
            if(signals_.contains(signalName)){
                return signals_[signalName].getValue();
            }
            else{
                qDebug() << "Ramka" << name_ << "nie zawiera sygnalu o nazwie:" << signalName;
                return QString();
            }
        }

        void addSignal(const CANsignal& signal){signals_.insert(signal.getName(), signal);}

        friend QDebug operator<<(QDebug dbg, const CANframe &frame){
            dbg.nospace() << "CANframe\n" << "{\n" << "\tName: " << frame.name_ << "\n\tSignals: ";
            for (auto it = frame.signals_.cbegin(); it != frame.signals_.cend(); ++it) {
                dbg.nospace() << "\n\t\t" << it.value();
            }
            dbg.nospace() << "\n}";
            return dbg;
        }

        friend bool operator==(QString string, const CANframe &frame){return string == frame.name_;}

    private:
        QString name_;
        QHash<QString,CANsignal> signals_;

};

QJsonObject text_to_JSON(const QString& message);
CANframe parseLine(const QString& line);
QList<CANframe> loadSubscriptions(); 

#endif // FUNCTIONS_H
