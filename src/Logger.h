#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QDir>

/**
 * @brief Categorii de log pentru clasificare mesaje
 */
enum class LogCategory {
    Metrology,    // Operațiuni metrologice (măsurători, calcule)
    UserAction,   // Acțiuni utilizator (export, salvare, configurare)
    System,       // Operațiuni sistem (start/stop, fișiere, registry)
    Error         // Erori și excepții
};

/**
 * @brief Clasa Logger - Sistem logging production-ready pentru WStreamLab
 *
 * Singleton thread-safe pentru logging cu rotație automată fișiere.
 * Nivele: Info, Warning, Error, Critical (fără Debug).
 *
 * Fișiere salvate în: {FolderAplicație}\Logs\
 * Format: wstreamlab_YYYY-MM-DD.log
 * Rotație: 1 fișier/zi, păstrare 30 zile, max 10MB/fișier
 */
class Logger
{
public:
    /**
     * @brief Obține instanța singleton
     */
    static Logger& instance();

    /**
     * @brief Log mesaj nivel INFO
     * @param category Categoria log
     * @param message Mesajul de logat
     */
    static void info(LogCategory category, const QString& message);

    /**
     * @brief Log mesaj nivel WARNING
     * @param category Categoria log
     * @param message Mesajul de logat
     */
    static void warning(LogCategory category, const QString& message);

    /**
     * @brief Log mesaj nivel ERROR
     * @param category Categoria log
     * @param message Mesajul de logat
     */
    static void error(LogCategory category, const QString& message);

    /**
     * @brief Log mesaj nivel CRITICAL
     * @param category Categoria log
     * @param message Mesajul de logat
     */
    static void critical(LogCategory category, const QString& message);

    /**
     * @brief Setează numărul maxim de zile pentru păstrare log-uri
     * @param days Număr zile (default: 30)
     */
    void setMaxDays(int days);

    /**
     * @brief Setează dimensiunea maximă per fișier log
     * @param bytes Dimensiune în bytes (default: 10MB)
     */
    void setMaxFileSize(qint64 bytes);

    /**
     * @brief Setează calea custom pentru salvare log-uri
     * @param path Cale absolută folder
     */
    void setLogPath(const QString& path);

    /**
     * @brief Obține lista fișierelor log existente
     * @return Lista căi absolute fișiere log
     */
    QStringList getLogFiles() const;

    /**
     * @brief Obține conținutul log pentru o dată specifică
     * @param date Data pentru care se dorește log-ul
     * @return Conținut fișier log sau QString gol dacă nu există
     */
    QString getLogContent(const QDate& date) const;

    /**
     * @brief Șterge log-urile mai vechi decât perioada configurată
     */
    void cleanOldLogs();

    /**
     * @brief Verifică dacă logging-ul este activat
     * @return true dacă logging este activ
     */
    bool isEnabled() const { return enabled; }

    /**
     * @brief Activează/dezactivează logging-ul
     * @param enabled true pentru activare
     */
    void setEnabled(bool enabled) { this->enabled = enabled; }

private:
    Logger();
    ~Logger();

    // Dezactivare copy/move
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Scrie mesaj în fișierul log
     * @param level Nivel log (INFO/WARNING/ERROR/CRITICAL)
     * @param category Categoria log
     * @param message Mesajul
     */
    void writeLog(const QString& level, LogCategory category, const QString& message);

    /**
     * @brief Verifică și efectuează rotația fișierului dacă e necesar
     */
    void rotateLogIfNeeded();

    /**
     * @brief Formatează un mesaj log conform standardului
     * @param level Nivel log
     * @param category Categoria
     * @param message Mesajul
     * @return String formatat: [timestamp] [nivel] [categorie] mesaj
     */
    QString formatLogEntry(const QString& level, LogCategory category, const QString& message);

    /**
     * @brief Convertește categoria în string pentru logging
     * @param category Categoria
     * @return Numele categoriei
     */
    QString categoryToString(LogCategory category) const;

    /**
     * @brief Obține calea fișierului log pentru data curentă
     * @return Cale absolută fișier log
     */
    QString getCurrentLogFilePath() const;

    /**
     * @brief Inițializează folder-ul de log-uri
     */
    void initializeLogDirectory();

    /**
     * @brief Obține calea implicită pentru log-uri din Registry sau AppData
     * @return Cale folder log-uri
     */
    QString getDefaultLogPath() const;

    /**
     * @brief Încarcă setări din Registry
     */
    void loadSettings();

private:
    QString logPath;           // Cale folder log-uri
    int maxDays;               // Zile păstrare (default: 30)
    qint64 maxFileSize;        // Dimensiune max per fișier (default: 10MB)
    bool enabled;              // Logging activat/dezactivat
    mutable QMutex mutex;      // Thread-safety (mutable pentru funcții const)
    QDate currentLogDate;      // Data fișierului log curent
    QString currentLogFile;    // Cale fișier log curent
};

#endif // LOGGER_H
