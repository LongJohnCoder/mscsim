#include <iostream>

#include <QString>
#include <QtTest>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Vector6Test : public QObject
{
    Q_OBJECT

public:

    Vector6Test();

private Q_SLOTS:

    void initTestCase();
    void cleanupTestCase();

    void sampleTest();
};

////////////////////////////////////////////////////////////////////////////////

Vector6Test::Vector6Test() {}

////////////////////////////////////////////////////////////////////////////////

void Vector6Test::initTestCase() {}

////////////////////////////////////////////////////////////////////////////////

void Vector6Test::cleanupTestCase() {}

////////////////////////////////////////////////////////////////////////////////

void Vector6Test::sampleTest()
{
    QVERIFY2( true, "Failure" );
}

////////////////////////////////////////////////////////////////////////////////

QTEST_APPLESS_MAIN(Vector6Test)

////////////////////////////////////////////////////////////////////////////////

#include "test_fdm_vector6.moc"
