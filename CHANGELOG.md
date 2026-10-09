# Changelog

## 1.0.2
- Time: 10–1300 ms statt 10–1000 ms.
- 180 ms als Standardwert exakt auf 12 Uhr.
- Zeitkennlinie an die gedruckten 10/20/180/400/900-ms-Skalenpunkte angepasst.
- Tests für Endpunkte, Mittelstellung, monotone Kennlinie, Umkehrung und frühere absolute Recall-Werte.
- Kompatibilität: Parameter-IDs bleiben erhalten. Absolute State-Werte bleiben erhalten; normalisierte Time-Automation ändert durch die neue Kennlinie ihre Bedeutung.

## 1.0.1
- Drehbereich aller zwölf Regler von 270° auf 300° erweitert.

## 1.0.0
- Erste native macOS-ARM64-VST3-Version mit zwölf Reglern, drei Tastern, Zustandsverwaltung und unveränderter Audiodurchleitung.
