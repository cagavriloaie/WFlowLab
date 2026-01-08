#include "Logger.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QSettings>
#include <QCoreApplication>
#include <QMutexLocker>
#include <QStringConverter>

// Constante
const int DEFAULT_MAX_DAYS = 30;
const qint64 DEFAULT_MAX_FILE_SIZE = 10 * 1024 * 1024; // 10 MB
const QString LOG_FILE_PREFIX = "wstreamlab_";
const QString LOG_FILE_EXTENSION = ".log";

Logger::Logger()
    : maxDays(DEFAULT_MAX_DAYS)
    , maxFileSize(DEFAULT_MAX_FILE_SIZE)
    , enabled(true)
{
    loadSettings();
    initializeLogDirectory();
    cleanOldLogs();
}

Logger::~Logger()
{
    // Cleanup automat
}

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::info(LogCategory category, const QString& message)
{
    instance().writeLog("INFO", category, message);
}

void Logger::warning(LogCategory category, const QString& message)
{
    instance().writeLog("WARNING", category, message);
}

void Logger::error(LogCategory category, const QString& message)
{
    instance().writeLog("ERROR", category, message);
}

void Logger::critical(LogCategory category, const QString& message)
{
    instance().writeLog("CRITICAL", category, message);
}

void Logger::setMaxDays(int days)
{
    QMutexLocker locker(&mutex);
    maxDays = days;
}

void Logger::setMaxFileSize(qint64 bytes)
{
    QMutexLocker locker(&mutex);
    maxFileSize = bytes;
}

void Logger::setLogPath(const QString& path)
{
    QMutexLocker locker(&mutex);
    logPath = path;
    initializeLogDirectory();
}

QStringList Logger::getLogFiles() const
{
    QMutexLocker locker(&mutex);
    QDir logDir(logPath);
    QStringList filters;
    filters << LOG_FILE_PREFIX + "*" + LOG_FILE_EXTENSION;

    QFileInfoList fileList = logDir.entryInfoList(filters, QDir::Files, QDir::Time | QDir::Reversed);
    QStringList result;

    for (const QFileInfo& fileInfo : fileList) {
        result.append(fileInfo.absoluteFilePath());
    }

    return result;
}

QString Logger::getLogContent(const QDate& date) const
{
    QMutexLocker locker(&mutex);
    QString fileName = LOG_FILE_PREFIX + date.toString("yyyy-MM-dd") + LOG_FILE_EXTENSION;
    QString filePath = logPath + "/" + fileName;

    QFile file(filePath);
    if (!file.exists()) {
        return QString();
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll();
    file.close();

    return content;
}

void Logger::cleanOldLogs()
{
    QMutexLocker locker(&mutex);
    QDir logDir(logPath);
    QStringList filters;
    filters << LOG_FILE_PREFIX + "*" + LOG_FILE_EXTENSION;

    QFileInfoList fileList = logDir.entryInfoList(filters, QDir::Files);
    QDate cutoffDate = QDate::currentDate().addDays(-maxDays);

    for (const QFileInfo& fileInfo : fileList) {
        // Extract data din numele fișierului: wstreamlab_YYYY-MM-DD.log
        QString baseName = fileInfo.baseName();
        QString dateStr = baseName.mid(LOG_FILE_PREFIX.length());
        QDate fileDate = QDate::fromString(dateStr, "yyyy-MM-dd");

        if (fileDate.isValid() && fileDate < cutoffDate) {
            QFile::remove(fileInfo.absoluteFilePath());
        }
    }
}

void Logger::writeLog(const QString& level, LogCategory category, const QString& message)
{
    if (!enabled) {
        return;
    }

    QMutexLocker locker(&mutex);

    // Verifică rotația (nouă zi sau fișier prea mare)
    rotateLogIfNeeded();

    // Formează mesajul
    QString logEntry = formatLogEntry(level, category, message);

    // Deschide fișierul în append mode
    QFile file(currentLogFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        // Nu putem loga - silent fail
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << logEntry << "\n";
    file.close();
}

void Logger::rotateLogIfNeeded()
{
    QDate currentDate = QDate::currentDate();
    QString currentFilePath = getCurrentLogFilePath();

    // Verifică dacă e nouă zi
    if (currentLogDate != currentDate) {
        currentLogDate = currentDate;
        currentLogFile = currentFilePath;
        // Cleanup fișiere vechi
        cleanOldLogs();
        return;
    }

    // Verifică dimensiunea fișierului
    QFileInfo fileInfo(currentLogFile);
    if (fileInfo.exists() && fileInfo.size() >= maxFileSize) {
        // Split fișier - adaugă timestamp la nume
        QString timestamp = QDateTime::currentDateTime().toString("_HHmmss");
        QString baseName = fileInfo.baseName();
        QString newName = logPath + "/" + baseName + timestamp + LOG_FILE_EXTENSION;

        // Redenumește fișierul curent
        QFile::rename(currentLogFile, newName);

        // Fișierul curent va fi recreat la următoarea scriere
    }
}

QString Logger::formatLogEntry(const QString& level, LogCategory category, const QString& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString categoryStr = categoryToString(category);

    return QString("[%1] [%2] [%3] %4")
        .arg(timestamp)
        .arg(level)
        .arg(categoryStr)
        .arg(message);
}

QString Logger::categoryToString(LogCategory category) const
{
    switch (category) {
        case LogCategory::Metrology:
            return "Metrology";
        case LogCategory::UserAction:
            return "UserAction";
        case LogCategory::System:
            return "System";
        case LogCategory::Error:
            return "Error";
        default:
            return "Unknown";
    }
}

QString Logger::getCurrentLogFilePath() const
{
    QString fileName = LOG_FILE_PREFIX + QDate::currentDate().toString("yyyy-MM-dd") + LOG_FILE_EXTENSION;
    return logPath + "/" + fileName;
}

void Logger::initializeLogDirectory()
{
    if (logPath.isEmpty()) {
        logPath = getDefaultLogPath();
    }

    QDir dir;
    if (!dir.exists(logPath)) {
        dir.mkpath(logPath);
    }

    currentLogDate = QDate::currentDate();
    currentLogFile = getCurrentLogFilePath();
}

QString Logger::getDefaultLogPath() const
{
    // Verifică Registry pentru custom path
    QSettings settings("HKEY_CURRENT_USER\\Software\\WStreamLab\\Logging", QSettings::NativeFormat);
    QString customPath = settings.value("LogPath", "").toString();

    if (!customPath.isEmpty() && QDir(customPath).exists()) {
        return customPath;
    }

    // Path implicit: Folderul aplicației + /Logs
    QString appPath = QCoreApplication::applicationDirPath();
    return appPath + "/Logs";
}

void Logger::loadSettings()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\WStreamLab\\Logging", QSettings::NativeFormat);

    // Enabled (default: true) - Creează cheia dacă nu există
    if (!settings.contains("Enabled")) {
        settings.setValue("Enabled", 1);
    }
    enabled = settings.value("Enabled", 1).toInt() != 0;

    // MaxDays (default: 30) - Creează cheia dacă nu există
    if (!settings.contains("MaxDays")) {
        settings.setValue("MaxDays", DEFAULT_MAX_DAYS);
    }
    maxDays = settings.value("MaxDays", DEFAULT_MAX_DAYS).toInt();
    if (maxDays <= 0) {
        maxDays = DEFAULT_MAX_DAYS;
        settings.setValue("MaxDays", DEFAULT_MAX_DAYS); // Corectează valoare invalidă
    }

    // MaxFileSizeMB (default: 10) - Creează cheia dacă nu există
    if (!settings.contains("MaxFileSizeMB")) {
        settings.setValue("MaxFileSizeMB", 10);
    }
    int maxSizeMB = settings.value("MaxFileSizeMB", 10).toInt();
    if (maxSizeMB <= 0) {
        maxSizeMB = 10;
        settings.setValue("MaxFileSizeMB", 10); // Corectează valoare invalidă
    }
    maxFileSize = static_cast<qint64>(maxSizeMB) * 1024 * 1024;

    // LogPath (default: gol = folder aplicație) - Creează cheia dacă nu există
    if (!settings.contains("LogPath")) {
        settings.setValue("LogPath", "");
    }
    logPath = settings.value("LogPath", "").toString();

    // Sincronizare imediată în Registry
    settings.sync();
}
