/**
 * \file PdfGeneratorWorker.cpp
 * \brief Implementation of Qt-based PDF generation worker
 *
 * \author Constantin
 * \date 2026-01-01
 */

#include "PdfGeneratorWorker.h"

#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPageLayout>
#include <QPageSize>
#include <QPrinter>
#include <QTextDocument>
#include <QUrl>

#include "Logger.h"  // For logging

PdfGeneratorWorker::PdfGeneratorWorker(QObject* parent)
    : QObject(parent) {
    // Constructor - no special initialization needed
}

PdfGeneratorWorker::~PdfGeneratorWorker() {
    // Destructor - automatic cleanup by Qt parent-child relationship
}

void PdfGeneratorWorker::generatePdf(const QString& htmlReport,
                                    const QString& outputPath,
                                    const QString& filePrefix) {
    // Generate unique timestamp for file name
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

    // Construct file name
    QString fileName = outputPath + QDir::separator() + filePrefix + timestamp + ".pdf";

    // Verify directory exists (should already be validated, but double-check)
    QDir outputDir(outputPath);
    if (!outputDir.exists()) {
        QString error = tr("Output directory does not exist: %1").arg(outputPath);
        Logger::error(LogCategory::UserAction, error);
        emit pdfGenerationFailed(error);
        emit finished();
        return;
    }

    // Initialize printer with optimal settings for A4 PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(true);

    // Set margins (5mm on all sides)
    qreal margin = 5.0;
    printer.setPageMargins(QMarginsF(margin, margin, margin, margin), QPageLayout::Millimeter);

    // Initialize QTextDocument with HTML report
    QTextDocument outputReport;
    outputReport.setHtml(htmlReport);
    outputReport.setDocumentMargin(0);

    // Validate document and printer before proceeding
    if (outputReport.isEmpty()) {
        QString error = tr("Cannot generate PDF from empty HTML document");
        Logger::error(LogCategory::UserAction, error);
        emit pdfGenerationFailed(error);
        emit finished();
        return;
    }

    if (!printer.isValid()) {
        QString error = tr("Printer configuration is invalid");
        Logger::error(LogCategory::UserAction, error);
        emit pdfGenerationFailed(error);
        emit finished();
        return;
    }

    // Generate PDF by printing document to file
    outputReport.print(&printer);

    // Verify file was created successfully
    QFileInfo outputFile(fileName);
    if (!outputFile.exists()) {
        QString error = tr("Failed to create PDF file: %1").arg(fileName);
        Logger::error(LogCategory::UserAction, error);
        emit pdfGenerationFailed(error);
        emit finished();
        return;
    }

    // Verify file has content
    qint64 fileSize = outputFile.size();
    if (fileSize == 0) {
        QString error = tr("Generated PDF file is empty: %1").arg(fileName);
        Logger::error(LogCategory::UserAction, error);
        emit pdfGenerationFailed(error);
        emit finished();
        return;
    }

    // Open PDF in default viewer
    bool opened = QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    if (!opened) {
        Logger::warning(LogCategory::UserAction,
                       QString("Nu s-a putut deschide automat PDF-ul: %1").arg(fileName));
    }

    // Log success with file size
    QString fileSizeStr;
    if (fileSize < 1024) {
        fileSizeStr = QString("%1 bytes").arg(fileSize);
    } else if (fileSize < 1024 * 1024) {
        fileSizeStr = QString("%1 KB").arg(fileSize / 1024.0, 0, 'f', 1);
    } else {
        fileSizeStr = QString("%1 MB").arg(fileSize / (1024.0 * 1024.0), 0, 'f', 2);
    }

    Logger::info(LogCategory::UserAction,
                QString("PDF generat cu succes: %1 (%2)").arg(fileName, fileSizeStr));

    // Signal success
    emit pdfGeneratedSuccessfully(fileName, fileSize);
    emit finished();
}
