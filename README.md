# Test Sensore Umidità Terreno (Capacitivo v1.2) 🌱

Questo progetto contiene lo script di test e diagnostica per un **Capacitive Soil Moisture Sensor v1.2** utilizzando una scheda **Arduino Mega 2560 Pro**. 

Il codice legge i valori analogici del sensore, esegue una diagnostica di base (per rilevare eventuali cortocircuiti o disconnessioni) e mappa i valori grezzi in una percentuale di umidità (0% - 100%) facilmente leggibile sul monitor seriale.

## 🛠️ Hardware Necessario

* **Microcontrollore:** Arduino Mega 2560 Pro (o compatibile, es. Arduino Mega 2560 standard).
* **Sensore:** Capacitive Soil Moisture Sensor v1.2.
* **Cavi:** Jumper femmina-femmina o maschio-femmina a seconda dei pin saldati sulla scheda.

## 🔌 Schema di Collegamento

Il collegamento tra il sensore e la scheda Arduino è molto semplice:

| Sensore Capacitivo (Pin) | Arduino Mega 2560 Pro (Pin) |
| :--- | :--- |
| **VCC** | 5V (o 3.3V) |
| **GND** | GND |
| **AOUT** | **A0** (Pin Analogico) |

## 💻 Ambiente di Sviluppo

Questo progetto è stato configurato per essere utilizzato con **Visual Studio Code** e l'estensione **PlatformIO IDE**.

1. Clona questo repository sul tuo computer.
2. Apri la cartella del progetto `test-humid-sensor` con Visual Studio Code.
3. PlatformIO scaricherà automaticamente le dipendenze e configurerà l'ambiente per il framework Arduino (`megaatmega2560`).
4. Usa il pulsante **Upload (freccia verso destra)** nella barra di stato di PlatformIO per compilare e caricare il codice.
5. Apri il **Serial Monitor (icona a forma di spina elettrica)** impostato a `9600 baud` per leggere i dati.

## ⚙️ Calibrazione del Sensore

I sensori capacitivi restituiscono un valore analogico che *diminuisce* all'aumentare dell'umidità. I valori di calibrazione predefiniti in questo script sono stati testati empiricamente:

* **Valore Asciutto (Sensore all'aria aperta):** ~570
* **Valore Bagnato (Sensore immerso in acqua o stretto nel palmo):** ~215

Nel codice `src/main.cpp`, la funzione `map()` viene utilizzata per invertire e trasformare questa scala in una percentuale da 0% (secco) a 100% (saturo d'acqua).

```cpp
// Esempio di mappatura utilizzata nel codice:
int percentuale = map(valoreGrezzo, 570, 215, 0, 100);
percentuale = constrain(percentuale, 0, 100);
```

> **Nota:** I valori possono variare leggermente a seconda della tensione di alimentazione (5V vs 3.3V) e delle tolleranze di fabbricazione del sensore. Se necessario, aggiorna i valori `570` e `215` nel codice in base alle tue letture.

## ⚠️ Diagnostica Integrata

Il codice include controlli di sicurezza:
* Se il valore letto è `<= 5`: Possibile cortocircuito a massa o pin scollegato.
* Se il valore letto è `>= 1020`: Circuito aperto, cavo del segnale interrotto o sensore guasto.