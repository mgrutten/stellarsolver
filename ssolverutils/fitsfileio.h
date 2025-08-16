#ifndef FITSFILEIO_H
#define FITSFILEIO_H

//Qt Includes
#include <QVariant>

//CFitsio Includes
#include "fitsio.h"

//KStars related includes
#include "bayer.h"

//Project Includes
#include "parameters.h"
#include "structuredefinitions.h"

class fileio : public QObject
{
    Q_OBJECT
public:

    /** Structure to hold FITS Header records */
    typedef struct
    {
        QString key;      /** FITS Header Key */
        QVariant value;   /** FITS Header Value */
        QString comment;  /** FITS Header Comment, if any */
    } Record;


    fileio();
    ~fileio();
    void deleteImageBuffer();
    bool logToSignal = false;
    bool loadFitsBufferOnly(QString fileName);
    bool loadFits(QString fileName);
    bool parseHeader();
    bool saveAsFITS(QString fileName, FITSImage::Statistic &imageStats, uint8_t *m_ImageBuffer, FITSImage::Solution solution, const QList<Record> &records, bool hasSolution);
    bool loadOtherFormat(QString fileName);
    bool checkDebayer();
    bool debayer();
    bool debayer_8bit();
    bool debayer_16bit();
    bool getSolverOptionsFromFITS();

    bool position_given = false;
    double ra;
    double dec;

    bool scale_given = false;
    double scale_low;
    double scale_high;
    SSolver::ScaleUnits scale_units;

    bool imageBufferTaken = false;
    uint8_t *getImageBuffer();

    FITSImage::Statistic getStats(){
        return stats;
    }

    const QList<Record> &getRecords() const
    {
        return m_HeaderRecords;
    }

    void setRecords(QList<Record> &records)
    {
        m_HeaderRecords = records;
    }

private:
    QString file;
    fitsfile *fptr { nullptr };
    FITSImage::Statistic stats;
    QList<Record> m_HeaderRecords;
    /// Generic data image buffer
    uint8_t *m_ImageBuffer { nullptr };
    /// Above buffer size in bytes
    uint32_t m_ImageBufferSize { 0 };
    bool justLoadBuffer = false;
    BayerParams debayerParams;
    void logIssue(QString messsage);

signals:
    void logOutput(QString logText);
};

#endif // FILEIO_H
