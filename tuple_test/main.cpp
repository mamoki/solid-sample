#include <tuple>
#include <QCoreApplication>
#include <QDebug>

using Data_row = std::tuple<QString, int, bool, QString>;
using Data_tab = QList<Data_row>;

enum class Data_col
{
    Row1 = 0,
    Row2 = 1,
    Row3 = 2,
    Row4 = 3,
};

Data_tab myTab;

template<Data_col col>
Data_row get(const typename std::tuple_element<static_cast<size_t>(col), Data_row>::type &key)
{
    qDebug() << "type: " << typeid(key).name();

    auto itr = std::find_if(myTab.constBegin(), myTab.constEnd(), [key](const Data_row& row) -> bool{return std::get<static_cast<size_t>(col)>(row) == key;});
    return itr != myTab.constEnd() ? *itr : Data_row{};
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    myTab << std::make_tuple(QString("r1"), 1, true, QString("r1-2"));

    Data_row res;

    res = get<Data_col::Row1>(QString("Test"));
    qDebug() << std::get<static_cast<size_t>(Data_col::Row1)>(res);

    res = get<Data_col::Row1>(QString("r1"));
    qDebug() << std::get<static_cast<size_t>(Data_col::Row1)>(res);

    get<Data_col::Row2>(1);

    return a.exec();
}
