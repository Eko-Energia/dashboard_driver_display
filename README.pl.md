<div align="center">

[🇬🇧 English](README.md) · **🇵🇱 Polski**

# Perła — Driver Display

**Cyfrowy ekran kierowcy (Qt/QML) dla pojazdu elektrycznego *Perła***

[![Qt](https://img.shields.io/badge/Qt-6.9.3-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Raspberry%20Pi-blue?logo=linux&logoColor=white)](#)

<img width="1600" height="600" alt="dashboard-mock-up" src="https://github.com/user-attachments/assets/44e8a73c-0876-4c98-b29a-63b999ad8bc5" />

</div>

---

## Opis

Ekran kierowcy pojazdu elektrycznego **Perła**, tworzonego przez koło naukowe **Eko-Energia AGH**. Wyświetla telemetrię na żywo jako bezramkowy pulpit 1600×600 o stałym układzie.

Aplikacja nie komunikuje się z magistralą CAN bezpośrednio. Korzysta z dwóch strumieni WebSocket:

- **`ws://localhost:8080`** — ramki CAN, z [dbc-can-bridge](https://github.com/Eko-Energia/dbc-can-bridge)
- **`ws://localhost:8081`** — telemetria z GPS-a i Raspberry Pi (prędkość, przebieg, energia, kody błędów), z [rpi_utilities](https://github.com/Eko-Energia/rpi_utilities)

Oba serwisy **muszą działać**, żeby na ekranie pojawiły się dane. Każde z gniazd samo ponawia próbę połączenia co sekundę po rozłączeniu.

## Co pokazuje

- Prędkościomierz (0–140 km/h) z trybem jazdy PRND
- Dwukierunkowy miernik mocy (−10…20 kW, wartości ujemne = rekuperacja)
- Stan naładowania baterii — świecący łuk wraz z odczytem liczbowym
- Światła (postojowe / mijania / drogowe), awaryjne i kierunkowskazy
- Popup błędów — aktywne kody błędów, każdy wygasa po 60 s
- Dane podróży — średnie zużycie energii i całkowity przebieg
- Data i godzina

## Wymagania

**Do uruchomienia**

- Linux z obsługą SocketCAN
- [dbc-can-bridge](https://github.com/Eko-Energia/dbc-can-bridge) — bramka CAN → WebSocket, port `8080`
- [rpi_utilities](https://github.com/Eko-Energia/rpi_utilities) — usługa telemetryczna, port `8081`

**Do kompilacji**

- CMake 3.16 lub nowszy
- **Qt dokładnie w wersji 6.9.3** (`find_package` wymaga `EXACT`), moduły `Quick`, `WebSockets`, `Core5Compat`
- Kompilator C++17
- Do kompilacji skrośnej: `aarch64-linux-gnu-gcc` / `g++`, Qt zbudowane pod ARM oraz sysroot Raspberry Pi

## Konfiguracja subskrypcji

Aplikacja subskrybuje tylko te ramki CAN, których potrzebuje. Lista znajduje się w [subs.txt](subs.txt), jedna ramka na linię:

```
NAZWA_RAMKI|SYGNAL_1,SYGNAL_2,SYGNAL_3
```

Puste linie i linie zaczynające się od `#` są pomijane. Plik jest osadzony jako zasób Qt, więc **jego edycja wymaga ponownej kompilacji**.

## Znane ograniczenia

- Stan naładowania to liniowe przybliżenie z napięcia — `(U − 63) / 24 × 100` — rozwiązanie tymczasowe, dopóki BMS nie udostępni właściwego oszacowania.
- Układ jest przypięty do 1600×600 z pozycjonowaniem absolutnym, dokładnie pod fizyczny wyświetlacz.
- Oba adresy WebSocket są wpisane na sztywno w [main.cpp](src/main.cpp).
- Rząd ostrzeżeń, wskaźnik tempomatu i odczyt temperatury zewnętrznej są obecne w źródłach, ale wyłączone do czasu pojawienia się źródeł danych.

## Autorzy

**Autor** — Igor Lelito · Eko-Energia AGH

Krój pisma: [Oxanium](https://fonts.google.com/specimen/Oxanium), na licencji SIL Open Font License ([OFL.txt](fonts/OFL.txt)).
