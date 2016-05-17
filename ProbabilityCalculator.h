#ifndef PROBABILITYCALCULATOR_H
#define PROBABILITYCALCULATOR_H

#include <QVector>
#include <QPair>

class Card;

class ProbabilityCalculator
{
public:
	ProbabilityCalculator();
	
	qreal CalculatePreFlopProbability(const QPair<Card, Card> &hand);
	qreal CalculateFlopToRiverProbability( const QPair<Card, Card> &hand, const QVector<Card> &flop );
	qreal CalculateRiverToTernProbability( const QPair<Card, Card> &hand, const QVector<Card> &river );
	qreal CalculateExpectedValue(const QPair<Card, Card> &hand, const QVector<Card> &table, qreal pot, qreal mise );
	
private:
	quint8 CalculateCountCardsForBestCombination( const QPair<Card, Card> &hand, 
	                                             const QVector<Card> &table );
	bool IsFlashDraw( const QPair<Card, Card> &hand, 
	                  const QVector<Card> &table );
	bool IsStreatDraw( const QPair<Card, Card> &hand, 
	                  const QVector<Card> &table );
	bool IsGotShot( const QPair<Card, Card> &hand, 
	                const QVector<Card> &table );
	bool IsFlashDrawOnTable( const QVector<Card> &table );
	bool IsStreatDrawOnTable( const QVector<Card> &table );
	
	qreal CalculatePotOdds( qreal pot, qreal mise );
};

#endif // PROBABILITYCALCULATOR_H
