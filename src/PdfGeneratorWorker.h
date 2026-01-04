/**
 * \file PdfGeneratorWorker.h
 * \brief Qt-based thread-safe PDF generation worker
 *
 * This replaces std::thread detached pattern with proper Qt threading.
 * Provides thread-safe PDF generation using Qt's signal/slot mechanism.
 *
 * \author Constantin
 * \date 2026-01-01
 */

#ifndef PDFGENERATORWORKER_H
#define PDFGENERATORWORKER_H

#include <QObject>
#include <QString>

/**
 * \brief Worker class for generating PDFs in a separate thread
 *
 * This class uses Qt's thread-safe signal/slot mechanism instead of
 * std::thread with shared static variables. Designed to run in a QThread.
 */
class PdfGeneratorWorker : public QObject {
    Q_OBJECT

public:
    /**
     * \brief Constructor
     * \param parent Parent QObject (optional)
     */
    explicit PdfGeneratorWorker(QObject* parent = nullptr);

    /**
     * \brief Destructor
     */
    ~PdfGeneratorWorker();

public slots:
    /**
     * \brief Generates PDF from HTML report content
     *
     * This slot is called when the worker thread starts. It generates a PDF
     * from the provided HTML content and saves it to the specified location.
     *
     * \param htmlReport The HTML content to render as PDF
     * \param outputPath The validated output directory path (must be pre-validated)
     * \param filePrefix The file prefix ("FM_" or "BV_")
     */
    void generatePdf(const QString& htmlReport, const QString& outputPath, const QString& filePrefix);

signals:
    /**
     * \brief Emitted when PDF generation completes successfully
     * \param filePath Full path to the generated PDF file
     * \param fileSize Size of the generated file in bytes
     */
    void pdfGeneratedSuccessfully(const QString& filePath, qint64 fileSize);

    /**
     * \brief Emitted when PDF generation fails
     * \param errorMessage Description of the error that occurred
     */
    void pdfGenerationFailed(const QString& errorMessage);

    /**
     * \brief Emitted when worker finishes (success or failure)
     *
     * This signal should be connected to QThread::quit() to properly
     * terminate the thread after work is complete.
     */
    void finished();
};

#endif // PDFGENERATORWORKER_H
