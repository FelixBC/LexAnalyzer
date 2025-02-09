#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar el botón "Analizar" con la función analyzeText()
    connect(ui->analyzeButton, &QPushButton::clicked, this, &MainWindow::analyzeText);
    ui->textEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::analyzeText()
{
    QString inputText = ui->textEdit->toPlainText();

    // Guardar el código en un archivo temporal
    QString inputFilePath = QCoreApplication::applicationDirPath() + "/input.txt";
    QFile inputFile(inputFilePath);
    if (inputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&inputFile);
        out << inputText;
        inputFile.close();
    } else {
        ui->outputText->setPlainText("Error: No se pudo escribir input.txt");
        qDebug() << "Error: No se pudo escribir input.txt";
        return;
    }

    // Verificar si el ejecutable `lexer` existe
    QString lexerPath = QCoreApplication::applicationDirPath() + "/lexer";
    if (!QFile::exists(lexerPath)) {
        ui->outputText->setPlainText("Error: lexer no encontrado en " + lexerPath);
        qDebug() << "Error: lexer no encontrado en " << lexerPath;
        return;
    }

    // Ejecutar el analizador FLEX
    QProcess process;
    process.setWorkingDirectory(QCoreApplication::applicationDirPath()); // Asegurar directorio correcto
    process.start("bash", QStringList() << "-c" << lexerPath + " < " + inputFilePath);
    process.waitForFinished();

    // Capturar errores de ejecución
    QString errorOutput = process.readAllStandardError();
    if (!errorOutput.isEmpty()) {
        ui->outputText->setPlainText("Error de ejecución: " + errorOutput);
        qDebug() << "Error de ejecución: " << errorOutput;
        return;
    }

    // Leer la salida del analizador
    QString output = process.readAllStandardOutput();
    if (output.isEmpty()) {
        ui->outputText->setPlainText("Error: No se recibió salida del analizador.");
        qDebug() << "Error: No se recibió salida del analizador.";
    } else {
        // Eliminar "Introduce código fuente:" para limpiar la salida
        output.replace("Introduce código fuente:\n", "");
        ui->outputText->setPlainText(output);
        qDebug() << "Salida del analizador: " << output;
    }
}
