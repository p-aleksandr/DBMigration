// DBMigration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CDBObjectSuccessors.h"
#include "DBObjectConstructor.h"
#include "CComparator.h"
#include "CDBObjectHistory.h"

#include "SQLControl.h"
// этот код работает на VS 2019 с выбранным с++17-ым стандартом, в других средах не пробовал
int main()
{
    SQLControl Controler;

    // для представления таблиц используем рекурсивную структуру и классы наследники для удобства
    // что позволяет уже на данном этапе сформировать класс содержащий любую информацию о таблице (например можем добавить сохранение триггеров)
    // просто добавив соответствующего новому типу наследника (и соответствующий ему enum class)
    // и создавать экземпляры как это делается ниже
    CTable Table("Table1");
    Table
        .AddProperty(CField("ID")
            .AddProperty(CProperty("Type", "int")))
        .AddProperty(CField("Description")
            .AddProperty(CProperty("Type", "varchar")
                .AddProperty(CProperty("size", "50"))));

    CTable TableOld("Table1");
    TableOld
        .AddProperty(CField("ID")
            .AddProperty(CProperty("Type", "int")));

    // другой способ получить таблийу это, например класс который может конструировать 
    // из скрипта сформированного в БД или, например, прочитанного из файла (сейчас это просто заглушка т.к. надо парсить
    // скрипт а это довольно большая по времени задача)
    TableConstructor Constructor(Controler.GetScript("Table2"));
    CTable* Table2 = Constructor.Construct();

    // в результате сравнения получаем структуру аналогичную исходной но с 
    // добавленным для каждого элемента, в том числе и вложенного свойством mStatus, 
    // которое впоследствии при формировании скрипта будем анализировать
    // текущая реализация копирует элементы целиком что не очень хорошо с точки зрения
    // затрат памяти и это надо будет оптимизировать, но концепция в целом такая
    CComparator comparator;
    auto comparation_result = comparator.Compare(&Table, &TableOld);


    // для хранения истории здесь используется простая оберткв над std::map а не 
    // что-то написанное в соответствии с паттерном снимок к которому, видимо, отсылка
    // потому, что не вижу практического применения в конкретно этой задаче
    CDBObjectHistory History;
    History.Store("ver 1", TableOld);
    History.Store("ver 2", Table);

    auto RestoredV1 = History.Get("ver 1");
    auto RestoredV2 = History.Get("ver 2");

    // для формирования скрипта надо использовать, видимо, тоже механизм с базовым классом и классами наследниками
    // где в классах наследниках реализуется логика по созданию части скрипта соответствующей типу получаемого на вход
    // объекта т.е. если на вход пришел CTable созданием скрипта занимается CTableCreator, CIndex -> CIndexCreator и т.д.
    // но это весьма сложная часть т.к. типов объектов много и вложенность может быть большая и за условный час конечного решения
    // я не дам
    // предполагается что на вход будет подаваться результат сравнения 2х таблиц и рекурсивно проходя по этому результату 
    // (аналогично тому как это делается при сравнении) будут создаваться эти классы-создатели, которые будут анализировать 
    // какие изменения были произведены и в результирующий скрипт добавлять соответсвующие строки
    // с очень высокой степенью вероятности надо будет задействовать StateMachine
    // 
    // На верхнем уровне будет что-то типа такого
    // CTableScriptCreator Creator( comparator.Compare(&Table, &TableOld))
    // auto SQLScript = Creator.Create();
    // Controler.ExecuteSQL(SQLScript);

}
