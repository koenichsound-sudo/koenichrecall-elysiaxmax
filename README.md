# Koenich Recall – elysia xMax V1.0.2

Native macOS Apple Silicon VST3 für REAPER. 12 Regler und drei Toggle-Taster speichern Hardware-Einstellungen im Projekt. Kein DSP, keine Hardware-Steuerung, kein Hintergrunddienst. Die vom Nutzer hochgeladene Frontplatten-Grafik ist unverändert eingebettet; LED-Meter sind rein statisch.

## Fertiges Plugin installieren

Das mitgelieferte Bundle `Koenich Recall - elysia xMax.vst3` nach `~/Library/Audio/Plug-Ins/VST3/` kopieren (Ordner gegebenenfalls anlegen). REAPER nativ auf Apple Silicon starten, unter Einstellungen → Plug-ins → VST neu scannen und das Plugin als Track-FX hinzufügen. Mindestversion macOS 12. Das Bundle ist lokal ad-hoc signiert, nicht Apple-notarisiert.

## Bedienung

- Vertikal ziehen oder Mausrad: Wert ändern. Shift beim Ziehen: feinere Bewegung.
- Über dem Regler verweilen oder ziehen: aktuellen Wert anzeigen.
- Doppelklick: Zahl eingeben, Return übernehmen, Escape abbrechen. Dezimalpunkt verwenden.
- LOWMO, PUNCH, HIT IT!: klicken zum Umschalten; grün bedeutet ein.
- Fenster proportional skalierbar. Die Originalvorlage ist eine vertikale Frontplatte.
- REAPER-Projekt speichern: alle 15 Werte werden im Plugin-State mitgespeichert. Auch REAPER-FX-Presets können diesen Zustand sichern.

| Regler | Bereich | Startwert |
|---|---|---|
| Link | 0–100 % | 0 % |
| Tone | −8 bis +8 | 0 |
| Mid Thres | 0–100 % | 0 % |
| Mid Gain | −12 bis +12 dB | 0 dB |
| Side Thres | 0–100 % | 0 % |
| Side Gain | −12 bis +12 dB | 0 dB |
| Low Thres | 0–100 % | 0 % |
| Low Gain | −12 bis +12 dB | 0 dB |
| X-Freq | 40–470 Hz | 140 Hz |
| S-Clip | 0–100 % | 0 % |
| Time | 10–1300 ms | 180 ms |
| Level | −12 bis +12 dB | 0 dB |

Alle Taster starten ausgeschaltet. X-Freq wird logarithmisch abgebildet. Time verwendet eine stückweise logarithmische Kennlinie entlang der gedruckten Skalenpunkte (10, 20, 180, 400, 900 ms), mit 1300 ms am rechten Anschlag. 180 ms steht genau oben mittig. Maßgeblich für präzise Werte ist die numerische Anzeige. Gain/Tone/Prozent: Schritte von 0,1; Hz/ms: ganze Zahlen.

## Aus dem Quellcode bauen

Voraussetzungen: Apple Silicon Mac, Xcode Command Line Tools (`xcode-select --install`), CMake ≥3.22, Git und Internet beim ersten Konfigurieren. JUCE 8.0.15 wird automatisch heruntergeladen. Kein Projucer nötig.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build --config Release --parallel 4
ctest --test-dir build --output-on-failure
```

Ergebnis: `build/KoenichRecall_artefacts/Release/VST3/Koenich Recall - elysia xMax.vst3`

Optional vorhandenes JUCE verwenden: `-DJUCE_SOURCE_DIR=/absoluter/pfad/JUCE`. Referenz-Commit: `91ad83ae34a81e0833b1a2b0866f54846370ae53` (Tag 8.0.15). Tests abschalten: `-DRECALL_BUILD_TESTS=OFF`.

```sh
codesign --force --deep --sign - 'build/KoenichRecall_artefacts/Release/VST3/Koenich Recall - elysia xMax.vst3'
mkdir -p "$HOME/Library/Audio/Plug-Ins/VST3"
ditto 'build/KoenichRecall_artefacts/Release/VST3/Koenich Recall - elysia xMax.vst3' "$HOME/Library/Audio/Plug-Ins/VST3/Koenich Recall - elysia xMax.vst3"
```

## Aufbau und Prüfung

`Source/Parameters.h`: stabile Parameter-IDs, Bereiche, Startwerte und Positionen. IDs und Plugin-Codes bei Updates unverändert lassen, damit alte Projekte laden.

`PluginProcessor`: AudioProcessorValueTreeState und XML-State; übereinstimmende Eingangs-/Ausgangsbelegung mit 1–64 Kanälen; Float/Double-Prozessblöcke ohne Sample-Manipulation, Latenz oder Audioanalyse. Keine MIDI-Ports.

`PluginEditor`: eingebettete PNG-Vorlage, JUCE-Regler/Taster und Parameter-Attachments. Keine extern benötigten Grafikdateien zur Laufzeit.

`Tests/RecallTests.cpp`: 15 Parameter, Wertebereiche, Recall in neuer Instanz, defekte Zustandsdaten, Bus-Layouts und bitgenaue Float-/Double-Durchleitung. Ein optionaler absoluter PNG-Pfad als Argument erzeugt ein Bildschirmabbild der tatsächlichen JUCE-Oberfläche.

Manueller REAPER-Abnahmetest: alle Regler/Taster verändern, Projekt speichern, REAPER schließen, Projekt erneut öffnen und Werte vergleichen. Zwei Instanzen mit unterschiedlichen Werten prüfen. Audio bei veränderten Werten per Nulltest mit dem Original vergleichen. Diese Host-Prüfung ergänzt die automatischen Prozessortests.

## Abhängigkeiten und Bildmaterial

JUCE: https://github.com/juce-framework/JUCE/tree/8.0.15 (Lizenzbedingungen dort). Das VST3-SDK wird durch JUCE eingebunden. Die Nutzer-Vorlage `Assets/frontpanel.png` enthält elysia-Bezeichnungen; es wird keine Verbindung zum Hardwarehersteller behauptet. Rechte an der Vorlage und Drittanbieterkomponenten bleiben bei den jeweiligen Rechteinhabern. Für eine Weiterveröffentlichung die mitgelieferten Drittanbieter-Lizenzen beachten.

## Änderung in V1.0.1

Drehwinkel aller zwölf Regler von 270° auf 300° erweitert (je 15° weiter an beiden Enden), passend zu den äußeren Skalenmarkierungen. Wertebereiche, Parameter-IDs und gespeicherte Projektzustände bleiben unverändert.

## Änderung in V1.0.2

Time: 10–1300 ms (1,3 s); Standardwert 180 ms exakt in Mittelstellung. Vorhandene Plugin-Zustände speichern absolute Millisekunden und bleiben erhalten. Bereits aufgezeichnete Time-Automationskurven verwenden dagegen normalisierte Werte und können durch die neue Kennlinie andere Zeiten ergeben; diese bei alten Projekten kontrollieren.

## GitHub

Dieser Ordner ist der Repository-Inhalt. Build-Dateien werden ignoriert. Abhängigkeiten werden beim Konfigurieren geladen; keine lokalen Rechnerpfade sind erforderlich. Vor öffentlicher Veröffentlichung eine Lizenz für den eigenen Quellcode wählen und die Nutzungsrechte an der Frontplatten-Grafik klären; Drittanbieter-Lizenzen liegen unter `ThirdParty/`. Das Repository enthält aktuell keine eigene Lizenzfreigabe.
