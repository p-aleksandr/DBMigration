// DBMigration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CDBObjectSuccessors.h"
#include "DBObjectConstructor.h"
#include "CComparator.h"

#include "SQLControl.h"
int main()
{
    SQLControl controler;
    
    //создаем новую таблицу которой еще нет в БД
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

    TableConstructor constructor(controler.GetScript("Table2"));
    CTable *Table2 = constructor.Construct();

    CComparator comparator;
    auto comparation_result = comparator.Compare(&Table, &TableOld);
    //для создания скрипта надо анализировать статус поля и в зависимости от него формировать скрипт

    //для хранения истории
    
Ъ

