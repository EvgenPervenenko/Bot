#include <QCoreApplication>
#include "ProbabilityCalculator.h"
#include "Card.h"
#include <QVector>
#include <QPair>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	ProbabilityCalculator c;
	
	Card c1( Nominal::Nine, Lead::Heards );
	Card c2( Nominal::Ten, Lead::Heards );
	
	Card c3( Nominal::Jack, Lead::Heards );
	Card c4( Nominal::Queen, Lead::Heards );
	Card c5( Nominal::Ten, Lead::Diamonds );
	Card c6( Nominal::Nine, Lead::Diamonds );
	
	QVector<Card> table;
	table.push_back( c3 );
	table.push_back( c4 );
	table.push_back( c5 );
	table.push_back( c6 );
	
	qDebug() << c.CalculateExpectedValue( qMakePair( c1, c2 ), table, 150, 50 );
	qDebug() << c.CalculatePreFlopProbability( qMakePair( c1, c2 ) );
	
	return 1;
}

