#include <iostream>

#include <QString>
#include <QtTest>

#include <fdm/sys/fdm_Lag.h>

////////////////////////////////////////////////////////////////////////////////

#define TIME_STEP 0.1
#define TIME_CONSTANT 2.0

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class LagTest : public QObject
{
    Q_OBJECT

public:

    LagTest();

private:

    std::vector< double > m_y;

    fdm::Lag *m_lag;

private Q_SLOTS:

    void initTestCase();
    void cleanupTestCase();

    void testUpdate();
};

////////////////////////////////////////////////////////////////////////////////

LagTest::LagTest() {}

////////////////////////////////////////////////////////////////////////////////

void LagTest::initTestCase()
{
    m_lag = new fdm::Lag( TIME_CONSTANT );

    FILE *file = fopen( "data/tst_fdm_lag.bin", "r" );

    if ( file )
    {
        char buffer[4];

        while ( fread( buffer, 1, 4, file ) == 4 )
        {
            float *y = (float*)(buffer);
            m_y.push_back( *y );
        }

        fclose( file );
    }
}

////////////////////////////////////////////////////////////////////////////////

void LagTest::cleanupTestCase()
{
    if ( m_lag ) delete m_lag;
    m_lag = 0;
}

////////////////////////////////////////////////////////////////////////////////

void LagTest::testUpdate()
{
    double t = 0.0;
    double y = 0.0;

    double u_prev = 0.0;
    double y_prev = 0.0;

    for ( unsigned int i = 0; i < m_y.size(); i++ )
    {
        double u = ( t < 0.99 ) ? 0.0 : 1.0;

        int steps = 10;
        for ( int j = 0; j < steps; j++ )
        {
            double dt = TIME_STEP / (double)steps;
            m_lag->update( u, dt );
            y = m_lag->getValue();

            if ( 0 )
            {
                double c1 = 1.0 / TIME_CONSTANT;
                double denom = 2.0 + dt * c1;
                double ca = dt * c1 / denom;
                double cb = ( 2.0 - dt * c1 ) / denom;

                y = ( u + u_prev ) * ca + y_prev * cb;

                u_prev = u;
                y_prev = y;
            }
        }

        cout << y << " " << m_y.at( i ) << endl;

        QVERIFY2( fabs( y - m_y.at( i ) ) < 1.0e-3, "Failure" );

        t += TIME_STEP;
    }
}

////////////////////////////////////////////////////////////////////////////////

QTEST_APPLESS_MAIN(LagTest)

////////////////////////////////////////////////////////////////////////////////

#include "tst_fdm_lag.moc"