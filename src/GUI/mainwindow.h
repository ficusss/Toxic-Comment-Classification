#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


/**
namespace Ui
@brief Пространство имён Ui, используемое объектами графического интерфейса
*/
namespace Ui {

/**
@brief Базовый класс окна
*/
class MainWindow;
}

/**
@brief Qt окно
*/
class GUIMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    @brief Конструктор класса.
    @param parent Родительский виджет.
    */
    explicit GUIMainWindow(QWidget *parent = 0);
    /**
    @brief Деструктор класса.
    */
    ~GUIMainWindow();

private slots:
    /**
    @brief Слот, соответствующий нажатию элемента меню "Открыть файл".
    */
    void on_action_triggered();

    /**
    @brief Слот, соответствующий нажатию элемента меню "Сохранить в файл".
    */
    void on_action_2_triggered();

    /**
    @brief Слот, соответствующий нажатию кнопки "Запуск".
    */
    void on_action_3_triggered();

private:
    /**
    @brief Вспомогательный метод, добавляющий новую строку в таблицу.
    @param cols Значения элементов столбцов новой строки.
    @return Порядковый номер строки.
    */
    int add_row(const QStringList& cols);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
