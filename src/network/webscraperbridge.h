#ifndef WEBSCRAPERBRIDGE_H
#define WEBSCRAPERBRIDGE_H

#include "Python_wrapper.h"

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QStringList>

class WebScraperBridge : public QObject
{
    Q_OBJECT

public:
    WebScraperBridge(const QString &pythonScriptPath, QObject *parent = nullptr)
        : QObject(parent), pInstance(nullptr), pyScrapedData(nullptr)
    {
        // Initialize the Python interpreter
        Py_Initialize();

        // Add the script path to the Python module search path
        QStringList paths = { pythonScriptPath };
        PyObject* sysPath = PySys_GetObject("path");
        for (const QString& path : paths) {
            PyObject* pPath = PyUnicode_FromString(path.toStdString().c_str());
            PyList_Append(sysPath, pPath);
            Py_DECREF(pPath);
        }

        // Load the Python module
        PyObject* pName = PyUnicode_DecodeFSDefault("webscraper");
        PyObject* pModule = PyImport_Import(pName);
        Py_DECREF(pName);

        if (pModule != nullptr) {
            pDict = PyModule_GetDict(pModule);
            pFunc = PyDict_GetItemString(pDict, "create_scraper");

            if (pFunc && PyCallable_Check(pFunc)) {
                pInstance = PyObject_CallObject(pFunc, nullptr);
                if (pInstance != nullptr) {
                    PyObject* pSignal = PyObject_GetAttrString(pInstance, "scraped_data");
                    if (pSignal != nullptr && PyCallable_Check(pSignal)) {
                        pyScrapedData = pSignal;
                    } else {
                        qWarning() << "Failed to get scraped_data signal";
                    }
                } else {
                    qWarning() << "Failed to create scraper instance";
                }
            } else {
                qWarning() << "create_scraper not found or not callable";
            }
            Py_DECREF(pModule);
        } else {
            qWarning() << "Failed to load webscraper module";
            PyErr_Print();
        }
    }

    ~WebScraperBridge() {
        Py_XDECREF(pInstance);
        Py_Finalize();
    }

    void scrape(const QString& url) {
        if (pInstance != nullptr) {
            PyObject* pScrapeMethod = PyObject_GetAttrString(pInstance, "scrape_website");
            if (pScrapeMethod && PyCallable_Check(pScrapeMethod)) {
                PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(url.toStdString().c_str()));
                PyObject* pResult = PyObject_CallObject(pScrapeMethod, pArgs);
                Py_DECREF(pArgs);
                if (pResult != nullptr) {
                    Py_DECREF(pResult);
                } else {
                    PyErr_Print();
                }
            } else {
                qWarning() << "scrape_website method not found or not callable";
            }
        }
    }

signals:
    void scrapedDataReceived(const QString& data);

private:
    PyObject *pDict, *pFunc, *pInstance, *pyScrapedData;
};

#endif // WEBSCRAPERBRIDGE_H
