#include <iostream>

#include <QString>
#include <QtTest>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Matrix6x6Test : public QObject
{
    Q_OBJECT

public:

    Matrix6x6Test();

private Q_SLOTS:

    void initTestCase();
    void cleanupTestCase();

    void sampleTest();
};

////////////////////////////////////////////////////////////////////////////////

Matrix6x6Test::Matrix6x6Test() {}

////////////////////////////////////////////////////////////////////////////////

void Matrix6x6Test::initTestCase() {}

////////////////////////////////////////////////////////////////////////////////

void Matrix6x6Test::cleanupTestCase() {}

////////////////////////////////////////////////////////////////////////////////

void Matrix6x6Test::sampleTest()
{
    QVERIFY2( true, "Failure" );
}

////////////////////////////////////////////////////////////////////////////////

QTEST_APPLESS_MAIN(Matrix6x6Test)

////////////////////////////////////////////////////////////////////////////////

#include "test_fdm_matrix6x6.moc"
