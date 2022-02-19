#pragma once

#include "TargetDummy.h"
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class Paladin
{
	// everything needed for holy paladin to dps rotation

public:
	Paladin(TargetDummy *dumbdumb);
	~Paladin() {}

	vector<double> inputs;
	vector<double> outputs;

	// pointer to the target dummy
	TargetDummy* target;

	// intellect = 1701, crit is .154, versatility is .20, haste is .2, weapon speed is 2.6, weapon low end is 48, weapon top end is 80
	int critChance;
	double damageMultiplier;

	// ai doesn't need to know that gcd is counting down
	double gcdTimeLeft;
	
	// #1 input neuron
	int holyPower; 

	// not needed by bot
	const int maxHolyPower = 5;

	// #2 input neuron
	bool consecrationActive;

	// #3 input neuron
	double consecrationActiveTimeLeft;
	double consecrationTimeTillNextDamage;

	// #4 input neuron
	double consecrationCdLeft;

	// #5 input neuron
	bool judgmentBuffActive; 
	
	// #6 input neuron
	double judgmentCdLeft;

	// #7 input neuron
	bool avengingWrathActive;
	double avengingWrathTimeLeftOnBuff;
	double avengingWrathCdLeft;
	
	// #8 input neuron
	double holyShockCdLeft;

	// #9 input neuron and #10 input neuron
	double crusaderStrikeCdLeftOne;
	double crusaderStrikeCdLeftTwo;

	// #11 input neuron
	int crusaderStrikeCharges;
	const int crusaderStrikeMaxCharges = 2;

	// #12 input neuron
	bool holyPrismCdLeft;

	// #13 input neuron
	bool holyAvengerActive;
	double holyAvengerActiveTimeLeft;
	double holyAvengerCdLeft;

	double hammerOfWrathCdLeft;

	// #14 input neuron to #17 input neuron[night fae covenant ability] 
	bool blessingOfSpringActive, blessingOfSummerActive, blessingOfFallActive, blessingOfWinterActive;

	// #18 and #19 are for trinkets to tell its available to be used, #20 is if the dot is on dummy
	bool dreadFireAvailable, glyphAvailable, glyphActiveOnTarget;  
	double glyphTimeOnTargetLeft, glyphTimeTillNextAttack;

	// neuron input #21
	double shieldOfRighteousCdLeft;

	bool glimmerOfLightActive;

	double meleeTimeTillNextSwing;

	// cast functions so agent can damage the dummy, the maintenance of all skills/spells/abilities will be done by other functions
	// normal holy paladin abilities
	void castConsecration(); void castCrusaderStrike(); void castJudgment(); void castShieldOfRighteous(); void castAvengingWrath(); void castHolyShock(); void castHolyAvenger();
	void castHolyPrism(); void castHammerOfWrath();

	// night fae covenant skill
	//void castBlessingOfSpring(); void castBlessingOfSummer(); void castBlessingOfFall(); void castBlessingOfWinter();

	// trinket useage - dreadfire does 10072 fire damage, 1.5 min cd; - glyph does 6510 over 10 seconds, arcane damage, 1.5 min cd;
	void castDreadFireVessel(); void castGlyphOfAssimilation();

	void consecration(); void crusaderStrike(); void judgment(); void shieldOfRighteous(); void avengingWrath(); void holyShock(); void holyAvenger(); void holyPrism();
	void hammerOfWrath(); void glyphOfAssimilation();
	//void blessingOfSpring(); void blessingOfSummer(); void blessingOfFall(); void blessingOfWinter(); 

	void reset();

	// melee is not a button agent pushes as it runs on its own. 
	void melee();

	void cycle();

	vector<double>& getInputs();
	void handleOutputs();
};

