# Plan Sistem Logging WStreamLab

**Versiune:** 1.0
**Data:** 2026-01-01
**Status:** Planificare

---

## Obiective

Implementare sistem de logging **production-ready** pentru:
- Audit trail operațiuni metrologice
- Troubleshooting probleme utilizatori
- Monitorizare performanță și erori
- Conformitate cerințe metrologice

**IMPORTANT:** Fără mesaje debug - doar Info, Warning, Error, Critical

---

## 1. Arhitectură Sistem

### 1.1 Nivele Log (fără Debug)

| Nivel | Utilizare | Exemple |
|-------|-----------|---------|
| **Info** | Operațiuni normale importante | Sesiune verificare începută, PDF exportat |
| **Warning** | Situații neobișnuite dar recuperabile | Conectare Modbus eșuată (retry), Date lipsă |
| **Error** | Erori care afectează operațiuni | Salvare fișier eșuată, Calcul invalid |
| **Critical** | Erori grave sistem | Aplicație crash, Corupție date |

### 1.2 Categorii Log

```cpp
enum class LogCategory {
    Metrology,    // Operațiuni metrologice (măsurători, calcule)
    UserAction,   // Acțiuni utilizator (export, salvare, configurare)
    System,       // Operațiuni sistem (start/stop, fișiere, registry)
    Error         // Erori și excepții
};
```

---

## 2. Specificații Tehnice

### 2.1 Format Log Entry

```
[2026-01-01 14:23:45] [INFO] [Metrology] Sesiune verificare început: Itron Flodis DN 25 R100
[2026-01-01 14:24:12] [INFO] [UserAction] Măsurătoare adăugată: Q=3.5 l/h, Index=1234.567
[2026-01-01 14:25:03] [WARNING] [System] Conectare Modbus device 1 eșuată (tentativa 2/3)
[2026-01-01 14:26:30] [INFO] [UserAction] PDF exportat: C:\Results\FM_20260101_142630.pdf
[2026-01-01 14:27:15] [ERROR] [System] Salvare configurație eșuată: Acces interzis
```

**Componente:**
- Timestamp: `[YYYY-MM-DD HH:MM:SS]`
- Nivel: `[INFO|WARNING|ERROR|CRITICAL]`
- Categorie: `[Metrology|UserAction|System|Error]`
- Mesaj: text descriptiv cu context

### 2.2 Salvare Fișiere

**Locație:** `C:\Users\{User}\AppData\Local\WStreamLab\Logs\`

**Fișiere rotative:**
```
wstreamlab_2026-01-01.log  (fișier curent)
wstreamlab_2025-12-31.log  (ziua precedentă)
wstreamlab_2025-12-30.log
...
```

**Reguli rotație:**
- 1 fișier nou pe zi
- Păstrare ultimele **30 zile** (configurable)
- Ștergere automată fișiere vechi
- Max size per fișier: **10 MB** (split dacă depășește)

### 2.3 Clasă Logger

```cpp
// logger.h
class Logger {
public:
    static Logger& instance();

    // Metode logging
    static void info(LogCategory category, const QString& message);
    static void warning(LogCategory category, const QString& message);
    static void error(LogCategory category, const QString& message);
    static void critical(LogCategory category, const QString& message);

    // Configurare
    void setMaxDays(int days);           // Default: 30
    void setMaxFileSize(qint64 bytes);   // Default: 10MB
    void setLogPath(const QString& path);

    // Utilități
    QStringList getLogFiles() const;
    QString getLogContent(const QDate& date) const;
    void cleanOldLogs();

private:
    Logger();
    ~Logger();

    void writeLog(const QString& level, LogCategory category, const QString& message);
    void rotateLogIfNeeded();
    QString formatLogEntry(const QString& level, LogCategory category, const QString& message);

    QString m_logPath;
    int m_maxDays;
    qint64 m_maxFileSize;
    QFile m_currentFile;
    QTextStream m_stream;
    QMutex m_mutex;  // Thread-safe
};
```

---

## 3. Ce se Loghează

### 3.1 Operațiuni Metrologice (Categoria: Metrology)

**Info:**
- ✓ Sesiune verificare început/terminat
- ✓ Tip apometru selectat
- ✓ Parametri verificare setați (temperatură, presiune, umiditate)
- ✓ Măsurătoare adăugată/modificată/ștearsă
- ✓ Calcule finalizate (rezultate verificare)

**Warning:**
- ✓ Valori măsurători în afara intervalului așteptat
- ✓ Erori calcul minore (valori corecte automat)

**Error:**
- ✓ Calcule eșuate (date invalide)
- ✓ Imposibilitate verificare (parametri lipsa)

### 3.2 Operațiuni Utilizator (Categoria: UserAction)

**Info:**
- ✓ PDF exportat (path + numele fișierului)
- ✓ Date salvate (JSON/CSV)
- ✓ Date încărcate din fișier
- ✓ Configurație schimbată (Registry settings)
- ✓ Raport generat

**Warning:**
- ✓ Export PDF cu date incomplete
- ✓ Salvare în locație nestandard

**Error:**
- ✓ Export PDF eșuat
- ✓ Salvare date eșuată
- ✓ Încărcare fișier corrupt

### 3.3 Operațiuni Sistem (Categoria: System)

**Info:**
- ✓ Aplicație pornită (versiune, utilizator, PC)
- ✓ Aplicație închisă
- ✓ Conectare interfață Modbus (success)
- ✓ Deconectare interfață Modbus
- ✓ Încărcare configurație watermeters.csv

**Warning:**
- ✓ Conectare Modbus eșuată (cu retry)
- ✓ Fișier configurație lipsă (folosește default)
- ✓ Registry key lipsă (creează nou)

**Error:**
- ✓ Încărcare watermeters.csv eșuată
- ✓ Scriere Registry eșuată
- ✓ Acces fișier refuzat

**Critical:**
- ✓ Aplicație crash (exceptii necaptate)
- ✓ Corupție date critice

---

## 4. Viewer Log în Aplicație

### 4.1 UI Log Viewer (Dialog nou)

**Menu:** `Help > View Logs` sau `Tools > Logs`

**Componente:**
- ComboBox: selectare dată (ultimele 30 zile)
- TextEdit (read-only): afișare conținut log
- Filtre: nivel (Info/Warning/Error/Critical), categorie
- Butoane:
  - Refresh
  - Open Log Folder
  - Export Selected
  - Clear Old Logs (> 30 zile)

### 4.2 Notificări Erori

**Opțional:** StatusBar notificare când apar Warning/Error în timpul sesiunii curente
- Icon Warning/Error în StatusBar
- Click → deschide Log Viewer la ultimele intrări

---

## 5. Integrare în Cod Existent

### 5.1 Exemple Utilizare

**MainWindow:**
```cpp
void MainWindow::onNewSession() {
    Logger::info(LogCategory::Metrology,
        QString("Sesiune nouă început: %1").arg(selectedInfo.nameWaterMeter.c_str()));
    // ...
}

void MainWindow::onExportPdf() {
    QString pdfPath = "...";
    if (success) {
        Logger::info(LogCategory::UserAction,
            QString("PDF exportat: %1").arg(pdfPath));
    } else {
        Logger::error(LogCategory::UserAction,
            QString("Export PDF eșuat: %1 - %2").arg(pdfPath).arg(errorMsg));
    }
}
```

**Interface (Modbus):**
```cpp
void Interface::connectModbus() {
    if (!modbusDevice_1->connectDevice()) {
        Logger::warning(LogCategory::System,
            QString("Conectare Modbus device 1 eșuată: %1").arg(modbusDevice_1->errorString()));
    } else {
        Logger::info(LogCategory::System, "Conectare Modbus device 1 reușită");
    }
}
```

**TableBoard (Calcule):**
```cpp
void TableBoard::calculateResults() {
    try {
        // calcule...
        Logger::info(LogCategory::Metrology,
            QString("Calcule finalizate: %1 măsurători procesate").arg(count));
    } catch (const std::exception& e) {
        Logger::error(LogCategory::Metrology,
            QString("Calcule eșuate: %1").arg(e.what()));
    }
}
```

### 5.2 Înlocuire qDebug/qWarning Existent

**Înainte:**
```cpp
qWarning() << "Failed to open modbusDevice_1:" << errorString;
```

**După:**
```cpp
Logger::warning(LogCategory::System,
    QString("Failed to open modbusDevice_1: %1").arg(errorString));
```

---

## 6. Configurare și Setări

### 6.1 Registry Settings (opțional)

**HKEY_CURRENT_USER\Software\WStreamLab\Logging**

| Key | Tip | Default | Descriere |
|-----|-----|---------|-----------|
| `Enabled` | DWORD | 1 | 1=activ, 0=dezactivat |
| `MaxDays` | DWORD | 30 | Zile păstrare log-uri |
| `MaxFileSizeMB` | DWORD | 10 | Size maxim per fișier |
| `LogPath` | String | AppData | Path custom (opțional) |

### 6.2 Nivel Minim Log

Default: **Info** (toate mesajele)
Opțional: registry setting pentru Warning/Error only

---

## 7. Avantaje pentru Utilizatori

✓ **Troubleshooting rapid** - vizualizare operațiuni când apar probleme
✓ **Audit trail complet** - istoric sesiuni verificare (conformitate)
✓ **Identificare erori** - mesaje clare pentru raportare bug-uri
✓ **Fără impact performanță** - async writing, fără debug overhead
✓ **Gestiune automată** - rotație și ștergere fișiere vechi
✓ **Privacy** - doar operațiuni, fără date personale sensibile

---

## 8. Timeline Implementare (Estimativ)

1. **Clasă Logger de bază** - 2-3 ore
2. **Rotație fișiere și cleanup** - 1-2 ore
3. **Integrare în cod existent** - 3-4 ore
4. **Log Viewer UI** - 2-3 ore
5. **Testing și optimizare** - 2-3 ore

**Total:** ~10-15 ore dezvoltare

---

## 9. Considerații Suplimentare

### 9.1 Performanță
- Scriere asincronă (QThread sau QTimer batch)
- Buffer in-memory pentru reduce I/O
- Mutex pentru thread-safety

### 9.2 Privacy și Securitate
- Nu loga date sensibile (parole, licențe)
- Nu loga date personale clienți (GDPR)
- Loga doar informații tehnice și operaționale

### 9.3 Mentenanță
- Cleanup automat la pornire aplicație
- Notificare user dacă log folder > 100MB
- Compresie fișiere vechi (opțional .zip)

---

## 10. Întrebări Deschise

- [ ] Include metadate în log (versiune app, OS, PC name)?
- [ ] Export log complet pentru suport tehnic?
- [ ] Statistici operațiuni (nr. sesiuni/zi, etc.)?
- [ ] Notificări email pentru erori critice?

---

**Status:** Planificare completă - Așteptare aprobare implementare
