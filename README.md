## Ekran Kierowcy

Program służy do wyświetlania danych przesyłanych przez magistralę CAN w czytelnej formie dla kierowcy, informujących o aktualnym stanie pojazdu Perła.


<h1 align="center"><strong>Obecna wersja ekranu</strong></h1>
<img width="1600" height="600" alt="dashboard-mock-up" src="https://github.com/user-attachments/assets/44e8a73c-0876-4c98-b29a-63b999ad8bc5" />

## Funkcje
- Wysyłanie subskrypcji ramek do serwera
- Odbiór JSON-ów i ich parsowanie
- Aktualizacja i wyświetlanie odbieranych danych

## Wymogi do uruchomienia

System linux z obsługą sieci CAN (socketcan)

Aplikacja odbierająca ramki CAN, [can-receiver](https://github.com/Eko-Energia/Perla-Monitor/tree/main/can-receiver) 

Opcjonalnie : do symulacji ramek na vcan [perla-bus](https://github.com/Eko-Energia/Perla-Monitor/tree/main/perla-bus)

## Wymogi do kompilacji

CMake 3.16+

Qt 6.8 +

Kompilator C++ ze standardem C17



<br>
<br>
<br>
<br>
<br>
<br>
Autor - Igor Lelito
