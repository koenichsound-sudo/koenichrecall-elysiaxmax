# Prüfbericht – Version 1.0.2

- Native Release-Kompilierung auf macOS mit Apple Clang 17, Ziel ARM64/macOS 12+ erfolgreich.
- JUCE 8.0.15, Commit 91ad83ae34a81e0833b1a2b0866f54846370ae53.
- VST3-Bundle inklusive Factory-Metadaten erfolgreich erzeugt.
- 15 Parameter vorhanden; alle 12 Regler-Minima/Maxima geprüft.
- Zustands-Roundtrip in neue Prozessorinstanz bestanden, einschließlich drei eingeschalteter Toggle-Taster.
- Ungültiger Zustandsblock verändert bestehende Werte nicht.
- Alle 12 GUI-Regler: GUI → Parameter und Parameter → GUI geprüft.
- Alle drei GUI-Taster: aus/ein → Parameter geprüft.
- Bitgenaue Audiodurchleitung: Float und Double; 1, 2, 8, 64 Kanäle; Blockgrößen 0, 1, 64, 1024.
- Unterschiedliche Eingangs-/Ausgangsbelegung wird abgelehnt.
- Tatsächliche JUCE-GUI als PNG gerendert und visuell mit der Vorlage verglichen.
- Lokale Ad-hoc-Signatur des ausgelieferten Bundles verifiziert.

Noch nicht durchgeführt: manueller Scan, Interaktion und Projekt-Neuladen innerhalb von REAPER; Apple-Notarisierung. Keine Installation in die persönliche Plugin-Bibliothek vorgenommen.

## Winkelkorrektur 1.0.1

Alle zwölf Regler: 300° statt 270° Drehbereich. Neue JUCE-Ansicht gerendert und Endstellung visuell geprüft; bestehende automatische Prüfungen erneut bestanden. Der Nutzer hat die grundsätzliche Funktion der vorherigen Version in REAPER bestätigt.

## Time-Korrektur 1.0.2

180 ms = normalisierte Position 0,5; Endpunkte 10/1300 ms. Kennlinie für jeden ganzzahligen Millisekundenwert auf Monotonie und Umkehrbarkeit geprüft. Frühere absolute State-Werte 180 und 1000 ms werden erhalten. Neue Default-GUI gerendert; Zeiger bei 180 ms visuell bestätigt.
