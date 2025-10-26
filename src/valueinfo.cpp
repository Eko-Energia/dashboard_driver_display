#include "valueinfo.h"

ValueInfo::ValueInfo(QMetaType type, QVariant defaultValue, QObject *parent) : QObject(parent) , type_(type), value_(defaultValue) {
    //std::cout << "Utworzono ValueInfo dla typu: " << type_.name() << std::endl; //DEBUG
}

void ValueInfo::setValue(QVariant newValue){
    

    if (!newValue.canConvert(type_)) { // Sprawdza czy da sie przekonwertowac
            std::cout << "Nie mozna przekonwertowac" << newValue.typeName() << "na" << type_.name() << std::endl;
            return;
    }


    newValue.convert(type_); // Konwertuje na odpowiedni typ

    

    if( newValue == value_ ) {return;} // Sprawdza czy wartosc jest nowa

    value_ = newValue;

    emit valueChanged();

}


void ValueInfo::setGear(uint newGear){
    
    switch(newGear){
        case 0: value_ = "P"; break;
        case 1: value_ = "R"; break;
        case 2: value_ = "N"; break;
        case 3: value_ = "D"; break;
        default: value_ = "-"; break; // Jak nie ma biegu to -
    }

    emit valueChanged();
}